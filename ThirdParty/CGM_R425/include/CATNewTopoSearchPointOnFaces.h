#ifndef CATNewTopoSearchPointOnFaces_h
#define CATNewTopoSearchPointOnFaces_h
//

// COPYRIGHT DASSAULT SYSTEMES 1999

//    recherche si un point est pose sur une face. Si oui on rend la face
//    et le positionnement du point sur la surface. L'utilisation du CATLayDownOperator
//    serait sans doute plus approprie, mais on ne dispose par encore de cette propriete
//    dans les CATLayDownOperator
//
class CATGeoFactory;
class CATEdge;
class CATVertex;
class CATTopData;

#include "CATSurParam.h"
#include "CATCrvParam.h"
#include "CATFace.h"
#include "ExportedByCATTopologicalObjects.h"

ExportedByCATTopologicalObjects
void  CATNewTopoSearchPointOnFaces(CATGeoFactory * iFacto, 
                            CATTopData * iTopData, 
                            const CATLISTP(CATFace) * iListOfFaces, 
                            CATVertex * iVertex,
                             CATSurParam & oOnFaceParam,CATLONG32 & oNumFace,
                             CATCrvParam & oOnEdge, CATEdge *& oEdge,
                             double * iTolerance = NULL);

#endif
