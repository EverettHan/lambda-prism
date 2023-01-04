//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2005                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttp                                                                  *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation aout 2005                                           adt         *
//*===========================================================================*
#ifndef CATSYSHTTPSTREAMER_H
#define CATSYSHTTPSTREAMER_H
#include <stdlib.h>
#include <memory.h>
#include "CATHttp.h"

#include "CATHttpClient.h"
#include "CATHttpFlags.h"


class CATHttpDriver;


class ExportedByJS0HTTP  CATSysHttpStreamer
{
  friend class CATHttpDriver;
  public:
  CATSysHttpStreamer () :_Driver(NULL){};
  virtual ~CATSysHttpStreamer(){};

/**
 * Gives the streamer type.
 * <br><b>Role</b>:  Retrieves if the streamer will send in chunked mode, or
 * if not the size of the body to be sent.
 * @param oLenToStream [out]
 *	Size of the body if applicable
 * @param oIsChunkable [out]
 *	null if the transfert in not chunked. otherwise, the client will
 *      unse the transfert encoding chunked and do not consider
 * @return
 */
  virtual HRESULT GetType ( size_t &oLenToStream, int &oIsChunkable)=0;


/**
 * Streams data.
 * <br><b>Role</b>:  Streams a chunk of data. The implementation must use 
 * the Send method that is provided as adaptor to physicaly send the data
 * @param oStreamed [out]
 *	Size of the sent chunk
 * @param oNoMoreData [out]
 *	null if there are still data to send after this chunk
 * @return
 */
  virtual HRESULT Stream (size_t &oStreamed, int &oNoMoreData)=0;

/**
 * Rewinds the streams.
 * <br><b>Role</b>:  Indicates the streamer that it must reinitate the process
 * because it will be called again to resend all data for exemple in case of
 * redirection>
 * @return
 */
  virtual HRESULT Rewind ()=0;


  void  SetDriver ( CATHttpDriver *iDrv) ;

 protected:
  HRESULT Send (const char *iBuff, size_t iLen);

 private:
  CATHttpDriver *_Driver;
 
};


#endif
