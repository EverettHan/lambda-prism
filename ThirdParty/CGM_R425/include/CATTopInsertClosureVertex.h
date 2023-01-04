#ifndef CATTopInsertClosureVertex_H
#define CATTopInsertClosureVertex_H
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 19 12 2000  Creation pour supprimer CATTopBodyTools.h
//---------------------------------------------------------------------------------------------------------
// code retour = diagnostic d'erreur
// 0 : OK, vertex inserted
// 10 : KO, iVertexBody n'est pas un vertex
// 11 : KO, iVertexBody contient plus d'un vertex
// 12 : KO, vertex non confondu geometriquement avec le wire (a la resolution)
// 20 : KO, iClosedWireBody contient plus d'un wire
// 21 : KO, iClosedWireBody n'est pas un wire
// 22 : KO, iClosedWireBody n'est pas ferme 
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATTopData.h"
class CATGeoFactory;
class CATBody;

ExportedByCATTopologicalObjects  int CATTopInsertClosureVertex(CATGeoFactory       *  iFactory,
                                                                CATBody            *  iClosedWireBody,
                                                                CATBody            *  iVertexBody,
                                                                CATBody            *   &oBody,
                                                                const CATTopData       &iTopData );

// For CATIALiveShape
ExportedByCATTopologicalObjects  int CATTopInsertLiveClosureVertex(CATGeoFactory       *  iFactory,
                                                                    CATBody            *  iClosedWireBody,
                                                                    CATBody            *  iVertexBody,
                                                                    CATBody            *   &oBody,
                                                                    const CATTopData       &iTopData );

  
#endif
