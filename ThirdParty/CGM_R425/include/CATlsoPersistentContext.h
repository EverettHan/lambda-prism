/* -*-C++-*- */

#ifndef CATlsoPersistentContext_H
#define CATlsoPersistentContext_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : Donnees contextuelles pour les operateurs  
               derivant de CATPersistentExtTopOperator

=============================================================================
*/
#include "CATlsoContext.h"
#include "CATTopData.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "PersistentCell.h"
#include "CATListOfCATPlanes.h"
#include "ListPOfCATPersistentBodies.h"
#include "ListPOfCATLiveBody.h"
#include "CATlsoChainMaster.h"

//BEGIN_TCX (pour simplifier la vie AddRef-Release)
#include "CATCGMFormol.h"
#include "CATCGMNewArray.h"
#include "CATWeekVersioning.h"
#include "CATCGMStream.h"
// #include "CATDeclarativeApplication.h"
#include "CATCGMHashTableWithAssoc.h"

//END_TCX

class CATlsoTransformFaceContext;
class CATlsoRemoveFaceContext;
class CATlsoVariationalTransformCellContext;
class CATlsoAlgoElt;
class CATBody;
class CATGeoFactory;
class CATPersistentCellInfra;
class CATGMLivePersistentCellInformer;
class CATPersistentExtTopOperator;
class CATPersistentBody;
class CATLiveBody;
class CATPlane;
class CATDomain;
class CATPersistentOperator;
class CATlsoStreamableAlgoElt;

//--------------------------------------------------------------------------
// @nocgmitf (do not create phase 2 interface)
class ExportedByPersistentCell CATlsoPersistentContext : public CATlsoContext
{

public:

  // Official constructor
  // constructeur a partir d'une Factory, d'un CATPersistentExtTopOperator 
  CATlsoPersistentContext(CATGeoFactory                & iFactory,
                          CATPersistentExtTopOperator  & iPersistentExtTopOperator,
                          CATSoftwareConfiguration     * iConfig=NULL,
                          CATBoolean                     iReplaceBasicContext=TRUE);

  // Constructeur 2 a partir d'une Factory, d'un CATPersistentExtTopOperator 
  // Sans replace context
  CATlsoPersistentContext(const CATPersistentExtTopOperator  & iPersistentExtTopOperator,
                          CATGeoFactory                      & iFactory,
                          CATSoftwareConfiguration           * iConfig=NULL
                          /*CATBoolean                           iReplaceBasicContext=FALSE*/);



  // @depracated - do not use.
  // constructeur a partir d'un CATBody initial, d'un CATPersistentExtTopOperator 
  CATlsoPersistentContext(CATBody                      & iBody,
                          CATPersistentExtTopOperator  * iPersistentExtTopOperator,
                          CATSoftwareConfiguration     * iConfig=NULL,
                          CATBoolean                     iReplaceBasicContext=TRUE);

  // destructeur 
  virtual ~CATlsoPersistentContext();

  //TYCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;

  virtual CATlsoPersistentContext * CastToPeristentContext();

  // Nettoyage des donnees geometriques generees non utilisees
  void CreateBodyForCleanNewerUnusedGeometry();
  void CleanNewerUnusedGeometry();
  void RemoveTheBodyForCleanNewerUnusedGeometry();
  //For Mirror - DeformNurbs operator
  void AddDomainForCleanNewerUnusedGeometry(CATDomain  & iDomain);

  //==============================================================================
  //
  // METHODES SET
  //
  //==============================================================================
  void SetPersistentBodyResultAndLastJournalResult(CATPersistentBody * iResultPBody,
                                                   CATCGMJournalList * iJournal,
                                                   CATBoolean          iRecordAJournalCopy=FALSE);
 

  // Indique si l'operation en cours doit etre interrompue et fourni un BestResult
  // iPersistentBody Meilleur résulat à enregistrer
  // iThrowIfInterrupted Indique si une erreur de type "MathInteruptedOperator_ERR_110" doit etre lancee en cas d'interruption
  // iProgressID         (Debug) Un identifiant unique localisant l'appel au SetProgress
  // iFileName           (Debug) Le nom du fichier depuis lequel l'appel a ete effectue
  // Retourne un booleen indiquant s'il faut continuer ou s'arreter
  CATBoolean IsInterruptedWithBestResult(CATPersistentBody * iPersistentBody,
                                         CATCGMJournalList * iJournal,
                                         const CATBoolean    iThrowIfInterrupted = FALSE,
                                         const CATLONG32     iProgressID = -1,
                                         const char        * iFileName = NULL );


  virtual void SetBestResultPersistentBody(CATPersistentBody * iPersistentBody,
                                           CATCGMJournalList * iJournal); // do not call directly

  INLINE void SetBestResultMode(CATBoolean iBestResultMode);
  INLINE CATBoolean GetBestResultMode() const;

