#ifndef CATPGMExtruded_h_
#define CATPGMExtruded_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATListOfInt.h"
#include "CATBoolean.h"

class CATCrvLimits;
class CATCrvParam;
class CATExtrudedInstance;
class CATGeometry;
class CATSetOfCrvParams;
class CATSurLimits;
class CATSurParam;
class CATPGMExtruder;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMExtruded: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMExtruded();

  /**
   * Destructor
   */
  virtual ~CATPGMExtruded();

  //-------------------------------------------------------------------------
  // GetResult() returns resulting composite geometry.
  // GetResult(Profile,Center,LinkWith) Returns sub-geometry generated from 
  // multiplication of a Sub-Geometry and 
  // a sub-geometry in the context of a previous extrusion.
  // Sub-Geometry is the one which is returned by CATCell::GetGeometryOn...
  //-------------------------------------------------------------------------
  virtual CATGeometry *GetResult(
    CATGeometry *iProfile = NULL,
    CATGeometry *iCenter = NULL,
    CATPGMExtruded *iLinkWith = NULL,
    CATGeometry *iGeom = NULL) = 0;

  //-------------------------------------------------------------------------
  virtual void GetCuttingParams(
    const CATSetOfCrvParams *&ioCuttingParams,
    CATListOfInt **ioSharpness) const = 0;

  //-------------------------------------------------------------------------
  // Surface: Returns TRUE whenever the normal of the generated surface 
  // could not be set to Profile ^ Center.
  // Curve: returns TRUE whenever the generated curve has a different
  // orientation from the input curve.
  // Must be called after GetResult() call.
  //-------------------------------------------------------------------------
  virtual CATBoolean IsOrientationChanged() const = 0;

  //-------------------------------------------------------------------------
  // Access to Extruder
  //-------------------------------------------------------------------------
  virtual CATPGMExtruder *GetExtruder() const = 0;

};

#endif /* CATPGMExtruded_h_ */
