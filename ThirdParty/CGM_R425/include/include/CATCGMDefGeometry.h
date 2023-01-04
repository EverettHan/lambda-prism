// COPYRIGHT DASSAULT SYSTEMES 1999
#ifndef CATCGMDefGeometry_H
#define CATCGMDefGeometry_H
//=============================================================================
//
// Base class designed to handle the geometrical definition 
// of a geometry based on another geomtery
//
//=============================================================================
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
//=============================================================================

#include "YP00IMPL.h"                    
#include "CATCGMVirtual.h"
#include "CATMathDef.h"
#include "CATCGMStreamVersion.h"
#include "CATBoolean.h"

class CATCGMStream;
class CATICGMUnknown;
class CATCGMQueryManager;

class ExportedByYP00IMPL CATCGMDefGeometry : public CATCGMVirtual
{
public:

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATCGMDefGeometry();
  virtual ~CATCGMDefGeometry();
  
  //-------------------------------------------------------------------------
  // For Streaming (stream all but the Curve and the type)
  //-------------------------------------------------------------------------
  virtual void Stream( CATCGMStream& Str ) =0;
  virtual void UnStream( CATCGMStream& Str ) =0;

  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const=0;
};

#endif
