//================================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved
//================================================================================
//
// CATStoTopoOperator.h
//
//================================================================================
//
// Usage notes: Stockage des liens entre CATBody et CATSubdivMesh
//
//================================================================================
// April,     2007 : RAQ : Déplacement de CATStoTopo pour pb IMA de chargement
// October,   2006 : RAQ : Ajout d'attributs artificiel pour compatibilité < R18
// April,     2005 : RNO : Creation
//================================================================================
#ifndef CATStoTagLinksAttr_H
#define CATStoTagLinksAttr_H

//Pour l'export
#include "YP0LOGRP.h"

//Classe mère
#include "CATCGMStreamAttribute.h"

//Divers
#include "CATDataType.h"
#include "CATIAV5Level.h"


class ExportedByYP0LOGRP CATStoTagLinksAttr: public CATCGMStreamAttribute
{
  CATCGMDeclareAttribute(CATStoTagLinksAttr, CATCGMStreamAttribute);

public :

  //Constructeur
  CATStoTagLinksAttr();
  
  //Destructeur
  virtual ~CATStoTagLinksAttr();

  //Gestion Stream
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream & ioStream);

  //Les liens
  void SetLinkTag(CATULONG32 iTag);
  CATULONG32 GetLinkTag();

  //-------------------------------------------------------------------------------------------------
  // DO NOT USE -- Gestion d'attributs pour compatibilité stream (utile avant R18 ou R204 seulement)
  //-------------------------------------------------------------------------------------------------
#if !defined CATIAV5R18 && !defined CATIAR204
  //********** DO NOT USE - Type de PCCM
  void SetPCCMCommonType();
  CATBoolean IsPCCMCommonType() const;

  //********** DO NOT USE - Type de raccords pour le PCCM
  void SetPCCMContinuityType(const CATBoolean iG0, const CATBoolean iG1, const CATBoolean iG2);
  void GetPCCMContinuityType(CATBoolean& oG0, CATBoolean& oG1, CATBoolean& oG2) const;

  //********** DO NOT USE - Correction des surfaces singulières
  void SetProcessSingularSurfaces(const CATBoolean iProcessOnOff);
  CATBoolean MustProcessSingularSurfaces() const;

  //********** DO NOT USE - Copie d'attributs
  void CopySubdivMeshProperties(CATStoTagLinksAttr* iFromAttribute);
#endif  //!R18 et !R204

private:

  //------ Streamed Data:
  CATULONG32 _Tag;

  //------ Not streamed Data:
#if !defined CATIAV5R18 && !defined CATIAR204
  //CATSubdivMeshProperty _PCCMType, _GeometricContinuityType, _SingularSurfacesMode;
  int _PCCMType;                      // 0 -> défaut
  int _GeometricContinuityType;       // 0->G0, 1->G1, 2->G2
  CATBoolean _SingularSurfacesMode;   // FALSE -> pas de correction, TRUE -> correction active
#endif  //!R18 et !R204
};

#endif




