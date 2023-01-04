//=======================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//=======================================================================
//
// CATSobCell.h
//
//=======================================================================
//
// Usage notes:
//
//=======================================================================
// November,  2007 : RNO : Nouvelle gestion des attributs (MultiAttributs)  
// December,  2006 : RAQ : Ajout IsMeshFrozen
// February,  2005 : RAQ : Suppression champ _MyDiag, ajout SetDiag(...)
// October,   2004 : RAQ : Optimisation mémoire
// May,       2004 : RAQ : Ajout tags de modification
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// July,      2003 : JCV : le poids accessible uniquement dans CATVertex
// Marsh,     2003 : JCV : Creation CATSobCell.h
//=======================================================================
#ifndef CATSobCell_H
#define CATSobCell_H

#include "CATSobObjects.h"

#include "CATSobMesh.h"
#include "CATSobListOfCell.h"

#include "CATSobDiag.h"

#include "CATBoolean.h"
#include <math.h>

#include "CATSobListOfAttributes.h"
#include "CATSobAttributes.h"

#include "CATSobAttributesId.h"

class ExportedByCATSobObjects CATSobCell
{
public:
  
/** 
 * Build a Cell in a mesh
 *
 * @param iMesh
 * The pointer on the mesh where is the cell
 *
 */
  CATSobCell(CATSobMesh* iMesh);

/** 
 * @nodoc
 */
  virtual ~CATSobCell();

/** 
 * Gets the number of references of this Cell
 * (number of use in the mesh)
 *
 * @return
 * The number of references
 * if the number of references is nul, the cell can be delete.
 */
  int GetNbRef() const;

/**
 * Gets the type of 'this' cell
 *
 * @return
 * The type of 'this' cell
 */
  virtual CATSobCellType GetCellType() const = 0;

/**
 * Checks the type of 'this' cell
 *
 * @param iCellType
 * The type to check
 *
 * @return
 * TRUE if 'this' cell has type iCellType
 */
  virtual CATBoolean IsATypeOf(const CATSobCellType iCellType) const = 0;

/** 
 * Gets the mesh owning the cell
 *
 * @return
 * The pointer on the mesh
 */
 CATSobMesh* GetMesh() const;

/** 
 * Indicates if the cell has been modified
 *
 * @return
 * 0 if the cell is not modified
 */
  short IsModified() const;

/** 
 * Imposes a modification on the cell
 *
 * @param iNbModif
 * the value of the modification
 * 0 -> reset modifications
 */
  virtual void SetModif(const short iNbModif = 0);

/** 
 * Gets the information on the cell
 *
 * @return
 * the information value.
 * Use @href CATSobDiag include to see all the information values.
 */
  CATSobDiag GetDiag() const;

  //////////////////////////////////////////////////////////////////////////
  // Relations d'héritage
  //////////////////////////////////////////////////////////////////////////

/** *********** DEPRECATED ***********
 * Imposes the father of the cell
 * (using by subdivision operator)
 *
 * @param iFather
 * The pointer of the father cell
 */
  void SetFather(CATSobCell* iFather);

/** *********** DEPRECATED ***********
 * Gets the father of the cell
 * (using by subdivision operator)
 *
 * @return
 * The pointer of the father cell
 */
  CATSobCell* GetFather() const;

/** *********** DEPRECATED ***********
 * Imposes a son of the cell
 * (using by subdivision operator)
 *
 * @param iSon
 * The pointer of the son cell
 */
  void SetSon(CATSobCell* iSon);

/** *********** DEPRECATED ***********
 * Gets the number of sons of the cell
 * (using by subdivision operator)
 *
 * @return
 * The number of sons of the cell
 */
  int GetNbOfSons() const;

/** *********** DEPRECATED ***********
 * Gets all sons of the cell
 * (using by subdivision operator)
 *
 * @return
 * The pointer of the list of sons cells
 */
  CATLISTP(CATSobCell)* GetSons() const;

/** *********** DEPRECATED ***********
 * Gets one son of the cell
 * (using by subdivision operator)
 *
 * @param iIndex
 * the index of the son in the list
 *
 * @return
 * The pointer of the son cell
 */
  CATSobCell* GetSon(const int iIndex) const;

/**
 * Get the value of the highest subdivision
 * level already computed for this object.
 *
 * @return
 * The value of the subdivision level
 **/
  short GetMaxLevelComputed() const;

  
/**
 * Set the value of the highest subdivision
 * level already computed for this object.
 *
 * @param iMaxLevelComputed
 * The value of the subdivision level
 **/
  void SetMaxLevelComputed(const short iMaxLevelComputed);


/**
 * @nodoc
 * When doing Mesh->GetAllxxx where xxx could be either Faces, Vertices, or Edges
 * you can use the optional computation of the cell rank.
 * The Set allow to store in the cell its rank in the List got by GatAllxxx.
 * Be sure that the Mesh has not changed between SetCellRank and GetCellRank
 * If you wish to use the iSafeRankKey, you should free your Rank Key via FreeRankKey() on this cell or on the whole Mesh
 * * @return
 * The rank of the cell in the List.
 **/
  unsigned int GetCellRank(CATLONGPTR iSafeKey=0);
/**
 * @nodoc
 **/
  void SetCellRank(unsigned int iRank,CATLONGPTR iSafeKey=0);
  
