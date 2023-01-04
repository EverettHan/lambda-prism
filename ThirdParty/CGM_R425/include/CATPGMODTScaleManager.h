#ifndef CATPGMODTScaleManager_h_
#define CATPGMODTScaleManager_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"

class CATError;
class CATGeoFactory;
class CATICGMObject;
class CATTransfoManager;
class CATMathTransformation;

//
class ExportedByCATGMModelInterfaces CATPGMODTScaleManager
{
public:
  /**
   * Constructor
   */
  CATPGMODTScaleManager();

  /**
   * Destructor
   */
  virtual ~CATPGMODTScaleManager();

  // Initialize input factory
  virtual void SetFactory(CATGeoFactory *iFactory) = 0;

  // Access to transfomanager
  virtual CATTransfoManager *GetTransfoManager() = 0;

  // Access to transfomanager
  virtual HRESULT GetMathTransformation(CATMathTransformation &oMathTransfo) = 0;

  // Apply scale to elements
  virtual int ApplyScale(CATError *&oError) = 0;

  // Read output factory
  virtual CATGeoFactory *GetScaledFactory() = 0;

  // Read scale ratio
  virtual double GetScaleRatio() = 0;

  // Access to object by its tag, taking transfomanager into account, if any
  virtual CATICGMObject *FindObjectFromTag(int iTag) = 0;

  // Access to image object
  virtual CATICGMObject *ReadImage(CATICGMObject *iInputObject) = 0;

};

/**
 * @return [out, delete]
 */
ExportedByCATGMModelInterfaces CATPGMODTScaleManager *CATPGMCreateODTScaleManager();

#endif /* CATPGMODTScaleManager_h_ */
