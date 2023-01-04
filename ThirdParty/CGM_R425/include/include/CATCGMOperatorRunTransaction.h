#ifndef CATCGMOperatorRunTransaction_h
#define CATCGMOperatorRunTransaction_h
/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CGMTransaction used to collect various data from CATTopOperators created
// on a specific CATGeoFactory.
//
// Use the following macros to make your code simple :
//
//   CATCGMOperatorRunTransactionBegin(name_of_your_transaction, CATGeoFactory*)
//   CATCGMOperatorRunTransactionEnd(name_of_your_transaction)
//
//=============================================================================
// Dec. 03 Creation                                                       HCN
// May. 04 Gestion des interruptions                                      HCN
// Jun. 05 Ajout de la donnee membre _StoreWarning et macros associees    FDN
// Nov. 05 La focntion d'interruption est maintenant gérée directement par
//         CATCGMTransaction                                              FDN
//=============================================================================
/*

  1) In order to collect all the warnings issued by CATTopOperators within
     a certain code span, use a code similar to the following example :
     ==================================================================
  

      // Start CATCGMOperatorRunTransaction
      //
      // Only ONE such transaction can be created : CATCGMOperatorRunTransactions CANNOT be nested.
      // (an error will be thrown)
      //
      // If MyCATGeoFactory is NOT NULL, only warnings issued by operators created on MyCATGeoFactory
      // will be collected.
      //
      CATCGMOperatorRunTransactionBegin(pTransaction, &MyCATGeoFactory)

        // Use this transaction to collect warnings
        pTransaction->SetWarningMode(Warning_On);


        // Creates and runs operators
        // Don't forget to set their warning mode
        // ...
        // ...


        // Collect the warnings issued by the operators
        CATTopOpInError* pTopOpInError = pTransaction->GetWarnings();
        if (pTopOpInError)
        {
          // Retrieve and Releases the CATCGMDiagnosis
          //...
        }


      // End CATCGMOperatorRunTransaction
      CATCGMOperatorRunTransactionEnd(pTransaction)




  2) In order to manage interruptions, use a code similar to the following example :
     ===============================================================================


     From the Operator Caller : 
     --------------------------

       // Implement Interrupt function

       CATBoolean MyInterruptFunction(int iProgressValue, int iProgressRange)
       {
         // Manage Progressbar ?...
         // iProgressValue, iProgressRange

         // Check whether the operator should break execution (user input etc...)

         if (The Operator Should be interrupted)
           return TRUE;
         else
           return FALSE:
       }


       // Start CATCGMOperatorRunTransaction
       CATCGMOperatorRunTransactionBegin(pTransaction, MyCATGeoFactory, &MyInterruptFunction)
        
         // Creates and runs operators
         // ...
         // ...

       // End CATCGMOperatorRunTransaction
       CATCGMOperatorRunTransactionEnd(pTransaction)



     Within the Operator Run method :
     --------------------------------

        // Somewhere which is called REGULARLY

        // Retrieve the transaction
        CATCGMOperatorRunTransaction* pOperatorRunTransaction = (CATCGMOperatorRunTransaction*)CATCGMTransaction::Search(CatCGMOperatorRunTransaction);
 
        if (pOperatorRunTransaction)
        {
          CATCGMInterruptFunction pInterruptFunction = pOperatorRunTransaction->GetInterruptFunction();

          if (pInterruptFunction)
          {
            // Compute progress information
            int ProgressValue = ...;
            int ProgressRange = ...;

            // Call the function
            CATBoolean MustBreakExecution = (*pInterruptFunction)(ProgressValue, ProgressRange);

            if (MustBreakExecution)
            {
              // Breaks the execution by throwing an exception or with any other way...
            }

          } // if (pInterruptFunction)

        } // if (pOperatorRunTransaction)

      
        The operator can also call CATBoolean CATExtTopOperator::MustInterruptExecution(int iProgressValue = 0, int iProgressRange = 0);

*/

#include "YP0LOGRP.h"
#include "CATCGMTransaction.h"
#include "CATCGMWarning.h"
#include "CATCGMWarningAdvanced.h"
//#include "CATListPOfCATCGMDiagnoses.h"
#include "CATCGMOperator.h"
#include "CATCGMNoMoreMemory.h"
#include "CATCGMProgressBar.h"
#include "CATCollec.h"

class CATTopOpInError;
class CATGeoFactory;
class CATCGMDiagnosis;


class ExportedByYP0LOGRP CATCGMOperatorRunTransaction : public CATCGMTransaction
{
public :
  // Creation
  static CATCGMOperatorRunTransaction* Create(CATGeoFactory* piFactory);

  static CATCGMOperatorRunTransaction* Create(CATGeoFactory* piFactory, CATCGMInterruptFunction iInterruptFunction);

  // Destructor
  virtual ~CATCGMOperatorRunTransaction();

  // Factory
  virtual CATGeoFactory* GetFactory() const = 0;

  // Warnings
  virtual CATCGMWarning GetWarningMode() const = 0;
  virtual CATCGMWarningAdvanced GetWarningAdvancedMode(CATCGMWarningAdvanced iMode) const = 0;

