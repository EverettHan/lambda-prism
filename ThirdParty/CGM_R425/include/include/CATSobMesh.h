//========================================================================================
// Copyright Dassault Systemes Provence 2003, All Rights Reserved
//========================================================================================
//
// CATSobMesh.h
//
//========================================================================================
//
// Usage notes:
//
//========================================================================================
// December,  2009 : RAQ : Ajout des listeners
// March,     2009 : RAQ : Ajout AddRef/Release
// January,   2008 : RAQ : Déplacement des méthodes GetMaxTagXXX de protected à public
// December,  2006 : RAQ : Ajout IsMeshFrozen
// October,   2006 : RAQ : SetExistsSubdivMesh passe dans CATSobMeshProtected
// October,   2006 : RAQ : Gestion tags sur les vertex
// October,   2005 : RAQ : Ajout Tag pour modif topo
// March,     2005 : RAQ : Ajout de transactions topo. pour update des BM locaux
// February,  2005 : RAQ : Ajout ReorderMeshElements pour optimisation mémoire
// February,  2005 : RAQ : Ajout constructeur par copie
// October,   2004 : RAQ : Optimisation mémoire
// July,      2004 : RAQ : Gestion precision pour le stream avec pertes
// July,      2004 : RAQ : Ajout SetExistsSubdivMesh et ExistsSubdivMesh
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// October,   2003 : RAQ : Suppression des méthodes RemoveXXX et Update
// September, 2003 : JCV : Constructeur a partir d'une liste de faces
// September, 2003 : JCV : Gestion Diag
// February,  2003 : JCV : Creation d'apres le proto de LLR
//========================================================================================
#ifndef CATSobMesh_H
#define CATSobMesh_H

//Version Catia
#include "CATIAV5Level.h"

//Pour l'export
#include "CATSobObjects.h"

//Objets Subdivision
#include "CATSobDiag.h"
#include "CATSobDefine.h"
#include "CATSobListOfFace.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"
#include "CATSobAttributes.h"

//Divers
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATLib.h"

class CATSobVertex;
class CATSobEdge;
class CATSobFace;
class CATSobCell;
class CATSobMeshListener;
class CATSobMeshLayer;
class CATSobMeshLayerId;


//#define REMOVE_DESTRUCTOR


/**
 * Interface representing a Mesh
 */
class ExportedByCATSobObjects CATSobMesh
{
public:

/**
 * Increments the reference counter of 'this' mesh.
 *
 * @return
 * The new reference counter
 */
  virtual int AddRef() = 0;

/**
 * Decrement the reference counter of 'this' mesh
 */
  virtual void Release() = 0;
  
/**
 * DEPRECATED: Do not use anymore, use AddRef/Release mechanism instead
 */
#ifdef REMOVE_DESTRUCTOR
protected:
#endif  //REMOVE_DESTRUCTOR
  virtual ~CATSobMesh() {}
#ifdef REMOVE_DESTRUCTOR
public:
#endif  //REMOVE_DESTRUCTOR


