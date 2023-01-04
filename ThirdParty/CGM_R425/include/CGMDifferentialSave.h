#ifndef CGMDifferentialSave_h
#define CGMDifferentialSave_h

// COPYRIGHT DASSAULT SYSTEMES  2001
#include "ExportedByCATCGMFusion.h"
#include "CATCGMStreamDifferentialSave.h"
#include "CATCGMNewArray.h"

//===================================================================================================
//  Le proxy d'implementation du fichier NCGM  CGMStreamDifferentialSave
//===================================================================================================
class ExportedByCATCGMFusion CGMDifferentialSave : public CATCGMStreamDifferentialSave
{
public :
  CGMDifferentialSave(CATGeoFactory* iFactory, const char iFilename[]);
  virtual ~CGMDifferentialSave();
  CATCGMNewClassArrayDeclare;

  void Save();
};

#endif
