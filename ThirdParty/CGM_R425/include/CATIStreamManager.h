#ifndef CATIStreamManager_h
#define CATIStreamManager_h

/* 
* @COPYRIGHT DASSAULT SYSTEMES 2012
* -------------------------------------------------------------------------------------------------
*   Interface for implementation of manager for streaming of data for phoenix infrastructure
*   manipulated through a CATechModelData_Get instance
* -------------------------------------------------------------------------------------------------
*/

// System
#include "CATBaseUnknown.h"

// CATMathStream
#include "ExportedByCATTechTools.h"

// BSFBuildtimeData
#include "CATIAV5Level.h"

// Forward declarations
class CATUnicodeString;
class CATIDataStreamer;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATIStreamManager;
#else
extern "C" const IID IID_CATIStreamManager;
#endif

class ExportedByCATTechTools CATIStreamManager : public CATBaseUnknown
{
  CATDeclareInterface;

public:

  /*
  * GetRepStreamer : Gets the streamer class necessary for streaming/unstreaming
  *                  of CATRep's to/from *.cgr or *.uvr files
  */
  virtual CATIDataStreamer * GetRepStreamer() = 0;

  /*
  * GetPolyBodyStreamer : Gets the streamer class necessary for streaming/unstreaming
  *                       of CATPolyBody's to/from *.poly files
  */
  virtual CATIDataStreamer * GetPolyBodyStreamer() = 0;

  /*
  * GetBVHTreeStreamer : Gets the streamer class necessary for streaming/unstreaming
  *                      of CATBVHTree's to/from *.bvh files
  */
#ifdef CATIAR214
  virtual CATIDataStreamer * GetBVHTreeStreamer() = 0;
#endif

  /*
  * GetPolygon2DStreamer : Gets the streamer class necessary for streaming/unstreaming
  *                        of CATPolyPolygon2D's to/from *.txt files
  */
  virtual CATIDataStreamer * GetPolygon2DStreamer() = 0;

  /*
  * GetV4ModelStreamer : Gets the streamer class necessary for streaming/unstreaming
  *                      of V4Model's to/from *.model files
  */
  virtual CATIDataStreamer * GetV4ModelStreamer() = 0;

  /*
  * SetCaptureDirectory : Set the directory path into which data is to be streamed.
  *                       To be set by the extension once a phoenix transaction is
  *                       started, relevant only in the capture context
  */
  virtual void SetCaptureDirectory(const CATUnicodeString & iStreamDirectory) = 0;

  /*
  * GetCaptureDirectory : Get the directory path into which data is to be streamed.
  *                       Requested by the CATech3dData instance for passing the path
  *                       to the different streamers
  */
  virtual const CATUnicodeString & GetCaptureDirectory() const = 0;
};

#endif
