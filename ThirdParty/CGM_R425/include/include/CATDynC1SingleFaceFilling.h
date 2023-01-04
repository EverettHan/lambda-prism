#ifndef CATDynC1SingleFaceFilling_H
#define CATDynC1SingleFaceFilling_H

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

/**
 * @level Protected
 * @usage U1
 */

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATShell;
class CATTopFillingTool;
class CATTopFillingReport;
class CATTopFillingInput;

/**
 * Function used to fill a contour and create a blend vertex 
 * surface. This function is not to be used directly. This specific filling capability is used as the argument of
 * the <tt>CATDynEdgeFilletRibbon::SetReconfigFillFunction</tt><br>
 * Example:<br>
 * <pre>
 * CATDynFilletBlendVertexSpec* pSpec=  ::CATCreateDynFilletBlendVertexSpec(pCurEdge, ..., ...);
 * ...
 * CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(Edges1, listRadius);
 * ...
 * pRibbon->SetReconfigFillFunction(CATDynC1SingleFaceFilling, TRUE);
 * </pre>
 */


extern "C" ExportedByCATGMOperatorsInterfaces CATLONG32 CATDynC1SingleFaceFilling(CATGeoFactory* iCreationFactory,
                                                                CATTopData*            iTopData,
                                                                CATTopFillingTool*     iFillingTool, 
                                                                CATBody*               iCreationBody,     
                                                                CATShell*              iCreationShell,
                                                                CATTopFillingInput*    iContour,
                                                                CATTopFillingReport* & oReport)  ;    

#endif








