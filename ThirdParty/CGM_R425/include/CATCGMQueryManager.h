#ifndef CATCGMQueryManager_H
#define CATCGMQueryManager_H
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// Operateur : CATCGMQueryManager
//
// Auteurs: TCX        Date: 06/06/2002
//
// Description:   Offre generique d'un service de requete dans le modeleur topologique/geometrique
//                Il s'agit de capitaliser les informations de propagations. 
//     Les renseignements obtenus par cet operateur dependent du type de l'operateur :
//
//     "UsefulDependancies") 
//              L'analyse des supports geometriques vraiment utiles a la Topologie
//              pour requilibrer la tendance a l'obesite des macro-points et edgecurves.
//              --> utilitaire interne pour le CATBodyDatumiser
//
//     "UsefulLimits") 
//              L'analyse des parametrages utiles des Courbes et Surfaces
//              en partant des restrictions topologiques 
//              mais en tenant compte de la propagations interne des geometries 
//                 (Exemple FilletSurface --> PCurve d'appui des deux surface de contact) 
//               --> utilitaire pour identification des donnees "sur"-extrapolees
//                   en vue d'une reduction pour un "trim"
//
//   sdp 03jun03:
//     "NegativeOffsets")
//              L'analyse des objets porteurs de KnotVectors a _Offset negatif,
//              en vue de les trafiquer (les remettre >=0) prealablement a un CATBack
//              vers une version de stream <R11.
//
//=============================================================================
// Jul. 03 Parametre iGeomTargetType pour GetFatGeometries(...)           HCN
// Oct. 03 OverrideFatStatus(...), ComputeOverrideFatStatusesBefore(),
//         GetArrayBoundingEdgeHashTable()                                HCN
// Nov. 03 GetListDbgPoseSurVertexHashTable(),
//         ComputeOverrideFatStatusesAfter(...)                           HCN
// Apr. 04 Ajout de SetMultiCopyPasteMode pour indiquer au querymanager
//         s'il doit activer le bodycleaner en fin de multicopy paste (voir
//         CATCXBodyCleaner.h)                                            FDN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATCGMOperator.h" 

#include "CATCGMNewArray.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATString.h"
#include "CATBoolean.h"
#include "CATListOfCATCGMLimOfParm.h"
#include "CATListOfCATCGMGeometryOfFatAble.h"
#include "CATListOfCATCGMObjects.h"

#include "CATCGMLimitsManagement.h"
#include "CATGeometryType.h"
#include "CATCGMGeometryOfFatAble.h"
#include "CATMathInline.h"

class CATICGMUnknown;
class CATICGMObject;
class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATSoftwareConfiguration;
class CATCrvLimits;
class CATSurLimits;
class CATMathPoint;
class CATCrvParam;
class CATCGMExtrapolated;
class CATArrayBoundingEdgeHashTable;
class CATListDbgPoseSurHashTable;
class CATCGMHashTable;

class CATTopology;
class CATGeometry;


class  ExportedByGeometricObjects CATCGMQueryManager : public CATCGMOperator
{
public:
  virtual ~CATCGMQueryManager();

  //=======================
  // Typage de la requete
  //=======================
  enum TypeOfQuery { UsefulDependancies, UsefulLimits, UnExtrapolate, NegativeOffsets };

  INLINE CATCGMQueryManager::TypeOfQuery GetQueryType() const;


 



  //======================================================================================================================
  //  "UsefulLimits"     : Obtention des resultats d'analyses apres Run()
  //     Faites attention ce resultat ne doit plus etre adresse/exploite apres la suppression de l'operateur
  //======================================================================================================================
  virtual void GetLimitsAnalysis(CATLISTP(CATCGMLimOfParm) & ioResult,
                                 const CATBoolean iAppendFat               = TRUE,
                                 const CATBoolean iAppendOkay              = FALSE,
                                 const CATBoolean iAppendUnavailable       = FALSE,
                                 const CATBoolean iOnlyHoldingKnotVector   = FALSE ) = 0;

  
  //======================================================================================================================
  //  "UsefulLimits"     : Declenchement des operations de desextrapolations
  //======================================================================================================================
  virtual void RunUnExtrapolate() = 0;

  virtual int GetKnotsWeight( int & ioOkayWithoutMaxLimits, 
                              int & ioOkayDirectMaxLimits,
                              int & ioFat,
                              int & ioUnavailable,
                              int & ioUselessAnalysed    ) = 0;


  virtual void GetNbGeometries_With_Knots_NegativeOffset( int & ioBefore, 
                                                          int & ioAfterIfWasAllowed) = 0;



  virtual CATBoolean HasDetectedUselessExtrapolation( int & ioNbArcPatch, int & ioNbFatObjets ) = 0;

  virtual void GetKnotsWeight_Unextrapolated( int & ioUselessCleaned ) = 0;


