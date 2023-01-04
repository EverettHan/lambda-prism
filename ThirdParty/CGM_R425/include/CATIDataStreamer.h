#ifndef CATI3DDataStreamer_h
#define CATI3DDataStreamer_h

// System
#include "CATBaseUnknown.h"

// Forward declarations
class CATUnicodeString;

//-------------------------------------------------------------------------------------------------
//  C++ Interface(non CAA) for implementation of streamer for streaming of data for phoenix 
//  infrastructure
//-------------------------------------------------------------------------------------------------

class CATIDataStreamer
{
public:

  /*
  * Stream : Streams the input data into appropriate file format.
  *          The correct type to choose is based on the actual streamer 
  *          used. This inturn is controlled by the CATIStreamStreamManager
  * @param ipData : Pointer to the data to be streamed
  * @param iStreamDirectory : The directory into which the data is to be streamed
  * @return
  *   Returns S_OK if streaming succeeds without any issues
  */
  virtual HRESULT Stream(void * ipData, const CATUnicodeString & iStreamDirectory) = 0;


  /*
  * StreamVaultedData : In some case(like V4 entities), data is not streamed immediately as multiple entities
                        could be present in a file and we dont want them to be streamed separately. It is just
                        stored temporarily. This method streams such data
  */
  virtual HRESULT StreamVaultedData()
  {
    return E_NOTIMPL;
  }


  /*
  * GetStreamedFileData : Gets data associated with the file 
  * @param oFileName : File name for the streamed file (with extension)
  * @param iFileData : Some data associated with the file
  */
  virtual void GetStreamedFileData(CATUnicodeString   & oFileName, 
                                   void              ** iFileData = (void **) NULL) const = 0;

  /*
  * Unstream : Unstreams the passed file and returns a pointer to the data.
  *            The correct type to choose is based on the actual streamer 
  *            used. This inturn is controlled by the CATIStreamStreamManager
  * @param iFilePath : File path for the file to unstreamed
  * @param ippAddInfo : Pointer to additional information needed for unstreaming the data
  * @param opData : Pointer to the data which is unstreamed
  * @return
  *   Returns S_OK if unstreaming succeeds without any issues
  */
  virtual HRESULT Unstream(const CATUnicodeString   & iFilePath, 
                           void                    ** ippAddInfo,
                           void                    *& opData) const = 0;
  
};

#endif
