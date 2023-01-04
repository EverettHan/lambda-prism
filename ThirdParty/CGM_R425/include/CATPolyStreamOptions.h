// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyStreamOptions.h
//
//===================================================================
// February 2010 Creation: NDO
//===================================================================
#ifndef CATPolyStreamOptions_H
#define CATPolyStreamOptions_H

class CATMathStream;


/**
Options and manipulators that control and modify how the data are streamed or unstreamed.
*/
class CATPolyStreamOptions
{

public:

  CATPolyStreamOptions () {}
  ~CATPolyStreamOptions () {}

  /**
   * Filtering of the layers and support during the stream or unstream.
   *
   * The data from the various layers are streamed if the corresponding flags are set.
   * By default, all flags are set and all layers are streamed.
   */
  enum LayerFilter
  {
    /** */                                                        eNoLayer = 0x000,
    /** */                                                        eVertexPositionLayer = 0x001,
    /** */                                                        eVertexNormalLayer = 0x002,
    /** */                                                        eVertexUVLayer = 0x004,
    /** */                                                        eVertexCellLayer = 0x008,
    /** */                                                        eVertexTangentLayer = 0x010,
    /** */                                                        eVertexWLayer = 0x020,
    /** */                                                        eVertexTextureCoordLayer = 0x040,
    /** */                                                        eSupport = 0x080,
    /** */                                                        eBlackBoxLayer = 0x100,
    /** */                                                        eSurfaceFlagLayer = 0x200,
    /** Reserved for streaming a bad body. */                     eEnableStreamOfBadBody = 0x20000000,
    /** Reserved for persistence of the vertex indices. */        eVertexIndices = 0x40000000,
    /** Reserved for persistence of the facet indices. */         eFacetIndices = 0x80000000,
    /** All layers excluding vertex and facet index layers. */    eAllLayers = 0x0FFFFFFF,
    /** Default option (all layers). */                           eDefault = eAllLayers | eEnableStreamOfBadBody
  };

  /**
   * Returns the default layer option (all layers) excluding a set of given layers.
   */
  inline static unsigned int DefaultExcluding (unsigned int excludedLayers);

public:

  /**
   * @nodoc
   */
  enum StreamingMode
  {
    //eNativeMode                           = 0x00,  // Streaming of entities in the framework where the entities are implemented.
    ePolyhedralObjectsMode                = 0x01   // Streaming of entities as polyhedral objects.
  };

  // Used to aggregate compression methods to a field of type CATPolyStreamOptions::Compression
  enum CompressionMethods
  {
    eDeflate = 0x01, // Compression algorithm used by Zip. Turn on only if target container isn't zipped.
    eEdgeBreaker = 0x02, // Optimized (lossless) compression algorithm for 3D meshes. EdgeBreaker is not applied if not relevant.

    // Pre-aggregated sets of options to choose from
    eCompressionFor3DXML = eEdgeBreaker, // DEFLATE (zip) disabled (applied within 3dxml)
    eFullCompression = eDeflate | eEdgeBreaker // Everything that EdgeBreaker cannot compress will be handled by DEFLATE.
  };

  typedef unsigned int Compression;

  // Old compression flags that didn't do anything and were never supposed to be used
  // by anybody in the first place.
  // PLEASE DO NOT USE!
  enum CompressionDeprecated
  {
    eNoCompression = 0x0,
    eLowCompression = 0x0,
    eMediumCompression = 0x0,
    eHighCompression = 0x0
  };

};

inline unsigned int CATPolyStreamOptions::DefaultExcluding (unsigned int excludedLayers)
{
  return eDefault & ~excludedLayers;
}


#endif
