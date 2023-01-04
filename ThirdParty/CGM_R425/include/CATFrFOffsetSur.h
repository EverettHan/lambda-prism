/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998 
//==========================================================================
//
// CATFrFOffsetSur:
// Interface class of CATFrFOffsetSurface Object.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// August 98     Creation                       NDN
//========================================================================== 

#ifndef CATFrFOffsetSur_H
#define CATFrFOffsetSur_H

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"

class CATSurface;
class CATNurbsSurface;
class CATGeoFactory;
class CATSurLimits;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFOffsetSur  : public CATCGMVirtual
{
  public :

  virtual ~CATFrFOffsetSur();

  virtual void Run() =0;

//-------------------------------------------------------------
//GET Methods
//-------------------------------------------------------------
//Getting the result surface
  virtual CATNurbsSurface * GetOffsetSurface() =0;

//Getting the max error between real and result offset
  virtual double GetMaxDeviation() =0;

//Getting the real delta degree
//  virtual CATLONG32 GetDeltaDegree() =0;

//-------------------------------------------------------------
//SET Methods - In order to call this method, you should create
//this operator with an ADVANCED CATSkillValue, make your Set
//and then call the Run method.
//-------------------------------------------------------------
//If you want to set the max degree allowed
  virtual void SetMaxDegree(CATLONG32 MaxDegreeU,CATLONG32 MaxDegreeV) =0;

//If you want to set the offset law
  virtual void SetOffsetValues(const double iOffsetLaw[]) =0;

//If you want to set the input tolerance
  virtual void SetTolerance(double iTolerance) =0;

//If you want to set the limits to be used on surface.
  virtual void SetLimits(const CATSurLimits & iLimits) =0;

  //If you want to activate fast computation mode
  virtual void SetNewComputation(CATBoolean iMode=TRUE) =0;

  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig) =0;

};

//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces  CATFrFOffsetSur * CreateFrFOffsetSur(CATGeoFactory * Factory,
								  const CATSurface * iSurface,
								  const double iOffsetLength,
								  const double iTol,
								  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces  CATFrFOffsetSur * CreateFrFOffsetSur(CATGeoFactory * Factory,
								  const CATSurface * iSurface,
								  const double iOffsetLaw[],
								  const double iTol,
								  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces  CATFrFOffsetSur * CreateFrFOffsetSur(CATGeoFactory * Factory,
								  const CATSurface * iSurface,
								  const double iOffsetLength,
								  const double iTol,
								  const CATLONG32   iKeepKnots ,
								  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces  CATFrFOffsetSur * CreateFrFOffsetSur(CATGeoFactory * Factory,
								  const CATSurface * iSurface,
								  const double iOffsetLaw[],
								  const double iTol,
								  const CATLONG32   iKeepKnots ,
								  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces void Remove(CATFrFOffsetSur *&iFrFOffsetSur);

#endif
