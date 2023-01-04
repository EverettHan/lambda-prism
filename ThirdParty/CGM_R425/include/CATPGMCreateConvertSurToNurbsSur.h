#ifndef CATPGMCreateConvertSurToNurbsSur_h_
#define CATPGMCreateConvertSurToNurbsSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATConvertSurToNurbsSur;
class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;

/**
 * @deprecated V5R10 CreateSurFittingToNurbsSur 
 * Creates the geometric operator that computes the Nurbs representation of a CATSurface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iSurface
 * The pointer to the surfacee to convert.
 * @param iMode
 * The mode of use.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 * @see CATConvertSurToNurbsSur
 */
ExportedByCATGMOperatorsInterfaces CATConvertSurToNurbsSur *CATPGMCreateConvertSurToNurbsSur(
  CATGeoFactory *iFactory,
  const CATSurface &iSurface,
  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces CATConvertSurToNurbsSur *CATPGMCreateConvertSurToNurbsSur(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATSurface &iSurface);

#ifndef CATConvertSurToNurbsSur_Remove
#define CATConvertSurToNurbsSur_Remove

/**
 * @nodoc
 */
ExportedByCATGMOperatorsInterfaces
void Remove( CATConvertSurToNurbsSur *&ioCATConvertSurToNurbsSur );

#endif

#endif /* CATPGMCreateConvertSurToNurbsSur_h_ */
