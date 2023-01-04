/* -*-C++-*- */

#ifndef CATlsoContext_H
#define CATlsoContext_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : Donnees contextuelles pour l'operateur HybridVariableOffset ou HVOConstraintsComputer
               et soft d'acces et d'edition de ces donnees

=============================================================================
*/

#include "CATlsoChainMaster.h"
#include "CATTopData.h"
#include "CATCGMVirtual.h"
#include "CATGeometry.h"
#include "CATMathInline.h"
#include "PersistentCell.h"
#include "CATlsoUtilTrace.h"
#include "CATlsoUtilTraceDef.h"
#include "ListPOfCATBody.h"
#include "CATDeclarativeApplication.h"
#include "ListPOfCATPersistentBodies.h"

//BEGIN_TCX (pour simplifier la vie AddRef-Release)
#include "CATCGMFormol.h"
#include "CATCGMNewArray.h"
//END_TCX

// Pour la gestion du temps (analyse perfo)
#include "CATLib.h"



class CATlsoPersistentContext;
class CATlsoLiveContext;
class CATlsoTransformFaceContext;
class CATlsoRemoveFaceContext;
class CATlsoVariationalTransformCellContext;
class CATlsoSingleModifyFaceContext;
class CATlsoModifyFaceContext;
class CATlsoRemoveDraftContext;
class CATlsoAlgoElt;
class CATBody;
class CATGeoFactory;
class CATlsoRedoDraftContext;
class CATlsoProgressBarManager;
class CATDRepExtTopOperator;
class CATCGMProgressBar;
class CATPGMDRepBehavior;
class CATlsoSweepableElementContext;
class CATUnicodeString;

#define CtxOperator                     CATlsoContext::CTXOPER
#define CtxBasic                        CATlsoContext::BASIC
#define CtxTransformFace                CATlsoContext::OP_TRANSFORMFACE
#define CtxRemoveFace                   CATlsoContext::OP_REMOVEFACE
#define CtxVariationalTransformCell     CATlsoContext::OP_VARIATIONALTRANSFORMCELL
#define CtxDRepDependencyUpdater        CATlsoContext::OP_DREPDEPENDENCYUPDATER
#define CtxModifyFace                   CATlsoContext::OP_MODIFYFACE
#define CtxSingleModifyFace             CATlsoContext::OP_SINGLEMODIFYFACE


#define CtxClassicMode                  0
#define CtxDebugWithoutErrorBody        1
#define CtxDebugWithErrorBody           2
// Mode d'appel de HybridVariableOffset pour ConstraintsComputer en CGMReplay
// afin de voir les body d'erreur
#define CtxClassicModeWithErrorBody    -1

//--------------------------------------------------------------------------
// @nocgmitf (do not create phase 2 interface)
class ExportedByPersistentCell CATlsoContext : public CATCGMVirtual
{

public:

  // constructeur a partir d'un CATBody initial, d'un CATTopOperator )
  CATlsoContext(CATBody  & iBody);
  // constructeur a partir du CATTopOperator
  CATlsoContext(CATGeoFactory &iFactory);
  // official constructor
  CATlsoContext(CATGeoFactory                & iFactory,
                const CATDRepExtTopOperator  & iDRepExtTopOperator,
                CATSoftwareConfiguration     * iConfig,
                CATBoolean                     iReplaceBasicContext=TRUE);


  // destructeur 
  virtual ~CATlsoContext();


  enum CTXOPER { BASIC=0,
                 OP_TRANSFORMFACE,
                 OP_REMOVEFACE, 
                 OP_VARIATIONALTRANSFORMCELL,
                 OP_DREPDEPENDENCYUPDATER,
                 OP_MODIFYFACE,
                 OP_SINGLEMODIFYFACE,
               };

  enum CTXTIMECONSUMINGLEVEL { TIMECONSUMING_OVERALL=1, TIMECONSUMING_MEDIUM , TIMECONSUMING_FINE};

  //TCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;

  // Methodes de cast
  // ---------------------------
  virtual CATlsoPersistentContext *                CastToPeristentContext();
  virtual CATlsoLiveContext *                      CastToLiveContext();
  virtual CATlsoTransformFaceContext *             CastToTransformFaceContext();
  virtual CATlsoRemoveFaceContext *                CastToRemoveFaceContext();
  virtual CATlsoVariationalTransformCellContext *  CastToVariationalTransformCellContext();
  virtual CATlsoSingleModifyFaceContext *          CastToSingleModifyFaceContext();
  virtual CATlsoModifyFaceContext *                CastToModifyFaceContext();
  virtual CATlsoRemoveDraftContext *               CastToRemoveDraftContext();
  virtual CATlsoRedoDraftContext *                 CastToRedoDraftContext();
  virtual CATlsoSweepableElementContext*           CastTolsoSweepableElementContext();
  //==============================================================================
  //
  // METHODES SET
  //
  //==============================================================================

