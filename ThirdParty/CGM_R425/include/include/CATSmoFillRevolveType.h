//====================================================================
// Copyright Dassault Systemes Provence 2006, all rights reserved 
//====================================================================
//
// CATSmoFillRevolveType.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// August,      2008 : RBD : Creation
//====================================================================
#ifndef CATSmoFillRevolveType_H
#define CATSmoFillRevolveType_H

//---------------------------------------------------------------//
//                      For Revolve creation operator            //
//---------------------------------------------------------------//

// CATSmoFillRevol : Type concernant le remplissage de la surface de révolution
typedef enum 
{ 
  CATSmoNoFillRevol     = 0,
  CATSmoFillRevolBottom = 1,
  CATSmoFillRevolTop    = 2,          
  CATSmoFillRevolBoth   = 3
} CATSmoFillRevol;


#endif
