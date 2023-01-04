// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2014
// ................................
//
// IZE : Refeaturing : Communication object creator
// To be specialized by the application to be able to create Feature Tree
// ----------------------------------------------------------------------------//

#ifndef CATRefeatureSeedFactory_H
#define CATRefeatureSeedFactory_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"

#include "CATBoolean.h"
#include "CATRefeatureSeed.h"

class CATCGMFeatSpec;

class ExportedByCATGMModelInterfaces CATRefeatureSeedFactory
{
public: 
  CATRefeatureSeedFactory(); 
  virtual ~CATRefeatureSeedFactory();

  virtual CATRefeatureSeed* CreateFilletSeed(CATCGMFeatSpec *iSpec);
  virtual void UpdateFromSeed(CATRefeatureSeed * iUpdatedSeed);
  
protected:

private:
};


#endif

