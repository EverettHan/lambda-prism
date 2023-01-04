//======================================================================
// Copyright Dassault Systemes Provence 2009, All rights reserved
//======================================================================
//
// CATSobMeshLayerId.h
//
//======================================================================
//
// Usage notes: ID for mesh layers.
//
//======================================================================
// December,    2009 : RAQ : Création
//======================================================================
#ifndef CATSobMeshLayerId_H
#define CATSobMeshLayerId_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATBoolean.h"
#include "CATDataType.h"


class ExportedByCATSobObjects CATSobMeshLayerId
{
public:

  //Constructeur
  CATSobMeshLayerId(char* const IdName);

  //Gestion références
  virtual int AddRef();
  virtual void Release();

  //Opérateurs de comparaison
  int operator==(const CATSobMeshLayerId& iToCompare);
  int IsSimilarTo(const CATSobMeshLayerId*) const;
  int operator!=(const CATSobMeshLayerId& iToCompare);

  //Recopie
  CATSobMeshLayerId& operator=(CATSobMeshLayerId&);

protected:

  //Destructeur
  virtual ~CATSobMeshLayerId();

  //Contructeur par recopie
  CATSobMeshLayerId(CATSobMeshLayerId&);
  
  //Obtention du type
  inline char* const GetType() const {return _Type;}

private:

  //Constructeur par défaut
  CATSobMeshLayerId();

  //Recopie du type
  char* const CopyType() const;

  //----------- Private data:
  char* const _Type;
  int _RefCounter;
};

//---------------------
// Gestion références
//---------------------
inline int CATSobMeshLayerId::AddRef()
{
  return ++_RefCounter;
}


inline void CATSobMeshLayerId::Release()
{
  if(--_RefCounter<=0) delete this;
}


//**************************** Objet de création des ID ****************************

class ExportedByCATSobObjects CATSobMeshLayerIdStatic
{
public:
  
  //Constructeurs
  CATSobMeshLayerIdStatic(char* const IdName);
  CATSobMeshLayerIdStatic(CATSobMeshLayerId* iD);
  
  //Destructeur
  virtual ~CATSobMeshLayerIdStatic();
  
  //Gestion ID
  CATSobMeshLayerId* GetId();
  void SetId(CATSobMeshLayerId* iD);

private:

  //------- Data:
  CATSobMeshLayerId *_Id;
};


// Macro declare a new layer
#define CATDECLARESOBMESHLAYER(itype, VAR)                  \
static CATSobMeshLayerId* itype##IDInitializer();           \
static CATSobMeshLayerId* itype##IDInitializer()            \
{                                                           \
  return new CATSobMeshLayerId(#itype);                     \
}                                                           \
static CATSobMeshLayerId* VAR=itype##IDInitializer();       \
static CATSobMeshLayerIdStatic VAR##IDStatic(VAR);

#endif
