//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobQuadOperator.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// May,       2004 : RAQ : Prise en compte des mesh Tri/Quad
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// September, 2003 : JCV : Gestion Diag
// Marsh    , 2003 : JCV : Creation
//====================================================================
#ifndef CATSobQuadOperator_H
#define CATSobQuadOperator_H

//Pour l'export
#include "CATSobOperators.h"

//Divers
#include "CATSobDiag.h"
#include "CATBoolean.h"
#include "CATLib.h"

class CATSobMesh;


class ExportedByCATSobOperators CATSobQuadOperator
{
public:

  CATSobQuadOperator(CATSobMesh* iMesh);

  virtual ~CATSobQuadOperator();

  virtual int IsAQuadMesh() const = 0;

  virtual int IsATriQuadMesh() const = 0;

  virtual CATSobDiag Run() = 0;

  virtual CATSobMesh* GetQuadMesh() = 0;

private:

  //Copy constructor and equal operator
  CATSobQuadOperator (CATSobQuadOperator &);
  CATSobQuadOperator& operator=(CATSobQuadOperator&);
};


ExportedByCATSobOperators
CATSobDiag CATSobCreateQuadMesh(CATSobMesh* iMesh, CATSobMesh*& oQuadMesh);

ExportedByCATSobOperators
CATSobDiag CATSobCreateTriQuadMesh(CATSobMesh* iMesh, CATSobMesh*& oTriQuadMesh);

ExportedByCATSobOperators
CATBoolean CATSobIsAQuadMesh(CATSobMesh* iMesh);

ExportedByCATSobOperators
CATBoolean CATSobIsATriQuadMesh(CATSobMesh* iMesh);


//------ DEPRECATED: Do not use anymore, for compilation purpose only
#ifdef _WINDOWS_SOURCE
ExportedByCATSobOperators
CATSobDiag __declspec(deprecated("Deprecated subdiv method, use CATSobCreateQuadMesh(CATSobMesh* iMesh, CATSobMesh*& oQuadMesh) instead")) CATSobCreateQuadMesh(CATSobMesh* iMesh);
#else
ExportedByCATSobOperators
CATSobDiag CATSobCreateQuadMesh(CATSobMesh* iMesh);
#endif  //#ifdef _WINDOWS_SOURCE


#endif