  //-------------------------------- TOPOLOGICAL SERVICES --------------------------------//

/**
 * Adds a List Of Faces in the Mesh.
 *
 * @param iFaces
 * The List Of Faces to add.
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                   </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullList        </tt> <dd> iFaces is null
 * <dl><dt><tt>CATSobDiag_InputNullListElement </tt> <dd> one face of iFaces is null.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag AddFaces(CATLISTP(CATSobFace)* iFaces) = 0;

/**
 * Creates a Face in the Mesh.
 *
 * @param iEdges
 * The List Of Edges to define de boundary of the Face.
 *
 * @return
 * the pointer on the created Face 
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                   </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullList        </tt> <dd> iEdges is null
 * <dl><dt><tt>CATSobDiag_InputInvalidSize     </tt> <dd> number of edges must be greater or equal to 3.
 * <dl><dt><tt>CATSobDiag_InputNullListElement </tt> <dd> one edge of iEdges is null.
 * <dl><dt><tt>CATSobDiag_FaceNotConnectedEdge </tt> <dd> all edge must be connected (same vertex) with the next edge
 * <dl><dt><tt>CATSobDiag_FaceNotClose         </tt> <dd> the first and the last edge must be connected.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobFace* CreateFace(CATLISTP(CATSobEdge)* iEdges) = 0;
  
/**
 * Creates an Edge in the Mesh.
 *
 * @param iStart
 * The start vertex of the edge
 *
 * @param iEnd
 * The end vertex of the edge.
 *
 * @return
 * the pointer on the created Edge 
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK              </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullVertex </tt> <dd> iStart or iEnd is null
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
	virtual CATSobEdge* CreateEdge(CATSobVertex* iStart,  
                                 CATSobVertex* iEnd) = 0;
  
/**
 * Creates a Vertex in the Mesh.
 *
 * @param iX
 * Define the first coordinate of the Vertex
 * @param iY
 * Define the second coordinate of the Vertex
 * @param iZ
 * Define the third coordinate of the Vertex
 *
 * @return
 * the pointer on the created Vertex 
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK</tt> <dd> OK.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
	virtual CATSobVertex* CreateVertex(const double& iX, const double& iY, const double& iZ) = 0;

/**
 * Creates a Vertex in the Mesh.
 *
 * @param iX
 * An array of three double containing the coordinates of the Vertex
 *
 * @return
 * the pointer on the created Vertex 
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK</tt> <dd> OK.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
	virtual CATSobVertex* CreateVertex(const double iCoords[]) = 0;

/**
 * Removes a face given by its pointer.
 *
 * @param ioFace
 * the pointer of the face to remove
 * after remove, the pointer is put to null
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK            </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullFace </tt> <dd> ioFace is null
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
	virtual CATSobDiag RemoveFace(CATSobFace*& ioFace) = 0;

/**
 * Removes a Edge given by its pointer.
 *
 * @param ioEdge
 * the pointer of the Edge to remove
 * after remove, the pointer is put to null
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK            </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullEdge </tt> <dd> ioEdge is null
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag RemoveEdge(CATSobEdge*& iEdge) = 0;
  
/**
 * Removes a Vertex given by its pointer.
 *
 * @param ioVertex
 * the pointer of the Vertex to remove
 * after remove, the pointer is put to null
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK              </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullVertex </tt> <dd> ioVertex is null
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag RemoveVertex(CATSobVertex*& iVertex) = 0;

/**
 * Removes a face given by its index in the list of faces of the mesh.
 *
 * @param iIndex (1..number of faces)
 * the index of the face to remove
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidIndex </tt> <dd> iIndex is null or greater than number of faces
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag RemoveFace(const int iIndex) = 0;

/**
 * Removes an Edge given by its index in the list of Edges of the mesh.
 *
 * @param iIndex (1..number of Edges)
 * the index of the Edge to remove
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidIndex </tt> <dd> iIndex is null or greater than number of Edges
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag RemoveEdge(const int iIndex) = 0;
  
/**
 * Removes a Vertex given by its index in the list of Vertices of the mesh.
 *
 * @param iIndex (1..number of Vertices)
 * the index of the Vertex to remove
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidIndex </tt> <dd> iIndex is null or greater than number of Vertexs
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag RemoveVertex(const int iIndex) = 0;

/**
 * Verifies the validity  of the mesh
 * - No Null Faces
 * - Connexity
 * - Lenght of Edge
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                   </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_FaceNull             </tt> <dd> Null Faces exist in Mesh
 * <dl><dt><tt>CATSobDiag_EdgeNull             </tt> <dd> Null Edges exist in Mesh
 * <dl><dt><tt>CATSobDiag_MeshInvalidConnexity </tt> <dd> not connec Faces
 * <dl><dt><tt>CATSobDiag_EdgeLenghtMin        </tt> <dd> Lenght Edge too small
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag Verification() = 0;
  
/**
 * Updates the mesh
 * - Remove Nulls pointer in the lists
 * - Edges Not used by faces
 * - Vertex Not used by edge
 * After Update, the mesh must be connect.
 *
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK </tt> <dd> OK.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag Update() = 0;

/**
 * Adds a listener to 'this' mesh.
 *
 * @param iListener
 * The listener to add.
 */
  virtual void AddListener(CATSobMeshListener* iListener) = 0;

/**
 * Removes a listener from 'this' mesh.
 *
 * @param iListener
 * The listener to remove.
 */
  virtual void RemoveListener(CATSobMeshListener* iListener) = 0;


