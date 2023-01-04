//=======================================================================================
// Copyright Dassault Systemes Provence 2009, All rights reserved
//=======================================================================================
//
// CATSobMeshLayer.h
//
//=======================================================================================
//
// Usage notes: Classe mère pour tous les layers sur un base mesh.
//              Les classes sont definies par famille (nom de famille) c'est a dire le CATSobMeshLayerId
//              On peut compléter l'identification par une méthode GetSecondName() (prénom) pour avoir plusieurs instances de la même famille.
//              Ce second nom optionnel est defini par un void* par la methode GetSecondName().
//
//=======================================================================================
// December,    2009 : RAQ : Création
//=======================================================================================
#ifndef CATSobMeshLayer_H
#define CATSobMeshLayer_H

//Pour l'export
#include "CATSobObjects.h"

//ID des layers
#include "CATSobMeshLayerId.h"

//Divers
#include "CATBoolean.h"
#include "CATDataType.h"


class ExportedByCATSobObjects CATSobMeshLayer
{
public:

  //Gestion références
  virtual int AddRef();
  virtual void Release();

  //Récupération de l'ID ou du nom
  inline CATLONGPTR GetName() const {return(_Name);}
  inline CATSobMeshLayerId* GetLayerId() const {return _LayerId;}

  //Opérateurs de comparaison
  int operator==(const CATSobMeshLayer& iToCompare);
  int IsSame(const CATSobMeshLayerId* iLayerID, const CATLONGPTR iName) const;
  int operator!=(const CATSobMeshLayer& iToCompare);

protected:

  //Constructeurs
  CATSobMeshLayer(CATSobMeshLayerId* iLayerID, CATLONGPTR iName=0);
  CATSobMeshLayer(CATSobMeshLayer&);

  //Destructeur
  virtual ~CATSobMeshLayer();

private:

  //Constructeurs
  CATSobMeshLayer();
  CATSobMeshLayer& operator=(CATSobMeshLayer&);

  //-------- Data:
  CATLONGPTR _Name;
  CATSobMeshLayerId* _LayerId;
  int _RefCounter;
};


//---------------------
// Gestion références
//---------------------
inline int CATSobMeshLayer::AddRef()
{
  return ++_RefCounter;
}

inline void CATSobMeshLayer::Release()
{
  if(--_RefCounter<=0) delete this;
}


#endif




