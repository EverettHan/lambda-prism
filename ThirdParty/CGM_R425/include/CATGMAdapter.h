/* -*-c++-*- */
#ifndef CATGMAdapter_h
#define CATGMAdapter_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES	1999
//=============================================================================
#include "CATMathematics.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
 

class CATechAttribute;
class CATechSet;
class CATechGet;
 
/**
* Genuine common adaptor for State/Operation of GMTk 
*/
class ExportedByCATMathematics CATGMAdapter : public CATBaseUnknown
{
public:

  /**
  * GetShortName  
  */
  virtual HRESULT GetShortName(CATUnicodeString & oValue) const = 0 ;

  //===================================================================================
  // Meta description for Recording Replaying
  //    for common Replay-PlayBack-Phoenix integration
  //       same descriptive infrastructure available
  //       with CGMReplay as Proof Of Concept (2012Spring)
  //===================================================================================

  /**
  * GetRecording (generate if necessary (and before Run())
  */
  virtual CATechAttribute * GetRecording(CATechSet **iContext = NULL) const = 0 ;

  /**
  * SetRecording 
  */
  virtual HRESULT  SetRecording(CATechAttribute * iReplaying, CATechSet *iContext)  = 0 ;

  /**
  * GetReplaying 
  */
  virtual CATechAttribute * GetReplaying(CATechSet **iContext = NULL) const = 0 ;

  /**
  * SetReplaying 
  */
  virtual HRESULT  SetReplaying(CATechAttribute * iReplaying, CATechSet *iContext)  = 0 ;
};
 

#endif



