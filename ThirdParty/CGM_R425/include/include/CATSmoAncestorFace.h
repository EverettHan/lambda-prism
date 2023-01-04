//=======================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=======================================================================
//
// CATSmoAncestorFace.h
//
//=======================================================================
//
// Usage notes: Ancêtre d'une face pour le suivi dans les journaux.
//
//=======================================================================
// November,    2009 : RAQ : Création
//=======================================================================
#ifndef CATSmoAncestorFace_H
#define CATSmoAncestorFace_H

//Pour l'export
#include "CATSmoOperators.h"


class ExportedByCATSmoOperators CATSmoAncestorFace
{
public:

  //Constructeurs
  CATSmoAncestorFace();
  CATSmoAncestorFace(const unsigned int iAncestorFaceTag, const int iAncestorDaughterFaceIndex = 0);
  CATSmoAncestorFace(const CATSmoAncestorFace& iToCopy);

  //Destructeur
  ~CATSmoAncestorFace();

  //Assignement
  CATSmoAncestorFace& operator=(const CATSmoAncestorFace& iToCopy);

  //--------- Data:
  unsigned int _AncestorFaceTag;
  int _AncestorDaughterFaceIndex;
};


#endif

