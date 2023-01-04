/* -*-C++-*- */

#ifndef CATPGMVolumePartitionBodyToolKit_H
#define CATPGMVolumePartitionBodyToolKit_H

// COPYRIGHT DASSAULT SYSTEMES 2022

//=============================================================================
//
// CATPGMVolumePartitionBodyToolKit 
//
// DESCRIPTION : Tool Kit of services dedicated to a CATBody containing volumes,
//               supporting all topological configurations: 
//                          connected in a single lump or not, partitioned or not,
//               retrieving all topological neighborhood information,
//               creating new bodies from subsets of volumes
//
//=============================================================================

#include "CATGMModelInterfaces.h" // ExportedBy

#include "CATErrorDef.h"          // HRESULT

#include "ListPOfCATCell.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATShell.h"
#include "ListPOfCATFace.h"
#include "CATListOfInt.h"          

#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATSoftwareConfiguration;

class CATTopology;
class CATBody;
class CATFace;
class CATLump;
class CATVolume;
class CATShell;

/**
 * Class defining the ToolKit dedicated to a CATBody containing volumes,
 * and returning topological information
 * It must be directly deleted with the usual C++ <tt>delete</tt> 
 * operator after use. It is not streamable. 
 */
class ExportedByCATGMModelInterfaces CATPGMVolumePartitionBodyToolKit
{
public:

  /**
  * Destructor
  */
  virtual ~CATPGMVolumePartitionBodyToolKit();


public:

  // ------------------------------------------------------------------------------------------------------------
  /**
  * Partition Validity Status
  */
  // ------------------------------------------------------------------------------------------------------------
  virtual CATBoolean GetPartitionValidityStatus() = 0;


  // ------------------------------------------------------------------------------------------------------------
  /**
  * Retrieve cells and domains information at the input CATBody level
  * GetAllFacesBoundingVolumePartition, GetAllFacesInsideVolumePartition and GetAllFacesOutsideVolumePartition are complementary
  */
  // ------------------------------------------------------------------------------------------------------------

  // Retrieve all the faces bounding only one volume: walls between matter and void
  // oBoundaryFaces, oFacesMatterOri, oBoundedVolumes (and optionally ioBoundedLumps) are 4 parallel lists
  // oBoundaryFaces is not supposed to contain NULL pointers, neither oBoundedVolumes, (neither the optional ioBoundedLumps)
  // If this method returns empty lists, that means the input body has no volume.
  virtual void GetAllFacesBoundingVolumePartition(ListPOfCATFace & oBoundaryFaces, CATListOfInt & oFacesMatterOri, ListPOfCATCell & oBoundedVolumes, 
                                                  ListPOfCATDomain * ioBoundedLumps=NULL) = 0;

  // Retrieve all the faces inside the matter of lumps, 
  // Full face inside one volume, or bounding 2 different volumes sharing this face
  // oInsideFaces, oPosSideVolumes, oNegSideVolumes (and optionally ioContainingLumps) are 4 parallel lists
  // oInsideFaces, oPosSideVolumes & oNegSideVolumes are not supposed to contain NULL pointers, (neither the optional ioContainingLumps) 
  // If this method returns empty lists, that means the input body is not partitioned
  virtual void GetAllFacesInsideVolumePartition(ListPOfCATFace & oInsideFaces, ListPOfCATCell & oPosSideVolumes, ListPOfCATCell & oNegSideVolumes, 
                                                ListPOfCATDomain * ioContainingLumps=NULL) = 0;

  // Retrieve all the faces not referenced by any CATLump but contained by CATShells directly referenced by the input CATBody
  // oSkinFaces, oFacesOriInShell, (and optionally ioContainingShells) are 3 parallel lists
  // oSkinFaces is not supposed to contain NULL pointers, (neither the optional ioContainingShells) 
  // If this method returns empty lists, that means the input body doesn't contain any CATShell with location in 3DSpace
  virtual void GetAllFacesOutsideVolumePartition(ListPOfCATFace & oSkinFaces, CATListOfInt & oFacesOriInShell, 
                                                 ListPOfCATShell * ioContainingShells=NULL) = 0;

  
  // ------------------------------------------------------------------------------------------------------------
  /**
  * Retrieve cells and domains information at a given CATLump level
  * GetAllFacesBoundingLump and GetAllFacesInsideLump are complementary at this level
  */
  // ------------------------------------------------------------------------------------------------------------

