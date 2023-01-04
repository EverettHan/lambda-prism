#ifndef CATPGMGeoBox_h_
#define CATPGMGeoBox_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATMathLine.h"
#include "CATMathBox.h"
#include "CATCollec.h"


class CATMathCombinationXY;
class CATMathSystemXYc;
class CATMathSetOfPointsND;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPGMGeoFace;

class ExportedByCATGMModelInterfaces CATPGMGeoBox
{
public:
  /**
   * Constructor
   */
  CATPGMGeoBox();

  /**
   * Destructor
   */
  virtual ~CATPGMGeoBox();

  virtual CATPGMGeoBox **Subdivide() = 0;

  virtual void Intersect(CATMathSetOfPointsND **&ioIntPoints) = 0;

  virtual void Intersect(const CATMathLine &iLine, CATMathSetOfPointsND *&ioIntPoints) = 0;

};

ExportedByCATGMModelInterfaces CATPGMGeoBox *CATPGMCreateGeoBox(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  const CATMathBox &iBox,
  CATPGMGeoFace **iGeoFaces,
  CATLONG32 iNbFaces);

#endif /* CATPGMGeoBox_h_ */
