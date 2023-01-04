//======================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//======================================================================
//
// CATStoFadingEdge.h
//
//======================================================================
//
// Usage notes: Objet fading edge.
//
//======================================================================
// March,    2010 : RAQ : Création
//======================================================================
#ifndef CATStoFadingEdge_H
#define CATStoFadingEdge_H

//Pour l'export
#include "YP0LOGRP.h"

//Classe mère
#include "CATCGMStreamAttribute.h"

//Fading edge
#include "CATStoFadingEdgeDefine.h"
#include "CATStoFadingEdgeState.h"
#include "CATStoFadingEdgeImpl.h"

//Divers
#include "CATListOfInt.h"
#include "CATBoolean.h"
#include "CATMathStream.h"
#include "CATCGMStream.h"


class CATStoFadingEdgeImpl;
class CATMathVector;



class ExportedByYP0LOGRP CATStoFadingEdge: public CATCGMStreamAttribute
{
  CATCGMDeclareAttribute(CATStoFadingEdge, CATCGMStreamAttribute);

  friend ExportedByYP0LOGRP CATStoFadingEdge* CATCreateStoFadingEdge();
  friend ExportedByYP0LOGRP CATStoFadingEdge* CATCreateStoFadingEdge(const CATListOfInt & iVerticesTags, const double iStartParam, const double iEndParam, const CATBoolean iIsClosed);
  friend ExportedByYP0LOGRP CATStoFadingEdge* CATCreateStoFadingEdge(const CATStoFadingEdge& iFadingEdgeToCopy);


public:

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
  CATStoFadingEdgeState GetState() const;
  CATBoolean IsValid() const;

  //Temporaire : Nouvelle version des fading edges
  CATBoolean IsTOPOFadingEdge() const;

  //********************************************* Stream *********************************************//
  virtual void Stream(CATCGMStream& ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);

  //Stream version CATMathStream
  void Stream(CATMathStream& ioStream) const;
  void UnStream(CATMathStream& ioStream);

  //Dump
  void Dump(CATCGMOutput& os);

  //******************************************* DO NOT USE *******************************************//
  //Récupération de l'implémentation
  void* GetImpl();

  //Constructeurs
  CATStoFadingEdge();
  CATStoFadingEdge(const CATListOfInt & iVerticesTags, const double iStartParam, const double iEndParam, const CATBoolean iIsClosed = FALSE);
  CATStoFadingEdge(const CATStoFadingEdge& iFadingEdgeToCopy);

  //Destructeur
  virtual ~CATStoFadingEdge();

protected:


private:

  //Pas de copie
  CATStoFadingEdge& operator=(const CATStoFadingEdge&);


  //--------- Data:
  CATStoFadingEdgeImpl _FadingEdgeImpl;

};

/**
 * Creates fading edge object
 **/
ExportedByYP0LOGRP CATStoFadingEdge* CATCreateStoFadingEdge();
ExportedByYP0LOGRP CATStoFadingEdge* CATCreateStoFadingEdge(const CATListOfInt & iVerticesTags, const double iStartParam, const double iEndParam, const CATBoolean iIsClosed = FALSE);
ExportedByYP0LOGRP CATStoFadingEdge* CATCreateStoFadingEdge(const CATStoFadingEdge& iFadingEdgeToCopy);


#endif

