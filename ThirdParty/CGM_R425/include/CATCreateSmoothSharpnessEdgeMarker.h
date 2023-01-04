// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation HCN  10/09/2001
//
// Methode permettant la creation d'une instance de l'operateur de marquage
// des edges mortes d'un body
//=============================================================================

#ifndef __CATCreateSmoothSharpnessEdgeMarker_h__ 
#define __CATCreateSmoothSharpnessEdgeMarker_h__ 

#include "ExportedByCATTopologicalObjects.h"

#include "CATMathConstant.h"
#include "CATTopDef.h"

class CATTopSmoothSharpnessEdgeMarker;
class CATGeoFactory;
class CATTopData;
class CATBody;


//--------------------------------------------------------------------------
//
// Methode: CATCreateSmoothSharpnessEdgeMarker
//
// Auteurs: HCN	       Date: 10/09/2001
//
// Description: 
//   Creation d'une instance de l'operateur de marquage des edges mortes d'un body.
//	 Cet operateur smart-duplique le body et marque les edges mortes du body duplique.
//
//
//   Cf. CATTopSmoothSharpnessEdgeMarker.h
//
// Arguments:
//   iFactory					Container geometrique de iSolidBody et de iSkinBody
//   iTopData					Configuration pour le versionning + journaling
//   iBody						Body a analyser et dupliquer
//   iMaxSmoothnessAngle		Angle limite determinant la nature de la vivicite (smooth/sharp) en rad
//   iNumberOfSharpnessSamples  Nombre de points de mesures determinant la vivicite
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopSmoothSharpnessEdgeMarker *
CATCreateSmoothSharpnessEdgeMarker(	CATGeoFactory * iFactory,
								CATTopData    * iTopData,
			                    CATBody       * iBody,
								CATAngle		iMaxSmoothnessAngle = CATTopSharpAngle,
								int				iNumberOfSharpnessSamples = 5);
#endif






