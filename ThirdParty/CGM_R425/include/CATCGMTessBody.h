#ifndef CATCGMTessBody_h_
#define CATCGMTessBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/** @_C_A_A_2_Required */ // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate) - NHD
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/

#include "CATGMModelInterfaces.h"
#include "CATMathLimits.h"
#include "CATMathDef.h"
#include "CATErrorDef.h"
#include "CATCGMTessBodyList.h"

#include "CATCGMRefCounted.h"
#include "CATIAV5Level.h"
#include "CATTopDefine.h"

class CATBody;
class CATCell;
class CATVertex;
class CATEdge;
class CATFace;

class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATIPolySurfaceVertex;
class CATIPolySurfaceVertexLine;

class CATMapOfEdgeToPolySurfaceVertexLine;
class CATMapOfVertexToPolySurfaceVertex;
class CATMapOfVertexToPolyCurveVertex;

class CATCGMTessID;
class CATCGMTessParam;
class CATCGMTessellateParam;
class CATCGMTessellateID;
class CATSoftwareConfiguration;
class CATTessellateBodyStatic;

class CATMathPolyBuffers;

/**
* Interface returning CATIPolySurface, CATIPolyCurve and CATIPolyPoint instances encapsulating the tessellated data 
* computed from a CATBody. 
*
* Repetitive calls to the methods of this class may create new polyhedral entities representing the same tessellation of
* the CATBody.
*
* All instances returned by the methods are ref-counted and must be released by the caller.
*/
class ExportedByCATGMModelInterfaces CATCGMTessBody : public CATCGMRefCounted
{

public:

  /**
   * Constructor
   */
  CATCGMTessBody();

protected:

  /**
   * Destructor
   */
  virtual ~CATCGMTessBody();

public:

  /**
   * Returns a reference to the CATBody that is tessellated.
   * @return
   *   The CATBody that is tessellated.
   */
  virtual const CATBody &GetBody() const = 0;

  /**
   * Returns a reference to the CATBody that is tessellated.
   * @return
   *   The CATBody that is tessellated.
   */
  virtual CATBody& GetBody () = 0;

  /**
   * Returns the target sag of the tessellation data.  This is the sag that was defined in the input parameters.
   * @return 
   *   The sag of the tessellation data.
   */
  virtual double GetSag () const = 0;

  /**
   * Returns the tessellation ID associated to a CATCell.
   * @param iCell
   *   The input CATCell.
   * @param oTessID
   *   The output CATCGMTessellateID, to be deleted by the caller.
   * @return
   *   <ul>
   *     <li> S_OK if the CATCGMTessellateID has been set.
   *     <li> E_FAIL or any other error when a failure occurs and the CATCGMTessellateID has not been set.
   *   </ul>
   */
  virtual HRESULT GetTessellateID (CATCell &iCell, CATCGMTessellateID* &oTessID) = 0;

  /**
   * Returns the tessellation ID associated to a CATCell.
   * @param iCell
   *   The input CATCell.
   * @param oTessID
   *   The output CATCGMTessID.
   * @return
   *   <ul>
   *     <li> S_OK if the CATCGMTessID has been set.
   *     <li> E_FAIL or any other error when a failure occurs and the CATCGMTessID has not been set.
   *   </ul>
   */
  virtual HRESULT GetTessID (CATCell &iCell, CATCGMTessID &oTessID) = 0;

public:

