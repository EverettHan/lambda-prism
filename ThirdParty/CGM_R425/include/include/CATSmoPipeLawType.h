//====================================================================
// Copyright Dassault Systemes Provence 2009, all rights reserved 
//====================================================================
//
// CATSmoPipeLawType.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// December,      2009 : RBD : Creation
//====================================================================
#ifndef CATSmoPipeLawType_H
#define CATSmoPipeLawType_H

//---------------------------------------------------------------//
//                      For Pipe creation                        //
//---------------------------------------------------------------//
// Type de loi de balayage a creer
//  Frenet
//  Orthogonal à une direction
//  ...

typedef enum 
{ 
  CATSmoPipeLaw_FRENET          ,
  CATSmoPipeLaw_ORTHO_DIRECTION ,
} CATSmoPipeLawType;

#endif
