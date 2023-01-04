#ifndef CATIPGMCATAxisBodyItfBldr_h
#define CATIPGMCATAxisBodyItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "CATDataType.h"

class CATBody;
class CATCell;
class CATGeoFactory;
class CATVertex;
class CATMathAxis;
class CATTopData;
class CATCGMCoordSystemBodyAttr;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCATAxisBodyItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework AdvancedTopologicalOpe.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMCATAxisBodyItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATBody *CATCGMCreateCoordSystemBody(CATGeoFactory *iFactory, CATMathAxis &iAxis) = 0;

  virtual CATBody *CATCGMCreateCoordSystemBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATMathAxis &iAxis) = 0;

  virtual CATCGMCoordSystemBodyAttr *CATCGMCreateCGMCoordSystemBodyAttrImpl() = 0;

  virtual void CATCGMPrivExtractCellFromAxisSystemBody(CATBody *iBody, CATCell **oCell) = 0;

  virtual void CATCGMPrivGetInfiniteBodyFromAxisSystemElement(
    CATCell *iCell,
    CATGeoFactory *iFactory,
    CATBody **oInfiniteBody) = 0;

  virtual void CATCGMPrivGetInfiniteBodyFromAxisSystemElement(
    CATBody *iBody,
    CATGeoFactory *iFactory,
    CATBody **oInfiniteBody) = 0;

  virtual CATBoolean CATCGMPrivIsElementFromAxisSystem(
    CATCell *iCell,
    CATVertex **oOriginVertex) = 0;

  virtual CATBoolean CATCGMPrivIsElementFromAxisSystem(CATBody *iBody) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework AdvancedTopologicalOpe.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMCATAxisBodyItfBldr *CATCGMGetCATAxisBodyItfBldr();

#endif /* CATIPGMCATAxisBodyItfBldr_h */