  /**
   * Given a CATFace returns its tessellation as a CATIPolySurface.
   *
   * @param iFace
   *   The input CATFace whose tessellation is requested.
   * @param oPolySurface
   *   The output instance providing access to the tessellation of the CATFace.
   *   The returned instance must be released by the caller.
   * @param oOriPolySurfaceVsFace (optional)
   *   Orientation of the output polysurface with respect to the CATFace.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolySurface is returned successfully for this CATFace.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolySurface (CATFace &iFace, CATIPolySurface *&oPolySurface, CATOrientation * oOriPolySurfaceVsFace=0) = 0;

#if defined (CATIAV5R24) || defined (CATIAR215)
  /**
   * Given a CATFace returns its tessellation as a CATIPolySurface.
   *
   * @param iFace
   *   The input CATFace whose tessellation is requested.
   * @param oPolySurface
   *   The output instance providing access to the tessellation of the CATFace.
   *   The returned instance must be released by the caller.
   * @param ioEdgeMapToPolyCurve
   *   An instance mapping the edges adjacent to the CATFace to their tessellation in the form of 
   *   a CATIPolySurfaceVertexLine (same orientation as corresponding PolyCurve returned by GetPolyCurve).
   *   This argument may be null.
   * @param ioVertexMapToPolyPoint
   *   An instance mapping the vertices adjacent to the CATFace to their tessellation in the form of 
   *   a CATIPolySurfaceVertex.
   *   This argument may be null.
   * @param oOriPolySurfaceVsFace (optional)
   *   Orientation of the output polysurface with respect to the CATFace.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolySurface is returned successfully for this CATFace.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolySurface (CATFace &iFace, CATIPolySurface *&oPolySurface,
                                  CATMapOfEdgeToPolySurfaceVertexLine* ioEdgeMapToPolyCurve,
                                  CATMapOfVertexToPolySurfaceVertex* ioVertexMapToPolyPoint, 
																	CATOrientation * oOriPolySurfaceVsFace=0) = 0;

	/**
   * Given a CATFace returns its local tessellation (CATBody context independent) as a CATIPolySurface.
   *
   * @param iFace
   *   The input CATFace whose tessellation is requested.
   * @param oPolySurface
   *   The output instance providing access to the tessellation of the CATFace.
   *   The returned instance must be released by the caller.
   * @param ioEdgeMapToPolyCurve
   *   An instance mapping the edges adjacent to the CATFace to their tessellation in the form of 
   *   a CATIPolySurfaceVertexLine (same orientation as corresponding PolyCurve returned by GetPolyCurve).
   *   This argument may be null.
   * @param ioVertexMapToPolyPoint
   *   An instance mapping the vertices adjacent to the CATFace to their tessellation in the form of 
   *   a CATIPolySurfaceVertex.
   *   This argument may be null.
   * @param oOriPolySurfaceVsFace (optional)
   *   Orientation of the output polysurface with respect to the CATFace.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolySurface is returned successfully for this CATFace.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolySurfaceLocal (CATFace &iFace, CATIPolySurface *&oPolySurface,
                                  CATMapOfEdgeToPolySurfaceVertexLine* ioEdgeMapToPolyCurve,
                                  CATMapOfVertexToPolySurfaceVertex* ioVertexMapToPolyPoint, 
																	CATOrientation * oOriPolySurfaceVsFace=0);

	/**
   * Given a CATFace and its CATIPolySurface previously computed returns the list of IsoVertexLines.
   *
   * @param iFace
   *   The input CATFace whose tessellation is requested.
   * @param iPolySurface
   *   The input instance providing access to the tessellation of the CATFace.
   * @param ioIsoVertexLinesList
   *   The list of CATIPolySurfaceVertexLine, to be deleted by the caller.
   * @return
	 *   Number of CATIPolySurfaceVertexLine
   */
  virtual CATULONG32 GetPolySurfaceIsoVertexLines(CATFace &iFace, CATIPolySurface &iPolySurface, CATIPolySurfaceVertexLine** &ioIsoVertexLinesList);
#endif

