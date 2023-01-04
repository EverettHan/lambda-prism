#ifndef CATCGMMultiCopyPasteTransaction_h
#define CATCGMMultiCopyPasteTransaction_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
//
//==========================================================================
/**
 * 
 *        Identify a specific transaction 
 * allowing underneath (deep level) treatment to optimise 
 * multiple COPY / PASTE or transformation operation between OldFactory and NewFactory
 *
 *
 *              **** INTERNAL VERY SPECIFIC USE ****
 *
 * Objective :  To optimize the final model size during copy or transformation of several bodies 
 * by keeping geometrical sharing between cells.
 * 
 * Important notice : The recommanded method for this optimisation is not to use this transaction but 
 * is to call the CloneManager / Transfomanager in a single shot for multiple bodies.
 *
 * This optimisation apply only to following operator :
 * - Clonemanager 
 * - TransfoManager
 * - CATBodyDatumiser
 * - CATDynTransfomation
 *
 * This optimisation is active only when option
 * are kept invariant between successive call , theses options are :
 * - input factory.
 * - output factory.
 * - duplicate mode.
 * - transformation value ( in case of transformation ).
 *
 * Limitations : 
 * - In case of transformation , this optimisation is valid only for isometry.
 * - Until the end of the transaction , bodies are kept in a non frozen state. So they
 * must not be use as input of any other operator before the end of the transaction.
 *  
 *        In Case of multi-threaded application,
 * Call-back for end of a particuliar transaction is done
 * at the end of the last alive transaction
 * (transmition of callback can be done ...)
 *
 * Example of use ( the transaction is put at a high level in the code ) :
 *
 *     CATCGMMultiCopyPasteTransactionBeginSafe(conchita,OldFactory,NewFactory) 
 *     {
 *         // --> multiple copy / paste between factories 
 *         // ( CloneManager , TransfoManager , CATBodyDatumiser ... )
 *     }
 *     CATCGMMultiCopyPasteTransactionEnd(conchita);
 */

#include "YP0LOGRP.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATCGMTransaction.h"
#include "CATCloneManager.h"
#include "CATCGMAttrReframeDesignLimits.h"

class CATGeoFactory;
class CATMapGeoToAssoc;
class CATSoftwareConfiguration;
class CATMathTransformation;
class CATCGMObject;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByYP0LOGRP CATCGMMultiCopyPasteTransaction : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // CLIENT : life of one CATCGMMultiCopyPasteTransaction Object identify a transaction
  //------------------------------------------------------------------
  CATCGMMultiCopyPasteTransaction();
  CATCGMMultiCopyPasteTransaction( CATGeoFactory * iInputFactoryExpected  ,
                                   CATGeoFactory * iOutputFactoryExpected );
  CATCGMNewClassArrayDeclare;   

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  // in case of exception throw with longjmp ..
  //------------------------------------------------------------------
  virtual void Clean();

  //-----------------------------------------------------------------------------------------------------------------------
  // RESTRICTED USAGE for sheetmetal only ( seen with FAY )
  // During the multi copy paste transaction , the freeze mode of the bodies is desactived until the end of the transaction
  // For specific treatement , sheet metal needs to restore temporary the freeze mode
  //  Note : 
  //  - the freeze mode must been absolutely be reset to 0 at the end
  //  - no copy of datas must be done with freeze mode active
  // Sample of code :
  //   #include "CATCGMMultiCopyPasteTransaction.h"
  //   ....
  //   CATCGMMultiCopyPasteTransaction * MultiCopyPasteTransaction =  
  //     ( CATCGMMultiCopyPasteTransaction * ) CATCGMTransaction::Search(CatCGMMultiCopyPasteManagement);
  //	CATTry 
  //  {
  //    int previousmode = MultiCopyPasteTransaction -> ChangeTemporaryFreezeMode ( 1 );
  //    ***** your local treatment here with freeze mode actif **********
  //    MultiCopyPasteTransaction -> ChangeTemporaryFreezeMode ( previousmode );
  //  }
  //  CATCatchOthers
  //  {
  //    MultiCopyPasteTransaction -> ChangeTemporaryFreezeMode ( previousmode );
  //    CATRethrow;
  //  }
  //  CATEndTry;
  //  ***** use CATBodyDatumiser here to copy datas with freeze mode inactive **********
  //------------------------------------------------------------------------------------------------------------------------
  int ChangeTemporaryFreezeMode ( const int iFreezeMode = 0 );

