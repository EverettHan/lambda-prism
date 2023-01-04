/* -*-C++-*- */

#ifndef CATlsoFile_H
#define CATlsoFile_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : class to debug with files.

=============================================================================
                The options
                -----------

Set CATLSOFile_On  =0/1		              To turn on the file creation
Set CATLSOFile_In  =0/1
Set CATLSOFile_Out =0/1		              Default value 1, to pilote the output.
Set CATLSOFile_Data=0/1

Choose to merge all files
Set CATLSOFile_OneFile=0/1		          Default value 0

Choose the output
Set CATLSOFile_OutputPath=D:\tmp / console 	Default value E:\tmp

Choose the object you want to display
Set CATLSOFile_"Name"=0/1		            If there are no set, default value 1.
Set CATLSOFile_PersistentInfra=1	      If there is one set, default value 0.

=============================================================================
                PPT documentation
                -----------------

DeclarativeOperators.tst\LSODoc.d\LSO_Debug\CATLSOFile_EasyWayToCreateTextFile.pptx

=============================================================================
*/
#include "PersistentCell.h"
#include "IUnknown.h"
#include "CATCGMOutput.h"

// @nocgmitf
enum CATlsoFileDataType {
  CATlsoFileDataType_IN   = 1, // For input data in the object. It's used for set method.
  CATlsoFileDataType_OUT  = 2, // For output data of the object. It's used for get method.
  CATlsoFileDataType_DATA = 3, // For inner data of the object. It's used to dump object.
  //
  CATlsoFileDataType_NBTYPES
};

//-----------------------------------------------------------------------------
// Methods for cpp file 
//-----------------------------------------------------------------------------
// @nocgmitf
ExportedByPersistentCell int            LSOFileSubscribe(const char * ipName);  // Return a LSOFileKey
// @nocgmitf
ExportedByPersistentCell void           LSOFileCreate   (void       * ipObject, int iLSOFileKey, const char * ipAdditionalName=NULL);
// @nocgmitf
ExportedByPersistentCell void           LSOFileClose    (void       * ipObject);
// @nocgmitf
ExportedByPersistentCell CATCGMOutput * LSOFileGetOutput(void       * ipObject, CATlsoFileDataType iDataType);

//-----------------------------------------------------------------------------
// Methods to manage parameters with UI 
//-----------------------------------------------------------------------------
// @nocgmitf
ExportedByPersistentCell int            GetLSOFileNbSubscriptions();
// @nocgmitf
ExportedByPersistentCell const char *   GetLSOFileObjectName     (int iLSOFileKey);
// @nocgmitf
ExportedByPersistentCell const char *   GetLSOFileDataTypeName   (CATlsoFileDataType iDataType);
// @nocgmitf
ExportedByPersistentCell int            GetLSOFile_Activated     (int iLSOFileKey, CATlsoFileDataType iDataType);
// @nocgmitf
ExportedByPersistentCell void           SetLSOFile_Activated     (int iLSOFileKey, CATlsoFileDataType iDataType, int iActivated);
// @nocgmitf
ExportedByPersistentCell const char *   GetLSOFile_OutputPath    ();
// @nocgmitf
ExportedByPersistentCell void           SetLSOFile_OutputPath    (const char * iOutputPath);
// @nocgmitf
ExportedByPersistentCell const char *   GetLSOFilePrefix         ();

#endif
