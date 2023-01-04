#ifndef CATIPGMConnectTool_h_
#define CATIPGMConnectTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATGeoFactory;
class CATGeoODTScaleManager;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConnectTool;

class ExportedByCATGMModelInterfaces CATIPGMConnectTool: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConnectTool();

  virtual CATLONG32 GetType() const = 0;

  virtual void SetOriginCurveSupport(CATSurface *iSupp, CATLONG32 iOrient) = 0;

  virtual void GetOriginCurveSupport(CATSurface *&oSupp, CATLONG32 &oOrient) = 0;

  static void WriteScaleInfo(CATCGMStream &Str);

  static void ReadScaleInfo(CATCGMStream &Str, double &oRefScale);

  static CATBoolean GetScaleManager(
    CATGeoFactory *iFactory,
    CATGeoODTScaleManager *&oScaleManager);

  static CATBoolean GetScaleManager(
    const double iScaleRef,
    CATGeoODTScaleManager *&oScaleManager);

  virtual CATGeoODTScaleManager *GetScaleManager() const = 0;

  virtual void SetScaleManager(CATGeoODTScaleManager *iScaleManager) = 0;

  virtual CATLONG32 GetSectionType() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConnectTool(); // -> delete can't be called
};

#endif /* CATIPGMConnectTool_h_ */
