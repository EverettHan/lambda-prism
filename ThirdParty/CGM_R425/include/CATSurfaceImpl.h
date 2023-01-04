/* -*-c++-*-*/
#ifndef CATSurfaceImpl_h
#define CATSurfaceImpl_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 *  Default implementation for CATSurface Interface
 */

#include "CATGeometryImpl.h"
#include "CATSurface.h"
class CATMathTransformation2D;
class CATMathTransformation;

class ExportedByYP00IMPL CATSurfaceImpl : public CATGeometryImpl
{
public:
  CATDeclareClass;
  CATSurfaceImpl();
  virtual ~CATSurfaceImpl();

  // Interface CATSurface
  //-----------------------------------------------------------------------------
  virtual void GetBox(const CATSurLimits & iLimits, CATMathBox & oBox) const;
  virtual void EvalPoint(const CATSurParam & iPosition,
			 CATMathPoint & oPoint )const ;
  virtual CATMathPoint EvalPoint(const CATSurParam & iParam) const;
  virtual void EvalFirstDeriv(const CATSurParam & iParam,
			      CATMathVector     & oDU,
			      CATMathVector     & oDV) const ;
  virtual void EvalSecondDeriv(const CATSurParam & iParam,
			       CATMathVector     & oDU2,
			       CATMathVector     & oDUDV,
			       CATMathVector     & oDV2) const ;
  virtual void EvalThirdDeriv(const CATSurParam & iParam,
			      CATMathVector     & oDU3,
			      CATMathVector     & oDU2DV,
			      CATMathVector     & oDUDV2,
			      CATMathVector     & oDV3) const ;
  virtual CATMathDirection EvalNormal(const CATSurParam & iParam) const;
  virtual void EvalNormal(const CATSurParam & iParam, CATMathDirection & oNormal) const;
  virtual void Eval(const CATSurLimits & iBoxToEvaluate,
		    CATEvalCommand iCommand,
		    CATMathGridOfPoints  * iPointm,
		    CATMathGridOfVectors * iVectord1,
		    CATMathGridOfVectors * iVectord2) const;
  virtual void EvalMultiple(const CATSurLimits      & iBox,
			    CATLONG32                      iNbOfPointsInU,
			    CATLONG32                      iNbOfPointsInV,
			    const CATSurEvalCommand & iCommand,
			    CATSurEvalResult        & oResult) const ;
  virtual void EvalLocal(const CATSurParam       & iPoint,
			 const CATSurEvalCommand & iCommand,
			 CATSurEvalLocal         & oResult) const ;
  virtual CATCurve *ExtractIsoParametricCurve(const CATIsoParameter iIsoParameter,
					      const CATSurParam & iParam,     
					            CATGeoFactory *iWhere ) const;
  virtual CATBoolean IsClosedU() const;
  virtual CATBoolean IsClosedV() const;
  virtual void GetMappingU(CATMathTransformation1D &oTransfo1D) const ;
  virtual void GetMappingV(CATMathTransformation1D &oTransfo1D) const;
  virtual short GetOrientation( ) const  ;
  virtual void SetOrientation( const short iNewOrientation ) ;
  virtual const CATKnotVector * GetKnotVectorU() const;
  virtual const CATKnotVector * GetKnotVectorV() const;
  virtual void CreateParam(const double & iParamU,
			   const double & iParamV,
			   CATSurParam & oResult) const;