  //==============================================================================
  // Donne le type de l'operateur contextuel
  // (enum defini par le #define CtxOperator, prend les valeurs 
  // {CtxHybridVariableOffset, CtxConstraintsComputer }
  //==============================================================================
  INLINE void  SetExtOperator(const CATDRepExtTopOperator * iDRepExtOpe);
  INLINE const CATDRepExtTopOperator * GetExtOperator () const;

  INLINE CtxOperator GetCtxOperator() const;
  INLINE void SetCtxOperator(CtxOperator iCtxOperator);

  //==============================================================================
  //
  // METHODES RUN
  //
  //==============================================================================

  // Cree les fichiers AllReps
  void CreateAllReps(const char * iNameOp);

  // Keep All Objects Mode for the AllReps creation
  void KeepAllObjectsMode(); 


  // ========================================================================
  // ProgressBars
  // ========================================================================
  // Do not call this methode during the constructeur of exttopoperator: it will throw an error.
  // Call it before run
  void CreateProgressBarManager(); 

  // Ajout de la progress bar mere du ProgressBarManager
  void SetProgressBar( CATCGMProgressBar * iProgressBar );

  // Mise a jour de l'etat d'avancement de la tache.
  // iValue              La valeur atteinte
  // iTotalValue         La valeur atteinte lorque la tache sera terminee a 100%
  // iThrowIfInterrupted Indique si une erreur de type "MathInteruptedOperator_ERR_110" doit etre lancee en cas d'interruption
  // iProgressID         (Debug) Un identifiant unique localisant l'appel au SetProgress
  // iFileName           (Debug) Le nom du fichier depuis lequel l'appel a ete effectue
  // Retourne un booleen indiquant s'il faut continuer (TRUE) ou s'arreter (FALSE)
  // A noter : SetProgress(0., 0., iThrowIfInterrupted) force l'appel au callback d'interruption pour verifier si l'arret est demande
  CATBoolean SetProgress ( const double      iValue,
                           const double      iTotalValue = 100.0,
                           const CATBoolean  iThrowIfInterrupted = FALSE,
                           const CATLONG32   iProgressID = -1,
                           const char      * iFileName = NULL );

  // Creation d'une tache fille
  // iStartPercentage Valeur entre 0 et 100 correspondant au pourcentage d'accomplissement 0
  // iEndPercentage   Valeur entre 0 et 100 correspondant au pourcentage d'accomplissement 100
  // Retourne la progress bar fille creee
  CATCGMProgressBar * CreateAChildProgressBar( const double iStartPercentage = 0.0, const double iEndPercentage = 100.0, CATTopOperator * iTopOpe=NULL);


  //==============================================================================
  //
  // METHODES GET
  //
  //==============================================================================
  // Retourne la valeur de progression de la progress bar mere du ProgressBarManager
  double GetProgress() const;
  // Indique si une demande d'interruption a ete detectee
  // Attention : n'interroge pas la progressBar
  CATBoolean GetInterruptionRequested( const CATBoolean iThrowIfInterrupted = FALSE ) const;  
  void SetInterruptionRequested(CATBoolean iInterruptionRequested);

  // Indique si l'operation en cours doit etre interrompue
  // iThrowIfInterrupted Indique si une erreur de type "MathInteruptedOperator_ERR_110" doit etre lancee en cas d'interruption
  // iProgressID         (Debug) Un identifiant unique localisant l'appel au SetProgress
  // iFileName           (Debug) Le nom du fichier depuis lequel l'appel a ete effectue
  // Retourne TRUE si une interruption a ete demandee, FALSE sinon
  CATBoolean IsInterrupted ( const CATBoolean  iThrowIfInterrupted = FALSE,
                             const CATLONG32   iProgressID = -1,
                             const char      * iFileName = NULL );


  //==============================================================================
  // acces a la factory
  // iImpliciteFactory est par defaut a 1
  //==============================================================================
  CATGeoFactory * GetFactory(short iImpliciteFactory=1) const;

  // -----------------------------------------------------------------------------
  // CATPGMDRepBehavior
  // -----------------------------------------------------------------------------
  const CATPGMDRepBehavior * GetDRepBehavior() const;
  CATDeclarativeApplication  GetDeclarativeApplication() const;
  
  // acces a la resolution et visual-debug
  INLINE double GetEpsgForLengthTest() const;
  INLINE double GetEpsgForRelativeTest() const;
  INLINE double GetResolution() const;
  INLINE double GetTopSharpAngle() const;
  INLINE double GetTopWeaklySharpAngle() const;
  INLINE double GetInfinite() const;
  INLINE double GetLayDownTolerance() const;

  // acces au CATTopData (qui contient le journal)
  // renvoie 1 si pas de probleme, 0 sinon
  virtual short GetTopData(CATTopData &oTopData) const;