  INLINE CATBoolean GetNoCopyCreateManifolds() const { return _NoCopyCreateManifold; }
  INLINE void SetNoCopyCreateManifolds(CATBoolean iVal) { _NoCopyCreateManifold = iVal; }

  void CleanBestResultPersistentBody();
  void Set_HaveToDeleteBestResultJournal(CATBoolean HaveToDeleteBestResultJournal=TRUE);
  INLINE void SetParentContext(CATlsoPersistentContext *iParentContext);

  CATPersistentBody * ComputeInputPersistentBodyWithJournal(CATBody * iBody, CATCGMJournalList * iJournal);

  // Methode permettant de setter des ChainMaster au PersistentContext. 
  // Evite d'avoir à creer une classe dérivée de lsoPersistentContext pour chaque nouvel operateur.
  // Return E_FAIL if iChainMaster is NULL
  //               or if _AdminTab is already set
  //               or if _PersistentExtTopOperator is NULL
  HRESULT AttachChainMaster (CATlsoChainMaster *iChainMaster[], const int iSizeOf=1);

  /**
   * @brief	Attach a chain master to _AdminTab
   * 				
   * @param [in]	ipChainMasterToAttach		Chain master to be attached to _AdminTab.
   * @param 			iAdminIndex					 		Index position of new chain master (starting at 0).
   * 
   * @returns			E_FAIL if ipChainMasterToAttach is NULL 
   * 								     or if iAdminIndex < _NbAdmin
   */
  HRESULT AttachOneChainMaster (CATlsoChainMaster * ipChainMasterToAttach, const int iAdminIndex);

  //==============================================================================
  //
  // METHODES GET
  //
  //==============================================================================

  CATPersistentCellInfra          & GetPersistentCellInfra() const;
  CATGMLivePersistentCellInformer & GetPersistentCellInformer() const;
  CATBody                         & GetInputBody() const;
  CATPersistentBody               * GetInputPersistentBody() const;
  void                              GetInputPersistentBodies( ListPOfCATPersistentBodies & oInputPersistentBodies) const;
  CATBoolean                        IsInfraShared() const;
  CATLiveBody                     * GetLiveBodyCGM(CATBody * iBody) const;

  CATPersistentExtTopOperator     * GetPersistentExtTopOperator() const;

  INLINE CATlsoPersistentContext * GetParentContext() const;

  CATBoolean GetLiveBodyAllowed() const;
  // CATLISTP(CATPlane) * GetListOfPlaneOfSymmetry() const;
  // CATPlane * GetPlaneOfSymmetry() const;
  INLINE CATPersistentBody* GetBestResultPersistentBody() const;
  CATBody * GetBodyAndJournalFromBestResultPersistentBody(CATCGMJournalList *oJournal) ;
  CATPersistentBody * GetPersistentBodyAndJournalFromBestResultPersistentBody(CATCGMJournalList *oJournal);
  void RunCreateManifolds(CATPersistentBody           * iResultPersistentBody,
                          CATCGMJournalList           * ioLiveJournal,
                          CATLISTP(CATPersistentBody) * iLocalInputPersistentBodies = NULL,
                          ListPOfCATLiveBody          * ipLivificationInputLiveBodyList = NULL,
                          CATMathTransformation       * iGlobalTransfo=NULL,
                          CATBoolean                    iIsLastRun = FALSE,
                          CATBoolean                    iSmartContext = FALSE,
                          CATCGMHashTableWithAssoc    * iSmartFaceListOnInputBodies = NULL,
                          CATBoolean                    iAssembleContext = FALSE);

  // Special remove to clean memory in multi-run
  void MyRemoveBodyWithCheck(CATPersistentBody* &ioPersistentBody);
  void MyRemoveBodyWithCheck(ListPOfCATPersistentBodies & iPersistentBodyList);
  INLINE void AppendPersistentBodyToKeepForAllRun(CATPersistentBody * iPersistentBodyToKeepForAllRun); 

  // acces au CATTopData (qui contient le journal)
  // renvoie 1 si pas de probleme, 0 sinon
  virtual short GetTopData(CATTopData &oTopData) const;

  int GetNumberOfRun() const ;

  void ComputeSoftwareConfiguration();

  CATCGMJournalList * GetJournalForBestResult();

  INLINE CATBoolean GetIsSHMInput() const;
  INLINE void SetIsSHMInput(CATBoolean iIsSHMInput);


  static void WriteMultiInputData(CATlsoPersistentContext &iPersistentContext, CATCGMStream &ioStr);
  static void ReadMultiInputData(CATlsoPersistentContext &iPersistentContext, CATPersistentOperator &iOpe, CATCGMStream &iStr);

