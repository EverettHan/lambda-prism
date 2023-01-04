#ifndef CATHybDef_h
#define CATHybDef_h

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/
#include<stdlib.h>
#include<string.h>

// Geometry
class CATGeoFactory;
class CATGeometry;
class CATPoint;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATSimCurve;
class CATMacroPoint;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPointOnSurface;
class CATCartesianPoint;
class CATSurface;
class CATSurLimits;
class CATSurParam;
class CATCrvLimits;
class CATCrvParam;
class CATMathPoint;
class CATMathBox;
class CATMathDirection;
class CATProjectionPtCrv;
class CATProjectionPtSur;
class CATProjectionCrvSur;
class CATIntersectionCrvCrv;
class CATIntersectionCrvSur;

// Topology
class CATBody;
class CATCell;
class CATVertex;
class CATEdge;
class CATFace;
class CATDomain;
class CATVertexInVolume;
class CATWire;
class CATShell;

// Hybrid Operator
class CATHybOperator;
class CATHybOperatorImp;
class CATHybAssemble;
class CATHybBoundary;
class CATHybConfusion;
class CATHybDisconnect;
class CATHybIntersect;
class CATHybPoseSur;
class CATHybProject;
class CATHybRegularize;
class CATHybSplit;
class CATHybTrim;

// Hybrid Operator Implementation
class CATExtHybOperator;
class CATExtHybOperatorImp;
class CATExtHybAssemble;
class CATExtHybBoundary;
class CATExtHybConfusion;
class CATExtHybDisconnect;
class CATExtHybIntersect;
class CATExtHybPoseSur;
class CATExtHybProject;
class CATExtHybRegularize;
class CATExtHybSplit;
class CATExtHybTrim;

class CATTopologicalOperator;
class CATHybDebug;
class CATCGMActivateDebug;


class CATHybOperatorCx2;
class CATHybBoundaryCx2;
class CATHybInvertCx2;
class CATHybSegmentWire;
class CATHybWireExtrapolationCx2;
class CATHybDocker;

// Topological report
class CATCGMJournal;
class CATCGMJournalList;
class CATCGMJournalInfo;

// Versionning
class CATTopData;
class CATSoftwareConfiguration;
class CATSoftwareModification;

// Divers
class CATCellHashTable;

#define DOWNCAST(type,baseobject,object)\
  if( baseobject->IsAKindOf( type ::ClassName()) )\
    object=( type *)baseobject;\
  else\
    object=NULL;

/**
* Defines the domains to be kept after a cutting operation.
* <b>Right and Left definitions</b>:
* <ul>
* <li>The right of a shell cut by another shell is the part 
* of the cut shell which is pointed out by the orientation of the cutting shell.
* The left side is the other one. 
* <li>The right of a shell cut by a wire is the part
* of the cut shell such that the orientation of the shell, 
* the orientation of the wire and the direction on the selected part is direct. 
* <li>The right of a wire cut by a shell, a wire or a vertex is the part
* of the wire that is pointed out by the orientation of the wire.
* </ul>
* @param BOTH_SIDES
* Keeps all the domains
* @param POSITIVE_POSITIVE_SIDE
* Keeps the domains that are to the right of the cut body and the cutting body. 
* @param NEGATIVE_POSITIVE_SIDE
* Keeps the domains that are to the left of the cut body and to the right 
* of the cutting body. 
* @param POSITIVE_NEGATIVE_SIDE
* Keeps the domains that are to the right of the cut body and to the left 
* of the cutting body. 
* @param NEGATIVE_NEGATIVE_SIDE
* Keeps the domains that are to the left of the cut body and to the left 
* of the cutting body. 
* @param POSITIVE_POSITIVE_SIDE_NO_CONFUSION
* Keeps the domains that are to the right of the cut body and the cutting body. 
* Does not keep the portions of the domains which are shared between the input bodies. 
* @param NEGATIVE_POSITIVE_SIDE_NO_CONFUSION
* Keeps the domains that are to the left of the cut body and to the right 
* of the cutting body. 
* Does not keep the portions of the domains which are shared between the input bodies. 
* @param POSITIVE_NEGATIVE_SIDE_NO_CONFUSION
* Keeps the domains that are to the right of the cut body and to the left 
* of the cutting body. 
* Does not keep the portions of the domains which are shared between the input bodies. 
* @param NEGATIVE_NEGATIVE_SIDE_NO_CONFUSION
* Keeps the domains that are to the left of the cut body and to the left 
* of the cutting body. 
* Does not keep the portions of the domains which are shared between the input bodies. 
*/
enum CATHybSelectionMode { BOTH_SIDES,
                           POSITIVE_POSITIVE_SIDE,
                           NEGATIVE_POSITIVE_SIDE,
                           POSITIVE_NEGATIVE_SIDE,
                           NEGATIVE_NEGATIVE_SIDE,
                           POSITIVE_POSITIVE_SIDE_NO_CONFUSION,
                           NEGATIVE_POSITIVE_SIDE_NO_CONFUSION,
                           POSITIVE_NEGATIVE_SIDE_NO_CONFUSION,
                           NEGATIVE_NEGATIVE_SIDE_NO_CONFUSION };

/**
* Defines the mode of extrapolation during a cutting operation.
*<br>This is useful when the cutting body does not cut right along the body to cut, or
* vice versa in case of a trim operation.
* @param NO_EXTRAPOLATION
* No extrapolation is performed. In this case, the operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* @param TANGENT_DIRECTION
* If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
*/
enum CATHybExtrapolationMode{ NO_EXTRAPOLATION, TANGENT_DIRECTION };

