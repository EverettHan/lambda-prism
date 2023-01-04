#ifndef CATCGMFactoryTransaction_h
#define CATCGMFactoryTransaction_h
/* -*-C++-*-*/
//======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//======================================================================================
// NOTA BENE : IL N'EST PAS PREVU QU'ON PUISSE EFFECTUER DES FERMETURES DE DOCUMENTS 
//                     AU COURS DE CES TRANSACTIONS EXPLICITES
//  HEADER IMPLEMENTATION : INTERDICTION D'INCLURE DANS HEADER CAA
//--------------------------------------------------------------------------------------
// Declaration de Transaction explicite sur Factory/Document geometrique V5
//    pour pouvoir enclencher/reporter des traitements automatiques 
//    en fonction du contexte de l'environnement
//=============================================================================
/*
            CATCGMFactoryBegin(session,Factory) 
            {
                // ...  
            }
            CATCGMFactoryEnd(session);

   ...

            CATCGMDocumentBegin(session,Document) 
            {
                // ...  
            }
            CATCGMDocumentEnd(session);

   ...

            CATCGMFactoryBeginODT(session,Inputs,OldResults) 
            {
                // ...  
            }
            CATCGMFactoryEndODT(session,NewResults,NothingTODO);
*/
//
//==========================================================================
#include "ExportedByGeometricObjects.h"
#include "CATErrorMacros.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMTransaction.h"
#include "CATBoolean.h"
#include "CATCGMTransactionControl.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATDocument;

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByGeometricObjects CATCGMFactoryTransaction : public CATCGMTransaction
{
public :

  //-------------------------------- 
  // Transaction CATPart
  //-------------------------------- 
  static CATCGMFactoryTransaction *Create(CATDocument *Document, CATCGMTransactionControl *iManage = NULL);

  //-------------------------------- 
  // Transaction NCGM ODT N1
  //-------------------------------- 
  static CATCGMFactoryTransaction *Create(const CATLISTP(CATICGMObject) & Inputs,  const CATLISTP(CATICGMObject) & OldResults,
                                          CATCGMTransactionControl *iManage = NULL);

  //-------------------------------- 
  // Transaction NCGM
  //-------------------------------- 
  static CATCGMFactoryTransaction *Create(CATGeoFactory *Factory,  CATCGMTransactionControl *iManage = NULL);

  
  //-------------------------------- 
  // Cycle de Vie
  //-------------------------------- 
  virtual ~CATCGMFactoryTransaction();

  CATCGMNewClassArrayDeclare;  


  //-------------------------------- 
  // Decodage 
  //-------------------------------- 
  INLINE CATGeoFactory          *GetFactory()  const;
  INLINE CATDocument            *GetDocument() const;
  INLINE void                    GetControl(CATCGMTransactionControl &ioCtrl) const;

  //-------------------------------- 
  // Achevement 
  //-------------------------------- 
  int  FinishOKAY(CATLISTP(CATICGMObject) * pNewResults = NULL, CATCGMTransactionControl *ioControls = NULL);
  void FinishKO(CATError *iError);

  static  void ManageControlFailure();
  virtual void Snapshot(short i0Before_1After_2Error);

  //------------------------------------------------------------------
  // INTERNAL : virtual de CATCGMTransaction 
  //------------------------------------------------------------------
  virtual void Clean();


protected:


  void SomeControlFailed(const char Message[]);

  CATCGMFactoryTransaction(CATDocument                    * Document, 
                CATGeoFactory                  * iFactory, 
                CATCGMTransactionControl       & iManage,
                const CATLISTP(CATICGMObject)  * pInputs,
                const CATLISTP(CATICGMObject)  * pOldResults );

  CATGeoFactory                   *_Factory;
  CATDocument                     *_Document;

  CATLISTP(CATICGMObject)         *_Inputs;
  CATLISTP(CATICGMObject)         *_OldResults;
  CATLISTP(CATICGMObject)         *_NewResults;

  CATCGMTransactionControl        _Management;
  CATBoolean                      _DedicatedODT;
  CATBoolean                      _UnderControl;

  
  //-----------------------------------------
  //  Renvoie TRUE si necessite ExtendedFactory
  //-----------------------------------------
  static CATCGMFactoryTransaction * Create(CATDocument                    * Document, 
                                           CATGeoFactory                  * iFactory, 
                                           CATCGMTransactionControl       & ioManage,
                                           const CATLISTP(CATICGMObject)  * pInputs ,
                                           const CATLISTP(CATICGMObject)  * pOldResults );
  
  
  friend class CATCGMFeatureMonitor;

private :
  CATLONG32                              _NbControlFailed; // En phase de controle : Nombre d'anomalie decouverte


};

