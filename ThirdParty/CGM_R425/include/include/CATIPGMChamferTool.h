#ifndef CATIPGMChamferTool_h_
#define CATIPGMChamferTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMConnectTool.h"

class CATCurve;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMChamferTool;

class ExportedByCATGMModelInterfaces CATIPGMChamferTool: public CATIPGMConnectTool
{
public:
  /**
   * Constructor
   */
  CATIPGMChamferTool();

  virtual CATLONG32 GetType() const = 0;

  // new chamfer 
  virtual double GetFirstValue() const = 0;

  virtual double GetSecondValue() const = 0;

  virtual void SetConfig(CATSoftwareConfiguration *iConfig) = 0;

  virtual void SetType(const CATLONG32 iType) = 0;

  virtual void SetFirstValue(const double iFirstValue) = 0;

  virtual void SetSecondValue(const double iSecondValue) = 0;

  virtual void SetBadShapeStaus(const CATBoolean iStatus) = 0;

  virtual CATBoolean GetBadShapeStatus() const = 0;

  virtual void SetApproxChamferMode() = 0;

  virtual CATBoolean GetStatusOfApproxChamferMode() const = 0;

  virtual void SetOriginalChamferValues(double iD1, double iD2) = 0;

  virtual void GetOriginalChamferValues(double &ioD1, double &ioD2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMChamferTool(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMChamferTool *CATPGMCreateChamferTool(
  CATSoftwareConfiguration *iConfig,
  const double iValue1,
  const double iValue2,
  const CATLONG32 iCATChamferToolType);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMChamferTool *CATPGMCreateChamferTool(
  CATSoftwareConfiguration *iConfig,
  const double idist1,
  const double idist2,
  CATCurve *iSpine);

//Do not use - Use the constructor with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMChamferTool *CATPGMCreateChamferTool(
  const double iValue1,
  const double iValue2,
  const CATLONG32 iCATChamferToolType);

//Do not use - Use the constructor with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMChamferTool *CATPGMCreateChamferTool(
  const double idist1,
  const double idist2,
  CATCurve *iSpine);

#endif /* CATIPGMChamferTool_h_ */