  //Free the Key used to store the rank on this cell
  void FreeRankKey(CATLONGPTR iSafeKey);
  
  
  void SetCutFather(CATSobCell* iCutFather);

  CATSobCell* GetCutFather() const;

  CATLISTP(CATSobCell)* GetCutSons() const;

  void SetCutSon(CATSobCell* iCutSon);

  void SetUseStaticBuffer(const CATBoolean iOnOff = TRUE);
  CATBoolean GetUseStaticBuffer() const;

  void SetIsOnLocalMesh(const CATBoolean iIsOnLocalMesh = TRUE);
  CATBoolean IsOnLocalMesh();


  //---------------------------- Methods used for local frame ----------------------------//
  static void Orthonormalize2D(double*& iFirstVector, double*& iSecondVector);
  static void Orthonormalize3D(double*& iFirstVector, double*& iSecondVector, double*& iThirdVector);
  //inline static void GetNorm(double*& iVector, double& oNorm);
  inline static void Normalize(double*& iVector);
  inline static void CrossProduct(double*& iFirstVector, double*& iSecondVector, double*& iThirdVector);
  inline static void AddCrossProduct(double*& iFirstVector, double*& iSecondVector, double*& iWhereToAddCrossProduct);
  inline static void EvalLocalVectorInGlobalFrame(double*& iLocalFrame, double*& iLocalVector, double*& ioGlobalVector);
  inline static void EvalGlobalVectorInLocalFrame(double*& iLocalFrame, double*& iGlobalVector, double*& ioLocalVector);
  //--------------------------------------------------------------------------------------//


  /* DO NOT USE */
  void CopyFlag(const CATSobCell* iCellToCopyFlag);

/** 
 * Removes links with father and sons
 */
  void RemoveLinks();

  /////////////////////////////
  // Gestion des attributs
  /////////////////////////////
  void AddAttribute(CATSobAttributes * iAttribute);
  CATSobAttributes * GetAttribute(CATSobAttributesId * iID, CATLONGPTR iName=0);
  void ReleaseAttr(CATSobAttributes * & ioAttribute);
  const CATLISTP(CATSobAttributes)* GetAllAttributes() const;
  
  
protected:

  void SetDiag(const CATSobDiag iDiag);
  
  inline int Power(const int iX, const int iExp) const { return (1 << iExp); }

  CATBoolean IsMeshFrozen() const;


  //--------- Data:
  unsigned int _RankInList;
  int _NbRef;
  CATSobMesh* _MySobMesh;
  unsigned char _MaxLevelComputed;

  //Codage de données binaires, ce champ est partagé par les objets Face/Edge/Vertex:
  // Bit 0x01:	Vertex: IsModified (Modifié 1 / Non modifié 0)
  //            Edge:   IsModified (Modifié 1 / Non modifié 0)
  //            Face:   IsModified (Modifié 1 / Non modifié 0)
  //
  // Bit 0x02:  Vertex: Not Used
  //            Edge:   Not Used
  //            Face:   IsSurfaceModified pour les Faces quad ou pour la 1° surface d'une face triangulaire
  //
  // Bit 0x04:  Vertex: Not Used
  //            Edge:   Not Used
  //            Face:   IsSurfaceModified pour la 2° surface d'une face triangulaire
  //
  // Bit 0x08:  Vertex: Not Used
  //            Edge:   Not Used
  //            Face:   IsSurfaceModified pour la 3° surface d'une face triangulaire
  //
  // Bit 0x10:  Vertex: Not Used
  //            Edge:   Not Used
  //            Face:   IsAHole pour les faces et la compression: précise que cette face n'est ajoutée que le temps de la compression.
  //
  // Bit 0x20:  Vertex: Catmull Clark subdivision (0) / Loop Subdivision (1)
  //            Edge:   IsEdgeCut pour les Edges, si l'edge n'est pas le support de la subdivision lorsqu'elle est coupée
  //            Face:   Not Used
  //
  // Bit 0x40:  Vertex: SetUseStaticBuffer: Utilisation du buffer statique (1)
  //            Edge:   SetUseStaticBuffer: Utilisation du buffer statique (1)
  //            Face:   SetUseStaticBuffer: Utilisation du buffer statique (1)
  //
  // Bit 0x80:  Vertex: IsOnLocalMesh
  //            Edge:   IsOnLocalMesh
  //            Face:   IsOnLocalMesh
  //
  unsigned char _BinaryInfos;

  

private:
  //Les attributs
  CATLISTP(CATSobAttributes) * _AllCellAttributes;

  // Copy constructor and equal operator
  CATSobCell(CATSobCell&);
  CATSobCell& operator=(CATSobCell&);

  CATSobCell* _Father;
  CATLISTP(CATSobCell)* _Sons;

  //Pour les découpes locales
  CATSobCell* _CutFather;
  CATLISTP(CATSobCell)* _CutSons;
};


