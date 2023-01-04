#ifndef CATPGMTopologicalUtilities_h_
#define CATPGMTopologicalUtilities_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATIsoParameter.h"
#include "CATTopDefine.h"
#include "CATMathDef.h"
#include "CATTopDef.h"
#include "CATErrorDef.h" // HRESULT

class CATTopology;
class CATBody;
class CATCGMJournalList;
class CATCrvParam;
class CATCurve;
class CATDomain;
class CATEdge;
class CATEdgeCurve;
class CATFace;
class CATGeoFactory;
class CATLoop;
class CATMathVector;
class CATPCurve;
class CATPoint;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPointOnSurface;
class CATRibTopOp;
class CATShell;
class CATSoftwareConfiguration;
class CATSurParam;
class CATTopData;
class CATTopologicalOperator;  // Not interfaced here for the moment
class CATVertex;
class CATWire;
class CATCell;
class CATMathDirection;
class CATMathPoint;
class CATMathAdvancedBox;
class CATCrvLimits;
class CATSurface;
class CATSurLimits;
class CATGeometry;
class CATLISTP(CATVertex);
class CATLISTP(CATDomain);
class CATLISTP(CATCell);
class CATLISTP(CATGeometry);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

//----------------------------------------------------------------------------
// Creation d'un Body mono-wire-mono-edge
// a partir d'une edge, et eventuellement du body s'il existe deja
//----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateBodyMonoWireMonoEdge(
  CATEdge *iEdge,
  CATGeoFactory *iGeoFactory,
  CATBody *iBody = NULL,
  const CATBoolean iDuplicate = FALSE);

//----------------------------------------------------------------------------
// Creation d'un Body mono-shell
// a partir d'un shell, et eventuellement du body s'il existe deja
//----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateBodyMonoShell(
  CATShell *iShell,
  CATGeoFactory *iGeoFactory,
  CATBody *iBody = NULL);

//----------------------------------------------------------------------------
// Creation d'un Body mono-shell-mono-face
// a partir d'une face, et eventuellement du body s'il existe deja
//----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateBodyMonoShellMonoFace(
  CATFace *iFace,
  CATGeoFactory *iGeoFactory,
  CATBody *iBody = NULL,
  const CATBoolean iDuplicate = FALSE);

//------------------------------------------------------------------------------
// Get the uv bounding box of an edge on a face
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void CATPGMGet2DBoundingBox(
  CATSoftwareConfiguration *iConfig,
  CATEdge *iEdge,
  CATFace *iFace,
  CATSurLimits &o2DBoundingBoxForEdge,
  CATVertex *iStart = NULL,
  CATVertex *iEnd = NULL);

//------------------------------------------------------------------------------
// Get the CrvLimits of an Edge
// If iCurve, oLimits is related to this Curve, otherwise, it is related to the underlying EdgeCurve. 
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void CATPGMGetLimits(CATEdge *iEdge, CATCrvLimits &oLimits, CATCurve *iCurve = NULL);

//-----------------------------------------------------------------------------
// Compare the orientation of a shell or a face with a given direction
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATTopSign CATPGMGetRelativeOrient(
  CATFace *iFace,
  CATMathDirection &iDirection,
  CATOrientation iOrientation = CATOrientationPositive,
  CATShell *iShell = NULL,
  CATBody *iBody = NULL,
  CATVertex *iVertexOnFace = NULL,
  CATEdge *iEdgeOnFace = NULL,
  double iTol = 0.);

/**
* EvalTopoAreaOrientation() function
* The main purpose of this function consists in guessing the global orientation of a topological object in regards with a given direction.
* This function will compute signed areas from the boundary of the object and won't depend on any local evaluation of normal, 
* avoiding this way many unstabilities due to the randomly choice of one reference point from the topological object.
* The caller is supposed to use this service for open surfacic bodies, faces or closed wire bodies (according to the 'turns left' convention), 
* defining a closed area from their boundaries unfold in a mathematical plane (whose the normal is the input direction)
* In case of conflict between positive and negative areas, the biggest one will give its sign to the returned orientation.
* In case of perfect balance between negative and positive areas, or if no area can be computed (vertical face asking its orientation in Z direction),
* the output orientation will be CATOrientationUnknown !
* This service is available for both exact and polyhedral objects.
* @param iConfig
* The pointer to the software configuration driving the versionning of code modifications
* @param iTopObject
* The topological object defining a closed oriented area : 
* open CATShell, open CATFace, CATLoop (if not full), closed CATWire, or CATBody containing open Shells or closed Wires
* all other types of topological objects (like points or volumes) will be refused (returning E_FAIL)
* @param iRefDirection
* The reference direction used to compute the signed area onto a plane (whose the normal is this direction)
* @param oTopoAreaOrientation
* CATOrientationPositive if the sum of positive areas is bigger than the negative one(s),
* CATOrientationNegative if the sum of negative areas is bigger than the positive one(s),
* CATOrientationUnknown if the computed area is null or perfectly balanced between negative and positive areas,
* @return 
* E_FAIL if the request doesn't make sense because the input topological object doesn't define any oriented area,
* S_FALSE if the returned orientation is Unknown after computation on a valid input,
* S_OK if a positive or negative orientation has been computed and returned
*/
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMEvalTopoAreaOrientation(
  CATSoftwareConfiguration * iConfig,
  CATTopology              * iTopObject,
  const CATMathDirection   & iRefDirection,                                                      
  CATOrientation           & oTopoAreaOrientation);

