// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyAttributes.h
//
//===================================================================
// October 2009  Creation: NDO
// June    2014  JXO: Geometric diagnosis
//===================================================================
#ifndef CATIPolyBodyAttributes_H
#define CATIPolyBodyAttributes_H

#include "PolyhedralAttributes.h"
#include "IUnknown.h"
#include "CATBoolean.h"

class CATIPolyPrimitiveSupport;
class CATIPolyBodyStreamer;
class CATPolyBodyDiagnosis;
class CATPolyBodyGeoDiagnosis;
class CATMathStream; 
class CATTolerance;
class CATPolyBodyBaseAttributes;
class CATPolyBodyNativeAttributes;


/**
* Interface providing access to various attributes about the CATPolyBody.
* This interface also determines how a CATPolyBody should be streamed.
*/
class ExportedByPolyhedralAttributes CATIPolyBodyAttributes
{

public:

  virtual ~CATIPolyBodyAttributes () {}

public:

/** @name Queries
    @{ */

  /**
   * Query about the ID.
   * Fetches the ID or CGM ID associated to the CATPolyBody if available.
   * @param oID
   *   The ID of the CATPolyBody.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if an ID is available.
   *   <li> <tt>S_FALSE</tt> if no ID is available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT GetID (unsigned int& oID) const = 0;

  /**
   * Query about the sag.
   * Fetches the sag associated to the CATPolyBody if available.
   * (This is a target sag not necessarily the sag met by the CATPolyBody.)
   * @param oSag
   *   The sag of the CATPolyBody.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a sag is available.
   *   <li> <tt>S_FALSE</tt> if no sag is available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT GetSag (double& oSag) const = 0;

  /**
   * Query about the CATTolerance.
   * Fetches the CATTolerance associated to the CATPolyBody if available.
   * The instance returned cannot be delete by the caller.
   * @param oTolerance
   *   The CATTolerance associated to the CATPolyBody.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a CATTolerance is available.
   *   <li> <tt>S_FALSE</tt> if no CATTolerance is available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT GetTolerance (const CATTolerance*& oTolerance) const = 0;

  /**
   * Query about the support.
   * Returns the underlying primitive support associated to a CATPolyBody, if any.
   * @param oSupport
   *   The support.  The returned support must be released (ref-counted.)
   * <ul>
   *   <li> <tt>S_OK</tt> if a support is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a support is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT GetSupport (CATIPolyPrimitiveSupport*& oSupport) const = 0;

  /**
   * Query about the diagnosis.
   * Returns the diagnosis computed on the CATPolyBody.
   * The object returned is owned by the CATPolyBody and should not be deleted.
   * @param oDiagnosis
   *   The diagnostics.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the diagnostics are available.
   *   <li> <tt>S_FALSE</tt> if the diagnostics are not available.
   *   <li> <tt>E_FAIL</tt> or any other error if an error occurs.
   * </ul>   
   */
  virtual HRESULT GetDiagnosis (CATPolyBodyDiagnosis*& oDiagnosis) = 0;

  /**
   * Query about the geometric diagnosis.
   * Returns the diagnosis computed on the CATPolyBody.
   * The object returned is owned by the CATPolyBody and should not be deleted.
   * @param oDiagnosis
   *   The geometric diagnostics.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the diagnostics are available.
   *   <li> <tt>S_FALSE</tt> if the diagnostics are not available.
   *   <li> <tt>E_FAIL</tt> or any other error if an error occurs.
   * </ul>   
   */
  virtual HRESULT GetGeoDiagnosis (CATPolyBodyGeoDiagnosis*& oDiagnosis) = 0;

/** @} */

public:

/** @name Domains
    @{ */

  /**
   * Query about topological domains. 
   *
   * There is no notion of domains in the CATPolyBody.  The information returned about domains is
   * just a stored or implicit attribute.
   *
   * A domain is composed of connected cells of the same dimension: d.  It is defined by 
   * its closed boundary representation.  A domain can have several boundaries.
   * Each boundary of a domain must be closed (Sum of boundaries of each boundary equals to 0; 
   * or equivalently, each boundary of domain has no boundary.)
   * 
   * Domain of Dimension 3
   * A domain of dimension 3 defines a solid (contiguous volume, a lump).  
   * Each of its boundaries is defined by connected CATPolyFace's.
   *
   * Domain of Dimension 2
   * A domain of dimension 2 defines a skin (contiguous surface, a shell).  
   * Each of its boundaries is defined by connected CATPolyEdge's.
   *
   * Domain of Dimension 1
   * A domain of dimension 1 defines a wire (contiguous curve).
   * Each of its boundaries is defined by CATPolyVertex's.
   * 
   * Domain of Dimension 0
   * A domain of dimension 0 defines a point.
   * It has no boundary.
   * 
   * @param iDimension
   *   The dimension of the domain to query.
   * @return
   *   <ul>
   *     <li> +1 if the body contains domains of that dimension;
   *     <li>  0 if the body does not contain domains of that dimension;
   *     <li> -1 if it's unknown.
   *   </ul>
   */

