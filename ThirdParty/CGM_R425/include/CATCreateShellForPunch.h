#ifndef CATCreateShellForPunch_H
#define CATCreateShellForPunch_H
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 1999

//===================================================================
//
// Function definition for overiding default shape of min/Punch mode skin skin Fillet 
//
//===================================================================

// TopologicalOperators
class CATSoftwareConfiguration;

//NewTopologicalObjects
class CATBody;
class CATShell;
class CATFace;
class CATVertex;
class CATCell;

//GeometricObjects
class CATSurParam;

//Mathematics
#include "CATMathDef.h"
class CATMathPoint;
class CATMathVector;



//===================================================================
typedef void (*CATCreateShellForPunch)(CATSoftwareConfiguration* iConfig,
                                       void*                     iAnyData,
                                       CATBody*                  iBodyToTrim,  // Body support qui contient les surfaces d'appuis ainsi que la skin fillet,         
                                       CATBody*                  iTrimmingBody,//Body résultat ou il faut stocker le shell crée par la fonction
                                       CATVertex*                iFirstVertex, //vertex géneré par fillet jusqu'ou extrapoler le shell resultat
                                       CATCell*                  iFirstContact , //edge ou vertex de l'appui indiquant l'endroit de la boundary a extrapoler
                                       CATVertex*                iFirstVertexOnContactEdge,//vertex génère par fillet pose coupant sur iFirstContact.
                                       CATVertex*                iSecondVertex, //idem ci-dessus, pour le contact en face
                                       CATCell*                  iSecondContact ,// 
                                       CATVertex*                iSecondVertexOnContactEdge,//
                                       CATShell*               & oTrimmingShell,    //shell créé,    
                                       CATFace*                & oFirstTrimmingFace, //la face ou poser le iFirstVertex,  
                                       CATSurParam             & oOriginPositionOnFace, //position du iFirstVertex sur la face
                              
                                       CATMathVector           & iFirstDirection,//direction de l'intersection calculée sur le iFirstVertex,
                                       CATMathVector           & iSecondDirection //direction d'extrusion correspond a la moyenne des normales au support 
                                                                                  //calculées dans  iFirstVertex et iSecondVertex.
                                         );     //
//===================================================================
#endif
