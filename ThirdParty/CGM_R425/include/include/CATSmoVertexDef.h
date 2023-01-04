//====================================================================
// Copyright Dassault Systemes Provence 2004, all rights reserved 
//====================================================================
//
//====================================================================
//
// Usage notes:
//
//====================================================================
//  Avril 2004 : ANR : Creation 
//====================================================================

#ifndef CATSmoVertexDef_H
#define CATSmoVertexDef_H



/**
 * The type of Vertex.
 *
 **/
enum CATSmoVertexType
{
  CATSmoVertex_Close          = 0 // no sharped edges 
, CATSmoVertex_CloseAndSmooth = 1 
, CATSmoVertex_CloseAndSharp  = 2 
, CATSmoVertex_CloseSharpAndSmooth = 3 
, CATSmoVertex_Open          = 4 
, CATSmoVertex_OpenAndSmooth = 5 
, CATSmoVertex_OpenAndSharp  = 6 
, CATSmoVertex_OpenSharpAndSmooth = 7 
};

#endif
