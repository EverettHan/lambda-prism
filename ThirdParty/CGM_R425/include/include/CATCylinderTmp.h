/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCylinderTmp:
// Temporary implementation of CATCylinder interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation
// Jan. 05 Suppression CATIAV5R13 et CATIAV5R14                           HCN   
//=============================================================================
#ifndef CATCYLINDERTMP_H
#define CATCYLINDERTMP_H

#include "YP00TMP.h"
#include "CATElementarySurfaceTmp.h"
#include "CATCylinder.h"
#include "CATMathTransformation.h"                        

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATCylinderTmp: public CATElementarySurfaceTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATCylinderTmp(const CATCylinder *iRefCylinder,
		 const CATMathTransformation &iTransfo ) ;
  ~CATCylinderTmp() ;

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
  //- Implementations for CATCylinder interface
  //=========================================================================
  CATPositiveLength GetRadius()const;
  CATLength GetStartLength()const;
  CATLength GetEndLength()const;
  CATAngle GetStartAngle()const;
  CATAngle GetEndAngle()const;
  void SetRadius(CATPositiveLength iRadius);
  void SetLength(CATLength iStartLength, CATLength iEndLength);
  void SetAngle(CATAngle iStartAngle, CATAngle iEndAngle);

// OAU MicroFillet
  void GetCylinderParam(double & iUnitU,double & iMinParam,double & iStartParam,double & iEndParam);
  void SetCylinderParam(double iUnitU,double iMinParam,double iStartParam,double iEndParam);

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
  const CATCylinder *_RefCylinder;

};

#endif




