inline void CATSobCell::SetDiag(const CATSobDiag iDiag)
{
  if(_MySobMesh) _MySobMesh->SetDiag(iDiag);
}


inline CATBoolean CATSobCell::IsMeshFrozen() const
{
  return (_MySobMesh!=0) ? _MySobMesh->IsMeshFrozen() : TRUE;
}


inline void CATSobCell::SetUseStaticBuffer(const CATBoolean iOnOff)
{
  if(iOnOff)
    _BinaryInfos|=0x40;
  else
    _BinaryInfos&=0xBF;
}


inline CATBoolean CATSobCell::GetUseStaticBuffer() const
{
  return (_BinaryInfos&0x40) ? TRUE : FALSE;
}


inline void CATSobCell::SetIsOnLocalMesh(const CATBoolean iIsOnLocalMesh)
{
  if(iIsOnLocalMesh)
    _BinaryInfos|=0x80;
  else
    _BinaryInfos&=0x7F;
}


inline CATBoolean CATSobCell::IsOnLocalMesh()
{
  return (_BinaryInfos & 0x80) ? TRUE : FALSE;
}

inline int CATSobCell::GetNbRef() const
{
  return (_NbRef);
}

inline CATSobCell * CATSobCell::GetFather () const
{
  return (_Father);
}

inline void CATSobCell::SetFather(CATSobCell * iFather)
{
  _Father = iFather;
}

/*---------------------------------- Nouvelles méthodes pour le LocalCut--------------------------------*/
inline void CATSobCell::SetCutFather(CATSobCell* iCutFather)
{
  _CutFather = iCutFather;
}

inline CATSobCell* CATSobCell::GetCutFather() const
{
  return _CutFather;
}

inline CATLISTP(CATSobCell)* CATSobCell::GetCutSons() const
{
  return _CutSons;
}

/*
inline void CATSobCell::GetNorm(double*& iVector, double& oNorm)
{
  oNorm=sqrt(iVector[0]*iVector[0]+iVector[1]*iVector[1]+iVector[2]*iVector[2]);
}
*/

inline void CATSobCell::Normalize(double*& iVector)
{
  double Norme=sqrt((iVector[0]*iVector[0])+(iVector[1]*iVector[1])+(iVector[2]*iVector[2]));
  iVector[0]/=Norme;
  iVector[1]/=Norme;
  iVector[2]/=Norme;
}


inline void CATSobCell::CrossProduct(double*& iFirstVector,
                                     double*& iSecondVector,
                                     double*& iThirdVector)
{
  iThirdVector[0]=iFirstVector[1]*iSecondVector[2]-iFirstVector[2]*iSecondVector[1];
  iThirdVector[1]=iFirstVector[2]*iSecondVector[0]-iFirstVector[0]*iSecondVector[2];
  iThirdVector[2]=iFirstVector[0]*iSecondVector[1]-iFirstVector[1]*iSecondVector[0];
}


inline void CATSobCell::AddCrossProduct(double*& iFirstVector,
                                        double*& iSecondVector,
                                        double*& iWhereToAddCrossProduct)
{
  iWhereToAddCrossProduct[0]+=iFirstVector[1]*iSecondVector[2]-iFirstVector[2]*iSecondVector[1];
  iWhereToAddCrossProduct[1]+=iFirstVector[2]*iSecondVector[0]-iFirstVector[0]*iSecondVector[2];
  iWhereToAddCrossProduct[2]+=iFirstVector[0]*iSecondVector[1]-iFirstVector[1]*iSecondVector[0];
}


inline void CATSobCell::EvalLocalVectorInGlobalFrame(double*& iLocalFrame, double*& iLocalVector, double*& ioGlobalVector)
{
  ioGlobalVector[0]=iLocalFrame[0]*iLocalVector[0]+iLocalFrame[3]*iLocalVector[1]+iLocalFrame[6]*iLocalVector[2];
  ioGlobalVector[1]=iLocalFrame[1]*iLocalVector[0]+iLocalFrame[4]*iLocalVector[1]+iLocalFrame[7]*iLocalVector[2];
  ioGlobalVector[2]=iLocalFrame[2]*iLocalVector[0]+iLocalFrame[5]*iLocalVector[1]+iLocalFrame[8]*iLocalVector[2];
}


inline void CATSobCell::EvalGlobalVectorInLocalFrame(double*& iLocalFrame, double*& iGlobalVector, double*& ioLocalVector)
{
  ioLocalVector[0]=iLocalFrame[0]*iGlobalVector[0]+iLocalFrame[1]*iGlobalVector[1]+iLocalFrame[2]*iGlobalVector[2];
  ioLocalVector[1]=iLocalFrame[3]*iGlobalVector[0]+iLocalFrame[4]*iGlobalVector[1]+iLocalFrame[5]*iGlobalVector[2];
  ioLocalVector[2]=iLocalFrame[6]*iGlobalVector[0]+iLocalFrame[7]*iGlobalVector[1]+iLocalFrame[8]*iGlobalVector[2];
}


#endif

