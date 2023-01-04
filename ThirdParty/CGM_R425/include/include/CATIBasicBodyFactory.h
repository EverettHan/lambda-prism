/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1998
//
// DESCRIPTION : CATIBasicBodyFactory class declaration
//
//  April 98         Documentation                 ??????.
//=============================================================================
#ifndef CATIBasicBodyFactory_H
#define CATIBasicBodyFactory_H
#include "CATGMOperatorsInterfaces.h"
//extern ExportedByCATGMOperatorsInterfaces const char* CATGeometricContainer ; 
//=============================================================================
#include "CATBaseUnknown.h"
#include "CATMathDef.h"
#include "CATTopDef.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATBody.h"
#include "CATMathDirection.h"

class CATMathSetOfVectors;

class CATBody;
class CATShell;
class CATWire;
class CATLoop;
class CATVertexInFace;
class CATVertexInVolume;
class CATCGMJournalList;
class CATTopData;
class CATSoftwareConfiguration;

class CATFace;
class CATEdge;
class CATVertex;


//-------------------------------------------------------------------------
//#include "CATGMOperatorsInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMOperatorsInterfaces IID IID_CATIBasicBodyFactory ;
#else
extern "C" const IID IID_CATIBasicBodyFactory ;
#endif

class ExportedByCATGMOperatorsInterfaces CATIBasicBodyFactory : public CATBaseUnknown
{
  CATDeclareInterface;
  
public:
  
  enum CATIBasicBodyType { 
    Linear,
    Circular,
    CircularComplementary,
    CircularDirect,
    Spline,
    Planar,
    Point };
  
  enum CATIBasicBodySubType { 
    Tangent,
    Normal,
    PointToPoint,
    PointDirection,
    MultiPoints,
    CenterRadius,
    CenterPoint,
    PointsRadius,
    //- Direct,
    //- Complementary,
    //- Complete,
    Directions,
    Curve,
    Equation,
    Offset,
    MeanOfPoints,
    CubicC2,
    WilsonFohler,
    BiTangent,
    TriTangent  };
  
  enum CATIBasicBodyGeoType { 
    Euclidean ,
    EuclideanOnSupport,
    Geodesic } ;
  
  enum CATIBasicBodyResultType { 
    NoSolution ,
    OnLine,
    OnPlane,
    OnCurve,
    ProjectedOnCurve,
    OnEdge,
    DistanceMinToEdge,
    ProjectedOnEdge,
    OnSurface,
    ProjectedOnSurface,
    OnFace,
    DistanceMinToFace,
    ProjectedOnFace,
    NotPertinent } ;
  