  //-------------------------------- CELLS RETRIEVING UTILITIES --------------------------------//

/**
 * Gets the number of faces in 'this' mesh
 *
 * @return
 * The number of faces in 'this' mesh
 */
  virtual int GetNbFaces() const = 0;
  
/**
 * Gets the number of edges in 'this' mesh
 *
 * @return
 * The number of edges in 'this' mesh
 */
  virtual int GetNbEdges() const = 0;

/**
 * Gets the number of vertices in 'this' mesh
 *
 * @return
 * The number of vertices in 'this' mesh
 */
  virtual int GetNbVertices() const = 0;

/**
 * Gets all Faces defined in the Mesh.
 *
 * @param ioFaces
 * a pointer on the list of faces defined in the mesh
 *
 * @return
 * the number on the defined Faces 
 */
  virtual int GetAllFaces(CATLISTP(CATSobFace)*& ioFaces) const = 0;

/**
 * Gets all Edges defined in the Mesh.
 *
 * @param ioEdges
 * a pointer on the list of Edges defined in the mesh
 *
 * @return
 * the number on the defined Edges 
 */
  virtual int GetAllEdges(CATLISTP(CATSobEdge)*& ioEdges) const = 0;

/**
 * Gets all Vertices defined in the Mesh.
 *
 * @param ioVertices
 * a pointer on the list of Vertices defined in the mesh
 *
 * @return
 * the number on the defined Vertices 
 */
  virtual int GetAllVertices(CATLISTP(CATSobVertex)*& ioVertices) const = 0;

/**
 * Retreives a CATSobFace of 'this' mesh from its tag
 *
 * @param iTag
 * The tag of the face to be retreived
 *
 * @return
 * The face whose tag is iTag
 */
  virtual CATSobFace* GetFaceFromTag(const unsigned int iTag) const = 0;

/**
 * Retreives a CATSobVertex of 'this' mesh from its tag
 *
 * @param iTag
 * The tag of the vertex to be retreived
 *
 * @return
 * The vertex whose tag is iTag
 */
  virtual CATSobVertex* GetVertexFromTag(const unsigned int iTag) const = 0;

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

/**
 * Retrieves a CATSobEdge from its vertices.
 * @param iVertex1
 * The first vertex
 * @param iVertex2
 * The second vertex
 * @return
 * The corresponding edge or NULL if not found
 */
  virtual CATSobEdge* GetEdgeBetweenVertices(CATSobVertex* iVertex1, CATSobVertex* iVertex2) const = 0;

/**
 * Retrieves a CATSobEdge from the tag of its extremity vertices.
 * @param iVertexTag1
 * The first vertex tag
 * @param iVertexTag2
 * The second vertex tag
 * @return
 * The corresponding edge or NULL if not found
 */
  virtual CATSobEdge* GetEdgeBetweenVertices(const unsigned int iVertexTag1, const unsigned int iVertexTag2) const = 0;

/**
 * Gets the highest tag on faces in 'this' mesh
 *
 * @return
 * The highest tag
 */
  virtual unsigned int GetMaxTagForFaces() const = 0;

/**
 * Gets the highest tag on vertices in 'this' mesh
 *
 * @return
 * The highest tag
 */
  virtual unsigned int GetMaxTagForVertices() const = 0;

/**
 * Gets the maximum valence on all vertices of the mesh
 *
 * @return
 * The maximum valence
 */
  virtual int GetValenceMax() const = 0;

