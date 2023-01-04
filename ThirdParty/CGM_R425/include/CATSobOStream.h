//======================================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//======================================================================================
//
// CATSobOStream.h
//
//======================================================================================
//
// Usage notes : ostream-like class.
//
//======================================================================================
// October,   2010 : RAQ : Creation
//======================================================================================
#ifndef CATSobOStream_H
#define CATSobOStream_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATBoolean.h"

class CATSobOStreamImpl;


class ExportedByCATSobObjects CATSobOStream
{
public:

  //Constructeur
  CATSobOStream();

  //Destructeur
  ~CATSobOStream();

  //Les méthodes de print
  CATSobOStream& operator<<(const char*);
  CATSobOStream& operator<<(const char);
  
  CATSobOStream& operator<<(const short);
  CATSobOStream& operator<<(const int);
  CATSobOStream& operator<<(const float);
  CATSobOStream& operator<<(const double);


protected:

  //Création du stream
  void CreateOStreamImpl();


  //--------- Data :
  CATBoolean _OStreamImplHasBeenCreated;
  CATSobOStreamImpl* _ostreamImpl;
  unsigned int _ID;
};


extern ExportedByCATSobObjects CATSobOStream& sobout;
#define sobendl "\n"


#endif


