/* -*-C++-*-*/
#ifndef CATPGMPolyBodyImporter_H
#define CATPGMPolyBodyImporter_H

//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2019
//
// CATPGMPolyBodyImporter 
//
// DESCRIPTION :
// Import a PolyBody into a polyhedral CATBody in the ContainerCGM
// with the full BRep description
//
//=============================================================================

// For Windows NT export
#include "CATGMOperatorsInterfaces.h" // ExportedBy
#include "CATErrorDef.h"              // HRESULT
#include "CATSysDataType.h"           // NULL
#include "CATTopDefine.h"             // CATOrientation

#include "CATBoolean.h" 
#include "CATSysBoolean.h" 

#include "CATCollec.h"
#include "CATListPV.h"
#include "CATListOfInt.h"
#include "ListPOfCATCell.h"
#include "CATListOfCATCells.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATMathTransformation;
class CATMapOfIntToInt;

class CATPolyBody;
class CATPolyVertex;
class CATPolyFace;
class CATPolyEdge;
class CATPolyCell;
class CATIPolyMesh;

class CATBody;
class CATFace;
class CATVertex;
class CATEdge;
class CATCell;


/**
* Please, note that the convention of matter side for a CATShell bounding a CATVolume is INWARD,
* opposite to the PolyBody convention  which is always OUTWARD.
* So, importing a volumic set of PolyFaces obviously leads to reverse the global side of the imported CATDomain.
* The default behavior in case of surfacic set of faces consists in reversing the original sides as if the domain was volumic.
*/

class ExportedByCATGMOperatorsInterfaces CATPGMPolyBodyImporter
{

public:

  /**
  * Destructor
  */
  virtual ~CATPGMPolyBodyImporter();


  //=============================================================================
  // Settings
  //=============================================================================

  /*
  * The following option allows the caller to specify the global orientation of 2D-bodies, keeping or reversing the original mesh orientation
  * @param iOriShellVsMesh
  * The relative orientation of the imported 2D-Body, versus the original mesh orientation
  * Only 2 values are accepted : CATOrientationPositive or CATOrientationNegative
  * The current Default behavior is CATOrientationNegative if the option is not called
  */
  virtual void SetSurfacicBodyOrientationVsMesh(const CATOrientation iOriShellVsMesh) = 0;

  /*
  * Option enabling to store the mapping of MeshVertices and MeshTriangles after duplication/transformation
  * in order to retrieve them after Run, thanks to the GetImage() API
  * @param iEnableMeshVerticesMapping
  * Pilots the storage of Mesh Vertices mapping
  * @param iEnableMeshTrianglesMapping
  * Pilots the storage of Mesh Vertices mapping
  */
  virtual void SetMeshMappingKnowledge(CATBoolean iEnableMeshVerticesMapping=TRUE, CATBoolean iEnableMeshTrianglesMapping=FALSE) = 0;


  //=============================================================================
  // Computation
  //=============================================================================
  /**
  * Compute the polyhedral CATBody from the input CATPolyBody 
  * Returns S_OK if the Body is created without any pathology, else E_FAIL
  */
  virtual HRESULT Run(CATBody * &oResultBody) = 0;



  //=============================================================================
  // Information and Diagnosis
  //=============================================================================

  // Information about the highest domains directly owned by the imported CATBody
  // In each service (one for each dimension), the optional boolean argument allows the caller 
  // to know if the input PolyBody declared containing this dimension.
  // Returns -1 if the query doesn't make sense
  // ----------------------------------------------------------------------------
  virtual int GetNbImportedHighLevelDomains(int iExpectedDimension012or3, CATBoolean * oInLineWithExpectation=NULL) = 0;

  virtual int GetNbImportedVerticesInSpace(CATBoolean * oInLineWithExpectation=NULL) = 0; // idem GetNbDomains(0,...)
  virtual int GetNbImportedWires(CATBoolean * oInLineWithExpectation=NULL) = 0;           // idem GetNbDomains(1,...)
  virtual int GetNbImportedSurfaces(CATBoolean * oInLineWithExpectation=NULL) = 0;        // idem GetNbDomains(2,...)
  virtual int GetNbImportedVolumes(CATBoolean * oInLineWithExpectation=NULL) = 0;         // idem GetNbDomains(3,...)


  // "Non watertight edges" diagnosis
  // The list oImportedEdges is filled only if "Mode Without Failure" has been enabled
  // and its size might be greater than oPolyEdges.Size() in case of duplication
  // Returns TRUE if this diagnosis happens at least once, else returns FALSE
  // ---------------------------------------------------------------------------
  virtual CATBoolean GetNonWatertightPolyEdges(CATListPV &oPolyEdges, CATLISTP(CATCell) * oImportedEdges=NULL) = 0;


