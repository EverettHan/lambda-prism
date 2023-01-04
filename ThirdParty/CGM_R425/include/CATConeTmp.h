/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATConeTmp:
// Temporary implementation of CATCone interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATCONETMP_H
#define CATCONETMP_H

#include "YP00TMP.h"
#include "CATElementarySurfaceTmp.h"
#include "CATCone.h"
#include "CATMathTransformation.h"                        

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATConeTmp: public CATElementarySurfaceTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATConeTmp(const CATCone *iRefCone, const CATMathTransformation &iTransfo ) ;
  ~CATConeTmp() ;

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
  //- Implementations for CATCone interface
  //=========================================================================
  CATAngle          GetSemiAngle()  const;
  CATAngle          GetStartAngle() const;
  CATAngle          GetEndAngle()   const;

  void Set( const CATMathAxis      & iAxis,
	    const CATPositiveLength  iRadius,
	    const CATPositiveLength  iLength,
	    const CATAngle           iSemiAngle,
	    const CATAngle           iStart,
	    const CATAngle           iEnd  ) ; 
  
  void SetRadius   ( const CATPositiveLength iRadius)  ;
  void SetSemiAngle( const CATAngle iSemiAngle )       ;
  void SetLength   ( const CATPositiveLength iLength ) ;

  CATMathPoint      GetApex()         const;
  void    GetApex(CATMathPoint  & oPoint)         const;
  //-New methods
  CATAngle    GetConeAngle() const;
  CATLength   GetStartRadius() const;
  CATLength   GetStartRuleLength() const;
  CATLength   GetEndRuleLength() const;
  double      GetDilation() const;
  void        SetDilation(const double newDil);
  double      GetUScale() const;
  void        SetUScale(const double newUScale);
  void        SetVScale(const double iNewVScale);
  double      GetVShift() const;
  void        SetVShift(const double iNewVScale);
  CATLength   GetRadiusAtV(const double iVval);
  double      GetVScale() const;
  CATBoolean  IsInvariant(const CATMathTransformation & iTransfo,
			  CATMathTransformation2D* oTransfo2D = NULL) const;
  
  
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
  const CATCone *_RefCone;

};

#endif
