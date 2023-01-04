// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyStreamerRegistry.h
//
//===================================================================
// May 2021 Creation: NDO
//===================================================================
#ifndef CATPolyStreamerRegistry_H
#define CATPolyStreamerRegistry_H

#include "PolyStream.h"
#include "CATErrorDef.h"
#include "CATPolyStreamOptions.h"
#include "CATMathStreamVersionDef.h"

class CATMathStream;
class CATIPolyObject;
class CATIPolyLayer;
class CATPolyStreamRecord;
class CATPolyUnstreamRecord;
class CATPolyStreamerRegistryLayer;


namespace Poly
{
  /**
   * Interface to the stream and unstream functions for a class of layers.
   *
   * Registered instances of classes implementing this interface performs the stream and
   * unstream of the layers.
   */
  class LayerStreamer
  {
  public:

    /**
     * Returns the class ID of the layers.
     */
    virtual const CLSID& GetLayerClassID () const = 0;

    /**
     * Interface of the function that streams the layer associated to a polyhedral object.
     */
    virtual HRESULT Stream (CATMathStream& iStream, const CATIPolyObject& iPolyObject,
                            const CATIPolyLayer& iLayer) = 0;

    /**
     * Interface of the function that unstreams the layer associated to a polyhedral object.
     */
    virtual HRESULT Unstream (CATMathStream& iStream, CATIPolyObject& iPolyObject,
                              CATIPolyLayer*& oLayer) = 0;
  };
}


/**
A class to record various polyhedral streamers for various classes (layers).
*/
class ExportedByPolyStream CATPolyStreamerRegistry
{

public:

  ~CATPolyStreamerRegistry ();

  /**
   * Returns a new default streamer registry instance.
   * The default native streamers for various layers (including flag layer, texture layer and
   * support) are registered on this instance.
   *
   * @param iLayerFilter
   *    A filter to specify which layer should be streamed.  By default, all native polyhedral layers
   *    are streamed (given they are supported for the given stream version.)
   * @param iNativeStream
   *   A flag to specify how the objects should be streamed. 
   *   This applies only to non-native polyhedral objects which are streamed by specific streamers.
   *   This is the default.  To stream non-native polyhedral objects as native polyhedral objects,
   *   sets this option to true.
   */
  static CATPolyStreamerRegistry* NewInstance (unsigned int iLayerFilter = CATPolyStreamOptions::eDefault,
    bool iNativeStream = false);

  /**
   * Returns a filter to disable the streaming or unstreaming of various native layers.
   */
  inline unsigned int LayerFilter () const;

  /**
   * Returns true to stream all objects as native polyhedral objects.
   */
  inline bool NativePolyhedralStream () const;

public:

  /**
   * Registers the stream and unstream functions for a class of layers.
   * The life-cycle of the registered streamer should be greater than that of the options.
   */
  HRESULT Register (Poly::LayerStreamer& streamer);

  /**
   * Returns true if a layer is streamable meaning a streamer is registered in the registry
   * for a given stream version.
   */
  bool IsStreamable (CATCGMStreamVersion iVersion, const CATIPolyLayer& iLayer) const;

public:

  /**
   * Streams a layer of registered class id.
   */
  HRESULT Stream (CATMathStream& iStream, const CATIPolyObject& iPolyObject, const CATIPolyLayer& iLayer,
    CATPolyStreamRecord& ioRecords) const;

  /**
   * Unstreams a layer of registered class id.
   */
  HRESULT Unstream (CATMathStream& iStream, CATIPolyObject& iPolyObject, CATIPolyLayer*& oLayer,
    CATPolyUnstreamRecord& ioRecords) const;

private:

  CATPolyStreamerRegistryLayer& _StreamerLayers;
  unsigned int _LayerFilter;
  mutable CATCGMStreamVersion _StreamVersion;
  bool _NativeStream;

  CATPolyStreamerRegistry ();

  void RegisterAllNativeStreamers (CATCGMStreamVersion iVersion) const;

};

inline unsigned int CATPolyStreamerRegistry::LayerFilter () const
{
  return _LayerFilter;
}

inline bool CATPolyStreamerRegistry::NativePolyhedralStream () const
{
  return _NativeStream;
}

#endif
