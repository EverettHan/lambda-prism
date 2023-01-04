//============================================================================= 
// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Working Object  of the CATGMNodeLauncher
//
//     
#ifndef CATGMMultiProcCallbacks_H
#define CATGMMultiProcCallbacks_H

#include "CATIACGMLevel.h"
#ifdef CATIAR424

#include "CATGMModelInterfaces.h"
#include "CATMathInline.h"
#include <functional>
#include "CATSysErrorDef.h" // HRESULT


class CATGMExchangeChannel;
class CATGMDataPool;

namespace EK {
  class Node;
  class Channel;
}

namespace JSON {
  class JIStream;
}


typedef std::function<HRESULT(const JSON::JIStream  &iInput, 
                              CATGMExchangeChannel  &iChannel)> CallbackJson;

typedef std::function<HRESULT(const CATGMDataPool  & iPool,
                              CATGMExchangeChannel & iChannel )> CallbackPoolData;


class ExportedByCATGMModelInterfaces CATGMMultiProcCallbacks
{
public:

  CATGMMultiProcCallbacks();

  INLINE CATGMMultiProcCallbacks(CallbackJson iOnJson) :
      _OnJson(iOnJson) {};
  INLINE CATGMMultiProcCallbacks(CallbackPoolData iOnChannel) : 
      _OnData(iOnChannel) {};

  INLINE CATGMMultiProcCallbacks(CallbackJson iOnJson, CallbackPoolData iOnChannel) :
    _OnJson(iOnJson), _OnData(iOnChannel) {};


  virtual ~CATGMMultiProcCallbacks();

public :
  CallbackJson       GetOnJson() const { return _OnJson; }
  CallbackPoolData   GetOnPoolData() const { return _OnData; }


private :
  CallbackJson      _OnJson;
  CallbackPoolData  _OnData;

};

#endif

#endif