  // Retrieve all the faces bounding only one volume belonging to a given lump
  // oBoundaryFaces, oFacesMatterOri, oBoundedVolumes are 3 parallel lists
  // oBoundaryFaces and oBoundedVolumes are not supposed to contain NULL pointers
  // If this method returns empty lists, that means the given lump has no volume known by the input body.
  virtual void GetAllFacesBoundingLump(CATLump & iBoundedLump, ListPOfCATFace & oBoundaryFaces, CATListOfInt & oFacesMatterOri, ListPOfCATCell & oBoundedVolumes) = 0;

  // Retrieve all the faces inside the matter of a given lump 
  // Full face inside one volume, or bounding 2 different volumes sharing this face
  // oInsideFaces, oPosSideVolumes, oNegSideVolumes are 3 parallel lists
  // oInsideFaces, oPosSideVolumes & oNegSideVolumes are not supposed to contain NULL pointers,
  // If this method returns empty lists, that means the given lump is not partitioned (or doesn't belong to the input body)
  virtual void GetAllFacesInsideLump(CATLump & iContainingLump, ListPOfCATFace & oInsideFaces, ListPOfCATCell & oPosSideVolumes, ListPOfCATCell & oNegSideVolumes) = 0;


  // ------------------------------------------------------------------------------------------------------------
  /**
  * Retrieve cells and domains information at a given CATVolume level
  * GetAllFacesFromVolume is complete at a given CATVolume level
  * GetSharedFacesFromVolume and GetExclusiveFacesFromVolume are complementary at this level
  */
  // ------------------------------------------------------------------------------------------------------------

  // Retrieve the list of faces bounding a given volume, with the knowledge of the adjacent volumes
  // oFaces will be ordered Shell by Shell, beginning by the outer Shell, including full shells at the end if any
  // oFaces, oFacesOriInShell, oBoundingShells, oNeighborVolumes are 4 parallel lists
  // a bounding shell can be present several times in oBoundingShells (as many times as there are faces in this shell)
  // a neighbor volume can be present several times in oNeighborVolumes and oNeighborVolumes may contain null pointers
  // if a neighbor volume is equal to the input volume itself, that means the current face is full inside the given volume
  virtual void GetAllFacesFromVolume(CATVolume & iVolume, ListPOfCATFace & oFaces, CATListOfInt & oFacesOriInShell, 
                                     ListPOfCATShell & oBoundingShells, ListPOfCATCell & oNeighborVolumes) = 0;

  // Retrieve the list of faces shared by a given volume and other volumes (different from the first one)
  // Those faces may belong to the outer shell or one inner shell of the given body
  // oSharedFaces, oFacesOriInShell, oBoundingShells, oShellsLocation and oNeighborVolumes are 5 parallel lists
  // oSharedFaces, oBoundingShells and oNeighborVolumes are not supposed to contain NULL pointers
  // oNeighborVolumes is not supposed to contain iVolume
  // If this method returns empty lists, that means the given volume is entirely isolated, single in its CATLump
  virtual void GetSharedFacesFromVolume(CATVolume & iVolume, ListPOfCATFace & oSharedFaces, CATListOfInt & oFacesOriInShell, 
                                        ListPOfCATShell & oBoundingShells, CATListOfInt & oShellsLocation, ListPOfCATCell & oNeighborVolumes) = 0;

  // Retrieve the list of faces exclusively referenced by a given volume (not shared by another one)
  // Those faces may belong to the outer shell or one inner shell or one full shell of the given body
  // oExclusiveFaces, oFacesOriInShell, oBoundingShells and oShellsLocation are 4 parallel lists
  // oExclusiveFaces and  oBoundingShells are not supposed to contain NULL pointers
  // If this method returns empty lists, that means the given volume is totally surrounded by other volumes in its CATLump
  virtual void GetExclusiveFacesFromVolume(CATVolume & iVolume, ListPOfCATFace & oExclusiveFaces, CATListOfInt & oFacesOriInShell, 
                                           ListPOfCATShell & oBoundingShells, CATListOfInt & oShellsLocation) = 0;


  // Retrieve the single CATLump containing a given CATVolume
  // if the method returns NULL, that means the given volume doesn't belong to the input body, or the partition is not valid
  virtual CATLump * GetLumpContainingVolume(CATVolume & iVolume) = 0;


  // ------------------------------------------------------------------------------------------------------------
  /**
  * Retrieve shells and volumes information at a given CATFace level
  */
  // ------------------------------------------------------------------------------------------------------------

