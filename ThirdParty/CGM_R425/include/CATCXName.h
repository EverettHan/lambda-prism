/* -*-C++-*- */
#ifndef CATCXName_H
#define CATCXName_H
// COPYRIGHT DASSAULT SYSTEMES 2002
//================================================================================
// Short name to identity a geometrical object (type and tag)
//---------------------------------------------------------------------------
#include "ExportedByCATCGMFusion.h"
#include "CATCGMName.h"

class CATCGMObject;

ExportedByCATCGMFusion size_t CATCXName(const CATCGMObject * iObject, 
                                              const size_t MaxLength, 
                                              char ioName[], 
                                              const short iFlags = CATCGMNameFlagDefault );

ExportedByCATCGMFusion size_t CATCXName(const CATCGMObject * iObject, 
                                             CATString & ioName,
                                             const short iFlags = CATCGMNameFlagDefault  );

ExportedByCATCGMFusion size_t CATCXName(const CATCGMObject * iObject, 
                                             CATUnicodeString & ioName, 
                                             const short iFlags = CATCGMNameFlagDefault  );

ExportedByCATCGMFusion CATCGMOutput & CATCXName(const CATCGMObject * iObject, 
                                             CATCGMOutput & ioName, 
                                             const short iFlags = CATCGMNameFlagDefault  );

ExportedByCATCGMFusion ostream      & CATCXName(const CATCGMObject * iObject, 
                                             ostream & ioName, 
                                             const short iFlags = CATCGMNameFlagDefault  );

#endif