/**
* ComputeTopoAdvancedBox() function
* The main purpose of this function consists in computing the advanced bounding box of a topological object.
* The optional direction allows the caller to force the output box to be an extrusion of a 2D-Box in this input direction
* The returned AdvancedBox might wrap an OBB, an OBBCloud or an AABB according to the specification of the smallest bounding box.
* see CATMathAdvancedBoxTypeEnum.h for the different types, CATMathOBB2DType is not supported by this function
* This service is available for both exact and polyhedral objects.
* @param iConfig
* The pointer to the software configuration driving the versionning of code modifications
* @param iTopObject
* The topological object defining a bounding box : 
* CATBody, CATDomain, CATCell
* @return 
* The pointer to the computed CATMathAdvancedBox, to be deleted by the caller after use
* Null if the request doesn't make sense because the input topological object doesn't define any bounding box (empty body ?)
* 3 possible types (CATMathAdvancedBoxType) for the returned CATMathAdvancedBox
* CATMathAABBType     Axis Aligned Bounding Box
* CATMathOBBType      Oriented Bounding Box
* CATMathOBBCloudType Oriented Bounding Box Tree
*(CATMathOBB2DType    not supported by this function)
*/
ExportedByCATGMOperatorsInterfaces CATMathAdvancedBox * CATPGMComputeTopoAdvancedBox(
  CATSoftwareConfiguration * iConfig,
  CATTopology              * iTopObject);

//------------------------------------------------------------------------------
// finds all the faces adjacent to the RefFace
// iPropagMod    = CATSmooth (default) : propagation through smooth edges only
//               = Other               : propagation through all edges
// faces :         List of the adjacent faces which verify the propagation mode
// OtherAdjFaces : List of the "stopping" faces (adjacent, but don't propagate)
// iPropagEdges  : Input list of the edges which mandatory propagate
// oTransitEdges : List of the propagation edges corresponding to each result face
//                 = edge, if the edge was in iPropagEdge
//                 = NULL, else
// OnlyPropag    : TRUE if oTransitEdges will contains only mandatory propagate edges
// oBorders      : Edges n'ayant pas propage pour cette adjacence (bords)
// iForbiddenBoundingEdges : Les faces bordees par une des edges de cette liste seront eliminees
//                 de la solution
//------------------------------------------------------------------------------ 
ExportedByCATGMOperatorsInterfaces void CATPGMGetAllAdjacentFaces(
  CATSoftwareConfiguration *iConfig,
  CATBody *InitBody,
  CATFace *RefFace,
  CATLISTP(CATFace) *faces,
  CATDomain *iDomain = 0,
  int iPropagMod = CATSmooth,
  CATLISTP(CATFace) *OtherAdjFaces = NULL,
  CATLISTP(CATEdge) *oTransitEdges = NULL,
  CATLISTP(CATEdge) *iPropagEdges = NULL,
  CATBoolean OnlyPropag = FALSE,
  CATLISTP(CATEdge) *oBorders = NULL,
  CATLISTP(CATEdge) *iForbiddenBoundingEdges = NULL);

/* @nodoc */
ExportedByCATGMOperatorsInterfaces void CATPGMGetComplementaryCell(
  CATBody *iBody,
  CATSoftwareConfiguration *iConfig,
  CATCell *iCell,
  CATCell *iBorderCell,
  CATLISTP(CATCell) &oComplementaryCell,
  CATBody *iNewBody = NULL,
  CATDomain *iDomain = NULL);

#endif /* CATPGMTopologicalUtilities_h_ */
