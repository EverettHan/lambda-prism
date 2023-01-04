#ifndef CATCGAMeasureDefine_h
#define CATCGAMeasureDefine_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================

// For depths
#define CATCGAMeasureCSI_Depth_Root         0x0001
#define CATCGAMeasureCSI_Depth_Type         0x0002
#define CATCGAMeasureCSI_Depth_TypeName     0x0004

// For commands
#define CATCGAMeasureCSI_Domain_Command     0x0001
#define CATCGAMeasureCSI_Domain_Feat        0x0002
#define CATCGAMeasureCSI_Domain_GM          0x0004
#define CATCGAMeasureCSI_Domain_Part        0x0008
#define CATCGAMeasureCSI_Domain_DataIO      0x0010
#define CATCGAMeasureCSI_Domain_Afr         0x0020
#define CATCGAMeasureCSI_Domain_Unknown     0x0080


// For Criteria
#define CATCGAMeasureCSI_Criteria_CPU         0x0001
#define CATCGAMeasureCSI_Criteria_ELS         0x0002
#define CATCGAMeasureCSI_Criteria_Ticks       0x0004
#define CATCGAMeasureCSI_Criteria_MEM         0x0008
#define CATCGAMeasureCSI_Criteria_DLL         0x0010
#define CATCGAMeasureCSI_Criteria_DISK        0x0020
#define CATCGAMeasureCSI_Criteria_HEAP        0x0040


// For Criteria
//      Feature with  non persistent GM Purged  at end of each Update (WorkingSet Peak)
#define CATCGAMeasureForce_FeatPurge      0x0001
//      CGMGEOM (CATGeoFactory) with No Full Loading (systematic Partial + Complementary)   
#define CATCGAMeasureForce_PartialLoad    0x0002
//      CATGeoFactory Cleaned at Each Load 
#define CATCGAMeasureForce_CleanLoad      0x0004

 
// For more precise Memory Managements
#define CATCGAMeasureHeapIdx_NbHeap         0
#define CATCGAMeasureHeapIdx_VirtualBytes   1
#define CATCGAMeasureHeapIdx_NbBlocks       2
#define CATCGAMeasureHeap_NbCriteria        3


#endif