  //=========================================================================
  //- Create a basic body
  //-
  //- ParamValue : angle in radian, offset or radius.
  //- Orientation: orientation of the curve or the support when there is no
  //-              Curve
  //- The type and subtype allowed are as follow:
  //-
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  //- Type:     Linear
  //- SubType:  Tangent
  //-
  //- Arguments:  Vertex, Edge, Face
  //-
  //- The Vertex serves as the pivot on the Edge passed as argument and will
  //-   be projected on that Edge if necessary (ie: if the vertex is not ON 
  //-   the Edge).
  //- The Edge is the reference with which we calculate the new Edge.  The Vertex
  //-   must lie on this Edge, the direction of the Edge and the Length of the Edge
  //-   are used to calculate the new Length and directions of the new Edge.
  //- The Face provides a normal vector which becomes the rotation axis.  This
  //-   axis will pass through the Vertex and therefore crosses the Edge as well.
  //-
  //- The Param is the angle.  An angle of 0 degrees would result in returning 
  //-   an edge that would be parallel to the one passed as argument.  90 degrees
  //-   would result in an edge perpendicular to the Edge passed as argument.
  //-
  //- The Start and End values will limit the resulting Edge.  They are length values
  //-   by which the distance is calculated from the Vertex passed as argument.
  //-
  //- Orientation:  Allows the user to give a different orientation to the new Edge
  //-   which would otherwise be the same as the Edge passed as argument.
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  //- Type:     Linear
  //- SubType:  Normal
  //-
  //- Arguments:  Vertex, Edge
  //-             Vertex, Face
  //-             Vertex, Edge, Face
  //-
  //- The Vertex serves as the origin of the resulting Edge.
  //- The Edge, if there is one, gives the direction of the resulting Edge.
  //-   If the Edge is Euclidean, the direction is the same as the Edge.
  //-   If the Edge is Geodesic, the direction is the tangent at the point
  //-   where the passed Vertex is projected on this Edge.
  //- The Face, if there is one, provides a normal vector which will be the
  //-   new direction of the resulting Edge.
  //-
  //- If Both the Edge and the Face are passed as arguments, the cross product is 
  //-   taken with the Edge's direction and the Face's normal to give the resulting
  //-   Edge it's new direction.
  //-
  //- The Param is the angle.  An angle of 0 degrees would result in returning 
  //-   an edge that would be parallel to the direction calculated with either the
  //-   Edge or the Normal of the Face that were passsed as arguments.  An angle of 90
  //-   degrees would result in an edge perpendicular to the Edge passed as argument.
  //-
  //- The Start and End values will limit the resulting Edge.  They are length values
  //-   by which the distance is calculated from the Vertex passed as argument.
  //-
  //- Orientation:  Allows the user to give a different orientation to the new Edge
  //-   which would otherwise be the same as the Edge or Face passed as argument.  
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  //- Type:     Linear
  //- SubType:  PointDirection
  //-
  //- Arguments:  Vertex, Edge
  //-             Vertex, Edge, Face
  //-
  //- The Vertex serves as the origin of the resulting Edge.
  //- The Edge, gives the direction of the resulting Edge.  If a Face is given, the
  //-   direction of the resulting Edge is calculated with the normal of that Face
  //-   by rotating the new direction by an angle passed as argument (see Param).
  //-   If the Edge is Euclidean, the direction is the same as the Edge.
  //- The Face, if there is one, provides a normal vector which will be used to calculate
  //-   the new direction.  The resulting Edge is projected on the surface of the Face.
  //-
  //- The Param is the angle.  An angle of 0 degrees would result in returning 
  //-   an edge that would be parallel to the direction calculated with either the
  //-   Edge or the Normal of the Face that were passsed as arguments.  An angle of 90
  //-   degrees would result in an edge perpendicular to the Edge passed as argument.
  //-   NOT taken into account for this implementation.
  //-
    //- The Start and End values will limit the resulting Edge.  They are length values
    //-   by which the distance is calculated from the Vertex passed as argument.  In this 
    //-   method, they are mandatory!
    //-
    //- Orientation:  Allows the user to give a different orientation to the new Edge
    //-   which would otherwise be the same as the Edge or Face passed as argument.  
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    //- Type:     Linear
    //- SubType:  PointToPoint
    //-
    //- Arguments:  Vertex, Vertex
    //-             Vertex, Vertex, Face
//-
//- The First Vertex is the origin of the resulting Edge.
//- The Second Vertex is the end point of the resulting Edge.
//- The Face, if there is one, will be the surface on which the resulting Edge will
//-   be projected.
//-
//- The Param is the angle.  An angle of 0 degrees would result in returning 
//-   an edge that would be parallel to the direction calculated with either the
//-   Edge or the Normal of the Face that were passsed as arguments.  An angle of 90
//-   degrees would result in an edge perpendicular to the Edge passed as argument.
//-
//- The Start and End values will limit the resulting Edge.  They are length values
//-   by which the distance is calculated from the Vertex passed as argument.
//-
//- Orientation:  Allows the user to give a different orientation to the new Edge
//-   which would otherwise be the same as the Edge or Face passed as argument.  
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Linear
//- SubType:  MultiPoints
//-
//- Arguments:  CATLISTP(CATVertex)
//-             CATLISTP(CATVertex), Face
//-
//- The list of Vertices will be the start and end points of a series of segmented but
//-   connected lines.  Vertex1-Vertex2, Vertex2-Vertex3.  
//- The Face, if there is one, will be the surface on which the resulting Edge will
//-   be projected.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

//*************************************************************************

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Circular
//- SubType:  Direct
//-
//- Arguments:  Vertex, Vertex, Vertex
//-             
//- The three Vertices make a plane, and resulting circle is an arc passing from
//-   the first vertex through to the third vertex, by passing by the second vertex.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Circular
//- SubType:  Complementary
//-
//- Arguments:  Vertex, Vertex, Vertex
//-             
//- The three Vertices make a plane, and resulting circle is an arc passing from
//-   the first vertex through to the third vertex, but taking the opposite direction
//-   of the "direct" circle, therefore leaving the second vertex unconnected.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Circular
//- SubType:  Complete
//-
//- Arguments:  a) Vertex, Vertex, Vertex
//-             b) Vertex, Vertex, Face
//-             c) Vertex, Vertex, Edge
//-             d) Vertex, Edge, Face
//-             e) Vertex, Edge, Edge             
//-             f) Vertex, Face
//-             g) Vertex, Edge
//-             
//- a) The three Vertices make a plane, the resulting circle automatically passes
//- through all three vertices and makes a complete circle.
//- b) The surface on which the circle will rest is created with the Face's normal
//- and the Second vertex as origin (projected on surface to find the normal).  The
//- first vertex is used to define the radius
//- c) The same as b) except that the normal is the Edge transposed on the second
//- vertex.
//- d) The vertex is the origin, the Edge calculates its intersection on the Face for
//- the second vertex which represents the radius.  The Face provides a surface and a
//- normal.
//- e) Both edges give directions to create a surface and the Vertex is the origin.
//- A parameter for the radius must be provided.
//- f) The Vertex is the Origin of the circle.  The Face gives a normal (at projected vertex)
//- and a parameter for the radius must be provided.
//- g) The vertex is the origin of the circle.  The Edge is the normal and a parameter
//- must be provided to give the radius.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

//*************************************************************************

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  Curve
//-
//- Arguments:  Edge
//-             
//- All Vertices are not taken into account.
//- The Edge must be a circle.  The center of the circle becomes the origin of
//-   the resulting Face.  From the circle are extracted both directions 
//-   necessary for the creation of the resulting Face.
//- Any Face passed as argument will not be taken into account.
//-
//- The Param is the angle.  It is not taken into account.
//- The Start and End values are not taken into account.
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be the same as the Surface on which the circle lies.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  Directions
//-
//- Arguments:  Vertex, Edge, Edge.
//-             
//- The Vertex is the origin of the resulting Face.
//- The two Edges are used to create the two directions of the Face
//- Any Face passed as argument will not be taken into account.
//-
//- The Param is the angle.  It is not taken into account.
//- The Start and End values are not taken into account.
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be the same as the Surface on which the circle lies.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  Equations
//-
//- Arguments:  CATLength, CATLength, CATLength, CATLength
//-             
//- The first 3 CATLengths create a Normal-Vector at (0, 0, 0) for the resulting
//-   Face.  The last CATLength is the distance, from (0, 0, 0) in the direction
//-   of the Normal-Vector at which to create the Plane.
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be Positive.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  MultiPoints
//-
//- Arguments:  Face, Param
//-             
//- In both cases, 3 vertices are needed to create the resulting Face.  If less
//-   than 3 vertices are given, the Face is not created, if more than 3 are given,
//-   only the first 3 are taken into account.
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be Positive.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  Normal
//-
//- Arguments:  Edge
//-             Vertex, Edge
//-             Vertex, Vertex, Face
//-             
//- The first Vertex is the origin of the resulting Face. 
//- The second Vertex, if there is one, is projected on the Edge instead of the first
//-   Vertex in order to calculate the Normal.
//- The Edge is used for the Normal of the new Face.  If no Vertices are given, the origin
//-   of the Face is the StartingPoint of the Edge.  If a single Vertex is given, it 
//-   will be projected on the Edge and the normal will be calculated as a tangent at
//-   that point.  If two vertices are given, only the second Vertex is projected on the Edge.
//- If a Face is passed as argument, two Vertices are necessary.  The first vertex is the
//-   origin of the resulting Face, the second is projected on the Face to get the Normal at
//-   that point.  
//- 
//- The Param value is the angle.  For the moment, it is not taken into account
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be Positive.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  Offset
//-
//- Arguments:  Face
//-             
//- All Vertices and any Edge passed as argument is useless and won't be taken into account
//- The Face is the 'planar reference' from which the offset is used to create the new Face.
//-
//- The Param value is the distance of the offset.  A value of '0.' being the exact location
//-   of the Face passed as argument.
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be Positive.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  PointDirection
//-
//- NOT IMPLEMENTED!  SEE OTHER METHODS!
//-
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Planar
//- SubType:  Tangent
//-
//- Arguments:  Vertex, Face
//-             Vertex, Vertex, Face
//-             Edge, Face
//-             
//- The Vertex will be projected on the Face for the resulting Face's Normal.
//-   If two vertices are given, they are used to create a Rotation Axis.
//- The Edge, if there is one, becomes the rotation axis for the resulting Face.
//- The Face gives a reference for Normal calculations at the projected vertex or
//-   is simply rotated around the Axis by an angle given by Param.
//-
//- The Param value is the angle of rotation.
//-
//- Orientation:  Allows the user to give a different orientation to the new Face
//-   which would otherwise be Positive.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

//*************************************************************************

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//- Type:     Spline
//- SubType:  MultiPoints
//-
//- Arguments:  CATLISTP(CATVertex)
//-             CATLISTP(CATVertex), Face
//-
//- The list of Vertices will be the start and end points of a SplineCurve
//- The Face, if there is one, will be the surface on which the resulting Spline
//-   will be projected.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

//*************************************************************************
//*************************************************************************

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *Origin,
                                  const CATEdge              *Curve,
                                  const CATFace              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *StartPoint,
                                  const CATVertex            *EndPoint,
                                  const CATFace              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *FirstPoint,
                                  const CATVertex            *SecondPoint,
                                  const CATVertex            *ThirdPoint,
                                  const CATFace              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *Origin,
                                  const CATEdge              *FirstCurve,
                                  const CATEdge              *SecondCurve,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATBody              *FirstBody,
                                  const CATBody              *SecondBondy,
                                  const CATBody              *ThirdBody,
                                  const CATBody              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATBody              *FirstBody,
                                  const CATBody              *SecondBondy,
                                  const CATBody              *ThirdBody,
                                  const CATBody              *FourthBody,
                                  const CATBody              *iSupport,
                                  const CATOrientation        FirstOrientation = CATOrientationPositive,
                                  const CATOrientation        SecondOrientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATLISTP(CATVertex)  *Points,
                                  const CATMathSetOfVectors  *Vectors = NULL,
                                  const CATFace              *Support = NULL,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATLISTP(CATBody)    *Points,
                                  const CATMathSetOfVectors  *Vectors = NULL,
                                  const CATBody              *Support = NULL,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

//-------------------------------------------------------------------------
virtual CATBody * CreateBasicBody( CATTopData* iTopData,
                                  const CATIBasicBodyType    Type,
                                  const CATIBasicBodySubType SubType,
                                  const CATLength            A,
                                  const CATLength            B,
                                  const CATLength            C,
                                  const CATLength            D,
                                  const CATOrientation       Orientation = CATOrientationPositive,
                                  CATIBasicBodyResultType   *ResultType = NULL ) = 0;


/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *Origin,
                                  const CATEdge              *Curve,
                                  const CATFace              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *StartPoint,
                                  const CATVertex            *EndPoint,
                                  const CATFace              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *FirstPoint,
                                  const CATVertex            *SecondPoint,
                                  const CATVertex            *ThirdPoint,
                                  const CATFace              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATVertex            *Origin,
                                  const CATEdge              *FirstCurve,
                                  const CATEdge              *SecondCurve,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATBody              *FirstBody,
                                  const CATBody              *SecondBondy,
                                  const CATBody              *ThirdBody,
                                  const CATBody              *Support,
                                  const CATLength            *ParamValue  = NULL,
                                  const CATLength            *Start       = NULL,
                                  const CATLength            *End         = NULL,
                                  const CATOrientation        Orientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATBody              *FirstBody,
                                  const CATBody              *SecondBondy,
                                  const CATBody              *ThirdBody,
                                  const CATBody              *FourthBody,
                                  const CATBody              *iSupport,
                                  const CATOrientation        FirstOrientation = CATOrientationPositive,
                                  const CATOrientation        SecondOrientation = CATOrientationPositive,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATLISTP(CATVertex)  *Points,
                                  const CATMathSetOfVectors  *Vectors = NULL,
                                  const CATFace              *Support = NULL,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType     Type,
                                  const CATIBasicBodySubType  SubType,
                                  const CATLISTP(CATBody)    *Points,
                                  const CATMathSetOfVectors  *Vectors = NULL,
                                  const CATBody              *Support = NULL,
                                  const CATIBasicBodyGeoType  GeoType     = Euclidean,
                                  CATCGMJournalList          *Journal = NULL,
                                  CATIBasicBodyResultType    *ResultType = NULL ) = 0;*/