  // Retrieve the shells and volumes (if any) containing a given CATFace
  // oPosNegShells[2], oPosNegLocations[2], oPosNegSideVolumes[2] are complementary to describe the bounded neighborhood of the CATFace in the input CATBody
  // The first index [0] is dedicated to the CATPositiveOrientation relative to the given CATFace
  // The second index [1] is dedicated to the CATPositiveNegative relative to the given CATFace
  // 4 possibles configurations :
  // 1. iFace doesn't belong to the input CATBody : 
  //     all the returned pointers are NULL
  // 2. iFace belongs to a CATShell directly referenced by the input CATBody : 
  //     one and only one oPosNegShells is not NULL and its CATLocation is supposed to be CATLocationIn3DSpace, the other pointers are all NULL
  // 3. iFace is contained by one and only volume in the partition of the input CATBody : 
  //     one oPosNegShells is not NULL and its CATLocation is supposed to be CATLocationOuter, CATLocationInner or CATLocationFull, oLump is not NULL
  //     in case of CATLocationOuter or CATLocationInner, only one oPosNegSideVolumes (same index than oPosNegShells) is not NULL (BoundingLump case)
  //     in case of CATLocationFull, the 2 oPosNegSideVolumes have the same not NULL value (InsideLump case)
  // 4. iFace is shared by 2 different volumes in the partition of the input CATBody
  //     all the returned pointers are not NULL and different from each other.
  //     the 2 oPosNegLocations are supposed to be CATLocationOuter (at least one) or CATLocationInner (at most one)

  virtual void GetTopObjectsContainingFace(CATFace & iFace, CATShell * oPosNegShells[2], CATLocation oPosNegLocations[2], CATVolume * oPosNegSideVolumes[2], CATLump * &oLump) = 0;


  // ------------------------------------------------------------------------------------------------------------
  /**
  * Create body with a subset of volumes belonging to the partition
  */
  // ------------------------------------------------------------------------------------------------------------

  // Create a new CATBody containing a subset of volumes contained by iPartitionBody
  // The option iComplementaryMode allows the caller to pilot the behavior, removing (instead of keeping) the input set of volumes.
  // The option ioRemovedFaces allows the caller to know which faces belonging to the PartitionBody won't belong to the returned body
  // returns NULL if one of the input volume doesn't belong to iPartitionBody, or if the list of volumes to keep is empty
  
  virtual CATBody * CreateBodyContainingVolumes(ListPOfCATCell & oListOfVolumesToExtract, CATBoolean iComplementaryMode=FALSE, ListPOfCATFace * ioRemovedFaces=NULL) = 0;


  // Create a new CATBody containing one single volume contained by iPartitionBody
  // The option ioRemovedFaces allows the caller to know which faces belonging to the PartitionBody won't belong to the returned body
  // returns NULL if the input volume doesn't belong to iPartitionBody

  virtual CATBody * CreateBodyContainingOneSingleVolume(CATVolume & iVolume, ListPOfCATFace * ioRemovedFaces=NULL) = 0;

    
  // ------------------------------------------------------------------------------------------------------------
  /**
  * Create surfacic body with a subset of faces
  */
  // ------------------------------------------------------------------------------------------------------------

  // Create a new CATBody containing all the faces bounding the volume partition
  // Some of those faces may bound a cavity if any
  // The option iOutwardMatterOrientation allows the caller to invert (setting to TRUE) the global orientation of the returned surfacic body
  // The option ioRemovedFaces allows the caller to know which faces belonging to the PartitionBody won't belong to the returned body
  // returns NULL if the volume partition is empty or invalid

  virtual CATBody * CreateSurfacicBodyEnvelopingPartition(CATBoolean iOutwardMatterOrientation=FALSE, ListPOfCATFace * ioRemovedFaces=NULL) = 0;


protected:

  /**
  * Constructor dedicated to implementation derived class only
  * Use CATPGMCreateVolumePartitionBodyToolKit instead
  */
  CATPGMVolumePartitionBodyToolKit();
};

/**
* Creates a ToolKit dedicated to a CATBody containing volumes,
* @param iPartitionBody
* The CATBody containing volumes, connected in a single lump or not, partitioned or not 
* (all topological configurations are supported)
* @param iConfig
* The pointer to the CATSoftwareConfiguration to take advantage of versioning mechanism (optional argument)
* @return
* The pointer to the created ToolKit instance. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByCATGMModelInterfaces
  CATPGMVolumePartitionBodyToolKit * CATPGMCreateVolumePartitionBodyToolKit(CATBody * iPartitionBody, CATSoftwareConfiguration * iConfig);

#endif // !CATPGMVolumePartitionBodyToolKit_H
