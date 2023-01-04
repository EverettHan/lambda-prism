// COPYRIGHT DASSAULT SYSTEMES 2013
//=============================================================================
// Creation YL3  Feb 2013
//
// VoB protected interface for Boolean contact check
//
//=============================================================================

#ifndef __CATTopVoBOperatorProItf_h__
#define __CATTopVoBOperatorProItf_h__

#include "CATTopVoBOperatorImpl.h"
#include "CATCGMVoBCheckOptions.h"

class CATVoBContactCheck;
class CATBody;

class CATTopVoBOperatorProItf:  public CATTopVoBOperatorImpl
{
public:
  //========================================
  // Constucteur et destructeurs
  //========================================
    /**
  * @nodoc
  * Constructor
  */
  CATTopVoBOperatorProItf(CATGeoFactory    * iFactory,
                  CATTopData       * iData,
                  CATExtTopOperator * iExtensible);
  virtual ~CATTopVoBOperatorProItf();

  //========================================
  // Methodes d'accès aux données membres
  //========================================
  //@nocgmitf
  virtual void ActiveVoBContactCheck();
  virtual CATVoBContactCheck* GetVoBContactCheck();

  virtual void ActiveWarningMode();
  //@nocgmitf

};

ExportedByCheckOperators CATTopVoBOperator *
CATCreateTopVoBOperatorProItf(CATGeoFactory * iFactory,
                        CATTopData    * iData,
                        CATBody       * iBodyToCheck,
                        const CATCGMVoBCheckOptions & iTool);

#endif



