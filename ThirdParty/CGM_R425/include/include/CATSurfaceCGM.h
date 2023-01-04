/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSurfaceCGM:
//  class for CGM objects that are compliant with CATSurface Interface
//=============================================================================
// Usage notes:
//
// This is an implementation of the CATSurface based on CATCGMContainer
// infrastructure.
//
// No check is done on Parameter being inside Parametric definition
// of the Surface.
//=============================================================================
// Mar. 97   Creation                                     S. Royer
// Apr. 98   Add IsInvariant method                       I. Levy
// May  98   Add IsConfused method                        I. Levy
// Sept 98   Add UpdateDataForExtrapol                    P. Tonnerre
// Oct. 98   Add IsDeepConfused method                    I. Levy
// Nov. 03   friend class CATCGMDebugImpl                 HCN
// Mar. 05 RI0486478 : GetStreamPreferedRank()                            HCN
// Nov. 16 IR-462457 : Added TestConfusionUsingCompareGeometry().         R1Y
//=============================================================================
//
// CATGeometryCGM:
//        CATCanonicalSurfaceCGM:
//               CATConeCGM:
//               CATCylinderCGM:
//               CATPlaneCGM:
//               CATSphereCGM:
//               CATTorusCGM:
//        CATCircularSweepCGM:  !! 0 ODT !!
//        CATExtrudedSurfaceCGM:
//               CATRevolutionSurfaceCGM:
//               CATTabulatedCylinderCGM:
//        CATForeignSurfaceCGM:
//        CATGenericFilletCGM:
//        CATGenericRuledSurfaceCGM:
//        CATNurbsSurfaceCGM:
//        CATProcOffsetSurfaceCGM: 
//        CATProcSurfaceCGM:    !! Surely not used (9 odts)
//        CATRuledSurfaceCGM :  !! Probably not used now, but some modle exist with this surface (see impact on unstream) !!!
//        CATSpecSurfaceBaseCGM: 
//               CATChamferSurfaceCGM:
//               CATDirectionalSurfaceCGM:
//               CATDraftSurfaceCGM:
//               CATFilletSurfaceCGM:
//               CATOffsetSurfaceCGM:
//               CATSpecSurfaceCGM:
//               CATSweepSegmentSurfaceCGM:
//               CATSweepSurfaceCGM:
//        CATSubdivCellSurfaceCGM:
//        CATSubdivGridSurfaceCGM: 
//        CATTransformedSurfaceCGM: 
//               CATLinearTransfoSurfaceCGM:
//               CATNonLinearTransfoSurfaceCGM:
//
//=============================================================================

#ifndef CATSurfaceCGM_H
#define CATSurfaceCGM_H

class CATSurLimits ;                          // For Interface
class CATSurParam ;
class CATSurParamReference;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATCartesianPoint ;
class CATKnotVector;
class CATMathFunctionRN;
class CATMathCurve ;
class CATMathBox ;              
class CATMathIntervalND;
class CATSurfaceCGMOptData1;
class CATCGMPeriodicityInfo;

class CATCX_CHECKUP ;                          // For CheckUp

#include "CATMathDef.h"
#include "CATGeometryCGM.h"                  // For Inheritance
#include "CATSurface.h"
#include "CATCGMLimitsManagement.h"
#include "CATMathInline.h"
#include "ExportedByCATGeometricObjectsCGM.h"
 
#include "CATListOfCATPCurves.h"
typedef CATLISTP(CATPCurve) ListPOfCATPCurves;


#define JSX_ArchiGeo_Surface_0 // actif 03/10/2014 JSX use mother's classe methods for deprecated
#define JSX_ArchiGeo_Surface_1 // actif 03/10/2014 JSX use mother's classe methods for deprecated

//-----------------------------------------------------------------------------
class ExportedByCATGeometricObjectsCGM CATSurfaceCGM: public CATGeometryCGM
{
  public :
     
  //--------------------------------------------------------
  // Fusion
  virtual void LockEquation(void *iForDebug);
  virtual void UnLockEquation(void *iForDebug);
  virtual CATCGMLimitsManagement GetLimitsManagement();

