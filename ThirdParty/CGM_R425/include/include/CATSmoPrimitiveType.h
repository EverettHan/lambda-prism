//====================================================================
// Copyright Dassault Systemes Provence 2006, all rights reserved 
//====================================================================
//
// CATSmoPrimitiveType.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// September,      2006 : RBD : Creation
//====================================================================
#ifndef CATSmoPrimitiveType_H
#define CATSmoPrimitiveType_H

//---------------------------------------------------------------//
//                      For Primitive creation                   //
//---------------------------------------------------------------//
// Type de primitive a creer
//  Sphere
//  Cylinder
//  Box
//  Torus
//  Pyramid
//  Square Face
//  Circle Face
//  Triangular Face
//  Ring Face

typedef enum 
{ 
  CATSmoPrimitive_SPHERE          ,
  CATSmoPrimitive_CYLINDER        ,
  CATSmoPrimitive_BOX             ,
  CATSmoPrimitive_TORUS           ,
  CATSmoPrimitive_PYRAMID         ,
  CATSmoPrimitive_SQUARE_FACE     ,
  CATSmoPrimitive_CIRCLE_FACE     ,
  CATSmoPrimitive_TRIANGULAR_FACE ,
  CATSmoPrimitive_RING_FACE       
} CATSmoPrimitiveType;

#endif