  //======================================================================================================================
  //  "UsefulDependancies"   : Obtention du resultat apres Run()
  //     Faites attention ce resultat ne doit plus etre adresse/exploite apres la suppression de l'operateur
  //
  //  Les geometries grasses mais sur lesquelles OverrideFatStatus(...) a ete appele ne sont PAS renvoyes dans ioFatCells
  //  (on ne veut PAS nettoyer ces geometries), mais peuvent etre recuperee dans iopNotFatWithSymptomsCells
  //
  //======================================================================================================================

  virtual void GetFatGeometries(CATLISTP(CATCGMGeometryOfFatAble)& ioFatCells, 
                                CATGeometricType                   iGeomTargetType = CATGeometryType,
                                CATLISTP(CATCGMGeometryOfFatAble)* iopNotFatWithSymptomsCells = NULL) = 0;

  // Specifique multicopypaste
  virtual void SetMultiCopyPasteMode();

  //=======================================================================================
  //  "UsefulLimits"  dedie aux implementations des objets suivants
  //
  //  void CATPoint::PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery );
  //  void CATCurve::PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery );
  //  void CATSurface::PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery );
  //  void CATTopology::PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery );
  //
  // Afin d'eviter les redondances de traitements
  //   ATTENTION POUR DES NECESSITE DE RECADRAGE   : iLimits est potentiellement recadre (entree/sortie)
  //
  //=======================================================================================
  virtual short NeedNewSearch(CATICGMUnknown *iFrom, CATCrvLimits &iLimits, CATCurve   *iTo) = 0;
  virtual short NeedNewSearch(CATICGMUnknown *iFrom, CATSurLimits &iLimits, CATSurface *iTo) = 0;

  //=======================================================================================
  //  "UsefulLimits"  and "UsefulDependancies" 
  //=======================================================================================
  virtual short NeedNewSearch(CATICGMUnknown *iFrom, CATICGMObject *iTo) = 0;
  
  //=====================================================================================================
  //   "UsefulDependancies"  et  "UsefulLimits"  : possibilite de propagation initiale
  //   "UsefulLimits"  Invalidation de l'analyse suite a une incapacite a analyser/traiter l'objet
  //=====================================================================================================
  enum TypeOfPropagate { DummyPropagate, DisableUsefulLimits };
  virtual void PropagateAnalysis(CATCGMQueryManager::TypeOfPropagate iPropagate, CATICGMObject *iObject) = 0;


  //=======================================================================================
  //   "UsefulLimits"  TEMPORARY  Force la propagation aux MaxLimits
  //=======================================================================================
  virtual void ForceMaxLimitsPropagation(CATICGMUnknown *iFrom, CATICGMObject *iTo) = 0;

  //=======================================================================================
  //   "UsefulLimits"  : TOOLS FOR DEBUGGING
  //=======================================================================================
  virtual void       ForceExtendToArcLimits(CATBoolean iExtend = TRUE) = 0; 
  INLINE  CATBoolean IsForcedToExtendToArcLimits() const;

  virtual void       ForceExtendSurfaceOfLoop(CATBoolean iExtend = TRUE) = 0; 
  INLINE  CATBoolean IsForcedToExtendSurfaceOfLoop() const;

  virtual void       ForceSecureCertifiedUnextrapolable(CATBoolean iCertified = TRUE) = 0; 
  INLINE  CATBoolean IsForceSecureCertifiedUnextrapolable() const; 


  virtual void       ForceCorruptingForgetOriginalLimits(CATBoolean iCorrupting = FALSE) = 0; 
  INLINE  CATBoolean IsForceCorruptingForgetOriginalLimits() const; 

  virtual void       ForceCorruptingUnextrapol(CATBoolean iCorrupting = FALSE) = 0; 
  INLINE  CATBoolean IsForcedCorruptingUnextrapol() const; 

  virtual void       ForceCorruptingNoMaxLimitsPropagation(CATBoolean iCorrupting = FALSE) = 0; 
  INLINE  CATBoolean IsForceCorruptingNoMaxLimitsPropagation() const; 

  virtual void       ForceCorruptingNoUnavailablePropagation(CATBoolean iCorrupting = FALSE) = 0; 
  INLINE  CATBoolean IsForceCorruptingNoUnavailablePropagation() const; 

  virtual void       ForceCorruptingWithDegeneratedLimits(CATBoolean iCorrupting = FALSE) = 0; 
  INLINE  CATBoolean IsForceCorruptingWithDegeneratedLimits() const; 
  
  virtual void       AllowNewFormat_NegativeOffset_KnotVector(CATBoolean iCorrupting = FALSE) = 0; 
  INLINE  CATBoolean IsAllowedNewFormat_NegativeOffset_KnotVector() const; 

