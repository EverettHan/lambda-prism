//======================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//======================================================================
//
// CATStoFadingEdgeImpl.h
//
//======================================================================
//
// Usage notes: Objet fading edge.
//
//======================================================================
// March,    2010 : RAQ : Création
//======================================================================
#ifndef CATStoFadingEdgeImpl_H
#define CATStoFadingEdgeImpl_H

//Pour l'export
#include "YP0LOGRP.h"

//Fading edge
#include "CATStoFadingEdgeState.h"
#include "CATStoFadingEdgeDefine.h"

//Divers
#include "CATListOfInt.h"
#include "CATBoolean.h"
#include "CATMathVector.h"
#include "CATCGMOutput.h"

class CATMathStream;


class ExportedByYP0LOGRP CATStoFadingEdgeImpl
{
public:

  //Constructeur
  CATStoFadingEdgeImpl();

  //Destructeur
  virtual ~CATStoFadingEdgeImpl();

  //Opérateur de recopie
  CATStoFadingEdgeImpl& operator=(const CATStoFadingEdgeImpl& iToCopy);


  //********************************************* Services *********************************************//
  //Récupération des tags des vertex des edges du fading edge
  const CATListOfInt& GetVerticesTags() const;

  //Test de fermeture
  CATBoolean IsClosed() const;

  //Obtention des paramètres
  double GetStartParam() const;
  double GetEndParam() const;
  void GetParams(double& oStartParam, double& oEndParam) const;

  //Imposition du déplacement du point de fin de FE
  CATBoolean MustSlideEndPoint() const;
  CATBoolean GetEndPointSlidingParams(CATStoFE_Side& oSide, double& oRatio) const;  //Renvoie TRUE si un glissement est imposé

  //Imposition de la direction de fin de FE
  CATBoolean HasEndingDirection() const;
  CATBoolean GetEndingDirection(CATMathVector& oDirection) const;  //Renvoie TRUE si une direction existe

  //Imposition de la tension en fin de FE
  CATBoolean HasEndingTension() const;
  CATBoolean GetEndingTension(double& oTension) const;  //Renvoie TRUE si une tension est imposée

  //Diags de validité
  void SetState(const CATStoFadingEdgeState iState);
  inline CATStoFadingEdgeState GetState() const { return _FadingEdgeState; }
  CATBoolean IsValid() const;

  //********************************************* Stream *********************************************//
  virtual void Stream(CATMathStream& ioStream) const;
  virtual void UnStream(CATMathStream& ioStream);

  //Dump
  void Dump(CATCGMOutput& os);

  //***************************************** Accès restreint *****************************************//
  //Temporaire : Nouvelle version des fading edges
  CATBoolean IsTOPOFadingEdge() const;
  void SetTOPOFadingEdge();

  //Modification des paramètres
  void SetParameters(const double iStartParam, const double iEndParam);

  //Imposition du déplacement du point de fin de FE
  void SetEndPointSlidingParams(const CATStoFE_Side iSide, const double iRatio);
  void RemoveEndPointSliding();

  //Imposition de la direction de fin de FE
  void SetEndingDirection(const CATMathVector& iDirection);
  void RemoveEndingDirection();

  //Imposition de la tension en fin de FE
  void SetEndingTension(const double iTension);
  void RemoveEndingTension();

  //Modification des données
  void SetData(const CATListOfInt & iVerticesTags, const double iStartParam, const double iEndParam, const CATBoolean iIsClosed = FALSE);

  //Inversion de l'orientation du fading edge
  void Reverse();

private:

  //Flag de fermeture
  void SetClosed(const CATBoolean iIsClosed);

  //Non implémenté
  CATStoFadingEdgeImpl(const CATStoFadingEdgeImpl&);


  //-------- Data:
  CATListOfInt _VerticesTags;
  double _StartParam, _EndParam;
  CATStoFE_Side _SlideSide; //Côté vers lequel il faut déplacer le point de fin de la FE
  double _EndSlideRatio;  //Ratio pour le déplacement du point de fin de FE, 0.0 --> pas de déplacement imposé
  CATMathVector _EndingDirection;
  double _EndingTension;

  CATStoFadingEdgeState _FadingEdgeState;

  //Codage des infos binaires
  // Bit 0x01 : (0) Fading edge ouvert, (1) Fading edge fermé
  // Bit 0x02 : (0) Pas de déplacement du vertex de fin, (1) Imposition du déplacement du vertex de fin
  // Bit 0x04 : (0) Pas de direction imposée à la fin, (1) Direction imposée à la fin
  // Bit 0x08 : (0) Pas de tension imposée à la fin, (1) Tension imposée
  // Bit 0x10 : 
  // Bit 0x20 : 
  // Bit 0x40 : 
  // Bit 0x80 : (0) Fading Edge PCCM, (1) TOPO Fading Edge, pour compatibilité de structure et doit disparaître
  unsigned char _BinaryInfos;

};


#endif

