/*-*-c++-*-*/
//=======================================================================
//  Interface representing a CATSubdivMesh for subdivision
//=======================================================================
// July,   2004 : RAQ : Creation
//=======================================================================
#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"


#ifndef CATSubdivMesh_H
#define CATSubdivMesh_H

#include "CATMathDef.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "IUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSubdivMesh ;
#else
extern "C" const IID IID_CATSubdivMesh ;
#endif

#include "CATGeometry.h"

class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobVertex;
class CATBody;
class CATSubdivMeshGeo;


class ExportedByCATGMGeometricInterfaces CATSubdivMesh: public CATGeometry
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
 * Erases all the surfaces under each CATSobFace (ie. mesh face)
 * @return
 * 0 if successful
 */
  virtual int RemoveGeometry() = 0;


#if defined CATIAV5R18 || defined CATIAR204
/**
 * Retrieves a CATSobFace from its tag in the mesh
 * @param iFaceTag
 * The tag of the face
 * @return
 * The corresponding face or NULL if not found
 */
  virtual CATSobFace* GetFaceFromTag(const unsigned int iFaceTag) = 0;
#endif  //R18 ou R204

#if defined CATIAV5R18 || defined CATIAR204
/**
 * Retrieves a CATSobVertex from its tag in the mesh
 * @param iVertexTag
 * The tag of the vertex
 * @return
 * The corresponding vertex or NULL if not found
 */
  virtual CATSobVertex* GetVertexFromTag(const unsigned int iVertexTag) = 0;
#endif  //R18 ou R204

#if defined CATIAV5R18 || defined CATIAR204
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
#endif  //R18 ou R204



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
  //                                                                                //
  //               N O N - C A A             M E T H O D S                          //
  //                                                                                //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

  //-------------------------------------------------------------------------
	// Gestion des attributs, cf: CATSubdivisionTopOperators\ProtectedInterfaces\CATStoSubdivMeshProperties.h
	//-------------------------------------------------------------------------
#if defined CATIAV5R18 || defined CATIAR204
  
  //********** DO NOT USE - Type de PCCM
  virtual void SetPCCMCommonType() = 0;
  virtual CATBoolean IsPCCMCommonType() const = 0;

  //********** DO NOT USE - Type de raccords pour le PCCM
  virtual void SetPCCMContinuityType(const CATBoolean iG0, const CATBoolean iG1, const CATBoolean iG2) = 0;
  virtual void GetPCCMContinuityType(CATBoolean& oG0, CATBoolean& oG1, CATBoolean& oG2) const = 0;

  //********** DO NOT USE - Correction des surfaces singulières
  virtual void SetProcessSingularSurfaces(const CATBoolean iProcessOnOff) = 0;
  virtual CATBoolean MustProcessSingularSurfaces() const = 0;

  //********** DO NOT USE - Gestion lien CATSubdivMesh -> CATBody
  virtual void SetLinkedBodyTag(const CATULONG32 iLinkedBodyTag) = 0;
  virtual CATULONG32 GetLinkedBodyTag() const = 0;

#endif  //R18 ou R204

  //Niveau de subdivision utilisé pour l'appel au PCCM
  virtual void SetSubdivisionLevelForPCCM(const int iLevel) = 0;
  virtual int GetSubdivisionLevelForPCCM() const = 0;

#if defined CATIAV5R19 || defined CATIAR206

  //********** DO NOT USE - Utilisation des CATSubdivCellSurface
  virtual void SetUseSubdivCellSurface(const CATBoolean iUseSubdivCellOnOff) = 0;
  virtual CATBoolean MustUseSubdivCellSurface() const = 0;

  //********** DO NOT USE - Récupération du CATSubdivMeshGeo
  virtual void GetSubdivMeshGeo(const CATSubdivMeshGeo*& oSubdivMeshGeo) const = 0;
#endif  //R19 ou R206

  //Version de l'objet
#if defined CATIAV5R18 || defined CATIAR204
  virtual CATULONG32 GetObjectVersion() const = 0;
#endif  //R18 ou R204


};
CATDeclareHandler(CATSubdivMesh,CATGeometry);

#endif

