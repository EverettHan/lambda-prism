#ifndef __CATUtilForFastRun_H__
#define __CATUtilForFastRun_H__
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
// 
//==========================================================================
// Nov. 10  Outil FastRun                                                WQO
//==========================================================================

#include "CATGMModelInterfaces.h"
#include "IUnknown.h"
#include "CATFastRunStatus.h"
class CATSoftwareConfiguration;

// Est de mise a niveau pour courir vite?
ExportedByCATGMModelInterfaces CATUpgradeForFastRun IsToUpgradeForFastRun(const IID &iIID, 
                                                                          CATSoftwareConfiguration * pConfig);

#endif

