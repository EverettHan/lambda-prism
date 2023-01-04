#ifndef CATIPGMConstantFilletTool_h_
#define CATIPGMConstantFilletTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMConnectTool.h"

class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConstantFilletTool;

class ExportedByCATGMModelInterfaces CATIPGMConstantFilletTool: public CATIPGMConnectTool
{
public:
  /**
   * Constructor
   */
  CATIPGMConstantFilletTool();

  virtual void SetRadius(const double iradius) = 0;

  virtual double GetRadius() const = 0;

  virtual CATLONG32 GetType() const = 0;

  // cwm 12sept06: Pour le fillet conique
  virtual void SetConicalSection(double iConicParameter) = 0;

  //hln17092009: Pour le fillet G2
  virtual void SetG2Section() = 0;

  virtual CATLONG32 GetSectionType() const = 0;

  virtual double GetConicParameter() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConstantFilletTool(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConstantFilletTool *CATPGMCreateConstantFilletTool(
  CATSoftwareConfiguration *iConfig,
  const double iRadius);

//Do not use - Use the constructor with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConstantFilletTool *CATPGMCreateConstantFilletTool(const double iRadius);

#endif /* CATIPGMConstantFilletTool_h_ */
