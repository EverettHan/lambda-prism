// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCreatePolyBodyStreamer.h
//
//===================================================================
// June 2010  Creation: NDO
//===================================================================
#ifndef CATCreatePolyBodyStreamer_H
#define CATCreatePolyBodyStreamer_H

#include "PolyStream.h"
#include "CATErrorDef.h"  // HRESULT
#include "CATMathStreamDef.h"

class CATIPolyBodyAnyStreamer;
class CATIPolyBodyAnyUnstreamer;
class CATIPolyBodyStreamer;
class CATIPolyBodyUnstreamer;
class CATUnicodeString;
class CATMathStream;


/** @file 
 * Global functions that create instances of CATIPolyBodyStreamer and CATIPolyBodyUnstreamer.
 */


/**
 * Creates an instance of CATIPolyBodyAnyStreamer.
 *
 * @param oStreamer
 *   The returned instance of CATIPolyBodyAnyStreamer.  The returned instance must be deleted.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if a valid instance is returned.
 *   <li> <code> S_FALSE </code> if a valid instance cannot be returned.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
extern "C" ExportedByPolyStream HRESULT CATCreatePolyBodyAnyStreamer (CATIPolyBodyAnyStreamer*& oStreamer); 


/**
 * Creates an instance of CATIPolyBodyAnyUnstreamer.
 *
 * @param oUnstreamer
 *   The returned instance of CATIPolyBodyAnyUnstreamer.  The returned instance must be deleted.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if a valid instance is returned.
 *   <li> <code> S_FALSE </code> if a valid instance cannot be returned.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
extern "C" ExportedByPolyStream HRESULT CATCreatePolyBodyAnyUnstreamer (CATIPolyBodyAnyUnstreamer*& oUnstreamer);


/**
 * Creates an instance of CATIPolyBodyStreamer.
 *
 * @param iStreamerVersion
 *   The version of the streamer to construct.
 * @param oStreamer
 *   The returned instance of CATIPolyBodyStreamer.  The returned instance must be deleted.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if a valid instance is returned.
 *   <li> <code> S_FALSE </code> if a valid instance cannot be returned.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
extern "C" ExportedByPolyStream HRESULT CATCreatePolyBodyStreamer (CATIPolyBodyStreamer*& oStreamer);

#ifndef _STATIC_SOURCE

/**
 * Creates an instance of CATIPolyBodyUnstreamer.
 *
 * @param iStreamerVersion
 *   The version of the unstreamer to construct.
 * @param oUnstreamer
 *   The returned instance of CATIPolyBodyUnstreamer.  The returned instance must be deleted.
 * @return
 * <ul>
 *   <li> <code> S_OK </code> if a valid instance is returned.
 *   <li> <code> S_FALSE </code> if a valid instance cannot be returned.
 *   <li> <code> E_FAIL </code> or any other error if an error occurs.
 * </ul>
 */
extern "C" ExportedByPolyStream HRESULT CATCreatePolyBodyUnstreamer (CATIPolyBodyUnstreamer*& oUnstreamer);

#endif


/**
 * Reserved.
 * Creates an instance of a CATMathStream (or CATCGMStream).
 * @param iFileName
 *   The input file name to open (create, write or read).
 * @param iAccessMode
 *   The acces mode:
 *   <ul>
 *     <li> CatCGMStreamWriteOnly: to open an output stream.
 *     <li> CatCGMStreamReadOnly: to open an input stream.
 *   </ul>
 * @return
 *   A CATMathStream.
 */
extern "C" ExportedByPolyStream CATMathStream* CATPolyCreateStream (const CATUnicodeString& iFileName, const CATCGMStreamType iAccessMode);

#endif // !CATCreatePolyBodyStreamer_H
