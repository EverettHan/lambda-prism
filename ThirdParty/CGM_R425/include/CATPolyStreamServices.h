// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyStreamServices.h
//
//===================================================================
// May 2013  Creation: NDO
//===================================================================
#ifndef CATPolyStreamServices_H
#define CATPolyStreamServices_H

#include "PolyStream.h"
#include "CATPolyStreamOptions.h"
#include "CATPolyDeprecated.h"
#include "CATErrorDef.h"
#include "CATMathStreamVersionDef.h"
#include "Poly/MathStream.h"


/** @file 
 * Services to stream or unstream specific implementations of CATIPolySurface or CATIPolyMesh:
 * <ul> 
 *   <li> CATPolyMeshImpl
 *   <li> CATPolyCompactMesh
 *   <li> CATPolyEditableMesh
 * </ul>
 *
 * @see CATPolyBodyServices.h
*/

class CATPolyBody;
class CATIPolyObject;
class CATMathStream;
class CATMathTransformation;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;
class CATPolyUnstreamRecord;
class CATPolyMeshImpl;
class CATPolyCompactMesh;
class CATPolyEditableMesh;
class CATPolyDeltaMeshConst;
class CATPolySubMesh;
class CATPolyProxyMesh;
class CATUnicodeString;


namespace Poly
{

  /** @name Streaming of CATPolyBody.
   *
   * CATPolyStreamServices.h
   * @{ */

  /**
   * Returns the current stream version.
   */
  ExportedByPolyStream CATCGMStreamVersion GetCurrentStreamVersion ();

  /**
    * Returns the CGM stream version.
    * @param iStream
    *   The input CATMathStream.
    */
  ExportedByPolyStream CATCGMStreamVersion GetCGMStreamVersion (const CATMathStream& iStream);

  /**
    * Returns true if the CATMathStream supports the input version.
    * @param iStream
    *   The input CATMathStream.
    * @param iVersion
    *   The input version.
    */
  ExportedByPolyStream bool IsVersionSupported (const CATMathStream& iStream, CATCGMStreamVersion iVersion);

  inline bool IsVersionGreaterOrEqual (CATCGMStreamVersion iLHS, CATCGMStreamVersion iRHS);

  /**
   * Checks is a CATPolyBody is streamable to a CATMathStream in a native mode.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param iStream
   *   A CATMathStream.
   * @return
   *   Returns true when the CATPolyBody is streamable in a native polyhedral mode.
   */
  ExportedByPolyStream bool IsStreamable (const CATPolyBody& iPolyBody, const CATMathStream& iStream);

  /**
   * Streams a CATPolyBody to a file.
   * @param iFileName
   *   The file name where the data are streamed.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param iPosMatrix
   *   An optional transformation defining the position of the CATPolyBody.
   * @param iNativePolyhedralObjects
   *   Defines how the polyhedral data will be streamed.
   *   By default, the types of the objects are preserved by the streaming operation. 
   *   There is no change of object types.  An implementation of a streamer must be available for
   *   non-native polyhedral objects. For example, to stream an instance of an adapter on tessellated data, 
   *   an implementation of a streamer for this adapter is needed.  The streamer should be available in 
   *   the framework (component) where the data structures are implemented.
   *   If the flag is set to true, then the data are streamed as native polyhedral objects with the
   *   default streamers.
   * @param iOptions
   *   The filtering options for the various layers.  By default all layers are streamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @param ioStreamRecord
   *   An optional argument recording the geometrical entities (<code>CATIPolyPoint</code>'s,
   *   <code>CATIPolyCurve</code>'s and <code>CATIPolySurface</code>'s)
   *   that are sent to the stream.  Geometrical entities from the CATPolyBody that are already recorded
   *   will not be streamed.
   * @ param iCompressionFlags
   *   Compression options (optional). See CATPolyStreamOptions for more information about compression.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Stream (const CATUnicodeString& iFileName,
    const CATPolyBody& iPolyBody, const CATMathTransformation* iPosMatrix = 0,
    CATPolyStreamRecord* ioStreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0,
    CATPolyStreamOptions::Compression iCompressionFlags = 0);

  /**
   * Streams a CATPolyBody to a CATMathStream.
   * @param str
   *   A CATMathStream (CATCGMStream)
   */
  ExportedByPolyStream HRESULT Stream (CATMathStream& str,
    const CATPolyBody& iPolyBody, const CATMathTransformation* iPosMatrix = 0,
    CATPolyStreamRecord* ioStreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0,
    CATPolyStreamOptions::Compression iCompressionFlags = 0);

