#ifndef CGMIncrementalOpen_h
#define CGMIncrementalOpen_h

// COPYRIGHT DASSAULT SYSTEMES  2001
#include "ExportedByCATCGMFusion.h"
#include "CATCGMStreamIncrementalOpen.h"
#include "CATCGMNewArray.h"

class CATCGMStream;

//===================================================================================================
//  Le proxy d'implementation du fichier NCGM
//===================================================================================================
class ExportedByCATCGMFusion CGMIncrementalOpen : public CATCGMStreamIncrementalOpen
{
public :
  CGMIncrementalOpen(const char iFilename[]);
  CGMIncrementalOpen(CATGeoFactory* iFactory, const char iFilename[]);
  virtual ~CGMIncrementalOpen();
  CATCGMNewClassArrayDeclare;

  virtual void Open( CATGeoFactory* &ioFactory, CATCGMListOfCATULONGPTR &ioObjects );
  virtual void Append( CATGeoFactory* iFactory, CATCGMListOfCATULONGPTR &ioObjects );

protected:

  int CommonRead( CATGeoFactory**ioFactory, CATCGMStream *streamarea, CATCGMListOfCATULONGPTR &ioObjects );

  CGMIncrementalOpen(CATStreamArea *iStreamArea, const char iFilename[], CATGeoFactory* iFactory);
};

#endif