  /**
   * Given a CATEdge returns its tessellation as a CATIPolyCurve.
   *
   * The CATIPolyCurve instance returned is just a discrete curve in space with no reference to the underlying surface
   * even when the CATEdge is adjacent to a CATFace.  This CATIPolyCurve is *not* a CATIPolySurfaceVertexLine. 
   * See GetPolySurface to obtain the tessellation of an edge with references to the underlying geometry.
   *
   * @param iEdge
   *   The input CATEdge whose tessellation is requested.
   * @param oPolyCurve
   *   The output instance providing access to the tessellation of this CATEdge.
   *   The returned instance must be released by the caller.
   * @param oOriPolyCurveVsEdge (optional)
   *   Orientation of the output polycurve with respect to the CATEdge.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolyCurve is returned successfully for this CATEdge.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolyCurve (CATEdge &iEdge, CATIPolyCurve *&oPolyCurve, CATOrientation * oOriPolyCurveVsEdge=0) = 0;

#if defined (CATIAV5R24) || defined (CATIAR215)
  /**
   * Given a CATEdge returns its tessellation as a CATIPolyCurve.
   *
   * The CATIPolyCurve instance returned is just a discrete curve in space with no reference to the underlying surface
   * even when the CATEdge is adjacent to a CATFace.  This CATIPolyCurve is *not* a CATIPolySurfaceVertexLine. 
   * See GetPolySurface to obtain the tessellation of an edge with references to the underlying geometry.
   *
   * @param iEdge
   *   The input CATEdge whose tessellation is requested.
   * @param oPolyCurve
   *   The output instance providing access to the tessellation of this CATEdge.
   *   The returned instance must be released by the caller.
   * @param ioVertexMapToPolyPoint
   *   An instance mapping the vertices adjacent to the CATEdge to their tessellation in the form of 
   *   a CATIPolyCurveVertex.  Note that there are two and only two CATVertex adjacent to a CATEdge.
   *   This argument may be null.
   * @param oOriPolyCurveVsEdge (optional)
   *   Orientation of the output polycurve with respect to the CATEdge.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolyCurve is returned successfully for this CATEdge.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolyCurve (CATEdge &iEdge, CATIPolyCurve *&oPolyCurve,
                                CATMapOfVertexToPolyCurveVertex* ioVertexMapToPolyPoint, 
																CATOrientation * oOriPolyCurveVsEdge=0) = 0;

	/**
   * Given a CATEdge returns its local tessellation (CATBody context independent) as a CATIPolyCurve.
   *
   * The CATIPolyCurve instance returned is just a discrete curve in space with no reference to the underlying surface
   * even when the CATEdge is adjacent to a CATFace.  This CATIPolyCurve is *not* a CATIPolySurfaceVertexLine. 
   * See GetPolySurface to obtain the tessellation of an edge with references to the underlying geometry.
   *
   * @param iEdge
   *   The input CATEdge whose tessellation is requested.
   * @param oPolyCurve
   *   The output instance providing access to the tessellation of this CATEdge.
   *   The returned instance must be released by the caller.
   * @param ioVertexMapToPolyPoint
   *   An instance mapping the vertices adjacent to the CATEdge to their tessellation in the form of 
   *   a CATIPolyCurveVertex.  Note that there are two and only two CATVertex adjacent to a CATEdge.
   *   This argument may be null.
   * @param oOriPolyCurveVsEdge (optional)
   *   Orientation of the output polycurve with respect to the CATEdge.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolyCurve is returned successfully for this CATEdge.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolyCurveLocal (CATEdge &iEdge, CATIPolyCurve *&oPolyCurve,
                                CATMapOfVertexToPolyCurveVertex* ioVertexMapToPolyPoint, 
																CATOrientation * oOriPolyCurveVsEdge=0);
#endif

  /**
   * Given a CATVertex returns its tessellation as a CATIPolyPoint.
   *
   * The CATIPolyPoint instance returned is just a discrete point in space with no reference to the underlying curve or surface
   * even when the CATVertex is adjacent to a CATEdge and a CATFace.  This CATIPolyPoint is *not* a CATIPolyCurveVertex or CATIPolySurfaceVertex. 
   * See GetPolyCurve and GetPolySurface to obtain the tessellation of a vertex with references to the underlying geometry.
   *
   * @param iVertex
   *   The input CATVertex whose tessellation is requested.
   * @param oPolyPoint
   *   The output instance providing access to the tessellation of this CATVertex.
   *   The returned instance must be released by the caller.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolyPoint is returned successfully for this CATVertex.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolyPoint (CATVertex &iVertex, CATIPolyPoint *&oPolyPoint) = 0;

#if defined (CATIAV5R24) || defined (CATIAR215)
	/**
   * Given a CATFace returns its tessellation as a CATMathPolyBuffers.
   * 
   * @param iFace
   *   The input CATFace whose tessellation is requested.
   * @param oFacePolyBuffers [out, IUnknown#Release] 
   *   The output instance providing access to the tessellation of the CATFace.
   *   The returned instance must be released by the caller.
   * @param oOriPolyBuffersVsFace
   *   The orientation of triangles buffer regarding to the CATFace.
   * @return
   *   <ul>
   *     <li> S_OK if a CATIPolySurface is returned successfully for this CATFace.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetPolyBuffers(CATFace& iFace, const CATMathPolyBuffers* &oFacePolyBuffers, 
												 CATOrientation& oOriPolyBuffersVsFace,
												 int iLocalTessellation=0); // 1: local tessellation independent of CATBody context

  /**
   * Given a CATEdge returns its tessellation as a CATMathPolyBuffers.
   * 
   * @param iEdge
   *   The input CATEdge whose tessellation is requested.
   * @param oEdgePolyBuffers [out, IUnknown#Release] 
   *   The output instance providing access to the tessellation of the CATEdge.
   *   The returned instance must be released by the caller.
   * @param oOriBuffersVsEdge
   *   The orientation of position buffer regarding to the CATEdge.
   * @return
   *   <ul>
   *     <li> S_OK if a CATMathPolyBuffers is returned successfully for this CATFace.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
	virtual HRESULT GetEdgePolyBuffers(CATEdge &iEdge, const CATMathPolyBuffers* &oEdgePolyBuffers,
			  										 CATOrientation& oOriBuffersVsEdge,
														 int iLocalTessellation=0); // 1: local tessellation independent of CATBody context

  /**
   * Given a CATVertex returns its tessellation as coordinates.
	 *
   * @param iVertex
   *   The input CATVertex whose tessellation is requested.
   * @param oCoordinates [out, IUnknown#Release] 
   *   The output coordinates of the CATVertex, must be deleted by the caller.
   * @return
   *   <ul>
   *     <li> S_OK if coordinates are returned successfully for this CATVertex.
   *     <li> E_FAIL or any other error when a failure occurs.
   *   </ul>
   */
  virtual HRESULT GetVertexCoordinates(CATVertex &iVertex, double* &oCoordinates);
  virtual HRESULT GetVertexCoordinates(CATVertex &iVertex, float* &oCoordinates);

