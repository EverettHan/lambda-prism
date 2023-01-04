#ifndef CATWire_H
#define CATWire_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATEdgeDomain.h"

//-----------------------------------------------------------------------------
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATWire ;
#else
extern "C" const IID IID_CATWire ;
#endif

class CATEdge;
class CATVertex;
class CATSurface;
class CATMathVector;

/**
 * Interface representing a set connected edges
 * of a body or a volume.
 *<br> A CATWire is created with the @href CATBody#CreateWire or @href CATBody#CreateDomain
 * methods and deleted with the 
 * @href CATICGMContainer#Remove method.
 */
class ExportedByCATGMModelInterfaces CATWire : public CATEdgeDomain
{
  CATDeclareInterface;
public :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/** 
 * Returns the rank of a vertex in <tt>this</tt> CATWire.
 * @param iVertex
 * The pointer to the vertex.
 * @return
 * The corresponding rank.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0,..,N</tt></dt><dd>If <tt>this</tt> contains N edges.
 *<dt><tt>0</tt></dt><dd>If <tt>this</tt> is closed and <tt>iVertex</tt> is at the closure.
 *<dt><tt>-1</tt></dt><dd>If <tt>iVertex</tt> does not belong to <tt>this</tt> wire.
 * </dl>
 */
    virtual int        GetVertexRank(CATVertex* iVertex) = 0;

/** 
 * Retrieves a vertex of <tt>this</tt> CATWire.
 * @param iRank
 * The rank of the vertex to retrieve.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0,..,N</tt></dt><dd>If <tt>this</tt> contains N edges.
 *<dt><tt>0</tt></dt></dt><dd>If <tt>this</tt> is closed and the vertex is at the closure.
 * </dl>
 * @return
 * The pointer to the corresponding vertex.
 */
    virtual CATVertex* GetVertex(int iRank) = 0;

/** 
 * Retrieves the extremities of <tt>this</tt> CATWire.
 * @param oStartVertex
 * The pointer to the first vertex of <tt>this</tt>. If <tt>NULL</tt> in input, this is not output.
 * If <tt>this</tt> is closed, a pointer to <tt>NULL</tt> is returned, and the tangents are not computed.
 * @param oEndVertex
 * The pointer to the last vertex of <tt>this</tt>. If <tt>NULL</tt> in input, this is not output.
 * If <tt>this</tt> is closed, a pointer to <tt>NULL</tt> is returned, and the tangent are not computed.
 * @param oStartTangent
 * The pointer to the tangent at the first extremity, oriented as the wire.
 * If <tt>NULL</tt> in input, this is not output.
 * @param oEndTangent
 * The pointer to the tangent at the last extremity, oriented as the wire.
 * If <tt>NULL</tt> in input, this is not output.
 */
    virtual void GetExtremities(CATVertex    **oStartVertex,
                                CATVertex    **oEndVertex,
                                CATMathVector *oStartTangent =NULL,
                                CATMathVector *oEndTangent   =NULL) = 0;

/** 
 * Checks whether the first vertex and the last vertex of <tt>this</tt> CATWire are the same.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the first and last vertex are the same, <tt>FALSE</tt> otherwise.
 */
    virtual CATBoolean IsClosed() = 0;    

/** 
 * Changes the first vertex of <tt>this</tt> CATWire, if it is closed.
 * @param iNewClosureVertex
 * The pointer to the new closure vertex. 
 */
    virtual void       ChangeClosureVertex(CATVertex* iNewClosureVertex) = 0;



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/** 
 * @nodoc
 * Checks whether the edges of <tt>this</tt> CATWire are intersecting themselves.
 * @param iSurface
 * The pointer to the surface on which the wire is lying on (if it is).
 * @param iBody
 * The pointer to the Body the Wire belongs to.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> is self-intersecting, <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean CheckWireSelfIntersection(CATSurface * iSurface = NULL,
    CATBody *iBody= NULL ) = 0;
};

CATDeclareHandler(CATWire,CATEdgeDomain);

#endif // CATWire_H
