#ifndef CATCGMCoordSystemBodyAttr_h_
#define CATCGMCoordSystemBodyAttr_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMStreamAttribute.h"

class CATBody;
class CATCGMStream;
class CATCell;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATLine;
class CATPlane;
class CATPoint;
class CATTopData;
class CATVertex;
class CATMathAxis;

/**
 * Class representaing the attribute of a coordinate system body.
 * <br>Use it to ask a body if it is a coordinate system, and to retrieve the associated
 * features. 
 * <br>Sample:
 * <pre>
 * CATCGMCoordSystemBodyAttrImpl * RetrievedAttr= 
 *	 (CATCGMCoordSystemBodyAttrImpl*) aBody->GetAttribute(&UAIDName(CATCGMCoordSystemBodyAttrImpl));
 * //
 * // retrieves geometric definition.
 *   CATLine * Line1, *Line2, *Line3;
 *	 RetrievedAttr->GetLines(Line1,Line2,Line3);
 *
 * //
 * // retrieves topological definition (quarter infinite faces)
 *	 CATFace * f1, *f2, *f3;	
 *	 RetrievedAttr->GetFaces(f1,f2,f3);  
 * //
 * // creates topological (infinite) bodies 
 *	 CATBody  *Body3;	
 *	 RetrievedAttr->GetPlanes(NULL,NULL,&Body3);  
 * </pre>
 */
class ExportedByCATGMOperatorsInterfaces CATCGMCoordSystemBodyAttr: public CATCGMStreamAttribute
{
public:
  // Mandatory macro for inheriting from CATCGMStreamAttribute  
  CATCGMDeclareAttribute (CATCGMCoordSystemBodyAttr,CATCGMStreamAttribute);

  /**
   * Constructor
   */
  CATCGMCoordSystemBodyAttr();

  /**
   * Destructor
   */
  virtual ~CATCGMCoordSystemBodyAttr();

  /**
	*  Retrieves the mathematical definition of the coordinate system body.
	* @param ioAxis
	* The corresponding mathematical definition.
	*/
  virtual void GetMathAxis(CATMathAxis &ioAxis) const = 0;

  /**
	 * Retrieves the geometric definition of the planes of the coordinate system body.
	 *<br> The pointers always points to the same geometric objects. 
	 * @param oPlaneXY
	 * The geometric plane defined by the first and second directions.
	 * @param oPlaneYZ
	 * The geometric plane defined by the second and third directions.
	 * @param oPlaneZX
	 * The geometric plane defined by the third and first directions.
	 */
  virtual void GetPlanes(CATPlane *&oPlaneXY, CATPlane *&oPlaneYZ, CATPlane *&oPlaneZX) = 0;

  /**
	 * Retrieves the geometric definition of the lines of the coordinate system body.
	 *<br> The pointers always points to the same geometric objects. 
	 * @param oLineOY
	 * The geometric line defined by the first direction.
	 * @param oLineOY
	 * The geometric line defined by the second direction.
	 * @param oLineOZ
	 * The geometric line defined by the third direction.
	 */
  virtual void GetLines(CATLine *&oLineOX, CATLine *&oLineOY, CATLine *&oLineOZ) = 0;

  /**
	 * Retrieves the geometric definition of the origin of the coordinate system body.
	 *<br> The pointer always points to the same geometric object. 
	 * @param oOrigin
	 * The geometric point defining the origin.
	 */
  virtual void GetOrigin(CATPoint *&oOrigin) = 0;

  //Get Topological definition
  /**
	 * Retrieves the topological definition of the origin of the coordinate system body.
	 *<br> The pointer always points to the same vertex. 
	 * @param oOrigin
	 * The vertex defining the origin.
	 */
  virtual void GetVertex(CATVertex *&oOrigin) = 0;

  /**
	 * Retrieves the topological definition of the axes of the coordinate system body.
	 *<br> The pointers always points to the same topological edges. 
	 * @param oLineOY
	 * The edge defining the first direction.
	 * @param oLineOY
	 * The edge defining the second direction.
	 * @param oLineOZ
	 * The edge defining the third direction.
	 */
  virtual void GetEdges(CATEdge *&oLineOX, CATEdge *&oLineOY, CATEdge *&oLineOZ) = 0;

  /**
	 * Retrieves the quarter infinite topological faces from the coordinate system body.
	 * @param oPlaneXY
	 * The quarter infinite face defined by the first and second directions.
	 * @param oPlaneYZ
	 * The quarter infinite face defined by the second and third directions.
	 * @param oPlaneZX
	 * The quarter infinite face definied by the third and first directions.
	 */
  virtual void GetFaces(CATFace *&oPlaneXY, CATFace *&oPlaneYZ, CATFace *&oPlaneZX) = 0;

