/* -*-C++-*- */
#ifndef CATCGMName_H
#define CATCGMName_H
// COPYRIGHT DASSAULT SYSTEMES 2002
//================================================================================
// Short name to identity a geometrical object (type and tag)
//---------------------------------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

class CATICGMUnknown;

//----------------------------------------------------------------------------------------------
// If expecting interface on V5 geometrical object
//      and CATCGMNameBadAddress  gives TRUE as returned value, 
//  It is sure that "iObject" is a Bad Address (NULL or desallocated area)
//  But we can not make sure that all non valid address have been detected.
//----------------------------------------------------------------------------------------------
ExportedByGeometricObjects CATBoolean CATCGMNameBadAddressV5(const CATICGMUnknown * iObject);

//----------------------------------------------------------------------------------------------
// For generic dump (Name and PersistentTag) 
//----------------------------------------------------------------------------------------------
class CATString;
class CATUnicodeString;
class CATCGMOutput;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#define CATCGMNameMaxLength  128

#define CATCGMNameFlagRemoved    0x0001
#define CATCGMNameFlagTag        0x0002
#define CATCGMNameFlagShortType  0x0004
#define CATCGMNameFlagFactory    0x0008
#define CATCGMNameFlagDefault    CATCGMNameFlagRemoved|CATCGMNameFlagTag

ExportedByGeometricObjects size_t CATCGMName(const CATICGMUnknown * iObject, 
                                              const size_t MaxLength, 
                                              char ioName[], 
                                              const short iFlags = CATCGMNameFlagDefault );

ExportedByGeometricObjects size_t CATCGMName(const CATICGMUnknown * iObject, 
                                             CATString & ioName,
                                             const short iFlags = CATCGMNameFlagDefault  );

ExportedByGeometricObjects size_t CATCGMName(const CATICGMUnknown * iObject, 
                                             CATUnicodeString & ioName, 
                                             const short iFlags = CATCGMNameFlagDefault  );

ExportedByGeometricObjects CATCGMOutput & CATCGMName(const CATICGMUnknown * iObject, 
                                             CATCGMOutput & ioName, 
                                             const short iFlags = CATCGMNameFlagDefault  );

ExportedByGeometricObjects ostream      & CATCGMName(const CATICGMUnknown * iObject, 
                                             ostream & ioName, 
                                             const short iFlags = CATCGMNameFlagDefault  );

#endif
