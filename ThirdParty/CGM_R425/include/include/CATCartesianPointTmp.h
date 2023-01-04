/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCartesianPointTmp:
// Temporary implementation of CATCartesianPoint interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATCARTESIANPOINTTMP_H
#define CATCARTESIANPOINTTMP_H

#include "YP00TMP.h"
#include "CATCartesianPoint.h"
#include "CATMathTransformation.h"                        
#include "CATGeometryTmp.h"

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATCartesianPointTmp: public CATGeometryTmp
{
  public :

  CATDeclareKindOf;

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATCartesianPointTmp(const CATPoint *iPoint, 
		       const CATMathTransformation &iTransfo ) ;
  ~CATCartesianPointTmp() ;

  int IsATypeOf(CATGeometricType TypeReference);

  //=========================================================================
  //- Implementations for CATPoint interface
  //=========================================================================
  void GetCoord(CATLength & oXCoord,
			CATLength & oYCoord,
			CATLength & oZCoord ) const;
  CATLength GetX() const;
  CATLength GetY() const;
  CATLength GetZ() const;
  CATMathPoint GetMathPoint() const;
  void GetMathPoint(CATMathPoint & oPoint) const;

  //=========================================================================
  //- Implementations for CATCartesianPoint interface
  //=========================================================================
  void SetCoord(CATLength iXCoord,
			CATLength iYCoord,
			CATLength iZCoord);
  void SetX(CATLength iXCoord);
  void SetY(CATLength iYCoord);
  void SetZ(CATLength iZCoord);

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
  const CATPoint *_RefPoint;

};

#endif




















