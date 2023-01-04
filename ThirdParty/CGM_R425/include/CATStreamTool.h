#ifndef CATStreamTool_h
#define CATStreamTool_h

#include "ExportedByCATTopologicalObjects.h"   
#include "CATBoolean.h"
#include <string.h>

class CATCGMStream;

typedef void (*StreamingFunction)(CATCGMStream &, void *);

class ExportedByCATTopologicalObjects CATStreamTool
{
public:

  CATStreamTool();

  virtual ~CATStreamTool();

  void CreateBufferForWriteAndRead(size_t iEstimatedBufferSize = 512);

  void CreateBufferForFileWriting(const char * iFilename);

  void CreateBufferForFileReading(const char * iFilename);

  void FillBuffer(StreamingFunction iWritingFunction, void * iAdditionalObject);

  void InterpretBuffer(StreamingFunction iReadingFunction, void * iAdditionalObject);

  void WriteBufferToDestination(CATCGMStream & ioDestination) const;

  void ReadBufferFromSource(CATCGMStream & iSource);

  static CATBoolean BuffersAreIdentical(CATStreamTool & iTool1, CATStreamTool & iTool2);

  static int GetNumberOfStartingEqualBytes(CATStreamTool & iTool1, CATStreamTool & iTool2);

private:
  CATStreamTool(const CATStreamTool &);

  CATCGMStream * _Buffer;
};

#endif
