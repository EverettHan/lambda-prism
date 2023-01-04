#ifndef CATISGMSurfTopoOpeItfBldr_h
#define CATISGMSurfTopoOpeItfBldr_h

#include "CATSGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "CATTopologicalFillType.h"

class CATIPGMFilling;
class CATGeoFactory;
class CATTopData;
class CATIPGMHealing;
class CATBody;
class CATISGMTopologicalAutomaticFill;
class CATIPGMTopologicalFill;
class CATCGMJournalList;
class CATCldPolygon;
class CATPowerCldPolygon;
class CATISGMTopoDeformSwitchGeometry;
class CATIPGMPolygon2Surface;
class CATLISTP(CATBody);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

extern ExportedByCATSGMOperatorsInterfaces IID IID_CATISGMSurfTopoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework SurfacicTopoOperators.
 */
class ExportedByCATSGMOperatorsInterfaces CATISGMSurfTopoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATISGMTopologicalAutomaticFill *CATSGMCreateTopologicalAutomaticFill(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) const &iListOfWires,
    CATLISTP(CATBody) const &iListOfSupports,
    const CATTopologicalFillType iFillType) = 0;

  virtual CATISGMTopologicalAutomaticFill *CATSGMCreateTopologicalAutomaticFill(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) const &iListOfWires,
    const CATTopologicalFillType iFillType) = 0;

   virtual CATISGMTopoDeformSwitchGeometry *CATSGMCreateTopoDeformSwitchGeometry(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDeform) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework SurfacicTopoOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATISGMSurfTopoOpeItfBldr *CATSGMGetSurfTopoOpeItfBldr();

#endif /* CATISGMSurfTopoOpeItfBldr_h */
