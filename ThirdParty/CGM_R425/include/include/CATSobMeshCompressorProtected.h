//====================================================================
// Copyright Dassault Systemes Provence 2006, All Rights Reserved
//====================================================================
//
// CATSobMeshCompressorProtected.cpp
//
//====================================================================
//
// Usage notes: ************* DON'T INCLUDE THIS HEADER *************
//              Operateur de compression d'un base mesh polygonal
//              pour usage restreint (stream des CATSubdivMesh)
//
//====================================================================
// October,   2006 : RAQ : Création
// April,     2010 : RAQ : StreamLevel pour RI IR-045827V6R2011x
// 08.02.2017 : RAQ : Correction AddRef/Release pour IR-500221
//====================================================================
#ifndef CATSobMeshCompressorProtected_H
#define CATSobMeshCompressorProtected_H

//Pour l'export
#include "CATSobObjects.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobFace.h"
#include "CATSobListOfFace.h"
#include "CATSobVertex.h"
#include "CATSobListOfVertex.h"

//Divers
#include "CATBoolean.h"
#include "CATSobMeshCompressorLevel.h"

class CATSobStream;
class CATSobMesh;
class CATSobMeshCompressorCx2;

class ExportedByCATSobObjects CATSobMeshCompressorProtected
{
public:

  //Constructeur
  CATSobMeshCompressorProtected(CATSobStream* iStream);

  //Destructeur
  virtual ~CATSobMeshCompressorProtected();

  //Mode de compression
  void SetCompressMode(CATSobMesh* iMeshToCompress);

  //Mode de décompression
  void SetUncompressMode(const CATBoolean iMustSetNonModifiedFlagOnCells = FALSE);

  //Set d'une version de stream
  void SetLevelForStream(const CATSobMeshCompressorLevel iRequestedStreamLevel);

  //Run de l'opérateur
  CATSobDiag Run();

  //Diag de l'opérateur
  CATSobDiag GetDiag() const { return _Diag; }

  //Obtention du mesh décompressé, l'appelant doit faire un Release
  CATSobMesh* GetMesh();

  //Obtention des faces dans l'ordre de compression
  CATSobDiag GetOrderedStreamedFaces(CATLISTP(CATSobFace)& oOrderedStreamedFaces);

  //Obtention des vertex dans l'ordre de compression
  CATSobDiag GetOrderedStreamedVertices(CATLISTP(CATSobVertex)& oOrderedStreamedVertices);

private:

  //Mise à zéro des flag de modification des cellules
  CATSobDiag SetNonModifiedFlagOnCells();


  //------ Data:
  CATSobDiag _Diag;
  CATSobStream* _Stream;
  CATBoolean _IsCompressionMode, _SetNonModifiedFlagOnCells, _RequestedStreamLevelHasBeenSet;
  CATSobMeshCompressorCx2* _CompressorOperator;
  CATSobMesh* _MeshToCompress;
  CATSobMeshCompressorLevel _RequestedStreamLevel;
};

#endif


