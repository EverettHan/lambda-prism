#ifndef Data_GeometricObjectsCGM_h
#define Data_GeometricObjectsCGM_h

// COPYRIGHT DASSAULT SYSTEMES  1999
//-----------------------------------------------------------------------------
// Context : generic methods of Data_GeometricObjectsCGM
//-----------------------------------------------------------------------------
/**
* @level Private
* @usage U1
*/
#include "CATCGMStreamVersion.h"
#include "CATBoolean.h"
class CATCGMStream;

#define Data_GeometricObjectsCGM_Stream             \
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const; \
  virtual void Stream( CATCGMStream& Str ) ;        \
  virtual void UnStream( CATCGMStream& Str, CATLISTP(CATICGMObject)& ListDependencies ) ;

 
#endif
