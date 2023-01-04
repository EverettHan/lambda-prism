//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessCacheStreamSwitch
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef CATTessCacheStreamSwitch_H
#define CATTessCacheStreamSwitch_H

#include "CATBoolean.h"
#include "TessCacheObjects.h"

#define CATTessCacheIsStreamable
#define CATTessCacheStreamingEnabled CATTessCacheStreamSwitch::IsStreamingEnabled()

////////////////////////////////////////////////////////////////////////////////////////////////
// By default tess cache streaming is disabled at the moment
// But one may want to temporarily enable streaming for the purpose of debugging.
// This switch provides a way to enable/disable streaming of tess cache
// 
// To temporarily enable streaming, use CATTessCacheStreamSwitch::EnableStreaming() 
// followed by CATTessCacheStreamSwitch::DisableStreaming() as soon as streaming is over.
// Make sure to have a disable streaming in a catch block in order to ensure that streaming
// does not remain enabled in the event of a throw. Here's a sample:
//
//    // Temporarily enable streaming
//    CATTessCacheStreamSwitch::EnableStreaming();
//
//    CATTry
//    {
//      // code for streaming, for example:
//      CATCGMDebug::Save(Factory, FileName);
//    }
//    CATCatch (CATError, err)
//    {
//      // Disable streaming in catch block
//      CATTessCacheStreamSwitch::DisableStreaming();
//      CATRethrow;
//    }
//    CATEndTry;
// 
//    // Disable streaming outside the try/catch block
//    CATTessCacheStreamSwitch::DisableStreaming();
//
//
// Note that during unstreaming, it is not necessary to enable this switch.
//

class ExportedByTessCacheObjects CATTessCacheStreamSwitch
{
public:
  // Gets the current state of the switch
  static CATBoolean IsStreamingEnabled();

  static void EnableStreaming();
  static void DisableStreaming();

protected:
  static CATBoolean _IsStreamingEnabled;
};

#endif // !CATTessCacheStreamSwitch_H