  virtual void SetWarningMode(CATCGMWarning iMode) = 0;
  virtual void AddWarningAdvancedMode(CATCGMWarningAdvanced iMode) = 0;

  virtual void SetStoreWarningInTransaction(CATBoolean iAllowStorage) = 0;
  virtual CATBoolean IsStoreWarningInTransactionAllowed() const = 0;

  virtual CATTopOpInError* GetWarnings() = 0;
  // AppendWarning will throw an error if _StoreWarning is false
  virtual void AppendWarning(CATCGMDiagnosis* ipCGMDiagnosis) = 0;
  virtual void RemoveAllWarnings() = 0;
  
protected:
  // Constructor
  CATCGMOperatorRunTransaction();
};

//-----------------------------------------------------------------------------
// Macro CATCGMOperatorRunTransactionBegin
//-----------------------------------------------------------------------------
#define CATCGMOperatorRunTransactionBegin(pTransaction, ipFactory)                                     \
CATCGMOperatorRunTransaction* volatile pTransaction = CATCGMOperatorRunTransaction::Create(ipFactory); \
if (!pTransaction) CATCGMNoMoreMemory(sizeof(CATCGMOperatorRunTransaction));                           \
CATTry                                                                                                 \
{

//-----------------------------------------------------------------------------
// Macro CATCGMOperatorRunTransactionItrBegin
//-----------------------------------------------------------------------------
#define CATCGMOperatorRunTransactionItrBegin(pTransaction, ipFactory, ipInterruptFunction)                                  \
CATCGMOperatorRunTransaction* volatile pTransaction = CATCGMOperatorRunTransaction::Create(ipFactory, ipInterruptFunction); \
if (!pTransaction) CATCGMNoMoreMemory(sizeof(CATCGMOperatorRunTransaction));                                                \
CATTry                                                                                                                      \
{

//-----------------------------------------------------------------------------
// Macro CATCGMOperatorRunTransactionEnd
//-----------------------------------------------------------------------------
#define CATCGMOperatorRunTransactionEnd(pTransaction)                                                  \
}                                                                                                      \
CATCatch(CATError, Error)                                                                              \
{                                                                                                      \
  if (pTransaction)                                                                                    \
{                                                                                                      \
    delete pTransaction;                                                                               \
    pTransaction = NULL;                                                                               \
}                                                                                                      \
  CATRethrow;                                                                                          \
}                                                                                                      \
CATEndTry                                                                                              \
if (pTransaction)                                                                                      \
{                                                                                                      \
  delete pTransaction;                                                                                 \
  pTransaction = NULL;                                                                                 \
}

//-----------------------------------------------------------------------------
// Macro CATCGMOperatorRunTransactionInactiveWarningStorage(iFactory)
//       iFactory is used to identify the Transaction. 
//       Typically, iFactory is the result of (MyCGMOperator)->GetFactory() 
//-----------------------------------------------------------------------------
#define CATCGMOperatorRunTransactionInactiveWarningStorage(iFactory)                                   \
CATCGMOperatorRunTransaction* volatile pMacroTransaction = (CATCGMOperatorRunTransaction*)CATCGMTransaction::Search(CatCGMOperatorRunTransaction);  \
CATBoolean WarningStorageAllowed = FALSE;            \
if (pMacroTransaction)                                                                                 \
{                                                                                                      \
  CATGeoFactory * localfacto = pMacroTransaction->GetFactory();                                        \
  CATGeoFactory * transfacto = NULL;                                                                   \
  CATGeoFactory * userfacto = NULL;                                                                   \
  if (localfacto)                                                                                      \
    transfacto = localfacto->GetImplicitGeoFactory();                                                     \
  if (iFactory)                                                                                        \
    userfacto = iFactory->GetImplicitGeoFactory();                                                         \
  WarningStorageAllowed =  pMacroTransaction->IsStoreWarningInTransactionAllowed();         \
  if (userfacto == transfacto)                                                                         \
    pMacroTransaction->SetStoreWarningInTransaction(FALSE);                                            \
  else                                                                                                 \
    pMacroTransaction = NULL;                                                                          \
}                                                                                                      \
CATTry                                                                                                 \
{

//-----------------------------------------------------------------------------
// Macro CATCGMOperatorRunTransactionReactiveWarningStorage()
//-----------------------------------------------------------------------------
#define CATCGMOperatorRunTransactionReactiveWarningStorage()                                           \
}                                                                                                      \
CATCatch(CATError, Error)                                                                              \
{                                                                                                      \
  if ((pMacroTransaction)&& (WarningStorageAllowed == TRUE) && CATCGMTransaction::Search(CatCGMOperatorRunTransaction))   \
    pMacroTransaction->SetStoreWarningInTransaction(TRUE);                                             \
  CATRethrow;                                                                                          \
}                                                                                                      \
CATEndTry                                                                                              \
if ((pMacroTransaction)&& (WarningStorageAllowed == TRUE) && CATCGMTransaction::Search(CatCGMOperatorRunTransaction) )                                             \
{                                                                                                      \
  pMacroTransaction->SetStoreWarningInTransaction(TRUE);                                               \
}


#endif