  virtual void CreateParam(const double & u, const CATLONG32 & iu,
			   const double & v, const CATLONG32 & iv,
			   CATSurParam & oResult) const;
  virtual CATSurParam CreateParam(const double & iUParam,
				  const double & iVParam) const ;
  virtual CATSurParam CreateParam(const double & iUParam, const CATLONG32 & iUNum,
				  const double & iVParam, const CATLONG32 & iVNum) const ;
  virtual const CATSurParamReference * GetParamReference() const ;
  virtual void GetStartLimit(CATSurParam & oParam) const  ;
  virtual void GetEndLimit(CATSurParam & oParam) const  ;
  virtual void GetLimits(CATSurLimits & oLimits) const ;
  virtual void GetMaxLimits(CATSurLimits & oLimits) const  ;
  virtual void GetInternalMaxLimits(const CATLONG32 iIndexU, 
				    const CATLONG32 iIndexV,
				    CATSurLimits & oLimits) const ;
  virtual void GetInternalLimits(const CATLONG32 iIndexU, 
				 const CATLONG32 iIndexV,
				 CATSurLimits & oLimits) const ;
  virtual CATSurParam GetStartLimit() const;
  virtual CATSurParam GetEndLimit() const;
  virtual CATSurLimits GetLimits() const;
  virtual CATSurLimits GetMaxLimits() const;
  virtual CATSurLimits GetInternalLimits(const CATLONG32 iIndexU, const CATLONG32 iIndexV) const;
  virtual CATSurLimits GetInternalMaxLimits(const CATLONG32 iIndexU, const CATLONG32 iIndexV) const;
  virtual void SetLimits(const CATSurLimits & iNewLimits)  ;
  virtual void GetNumberOfComponent( CATLONG32 & oNbOfUPatches, CATLONG32 & oNbOfVPatches) const ;
  virtual void Lock() ;
  virtual void Unlock() ;
  virtual void OpenEquation () ;
  virtual void CloseEquation () const;
  virtual void GetEquation(const CATLONG32 iUNum, const CATLONG32 iVNum,
			   const CATMathFunctionXY * & oFx,
			   const CATMathFunctionXY * & oFy,
			   const CATMathFunctionXY * & oFz) const;
  virtual void GetGlobalEquation(const CATMathFunctionXY * & oFx,
				 const CATMathFunctionXY * & oFy,
				 const CATMathFunctionXY * & oFz) const;
  virtual CATMathFunctionRN *GetImplicitEquation () const ;
  virtual CATBoolean HasImplicitEquation() const ;
  virtual CATMathCurve* GetMathCurve(const CATIsoParameter   iIsoParameter,
				     const CATSurParam     & iLocation ) const  ;
  virtual CATBoolean HasMathCurve(const CATIsoParameter   iIsoParameter,
				  const CATSurParam     & iLocation ) const  ;
  virtual void GetInternalBoundingBox(const CATLONG32 IndexU, 
				      const CATLONG32 IndexV,
				      CATMathBox & oBox) const ;
  virtual void GetInternalMaxBoundingBox(const CATLONG32 IndexU, 
					 const CATLONG32 IndexV,
					 CATMathBox & oBox) const ;
  virtual CATMathBox GetInternalBoundingBox(const CATLONG32 iUNum,
	                                        const CATLONG32 iVNum) const ;
  virtual CATMathBox GetInternalMaxBoundingBox(const CATLONG32 iUNum,
	                                           const CATLONG32 iVNum) const ;
  virtual void GetDirBox( CATMathDirBox & oDirBox ) const  ;
  virtual void GetInternalDirBox(const CATLONG32 iIndexU, const CATLONG32 iIndexV, CATMathDirBox &oDirBox) const ;
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
						     CATSurParam  & oIndex ) const  ;
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
						     CATSurParam  & oIndex   ,
						     const CATSurLimits & iInside  ) const  ;
  virtual CATSurface::CATSolutionDiagnostic GetParamOnIsopar( const CATMathPoint    & iPoint,
                                                              const CATIsoParameter & iIsoparam,
                                                              const CATSurParam     & iStart,
                                                              const CATSurParam     & iEnd,
                                                                    double          & oLambdaOnIsopar) const ;
  virtual CATBoolean Compare( const CATSurParam &iw1, const CATSurParam & iw2 ) const ;
  virtual CATIsoParameter IsLinear() const ;
  virtual CATIsoParameter IsCircular() const ;
  virtual const CATSurface * GetGeometricRep() const ;
  virtual CATSurface * CreateOffset(CATGeoFactory * iWhere, 
		                                const CATLength & iOffset,
																		const CATSurLimits &iLimits,
																		CATMathTransformation2D * &oTransfo2D) const ;
  virtual CATMathSetOfLongs *GetNumberOfComponent() const;
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
				const CATSurface              * iTSurface,
				CATMathTransformation2D * oTransfo2D = NULL) const ;
  virtual CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
			         CATMathTransformation2D* oTransfo2D = NULL) const ;
  virtual int GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &ioBox) const;
};

#endif
