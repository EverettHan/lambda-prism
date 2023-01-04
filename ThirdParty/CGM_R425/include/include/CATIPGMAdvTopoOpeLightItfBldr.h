#ifndef CATIPGMAdvTopoOpeLightItfBldr_h
#define CATIPGMAdvTopoOpeLightItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATTopDefine.h"

class CATICGMTopologicalFill;
class CATIPGMTopologicalFill;
class CATGeoFactory;
class CATBody;
class CATTopData;
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvTopoOpeLightItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework AdvancedTopologicalOpe.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMAdvTopoOpeLightItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFillLight(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNumberOfWires,
    const CATBody **iArrayOfBodyWires,
    const CATBody **iArrayOfBodySupports) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFillLight(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    const CATLISTP(CATEdge) *iListOfEdges,
    const CATLISTP(CATFace) *iListOfFaces,
    const CATBody *iBody) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFillLight(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNumberOfWires,
    const CATBody **iArrayOfWires) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework AdvancedTopologicalOpeLight.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMAdvTopoOpeLightItfBldr *CATCGMGetAdvTopoOpeLightItfBldr();

#endif /* CATIPGMAdvTopoOpeLightItfBldr_h */
