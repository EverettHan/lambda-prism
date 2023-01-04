//========================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved
//========================================================================
//
// CATSubdivMeshGeo.h
//
//========================================================================
//
// Usage notes: Geometric part of the CATSubdivMesh object,
//              Objet usable since R20/R207
//
//========================================================================
// May,    2008 : RAQ : Creation
//========================================================================
#ifndef CATSubdivMeshGeo_H
#define CATSubdivMeshGeo_H

//Version
#include "CATIACGMLevel.h"

#if defined CATIAV5R19 || defined CATIAR206

//Pour l'export
#include "ExportedByCATGMGeometricInterfaces.h"

//Classe mère
#include "CATGeometry.h"

class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobVertex;
class CATBody;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSubdivMeshGeo ;
#else
extern "C" const IID IID_CATSubdivMeshGeo ;
#endif


class ExportedByCATGMGeometricInterfaces CATSubdivMeshGeo: public CATGeometry
{
CATDeclareInterface;

public:

/**
 * Retrieves the mesh object aggregated in 'this'
 * @return
 * The mesh object
 */
  virtual CATSobMesh* GetMeshStructure() = 0;

/**
 * Specifies that the mathematical mesh must not be deleted
 * when 'this' will be deleted. The deletion is the external.
 */

  virtual void DontEraseMeshStructure() = 0;

/**
 * ----------> A SUPPRIMER ????
 * Erases all the surfaces under each CATSobFace (ie. mesh face)
 * @return
 * 0 if successful
 */
  virtual int RemoveGeometry() = 0;

/**
 * Retrieves a CATSobFace from its tag in the mesh
 * @param iFaceTag
 * The tag of the face
 * @return
 * The corresponding face or NULL if not found
 */
  virtual CATSobFace* GetFaceFromTag(const unsigned int iFaceTag) = 0;

/**
 * Retrieves a CATSobVertex from its tag in the mesh
 * @param iVertexTag
 * The tag of the vertex
 * @return
 * The corresponding vertex or NULL if not found
 */
  virtual CATSobVertex* GetVertexFromTag(const unsigned int iVertexTag) = 0;

/**
 * Retrieves a CATSobEdge from the tag of a face containing it and 
 * the index of the edge in this face (see CATSobFace.h)
 * @param iFaceTag
 * The tag of the edge containing the edge
 * @param iEdgeIndex
 * The indx of the edge in the face
 * @return
 * The corresponding edge or NULL if not found
 */
  virtual CATSobEdge* GetEdgeInFace(const unsigned int iFaceTag, const unsigned int iEdgeIndex) = 0;

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
  //                                                                                //
  //               N O N - C A A             M E T H O D S                          //
  //                                                                                //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

  //Version de l'objet
  virtual CATULONG32 GetObjectVersion() const = 0;
};
CATDeclareHandler(CATSubdivMeshGeo,CATGeometry);

#endif  //R19 ou R206


#endif


