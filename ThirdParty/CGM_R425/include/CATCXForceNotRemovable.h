#ifndef CATCXForceNotRemovable_H
#define CATCXForceNotRemovable_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
// NE PAS UTILISER : cette methode va disparaitre !!!
// Eviter les perturbations d'un Remove effectif imprevue
//  (contexte d'un precedent Remove ayant decremente le compteur de Reference
//   mais ayant egalement provoquer un marquage Removable,
// Usage temporaire dans CATDynSolidDraftCGM permettant d'activer
//  le Verrou : on ne redefini pas la Topolgie d'un Object Gele !!!
//===========================================================================
#include "CXMODEL.h"
#include "ListPOfCATFace.h"

class CATICGMObject;
ExportedByCXMODEL void CATCXForceNotRemovable( CATICGMObject * iCGMObject );
ExportedByCXMODEL void CATCXForceNotRemovable( const ListPOfCATFace &faces );

#endif
