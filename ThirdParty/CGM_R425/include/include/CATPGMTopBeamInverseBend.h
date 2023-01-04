#ifndef CATPGMTopBeamInverseBend_h_
#define CATPGMTopBeamInverseBend_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"

class CATBody;
class CATGeoFactory;
class CATMathPoint;
class CATMathVector;
class CATPlane;
class CATSoftwareConfiguration;
class CATWire;

class ExportedByCATGMOperatorsInterfaces CATPGMTopBeamInverseBend
{
public:
  /**
   * Constructor
   */
  CATPGMTopBeamInverseBend();

  /**
   * Destructor
   */
  virtual ~CATPGMTopBeamInverseBend();

  //------------------------------------------------------------------------------
  // Get Number of Lines
  //------------------------------------------------------------------------------
  virtual int GetNumberOfLines() = 0;

  //------------------------------------------------------------------------------
  // Get One Line
  // UV are parameters on iBeamSupportPlane
  // 1 <= iPointIndex <= LinesNumber
  //------------------------------------------------------------------------------
  virtual void GetLine(
    const int iPointIndex,
    double &UStart,
    double &VStart,
    double &UEnd,
    double &VEnd) = 0;

  //------------------------------------------------------------------------------
  // Find Out Beam SupportPlane from Beam Wire
  //------------------------------------------------------------------------------
  static CATPlane *FindOutBeamSupportPlane(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBeamWire);

};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATPGMTopBeamInverseBend *CATPGMCreateTopBeamInverseBend(
  CATGeoFactory *iWorkingFactory,
  CATSoftwareConfiguration *iConfig,
  CATBody *iBeamWire,
  CATPlane *iBeamSupportPlane,
  const CATLength iBeamThicknesses[2],
  const CATPositiveLength iMaxLineLength,
  const CATPositiveLength iLineOverlap);

#endif /* CATPGMTopBeamInverseBend_h_ */
