/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATActiveCloneOnLimits :
// Clone a Curve or a Surface inside the given limits. 
//=============================================================================
//=============================================================================
// Oct. 03  Creation                          PFV
//=============================================================================
#ifndef CATActiveCloneOnLimits_H 
#define CATActiveCloneOnLimits_H 

#include "CATCGMOperator.h"
#include "Y30UIUTI.h"
#include "CATSurLimits.h"
#include "CATCreateActiveCloneOnLimits.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;


class ExportedByY30UIUTI CATActiveCloneOnLimits : public CATCGMOperator
{
public:
  virtual ~CATActiveCloneOnLimits ();

/**
 * Runs <tt>this</tt> operator.
 * @return
 * The information value :
 *
 *
 */
  virtual int Run () = 0;

/**
 * Returns the new surface computed by <tt>this</tt> operator.
 * @return
 * The pointer to the new surface.
 * Pointer is 0 if an error has occurred.
 */
  virtual CATSurface * GetResult () = 0;

protected:
CATActiveCloneOnLimits(CATGeoFactory * iFactory);

private:
CATActiveCloneOnLimits(const CATActiveCloneOnLimits &);
void operator = (const CATActiveCloneOnLimits &);
};

#endif