  // TCX le 02/02/02
  virtual void CheckFromFace( const CATSurLimits & iLimits, CATCGMObject *iFaceContext, CATCX_CHECKUP* report );

  virtual void CheckSmallArcs(int iAtCheckUp = 0);

  //-------------------------------------------------------------------------
  // Gestion par evenement des modifications modeles (Extrapolation / Trim)
  //-------------------------------------------------------------------------
  void MaxLimitsHaveChanged( const CATSurLimits & iBefore, const CATSurLimits & iAfter);

  //------------------------------------------------------------------------------
  // Identification des vrais implementations porteurs de donnees extrapolees
  //------------------------------------------------------------------------------
  virtual CATCGMLimitsManagement QueryLimitsManagement(CATSurLimits *ioMinimaLimits = NULL);
  
  //-------------------------------------------------------------------------
  // Methods of CATSurface interface
  //-------------------------------------------------------------------------
  virtual void GetBox( const CATSurLimits & iLimits, CATMathBox & oBox) const;

  virtual int        GetAdvancedBox                    (const CATSurLimits &iLimits, CATMathAdvancedBox &ioBox)                    const;
  virtual int        GetAdvancedBoundingBox            (CATMathAdvancedBox &ioBox)                                                 const;
  virtual CATBoolean IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType)                                              const;
  virtual int        GetInternalMaxAdvancedBoundingBox (const CATLONG32 IndexU, const CATLONG32 IndexV, CATMathAdvancedBox &ioBox) const;

  virtual void GetLimits           (CATSurLimits & oLimits)                                                                        const ;

  virtual void GetMaxLimits        (CATSurLimits & oLimits)                                                                        const = 0;
  
  virtual void GetStartLimit       (CATSurParam & oParam)                                                                          const = 0;
  
  virtual void GetEndLimit         (CATSurParam & oParam)                                                                          const = 0 ;
  
  virtual void GetInternalMaxLimits(const CATLONG32 iIndexU, const CATLONG32 iIndexV, CATSurLimits & oLimits)                      const = 0;
  
  virtual void GetInternalLimits   (const CATLONG32 iIndexU, const CATLONG32 iIndexV, CATSurLimits & oLimits)                      const ;

  virtual const CATKnotVector * GetKnotVectorU() const;

  virtual const CATKnotVector * GetKnotVectorV() const;

  virtual void CreateParam(const double & iParamU,
                           const double & iParamV,
                                 CATSurParam  & oResult) const;

  virtual void CreateParam(const double & u, const CATLONG32 & iu,
                           const double & v, const CATLONG32 & iv,
                           CATSurParam & oResult) const;

  // Equations

  virtual void Lock (const void *iDebugUsage=NULL);
  virtual void OpenEquation (const void *iDebugUsage=NULL);

  virtual void Unlock (const void *iDebugUsage=NULL);
  virtual void CloseEquation (const void *iDebugUsage=NULL);

  void GetEquation(const CATLONG32 iIndexU, const CATLONG32 iIndexV,
                   const CATMathFunctionXY * & oFx,
                   const CATMathFunctionXY * & oFy,
                   const CATMathFunctionXY * & oFz) const ;

  virtual void GetGlobalEquation(const CATMathFunctionXY * & oFx,
                                 const CATMathFunctionXY * & oFy,
                                 const CATMathFunctionXY * & oFz) const ;

  CATMathFunctionRN* GetImplicitEquation () const ;

  virtual void GetEquationsSize(int & oIndexOffsetU,
                                int & oMaxCountU,
                                int & oIndexOffsetV,
                                int & oMaxCountV,
                                int & oFunctionsSize) = 0 ;

  virtual void CreateLocalEquation(const CATLONG32 iIndexU, const CATLONG32 iIndexV,
                                   const CATMathFunctionXY * & oFx,
                                   const CATMathFunctionXY * & oFy,
                                   const CATMathFunctionXY * & oFz) ; // Par defaut, NULL, NULL, NULL

  virtual void CreateGlobalEquation( const CATMathFunctionXY * & ioFx,   // Par defaut, PieceWise de LocalEquations
                                     const CATMathFunctionXY * & ioFy,
                                     const CATMathFunctionXY * & ioFz) ; // Creation ou Extrapolation (Fx, Fy, Fz # NULL)

  virtual CATMathFunctionRN* CreateImplicitEquation () ; // Par defaut { return NULL } ;

  virtual void CreateFunctions(CATMathFunctionX ** Functions);

  virtual void DeleteEquations() ; // Par defaut, { if ( _Equations[*] ) delete _Equations[*] ; idem _Functions & _ImplicitEquation  }

  CATBoolean IsEquationComputed(const CATLONG32 iIndexU, const CATLONG32 iIndexV) const ; 

  virtual CATBoolean IsModifiable() const ;

          //                                                              // Ce service cree par TXO22/02/10 pour des besoins d'optimisation
          //                                                              // semble indiquer que toutes les equations sont homogenes
          //                                                              // du point de vue du IsOption().                        NLD030714
  virtual CATBoolean HasHomogeneousEquations() const;

  // Box
  virtual void GetInternalBoundingBox(const CATLONG32 IndexU, 
                                      const CATLONG32 IndexV,
                                            CATMathBox & oBox) const;

  virtual void GetInternalMaxBoundingBox(const CATLONG32 IndexU, 
                                         const CATLONG32 IndexV,
                                               CATMathBox & oBox) const;
  // 
  // Pure virtual methods of evaluation 
  
  virtual void EvalPoint(const CATSurParam  & iPosition,
                               CATMathPoint & oPoint )const = 0 ;

  virtual void EvalFirstDeriv(const CATSurParam &iPosition,
                                    CATMathVector     & oDU,
                                    CATMathVector     & oDV) const = 0;

  virtual void EvalSecondDeriv(const CATSurParam & iPosition,
                                     CATMathVector     & oDU2,
                                     CATMathVector     & oDUDV,
                                     CATMathVector     & oDV2) const = 0;

  virtual void EvalThirdDeriv(const CATSurParam & iPosition,
                                    CATMathVector     & oDU3,
                                    CATMathVector     & oDU2DV,
                                    CATMathVector     & oDUDV2,
                                    CATMathVector     & oDV3) const = 0;
 
  virtual void EvalNormal(const CATSurParam & iPosition, CATMathDirection & oUnitNormal) const;

  virtual void EvalMultiple(const CATSurLimits      & iBox,
                                  CATLONG32                      iCountPointsInU,
                                  CATLONG32                      iCountPointsInV,
                            const CATSurEvalCommand & iCommand,
                                  CATSurEvalResult        & oResult) const;
  
  virtual void EvalLocal(const CATSurParam       & iParameter,
                         const CATSurEvalCommand & iCommand,
                               CATSurEvalLocal         & oResult) const;

  // -----------------------------------------------------------------------
  // Sets the value of a direction box according to a given patch of the surface 
  // or the to the whole surface.
  // This methods takes into account the current limits of the surface.
  // All the normals of the surface ( returned by EvalNormal ) belong to
  // { CATMathDirection Dir / Dir * DirBox.GetDirection() > cos ( DirBox.GetSize() ) },
  // where DirBox = Surface->GetDirBox() ; 
  // -----------------------------------------------------------------------
  virtual void GetDirBox( CATMathDirBox & oDirBox ) const;
  virtual void GetInternalDirBox(const CATLONG32 IndexU, 
                                 const CATLONG32 IndexV, 
                                       CATMathDirBox &oDirBox) const;

  //------------------------------------------------------------------------
  virtual CATIsoParameter IsLinear   () const;
  virtual CATIsoParameter IsCircular () const;

  //------------------------------------------------------------------------
  virtual void            GetMappingU (CATMathTransformation1D &oTransfo1D) const;
  virtual void            GetMappingV (CATMathTransformation1D &oTransfo1D) const;

  // -----------------------------------------------------------------------
  virtual CATMathCurve*   GetMathCurve(const CATIsoParameter   iIsoParameter,
                                       const CATSurParam     & iLocation  ) const ;

  virtual CATBoolean      HasMathCurve(const CATIsoParameter   iIsoParameter,
                                       const CATSurParam     & iLocation ) const ;

  // -----------------------------------------------------------------------
  // Sets the parameters corresponding to a given point and returns how many
  // parameters may be evaluated on this point:
  // None, Single, Multiple or InfiniteCount. 
  // Only Parameters inside the Limits are provided.
  // If no Limits is provided, then MaxLimits is assumed.
  // GetParam() is only defined for surfaces for which GetImplicitEquation 
  // returns a non NULL pointer; otherwise, it returns an exception.
  // -----------------------------------------------------------------------
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
                                                           CATSurParam  & oIndex ) const;
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
                                                           CATSurParam  & oIndex   ,
                                                     const CATSurLimits & iInside  ) const;
  virtual CATSurface::CATSolutionDiagnostic GetParamOnIsopar( const CATMathPoint    & iPoint,
                                                              const CATIsoParameter & iIsoparam,
                                                              const CATSurParam     & iStart,
                                                              const CATSurParam     & iEnd,
                                                                    double          & oLambdaOnIsopar) const ;

  //-------------------------------------------------------------------------
  // Returns TRUE if the 2 parameters can be considered as being the same.
  // Compare is done in parametric space, according to 3D distance.
  // 2 points accross surface closure are not considered as being the same point.
  //-------------------------------------------------------------------------
  virtual CATBoolean Compare( const CATSurParam &iw1, const CATSurParam & iw2 ) const ;

  //-------------------------------------------------------------------------
  // Returns a pointer on the geometric representation of the CATSurface
  //-------------------------------------------------------------------------
  virtual const CATSurface * GetGeometricRep() const ;

  //-------------------------------------------------------------------------
  // Returns TRUE if the surface has an Implicit Equation
  //-------------------------------------------------------------------------
  virtual CATBoolean HasImplicitEquation() const ;

  //-------------------------------------------------------------------------
  // Returns TRUE if the surface is invariant
  //-------------------------------------------------------------------------
  virtual CATBoolean IsInvariant(const CATMathTransformation   & iTransfo,
                                       CATMathTransformation2D * oTransfo2D = NULL) const;
  
  //-------------------------------------------------------------------------
  // Returns TRUE if  T( this ) == TSurface
  //-------------------------------------------------------------------------
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
                                const CATSurface              * iTSurface,
                                      CATMathTransformation2D * oTransfo2D = NULL) const;

  virtual CATBoolean IsDeepConfused(      CATTransfoManager & iTransfo,
                                    const CATGeometry       * iTGeometry) const;

  //-------------------------------------------------------------------------
  // Method of the CATTranfoManager
  //-------------------------------------------------------------------------
  virtual CATGeometry* CloneAndMove3D(CATTransfoManager& iTransfo);

  //-------------------------------------------------------------------------
  // Creates an Offset Surface of the CATSurface
  //-------------------------------------------------------------------------
  virtual CATSurface * CreateOffset(      CATGeoFactory * iWhere,
                                    const CATLength & iOffset,
                                    const CATSurLimits &iLimits,
                                          CATMathTransformation2D * &oTransfo2D) const;

  //-------------------------------------------------------------------------
  // Methods of the CATGeometry Interface implemented at that level
  //-------------------------------------------------------------------------
  virtual void GetBoundingBox(CATMathBox & oBox) const ;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATSurfaceCGM();
  void Clear();
  void ClearBoxes();
  void ClearEquations();
  virtual ~CATSurfaceCGM();

  //-------------------------------------------------------------------------
  // Do Not Use
  //-------------------------------------------------------------------------
  virtual CATMathPoint EvalPoint(const CATSurParam &iParam) const  ;

  virtual CATSurLimits GetLimits() const ;

  virtual CATSurLimits GetMaxLimits() const  ;
  
  virtual CATSurParam GetStartLimit() const ;
  
  virtual CATSurParam GetEndLimit() const  ;

  virtual const CATSurParamReference * GetParamReference() const;
  
  virtual CATSurLimits GetInternalMaxLimits(const CATLONG32 iIndexU, 
                                            const CATLONG32 iIndexV) const ;

  virtual CATSurLimits GetInternalLimits(const CATLONG32 iIndexU, 
                                         const CATLONG32 iIndexV) const ;

  virtual CATSurParam CreateParam(const double & paramU,
                                  const double & paramV) const;

  virtual CATSurParam CreateParam(const double & u, const CATLONG32 & iu,
                                  const double & v, const CATLONG32 & iv) const;

  virtual CATMathDirection EvalNormal(const CATSurParam & iPosition) const;

  virtual CATMathBox GetBoundingBox() const ;

  virtual CATMathBox GetInternalBoundingBox   (const CATLONG32 IndexU, const CATLONG32 IndexV) const;

  virtual CATMathBox GetInternalMaxBoundingBox(const CATLONG32 IndexU, const CATLONG32 IndexV) const;

  short GetOrientation( ) const ;

  void  SetOrientation( const short iNewOrientation ) ;

  //-------------------------------------------------------------------------
  //  Stream / UnStream
  //-------------------------------------------------------------------------
  virtual void GetStartGlobalParam(double & oStartU, double & oStartV) const;
  virtual void GetEndGlobalParam(double & oEndU, double & oEndV) const;


 //-------------------------------------------------------------------------
  // Gestion des caches
  //-------------------------------------------------------------------------
  virtual void IsModified () ;


  virtual void PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery ) = 0;

  virtual CATCurve *CreateIsoParametricCurve(const CATIsoParameter iIsoParameter,
      const CATSurParam & iParam, const CATSurLimits & iSurLimits, CATCrvLimits & oCrvLimits,
      CATLONG32 & oOrient, CATGeoFactory *iWhere ) const;

  //-------------------------------------------------------------------------
  // Optimisation de la structure du container sur disque
  //-------------------------------------------------------------------------
  virtual CATULONG32 GetStreamPreferedRank();

  virtual CATULONG32  ReleaseReference ( CATICGMObject *From , CATBoolean iRemoveIfPossible = TRUE , CATBoolean * oRemoved = 0) ;

  //--------------------------------------------------------------------------------
  // Service permettant a une surface de proteger des PCurves posees sur elle-meme.
  // Pour utiliser ce service, il faut appeler la methode CloneProtectedPCurves dans
  // les methodes Clone et CloneAndMove3D de la surface et la methode 
  // MoveProtectedPCurves dans la methode Move3D de la surface.
  // Le clonage des ProtectedPCurves ne fonctionne pas en cas de clone entre 
  // plusieures factory.
  //--------------------------------------------------------------------------------
  // Renvoie l'index permettant d'acceder a la PCurve protegee (0 en cas d'echec) et met le pointer ioPCurveToProtect a NULL.
  CATLONG32 AddProtectedPCurve (CATPCurve *&ioPCurveToProtect);
  // Renvoie la PCurve protegee a partir de son index.
  CATPCurve * GetProtectedPCurve(CATLONG32 iPCurveIndex) const;
  // Renvoie le nombre de PCurves protegees.
  CATLONG32 GetNumberOfProtectedPCurves() const;
  // Methode a appeler dans les methodes Clone et CloneAndMove3D pour que la surface clonee protege les clones
  // des PCurves protegees par this.
  void CloneProtectedPCurves(CATSurface *iCloneOfThis, CATMathTransformation2D *iTransfo2D = NULL) const;
  // Methode a appeler dans la methode Move3D pour mettre a jour les PCurves protegees.
  void MoveProtectedPCurves(CATTransfoManager& iTransfo);

  //-------------------------------------------------------------------------
  // Integration CATCGMPeriodicityManager Procedural 
  //-------------------------------------------------------------------------
  virtual CATBoolean CATCGMPeriodicityManager_GetInfo(CATBoolean iUorV, CATCGMPeriodicityInfo & oInfo ) const ;
  virtual void CATCGMPeriodicityManager_SetInfo(CATBoolean iUorV,  const CATCGMPeriodicityInfo & iInfo)   ;

  //-----------------------------------------------------------------------
  // Niveau de protection des equations et CATCGMAttrIsopar
  //-----------------------------------------------------------------------
  INLINE int GetLockCount() const;

  //-------------------------------------------------------------------------
  // For Createparam
  //-------------------------------------------------------------------------
  virtual CATBoolean IsClosedU() const=0;
  virtual CATBoolean IsClosedV() const=0;

  virtual CATCurve *ExtractIsoParametricCurve(const CATIsoParameter iIsoParameter,
    const CATSurParam &iParam,
    CATGeoFactory *iWhere) const=0;

