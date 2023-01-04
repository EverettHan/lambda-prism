/* -*-C++-*-*/
#ifndef CATPGMPolyBodyAdapter_H
#define CATPGMPolyBodyAdapter_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2019
//
// CATPGMPolyBodyAdapter 
//
// DESCRIPTION :
// Export a polyhedral CATBody into a CATPolyBody sharing or duplicating its geometry
//
//=============================================================================

// For Windows NT export
#include "CATGMOperatorsInterfaces.h" // ExportedBy
#include "CATErrorDef.h"              // HRESULT
#include "CATTopDefine.h"             // CATOrientation
#include "CATSysDataType.h"           // NULL

#include "CATBoolean.h" 
#include "CATSysBoolean.h" 

class CATSoftwareConfiguration;
class CATMathTransformation;
class CATPolyBody;
class CATPolyCell;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;
class CATBody;
class CATFace;
class CATEdge;
class CATVertex;
class CATCell;
class CATDomain;
class CATMapOfPtrToPtr;

class ExportedByCATGMOperatorsInterfaces CATPGMPolyBodyAdapter
{
public:

  /**
  * Destructor
  */
  virtual ~CATPGMPolyBodyAdapter();


  //=============================================================================
  // Settings
  //=============================================================================
   
  // Please, note here that the convention of matter side for a CATShell bounding a CATVolume is INWARD,
  // opposite to the PolyBody convention  which is always OUTWARD.
  // So, importing a volumic set of PolyFaces obviously leads to reverse the global side of the imported CATDomain.
  // The default behavior in case of surfacic set of faces consists in reversing the original sides as if the domain was volumic.
  // The following option allows the user to keep (Positive) or not (Negative) the global orientation of surfacic shells only.
  virtual void SetMeshOrientationVsSurfacicShell(CATOrientation iOriMeshVsShell) = 0;

  virtual void ForceDuplicationMode() = 0;

  virtual void EnableCanonicityTransfer() = 0;

  virtual void EnablePolyVolumeMode() = 0;


  //=============================================================================
  // Computation
  //=============================================================================
  /**
  * Compute the PolyBody from the input polyhedral CATBody 
  * if the Check is required, the PolyBody result will be returned only if it's valid
  * PLEASE NOTE THAT THE CALLER HAS TO RELEASE THE RETURNED oResultBody AFTER USE !!!
  */
  virtual HRESULT Run(CATPolyBody * &oResultPolyBody, CATBoolean iCheckResult=FALSE) = 0;


  //=============================================================================
  // Journaling
  //=============================================================================


  /** Retrieve the image of an input vertex */
  virtual CATPolyVertex * GetImage(CATVertex & iPHVtx) = 0;

  /** Retrieve the image of an input edge */
  virtual CATPolyEdge   * GetImage(CATEdge   & iPHEdge, CATOrientation * oOriVsSource=NULL) = 0;

  /** Retrieve the image of an input face */
  virtual CATPolyFace   * GetImage(CATFace   & iPHFace, CATOrientation * oOriVsSource=NULL) = 0;


  /**
  * Get the map of equivalent image cell for each source cell
  * iDim allows the caller to filter according to a specific dimension :
  * -1 to get all cells (default), 0 to get only vertices, 1 to get only edges, 2 to get only faces, 3 to get only volumes
  */
  virtual HRESULT GetMapOfGMCellToPolyCell(CATMapOfPtrToPtr & ioMap, int iDim=-1) = 0;

  /**
  * Get the map of equivalent source cell for each image cell
  * iDim allows the caller to filter according to a specific dimension :
  * -1 to get all cells (default), 0 to get only vertices, 1 to get only edges, 2 to get only faces, , 3 to get only volumes
  */
  virtual HRESULT GetMapOfPolyCellToGMCell(CATMapOfPtrToPtr & ioMap, int iDim=-1) = 0;


};

/**
* Creates a CATPGMPolyBodyAdapter.
* @param iGMPolyBody
* The input polyhedral CATBody to adapt into a CATPolyBody
* @param iSoftwareConfig
* The pointer to the SoftwareConfiguration in order to drive the versionning of future modifications
* If iSoftwareConfig is NULL, default config 10313 will be used (versioning value of V5R32 SP2 / V6R424 FD03)
* @return [out]
* The pointer to the created operator. To be deleted after use.
*/
ExportedByCATGMOperatorsInterfaces CATPGMPolyBodyAdapter * CATPGMCreatePolyBodyAdapter(CATBody * iPHBody, CATSoftwareConfiguration * iSoftwareConfig=NULL); 

/**
* Creates a CATGMPolyBodyAdapter.
* @param iGMPolyDomain
* The input polyhedral CATDomain to adapt into a CATPolyBody
* @param iSoftwareConfig
* The pointer to the SoftwareConfiguration in order to drive the versionning of future modifications
* If iSoftwareConfig is NULL, default config 10313 will be used (versioning value of V5R32 SP2 / V6R424 FD03)
* @return [out]
* The pointer to the created operator. To be deleted after use.
*/
ExportedByCATGMOperatorsInterfaces CATPGMPolyBodyAdapter * CATPGMCreatePolyBodyAdapter(CATDomain * iPHDomain, CATSoftwareConfiguration * iSoftwareConfig=NULL);

#endif
