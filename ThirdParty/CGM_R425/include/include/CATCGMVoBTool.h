// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
// Creation JHN  23/05/2011
//
// VoB check options creation. 
// 3 options :
//    - intersection between two cells in the body
//    - self intersection in geoemtry inside topological boundaries
//    - check of non manifold configuration (contact of more than two faces on an edge, contact of several set of connex faces on one vertex)
//=============================================================================

#ifndef __CATCGMVoBTool_h__
#define __CATCGMVoBTool_h__
#include "CATCGMVoBCheckOptions.h"
#include "CATGMModelInterfaces.h"

struct ExportedByCATGMModelInterfaces CATCGMVoBTool
{
  CATCGMVoBCheckOptions _VoBOptions;
  CATBoolean _VoBBackGround;

  CATCGMVoBTool();
  // copy constructor 
  CATCGMVoBTool(const CATCGMVoBTool & iOther);
  //equal operator
  CATCGMVoBTool& operator=(const CATCGMVoBTool & iOther);

};



#endif