  /**
   * Streams a CATPolyBody to a buffer.
   * @param oBuffer
   *   The buffer containing the CATPolyBody data.  This buffer is allocated by a call to this method.
   *   It must be deleted by the caller.
   * @param oNbBytes
   *   The number of bytes in the buffer.
   */
  ExportedByPolyStream HRESULT Stream (char*& oBuffer, size_t& oNbBytes,
    const CATPolyBody& iPolyBody, const CATMathTransformation* iPosMatrix = 0,
    CATPolyStreamRecord* ioStreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0);

  /**
   * Unstreams a CATPolyBody from a file.
   * @param iFileName
   *   The file name where the data are found.
   * @param oPolyBody
   *   The instance of the CATPolyBody constructed during unstreaming.
   *   This instance must be released.
   * @param oPosMatrix
   *   An optional transformation defining the position of the CATPolyBody.
   *   The instance must be deleted (if different from null.)
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all layers are unstreamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @param ioUnstreamRecord
   *   An optional argument recording the geometrical entities (CATIPolyPoint's, CATIPolyCurve's and CATIPolySurface's)
   *   that are obtained from the stream.  If geometrical entities of the CATPolyBody are already recorded onto this
   *   instance, then they will not be unstreamed.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Unstream (const CATUnicodeString& iFileName,
    CATPolyBody*& oPolyBody, CATMathTransformation*& oPosMatrix,
    CATPolyUnstreamRecord* ioUnstreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0);

  /**
   * Unstreams a CATPolyBody from a CATMathStream.
   * @param str
   *   A CATMathStream (typically a CATCGMStream.)
   */
  ExportedByPolyStream HRESULT Unstream (CATMathStream& str,
    CATPolyBody*& oPolyBody, CATMathTransformation*& oPosMatrix,
    CATPolyUnstreamRecord* ioUnstreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0);

  /**
   * Unstreams a CATPolyBody from a buffer.
   * @param iBuffer
   *   The buffer containing the CATPolyBody data.
   */
  ExportedByPolyStream HRESULT Unstream (const char* iBuffer, const size_t iNbBytes,
    CATPolyBody*& oPolyBody, CATMathTransformation*& oPosMatrix,
    CATPolyUnstreamRecord* ioUnstreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0);

  /**
   * Unstreams a CATPolyBody.
   */
  ExportedByPolyStream HRESULT Unstream (const CATUnicodeString& iFileName,
    CATPolyBody*& oPolyBody,
    CATPolyUnstreamRecord* ioUnstreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0);

  /**
   * Unstreams a CATPolyBody.
   */
  ExportedByPolyStream HRESULT Unstream (CATMathStream& str,
    CATPolyBody*& oPolyBody,
    CATPolyUnstreamRecord* ioUnstreamRecords = 0,
    const CATPolyStreamerRegistry* iRegistry = 0);

   /** @} */
}


namespace Poly
{
  /** @name Streaming polyhedral surfaces: CATIPolySurface.
   *
   * CATPolyStreamServices.h
   * @{ */

