#ifndef CATCompareTopoContext_h
#define CATCompareTopoContext_h

/**
* Class CATCompareTopoContext
*
* Tool to compare 2 topologies or 2 geometries.
* To use it:
*  - Create it via static method CATCompareTopoContext::Create
*  - Eventually use "Set..." methods to set the behavior
*  - Use method "CompareTopology" or "CompareGeometry" to compare 2 elements
*  - Use method "Release" to delete it
*
* >>>>>> CGMReplay RECORDING IS POSSIBLE <<<<<<
* To record CGMReplay files, use "CATCompareTopology" as operator name:
* each call to method "CompareTopology" will generate 1 CGMReplay file.
*/

#include "ExportedByCATTopologicalObjects.h"
#include "CATBaseUnknown.h"
#include "CATCompareTopologyOutcome.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class HashTableAssocList;
class CATCGMOutput;
class CATTopology;
class CATGeometry;
class CATCompareTopoContextImp;
class CATAdaptiveHashTable;
class CATListPtrCATTopology;

class ExportedByCATTopologicalObjects CATCompareTopoContext : public CATBaseUnknown
{
public:

  /**
   * @nodoc @nocgmitf
   * Destructor.
  */
  virtual ~CATCompareTopoContext();

  /**
   * @nodoc @nocgmitf
   * @return [out, CATBaseUnknown#Release]
  */
  static CATCompareTopoContext * Create(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig);

  /**
   * @nodoc @nocgmitf
  */
  virtual HashTableAssocList * CreateTableWithAllIdenticalDependencies(CATBoolean iWithTopologies = TRUE, CATBoolean iWithGeometries = TRUE) = 0;

  /**
  * @nodoc @nocgmitf
  */
  virtual void DiagnosticDump(CATCGMOutput &os) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual CATCompareTopologyOutcome CompareTopology(CATTopology * iTopology1, CATTopology * iTopology2) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual CATCompareTopologyOutcome CompareGeometry(CATGeometry * iGeometry1, CATGeometry * iGeometry2) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void SetDoGeometricalComputations(CATBoolean iDoGeometricalComputations) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void SetCheckRank(CATBoolean iCheckRank) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void SetConsiderAsSameIfFirstSupportIsSmaller(CATBoolean iConsiderAsSameIfFirstSupportIsSmaller) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void SetCheckPersistencyOfLyingOnOfFirstTopo(CATBoolean iCheckPersistencyOfLyingOnOfFirstTopo) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void SetIgnoreMacroPoints(CATBoolean iIgnoreMacroPoints) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void DefineUsefulPointsOfFirstTopologies(CATListPtrCATTopology & iFirstTopologies) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void DefineUsefulPointsOfFirstTopologies(CATTopology * iMainFirstTopology) = 0;

  /**
   * @nodoc @nocgmitf
  */
  virtual void SetUsefulPointsOfFirstTopologies(CATAdaptiveHashTable * iUsefulPointsOfFirstTopologies) = 0;

  /**
  * @nodoc @nocgmitf
  */
  virtual void SetDeepAnalysis(CATBoolean iDeepAnalysis) = 0;

  /**
  * @nodoc @nocgmitf
  */
  virtual CATCompareTopoContextImp * CastToImp() = 0;

protected:
  CATCompareTopoContext();

private:
  CATCompareTopoContext(const CATCompareTopoContext & iOther);
};

#endif


