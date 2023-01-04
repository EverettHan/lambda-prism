/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATLineTmp:
// Temporary implementation of CATLine interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATLINETMP_H
#define CATLINETMP_H

#include "YP00TMP.h"
#include "CATLine.h"
#include "CATMathTransformation.h"                        
#include "CATGeometryTmp.h"
#include "CATCurve.h"
class CATSetOfCrvParams;
//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATLineTmp: public CATGeometryTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATLineTmp(const CATLine *iLine, 
	     const CATMathTransformation &iTransfo ) ;
  ~CATLineTmp() ;

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
			 CATMathTransformation1D* oTransfo1D ) const;
  CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
			            const CATCurve                * iTCurve,
			                  CATMathTransformation1D * iTransfo1D = NULL) const ;
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
  //- Implementations for CATLine interface
  //=========================================================================
  CATMathPoint GetOrigin() const;
  void GetOrigin(CATMathPoint &oOrigin) const;
  CATMathDirection GetDirection() const;
  void GetDirection(CATMathDirection &oDirection) const;
  void SetOrigin(const CATMathPoint &Origin);
  void SetDirection(const CATMathDirection &Direction);
  void Set( const CATMathPoint & iSegmentLimit1, const CATMathPoint & iSegmentLimit2 ); 

  void Set( const CATMathPoint & iOrigin, const CATMathDirection & iDirection);
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
		     CATSetOfCrvParams* iIndexOnCurve=NULL,CATSetOfCrvParams* ioIndexOnPCurve=NULL) const;
  protected :

  //-------------------------------------------------------------------------
  // Protected data
  //-------------------------------------------------------------------------
  CATMathTransformation _Transfo;
  const CATLine *_RefLine;

};

#endif
