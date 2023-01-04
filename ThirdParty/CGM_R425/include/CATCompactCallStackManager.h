#ifndef CATCompactCallStackManager_h
#define CATCompactCallStackManager_h
// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// CATCompactCallStack : Debug classes to manage various call stacks leading to an instruction
//
//=============================================================================
// Usage notes:
//   for debug purpose only: to scan and differentiate various call stacks leading to an instruction
//
//   may be used in batch mode and in debugger mode
// ----------------------------------------------------------------------------
// not published yet
#include "LesBonnesRecettesDuPereLochard.h"
LesBonnesRecettesDuPereLochard(_CompactCallStack090511,"(Les bonnes recettes du père Lochard: 090511) Usage des call stack compactes");
//=============================================================================
//
// sample of use :
// 1) in the interesting code block, on a specific condition
//   if (condition)
//     {
//      static CATCompactCallStackManager StackManager();
//      int NewStack = StackManager.StackChangeConditionalBreakPoint();
//     }
// 2) a)then a breakpoint may be put in CATCompactCallStackManager::StackChangeBreakPoint()
//    this method will be called everytime there is a new call stack leading to the interesting code block
//    N.B the call stack analysis depth may be changed with a debugger when the breakpoint is reached
//
//    b) an interesting breakpoint may also be set in CATCompactCallStackManager::StackCountBreakPoint()
//    this method is called at everytime the interesting code block is reached
//    and it gives the number of calls for this specific call stack
//=============================================================================
//=============================================================================
// 24/11/06 NLD Introduction de la notion de stack compacte dans CATGeoDebugCGM_CATCGMFollowTag.cpp
// 06/05/11 NLD Decoupage et isolation des données de gestion des traces compactes
//              et mise en place d'un système de points d'arrets conditionnels
//              sur les nouvelles stacks
// 09/05/11 NLD Creation de CATCompactCallStackManager en fichier isolé
// 12/05/11 NLD Ajout de la possibilité de definir un filtre externe:
//              Ajout CATCompactCallStackManagerFilterResult et CATCompactCallStackManagerFilterFunction
//              Ajout SetFilter() _FilterFunction et _FilterData dans CATCompactCallStackManager
//              Ajout de la gestion des poids
// 17/05/11 NLD Ajout argument optionnel iNumStack à Dump() pour dump d'une pile particulière
//              Ajout _NumCurrentStack et GetCurrentStackNumber()
//=============================================================================
#include <CATListOfInt.h>
#include <CATListOfDouble.h>
#include <CATListPV.h>
#include <CATMathematics.h>
#include <CATStackTrace.h>

//================================================================================================
// CATCompactCallStackMethodRecord: elementary record for a callstack method
//================================================================================================
// pour chaque methode de pile d'appel on a un enregistrement de description:
class ExportedByCATMathematics CATCompactCallStackMethodRecord
   {
    //--------------------------------------------------------------------------------------------
    public:
    //--------------------------------------------------------------------------------------------
    int   _Num ;
    int   _Length ; // au lieu de size_t NLD051206
    char* _Method ;
    void* _NextRecord ;
    //int   _Printed ; // (finalement non necesaire) devrait etre renommé; en _ZTrav? zone de travail applicative
    CATCompactCallStackMethodRecord();
    ~CATCompactCallStackMethodRecord();
   };


//================================================================================================
// CATCompactCallStackData: records for a set of callstacks
//================================================================================================
class ExportedByCATMathematics CATCompactCallStackData
   {
    //--------------------------------------------------------------------------------------------
    public:
    //--------------------------------------------------------------------------------------------

    CATCompactCallStackMethodRecord* _FirstRecord ;

    //------------------------------------------------------------------------------------------------
    CATCompactCallStackData();

    //------------------------------------------------------------------------------------------------
    ~CATCompactCallStackData();

    // Recherche (avec création éventuelle) du numero d'enregistrement de la méthode
    // --------------------------------------------------------------- -------------
    // indique s'il est nouveau (dans iIsNew) et rend (dans tous les cas) le pointeur vers l'enregistrement
    int FindMethodRecordNum(char* MethodName, int iLgMethodName,
                            int& oIsNew, CATCompactCallStackMethodRecord*& oRecord);
   };

