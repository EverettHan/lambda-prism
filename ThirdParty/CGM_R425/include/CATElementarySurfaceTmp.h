/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATElementarySurfaceTmp:
// Temporary implementation of CATElementarySurface interface 
// for Assembly Design
//
//=============================================================================
// Oct. 97   Creation   
//=============================================================================
#ifndef CATELEMENTARYSURFACETMP_H
#define CATELEMENTARYSURFACETMP_H

#include "YP00TMP.h"
#include "CATSurfaceTmp.h"
#include "CATElementarySurface.h"

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATElementarySurfaceTmp: public CATSurfaceTmp
{
  public :

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATElementarySurfaceTmp() ;
  ~CATElementarySurfaceTmp() ;

  //=========================================================================
  //- Implementations for CATElementarySurface interface
  //=========================================================================
  CATMathAxis GetAxis()const;
  virtual void GetAxis(CATMathAxis &Axis) const = 0;
  void SetOrigin(const CATMathPoint & iPoint);
  virtual void GetAxis(CATMathPoint  &oPoint  ,
		       CATMathVector &oVectorU,
		       CATMathVector &oVectorV,
		       CATMathVector &oVectorW) const=0;
  
};

#endif




















