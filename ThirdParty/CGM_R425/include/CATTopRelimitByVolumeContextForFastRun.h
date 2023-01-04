#ifndef CATTopRelimitByVolumeContextForFastRun_h
#define CATTopRelimitByVolumeContextForFastRun_h

#include "CATContextForFastRun.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATTopRelimitByVolumeContextForFastRun : public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopRelimitByVolumeContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATTopRelimitByVolumeContextForFastRun(); // -> delete can't be called
};

#endif
