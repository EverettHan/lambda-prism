/* -*-c++-*- */
#ifndef CATCGMSetting_h
#define CATCGMSetting_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2006
//-----------------------------------------------------------------------------
//  Manage CGMSetting 
//-----------------------------------------------------------------------------
#include "YN000MAT.h"
#include "CATErrorDef.h"
#include "CATCGMScaleCategoryDef.h"

// Read GeometricScale Setting
ExportedByYN000MAT HRESULT ReadSettingGeometricScale  (double &ioScale);

// Read XScale Setting
ExportedByYN000MAT CATCGMScaleCategory ReadCATCGMScaleCategoryEnvValue(double &ioScale);

// Check CATCGMScaleCategory Authorisation 
// return 0 if unstream/creation/stream not allowed
// return 1 if stream not allowed
// return 2 if unstream/creation/stream allowed
ExportedByYN000MAT int IsCATCGMScaleCategoryAllowed(const  CATCGMScaleCategory iScaleCategory);

// Check CATCGMSmallScale activation 
ExportedByYN000MAT int IsSmallScaleForR14_Activated();

// Check CATCGMSmallScale activation 
ExportedByYN000MAT int IsCGMBigScaleOn_Activated();
ExportedByYN000MAT int IsCGMScaleValue_Activated();

// Check InternalDS 
ExportedByYN000MAT int IsCGMInternalDS_Activated();

ExportedByYN000MAT int IsCGMCATToleranceError_Activated();

#endif

