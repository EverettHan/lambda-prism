// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATInitialPointCrvSur :
// A class of initial point for CATHomotopyCrvSur
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// Aug. 97     Creation                       J. Peter
// Octobre 2004 - Versionning Interne - EAB
//========================================================================== 

#ifndef CATInitialPointCrvSur_H
#define CATInitialPointCrvSur_H

#include "CATSurParam.h"
#include "CATCrvParam.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
//DG
//class CATInitialPointCrvSur
#include "Y30C3XGG.h"
class ExportedByY30C3XGG CATInitialPointCrvSur : public CATCGMVirtual
 {    
  private:
   const CATSurParam _surparam;
   const CATCrvParam _crvparam;
   CATSoftwareConfiguration * _Config;
   
  public:
  // destructor -----------------------------------
  //
    ~CATInitialPointCrvSur();
  //
  // constructor ----------------------------------
  //
    //Do not use - Use the Constructor with CATSoftwareConfiguration
    CATInitialPointCrvSur(CATCrvParam & crvparam, CATSurParam & surparam);
    CATInitialPointCrvSur(CATSoftwareConfiguration * iConfig,
      CATCrvParam & crvparam, CATSurParam & surparam);
    CATInitialPointCrvSur(CATInitialPointCrvSur & copie);
  //  
  // get methods -------------------------------
  //
    INLINE CATSurParam GetSurParam() const;
    INLINE CATCrvParam GetCrvParam() const; 
};

// --------------------------------------------------
// INLINE get methods -------------------------------
// --------------------------------------------------

INLINE CATSurParam CATInitialPointCrvSur::GetSurParam() const
{
   return _surparam;
}

INLINE CATCrvParam CATInitialPointCrvSur::GetCrvParam() const 
{
   return _crvparam; 
}

#endif