  virtual void       ForcedToExtendLoopLimits(CATBoolean iCorrupting = TRUE) = 0; 
  INLINE  CATBoolean IsForcedToExtendLoopLimits() const; 

  virtual void       ForcedDisableCGMObjectType(CATCGMLimits_DisableCGMObjectType iCorrupting = CATCGMLimits_DisableCGMObjectType_None) = 0;
  INLINE  CATBoolean IsForcedDisableCGMObjectType(CATCGMLimits_DisableCGMObjectType iDisableCGMObjectType) const; 

  //=======================================================================================
  //   Acces a des services non encore publie sur les interface officielle CAA
  //=======================================================================================
  virtual CATCGMLimitsManagement GetLimitsManagement(CATICGMObject   *iObject) = 0; 
  virtual CATCGMLimitsManagement QueryLimitsManagement(CATCurve   *iCurve,   CATCrvLimits *iOriginalLimits=NULL) = 0; 
  virtual CATCGMLimitsManagement QueryLimitsManagement(CATSurface *iSurface, CATSurLimits *iOriginalLimits=NULL) = 0; 
  
   
  //=======================================================================================
  //   "UsefulLimits"  : INTERNE 
  //   La valeur de retour est significatif d'une valeur valide
  //=======================================================================================
  virtual CATBoolean GetUsefulLimits(CATCurve   *iCurve,   CATCrvLimits & ioUsefulLimit ) = 0; 
  virtual CATBoolean GetUsefulLimits(CATSurface *iSurface, CATSurLimits & iOUsefulLimit ) = 0; 


  //=======================================================================================
  //   "UsefulLimits"  : TOOLS FOR MANAGEMENT
  //=======================================================================================
  virtual void  PropagateMinimaBeforeRun(CATCGMExtrapolated &log) = 0; 

  //=======================================================================================
  //  "UsefulDependancies"  
  //     ContainsNonDatumModelisation : implicitly the NonDatumModelisation will disappear by use of CloneManager
  //=======================================================================================
  virtual void AddUsefulDependancies(short iToDim, CATTopology *iHolder,  CATGeometry *iUsefullDependancy,  CATBoolean      iOnlyForUseFullSupport = FALSE )= 0;

  virtual void ContainsNonDatumModelisation(CATICGMUnknown *iHolder)= 0;

  //=======================================================================================
  //  Prevents iHolder from being seen Fat (because of LyingOn links for instance)
  //=======================================================================================
  virtual void OverrideFatStatus(CATICGMUnknown*                                  iHolder,
                                 CATCGMGeometryOfFatAble::OverrideFatStatusReason iReason) = 0;

  //=======================================================================================
  // To filter discarded anomalies
  //=======================================================================================
  virtual void ComputeOverrideFatStatusesBefore() = 0;
  virtual int ComputeOverrideFatStatusesAfter(CATLISTP(CATCGMGeometryOfFatAble)& iCandidateFatCells) = 0;

  //=======================================================================================
  // Pour optimisation perfo dans  CATCGMTopoCXMODEL::UpdateEdgeSimplifiedSupport(...)
  //=======================================================================================
  virtual CATArrayBoundingEdgeHashTable* GetArrayBoundingEdgeHashTable() = 0;
  virtual CATListDbgPoseSurHashTable*    GetListDbgPoseSurVertexHashTable() = 0;


  void       ForceLyingOnAnalysis(CATBoolean iUseful = TRUE); 
  INLINE  CATBoolean IsLyingOnAUsefulUsefulDependancy() const; 

  void       ForceSpecsOfPOECToBeChecked(CATBoolean iToCheck = TRUE); 
  INLINE  CATBoolean AreSpecsOfPOECToBeChecked() const; 

  //=====================================================================================================
  //   "UsefulLimits"  Utility used by FilletSurface, DraftSurface...
  //=====================================================================================================
  virtual void InclusionPtCrv(const CATMathPoint & M,
               const CATCurve * Crv,
               const CATCrvLimits & CrvLimits,
               double tol,
               CATLONG32 & nbsol,
               CATCrvParam & CrvParam,
               double & dist) const =0;




  //======================================================================================================================
  //  ODT Only (phase de PERFO)
  //======================================================================================================================
  virtual short PropagateUntilStep(short iUntilStep) = 0;

  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;

  
  //=======================================================================================
  // volatile usage,
  //  for delayed optimisation , more precise analysis of targetted optimisation  
  //             Poec/Pos detection is delayed if their support are still usefull
  //               (from strong link of Edge/Face defined in the context) 
  //             even if no explicit topological usage [ Cell(Edge,) or Subd(LyingOn)) ]
  //=======================================================================================
  virtual CATCGMHashTable *GetUseFullSupport() const = 0;

