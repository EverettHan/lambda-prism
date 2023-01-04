// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATInitialPoint3Sur :
// A class of initial point for CATHomotopy3Sur
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// Aug. 97     Creation                       J. Peter
// Octobre 2004 - Versionning Interne - EAB
//========================================================================== 

#ifndef CATInitialPoint3Sur_H
#define CATInitialPoint3Sur_H

#include "Y30C3XGG.h"
#include "CATSurParam.h"
#include "CATCGMVirtual.h"

class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATInitialPoint3Sur  : public CATCGMVirtual
 {    
  private:
    const CATSurParam _surparam1;
    const CATSurParam _surparam2;
    const CATSurParam _surparam3;
    CATSoftwareConfiguration * _Config;
   
  public:
  // destructor -----------------------------------
  //
    ~CATInitialPoint3Sur();
  //
  // constructor ----------------------------------
  //
    CATInitialPoint3Sur(CATSoftwareConfiguration * iConfig,
                        CATSurParam & surparam1,
                        CATSurParam & surparam2,
                        CATSurParam & surparam3);
    //do not use - Use the constructor with CATSoftwareConfiguration
    CATInitialPoint3Sur(CATSurParam & surparam1,
                        CATSurParam & surparam2,
                        CATSurParam & surparam3);
    CATInitialPoint3Sur(CATInitialPoint3Sur & copie);
  //  
  // get methods -------------------------------
  //
    void GetSurParam(CATLONG32 i, CATSurParam & oSurParam) const;
};


#endif