  /**
   * Returns the tessellation ID associated to a CATCell.
   * @param iCell
   *   The input CATCell.
   * @param oTessID
   *   The output CATCGMTessellateID is refcounted and will be released by this.
   * @return
   *   <ul>
   *     <li> S_OK if the CATCGMTessellateID has been set.
   *     <li> E_FAIL or any other error when a failure occurs and the CATCGMTessellateID has not been set.
   *   </ul>
   */
  virtual HRESULT GetRefCountedTessellateID (CATCell &iCell, CATCGMTessellateID* &oTessID);

  /**
   * Empty cache associated to a CATCell if any.
   * @param iCell
   *   The input CATCell.
   * @param iRemoveNonPersistantDeltaCache (optional)
   *    DeltaCache associated to faces is not removed even if it's not persistent.
   */
  virtual void EmptyCellCache (CATCell &iCell, CATBoolean iRemoveNonPersistantDeltaCache=FALSE);

  /**
  * Empty cache associated to the body if any.
  * @param iRemoveNonPersistantDeltaCache (optional)
  *    DeltaCache associated to faces is not removed even if it's not persistent.
  */
  virtual void EmptyBodyCache (CATBoolean iRemoveNonPersistantDeltaCache=FALSE);

  /**
  * Returns the CATTessellateBodyStatic if any
  */
  virtual CATTessellateBodyStatic * SafeCastToCATTessellateBodyStatic() = 0;

#endif

public:

  /**
   * @nodoc
   * @deprecated
   */
  virtual HRESULT GetPolySurfaceVertexLine(
    CATFace &iFace,
    CATEdge &iEdge,
    CATIPolySurface &iPolySurface,
    CATIPolySurfaceVertexLine *&oPolySurfaceVertexLine) = 0;

  /**
   * @nodoc
   * @deprecated
   */
  virtual HRESULT GetPolySurfaceVertex(
    CATFace &iFace,
    CATVertex &iVertex,
    CATIPolySurface &iPolySurface,
    CATIPolySurfaceVertex *&oPolySurfaceVertex) = 0;

};

/**
 * Creates an instance of CATCGMTessBody from a CATBody and the new tessellation parameters: please refer now to GMModelInterfaces\ProtectedInterfaces\CATCGMCreateTessBody.h
 */

/** @file 
 */
/**
 * @nodoc
 * Creates an instance of CATCGMTessBody from a CATBody and the new tessellation parameters.
 * Max Deviation (Sag) and Max Step should be greater than the container resolution value. 
 *
 * In the returned instance, the computation of the discrete data is done by global tessellation.
 *
 * @param iBody
 *   The input CATBody to tessellate.
 * @param iTessellateParam
 *   The tessellation parameters.
 * @param iSoftwareConfig
 *   The input Software Configuration.
 * @param iMode
 *   0: tessellation will be done immediately for the entire body.
 *   1: tessellation will be done cell by cell on demand (while calling get methods).
 * @return
 *   An instance of a CATCGMTessBody. Null if creation issue.
 */
//ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, const CATCGMTessellateParam &iTessellateParam, CATSoftwareConfiguration* iSoftwareConfig, int iMode=0);


/**
 * @nodoc
 * Creates an instance of CATCGMTessBody from a CATBody and the tessellation parameters.
 *
 * In the returned instance, the computation of the discrete data is done by global tessellation.
 *
 * @param iBody
 *   The input CATBody to tessellate.
 * @param iSag
 *   The sag to be met by the tessellated body.
 * @param iStep
 *   An optional step size parameter not to be exceeded.  
 * @param iMaxAngle
 *   An optional angle parameter not to be exceeded.
 * @return
 *   An instance of a CATCGMTessBody.
 */
ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateTessBody(
  CATBody &iBody,
  double iSag,
  double iStep = CATMathInfinite,
  double iMaxAngle = 0.25* CATPI);

/**
 * @nodoc
 * Creates an instance of CATCGMTessBody from a CATBody and the tessellation parameters.
 *
 * In the returned instance, the computation of the discrete data is done by global tessellation.
 *
 * @param iBody
 *   The input CATBody to tessellate.
 * @param iTessParam
 *   The tessellation parameters.
 * @return
 *   An instance of a CATCGMTessBody.
 */
ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, const CATCGMTessParam &iTessParam);

/**
 * @nodoc
 * Creates an instance of CATCGMTessBody from a CATBody and a previous CATCGMTessBody instance.
 * 
 * The tessellation parameters (sag,...) are obtained from the input CATCGMTessBody.  In the returned instance,
 * the computation of the discrete data is done by incremental tessellation.
 *
 * @param iBody
 *   The input CATBody to tessellate.
 * @param iTessBody
 *   An input CATCGMTessBody that refers to the tessellation of a body sharing cells with the input CATBody.
 * @return
 *   An instance of a CATCGMTessBody.
 */
ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, CATCGMTessBody &iTessBody);

/**
 * @nodoc
 * Creates an instance of CATCGMTessBody from a CATBody and a previous list of CATCGMTessBody instances.
 * 
 * The tessellation parameters (sag,...) are obtained from the input CATCGMTessBody instances.  In the returned instance,
 * the computation of the discrete data is done by incremental tessellation.
 *
 * @param iBody
 *   The input CATBody to tessellate.
 * @param iTessBodyList
 *   An input list of CATCGMTessBody instances that refer to the tessellation of bodies sharing cells with 
 *   the input CATBody.
 * @return
 *   An instance of a CATCGMTessBody.
 */
ExportedByCATGMModelInterfaces CATCGMTessBody *CATCGMCreateTessBody(
  CATBody &iBody,
  const CATCGMTessBodyList &iTessBodyList);


/** @example ExampleRenderVertex1.cpp
 * Here is an example of how to render a vertex given its serialized tessellation data from a CATCGMTessBody.
 */

/** @example ExampleRenderEdge1F.cpp
 * Here is an example of how to render an edge given its serialized tessellation data from a CATCGMTessBody (float data).
 */

/** @example ExampleRenderEdge1D.cpp
 * Here is an example of how to render an edge given its serialized tessellation data from a CATCGMTessBody (double data).
 */

/** @example ExampleRenderFace1F.cpp
 * Here is an example of how to render a face given its serialized tessellation data from a CATCGMTessBody (float data).
 */

/** @example ExampleRenderFace1D.cpp
 * Here is an example of how to render a face given its serialized tessellation data from a CATCGMTessBody (double data).
 */

/** @example ExampleRenderFace2.cpp
 * Here is an example of how to render a face from the tessellation data in a CATCGMTessBody.
 */

/** @example ExampleRenderBody1F.cpp
 * Here is an example of how to serialize the whole tessellation of a CATBody into float and triangle buffers.
 */

/** @example ExampleRenderBody1D.cpp
 * Here is an example of how to serialize the whole tessellation of a CATBody into double and triangle buffers.
 */

/** @example ExampleGlobalTessellation.cpp
 * Here is an example of how to create a CATCGMTessBody using global tessellation.
 */

/** @example ExampleIncrementalTessellation.cpp
 * Here is an example of how to create a CATCGMTessBody using incremental tessellation.
 */

#endif /* CATCGMTessBody_h_ */