  // acces sequentiel aux administrateurs de chaines
  CATlsoChainMaster * GetAdmin(CATLONG32 iAdminIndex) const;
  CATLONG32 GetNbAdmin() const;

  // acces a la donnee _LastUTag (_UTag du dernier objet CATlsoAlgoElt cree).
  INLINE void SetLastUTag(CATLONG32 iLastUTag);
  INLINE CATLONG32 GetLastUTag() const;

  // acces a un AlgoElt (INLINE pour etre accessible au debugger)
  // Si on fournit un algoelt de reference, on cherchera dans sa chaine
  INLINE CATlsoAlgoElt * GetAlgoElt(CATlsoChainMaster * iAdmin, CATLONG32 iNum) const;
  INLINE CATlsoAlgoElt * GetSameChainElt(CATlsoAlgoElt * iRefElt, CATLONG32 iNum) const;
  CATlsoAlgoElt * ImplementGetSameChainElt(CATlsoAlgoElt * iRefElt, CATLONG32 iNum) const;

  // Verifications de base
  void CheckValid(short iCostLevel) const;

  // Utilitaires modele (encapsulent les Addref et Release + verifications)
  INLINE void AddRef( CATGeometry * iObject );
  short IsAlive( CATGeometry * iObject ) const;
  void Release( CATGeometry * iObject );
  void Remove( CATGeometry * iObject, short iRecursiveMode=1);

  // Lecture du numero de session du TopOperator associe
  INLINE CATLONG32 GetTopOperatorSessionNumber() const;

  INLINE void SetSoftwareConfiguration(CATSoftwareConfiguration * iConfig);
  INLINE CATSoftwareConfiguration * GetSoftwareConfiguration() const;
  virtual void ComputeSoftwareConfiguration();

  INLINE short GetCGMMode() const;
  INLINE void SetCGMMode(short iCGMMode);

  // Bodies LifeCicle managment
  // -----------------------------
  INLINE void AppendTemporaryBody(CATBody *iTempBody);
  INLINE void AppendProtectedBody(CATBody *iInputOutputBody);

  INLINE CATCGMOutput* GetDbgOutput(CATLONG32 iTraceLevel) const;

  // Pour les Allresp
  // ---------------------------------------------------
  // Gestion des adresses de sortie des fichiers allreps
  void CreateAllRepsOutPut(const char * iNameOp);

  INLINE CATUnicodeString * GetAllRepsOpName() const;
  INLINE CATCGMOutput     * GetAllRepsOutPut() const;
  INLINE CATCGMOutput     * GetAllRepsChronoOutPut() const;

  //
  INLINE CATlsoChainMaster * GetAnomalyAdmin() const {return NULL; };

  CATBoolean IsActive(short iVariable) const;

  // dump
  friend CATCGMOutput& operator<< (CATCGMOutput& s, const CATlsoContext& iOpe);
  void ImplementDumpAll(CATCGMOutput * iOutStream=NULL) const;
  INLINE int DumpAll() const;

  virtual void Dump( CATCGMOutput& os ) const;

protected:

  void DeleteAlgoElements();
  // copy constructeur et operateur sans implementation
  // -> ne compile pas en cas d'appel
  CATlsoContext(CATlsoContext& iOrig);
  CATlsoContext& operator= (const CATlsoContext& iRight);

  // -------------------------------
  // Internal Data for context
  // -------------------------------
  // Sentinelle
  char            _ContextSentinel[8];

  // Type de l'operateur contextuel (HybridVaraibleOffset, HVOConstraintsComputer, ...)
  CtxOperator     _CtxOp;

  // caracteristiques (eventuellement decalees pour le debug) de la factory 
  CATGeoFactory * _GFactory;

  double          _EpsgForLengthTest;
  double          _EpsgForRelativeTest;
  double          _Resolution;
  double          _SharpAngle;
  double          _WeaklySharpAngle;
  double          _Infinite;

  // ProgressBarManager  
  CATlsoProgressBarManager    * _ProgressBarManager; 
  // pointeur vers le TopOperator 
  const CATDRepExtTopOperator * _DRepExtOperator;

  // Nombre d'objets derives de CATlsoAlgoElt crees lors d'une operation
  // Il suffit de stocker le dernier _UTag du dernier objet cree.
  // Ce nombre est remis a jour des l construction d'un nouveau element
  CATLONG32 _LastUTag;

  // TCX: pour se simplifier la vie sur les AddRef-Release
  CATCGMFormol      _formol;

  // Variable pour le versionning des autres operateurs appelés
  CATSoftwareConfiguration * _Config;

  // Chaines d'objets algorithmiques specifiques
  CATlsoChainMaster ** _AdminTab;

  int _NbAdmin; 

