// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2014
// ................................
//
// IZE : Refeaturing : Communication object with the application
// ----------------------------------------------------------------------------//

#ifndef CATRefeatureSeed_H
#define CATRefeatureSeed_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"

#include "CATBoolean.h"
#include "CATBody.h"
#include "CATCGMJournalList.h"

class CATCGMFeatSpec;

class ExportedByCATGMModelInterfaces CATRefeatureSeed
{
public: 
  CATRefeatureSeed(CATCGMFeatSpec *iSpec); 
  virtual ~CATRefeatureSeed();

  // Mandatory methods
  CATCGMFeatSpec* GetSpec();
  CATBody * GetResBody();
  CATCGMJournalList * GetResJournal();

  // For mother applicative class
  virtual int AddAsDatum(CATBody*  iBody);
  virtual int AddAsRootDatum(CATBody*  iBody);
  
  // For children applicative classes
  virtual void Build() = 0;
  virtual void Deactivate() = 0;
  virtual void Fallback() = 0;
  
protected:

  void SetResBody(CATBody *iResBody);
  void SetResJournal(CATCGMJournalList *iResJournal);

private:
  CATCGMFeatSpec    *_Spec;
  CATBody           *_ResBody;
  CATCGMJournalList *_ResJournal;
};


#endif

