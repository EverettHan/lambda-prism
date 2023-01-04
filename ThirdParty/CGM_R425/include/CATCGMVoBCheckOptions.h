// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
// Creation JHN  23/05/2011
//
// VoB check options creation. 
// 3 options :
//    - intersection between two cells in the body
//    - self intersection in geometry inside topological boundaries
//    - check of non manifold configuration (contact of more than two faces on an edge, contact of several set of connex faces on one vertex)
//=============================================================================

#ifndef __CATCGMVoBCheckOptions_h__
#define __CATCGMVoBCheckOptions_h__
#include "CATBoolean.h"
#include "CATGMModelInterfaces.h"


struct ExportedByCATGMModelInterfaces CATCGMVoBCheckOptions
{
  CATBoolean _VoBIntersectionBetweenCells;
  CATBoolean _VoBCellSelfIntersection;
  CATBoolean _VoBNonManifold;

  CATCGMVoBCheckOptions();
  // copy constructor
  CATCGMVoBCheckOptions(const CATCGMVoBCheckOptions & iOther);
  // equal operator 
  CATCGMVoBCheckOptions& operator=(const CATCGMVoBCheckOptions & iOther);
   
  // provisoire pour compatibilite sources non migres
  #define _VoBNonManiFold _VoBNonManifold



  
   
};

 

#endif