  // cgmmode: 0 classicalmode
  //          1 debug withouterror body
  //          2 debug with error body
  short _CGMMode;

  // Nom de l'operateur pour les traces avec GetDbgOutput
  CATlsoUtilTrace_OperatorName _OpeNameForDbgOutput;

  // --------------------------------------------------------------------------
  // Pilotage des AllReps
  // --------------------------------------------------------------------------

  CATUnicodeString * _AllRepsOpName;
  CATCGMOutput     * _AllRepsOutPut;
  CATCGMOutput     * _AllRepsChronoOutPut;

  // Body LifeCicle managment for non-persistent operations
  // Gestion du cicle de vie des bodies dans les operations sans persistent infra
  ListPOfCATBody  _ProtectedBodyList;   // <-- Liste protégée de body à garder absolument
  ListPOfCATBody  _TemporaryBodyList;   // <-- Liste des body intermédiaires qui seront supprimés

  private:

    void Initialise(CATBody & iBody);
    void Initialise(CATGeoFactory &iFactory);
    void RemoveTemporaryBodies();
};

// Implementations INLINE
INLINE void CATlsoContext::SetExtOperator(const CATDRepExtTopOperator * iDRepExtOpe) {
  if ( ! _DRepExtOperator )
    _DRepExtOperator = iDRepExtOpe; 
}

INLINE const CATDRepExtTopOperator * CATlsoContext::GetExtOperator () const {
  return _DRepExtOperator; }

INLINE CtxOperator CATlsoContext::GetCtxOperator() const { 
  return _CtxOp; }

INLINE void CATlsoContext::SetCtxOperator(CtxOperator iCtxOperator) {
  _CtxOp = iCtxOperator; }

INLINE double CATlsoContext::GetEpsgForLengthTest() const {
  return _EpsgForLengthTest; }

INLINE double CATlsoContext::GetEpsgForRelativeTest() const {
  return _EpsgForRelativeTest; }
    
INLINE double CATlsoContext::GetResolution() const {
  return _Resolution; }

INLINE double CATlsoContext::GetTopSharpAngle() const {
  return _SharpAngle; }

INLINE double CATlsoContext::GetTopWeaklySharpAngle() const {
  return _WeaklySharpAngle; }

INLINE double CATlsoContext::GetInfinite() const {
  return _Infinite; }

INLINE CATlsoAlgoElt * CATlsoContext::GetAlgoElt(CATlsoChainMaster * iAdmin, CATLONG32 iNum) const {
  return ((iAdmin) ? (iAdmin -> GetAlgoElt(iNum)) : (0)); }

INLINE CATlsoAlgoElt * CATlsoContext::GetSameChainElt(CATlsoAlgoElt * iRefElt, CATLONG32 iNum) const {
	return ImplementGetSameChainElt(iRefElt, iNum); }

INLINE int CATlsoContext::DumpAll() const {
  // cette fonction est INLINE uniquement pour etre accessible au debugger
  ImplementDumpAll();
  return 1;
}

INLINE void CATlsoContext::AddRef( CATGeometry * iGeometry ) { 
  // TCX: changement d'implementation dur AddRef
  _formol.lock(iGeometry); 
}

INLINE void CATlsoContext::SetLastUTag(CATLONG32 iLastUTag) {
  _LastUTag = iLastUTag; }

INLINE CATLONG32 CATlsoContext::GetLastUTag() const {
  return _LastUTag; }

INLINE void CATlsoContext::SetSoftwareConfiguration(CATSoftwareConfiguration * iConfig) {
  _Config = iConfig; }

INLINE CATSoftwareConfiguration * CATlsoContext::GetSoftwareConfiguration() const {
  return _Config; }

INLINE short CATlsoContext::GetCGMMode() const {
 return _CGMMode; }

INLINE void CATlsoContext::SetCGMMode(short iCGMMode) {
  _CGMMode = iCGMMode; }

INLINE void CATlsoContext::AppendTemporaryBody(CATBody *iTempBody) {
  if(iTempBody) _TemporaryBodyList.Append(iTempBody); }

INLINE void CATlsoContext::AppendProtectedBody(CATBody *iResultBody) {
  if(iResultBody) _ProtectedBodyList.Append(iResultBody); }

INLINE CATCGMOutput* CATlsoContext::GetDbgOutput(CATLONG32 iTraceLevel) const {
  return GetLSOTraceOuput(iTraceLevel, _OpeNameForDbgOutput); }

INLINE CATUnicodeString * CATlsoContext::GetAllRepsOpName() const {
  return _AllRepsOpName; }

INLINE CATCGMOutput * CATlsoContext::GetAllRepsOutPut() const {
  return _AllRepsOutPut; }

INLINE CATCGMOutput * CATlsoContext::GetAllRepsChronoOutPut() const {
  return _AllRepsChronoOutPut; }

// ------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------

#endif