//-----------------------------------------
//  GetFactory() ....
//-----------------------------------------
INLINE CATGeoFactory *CATCGMFactoryTransaction::GetFactory() const
{
  return _Factory;
}

//-----------------------------------------
//  GetDocument() ....
//-----------------------------------------
INLINE CATDocument *CATCGMFactoryTransaction::GetDocument() const
{
  return _Document;
}

INLINE void CATCGMFactoryTransaction::GetControl(CATCGMTransactionControl &ioCtrl) const
{
  ioCtrl = _Management;
}


//------------------------------------------------------------------------------ 
//  Macro d'acces a une transaction sur GeoFactory V5
//  Macro d'acces a une transaction sur Document V5
//------------------------------------------------------------------------------ 
#define CATCGMFactoryBegin(session,Factory)  \
CATCGMFactoryTransaction *volatile session = CATCGMFactoryTransaction::Create(Factory); \
CATTry  \
{

#define CATCGMFactoryBeginMngt(session,Factory,Manage)  \
CATCGMFactoryTransaction *volatile session = CATCGMFactoryTransaction::Create(Factory,Manage); \
CATTry  \
{

// IK8 FIX ERROR4 BEGIN
#define _CATCGMFactoryEnd(session)                                  \
        if ( session )                                              \
        {                                                           \
            int  KO##session = session->FinishOKAY();               \
            delete session;                                         \
            session=NULL;                                           \
            if ( KO##session )                                      \
                CATCGMFactoryTransaction::ManageControlFailure();   \
        }                                                           \
    }

#define CATCGMFactoryEndNoCatch(session)                            \
    _CATCGMFactoryEnd(session)                                      \
    CATEndTry
    
#define CATCGMFactoryEnd(session)                                   \
    _CATCGMFactoryEnd(session)                                      \
    CATCatch(CATError, error)                                       \
    {                                                               \
      if ( session )                                                \
      {                                                             \
        session->FinishKO(error);                                   \
        delete session;                                             \
        session=NULL;                                               \
      }                                                             \
      CATRethrow;                                                   \
    }                                                               \
    CATEndTry

// OLD CODE
// #define CATCGMFactoryEnd(session)  \
  // if ( session ) \
  // { \
    // int  KO##session = session->FinishOKAY(); \
    // delete session; \
    // session=NULL; \
    // if ( KO##session ) \
      // CATCGMFactoryTransaction::ManageControlFailure(); \
  // } \
// } \
// CATCatch(CATError, error) \
// {  \
  // if ( session ) \
  // { \
    // session->FinishKO(error); \
    // delete session; \
    // session=NULL; \
  // } \
  // CATRethrow; \
// }  \
// CATEndTry
// IK8 FIX ERROR4 END



#define CATCGMDocumentBegin(session,Document)  \
CATCGMFactoryTransaction *volatile session = CATCGMFactoryTransaction::Create(Document); \
CATTry  \
{

#define CATCGMDocumentBeginMngt(session,Document,Manage)  \
CATCGMFactoryTransaction *volatile session = CATCGMFactoryTransaction::Create(Document,Manage); \
CATTry  \
{


#define CATCGMDocumentEnd(session)  CATCGMFactoryEnd(session)

//------------------------------------------------------------------------------ 
//  Macro d'acces a une transaction sur GeoFactory V5, ODT a la mode N1
//------------------------------------------------------------------------------ 
#define CATCGMFactoryBeginODT(session,Inputs,OldResults)  \
CATCGMFactoryTransaction *volatile session = CATCGMFactoryTransaction::Create(Inputs,OldResults); \
CATTry  \
{

#define CATCGMFactoryBeginODTMngt(session,Inputs,OldResults,Manage)  \
CATCGMFactoryTransaction *volatile session = CATCGMFactoryTransaction::Create(Inputs,OldResults,Manage); \
CATTry  \
{



#define CATCGMFactoryEndODT(session,NewResults,NothingTODO,catgeoControls)  \
  if ( session ) \
  { \
    int  KO##session =0; \
    if (NothingTODO) \
      session->FinishKO(NULL); \
    else \
      KO##session = session->FinishOKAY(&NewResults,&catgeoControls); \
    delete session; \
    session=NULL; \
    if ( KO##session ) \
      CATCGMFactoryTransaction::ManageControlFailure(); \
  } \
} \
CATCatch(CATError, error) \
{  \
  if ( session ) { session->FinishKO(error); delete session; session=NULL; } \
  CATRethrow; \
}  \
CATEndTry 



#endif
