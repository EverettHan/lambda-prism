#ifndef EdgeUtilities_H_
#define EdgeUtilities_H_
/* -*-c++-*- */
//===================================================================
//  EdgeUtilities: utility services on edges
//-------------------------------------------------------------------
//  02/08/05 NLD Creation
//               IsEdgeDegenerate()
//===================================================================
#include <CXMODEL.h>
#include <CATBoolean.h>
#include <CATTopDefine.h>
#include "CATCollec.h"

class CATSoftwareConfiguration ;
class CATEdge ;
class CATEdgeCurve ;
class CATPointOnEdgeCurve ;
class CATPCurve;
class CATSurface;
class CATCurve;
class CATGeoFactory;
class CATLISTP(CATCurve);

//----------------------------------------------------------------------------------------------
// Calcul rapide de degenerescence d'edge
// rend la longueur seulement en dessous de la tolerance recue (et non pas en dessus)
// ce qui peut servir en cas d'algorithme a deux tolerances (passer alors la plus grande)
//----------------------------------------------------------------------------------------------
extern "C" ExportedByCXMODEL CATBoolean IsEdgeDegenerate(CATSoftwareConfiguration* iConfig, CATEdge* edge, double Tolerance,
                             double& oLengthIfDegenerate) ;

extern "C" ExportedByCXMODEL
void
FilterAndReplaceGeometryOnEdge(
   CATGeoFactory   *iFactory,
   CATSoftwareConfiguration * iConfig,
   CATEdge         *iEdge,
   CATSurface      *iRefSurface
  );

#endif
