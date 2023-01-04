#ifndef CATReturnManager_H
#define CATReturnManager_H
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATReturnManager : General and simple exception return mechanism for automatic stack objects free
//                    Suggested use in case of big objects, objects using internal allocations,
//                    or handlers
//
// CAUTION: imbedded exception will be raised at object deletion
//
//=============================================================================
//
// #Retourneur  (gestionnaire de retour)
//
// #Routourneur ("la routourne a tourné"
//               on va arreter de subir les MLKs dus aux options DS de gestion des exceptions
//               et aux compilateurs)
//
// #Rentourneur ("se rentourner")
//
//=============================================================================
#include "LesBonnesRecettesDuPereLochard.h"
LesBonnesRecettesDuPereLochard(_CATReturnManager061214,"(Les bonnes recettes du père Lochard: 06/12/14) Use of CATReturnManager for exception exit with no leak of objects on stack");
//
// Usage notes:
// -----------
// - object must be declared at first bracket level of calling method,
//   or, in any case, at a higher level than all objects to free
// - if exception to raise, the exception must be given to the object
// - call method must exit by return
// - exception will be automatically raised at return
//   after deletion of all objects on stack
//
// Sample of use 
// -------------
// 1: (KO: LEAK)    old code with memory leak
// 2: (SUGGESTED)   new code with no leak, using CATReturnManager
// 3: (POOR)        new code with no leak, using allocation on heap
//    (BAD)         same, but without volatile declaration: unguaranteed pointer. May lead to abend
// 4: (RECOMMENDED) new code with object freeing using {}
//
//                                                           ____________
// 1) old code                                               | KO: LEAK |
//    --------                                               ------------
//    void SubroutineWithExceptionThrow()
//    {
//     CATThrowForNullPointer();
//    }
//    void SubroutineWithPotentialLeak()
//    {
//     if ()
//       {
//                                                //  XXXXXX     X                       XXX      XXXX                       XXX
//                                                // XX    X    XX                        XX       XX                         XX
//                                                // XX        XXXXX    XXXXX    XXXXX    XX  XX   XX       XXXXX    XXXXX    XX  XX
//         CATXXX BigObjectOnStackInMemoryLeak(); //  XXXXX     XX          X   XX   XX   XX XX    XX      XX    X       X    XX XX
//                                                //      XX    XX     XXXXXX   XX        XXX      XX      XXXXXXX  XXXXXX    XXX
//                                                // X    XX    XX XX  X   XX   XX   XX   XX XX    XX  XX  XX       X   XX    XX XX
//                                                // XXXXXX      XXX   XXXXX X   XXXXX   XXX  XX  XXXXXXX   XXXXX   XXXXX X  XXX  XX
//                                                // 
//
//        this->SubroutineWithExceptionThrow();
//       }
//    }
//
//                                                           _______________
// 2) new code (fixed with return manager)                   | SUGGESTED   |
//    --------                                               ---------------
//    void SubroutineWithPotentialLeak()
//    {
//     CATReturnManager ReturnManager;
//     if ()
//       {
//        CATXXX BigObjectOnStackInMemoryLeak();
//
//        CATTry
//          {
//           this->SubroutineWithExceptionThrow();
//          }
//        CATCatch(CATError, ErrorCaught)
//          {
//           ReturnManager.SetError(ErrorCaught); // exception storage
//           return;                              // method exit with all levels {} closing and then exception throw
//          }
//        CATEndTry
//       }
//    }
//
//
//                                                           ________
// 3) other code (fixed with allocation on heap)             |(POOR)|
//    ----------                                             --------
//    void SubroutineWithPotentialLeak()
//    {
//     if ()
//       {
//        CATXXX  * volatile BigObject = new CATXXX();  // <-- Poor: useless and costly allocation
//     // CATXXX  *          BigObject = new CATXXX();  // <-- Bad : unguaranteed pointeur value after exception catch
//        CATError* volatile Error     = NULL;
//        CATTry
//          {
//           this->SubroutineWithExceptionThrow();
//          }
//        CATCatch(CATError, ErrorCaught)
//          {
//           Error = ErrorCaught;
//          }
//        CATEndTry
//        CATSysDeletePtr(BigObject);
//        if (Error)
//           CATThrow(Error);
//       }
//    }
//
//                                                           _________________
// 4) other code (fixed with cycle life management using {}) | (RECOMMENDED) |
//    ----------                                             -----------------
//    void SubroutineWithPotentialLeak()
//    {
//     CATError* volatile Error     = NULL;
//     if ()
//       {
//        CATXXX  BigObject();
//        CATTry
//          {
//           this->SubroutineWithExceptionThrow();
//          }
//        CATCatch(CATError, ErrorCaught)
//          {
//           Error = ErrorCaught;
//          }
//        CATEndTry
//       }
//     if (Error)
//        CATThrow(Error);
//    }
//
//=============================================================================
// 27/11/14 NLD Creation
//              - CATReturnManager constructor
//              - SetError()
//              - SetErrorForNullPointer()
//              - GetError()
// 18/05/20 NLD livraison portage (R424 / TECHNO / VS2019) modification IK8
//              macro CATReturnManager_Cpp11_NOEXCEPT <==> noexcept
//=============================================================================
#include <CATMathematics.h>

// ++IK8 Exceptions post C++11 support 
#if (!defined(_AIX_SOURCE) || defined(__ibmxl__)) // All platforms but non C++11 AIX
#define CATReturnManager_Cpp11_NOEXCEPT(a) noexcept(a)
#else
#define CATReturnManager_Cpp11_NOEXCEPT(a)
#endif
// ++IK8 

class CATError;
class ExportedByCATMathematics CATReturnManager
{
             //      -----------------------------------------------------------
 private   : // ----- Private   constructors
             //      -----------------------------------------------------------

     // Copy constructor
                                                 CATReturnManager              (const CATReturnManager&);

     // Operator '=' (overloaded) 
                                                 CATReturnManager& operator =  (const CATReturnManager&);

             //      ----------------------------------------------------------
 public :    // ----- Public    methods
             //      ----------------------------------------------------------

     //              ----------------------------------------------------------
     // ------------- Constructors
     //              ----------------------------------------------------------
     // Default constructor
                                                 CATReturnManager              ();

     //              ----------------------------------------------------------
     // ------------- Destructor
     //              ----------------------------------------------------------
   virtual                                      ~CATReturnManager() CATReturnManager_Cpp11_NOEXCEPT(false);


     // @nodoc @nocgmitf
     // Set error to raise at object deletion
     // (previous error is replaced without flush in case of multiple calls)
                 void                            SetError                      (      CATError                                    *  iError                 );

     // @nodoc @nocgmitf
     // Set error to raise at object deletion (internally created error equivalent to CATThrowForNullPointer() error)
                 void                            SetErrorForNullPointer        (                                                                            );

     // @nodoc @nocgmitf
     // Set error to raise at object deletion
                 CATError                     *  GetError                      (                                                                            );


   //===========================================================================
   // --- Data
   //===========================================================================

 public    :
 protected :
 private   :
     //                                          ------------------------------- Error to raise at object deletion
                 CATError                     *  _Error;
} ;

#endif
