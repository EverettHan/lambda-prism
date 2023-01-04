#ifndef CATMakePointStep_H
#define CATMakePointStep_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATCGAreport_Measures.h"
#include "CATGeoAbendInfo.h"


typedef struct sCATMakePointStep
{
  INLINE sCATMakePointStep() 
    : _CATIPerformanceUsage(FALSE),  _nbMeasures(0)
    , _CPU(0.0), _Elapsed(0.0), _WorkingSetDelta(0.0)
    , _DiskBytes(0), _Ticks(0) , _SoftLevel(0) , _BSFLevel(  (CATULONG64)  CATGeoAbendInfo::_SoftLevel._CGMBSF  )
    , _NumberOfGeometries(0), _NumberOfGeoRun(0), _NumberOfGeoErrors(0)
  { _Depth[0] =  _Depth[1] =0; }


  INLINE sCATMakePointStep(const char* ObjectName, CATBoolean iCATIPerformanceUsage,
    int nbMeasures, 
    double  CPU, double  Elapsed, double  WorkingSet, CATULONG64 Ticks, CATULONG64 Disk, double RSD[report_PCS_NbMeasures],
    const CATUnicodeString  & iScenarioName,
    CATULONG64 iNumberOfGeometries, CATULONG64 iNumberOfGeoRun, CATULONG64 iNumberOfGeoErrors, CATULONG64 iSoftLevel, CATLONG64 iDepths[2])  
    : _ObjectName(ObjectName?ObjectName:""), _CATIPerformanceUsage(iCATIPerformanceUsage)
    , _nbMeasures(nbMeasures) , _SoftLevel(iSoftLevel)  , _BSFLevel(  (CATULONG64)  CATGeoAbendInfo::_SoftLevel._CGMBSF  )
    , _CPU(CPU), _Elapsed(Elapsed), _WorkingSetDelta(WorkingSet) , _DiskBytes(Disk), _Ticks(Ticks) 
    , _ScenarioName(iScenarioName) 
    , _NumberOfGeometries(iNumberOfGeometries), _NumberOfGeoRun(iNumberOfGeoRun), _NumberOfGeoErrors(iNumberOfGeoErrors)
  {     _Depth[0] = iDepths[0];   _Depth[1] = iDepths[1];  memcpy(_RSD,RSD,report_PCS_NbMeasures*sizeof(double)); }


  INLINE sCATMakePointStep(const struct sCATMakePointStep &iOther)
    : _CATIPerformanceUsage(FALSE)
    ,  _nbMeasures(0),   _SoftLevel(0) , _BSFLevel(0)
    , _CPU(0.0), _Elapsed(0.0), _WorkingSetDelta(0.0)
    , _DiskBytes(0), _Ticks(0) 
    , _NumberOfGeometries(0), _NumberOfGeoRun(0), _NumberOfGeoErrors(0)
  {
    _ObjectName = iOther._ObjectName;
    _CATIPerformanceUsage = iOther._CATIPerformanceUsage;
    _nbMeasures = iOther._nbMeasures;
    _Depth[0] = iOther._Depth[0];
    _Depth[1] = iOther._Depth[1];
    _CPU = iOther._CPU;
    _Elapsed = iOther._Elapsed;
    _WorkingSetDelta = iOther._WorkingSetDelta;
    _DiskBytes = iOther._DiskBytes;
    _Ticks = iOther._Ticks;
    _ScenarioName = iOther._ScenarioName;
    _NumberOfGeometries = iOther._NumberOfGeometries;
    _NumberOfGeoRun = iOther._NumberOfGeoRun;
    _NumberOfGeoErrors = iOther._NumberOfGeoErrors;
    _SoftLevel = iOther._SoftLevel;
    _BSFLevel = iOther._BSFLevel;
    memcpy(_RSD, iOther._RSD, report_PCS_NbMeasures * sizeof(double) ); 
  }


  INLINE sCATMakePointStep&  operator=(const struct sCATMakePointStep &iOther)
  {
    if (&iOther == this)  return *this;

    _ObjectName = iOther._ObjectName;
    _CATIPerformanceUsage = iOther._CATIPerformanceUsage;

    _nbMeasures = iOther._nbMeasures;
    _Depth[0] = iOther._Depth[0];
    _Depth[1] = iOther._Depth[1];
    _CPU = iOther._CPU;
    _Elapsed = iOther._Elapsed;
    _WorkingSetDelta = iOther._WorkingSetDelta;
    _DiskBytes = iOther._DiskBytes;
    _Ticks = iOther._Ticks;
    _ScenarioName = iOther._ScenarioName;
    _NumberOfGeometries = iOther._NumberOfGeometries;
    _NumberOfGeoRun = iOther._NumberOfGeoRun;
    _NumberOfGeoErrors = iOther._NumberOfGeoErrors;
    _SoftLevel = iOther._SoftLevel;
    _BSFLevel = iOther._BSFLevel;

     memcpy(_RSD, iOther._RSD, report_PCS_NbMeasures * sizeof(double) );  

    return *this;
  }

    // Adding Measure
  INLINE void   AddMeasure(const struct sCATMakePointStep &iOther)
  {
    _nbMeasures += iOther._nbMeasures;

    _CPU += iOther._CPU;
    _Elapsed += iOther._Elapsed;
    _WorkingSetDelta += iOther._WorkingSetDelta;
    _DiskBytes += iOther._DiskBytes;
    _Ticks += iOther._Ticks;
    _NumberOfGeometries += iOther._NumberOfGeometries;
    _NumberOfGeoRun += iOther._NumberOfGeoRun;
    _NumberOfGeoErrors += iOther._NumberOfGeoErrors;

    _Depth[0] += iOther._Depth[0];
    _Depth[1] += iOther._Depth[1];
    _SoftLevel += iOther._SoftLevel;
    _BSFLevel = iOther._BSFLevel;
  }



  CATUnicodeString    _ObjectName;
  CATUnicodeString    _ScenarioName;

  int                 _nbMeasures;
  CATLONG64           _Depth[2];

  double              _CPU;
  double              _Elapsed;
  double              _WorkingSetDelta;
  double              _RSD[report_PCS_NbMeasures];

  CATULONG64          _Ticks;
  CATULONG64          _DiskBytes;
  CATULONG64          _NumberOfGeometries;
  CATULONG64          _NumberOfGeoRun;
  CATULONG64          _NumberOfGeoErrors;
  CATULONG64          _SoftLevel;
  CATULONG64          _BSFLevel;
 
  CATBoolean          _CATIPerformanceUsage;
} 
CATMakePointStep;


#endif