  // "Non manifold meshes" diagnosis
  // Returns TRUE if this diagnosis happens at least once, else returns FALSE
  // ---------------------------------------------------------------------------
  virtual CATBoolean GetPolyFacesWithNonManifoldMesh(CATListPV & oPolyFaces) = 0;


  // "Disconnected faces" diagnosis
  // The 2 lists oDisconnectedPolyFaces & oNbPartsByPolyFaces (if required) have the same size
  // The list oImportedFaces is filled only if "Mode Without Failure" has been enabled
  // and then might contain invalid imported faces.
  // Returns TRUE if this diagnosis happens at least once, else returns FALSE
  // ---------------------------------------------------------------------------
  virtual CATBoolean GetDisconnectedPolyFaces(CATListPV & oDisconnectedPolyFaces, CATListOfInt * oNbPartsByPolyFace=NULL, CATLISTP(CATCell) * oImportedFaces=NULL) = 0;


  // Faces with missing edges on their boundaries
  // The list oImportedFaces is filled only if "Mode Without Failure" has been enabled
  // The list oImportedMissingEdges is filled only if "Mode Without Failure" has been enabled
  // Returns TRUE if this diagnosis happens at least once, else returns FALSE
  // ----------------------------------------------------------------------------
  virtual CATBoolean GetPolyFacesWithMissingEdges(CATListPV & oPolyFaces, CATLISTP(CATCell) * oImportedFaces=NULL, CATLISTP(CATCell) * oImportedMissingEdges=NULL) = 0;

    
  // Faces with at least one NonManifold vertex on mesh which doesn't reference any PolyVertex (Mandatory)
  // Returns TRUE if this diagnosis happens at least once, else returns FALSE
  // ----------------------------------------------------------------------------
  virtual CATBoolean GetPolyFacesWithMissingNonManifoldVertices(CATListPV & oPolyFaces, CATListOfInt & oNonManifoldVtxIndexes) = 0;



  // Edges which don't match with the boundaries of their adjacent faces
  // The list oImportedNonMatchingEdges is filled only if "Mode Without Failure" has been enabled
  // Returns TRUE if this diagnosis happens at least once, else returns FALSE
  // ----------------------------------------------------------------------------
  virtual CATBoolean GetPolyEdgesNonLyingOnMeshBoundaries(CATListPV &oPolyEdges, CATLISTP(CATCell) * oImportedNonMatchingEdges=NULL) = 0;


  //=============================================================================
  // Journaling
  //=============================================================================

  virtual CATVertex * GetImage(CATPolyVertex & iPolyVtx) = 0;
  virtual CATEdge   * GetImage(CATPolyEdge   & iPolyEdge, CATOrientation * oRelativeOrientation=NULL) = 0;
  virtual CATFace   * GetImage(CATPolyFace   & iPolyFace, CATOrientation * oRelativeOrientation=NULL) = 0;
  virtual CATCell   * GetImage(CATPolyCell * iPolyCell, CATOrientation * oRelativeOrientation=NULL) = 0;

  // Retrieve image CATFace with Mesh Mapping information driven before Run by SetMeshMappingKnowledge() API
  // Each optional mapping object will be filled only if it has been explicitely requested by iEnableMeshVerticesMapping / iEnableMeshTianglesMapping
  // and only if at least one ID has changed 
  // -> An iso-mapping will be returned as empty with Size() == 0
  virtual CATFace   * GetImage(CATPolyFace   & iPolyFace, const CATIPolyMesh * & oImageMesh, CATMapOfIntToInt * ioSourceVtxToImageVtx = NULL,  CATMapOfIntToInt * ioSourceTriToImageTri = NULL) = 0;

};

/**
 * Creates a CATPGMPolyBodyImporter.
 * @param iTargetFactory
 * The factory in which the input data will be imported and contained. (MANDATORY)
 * @param iSoftwareConfig
 * The pointer to the SoftwareConfiguration in order to drive the versionning of future modifications
 * Default (9019) closed config with the versioning value of V5R31 SP1 / V6R423 FD01 releases will be considered if iSoftwareConfig is set to null
 * @param iPolyBodyToImport
 * The input PolyBody to import into a CATBody
 * @return [out]
 * The pointer to the created operator. To be deleted after use.
 */
ExportedByCATGMOperatorsInterfaces CATPGMPolyBodyImporter * CATPGMCreatePolyBodyImporter(CATGeoFactory * iTargetFactory, CATSoftwareConfiguration * iSoftwareConfig, CATPolyBody * iPolyBodyToImport); 

#endif
