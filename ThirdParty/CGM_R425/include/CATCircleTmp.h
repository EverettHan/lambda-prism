/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCircleTmp:
// Temporary implementation of CATCircle interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATCircleTMP_H
#define CATCircleTMP_H

#include "YP00TMP.h"
#include "CATCircle.h"
#include "CATMathTransformation.h"                        
#include "CATGeometryTmp.h"
#include "CATCurve.h"
class CATSetOfCrvParams;
//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATCircleTmp: public CATGeometryTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATCircleTmp(const CATCircle *iCircle, 
	     const CATMathTransformation &iTransfo ) ;
  ~CATCircleTmp() ;

  int IsATypeOf(CATGeometricType TypeReference);

  //=========================================================================
  //- Implementations for CATCurve interface
  //=========================================================================
  CATMathPoint EvalPoint(const CATCrvParam & param) const;
  CATMathVector EvalFirstDeriv(const CATCrvParam & param) const;
  CATMathVector EvalSecondDeriv(const CATCrvParam & param) const;
  CATMathVector EvalThirdDeriv(const CATCrvParam & param) const;
  void Eval(const CATCrvParam       & iPoint,
		    const CATCrvEvalCommand & iCommand,
		    CATCrvEvalLocal         & oResult) const ;

  void Eval(const CATCrvLimits      & iDomainToEvaluate,
		    const CATLONG32                iNbOfPoints,
		    const CATCrvEvalCommand & iCommand,
		    CATCrvEvalResult        & oResult) const ;

  void Eval(const CATCrvParam & iParam,
		    const CATCrvEvalCommand & iCommand,
		    CATMathPoint* oPoint,
		    CATMathVector* oFirstDeriv,
		    CATMathVector* oSecondDeriv,
		    CATMathVector* oThirdDeriv) const ;
  void Eval(const CATCrvLimits & box,
		    CATEvalCommand command,
		    CATMathSetOfPoints *& point,
		    CATMathSetOfVectors *& dw,
		    CATMathSetOfVectors *& dw2) const;
  void CreateParam(const double iGlobalParam, CATCrvParam & oParam) const ;
  void CreateParam(const double iLocal, const CATLONG32 iArc, CATCrvParam & oParam) const ;
  CATCrvParam CreateParam(const double & param) const;
  CATCrvParam CreateParam(const double & w, const CATLONG32 & iarc) const;
  const CATCrvParamReference * GetParamReference() const;
  CATLONG32 GetNumberOfComponent() const;
  const CATKnotVector * GetKnotVector() const;
  void GetStartLimit(CATCrvParam & oStartParam) const ;
  void GetEndLimit(CATCrvParam & oEndParam) const ;
  CATCrvParam GetStartLimit() const;
  CATCrvParam GetEndLimit() const;
  void GetLimits(CATCrvLimits & oCurrentLimits) const;
  CATCrvLimits GetLimits() const;
  void SetLimits(const CATCrvLimits & box);
  void Lock() ;
  void Unlock() ;
  void OpenEquation () const;
  void CloseEquation () const;
  void GetEquation(const CATLONG32 iInternal,
		   const CATMathFunctionX * & oFx,
		   const CATMathFunctionX * & oFy,
		   const CATMathFunctionX * & oFz) const;
  void GetGlobalEquation(const CATMathFunctionX * & oFx,
			 const CATMathFunctionX * & oFy,
			 const CATMathFunctionX * & oFz) const;
  CATBoolean IsClosed() const;
  void GetMaxLimits(CATCrvLimits & oMaxLimits) const ;
  CATCrvLimits GetMaxLimits() const ;
  void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & oInternalMaxLimits) const ;
  void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & oInternalMaxLimits) const;
  CATCrvLimits GetInternalMaxLimits(const CATLONG32 Internal) const;
  CATCrvLimits GetInternalLimits(const CATLONG32 Internal) const;
  void GetInternalMaxBoundingBox(const CATLONG32 iArc, CATMathBox & oBox) const  ;
  void GetInternalBoundingBox(const CATLONG32 iArc, CATMathBox & oBox) const ;
  CATMathBox GetInternalBoundingBox(const CATLONG32 iInternal) const ;
  CATMathBox GetInternalMaxBoundingBox(const CATLONG32 iInternal) const ;
  CATMathCurve* GetMathCurve() const ;
  CATBoolean HasMathCurve() const ;
  void GetBox( const CATCrvLimits & iLimits, CATMathBox & oBox ) const ;
  CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
			 CATMathTransformation1D* oTransfo1D = NULL) const;
  CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
			            const CATCurve                * iTCurve,
			                  CATMathTransformation1D * iTransfo1D ) const ;
  CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
					   CATCrvParam  & oIndex ) const ;
  CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
					   CATCrvParam  & oIndex   ,
					   const CATCrvLimits & iInside) const;
  CATGeometry* GetOwner ( ) const ;
	virtual double GetNaturalParamFromParam(const CATCrvParam &iParam) const;
	virtual void GetParamFromNaturalParam(double iNatural, CATCrvParam &oParam) const;
  virtual int GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &ioBox) const;


  //=========================================================================
  //- Implementations for CATConic interface
  //=========================================================================
  CATMathPlane GetAxis() const;
  void GetSupport(CATMathPlane &oSupport)const;
  double GetEccentricity()const;
  CATMathPoint GetOrigin()const;
  void GetOrigin(CATMathPoint &oPoint)const;
  void SetOrigin(const CATMathPoint & iNewOrigin);

  //=========================================================================
  //- Implementations for CATCircle interface
  //=========================================================================
  CATPositiveLength GetRadius()const;
  CATAngle GetStartAngle() const;
  CATAngle GetEndAngle() const;
  void Set (const CATPositiveLength   iRadius, 
		    const CATMathPlane      & iBackgroundPlane,
		    const CATAngle            iStart,
		    const CATAngle            iEnd              ); 
  void SetRadius(CATPositiveLength iNewRadius);


  //=========================================================================
  //- Implementations for CATCircle interface
  //=========================================================================
  virtual const CATCurve * GetGeometricRep(CATCrvLimits & oRepLimits,
				   short & oRepOrientation) const;
  virtual CATBoolean IsContaining ( const CATCurve* iContained ) const;


  //=========================================================================
  //- Acces aux donnees membres
  //=========================================================================
  CATGeometry * GetReference() const;
  CATMathTransformation GetMatrix() const;
  //-
  CATCurve::CATProjectionDiagnostic 
    CreateProjection(CATPlane* iOn, CATPCurve* & oProjection, 
		     CATSetOfCrvParams* iIndexOnCurve=NULL,
		     CATSetOfCrvParams* ioIndexOnPCurve=NULL) const;
  protected :

  //-------------------------------------------------------------------------
  // Protected data
  //-------------------------------------------------------------------------
  CATMathTransformation _Transfo;
  const CATCircle *_RefCircle;

};

#endif
