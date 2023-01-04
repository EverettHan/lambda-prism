#ifndef CATCXCGMOperatorRunTransaction_h
#define CATCXCGMOperatorRunTransaction_h
/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CGMTransaction used to collect various data from CATTopOperators created
// on a specific CATGeoFactory.
//
// Use the following macros to make your code simple :
//
//   CATCXCGMOperatorRunTransactionBegin(name_of_your_transaction, CATGeoFactory*)
//   CATCXCGMOperatorRunTransactionEnd(name_of_your_transaction)
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
  

      // Start CATCXCGMOperatorRunTransaction
      //
      // Only ONE such transaction can be created : CATCXCGMOperatorRunTransactions CANNOT be nested.
      // (an error will be thrown)
      //
      // If MyCATGeoFactory is NOT NULL, only warnings issued by operators created on MyCATGeoFactory
      // will be collected.
      //
      CATCXCGMOperatorRunTransactionBegin(pTransaction, &MyCATGeoFactory)

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


      // End CATCXCGMOperatorRunTransaction
      CATCXCGMOperatorRunTransactionEnd(pTransaction)




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


       // Start CATCXCGMOperatorRunTransaction
       CATCXCGMOperatorRunTransactionBegin(pTransaction, MyCATGeoFactory, &MyInterruptFunction)
        
         // Creates and runs operators
         // ...
         // ...

       // End CATCXCGMOperatorRunTransaction
       CATCXCGMOperatorRunTransactionEnd(pTransaction)



     Within the Operator Run method :
     --------------------------------

        // Somewhere which is called REGULARLY

        // Retrieve the transaction
        CATCXCGMOperatorRunTransaction* pOperatorRunTransaction = (CATCXCGMOperatorRunTransaction*)CATCGMTransaction::Search(CatCGMOperatorRunTransaction);
 
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

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMOperatorRunTransaction.h"
#include "CATCGMWarningAdvanced.h"
#include "CATCGMDiagnosis.h"
#include "CATListPOfCATCGMDiagnoses.h"

class ExportedByCATTopologicalObjects CATCXCGMOperatorRunTransaction : public CATCGMOperatorRunTransaction
{
public :
  // Creation
  static CATCXCGMOperatorRunTransaction* Create(CATGeoFactory* ipFactory);

  static CATCXCGMOperatorRunTransaction* Create(CATGeoFactory* ipFactory, CATCGMInterruptFunction ipInterruptFunction);

  // Destructor
  virtual ~CATCXCGMOperatorRunTransaction();

  // New/Delete
  CATCGMNewClassArrayDeclare;  

  // Factory
  CATGeoFactory* GetFactory() const;

  // Warnings
  CATCGMWarning GetWarningMode() const;
  CATCGMWarningAdvanced GetWarningAdvancedMode(CATCGMWarningAdvanced iMode) const;

  void SetWarningMode(CATCGMWarning iMode);
  void AddWarningAdvancedMode(CATCGMWarningAdvanced iMode);
  
  void SetStoreWarningInTransaction(CATBoolean iAllowStorage);
  CATBoolean IsStoreWarningInTransactionAllowed() const;

  CATTopOpInError* GetWarnings();
  // AppendWarning will throw an error if _StoreWarning is false
  void AppendWarning(CATCGMDiagnosis* ipCGMDiagnosis);
  void RemoveAllWarnings();

  void ReadWarningDiagnosis(CATLISTP(CATCGMDiagnosis)& ioDiagnosisList);

protected:
  // Constructor
  CATCXCGMOperatorRunTransaction(CATGeoFactory* ipFactory, CATCGMInterruptFunction ipInterruptFunction);

  // Factory
  CATGeoFactory*             _pFactory;

  // Mode
  CATCGMWarning              _WarningMode;
  CATCGMWarningAdvanced      _WarningAdvancedMode;

  // Warning storage mode : TRUE (the default) if warnings are stored in the transaction 
  //                        FALSE              if they are not (i. e. stored in Operator)
  CATBoolean                 _StoreWarning; 

  // Liste des warnings
  CATLISTP(CATCGMDiagnosis)* _pWarningDiagnosisList;
};


#endif