  //-------------------------------- LAYERS UTILITIES --------------------------------//

/**
 * Adds a layer to 'this' mesh.
 *
 * @param iMeshLayer
 * The layer to add, a reference is added on it.
 */
  virtual void AddLayer(CATSobMeshLayer* iMeshLayer) = 0;

/**
 * Removes a layer from 'this' mesh.
 *
 * @param iMeshLayer
 * The layer to remove, it is released.
 */
  virtual void RemoveLayer(CATSobMeshLayer* iMeshLayer) = 0;

/**
 * Retreives a layer from a LayerID.
 * /!\ No AddRef is done on the returned layer.
 *
 * @param iID
 * The layer ID.
 * @param iName
 * In case of multiple layers having the same ID, retrieves from the layer name.
 *
 * @return
 * The layer if found.
 */
  virtual CATSobMeshLayer* GetMeshLayer(const CATSobMeshLayerId* iID, const CATLONGPTR iName = 0) = 0;


  //-------------------------------- MISC UTILITIES --------------------------------//

/**
 * Verifies the closure of the mesh
 *
 * @return
 * The closure information.
 * 0 : The mesh is not Close
 * 1 : The mesh is Close
 */
  virtual int IsClose() = 0;

/**
 * Test whether the mesh contains triangular faces
 *
 * @return
 * 1 if the mesh contains triangular faces, 0 else
 */
  virtual int HasTriangularFaces() const = 0;

/**
 * Check whether 'this' mesh is frozen
 *
 * @return
 * TRUE if the mesh is frozen, FALSE otherwise.
 */
  virtual CATBoolean IsMeshFrozen() const = 0;

/**
 * Reorder mesh elements (ie. Faces, edges and vertices) in the lists
 * given by GetAllXXX for buffer optimisation.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  virtual CATSobDiag ReorderMeshElements() = 0;

/**
 * Release all buffers used during subdivision
 */
  virtual void ResetAllSubdivisionBuffers() = 0;
 
/**
 * Returns the information value of the last method
 * @return
 * The information value.
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobDiag GetDiag() const = 0;

/**
 * Set the diagnostic of the mesh
 * @param iDiag
 * The diagnostic of the mesh
 */
  virtual void SetDiag(CATSobDiag iDiag) = 0;

/**
 * Set that mesh topology state has changed.
 *
 * @param iTopoChanged
 * If iTopoChanged is TRUE the topology state of the mesh is "Changed",
 * else it is "Not Changed"
 **/
  virtual void SetTopologyChanged(const CATBoolean iTopoChanged) = 0;

/**
 * Check whether the mesh topology has changed.
 *
 * @return
 * TRUE if mesh topology has changed, else FALSE
 **/
  virtual CATBoolean HasTopologyChanged() const = 0;

/**
 * Set the precision to use while lossy streaming 'this' mesh
 * If the precision is negative, the mesh will be exactly saved
 *
 * @param iPrecision
 * The precision value
 */
  virtual void SetPrecisionForLossyStream(const float iPrecision) = 0;

/**
 * Get the precision used while lossy streaming 'this' mesh
 *
 * @return
 * The precision used if positive, else stream is exact
 */
  virtual float GetPrecisionForLossyStream() const = 0;

/**
 * Check if a subdivision has already been processed on 'this' mesh.
 *
 * @return
 * TRUE if a subdivision has already been processed, FALSE else
 */
  virtual CATBoolean ExistsSubdivMesh() const = 0;

/**
 * Set that mesh details are expressed in global or local frame(s).
 *
 * @param iUseLocalFrame
 * If iUseLocalFrame is TRUE, details are expressed in local frames,
 * else they are expressed in global frame.
 **/
  virtual void SetUseLocalFrame(const CATBoolean iUseLocalFrame) = 0;

/**
 * Return whether mesh details are expressed in global or local frame(s)
 *
 * @return
 * If returned value is TRUE mesh details are expressed in local frame,
 * else they are expressed in global frame.
 **/
  virtual CATBoolean GetUseLocalFrame() const = 0;

