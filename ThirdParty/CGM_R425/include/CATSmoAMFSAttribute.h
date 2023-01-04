//========================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved
//========================================================================================
//
// CATSmoAMFSAttribute.h
//
//========================================================================================
//
// Usage notes: Attributes used by CATSmoAdvancedMeshFromSubdivisionOperator to retrieve
//              the ancestor cell of each vertex of the sub mesh.
//
//========================================================================================
// October,   2008 : RAQ : Création
//========================================================================================
#ifndef CATSmoAMFSAttribute_H
#define CATSmoAMFSAttribute_H

//Pour l'export
#include "CATSmoOperators.h"

//Structure subdivision
#include "CATSobAttributes.h"
#include "CATSobDefine.h"
#include "CATSobCell.h"

class CATSobFace;
class CATSobEdge;
class CATSobVertex;


CATDECLARESOBATTRIBUTE(CATSmoAMFSAttribute, CATSmoAMFSAttributeID)

class ExportedByCATSmoOperators CATSmoAMFSAttribute: public CATSobAttributes
{
public:

  //Constructeurs
  CATSmoAMFSAttribute(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const int iDaughterFaceIndex = 0);
  CATSmoAMFSAttribute(CATSobEdge* iEdge, const int iU, const int iLevel);
  CATSmoAMFSAttribute(CATSobVertex* iVertex, const int iLevel);

  //Obtention du type de cellule parent
  CATSobCellType GetParentCellType() const;

  //Obtention du level
  int GetLevel() const;

  //Obtention des infos sur la cellule parent
  CATSobFace* GetParentFace(int& oU, int& oV, int& oDaughterFaceIndex);
  CATSobEdge* GetParentEdge(int& oU);
  CATSobVertex* GetParentVertex();


protected:

  //Destructeur
  virtual ~CATSmoAMFSAttribute();


private:

  //--------------- Data:
  CATSobCell* _ParentCell;
  int _U, _V;
  char _DaughterFaceIndex, _Level;

};


//-------------------------------------
// Obtention du type de cellule parent
//-------------------------------------
inline CATSobCellType CATSmoAMFSAttribute::GetParentCellType() const
{
  return (_ParentCell!=0) ? _ParentCell->GetCellType() : CATSobUndefType;
}


//---------------------
// Obtention du level
//---------------------
inline int CATSmoAMFSAttribute::GetLevel() const
{
  return (int) _Level;
}




#endif


