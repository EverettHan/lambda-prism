//===========================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//===========================================================================
//
// CATSobMeshFromGridOperator.h
//
//===========================================================================
//
// Usage notes: Creates a mesh from a grid of points
//
//===========================================================================
// 03.10.2016 : Implementation creation
// 29.07.2015 : RAQ : Possibilité de rajouter des grilles dans le même mesh en multi-run
// November,   2004 : RAQ : Création
//===========================================================================
#ifndef CATSobMeshFromGridOperator_H
#define CATSobMeshFromGridOperator_H

//Pour l'export
#include "CATSobOperators.h"

//Subdivision
#include "CATSobDiag.h"
#include "CATSobListOfVertex.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"

//Divers
#include "CATBoolean.h"
#include "CATLib.h"

//STL
class CATSobMesh;
class CATSobVertex;
class CATSobFace;


//----------------------------------------------------------------
// ------------- About mesh creation from a grid of points:
// 
// The points must be organized the following way:
//
//                      From left to right and from down to up, ie:
//                      (0, 0)  (1, 0)...........(NbCols-1, 0)
//         _________    (0, 1)...................(NbCols-1, 1)
//        |.........|   ---------------------------------------
//        |.........|   (0, NbRows-1)............(NbCols-1, NbRows-1)
//        |.........| 
//        |.........|
//        |.........|
//   /|\  |_________|
//    |      
//    v
//      u---->
//
//
// ----- For some rows of the grid to be sharp:
// void SetRowsSharp(const int* iRowsIndex, const int iNbIndex);
// iRowsIndex is an arry of integer containing the index of the rows to be sharp, ie:
// 0 < iRowsIndex < NbRows-1
// iNbIndex is the number of rows to be sharp.
//
// ----- For some columns of the grid to be sharp:
// void SetColumnsSharp(const int* iColumnsIndex, const int iNbIndex);
// iRowsIndex is an arry of integer containing the index of the columns to be sharp, ie:
// 0 < columns < NbCols-1
// iNbIndex is the number of columns to be sharp.
//
//----------------------------------------------------------------

class ExportedByCATSobOperators CATSobMeshFromGridOperator
{
public:

/**
 * Set the mesh if the grid is to be appened in an existing mesh.
 *
 * @param ipMesh
 * The mesh in which the grid will be added.
 **/
  virtual void SetMesh(CATSobMesh* ipMesh, const double iConfusionTolerance = 0.001 ) = 0;  //@NumValidated RAQ, pas d'accès à la factory

/**
 * Closes the mesh along the u-direction, in other words it produces a cylinder mesh
 * which axis direction is v.
 * This method can not be called with SetVClosed.
 **/
  virtual void SetUClosed() = 0;

/**
 * Closes the mesh along the v-direction, in other words it produces a cylinder mesh
 * which axis direction is u.
 * This method can not be called with SetUClosed.
 **/
  virtual void SetVClosed() = 0;

/**
 * Sets some rows as sharp
 *
 * @param iRowsIndex
 * An array of integers identifying the rows to be sharp
 * @param iNbIndex
 * The number of rows to be sharp
 **/
  virtual void SetRowsSharp(const int* iRowsIndex, const int iNbIndex) = 0;

/**
 * Sets some columns as sharp
 *
 * @param iColumnsIndex
 * An array of integers identifying the columns to be sharp
 * @param iNbIndex
 * The number of columns to be sharp
 **/
  virtual void SetColumnsSharp(const int* iColumnsIndex, const int iNbIndex) = 0;

/**
 * Adds a new grid to the mesh and check cells confusion to avoid creating invalid topology.
 * The operator needs to be re-run.
 *
 * @param iArrayOfPoints
 * An array of points coords, see above for organisation
 * @param iNbRows
 * The number of vertices rows
 * @param iNbCols
 * The number of vertices columns
 * @param iConfusionValue
 * A tolerance to check vertices confusion
 **/
  virtual void AddGrid(const double* iArrayOfPoints, const int iNbRows, const int iNbCols,
                       const double iConfusionValue = 0.001) = 0;	//@NumValidated (no access to factory tolerance from here)

/**
 * Constructs the mesh
 *
 * @return
 * CATSobDiag_OK if no error, else see CATSobDiag.h
 **/
  virtual CATSobDiag Run() = 0;

/**
 * Gets the mesh
 *
 * @return
 * A pointer to the mesh if no error, else NULL
 **/
  virtual CATSobMesh* GetMesh() = 0;

  //Get all created horizontal edges (along the rows)
  virtual const CATLISTP(CATSobEdge)& GetNewHorizontalEdges() const = 0;

  //Get all created faces
  virtual void GetNewFaces(CATLISTP(CATSobFace)& oListOfFaces) const = 0;

  //Get all the vertices really created by the operator.
  //Remind that due to the confusion tolerance some vertices can be re-used and thus won't appear as created ones.
  virtual const CATLISTP(CATSobVertex)& GetNewVertices() const = 0;

  //Check whether the mesh has been reversed during the 'Run'
  virtual CATBoolean GetMeshHasBeenReversed() const = 0;


  virtual ~CATSobMeshFromGridOperator() {}

protected:

  CATSobMeshFromGridOperator() {}

private:
  
  //Copy constructor and equal operator
  CATSobMeshFromGridOperator(CATSobMeshFromGridOperator&);
  CATSobMeshFromGridOperator& operator=(CATSobMeshFromGridOperator&);

};


/**
 * Builds the operator
 *
 * @param iArrayOfPoints
 * The grid of points, see above
 * @param iNbRows
 * The number of rows in the grid
 * @param iNbCols
 * The number of columns in the grid
 *
 * @return
 * A pointer to the operator
 **/
ExportedByCATSobOperators
  CATSobMeshFromGridOperator* CATSobCreateMeshFromGridOperator(const double* ipArrayOfPoints,
                                                               const int     iNbRows,
                                                               const int     iNbCols);



#endif