protected:
  // Init transaction at beginning
  void InitTransaction ( CATGeoFactory            *  iInputImplicitFactory      ,
                         CATGeoFactory            *  iOutputFactory             , 
                         CATSoftwareConfiguration *  iVersion                   ,
                         CATMathTransformation    *  iTransformation            ,
                         CATCloneManagerType         iCloneType                 ,
                         short                    &  ioOnlyBodiesInInput        ,
                         CATMapGeoToAssoc         *& oAssocList                 ,      
                         int                      &  oEligibleForMultiCopyPaste );

  // IsTransformationCompatible
  int IsTransformationCompatible ( CATGeoFactory         * iOutputFactory      ,
                                   CATMathTransformation * iMathTransformation ) const;

  // GetInputAndOutputFactory
  void GetInputAndOutputImplicitFactory ( CATGeoFactory *& oInputImplicitFactory  ,
                                          CATGeoFactory *& oOutputImplicitFactory ) const;
  
  // AddBodyForCompleted ( return TRUE if the body has been added )
  CATBoolean AddBodyForCompleted ( CATICGMObject * iBody );

  // Constructor initialisation
  void Init();

  // IsMultiCopyPasteProtected
  int IsMultiCopyPasteProtected ( CATICGMObject * iDeletedObject , int ReleaseToBeDone = 1 );

friend class CATExtCloneManager;
friend class CATGeoFactoryCGM;
friend class CATCXBodyDatumiser;
friend class CATCXTopology;

protected:
  CATBoolean     _OutputFactoryStarter;
  CATCGMObject * _OutputFactoryStart;
  CATULONG32     _OutputFactoryCounter;

  CATSoftwareConfiguration      * _Version;                       // version
  CATMapGeoToAssoc              * _AssocList;                     // association list between input and output elements
  CATGeoFactory                 * _InputImplicitFactory;          // Input implicit factory
  CATGeoFactory                 * _OutputImplicitFactory;         // Output implicit factory
  CATGeoFactory                 * _InputImplicitFactoryExpected;  // Expected implicit input factory 
  CATGeoFactory                 * _OutputImplicitFactoryExpected; // Expected implicit output factory 
  CATMathTransformation         * _MathTransformation;            // Transformation attendue si TransfoManager , = NULL si CloneManager
  int                             _InitTransformation;            // Init de la transformation ?
  int                             _FreezeMode;                    // FreezeMode ( 0 by default )
  CATCloneManagerType             _CloneType;                     // Type of clone
  short                           _OnlyBodiesInInput;             // = 1 , if only bodies in input
  short                           _BodyCleanerCalled;
  CATCGMOperator                * _BodyCleanerOperator;           // Bodies cleaner operator
  CATLISTP(CATICGMObject)         _BodyListToFreeze;              // Bodies to complete
  CATCGMAttrReframeDesignLimits * _ReframeAnchorLink;             // Chaine Attribut sur Image _Out des CATAssociation
};

#define CATCGMMultiCopyPasteTransactionBeginSafe(conchita, iInputFactory,iOutputFactory )  \
CATCGMMultiCopyPasteTransaction *volatile conchita = new CATCGMMultiCopyPasteTransaction(iInputFactory, iOutputFactory); \
CATTry   \
{  

#define CATCGMMultiCopyPasteTransactionEnd(conchita)  \
  if ( conchita ) { conchita->Clean(); delete conchita; conchita=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( conchita ) { conchita->Clean(); delete conchita; conchita=NULL; } \
  CATRethrow; \
}  \
CATEndTry 



#endif

