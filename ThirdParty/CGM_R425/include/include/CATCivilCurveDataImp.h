//=======================================================================================//
// COPYRIGHT Dassault Systemes 2020/04/17
//=======================================================================================//
//                      CATCivilCurveDataImp                                             //
//=======================================================================================//
// Historic:
// 17/04/20 F4E : Creation
// 05/06/20 F4E : Add missing include
// 11/08/20 Q48 : Small file tidy (const / C++ key-words) etc
// 08/09/20 JSX : add data that was in CATCivilCurveData
// 07/01/21 Q48 : Add CGMReplay stream/unstream/dump
// 07/06/21 Q48 : Make Run protected to prevent reset of civil curve parameters
// 10/09/21 Q48 : Add compare methods for CGMReplay validation (migration from global Compare)
// 23/12/21 Q48 : Add copy constructor
// 23/12/21 Q48 : Force traces in Compare
//=======================================================================================//

#ifndef CATCivilCurveData_Imp_H
#define CATCivilCurveData_Imp_H

// Base class
#include "CATCivilCurveData.h"

// ExportedBy
#include "GeoAdvCurves.h"

// C++11
#include "CATGeoOpVirtual.h"

// System
#include "CATBoolean.h"

// Mathematics
#include "CATMathConstant.h"

// Advanced Mathemtics
#include "CATMathIdentifierMacros.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"

// Geometric Operators
#include "CATCivilCurveDefProtected.h"

// Special API
#include "CATSysErrorDef.h"

class CATSoftwareConfiguration;
class CATTolerance;
class CATCGMOutput;
class CATCGMStream;
class CATGeoODTScaleManager;
class CATCivilCurveComputeParam;

class ExportedByGeoAdvCurves CATCivilCurveDataImp : public CATCivilCurveData
{

public:

  CATCivilCurveDataImp(      CATSoftwareConfiguration * iConfig,
                       const CATTolerance             & iTol);

protected:

  CATCivilCurveDataImp(const CATCivilCurveDataImp & iToCopy);

public:

  virtual ~CATCivilCurveDataImp();

  DECLARE_SIMPLE_IDENTIFIER();

  virtual CATCivilCurveType GetCivilCurveType() const CATGEOOverride CATGEOFinal;

  virtual       CATSoftwareConfiguration * GetSoftwareConfiguration() const CATGEOFinal;
  virtual const CATTolerance             & GetToleranceObject() const CATGEOFinal;

protected:

  virtual CATCivilCurveDef::CheckParamValue Run() = 0; /*CATGEOOverride*/ // to compute class internal data when needed

  virtual void Reset() = 0; // to reset the internal computed data

private:

  void InitContext( CATSoftwareConfiguration * iConfig);

  //-----------------------------------------------------------------------
  //- Data storage class to ease streaming
  //-----------------------------------------------------------------------

public:

  class CATCivilCurveDataImpData
  {
  public:
    CATCivilCurveDataImpData(      CATSoftwareConfiguration * iConfig,
                             const CATTolerance             & iTol,
                             const CATGeoODTScaleManager    * iScaleManager);

    virtual ~CATCivilCurveDataImpData();

    CATSoftwareConfiguration* GetConfig() const;
    const CATTolerance & GetTol() const;

    const CATGeoODTScaleManager* GetScaleManager() const;

  private:
    CATSoftwareConfiguration * _Config;
    const CATTolerance & _TolObject;

    const CATGeoODTScaleManager* _ScaleManager;
  };
  
  //-----------------------------------------------------------------------
  //- CGM replay
  //-----------------------------------------------------------------------

public:
  
  virtual CATBoolean Compare(const CATCivilCurveDataImp * iRefData,
                                   CATCGMOutput         * iOS) const CATGEOFinal;

  virtual CATBoolean CompareInt(const CATCivilCurveDataImp * iRefData,
                                      CATCGMOutput         * iOS) const = 0;

public:

  static void Stream(const CATCivilCurveDataImp*, CATCGMStream & ioStream);

  static CATCivilCurveDataImp* UnStream(      CATCGMStream             & ioStream,
                                              CATSoftwareConfiguration * iConfig,
                                        const CATTolerance             & iTol,
                                        const CATGeoODTScaleManager    * iScaleManager);

  static void Dump(const CATCivilCurveDataImp * iData,
                         CATCGMOutput         & iOS);

protected:
  
  virtual void Stream(CATCGMStream & ioStream) const CATGEOFinal;
  virtual void StreamProtected(CATCGMStream & ioStream) const = 0;
  
  virtual void Dump(CATCGMOutput & iOS) const /*CATGEOOverride*/;
  
  //-----------------------------------------------------------------------
  //- Data
  //-----------------------------------------------------------------------

protected:

  CATCivilCurveComputeParam * _ParamComputer;
     
  // Tolerance
  const CATTolerance             & _Tol;
  const double                     _TolGeo;

  // Versioning
  CATSoftwareConfiguration * _Config;
  short                      _CGMLevel;
};
#endif