  /**
	 * Creates topological planes from the planes of the coordinate system body.
	 *<br> Each created body contains an infinite face (this face is not a face of the initial coordinate
	 * system body, because the faces of a  coordinate
	 * system body are only quarter-infinite). 
	 * At each call, new bodies are created. 
     * @param iFactory
     * The factory where the body is created.
     * @param iData
     * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iData</tt> 
     * is never filled.
	 * @param oPlaneXY
	 * The created body containing an infinite face defined by the first and second directions. 
	 * If <tt>NULL</tt>, do nothing.
	 * @param oPlaneYZ
	 * The created body containing an infinite face defined by the second and third directions.
	 * If <tt>NULL</tt>, do nothing.
	 * @param oPlaneZX
	 * The created body containing an infinite face definied by the third and first directions.
	 * If <tt>NULL</tt>, do nothing.
	 */
  virtual void CreatePlanes(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody **oPlaneXY,
    CATBody **oPlaneYZ,
    CATBody **oPlaneZX) = 0;

  /**
     * Deprecated. Use the signature with CATTopData.
	 */
  virtual void CreatePlanes(CATBody **oPlaneXY, CATBody **oPlaneYZ, CATBody **oPlaneZX) = 0;

  /**
	 * Creates topological lines from the axes of the coordinate system body.
	 *<br> Each created body contains an infinite edge (this edge is not an edge of the initial coordinate
	 * system body, because the edges of a  coordinate
	 * system body are only semi-infinite).
	 * At each call, new bodies are created.  
     * @param iFactory
     * The factory where the body is created.
     * @param iData
     * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iData</tt> 
     * is never filled.
	 * @param oLineOX
	 * The created body containing an infinite edge defined by the first direction.
	 * If <tt>NULL</tt>, do nothing.
	 * @param oLineOY
	 * The created body containing an infinite edge defined by the second direction.
	 * If <tt>NULL</tt>, do nothing.
	 * @param oLineOZ
	 * The created body containing an infinite edge definied by the third direction.
	 * If <tt>NULL</tt>, do nothing.
	 */
  virtual void CreateLines(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody **oLineOX,
    CATBody **oLineOY,
    CATBody **oLineOZ) = 0;

  /**
     * Deprecated. Use the signature with CATTopData.
	 */
  virtual void CreateLines(CATBody **oLineOX, CATBody **oLineOY, CATBody **oLineOZ) = 0;

  /**
	 * Create the topological point from the origin of the coordinate system body.
	 *<br>The created body contains a vertex (this vertex is not the original vertex of the initial coordinate
	 * system body).
	 * At each call, a new body is created.  
     * @param iFactory
     * The factory where the body is created.
     * @param iData
     * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iData</tt> 
     * is never filled.
	 * @param oOrigin
	 * The created body . If <tt>NULL</tt>, do nothing.
	 */
  virtual void CreateOrigin(CATGeoFactory *iFactory, CATTopData *iData, CATBody **oOrigin) = 0;

  /**
     * Deprecated. Use the signature with CATTopData.
	 */
  virtual void CreateOrigin(CATBody **oOrigin) = 0;

  /**
	 * Streams <tt>this</tt> coordinate system attribute.
	 * <br>Internal use.
	 */
  virtual void Stream(CATCGMStream &iStr) const = 0;

  /**
	 * Unstreams <tt>this</tt> coordinate system attribute.
	 * <br>Internal use.
	 */
  virtual void UnStream(CATCGMStream &iStr) = 0;

  /**
	 * IsStreamable.
	 * <br>Internal use.
	 */
  virtual CATBoolean IsStreamable(
    const CATCGMStreamVersion iTargetVersion,
    CATBoolean &ioReversible) const = 0;

};

// ------------------------------------------------------------------------------------------
// PrivExtractCellFromAxisSystemBody(...)
// ------------------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void ExtractCellFromAxisSystemBody(CATBody *iBody, CATCell **oCell);

ExportedByCATGMOperatorsInterfaces void GetInfiniteBodyFromAxisSystemElement(
  CATCell *iCell,
  CATGeoFactory *iFactory,
  CATBody **oInfiniteBody);

// ------------------------------------------------------------------------------------------
// PrivGetInfiniteBodyFromAxisSystemElement(...)
// ------------------------------------------------------------------------------------------
// Returns an infinite Body from a Cell or a Body that is CHECKED TRUE BY PrivIsElementFromAxisSystem(...).
// If the input is an Axis System Face (or a Axis System Face inside the Body) :
//    - The returned Body is an Infinite Face.
// If the input is an Axis System Edge (or a Axis System Edge inside the Body) :
//    - The returned Body is an Infinite Edge.
// ------------------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void GetInfiniteBodyFromAxisSystemElement(
  CATBody *iBody,
  CATGeoFactory *iFactory,
  CATBody **oInfiniteBody);

ExportedByCATGMOperatorsInterfaces CATBoolean IsElementFromAxisSystem(
  CATCell *iCell,
  CATVertex **oOriginVertex = NULL);

// ------------------------------------------------------------------------------------------
// PrivIsElementFromAxisSystem(...)
// ------------------------------------------------------------------------------------------
// Check wether a Body or a Cell is an Axis System or a part of an Axis System.
// In order to return TRUE the input Body :
//    - either is an Axis System
//    - or contains ONE CELL that is a part of an Axis System (an Axis Edge or Axis Face).
// ------------------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean IsElementFromAxisSystem(CATBody *iBody);

#endif /* CATCGMCoordSystemBodyAttr_h_ */
