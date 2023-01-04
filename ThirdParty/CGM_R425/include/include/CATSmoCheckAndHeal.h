//=======================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//=======================================================================
//
// CATSmoCheckAndHeal.h
//
//=======================================================================
//
// Usage notes: Detection et reparation des anomlaies de connexite sans garantie de resultat
// Verification de la connexite et suppression des faces disconnectees
// Attention le check ne donne pas tous les problemes mais seulement les premiers rencontres
//
//
// !!!! Le Mesh abime ne pouvant etre duplique le Heal travaille directement sur le Mesh en entree NO COPY
// 
//=======================================================================
// 24/07/2009 : RNO : Creation
//=======================================================================




#ifndef CATSmoCheckAndHeal_H
#define CATSmoCheckAndHeal_H

#include "CATSmoOperators.h"

#include "CATSobListOfFace.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"

#include "CATSobDiag.h"

class CATSobFace;
class CATSobMesh;


class ExportedByCATSmoOperators CATSmoCheckAndHeal
{
public:

  //Constructeur
  CATSmoCheckAndHeal(CATSobMesh * Mesh);

  //Destructeur
  ~CATSmoCheckAndHeal();

  //Run de l'opérateur return (CATSobDiag_OK) if the Mesh is OK
  CATSobDiag Check();
    //Run de l'opérateur HEAL return CATSobDiag_OK has been correctly healed
  // !!!! Le Mesh abime ne pouvant etre duplique le Heal travaille directement sur le Mesh en entree NO COPY
  CATSobDiag Heal();

  inline void GetBorderEdges(CATLISTP(CATSobEdge) & oBorderEdge );
  inline void GetPbFaces(CATLISTP(CATSobFace) & oPbFaces );
  inline void GetPbVertices(CATLISTP(CATSobVertex) & oPbVertices );
  inline void GetPbEdges(CATLISTP(CATSobEdge) & oPbEdges );
  inline void GetUnConnectedFaces(CATLISTP(CATSobFace) & oUnConnectedFaces );
  
  
private:

  void Init();
  CATSobDiag CheckInternal(CATSobMesh * iMesh);
  CATSobMesh * _InputMesh;
  CATLISTP(CATSobEdge) _BorderEdges;
  CATLISTP(CATSobFace)_PbFaces;
  CATLISTP(CATSobFace)_UnConnectedFaces;
  CATLISTP(CATSobFace)_UnDiscovFaces;
  CATLISTP(CATSobEdge) _PbEdges;
  CATLISTP(CATSobVertex) _PbVertices;


};

void CATSmoCheckAndHeal::GetBorderEdges(CATLISTP(CATSobEdge) & oBorderEdge )
{
  oBorderEdge=_BorderEdges;
}
inline void CATSmoCheckAndHeal::GetPbFaces(CATLISTP(CATSobFace) & oPbFaces )
{
  oPbFaces=_PbFaces;
}

inline void CATSmoCheckAndHeal::GetPbVertices(CATLISTP(CATSobVertex) & oPbVertices )
{
  oPbVertices=_PbVertices;
}
inline void CATSmoCheckAndHeal::GetPbEdges(CATLISTP(CATSobEdge) & oPbEdges )
{
  oPbEdges=_PbEdges;
}
inline void CATSmoCheckAndHeal::GetUnConnectedFaces(CATLISTP(CATSobFace) & oUnConnectedFaces )
{
  oUnConnectedFaces=_UnConnectedFaces;
}





#endif
