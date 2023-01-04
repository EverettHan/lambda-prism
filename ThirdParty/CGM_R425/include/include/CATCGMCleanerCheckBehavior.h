/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */

/* -*-c++-*- */
#ifndef CATCGMCleanerCheckBehavior_H_
#define CATCGMCleanerCheckBehavior_H_

//=============================================================================
// Data for managing CGM cleaner activation and calls
//=============================================================================
// Nov. 02  Creation                                                      HCN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATCGMCheckBehavior.h"

class ExportedByGeometricObjects CATCGMCleanerCheckBehavior: public CATCGMCheckBehavior
{
public :
  CATCGMCleanerCheckBehavior(CatCGMCheckDefinition newBehavior);

  virtual ~CATCGMCleanerCheckBehavior();

  virtual CATBoolean CancelError(const CATCGMCheck::Category  anomalie,
                                 const CATICGMObject         *corrupted)const;


};


#endif
