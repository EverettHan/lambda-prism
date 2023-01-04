/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSphereTmp:
// Temporary implementation of CATSphere interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATSPHERETMP_H
#define CATSPHERETMP_H

#include "YP00TMP.h"
#include "CATElementarySurfaceTmp.h"
#include "CATSphere.h"
#include "CATMathTransformation.h"                        

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATSphereTmp: public CATElementarySurfaceTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATSphereTmp(const CATSphere *iRefSphere, 
	       const CATMathTransformation &iTransfo ) ;
  ~CATSphereTmp() ;

  int IsATypeOf(CATGeometricType TypeReference);

  //=========================================================================
  //- Overload for CATElementarySurface interface
  //=========================================================================
  CATMathAxis GetAxis() const;
  void GetAxis(CATMathAxis &Axis) const;
  void GetAxis(CATMathPoint  &oPoint  ,
	       CATMathVector &oVectorU,
	       CATMathVector &oVectorV,
	       CATMathVector &oVectorW) const;
  //=========================================================================
  //- Implementations for CATSphere interface
  //=========================================================================
  CATPositiveLength GetRadius()const;
  CATAngle GetMeridianStartAngle() const;
  CATAngle GetMeridianEndAngle() const;
  CATAngle GetParallelStartAngle() const;
  CATAngle GetParallelEndAngle() const;
  void Set(const CATMathAxis       &Axis,
		   const CATPositiveLength  Radius,
		   const CATAngle           MeridianStart,
		   const CATAngle           MeridianEnd, 
		   const CATAngle           ParallelStart,
		   const CATAngle           ParallelEnd); 
  void SetRadius(CATPositiveLength iRadius);

  //=========================================================================
  //- Acces aux donnees membres
  //=========================================================================
  CATGeometry * GetReference() const;
  CATMathTransformation GetMatrix() const;
  CATBoolean  IsInvariant(const CATMathTransformation & iTransfo,
			  CATMathTransformation2D* oTransfo2D = NULL) const;
  protected :

  //-------------------------------------------------------------------------
  // Protected data
  //-------------------------------------------------------------------------
  CATMathTransformation _Transfo;
  const CATSphere *_RefSphere;

};

#endif




















