//======================================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//======================================================================================
//
// CATSobOStreamImpl.h
//
//======================================================================================
//
// Usage notes : Implementation de CATSobOStream
//
//======================================================================================
// October,   2010 : RAQ : Creation
//======================================================================================
#ifndef CATSobOStreamImpl_H
#define CATSobOStreamImpl_H

//Pour l'export
#include "CATSobObjects.h"


class ExportedByCATSobObjects CATSobOStreamImpl
{
public:

  //Constructeur
  CATSobOStreamImpl();

  //Gestion des références
  virtual int AddRef();
  virtual void Release();

  //Les méthodes de print
  virtual void operator<<(const char*) {}
  virtual void operator<<(const char) {}
  
  virtual void operator<<(const short) {}
  virtual void operator<<(const int) {}
  virtual void operator<<(const float) {}
  virtual void operator<<(const double) {}


protected:

  //Destructeur
  virtual ~CATSobOStreamImpl();


private:

  //-------- Data:
  int _RefCounter;

};

#endif