/** 
* @nodoc
* Deprecated
*/
/*virtual CATBody * CreateBasicBody( const CATIBasicBodyType    Type,
                                  const CATIBasicBodySubType SubType,
                                  const CATLength            A,
                                  const CATLength            B,
                                  const CATLength            C,
                                  const CATLength            D,
                                  const CATOrientation       Orientation = CATOrientationPositive,
                                  CATCGMJournalList         *Journal = NULL,
                                  CATIBasicBodyResultType   *ResultType = NULL ) = 0;*/
/** 
* @nodoc
* Defines the Software configuration to be taken 
* into acccount by <tt>this</tt> operator.
* @param iConfig
* The Software configuration.
*/
virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig) = 0;

/** 
* @nodoc
* Returns the Software configuration to be taken 
* into acccount by <tt>this</tt> operator.
* @return
* The Software configuration.
*/
virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const = 0;

//-------------------------------------------------------------------------
//- Get The Circular Data from the last Circular Body made,
//- the boolean is used to know if there were a circular body created
//-------------------------------------------------------------------------
virtual CATBoolean GetCircularData( CATMathPoint     &oCenter,
                                   double           &oRadius,
                                   CATMathDirection &oFirst,
                                   CATMathDirection &oSecond,
                                   double           &oStartAngle,
                                   double           &oEndAngle ) const = 0;


/** 
* @nodoc
* Defines the CATMathVector that must be normal 
* Should be called before CreateBasicBody to be taken into account
* @param oVector
* The Software configuration.
*/
virtual void SetNormalePlane(const CATMathVector & iVector) = 0;

/** 
* @nodoc
* Returns the normale to the built plane 
* should be used after CreateBasicBody
* @return
* The Vector normal to the plane
*/
virtual void GetNormalePlane(CATMathVector & oVector) const = 0;
};

CATDeclareHandler(CATIBasicBodyFactory,CATBaseUnknown);

#endif


