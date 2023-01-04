#ifndef CATExtClonableManager_h_
#define CATExtClonableManager_h_
/** @CAA2Required */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//    Limited availability :  attribute's reporting
//    small abstraction for genuine "clonable operators"
//=============================================================================
#include "YP00IMPL.h"

class CATICGMObject;

/**
*   Limited availability :  attribute's reporting
*      restricted to entities'holder : Body/Face/Edge/Vertex holder
*      but genuine to Clone/TransfoManager (and partially to SmartDuplicator) services
*/
class ExportedByYP00IMPL CATExtClonableManager
{
public :

  /**
  * ReadImage.
  */
  virtual CATICGMObject   *ReadImage(CATICGMObject *) const = 0;
 
  /**
  * Destructor.
  */
  virtual ~CATExtClonableManager();

protected :

  /**
  * Constructor.
  */
  CATExtClonableManager();


private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATExtClonableManager(const CATExtClonableManager &iCopy);
  CATExtClonableManager& operator=(const CATExtClonableManager &iCopy);
};


//------------------------------------------------------------------------
// Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
//------------------------------------------------------------------------
extern "C" ExportedByYP00IMPL void  catcgmreportdone();  
extern "C" ExportedByYP00IMPL void  catcgmreporttodo();  


#endif