/**
* Defines the type of result of a fillet operation.
* @param NO_TRIMMING
* The resulting body is the topological fillet.
* @param TRIMMING
* The resulting body is the union between the topological fillet and the trimmed input
* domains.
*/
enum CATHybSegmentationMode{ NO_TRIMMING, TRIMMING };

/**
* Internal Use
*/
enum CATHybSimplifyMode{ TOPOLOGY_SHARING, POINT_SHARING, HOLE_SHARING };


// PropagateMode for Boundary
/** 
* Defines the propagation of a piece of the boundary of a shell domain.
* @param NO_CONTINUITY
* No restriction is made on the definition of the boundary. In particular, this boundary
* can be made of several domains (case of inner loops of a shell).
* @param POINT_CONTINUITY
* The boundary stops at the last cell of the bounding domain.
* @param TANGENT_CONTINUITY
* The boundary stops at the first vertex where the boundary is not continous in tangent.
*/
enum CATHybPropagateMode{ NO_CONTINUITY, POINT_CONTINUITY, TANGENT_CONTINUITY };

// Project Context
/** 
* Internal Use
*/ 
enum CATHybProjectionContext{ UNKNOWNCONTEXT , PROJECTION, POSAGE };

// Fillet Relimitation On RazorBlade Edge : Options
/**
* Defines how to relimit a topological fillet.
* The option is common to each end.
* Let <tt>StartOnSurface1</tt> and <tt>EndOnSurface1</tt> be the beginning and end points
* of the fillet trace on the first surface side, and <tt>StartOnSurface2</tt> and <tt>EndOnSurface2</tt>
* be beginning and end
* points of the fillet trace on the second surface side. Suppose <tt>StartOnSurface &lt; EndOnSurface</tt>.
* @param PLINE
* The boundaries are two lines <tt>(StartOnSurface1,StartOnSurface2)</tt> and
* <tt>(EndOnSurface1,EndOnSurface2)</tt> in the fillet surface space
* @param SPLINE
* The boundaries are two splines <tt>(StartOnSurface1,StartOnSurface2)</tt> and
* <tt>(EndOnSurface1,EndOnSurface2)</tt>  in the fillet surface space.
* Each PSpline is tangent to the limiting curves
* of the input bodies.
* @param MINIMUM
* The limiting boundaries are two isopar curves passing through
* <tt>max(StartOnSurface1,StartOnSurface2)</tt> for one end and
* <tt>min(EndOnSurface1,EndOnSurface2)</tt> for the other end.
* @param MAXIMUM
* The limiting boundaries are two isopar curves passing through
* <tt>min(StartOnSurface1,StartOnSurface2)</tt> for one end and
* <tt>max(EndOnSurface1,EndOnSurface2)</tt> for the other end.  
*/
enum CATHybRelimitationMode{ PLINE, SPLINE, MINIMUM, MAXIMUM};

// Wire Extrapolation options
enum CATHybExtrapolSelectionMode{ EXTRAPOL_WIRE_START, EXTRAPOL_WIRE_END, EXTRAPOL_WIRE_BOTH_SIDES };
enum CATHybExtrapolReplaceMode  { REPLACE_WIRE_START, REPLACE_WIRE_END, REPLACE_WIRE_BOTH_SIDES, REPLACE_NONE };

/**
* Defines the differents results of a confusion diagnostic.
* @param NO_CONFUSION
* There is no confusion at all between the bodies.
* @param FULL_CONFUSION
* There is a full confusion between the bodies.
* @param CONTACT
* There is an intersection between the bodies but not a full confusion.
*/
enum CATHybConfusionDiagnostic{ NO_CONFUSION=0, FULL_CONFUSION=1, CONTACT=2, UNKNOWN_CONFUSION=9999 };


// Assembly
class CATHybOperatorCx2;
class CATHybAssembly;
class CATHybSkin;
class CATHybWire;
class CATHybCell;
class CATHybVertex;
class CATHybEdge;
class CATHybFace;

// Neighbour
class CATHybNeighbour;
class CATHybSingleNeighb;
class CATHybMultiNeighb;
class CATHybNeighbEdge;
class CATHybNeighbFace;
class CATHybPosition;
class CATHybPosition;
class CATHybPart;
class CATHybBox;
class CATHybCloudBox;

// listes
class CATPointss;
class CATHybCells;
class CATHybCellss;
typedef CATHybCells CATHybFaces;
typedef CATHybCells CATHybEdges;
typedef CATHybCells CATHybVertexs;
typedef CATHybCellss CATHybFacess;
typedef CATHybCellss CATHybEdgess;

class CATPointsIter;
class CATHybCellsIter;
class CATHybVertexsIter;
class CATHybEdgesIter;
class CATHybFacesIter;

class CATHybCellssIter;
typedef CATHybCellssIter CATHybFacessIter;
typedef CATHybCellssIter CATHybEdgessIter;

// Misc
/** 
*
*/
enum CATHybEdgeStatus{ CATHybUnknownEdge,
CATHybMergedEdge,
CATHybBorderEdge,
CATHybDegeneratedEdge,
CATHybDegeneratedEdgeButKeep,
CATHybInactiveEdgeByLocalJoin
};

#endif