  // PCS (Be Carefull)
  void SetEmitterObjectsCount( int  iEmitterObjectsCount );
  void SetLimitedScope( CATLISTP(CATCGMObject) * iLimitedCopied ); // By Reference (NO COPY)


protected:

  CATCGMQueryManager(CATGeoFactory                    * iFactory, 
                     CATSoftwareConfiguration         * iConfig,
                     const CATLISTP(CATICGMUnknown)   & iInputs );

  
  INLINE void SetQueryType(CATCGMQueryManager::TypeOfQuery  iType);

  //=======================================================================================
  // Gestion u Contexte
  //=======================================================================================
  CATCGMQueryManager::TypeOfQuery   _TypeOfQuery;

  CATLISTP(CATICGMUnknown)    _Inputs;
  CATLISTP(CATCGMObject)    * _LimitedScope;

  CATSoftwareConfiguration   *_Config;
  CATBoolean                  _Validated;
  
  CATBoolean                  _HasRun;
    
  //---------------------------------------------------
  // Pour mode "UsefulDependancies"  gestion interne
  //---------------------------------------------------
  CATBoolean                  _LyingOnUseful;
  CATBoolean                  _SpecsOfPOECToBeChecked;
  
  //---------------------------------------------------
  // Pour mode "UsefulLimits"  gestion interne
  //---------------------------------------------------
  CATBoolean    _ForceSecureCertifiedUnextrapolable;
  CATBoolean    _ForceExtendSurfaceOfLoop;
  CATBoolean    _ForceExtendToArcLimits;

  CATBoolean    _ForcedCorruptingUnextrapol;
  CATBoolean    _ForceCorruptingForgetOriginalLimits;
  CATBoolean    _ForceCorruptingNoUnavailablePropagation;
  CATBoolean    _ForceCorruptingNoMaxLimitsPropagation;
  CATBoolean    _ForceCorruptingWithDegeneratedLimits;
  CATBoolean    _AllowedNewFormat_NegativeOffset_KnotVector;
  CATBoolean	_ForcedToExtendLoopLimits;
  CATCGMLimits_DisableCGMObjectType	_ForcedDisableCGMObjectType;

  int                      _EmitterObjectsCount;

};


//---------------------------------------------------
// gestion QueryType
//---------------------------------------------------

INLINE CATCGMQueryManager::TypeOfQuery CATCGMQueryManager::GetQueryType() const
{
  return _TypeOfQuery;
}

INLINE void CATCGMQueryManager::SetQueryType(CATCGMQueryManager::TypeOfQuery  iType)
{
  _TypeOfQuery = iType;
}

//---------------------------------------------------
// Pour mode "UsefulDependancies"   
//---------------------------------------------------
INLINE CATBoolean CATCGMQueryManager::IsLyingOnAUsefulUsefulDependancy() const
{
  return _LyingOnUseful;
}

INLINE  CATBoolean CATCGMQueryManager::AreSpecsOfPOECToBeChecked() const
{
  return _SpecsOfPOECToBeChecked;
}


//---------------------------------------------------
// Pour mode "UsefulLimits"   parametrage interne
//---------------------------------------------------
INLINE CATBoolean CATCGMQueryManager::IsForceSecureCertifiedUnextrapolable() const
{
  return _ForceSecureCertifiedUnextrapolable ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForcedToExtendToArcLimits() const
{
  return _ForceExtendToArcLimits ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForcedToExtendSurfaceOfLoop() const
{
  return _ForceExtendSurfaceOfLoop ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForcedCorruptingUnextrapol() const
{
  return _ForcedCorruptingUnextrapol ? TRUE : FALSE;
}


INLINE CATBoolean CATCGMQueryManager::IsAllowedNewFormat_NegativeOffset_KnotVector() const
{
  return _AllowedNewFormat_NegativeOffset_KnotVector ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForceCorruptingForgetOriginalLimits() const
{
  return _ForceCorruptingForgetOriginalLimits ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForceCorruptingNoMaxLimitsPropagation() const
{
  return _ForceCorruptingNoMaxLimitsPropagation ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForceCorruptingNoUnavailablePropagation() const
{
  return _ForceCorruptingNoUnavailablePropagation ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForceCorruptingWithDegeneratedLimits() const
{
  return _ForceCorruptingWithDegeneratedLimits ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForcedToExtendLoopLimits() const
{
  return _ForcedToExtendLoopLimits ? TRUE : FALSE;
}

INLINE CATBoolean CATCGMQueryManager::IsForcedDisableCGMObjectType(CATCGMLimits_DisableCGMObjectType iDisableCGMObjectType) const
{
  return _ForcedDisableCGMObjectType & iDisableCGMObjectType ? TRUE : FALSE;
}


extern "C" { typedef void CATCXBodyCleaner_LimitedScope(CATCGMOperator*iBodyCleaner, CATLISTP(CATCGMObject) *iLimitedScope); }


#endif
