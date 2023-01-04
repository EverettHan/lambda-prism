#ifndef CATPGMChain_h_
#define CATPGMChain_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
//#include "CATCGMVirtualItf.h"

#include "CATIPGMVirtual.h"
//#include "CATDataType.h"

class CATBody;
class CATCGMChainLinkManager;
class CATCGMStream;
class CATCGMUnit;
class CATGeoFactory;
class CATString;
class CATCGMChain;

extern ExportedByCATGMModelInterfaces IID IID_CATPGMChain;



class ExportedByCATGMModelInterfaces CATPGMChain 
{
protected:
  /**
   * Constructor
   */
  CATPGMChain();

public:
  /**
   * Destructor
   */
  virtual ~CATPGMChain();
 
  //-------------------------------------------------------------------------
  // Monitoring the recording process  
  //-------------------------------------------------------------------------
  static void SetCurrentCATCGMChain(CATPGMChain *iChain);

  static CATPGMChain *GetCurrentCATCGMChain();
 
  //-------------------------------------------------------------------------
  // MODIFY : to modify the chain structure  
  //-------------------------------------------------------------------------
  virtual void Inactivate(CATCGMUnit *iunit) = 0;

  virtual void DeleteInactiveUnits() = 0;

};

ExportedByCATGMModelInterfaces CATPGMChain *CATPGMCreateCGMChain(CATGeoFactory *ifactory);

#endif /* CATPGMChain_h_ */
