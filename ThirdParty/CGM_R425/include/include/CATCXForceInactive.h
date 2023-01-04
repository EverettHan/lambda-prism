#ifndef CATCXForceInactive_H
#define CATCXForceInactive_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
// NE PAS UTILISER : cette methode va disparaitre !!!
// Il s'agit de combler les insuffisances de la specification actuelle
// des operateurs  de Merge de Vertex.
//===========================================================================
#include "CXMODEL.h"

ExportedByCXMODEL void CATCXForceInactive( CATBody * iBody );

//-------------------------------------------------------------------------------------------
//  Dedicated To ODT (performance measure in same context)
//-------------------------------------------------------------------------------------------
ExportedByCXMODEL int CATCXForceInactiveEveryBody( CATGeoFactory *iFactory );

#endif
