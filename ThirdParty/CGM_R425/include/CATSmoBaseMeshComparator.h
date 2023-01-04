//===========================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//===========================================================================
//
// CATSmoBaseMeshComparator.h
//
//===========================================================================
//
// Usage notes: Comparaison de deux base mesh (style BodyMapping).
//
//===========================================================================
// January,  2010 : RAQ : Creation
//===========================================================================
#ifndef CATSmoBaseMeshComparator_H
#define CATSmoBaseMeshComparator_H

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATSobHashTableWithAssoc.h"


class CATSobMesh;
class CATSobVertex;



class ExportedByCATSmoOperators CATSmoBaseMeshComparator
{
public:

  enum ComparatorResult
  {
    Comparator_Identical,
    Comparator_InternalError,
    Comparator_Error_NotSameNumberOfVertices,
    Comparator_Error_NotSameNumberOfEdges,
    Comparator_Error_NotSameNumberOfFaces,
    Comparator_Error_EdgesNotMapped,
    Comparator_Error_FacesNotMapped,
    Comparator_Error_VerticesNotMapped,
    Comparator_Error_NotSameVertexWeight,
    Comparator_Error_NotSameEdgeWeight,
    Comparator_Error_NotSameLODDeepness,
    Comparator_Error_DetailsNotMapped
  };

  //Constructeur
  CATSmoBaseMeshComparator();

  //Destructeur
  ~CATSmoBaseMeshComparator();

  //Run de la comparaison
  ComparatorResult Run(const CATSobMesh* iRefMesh, const CATSobMesh* iMeshToCompare, const double iTolerance = 0.001);


private:

  //Set du diag
  ComparatorResult SetComparatorResult(const ComparatorResult iComparatorResult);

  //Initialisation
  void Initialize(const CATSobMesh* iRefMesh, const CATSobMesh* iMeshToCompare, const double iTolerance);

  //Check du nombre de cellules
  ComparatorResult CheckCellsNumber();

  //Identification des cellules
  ComparatorResult MapCells();

  //Identification des détails
  ComparatorResult MapDetails();

  //Calculs de distance
  double SquareDistanceBetween(const CATSobVertex* iVertex1, const CATSobVertex* iVertex2) const;
  double SquareDistanceBetween(const double* iPoint1, const double* iPoint2) const;



  //-------- Data:
  const CATSobMesh *_RefMesh, *_MeshToCompare;
  ComparatorResult _ComparatorResult;
  double _Tolerance;
  CATSobHashTableWithAssoc _RefVerticesMappingHashTable;  //A partir d'un vertex du mesh de référence, obtention du vertex dans l'autre mesh.
  CATSobHashTableWithAssoc _RefEdgesMappingHashTable;     //A partir d'une edge du mesh de référence, obtention de l'edge dans l'autre mesh.
  CATSobHashTableWithAssoc _RefFacesMappingHashTable;     //A partir d'une face du mesh de référence, obtention de la face dans l'autre mesh.
};


#endif