  //==============================================================================
  //
  // METHODES for VISUAL DEBUG or TRACE DEBUG
  //
  //==============================================================================
  //==============================================================================
  //
  // METHODES for VISUAL DEBUG or TRACE DEBUG
  //
  //==============================================================================
  // Do NOT use directly this method - use preferably the methods 
  // PutNameAndColorOnInputPBody and PutNameAndColorOnInternalPBody
  void PutNameAndColorOnPersistentBody(CATPersistentBody * iPBody,
                                       char              * iNameBody,
                                       short               iColor_R = -1,
                                       short               iColor_G = -1,
                                       short               iColor_B = -1,
                                       CATBoolean          iPreserveOldName = TRUE,
                                       CATLONG32           iNumber = -1,
                                       CATLONG32           iSubNumber = -1);

  // These methods are declared non virtual since there is no reason for you to
  // redefine them

  // Use this method to name and color INPUT bodies
  // (INPUT = given to you)
  void PutNameAndColorOnInputPBody(CATPersistentBody* iPBody,
                                   char*              iNameBody,
                                   short              iColor_R = -1,
                                   short              iColor_G = -1,
                                   short              iColor_B = -1,
                                   CATLONG32          iNumber  = -1);

  // Use this method to name and color INTERNAL bodies
  // (INTERNAL = created by you : this includes OUTPUT bodies) 
  void PutNameAndColorOnInternalPBody(CATPersistentBody* iPBody,
                                      char*              iNameBody,
                                      short              iColor_R   = -1,
                                      short              iColor_G   = -1,
                                      short              iColor_B   = -1,
                                      CATLONG32          iNumber    = -1,
                                      CATLONG32          iSubNumber = -1);

  CATULONG32 GetBodyTagFromPersistentBody(CATPersistentBody * iPBody);

protected:

  // copy constructeur et operateur sans implementation
  // -> ne compile pas en cas d'appel
  CATlsoPersistentContext(CATlsoPersistentContext& iOrig);
  CATlsoPersistentContext& operator= (const CATlsoPersistentContext& iRight);

  void InitPersistentContext(CATSoftwareConfiguration * iConfig/*, CATBoolean iReplaceBasicContext*/);

  void SetJournalForBestResult(CATCGMJournalList * iJournal,CATBoolean iRecordACopy=TRUE);
  void SetBestResultPersistentBodyForLive(CATPersistentBody * iPersistentBody,
                                          CATCGMJournalList * iJournal);


  // Stream / Unstrema input-data
  virtual void WriteMultiInputData(CATCGMStream  &ioStr) const;
  virtual void ReadMultiInputData (CATPersistentOperator &iOpe, CATCGMStream &iStr) const;
  virtual CATlsoStreamableAlgoElt * GetInputDataObject(int iAdminIndex);

  // -------------------------------
  // Internal Data for context
  // -------------------------------

  // body pour le nettoyage des objets non utilisés par le resultat
  CATBody                       * _BodyForNewerUnused;

  ListPOfCATPersistentBodies      _PersistentBodiesListToKeepForAllRun;

  CATBoolean                      _IsSHMInput;
 
  // pointeur vers le TopOperator,
  // pour pouvoir acceder entre autres a son TopData de partout dans notre code
  CATPersistentExtTopOperator  *  _PersistentExtTopOperator;

  CATPersistentBody            * _BestResultPersistentBody;
  CATCGMJournalList            * _JournalForBestResult;
  CATBoolean                     _HaveToDeleteJournalForBestResult;
  CATlsoPersistentContext      * _ParentContext; // Donne les infos sur l'appellant
  CATBoolean                     _BestResultMode;

  CATBoolean                     _NoCopyCreateManifold;
};


// Implementations INLINE
// ------------------------------------------------------------------------

INLINE CATPersistentBody* CATlsoPersistentContext::GetBestResultPersistentBody() const {
  return _BestResultPersistentBody; }
// ------------------------------------------------------------------------
//Parentcontext
// ------------------------------------------------------------------------
INLINE CATlsoPersistentContext * CATlsoPersistentContext::GetParentContext() const {
  return _ParentContext; }

INLINE void CATlsoPersistentContext::SetParentContext(CATlsoPersistentContext *iParentContext) {
  _ParentContext=iParentContext; }

// ------------------------------------------------------------------------
// AppendPersistentBodyToKeepForAllRun
// ------------------------------------------------------------------------
INLINE void CATlsoPersistentContext::AppendPersistentBodyToKeepForAllRun(CATPersistentBody * iPersistentBodyToKeepForAllRun) {
  _PersistentBodiesListToKeepForAllRun.Append(iPersistentBodyToKeepForAllRun); }

// ------------------------------------------------------------------------
// Get and SetIsSHMInput
// ------------------------------------------------------------------------
INLINE CATBoolean CATlsoPersistentContext::GetIsSHMInput() const {
  return _IsSHMInput; }

INLINE void CATlsoPersistentContext::SetIsSHMInput(CATBoolean iIsSHMInput) {
  _IsSHMInput = iIsSHMInput; }

INLINE void CATlsoPersistentContext::SetBestResultMode(CATBoolean iBestResultMode) {
  _BestResultMode=iBestResultMode; }

INLINE CATBoolean CATlsoPersistentContext::GetBestResultMode() const {
  return _BestResultMode; }


#endif
