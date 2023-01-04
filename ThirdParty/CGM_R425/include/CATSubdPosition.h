// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
// CATSubdPosition :
// type enumere decrivant le positionnement interieur/exterieur
// d'un objet par rapport a un autre
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct. 1996  Creation                       I. Chauvigne, X. Dupont, L. Laloy
// Sep. 2000  Ajout CATSubdPositionIncompatible                         EDS
//=============================================================================
#ifndef CATSubdPosition_H
#define CATSubdPosition_H

typedef enum
{
   CATSubdPositionOut     = -1 ,
   CATSubdPositionIn      =  1 ,
   CATSubdPositionUnknown      ,
   CATSubdPositionBoundary     ,
   CATSubdPositionUnset        ,
   CATSubdPositionError        ,
   CATSubdPositionIncompatible ,
   CATSubdPositionGeomBoundary ,
   CATSubdPositionKeep         ,
   CATSubdPositionRemove       ,
   CATSubdPositionKeepBoundary
} 
CATSubdPosition;

#endif