protected:
  //-----------------------------------------------------------------------
  // Detection d'equation ouvertes empechant la redefinition d'un objet
  //-----------------------------------------------------------------------
  virtual CATBoolean IsLocked(int * oLockCount = 0);
  // forced destruction of OptData (throws if locked)
  virtual void DestroyOptData();

  //-------------------------------------------------------------------------
  // Virtual method returning the number of patches
  //-------------------------------------------------------------------------
  virtual void GetNumberOfComponent( CATLONG32 & oUCount, CATLONG32 & oVCount) const = 0;

  //-------------------------------------------------------------------------
  // Gestion des caches
  //-------------------------------------------------------------------------
  virtual void IsTrimmed (CATBoolean NotifyModification = TRUE) ;
   
  //-------------------------------------------------------------------------
  // verification de validite minimale de la surface
  //-------------------------------------------------------------------------
  virtual void CheckUp(CATCX_CHECKUP* report);

  virtual void ComputeDirBoxes () const ;

  virtual void EvalMultipleOld(const CATSurLimits      & Box,
                 CATLONG32                      CountPointsInU,
                 CATLONG32                      CountPointsInV,
                 const CATSurEvalCommand & Command,
                 CATSurEvalResult        & Result) const;  

  virtual void ComputeInternalBox        (CATLONG32 iu, CATLONG32 iv,
                                          CATMathBox & Box          ) const;
  virtual void ComputeTrimmedBox         (CATLONG32 iu, CATLONG32 iv, 
                                          double local_u0, double local_u1,
                                          double local_v0, double local_v1,
                                          CATMathBox & Box          ) const;

  virtual int ComputeInternalAdvancedBox(CATLONG32 iu, CATLONG32 iv,
                                         CATMathAdvancedBox &ioBox  ) const;

  // Function to use the CATCompareGeometry operator to determine whether two surfaces are confused.
  // Returns TRUE if the two surfaces are the same, and FALSE otherwise.
  CATBoolean TestConfusionUsingCompareGeometry(const CATMathTransformation   & iTransfo,
                                               const CATSurface              * iTSurface,
                                                     CATMathTransformation2D * oTransfo2D = NULL) const;

  //-------------------------------------------------------------------------
  // Cache Bounding Boxes et DirBoxes
  //-------------------------------------------------------------------------
  CATMathDirBox *_DirBoxes ;
  
  //
  // Flaguer les Objets non C2 et deflaguer les Objets redevenu C2.
  //
  static void ContinuitySurfaceCheck(const CATSurface* ipSurfaceToCheck);

#ifdef JSX_ArchiGeo_Surface_0
  // Pour factoriser ici l'ancien changement de signature
  CATMathSetOfLongs* GetNumberOfComponent() const;
#endif
  //-------------------------------------------------------------------------
  // Data for the equations optimization.
  //-------------------------------------------------------------------------
private :
  int                     _LockCount;
  CATSurfaceCGMOptData1 * _OptData;

  friend class CATSurfaceCGMOptData1;

  ListPOfCATPCurves * _ProtectedPCurvesList; 

protected :

  CATSurfaceCGMOptData1 * GetOptData() const;
  virtual CATBoolean IsOptData() const;

  
  friend class CATCGMDebugImpl;
};

INLINE int CATSurfaceCGM::GetLockCount() const
{
  return _LockCount;
}


#endif