  //-------------------------------- LOCAL CUT UTILITIES --------------------------------//

/**
 * Local Cut: Begin of a step of topological modification.
 * None of the local base meshes will be updated until the step is closed
 */
  virtual void OpenTopoModifTransaction() = 0;

/**
 * Local Cut: Close a step of topological modification.
 * Local base meshes are automatically updated.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  virtual CATSobDiag CloseTopoModifTransaction() = 0;

/**
 * Local Cut: Check if a topological modification step is open on 'this' mesh
 *
 * @return
 * 0 if no topological moficiation step is open, else 1.
 */
  virtual CATBoolean IsTopoModifTransactionOpen() const = 0;

/**
 * RemoveAllAttributesOfType
 * Release On All Mesh's Cell the Attributes of the Given Type
 */
  virtual void RemoveAllAttributesOfType(CATSobAttributesId * iType, CATLONGPTR iName=0) =0;

  virtual void FreeAllCellRankWithKey(CATLONGPTR iKey)=0;
  
  
/************* DEPRECATED ***********
 * Gets the Quad Mesh
 *
 * @return CATSobMesh
 * The Quad Mesh. Null if not exist.
 */
#ifdef _WINDOWS_SOURCE
  virtual __declspec(deprecated("Deprecated subdiv method, Do not use anymore")) CATSobMesh* GetQuadMesh() const = 0;
#else
  virtual CATSobMesh* GetQuadMesh() const = 0;
#endif  //_WINDOWS_SOURCE
  

/************* DEPRECATED ***********
 * Gets QuadState of the mesh
 *
 * @return 
 * the State Mesh. Legal Values :
 * - CATSobQuad_Undef : Undef -> necessary to use the Quad Operator to define if mesh is quad 
 * - CATSobQuad_Yes   : Mesh is Quad
 * - CATSobQuad_No    : Mesh is Not Quad
 * Use @href CATSobDefine include to see all the state values.
 */
  virtual CATSobQuadState GetQuadState() const = 0;

/************* Debug: Do Not Use ***********
 * Loop subdivision
 **/
  virtual CATSobDiag SetLoopMesh(const CATBoolean iOnOff = TRUE) = 0;
  virtual CATBoolean IsLoopMesh() const = 0;

protected:

  //Constructeur
  CATSobMesh() {}

private :
  // Copy constructor and equal operator
  CATSobMesh (CATSobMesh &);
  CATSobMesh& operator=(CATSobMesh&);

};


/**
 * Subdivision mesh constructor
 *
 * @return
 * A pointer to a CATSobMesh object
 */
ExportedByCATSobObjects CATSobMesh* CATSobCreateMesh();

/**
 * Subdivision mesh copy constructor
 *
 * @param iMeshToCopy
 * A pointer to an existing mesh to copy
 *
 * @param iCopyCellsFlags
 * DO NOT USE, only default value must be used
 * if iCopyCellsFlags is TRUE, the method copies flags associated to each cell.
 *
 * @return
 * A pointer to a CATSobMesh object. The new mesh has the same
 * topology that the input mesh, details, sharpness and weights are
 * also copied.
 */
ExportedByCATSobObjects CATSobMesh* CATSobCreateMesh(CATSobMesh*      iMeshToCopy,
                                                     const CATBoolean iCopyCellsFlags = FALSE);

/**
 * Builds a mesh from a set of faces, cells tags, details, weights... are reported.
 *
 * @param iInputFaces
 * The faces to copy in 'this' new mesh.
 *
 * @return
 * A pointer to the new mesh if copy is successful.
 **/
ExportedByCATSobObjects CATSobMesh* CATSobCreateMesh(const CATLISTP(CATSobFace)& iInputFaces);


#endif
