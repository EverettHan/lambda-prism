#ifndef CATPGMCreateATOCompositeCurve_h_
#define CATPGMCreateATOCompositeCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATBody;
class CATEdge;
class CATFace;
class CATFrFCompositeCurve;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopOperator;

//class CATEdgeCurve;
// iNonConnexWireSupport a mettre a TRUE si on autorise
// les wires non connexes
// dans ce cas, malgre tout, la CCV est vue comme un seul 
// assemblage de courbes, sans notion de domaine; à charge
// pour l'utilisateur de gerer correctement les continuites
//   Nicolas, 10/01/00
ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
  CATTopData *iTopData,
  const CATBody *iWire,
  CATBoolean iNonConnexWireSupport = FALSE,
  CATLONG32 iStartIndex = -1,
  CATLONG32 iEndIndex = -1,
  CATIPGMTopOperator *iTopOperator = 0);

ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
  CATTopData *iTopData,
  const CATBody *iWire,
  CATEdge **&oEdges,
  CATBoolean iNonConnexWireSupport = FALSE,
  CATLONG32 iStartIndex = -1,
  CATLONG32 iEndIndex = -1,
  CATIPGMTopOperator *iTopOperator = 0);

// le mode Hybride 3d 2d cree une composite curve a partir d'un wire
// dont les edges contiennent soit des PCurves soit des MergedCurves sur des PCurves;
// les courbes 3D sont utilisees pour les evaluations, et les PCurves sont
// utilisees pour les evaluations de normales
ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATBody *iBodyWire,
  const CATBody *iBodySupport = 0,
  CATBoolean iNonConnexWireSupport = FALSE,
  CATBoolean iIgnoreOutsideEdgeParts = FALSE,
  CATBoolean iHybrid3D2DMode = FALSE,
  CATIPGMTopOperator *iTopOperator = 0,
  CATBoolean iWarningNotOnShellBoundary = FALSE);

ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATBody *iBodyWire,
  const CATBody *iBodySupport,
  CATEdge **&oEdges,
  CATFace **&oDummy,
  CATBoolean iNonConnexWireSupport = FALSE,
  CATBoolean iIgnoreOutsideEdgeParts = FALSE,
  CATBoolean iHybrid3D2DMode = FALSE,
  CATIPGMTopOperator *iTopOperator = 0,
  CATBoolean iWarningNotOnShellBoundary = FALSE);

#endif /* CATPGMCreateATOCompositeCurve_h_ */