  /**
   * Streams a CATPolyMeshImpl.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The input mesh.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all layers are streamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Stream (CATMathStream& str, const CATPolyMeshImpl& iMesh, 
                                       const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
   * Streams a CATPolyCompactMesh.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The input mesh.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all layers are streamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Stream (CATMathStream& str, const CATPolyCompactMesh& iMesh,
                                       const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
   * Streams a CATPolyEditableMesh.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The input mesh.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all layers are streamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Stream (CATMathStream& str, const CATPolyEditableMesh& iMesh,
                                       const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
   * Streams a CATPolyDeltaMeshConst.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The input mesh.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all layers are streamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Stream (CATMathStream& str, const CATPolyDeltaMeshConst& iMesh,
                                       const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
 * Streams a CATPolySubMesh.
 * @param str
 *   The input CATMathStream.
 * @param iMesh
 *   The input mesh.
 * @param iLayerFilter
 *   The filtering options for the various layers.  By default all layers are streamed.
 *   See CATPolyStreamOptions::LayerFilter.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if the mesh has been successfully streamed.
 *   <li> <code> S_FALSE </code> if the mesh cannot be streamed.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
  ExportedByPolyStream HRESULT Stream(CATMathStream &str, const CATPolySubMesh &iMesh,
    const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
 * Streams a CATPolyProxyMesh.
 * @param str
 *   The input CATMathStream.
 * @param iMesh
 *   The input mesh.
 * @param iLayerFilter
 *   The filtering options for the various layers.  By default all layers are streamed.
 *   See CATPolyStreamOptions::LayerFilter.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if the mesh has been successfully streamed.
 *   <li> <code> S_FALSE </code> if the mesh cannot be streamed.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
  ExportedByPolyStream HRESULT Stream(CATMathStream &str, const CATPolyProxyMesh &iMesh,
    const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
   * Unstreams a CATPolyMeshImpl.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The output mesh.  It must be released upon a successfull call.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all available layers are unstreamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Unstream (CATMathStream& str, CATPolyMeshImpl*& iMesh, 
                                         const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
   * Unstreams a CATPolyCompactMesh.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The output mesh.  It must be released upon a successfull call.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all available layers are unstreamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Unstream (CATMathStream& str, CATPolyCompactMesh*& iMesh, 
                                         const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /**
   * Unstreams a CATPolyEditableMesh.
   * @param str
   *   The input CATMathStream.
   * @param iMesh
   *   The output mesh.  It must be released upon a successfull call.
   * @param iLayerFilter
   *   The filtering options for the various layers.  By default all available layers are unstreamed.
   *   See CATPolyStreamOptions::LayerFilter.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the mesh has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the mesh cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  ExportedByPolyStream HRESULT Unstream (CATMathStream& str, CATPolyEditableMesh*& iMesh, 
                                         const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

 /**
  * Unstreams a CATPolyDeltaMeshConst.
  * @param str
  *   The input CATMathStream.
  * @param iMesh
  *   The output mesh.  It must be released upon a successfull call.
  * @param iLayerFilter
  *   The filtering options for the various layers.  By default all available layers are unstreamed.
  *   See CATPolyStreamOptions::LayerFilter.
  * @return
  * <ul>
  *   <li> <code> S_OK </code> if the mesh has been successfully unstreamed.
  *   <li> <code> S_FALSE </code> if the mesh cannot be unstreamed.
  *   <li> <code> E_FAIL </code> or any other error if an error occurs.
  * </ul>
  */
  ExportedByPolyStream HRESULT Unstream (CATMathStream& str, CATPolyDeltaMeshConst*& iMesh,
                                         const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

 /**
 * Unstreams a CATPolySubMesh.
 * @param str
 *   The input CATMathStream.
 * @param iMesh
 *   The output mesh.  It must be released upon a successfull call.
 * @param iLayerFilter
 *   The filtering options for the various layers.  By default all available layers are unstreamed.
 *   See CATPolyStreamOptions::LayerFilter.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if the mesh has been successfully unstreamed.
 *   <li> <code> S_FALSE </code> if the mesh cannot be unstreamed.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
  ExportedByPolyStream HRESULT Unstream(CATMathStream &str, CATPolySubMesh *&iMesh,
    const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

/**
 * Unstreams a CATPolyProxyMesh.
 * @param str
 *   The input CATMathStream.
 * @param iMesh
 *   The output mesh.  It must be released upon a successfull call.
 * @param iLayerFilter
 *   The filtering options for the various layers.  By default all available layers are unstreamed.
 *   See CATPolyStreamOptions::LayerFilter.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if the mesh has been successfully unstreamed.
 *   <li> <code> S_FALSE </code> if the mesh cannot be unstreamed.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
  ExportedByPolyStream HRESULT Unstream(CATMathStream &str, CATPolyProxyMesh *&iMesh,
    const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);

  /** @} */
}


inline bool Poly::IsVersionGreaterOrEqual (CATCGMStreamVersion iLHS, CATCGMStreamVersion iRHS)
{
  return iLHS >= iRHS;
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * @nodoc
 */
POLY_DEPRECATED ("See Poly::Stream ()",
ExportedByPolyStream HRESULT CATPolyStreamSurface (CATMathStream& str, const CATPolyMeshImpl& iMesh,
                                                  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);)

  /**
   * @nodoc
   */
POLY_DEPRECATED ("See Poly::Stream ()",
ExportedByPolyStream HRESULT CATPolyStreamSurface (CATMathStream& str, const CATPolyCompactMesh& iMesh,
                                                  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);)

/**
 * @nodoc
 */
POLY_DEPRECATED ("See Poly::Unstream ()",
ExportedByPolyStream HRESULT CATPolyUnstreamSurface (CATMathStream& str, CATPolyMeshImpl*& iMesh,
                                                    const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);)

/**
 * @nodoc
 */
POLY_DEPRECATED ("See Poly::Unstream ()",
ExportedByPolyStream HRESULT CATPolyUnstreamSurface (CATMathStream& str, CATPolyCompactMesh*& iMesh,
                                                     const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers);)

#endif

#endif
