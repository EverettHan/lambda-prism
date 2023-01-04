// COPYRIGHT DASSAULT SYSTEMES  <2005>
//=============================================================================
//
// CATSewOperatorOptions.h:
//
//=============================================================================
// Usage Notes:
//
// services permettant de modifier le comportement algorithmique de l'operateur
// de Sewing
//
//=============================================================================
// Jul. 05   Creation                                             JBX
//=============================================================================
//

#ifndef CATSewOperatorOptions_H
#define CATSewOperatorOptions_H

//DG
#include "ExportedByCATTopologicalObjects.h"

class CATTopSewSkin;

// iOperator  : l'operateur de Sewing a modifier.
// iMode == 0 : les faces issues d'une simplification ont un ordre de creation
ExportedByCATTopologicalObjects void SetSewSkinJournalingMode(CATTopSewSkin * iOperator, int iMode);
ExportedByCATTopologicalObjects void SetSewSkinDisableGeometricProjection(CATTopSewSkin * iOperator, int iDisable);


#endif // CATSewOperatorOptions_H
