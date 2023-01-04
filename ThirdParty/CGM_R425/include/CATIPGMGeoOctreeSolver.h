#ifndef CATIPGMGeoOctreeSolver_h_
#define CATIPGMGeoOctreeSolver_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATPGMGeoFace;
class CATLISTP_CATVoxel_;
class CATVoxel;
class CATBody;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMGeoOctreeSolver;

class ExportedByCATGMModelInterfaces CATIPGMGeoOctreeSolver: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMGeoOctreeSolver();

  virtual CATLONG32 CreateGeoFaces(CATPGMGeoFace **&ioGeoFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMGeoOctreeSolver(); // -> delete can't be called
};

ExportedByCATGMModelInterfaces CATIPGMGeoOctreeSolver *CATPGMCreateGeoOctreeSolver(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  CATBody *iBody);

#endif /* CATIPGMGeoOctreeSolver_h_ */
