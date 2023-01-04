
//===============================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved 
//===============================================================================
// CATSmoEvalLocation.h
//===============================================================================
//
// Usage notes: Class to handle the Location SobMesh
//===============================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved 
// 
// 30-04-09 RBD Embellissement divers et constructeur a partir d'une face et un sommet
// 21-11-07 MMO Correction des erreurs BAD004 (headerruler)
// ??-07-07 RNO Creation
//===============================================================================
#ifndef CATSmoEvalLocation_H
#define CATSmoEvalLocation_H

#include "CATIAV5Level.h"

//Pour l'export
#include "CATSmoOperators.h"

// #include "CATSobFace.h" // MMO BAD004
// #include "CATSobMesh.h" // MMO BAD004

class CATSobFace; // MMO BAD004
class CATSobVertex; // MMO BAD004


class ExportedByCATSmoOperators CATSmoEvalLocation
{
public:
// Constructor(s)
  inline CATSmoEvalLocation(CATSobFace* iSobFace, const int iLevel, const int iU, const int iV, const int iDaughter=0);
  inline CATSmoEvalLocation();
  CATSmoEvalLocation(CATSobFace* iSobFace, CATSobVertex* iSobVertex, const int iLevel = 0);
  // Destructor
  inline ~CATSmoEvalLocation();
  // Copy constructor 
  inline CATSmoEvalLocation (const CATSmoEvalLocation &);

  // Get
  inline CATSobFace* GetFace() const;
  inline int GetLevel() const;
  inline int GetU() const;
  inline int GetV() const;
  inline int GetDaughter() const;
  // Set
  inline void SetFace( CATSobFace * iSobFace);
  inline void SetLevel(const int iLevel);
  inline void SetU(const int iu);
  inline void SetV(const int iv);
  inline void SetDaughter(const int iDaughter);
  
  
public:
  CATSobFace * _SobFace; 
  int _Level;
  int _u, _v;
  int _Daughter;
};


//----------------------------------------------
// Methodes inlines
//----------------------------------------------
// Constructor(s)
inline CATSmoEvalLocation::CATSmoEvalLocation(CATSobFace* iSobFace, const int iLevel, const int iU, const int iV, const int iDaughter):
  _SobFace(iSobFace),
  _Level(iLevel),
  _u(iU),
  _v(iV),
  _Daughter(iDaughter)
{
}


inline CATSmoEvalLocation::CATSmoEvalLocation():
  _SobFace(0),
  _Level(0),
  _u(0),
  _v(0),
  _Daughter(0)
{
}

// Destructor
inline CATSmoEvalLocation::~CATSmoEvalLocation()
{
  _SobFace=0;
}

// Copy constructor 
inline CATSmoEvalLocation::CATSmoEvalLocation (const CATSmoEvalLocation & Loc)
{
  _SobFace=Loc._SobFace;
  _Level=Loc._Level;
  _u=Loc._u;
  _v=Loc._v;
  _Daughter=Loc._Daughter;
  
}

// Get
inline CATSobFace* CATSmoEvalLocation::GetFace() const 
{
  return(_SobFace);
}
inline int CATSmoEvalLocation::GetLevel() const 
{
  return(_Level);
}
inline int CATSmoEvalLocation::GetU() const 
{
  return(_u);
}
inline int CATSmoEvalLocation::GetV() const 
{
  return(_v);
}
inline int CATSmoEvalLocation::GetDaughter() const 
{
  return(_Daughter);
}

// Set
inline void CATSmoEvalLocation::SetFace( CATSobFace * iSobFace)  
{
  _SobFace=iSobFace;
}
inline void CATSmoEvalLocation::SetLevel(const int iLevel)   
{
  _Level=iLevel;
}
inline void CATSmoEvalLocation::SetU(const int iu)   
{
  _u=iu;
}
inline void CATSmoEvalLocation::SetV(const int iv)  
{
  _v=iv;
}
inline void CATSmoEvalLocation::SetDaughter(const int iDaughter)   
{
  _Daughter=iDaughter;
}

#endif

