/* -*-c++-*- */
#ifndef CATTopGeometricalMapType_H
#define CATTopGeometricalMapType_H
// COPYRIGHT DASSAULT SYSTEMES  2002

#define CATTopGeometricalMapType              CATULONG32 
#define CATTopGeometricalMapType_Vertex       0x000000FF
#define CATTopGeometricalMapType_Edge         0x0000FF00

//============================================================================
//    Un sommet est assimile a un point
//    Deux sommets sont equivalents si leurs points sont distants
//     d'une longueur inferieure ou egale a la resolution.
//============================================================================
#define CatTopGeometricalMap_VertexAsSinglePoint       0x00000001

//============================================================================
//    Un sommet est assimile a un nuage de points
//    Deux sommets sont equivalents si on trouve deux representations de leur nuage de points
//      a une distance inferieure ou egale a la resolution.
//============================================================================
#define CatTopGeometricalMap_VertexAsCloudOfPoints     0x00000002



//==================================================================================
// I - Deux Edges sont equivalentes au signe pres si leurs extremites sont equivalentes
//  et si le point milieu est equivalent à la sauce mapping de Body
//============================================================================
#define CatTopGeometricalMap_EdgeAsMiddleParam         0x00000100

//==================================================================================
// II - Deux Edges sont equivalentes au signe pres si 
//   1 - leurs extremites sont equivalentes et si le point milieu est equivalent 
//       à la sauce mapping de Body (voir I ci dessus)
//   2 - Au moins deux vertex de chaque edge sont en confusion (confusion sur au 
//       moins une extremité) et soit
//				i - les deux edges partage le même vertex sur l'autre extremité
//						et les deux edges sont confondus sur un échantillon de points internes
//        ii- soit pas de confusions entre les vertex de l'autre extremité mais 
//            confusion géométrique partielle sur la longueur de l'edge la plus petite 
//            (également sur un echantillon de points)	
// N.B : le cas ou deux edges sont confondus sur une partie de leurs longueurs sans 
//       qu'au moins une des deux extremités soit confondue n'est pas traité
//============================================================================
#define CatTopGeometricalMap_EdgePartOrFullConfusion         0x00001000

#endif
