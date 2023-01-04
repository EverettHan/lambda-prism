/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATPlaneTmp:
// Temporary implementation of CATPlane interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATPlaneTmp_H
#define CATPlaneTmp_H

#include "YP00TMP.h"
#include "CATPlane.h"
#include "CATMathTransformation.h"                        
#include "CATSurfaceTmp.h"

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATPlaneTmp: public CATSurfaceTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATPlaneTmp(const CATPlane *iPlane, const CATMathTransformation &iTransfo ) ;
  ~CATPlaneTmp() ;

  int IsATypeOf(CATGeometricType TypeReference);

  //===========================================================================
  //- Implementations for CATSurface interface
  //===========================================================================
  CATMathPoint EvalPoint(const CATSurParam & iPosition) const;
  void EvalPoint(const CATSurParam & iPosition, CATMathPoint & oPoint) const;
  CATSurParam GetStartLimit() const;
  CATSurParam GetEndLimit() const;
  CATSurLimits GetLimits() const;
  void GetStartLimit(CATSurParam & oStartLimit) const;
  void GetEndLimit(CATSurParam & oEndLimit) const;
  void GetLimits(CATSurLimits & oLimits) const;
  const CATSurParamReference * GetParamReference() const;
  CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
					     CATSurParam  & oIndex ) const ;
  CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
					     CATSurParam  & oIndex   ,
					 const CATSurLimits & iInside  ) const;

  //=========================================================================
  //- Implementations for CATPlane interface
  //=========================================================================
  CATMathPlane GetAxis() const;
  void SetAxis(const CATMathPlane &Plane);
  void GetAxis(CATMathPlane &oMathPlane) const;
  
  void GetAxis(CATMathPoint       &oPoint,
		       CATMathDirection &oDirU ,
		       CATMathDirection &oDirV ) const;
  
  void GetNormal(CATMathPoint     &oPoint ,
			 CATMathVector &oNormal) const;

  //=========================================================================
  //- Acces aux donnees membres
  //=========================================================================
  CATGeometry * GetReference() const;
  CATMathTransformation GetMatrix() const;

  protected :

  //-------------------------------------------------------------------------
  // Protected data
  //-------------------------------------------------------------------------
  CATMathTransformation _Transfo;
  const CATPlane *_RefPlane;

};

#endif




















