/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSurfaceTmp:
// Temporary implementation of CATSurface interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATSurfaceTmp_H
#define CATSurfaceTmp_H

#include "YP00TMP.h"
#include "CATGeometryTmp.h"
#include "CATSurface.h"

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATSurfaceTmp: public CATGeometryTmp
{
  public :

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATSurfaceTmp() ;
  ~CATSurfaceTmp() ;

  //=========================================================================
  //- Implementations for CATSurface interface
  //=========================================================================
  virtual void GetBox( const CATSurLimits & iLimits, CATMathBox & oBox) const;
  CATMathPoint EvalPoint(const CATSurParam & iPosition) const;
  void EvalPoint(const CATSurParam & iPosition,
		 CATMathPoint & oPoint )const;
  void EvalFirstDeriv(const CATSurParam & iPosition,
		      CATMathVector     & oDU,
		      CATMathVector     & oDV) const;
  void EvalSecondDeriv(const CATSurParam & iPosition,
		       CATMathVector     & oDU2,
		       CATMathVector     & oDUDV,
		       CATMathVector     & oDV2) const;
  void EvalThirdDeriv(const CATSurParam & iPosition,
		      CATMathVector     & oDU3,
		      CATMathVector     & oDU2DV,
		      CATMathVector     & oDUDV2,
		      CATMathVector     & oDV3) const;
  CATMathDirection EvalNormal(const CATSurParam & Param2) const;
  void EvalNormal(const CATSurParam & iParam, CATMathDirection & oNormal) const;
  void Eval(const CATSurLimits & iBoxToEvaluate,
	    CATEvalCommand iCommand,
	    CATMathGridOfPoints  * iPointm,
	    CATMathGridOfVectors * iVectord1,
	    CATMathGridOfVectors * iVectord2) const;
  void EvalMultiple(const CATSurLimits      & iBox,
		    CATLONG32                      iCountPointsInU,
		    CATLONG32                      iCountPointsInV,
		    const CATSurEvalCommand & iCommand,
		    CATSurEvalResult        & oResult) const;
  void EvalLocal(const CATSurParam       & iParameter,
		 const CATSurEvalCommand & iCommand,
		 CATSurEvalLocal         & oResult) const;
  CATCurve *ExtractIsoParametricCurve(const CATIsoParameter iIsoParameter,
				      const CATSurParam & Param1,     
				      CATGeoFactory *Where ) const;
  CATBoolean IsClosedU() const;
  CATBoolean IsClosedV() const;

  void GetMappingU(CATMathTransformation1D &oTransfo1D) const;
  void GetMappingV(CATMathTransformation1D &oTransfo1D) const;

  short GetOrientation( ) const ;
  void SetOrientation( const short iNewOrientation );
  const CATKnotVector * GetKnotVectorU() const;
  const CATKnotVector * GetKnotVectorV() const;
  CATSurParam CreateParam(const double & paramU,
			  const double & paramV) const;
  CATSurParam CreateParam(const double & u, const CATLONG32 & iu,
			  const double & v, const CATLONG32 & iv) const;
  void CreateParam(const double & iParamU,
		   const double & iParamV,
		   CATSurParam & oResult) const;
  void CreateParam(const double & u, const CATLONG32 & iu,
		   const double & v, const CATLONG32 & iv,
		   CATSurParam & oResult) const;
  const CATSurParamReference * GetParamReference() const;
  void GetMaxLimits(CATSurLimits & oLimits) const ;
  void GetLimits(CATSurLimits & oLimits) const ;
  void GetStartLimit(CATSurParam & oParam) const ;
  void GetEndLimit(CATSurParam & oParam) const ;
  void GetInternalMaxLimits(const CATLONG32 iIndexU, 
			    const CATLONG32 iIndexV,
			    CATSurLimits & oLimits) const;
  void GetInternalLimits(const CATLONG32 iIndexU, 
			 const CATLONG32 iIndexV,
			 CATSurLimits & oLimits) const;
  CATSurParam GetStartLimit() const;
  CATSurParam GetEndLimit() const;
  CATSurLimits GetLimits() const;
  CATSurLimits GetMaxLimits() const;
  CATSurLimits GetInternalLimits(const CATLONG32 IndexU, const CATLONG32 IndexV) const;
  CATSurLimits GetInternalMaxLimits(const CATLONG32 IndexU, 
				    const CATLONG32 IndexV) const;
  void SetLimits(const CATSurLimits & iNewLimits) ;
  void GetNumberOfComponent( CATLONG32 & oUCount, CATLONG32 & oVCount) const;
  void Lock() ;
  void Unlock() ;
  void OpenEquation () const;
  void CloseEquation () const;
  void GetEquation(const CATLONG32 iIndexU, const CATLONG32 iIndexV,
		   const CATMathFunctionXY * & oFx,
		   const CATMathFunctionXY * & oFy,
		   const CATMathFunctionXY * & oFz) const;
  void GetGlobalEquation(const CATMathFunctionXY * & oFx,
			 const CATMathFunctionXY * & oFy,
			 const CATMathFunctionXY * & oFz) const;
  CATMathFunctionRN *GetImplicitEquation () const;
  CATMathCurve* GetMathCurve(const CATIsoParameter   iIsoParameter,
			     const CATSurParam     & iLocation  ) const ;
  CATBoolean HasMathCurve(const CATIsoParameter   iIsoParameter,
			  const CATSurParam     & iLocation ) const;
  void GetInternalBoundingBox(const CATLONG32 IndexU, 
			      const CATLONG32 IndexV,
			      CATMathBox & oBox) const;
  void GetInternalMaxBoundingBox(const CATLONG32 IndexU, 
				 const CATLONG32 IndexV,
				 CATMathBox & oBox) const;
  CATMathBox GetInternalBoundingBox(const CATLONG32 IndexU, 
				    const CATLONG32 IndexV) const;
  CATMathBox GetInternalMaxBoundingBox(const CATLONG32 IndexU, 
				       const CATLONG32 IndexV) const;
  void GetDirBox( CATMathDirBox & oDirBox ) const ;
  void GetInternalDirBox(const CATLONG32 IndexU, const CATLONG32 IndexV,
			 CATMathDirBox &oDirBox) const;
  CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
					     CATSurParam  & oIndex ) const ;
  CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
					     CATSurParam  & oIndex   ,
					 const CATSurLimits & iInside  ) const;
  CATSurface::CATSolutionDiagnostic GetParamOnIsopar( const CATMathPoint    & iPoint,
                                                      const CATIsoParameter & iIsoparam,
                                                      const CATSurParam     & iStart,
                                                      const CATSurParam     & iEnd,
                                                            double          & oLambdaOnIsopar) const ;
  CATBoolean Compare( const CATSurParam &iw1, const CATSurParam & iw2 ) const;
  CATMathSetOfLongs *GetNumberOfComponent() const;
  const CATSurface * GetGeometricRep() const;
  CATIsoParameter IsLinear() const;
  CATIsoParameter IsCircular() const;
  
  virtual CATBoolean HasImplicitEquation() const;
  CATSurface * CreateOffset(CATGeoFactory * iWhere,
			                      const CATLength & iOffset,
														const CATSurLimits & iLimits,
														CATMathTransformation2D * &oTransfo2D) const; 
  CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
			 CATMathTransformation2D* oTransfo2D = NULL) const;
  CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
			const CATSurface              * iTSurface,
			CATMathTransformation2D * oTransfo2D = NULL) const;
  virtual int GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &ioBox) const;
};

#endif
