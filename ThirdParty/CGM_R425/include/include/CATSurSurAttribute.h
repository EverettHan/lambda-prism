/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATSurSurAttribute
//   this class is an attribute used by the Surface surface intersection 
//   operator to improve the performances. It consists in saving data on a given
//   surface (with a given surlimits) to avoid a recomputation while intersecting a new
//   time with this surface.
//=============================================================================
// Oct. 99   Creation                                     XGN
//=============================================================================
#ifndef CATSurSurAttribute_H
#define CATSurSurAttribute_H

#include "Y30C3XGG.h"
#include "CATCGMAttribute.h"

#include "CATSurLimits.h"
class CATSurface;
class CATCurve;
class CATGeoFactory;

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATSurSurAttribute : public CATCGMAttribute
{
  CATCGMDeclareAttribute(CATSurSurAttribute, CATCGMAttribute);
  public :
  CATSurSurAttribute();
  CATSurSurAttribute(CATGeoFactory * iFactory,
                     CATSurface * iSurface, const CATSurLimits & iSurLim);
  virtual ~CATSurSurAttribute();
  
  void SetIsopars(CATCurve * iIsopar[4]);

  void GetIsopars(CATCurve * oIsopar[4]);

  protected :
  CATGeoFactory * _Factory;
  CATSurface * _Surf;
  CATSurLimits _SurLim;
  
  // Isopar
  CATCurve * _Isopar[4];
};


#endif