  virtual int DoesBodyContainDomainsOfDimension (unsigned int iDimension) const = 0;

/** @} */

public:

/** @name Properties 
    @{ */

  /**
   * Returns the status about the validity of the CATPolyBody. 
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> if the CATPolyBody is valid;
   *     <li> <tt>S_FALSE</tt> if the CATPolyBody is invalid;
   *     <li> <tt>E_FAIL</tt> if a serious error is detected (corrupted CATPolyBody) and the tests
   *          could not be completed.
   *   </ul>
   * See CATPolyBodyDiagnosis if the CATPolyBody is invalid.
   */
  virtual HRESULT IsValid () const = 0;

  /**
   * Reports if a CATPolyBody is watertight or not topologically.
   * A CATPolyBody that is topologically watertight is geometrically watertight.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> if the CATPolyBody is topologically watertight;
   *     <li> <tt>S_FALSE</tt> if the CATPolyBody is not topologically watertight;
   *     <li> <tt>E_FAIL</tt> if a serious error is detected (corrupted CATPolyBody).
   *   </ul>
   */
  virtual HRESULT IsTopologicallyWatertight () const = 0;

  /**
   * Reports if a CATPolyBody is watertight or not geometrically.
   * A CATPolyBody that is geometrically watertight is not necessarily topologically watertight.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> if the CATPolyBody is geometrically watertight;
   *     <li> <tt>S_FALSE</tt> if the CATPolyBody is not geometrically watertight;
   *     <li> <tt>E_FAIL</tt> if a serious error is detected (corrupted CATPolyBody).
   *   </ul>
   */
  virtual HRESULT IsGeometricallyWatertight () const = 0;

  /**
   * Checks that all <code>CATPolyFace</code>s of this <code>CATPolyBody</code> are bounded by 
   * <tt>CATPolyEdge</tt>-s
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if all CATPolyFace-s of the CATPolyBody are bounded by CATPolyEdge-s.
   *     All boundaries of the CATPolyFace should consist of loops of connected CATPolyEdge-s. 
   *   <li> <tt>S_FALSE</tt> if one of more CATPolyFace is not completely bounded by CATPolyEdge-s.
   *   <li> <tt>E_FAIL</tt> if there is some kind of error with the CATPolyEdge's bounding the CATPolyFace-s.
   *     Check CATPolyBodyDiagnosis when an error occurs.
   * </ul>   
   */
  virtual HRESULT HasFaceEdges () const = 0;

/** @} */

public:

/** @name Streaming
    @{ */

  /**
   * Returns an instance of an interface for streaming this CATPolyBody.
   * @param oStreamer
   *   The returned streamer for this CATPolyBody.  This object must be deleted.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if a streamer is returned.
   *   <li> <code> S_FALSE </code> if no streamer is available.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>   
   */
  virtual HRESULT GetStreamer (CATIPolyBodyStreamer*& oStreamer) const = 0;

  /**
   * Checks if this <code> CATPolyBody </code> is streamable.
   * This is a quick way of finding out if a CATPolyBody is streamable or not.
   * @param iStream
   *   The math stream on which the object is supposed to be streamed.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if streamable
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  virtual CATBoolean IsStreamable (const CATMathStream& iStream) const = 0;

/** @} */

public:

/** @name Others
    @{ */

  /**
   * Returns the size in bytes of the CATIPolyBodyAttributes instance.
   */
  virtual unsigned int SizeOf () const = 0;

/** @} */

public:

/** @name Modification of attributes
    @{ */

  /**
   * Sets an underlying support to a CATPolyBody.  This method is called to associate a 
   * primitive to the CATPolyBody (see CATIPolyPrimitiveSupport.)
   * @param iSupport
   *   A pointer to the body support.  The method calls AddRef on the support.
   *   Any previous support owned by the object will be released.
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if a support is successfully set.
   *   <li> <tt>S_FALSE</tt> if a support cannot be set.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT SetSupport (CATIPolyPrimitiveSupport* iSupport) = 0;

/** @} */

public:

  /**
   * @nodoc
   * Reserved.
   * Returns 0 if the two class ID are the same.
   */
  static int CompareClassID (const CLSID& id1, const CLSID& id2);

  /**
   * @nodoc
   * Reserved.
   */
  virtual const CLSID& GetClassID () const = 0;

protected:

  CATIPolyBodyAttributes () {}

public:

  virtual CATPolyBodyBaseAttributes* CastAsBaseAttributes () {return 0;}
  virtual const CATPolyBodyBaseAttributes* CastAsBaseAttributes () const { return 0; }

  virtual CATPolyBodyNativeAttributes* CastAsNativeAttributes () { return 0; }
  virtual const CATPolyBodyNativeAttributes* CastAsNativeAttributes () const { return 0; }

};

#endif // !CATIPolyBodyAttributes_H
