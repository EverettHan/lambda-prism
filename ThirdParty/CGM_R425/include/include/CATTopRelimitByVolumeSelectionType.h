#ifndef CATTopRelimitByVolumeSelectionType_h_
#define CATTopRelimitByVolumeSelectionType_h_

// COPYRIGHT DASSAULT SYSTEMES 2010 

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Specifies the portions of the shell to be kept after relimitation.
 * @param  CATTopRelimitByVolumeSelTypeNone
 * No result is generated.
 * @param  CATTopRelimitByVolumeSelTypeInsideVolume
 * The skin which is inside the volume is kept.
 * @param  CATTopRelimitByVolumeSelTypeOutsideVolume
 * The skin which is outside the volume is kept.
 * @param  CATTopRelimitByVolumeSelTypeOnVolumeBoundary
 * The skin which is on the volume boundary is kept.
 */ 

enum CATTopRelimitByVolumeSelectionType
{	
  CATTopRelimitByVolumeSelTypeNone             = 0x00,
  CATTopRelimitByVolumeSelTypeInsideVolume     = 0x01,
  CATTopRelimitByVolumeSelTypeOutsideVolume    = 0x02,
  CATTopRelimitByVolumeSelTypeOnVolumeBoundary = 0x04
};

#endif /* CATTopRelimitByVolumeSelectionType_h_ */
