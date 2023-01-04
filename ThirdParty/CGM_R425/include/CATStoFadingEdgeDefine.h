//======================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//======================================================================
//
// CATStoFadingEdgeDefine.h
//
//======================================================================
//
// Usage notes: Enums et typedef pour les fading edges.
//
//======================================================================
// June,    2011 : RAQ : Création
//======================================================================
#ifndef CATStoFadingEdgeDefine_H
#define CATStoFadingEdgeDefine_H

//Pour l'export
#include "YP0LOGRP.h"


enum CATStoFE_Side
{
  Undef = 0,
  Left = -1,
  Right = 1
};


//Dump
ExportedByYP0LOGRP const char* ToString(const CATStoFE_Side iSide);

//Utiliatire : cast UChar --> FE_Side
ExportedByYP0LOGRP CATStoFE_Side CastToFE_Side(const unsigned char iUChar);

//Changement de sens
ExportedByYP0LOGRP CATStoFE_Side ReverseSide(const CATStoFE_Side iSide);


#endif  //CATStoFadingEdgeDefine_H


