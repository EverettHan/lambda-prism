#ifndef CATCurveImpl_h
#define CATCurveImpl_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 *  Default implementation for CATCurve Interface
 */

#include "CATGeometryImpl.h"
#include "CATCurve.h"
class CATMathTransformation1D;

class ExportedByYP00IMPL CATCurveImpl : public CATGeometryImpl
{
public:
  CATDeclareClass;
  CATCurveImpl();
  virtual ~CATCurveImpl();

  // Interface CATCurve
  //-----------------------------------------------------------------------------
  virtual CATMathPoint  EvalPoint(const CATCrvParam & iParam) const ;
  virtual CATMathVector EvalFirstDeriv(const CATCrvParam & iParam) const ;
  virtual CATMathVector EvalSecondDeriv(const CATCrvParam & iParam) const ;
  virtual CATMathVector EvalThirdDeriv(const CATCrvParam & iParam) const ;
  virtual void          Eval(const CATCrvLimits & box,
		             CATEvalCommand command,
		             CATMathSetOfPoints *& point,
		             CATMathSetOfVectors *& dw,
		             CATMathSetOfVectors *& dw2) const ;
  virtual CATCrvParam   CreateParam(const double & iGlobalParam) const ;
  virtual CATCrvParam   CreateParam(const double & iLocal, const CATLONG32 & iArc) const ;

  virtual const CATCrvParamReference * GetParamReference() const ;
  virtual CATLONG32                         GetNumberOfComponent() const ;
  virtual const CATKnotVector *        GetKnotVector() const ;
  virtual CATCrvLimits                 GetLimits() const ;
  virtual CATCrvLimits                 GetMaxLimits() const  ;
  virtual CATCrvLimits                 GetInternalMaxLimits(const CATLONG32 iArc) const ;
  virtual CATCrvLimits                 GetInternalLimits(const CATLONG32 iArc) const ;
  virtual CATCrvParam                  GetStartLimit() const ;
  virtual CATCrvParam                  GetEndLimit() const ;
	virtual double GetNaturalParamFromParam(const CATCrvParam &iParam) const;
	virtual void GetParamFromNaturalParam(double iNatural, CATCrvParam &oParam) const;

  virtual void SetLimits(const CATCrvLimits & iLimits);
  virtual void Lock() ;
  virtual void Unlock() ;
  virtual void OpenEquation () const;
  virtual void CloseEquation () const;
  virtual void GetEquation(const CATLONG32 iArc,
			   const CATMathFunctionX * & oFx,
			   const CATMathFunctionX * & oFy,
			   const CATMathFunctionX * & oFz) const;
  virtual void GetGlobalEquation(const CATMathFunctionX * & oFx,
				 const CATMathFunctionX * & oFy,
				 const CATMathFunctionX * & oFz) const;
  
  virtual CATBoolean    IsClosed() const;
  virtual CATMathBox    GetInternalMaxBoundingBox(const CATLONG32 iArc) const ;
  virtual CATMathBox    GetInternalBoundingBox(const CATLONG32 iArc) const ;
  virtual CATMathCurve* GetMathCurve() const ;
  virtual CATBoolean    HasMathCurve() const  ;
  virtual const CATCurve *                GetGeometricRep(CATCrvLimits & oRepLimits,
					                  short & oRepOrientation) const ;
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
						         CATCrvParam  & oParam) const ;
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
		          		       	         CATCrvParam  & oParam   ,
						   const CATCrvLimits & iInside  ) const ;
  virtual CATCurve::CATProjectionDiagnostic 
  CreateProjection(CATPlane* iOn, CATPCurve* & oProjection, 
		   CATSetOfCrvParams* iIndexOnCurve=NULL,CATSetOfCrvParams* ioIndexOnPCurve=NULL) const;
  virtual CATBoolean IsContaining ( const CATCurve* iOther ) const ;

  virtual CATGeometry* GetOwner ( ) const ;
  virtual void GetBox( const CATCrvLimits & iLimits, CATMathBox & oBox ) const ;
  virtual CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
			         CATMathTransformation1D* oTransfo1D = NULL) const;
  CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
			            const CATCurve                * iTCurve,
			                  CATMathTransformation1D * iTransfo1D ) const ;

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
  void CreateParam(const double iGlobalParam, CATCrvParam & oParam) const ;
  void CreateParam(const double iLocal, const CATLONG32 iArc, CATCrvParam & oParam) const ;
  void GetStartLimit(CATCrvParam & oStartParam) const ;
  void GetEndLimit(CATCrvParam & oEndParam) const ;
  void GetLimits(CATCrvLimits & oCurrentLimits) const;
  void GetMaxLimits(CATCrvLimits & oMaxLimits) const ;
  void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & oInternalMaxLimits) const ;
  void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & oInternalMaxLimits) const;
  void GetInternalMaxBoundingBox(const CATLONG32 iArc, CATMathBox & oBox) const  ;
  void GetInternalBoundingBox(const CATLONG32 iArc, CATMathBox & oBox) const ;
  virtual int GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &ioBox) const;
};

#endif