//================================================================================================
// CATCompactCallStackManager types: types for CATCompactCallStackManager
//================================================================================================
// Filter result
typedef enum
  {
   CATCompactCallStackManagerFilter_Keep      = 0, // method will be kept in the callstack (not filtered)
   CATCompactCallStackManagerFilter_Eliminate = 1, // method will be eliminated from the callstack
   CATCompactCallStackManagerFilter_Root      = 2  // method will be considered as callstack root
  }CATCompactCallStackManagerFilterResult;

// Filter function
//   ioData is an optional user data transmitted by manager
//   iMethod is the method to filter
//
typedef CATCompactCallStackManagerFilterResult (*CATCompactCallStackManagerFilterFunction) (void* ioData, char* iMethod);

//================================================================================================
// CATCompactCallStackManager: Conditional break point manager (break point on new CallStack) NLD060511
//================================================================================================
class ExportedByCATMathematics CATCompactCallStackManager
   {
    //--------------------------------------------------------------------------------------------
    private:
    //--------------------------------------------------------------------------------------------
    int   _DumpAtTheEnd;
    void* _FilterData;
    CATCompactCallStackManagerFilterFunction _FilterFunction;
    int   _WithWeights;
    int   _NumCurrentStack;

    //--------------------------------------------------------------------------------------------
    //public:
    //--------------------------------------------------------------------------------------------
    static const int _LgStackLine   = 1024;
    char*                   _Meth ;
    CATCompactCallStackData _CompactData;
    int                     _StackDepth;        // profondeur effective utilisée
    // Numeros d'enregistrements pour la stack courante
    CATListOfInt            _CurStack;          //
    CATListPV               _AllStacks;         // pointeurs vers toutes les piles numeriques
    CATListOfInt            _AllStacksCounters; // nombre d'occurences d'appels de chaque pile
    CATListOfDouble         _AllStacksWeights;  // poids total de chaque pile

    public:
    CATCompactCallStackManager();
    //------------------------------------------------------------------------------------------------
    ~CATCompactCallStackManager();

    //------------------------------------------------------------------------------------------------
    // Stack maximum depth definition (default: unlimited depth (only limited to 40 by System framework)
    //------------------------------------------------------------------------------------------------
    void SetStackDepth(int iStackDepth);

    //------------------------------------------------------------------------------------------------
    // BreakPoint at CallStack change (called if new call stack)
    //------------------------------------------------------------------------------------------------
    void  StackChangeBreakPoint(int& ioStackDepth); // (0: unlimited) stack depth to manage (modifiable under debugger)

    //------------------------------------------------------------------------------------------------
    // BreakPoint at each call
    //------------------------------------------------------------------------------------------------
    void  StackCountBreakPoint(int  iNumStack,
                               int  iNbCallForThisStack,
                               int& ioStackDepth   // (0: unlimited) stack depth to manage (modifiable under debugger)
                              );
    //------------------------------------------------------------------------------------------------
    // BreakPoint at CallStack change management (returns 0 if no breakpoint)
    // (calls StackChangeBreakPoint() if new stack)
    //------------------------------------------------------------------------------------------------
    int StackChangeConditionalBreakPoint(double iWeight=1.0);
    // (restricted use) same thing, but with user gotten callstack (GetTrace() must have been called on this stack)
    int StackChangeConditionalBreakPoint(CATStackTrace& iCallStackTrace, double iWeight=1.0);

    //------------------------------------------------------------------------------------------------
    // Filter function definition
    // (with optional filter data that will be sent to filter function)
    //------------------------------------------------------------------------------------------------
    void SetFilter(CATCompactCallStackManagerFilterFunction iFilterFunction = NULL,
                   void*                                    iFilterData     = NULL) ;

    //------------------------------------------------------------------------------------------------
    // Dump of all CallStacks (immediate dump, or dump at manager deletion)
    //------------------------------------------------------------------------------------------------
    void Dump(int iImmediateDump=1, // == 1 for immediate dump,    ==0: for dump at manager deletion
              int iNumStack=0       // != 0 for dump of one stack, ==0: for dump of all stacks
             );

    //------------------------------------------------------------------------------------------------
    // Access to current stack number (stack used at last call)
    //------------------------------------------------------------------------------------------------
    int GetCurrentStackNumber();

    //--------------------------------------------------------------------------------------------
    private:
    //--------------------------------------------------------------------------------------------
    int StackChangeConditionalBreakPointWork(CATStackTrace& iCallStackTrace, int iBeginStack, double iWeight);

   };

#endif
