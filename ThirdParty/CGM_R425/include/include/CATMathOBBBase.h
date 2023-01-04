//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
// CATMathOBBBase.h
// Oriented Bounding Box
// This class can represent any rectangular box in 3D space. 
// The box is composed  of a center expressed in the global axis system
//                      of 3 ORTHONORMAL directions expressed in the global axis system
//                      of the box' half diagonal expressed in the box' system

//=============================================================================
// 2009-02-05   JXO/XXC: New
// 2009-04-07   ZIB: create CATMathOBBBase based on CATPolyOBB
// 2010-03-23   ZIB: create CATMathOBBBase class to be used outside of the
//                   CATMathAdvancedBox system when memory use is critical
// 2014-09-01   KJD: Data migration from float to double
// 2014-10-10   KJD: the float data are put under define DEPRECATED_FloatBehavior
// 2021-10-28   NLD: DistancePoint2BoxPart()      est renommée SquareDistancePoint2BoxPart()
//                   DistanceEdge2Edge_NoBorder() est renommée SquareDistanceEdge2Edge_NoBorder()
//                   (N.B méthodes du 12/06/09)
//=============================================================================
#ifndef CATMathOBBBase_H
#define CATMathOBBBase_H


#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathPointf.h"
#include "CATMathVectorf.h"
#include "CATMathTransformation.h"
#include "CATMathBox.h"
#include "CATMathDebug.h"
#include "CATMath.h"
#include "CATMathInline.h"
#include "CATLISTV_CATMathPoint.h"

//output
#ifdef OBBBase_STDUse
//WARNING : when OBBBase_STDUse is defined, several fw (ex : CATMaterialRemovalSimulation) does not build
#include <iostream>
using namespace std;
#endif
class CATMathOBBBase;

#define CATMathOBB_RemoveFloatAPI
#ifdef CATMathOBB_RemoveFloatAPI
#define CATMATHOBBBASE_DOUBLEMIGRATION
#define CATMathOBB_MigrateOnDoubleAPI
#define CATMATHOBBBASE_DOUBLEMIGRATION_MRS
#endif


/**
* Oriented bounding box base class
* Do not include virtual methods here as this class has tight memory consumption constraints
* Note that boxes were stored using floats until the end of 2014 and using double after.
*/
class ExportedByCATMathematics CATMathOBBBase
{
public:
  /**
  * Build an empty undefined OBB
  */
                                CATMathOBBBase();

  /**
  * Build an OBB containing a given array of points
  * @param[in] iPointList the points.
  * @param[in] iSize the array's length.
  */
                                CATMathOBBBase(const CATMathPoint * iPointList,
                                                     int            iSize     );

  /**
  * Duplicate an OBB
  */
                                CATMathOBBBase(const CATMathOBBBase & iOBBToCopy);

  /**
  * Build an OBB from an axis aligned box.
  */
                                CATMathOBBBase(const CATMathBox     & iBoxToCopy);

  /**
  * Build on OBB from an axis aligned box given as doubles.
  */
                                CATMathOBBBase(double xMin, double xMax,
                                               double yMin, double yMax,
                                               double zMin, double zMax);

  /**
  * Build on OBB from an axis aligned box given as floats.
  */
                                CATMathOBBBase(float xMin, float xMax,
                                               float yMin, float yMax,
                                               float zMin, float zMax);


  /**
  * Build an OBB
  * @param[in] iBasis 3 orthonormal directions
  * @param[in] iDiag the box' half diagonal (ie the vector between
  *                     its center and the top right corner)
  * @param[in] iCenter the box' center
  */
                                CATMathOBBBase(const CATMathVector   iBasis[],
                                               const CATMathVector & iDiag   ,
                                               const CATMathPoint  & iCenter );

                               ~CATMathOBBBase();

  /**
  * Test for intersection against another OBB
  * @param[in] iOBB the other OBB
  * @return 1 if the OBBs intersect, 0 if they don't, -1 upon error
  */
          int                   IsIntersecting(const CATMathOBBBase &iOBB) const;

  /**
  * Test for intersection against another OBB
  * @param[in] iOBB the other OBB
  * @param[in] iTolerance a tolerance used when testing for intersection.
  *            More precisely the both boxes are inflated by iTolerance/2 before the intersection test
  * @return 1 if the OBBs intersect, 0 if they don't, -1 upon error
  */
          int                   IsIntersecting(const CATMathOBBBase &, double iTolerance) const;

  /**
  * Test for point inclusion 
  * @param[in] iPoint The point.
  * @param[in] iTolerance a tolerance used when testing for inclusion
  * @return 1 if the point is contained by the OBB (inflated by iTolerance), 0 if it isn't, -1 upon error
  */
         int                    IsContaining(const CATMathPoint &, double iTolerance) const;

  /**
  * Get a box containing the OBB
  * @param[out] oBox the axis aligned box.
  */
         void                   GetBox(CATMathBox &oBox) const;

  /**
  * Inflate the OBB more precisely inflate the box' half diagonal expressed in the box' system
  * @param[in] iTol the absolute (as opposed to relative) inflation value.
  */
         void                   Inflate(double iTol);

  /**
  * Check if the OBB is defined.
  * @return TRUE if the OBB is defined, FALSE otherwise.
  */
  INLINE CATBoolean             IsDefined() const;

  /**
  * Evaluate the minimum square distance to a point.
  * @param[in] iPoint the point.
  * @return negative value upon error, the square distance otherwise.
  */
         double                 SquareDistanceTo(const CATMathPoint &iPoint) const;

  /**
  * Evaluate the minimum square distance to another OBB cloud.
  * @param[in] iOBB the other OBB cloud.
  * @return negative value upon error, the square distance otherwise.
  */
         double                 SquareDistanceTo(const CATMathOBBBase &iOBB) const;

  /**
  * Define an OBB containing a given array of points
  * @param[in] iPointList the points.
  * @param[in] iSize the array's length.
  */
         HRESULT                DefineElements(const CATMathPoint * iPointList, int iSize);

#ifndef CATMathOBB_RemoveFloatAPI
  /**
  * @return the first direction
  */
  INLINE CATMathVectorf         U() const;
  /**
  * @return the second direction
  */
  INLINE CATMathVectorf         V() const;
  /**
  * @return the third direction
  */
  INLINE CATMathVectorf         W() const;

  /**
  * @return the box' center
  */
  INLINE CATMathPointf          Center() const;
  /**
  * @return the box' half diagonal
  */
  INLINE CATMathVectorf         Diagonal() const;
#endif

  /**
  * @return the first direction of the box expressed in the global axis system
  */
  INLINE CATMathVector          UDir() const;
  /**
  * @return the second direction of the box expressed in the global axis system
  */
  INLINE CATMathVector          VDir() const;
  /**
  * @return the third direction of the box expressed in the global axis system
  */
  INLINE CATMathVector          WDir() const;

  /**
  * @return the box' center expressed in the global axis system
  */
  INLINE CATMathPoint           CenterPoint() const;
  /**
  * @return the box' half diagonal expressed in the box' system
  */
  INLINE CATMathVector          BoxDiagonal() const;
  /**
  * Convert a point in the box' coordinate system to a global point
  * @param[in] iLocalPoint the point in the box' coordinate system
  * @return the point in the global coordinate system.
  */
         CATMathPoint           UVWtoXYZ           (const CATMathPoint & iLocalPoint) const;
  /**
  * Convert a point in the global coordinate system to the box'
  * @param[in] iLocalPoint the point in the global coordinate system
  * @return the point in the box' coordinate system.
  */
         CATMathPoint           XYZtoUVW           (const CATMathPoint & iGlobalPoint) const;

  /**
  * Convert a vector in the box' system to a global vector
  * @param[in] iLocalVector the point in the box' system
  * @return the vector in the global system.
  * Remark :
  * As it is a vector transformation, only the rotation is applied contrary to the APi with CATMathPoint
  */
         CATMathVector          UVWtoXYZv          (const CATMathVector & iLocalVector) const;

  /**
  * Convert a vector of the global system to a vector of the box'system
  * @param[in] iLocalVector the vector in the global system
  * @return the vector in the box'system.
  * Remark :
  * As it is a vector transformation, only the rotation is applied contrary to the APi with CATMathPoint
  */
         CATMathVector          XYZtoUVWv          (const CATMathVector  & iGlobalVector) const;

         double                 SquareDistanceMin  (const CATMathPoint   & iPoint) const;
         double                 SquareDistanceMax  (const CATMathPoint   & iPoint) const;
         double                 SquareDistanceMin  (const CATMathOBBBase & iOBB) const;
         double                 SquareDistanceMax  (const CATMathOBBBase & iOBB) const;
         double                 MaxSquareDistanceTo(const CATMathPoint   &) const;
         double                 MaxSquareDistanceTo(const CATMathOBBBase &) const;

  /**
  * Get the box' corners in the global axis system
  * @param[out] oCornersList list of the corners
  */
         HRESULT                GetCorners(CATLISTV(CATMathPoint) & oList) const;

  /**
  * Compute the coordinates of the box iOBB in the box' system
  * @param[in] iOBB the box to convert
  * @param[out] oOBB the initial box expressed in the this' system
  */
         void                   ConvertIn(const CATMathOBBBase & iOBB,
                                                CATMathOBBBase & oOBB) const;

  /**
  * Compute the coordinates in the box' system  of the point iSourceLocalPoint defined in the iSourceOBB's system. 
  * @param[in] iSourceLocalPoint the point in the iSourceOBB' coordinate system to convert
  * @param[in] iSourceOBB the initial box using to define iSourceLocalPoint
  * @param[out] oLocalPoint the point in the box' coordinate system
  */
         void                   ConvertIn(const CATMathPoint   & iSourceLocalPoint,
                                          const CATMathOBBBase & iSourceOBB       ,
                                                CATMathPoint   & oLocalPoint      ) const;

  /**
  * Compute the coordinates in the box' system of the center of the iSourceOBB box. 
  * @param[in] iSourceOBB the box whose center has to be converted
  * @param[out] oLocalCenter the center of the iSourceOBB box in the box' coordinate system
  */
         void                   ConvertCenterIn(const CATMathOBBBase & iSourceOBB,
                                                      CATMathPoint   & oLocalCenter) const;

  /**
  * Test if the iOBB box is included in the box' system within the tolerance iTolerance
  * @param[in] iOBB The box to test.
  * @param[in] iTolerance the tolerance 
  * @return 1 if the box is contained , 0 if it isn't, -1 upon error
  */
         CATBoolean             IsContaining(const CATMathOBBBase & iOBB,
                                                   double           iTolerance) const;

  /**
  * Compute in the global axis system the vector 
  * from the point iSourceLocalPoint expressed in the box' system 
  * to the point iTargetLocalPoint expressed in the iTargetOBB's system 
  * @param[in] iSourceLocalPoint the first point of the vector expressed in  the box's coordinate system 
  * @param[in] iTargetLocalPoint the target point of the vector expressed in the iTargetOBBs' coordinate system 
  * @param[in] iTargetOBB the box where is defined iTargetLocalPoint 
  * @param[out] oVector the vector in the global axis system
  */
         void                   GetVectorBetween(const CATMathPoint   & iSourceLocalPoint,
                                                 const CATMathPoint   & iTargetLocalPoint,
                                                 const CATMathOBBBase & iTargetOBB       ,
                                                       CATMathVector  & oVector          ) const;

  // Transformation
  friend ExportedByCATMathematics CATMathOBBBase operator * (const CATMathTransformation & iTransfo,
                                                             const CATMathOBBBase        & iOBB);

  /*
  * Compute the axis aligned box built if the box's axis was considered as the global axis system
  * and the transformation which transforms the global axis system into the box'axis 
  * i.e. the transformation to apply to the CATMathBox obox to obtain the box
  * @return E_FAIL if an error occurs (invalid box, ...), <tt>S_OK</tt> otherwise. 
  */
         HRESULT                ConvertToBoxAndTransformation(CATMathBox            & obox,
                                                              CATMathTransformation & otransfo) const;
         HRESULT                Absorb                       (CATMathOBBBase        & iobb);

  /**
  * @return the OBB's volume
  */
         double                 Volume() const;


  CATMathOBBBase &operator =(const CATMathOBBBase & iOBBToCopy);

         void                   PrintBoxData();
         void                   PrintBoxCorners();

protected:
  double _Dir    [9];
  double _Center [3];
  double _Diag   [3];
#ifdef DEPRECATED_FloatBehavior
  float  _Dirf   [9];
  float  _Centerf[3];
  float  _Diagf  [3];
  int    _DoubleOption;
#endif
  int    _TraceLevel;


private:
  /** Static auxiliary function for minimum distance operator between
  *  two OBB's.  Determines the distance between a point and a part
  *  of an OBB (the OBB itself, one of its faces, edges or vertices)
  *@param C1toC2: vector from the point to the center of the OBB
  *part, expressed in the basis of the first OBB.
  *@param map2: a mapping to retrieve the basis of the OBB part from
  *the basis of the OBB. E.g., if the part is a face of the original
  *OBB, with directions V and W, then one have map2[0]=1 (for V) and
  *map2[1]=2 (for W) and map[2]=0 (for the normal U).
  *@param diag2: a reference to the dimension of the OBB in each of
  *its directions.
  *dim2: dimension of the OBB part: 0 for a vertex, 1 for an edge, 2
  *for a face.
  *@param R: matrix containing the scalar products between any basis
  *vector of the first (this) OBB and any basis vector of the second
  *OBB.
  *@swap: boolean value that indicates if the OBB part belongs to the
  *first OBB (this, swap==TRUE) or to the second OBB (swap==FALSE).
  *@return the squared distance from the point to the OBB part.
  */
  static double            SquareDistancePoint2BoxPart(      double     C1toC2[],
                                                       const int        map2  [],
                                                       const double     diag2 [],
                                                       const int        dim2    ,
                                                             double     R[3][3] ,
                                                             CATBoolean swap);
  /** Static auxiliary function for minimum distance operator between
  *  two OBB's. Determines the distance between a segment of each
  *  OBB, iff the minimum distance between the lines they generate is
  *  made by two points on the segments. If one point is outside one
  *  segment, return a large number.
  *@param C1toC2: vector from the first segment center to the second
  *segment center, expressed in the basis of the first OBB.
  *@param map1: a mapping to retrieve the direction of the first
  *segment from the basis of the first OBB. E.g., if the direction of
  *the segment is the V direction in the OBB, then one have map2[0]=1
  *(for V) and map2[1]=0 or 2 (for orthogonal directions U or W) and
  *map[2]=0 or 2 (as for map[1]).
  *@param diag1: a reference to the dimension of the OBB in each of
  *its directions.
  *@param map2: as for the map1 parameter, but for the second
  *segment and second OBB.
  *@param diag2: a for the map1 parameter, but for the second
  *segment and second OBB.
  *@param R: matrix containing the scalar products between any basis
  *vector of the first (this) OBB and any basis vector of the second
  *OBB.
  */
  static double           SquareDistanceEdge2Edge_NoBorder(      double C1toC2[],
                                                           const int    map1  [],
                                                           const double diag1 [],
                                                           const int    map2  [],
                                                           const double diag2 [],
                                                                 double R [3][3]);

};

ExportedByCATMathematics CATMathOBBBase operator * (const CATMathTransformation & iTransfo,
                                                    const CATMathOBBBase        & iOBB);

// _____________________________________________________________________________
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// Inline methods implementation.
// _____________________________________________________________________________
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

CATBoolean CATMathOBBBase::IsDefined() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return _Diagf[0] >= 0.;
  else
#endif
    return _Diag[0] >= 0.;
}

//------------------------------------------------------------------------------
#ifndef CATMathOBB_RemoveFloatAPI
CATMathVectorf CATMathOBBBase::U() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathVectorf        (_Dirf[0*3+0], _Dirf[0*3+1], _Dirf[0*3+2]);
  else
#endif
    return CATMathVectorf((float)(_Dir[0*3+0]), (float) (_Dir[0*3+1]), (float)(_Dir[0*3+2]));

}

//------------------------------------------------------------------------------
CATMathVectorf CATMathOBBBase::V() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathVectorf        (_Dirf[1*3+0],          _Dirf[1*3+1],          _Dirf[1*3+2]);
  else
#endif
    return CATMathVectorf((float)(_Dir [1*3+0]), (float)(_Dir [1*3+1]), (float)(_Dir [1*3+2]));
}

//------------------------------------------------------------------------------
CATMathVectorf CATMathOBBBase::W() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)

    return CATMathVectorf(        _Dirf[2*3+0],          _Dirf[2*3+1],          _Dirf[2*3+2]);
  else
#endif
    return CATMathVectorf((float)(_Dir [2*3+0]), (float)(_Dir [2*3+1]), (float)(_Dir [2*3+2]));
}

//------------------------------------------------------------------------------
CATMathPointf CATMathOBBBase::Center() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)

    return  CATMathPointf       (_Centerf[0],          _Centerf[1],          _Centerf[2]);
  else
#endif
    return CATMathPointf((float)(_Center [0]), (float)(_Center [1]), (float)(_Center [2]));
}

//------------------------------------------------------------------------------
CATMathVectorf CATMathOBBBase::Diagonal() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return  CATMathVectorf       (_Diagf[0],          _Diagf[1],          _Diagf[2]);
  else
#endif
    return CATMathVectorf((float)(_Diag [0]), (float)(_Diag [1]), (float)(_Diag [2]));

}
#endif

//------------------------------------------------------------------------------
CATMathVector CATMathOBBBase::UDir() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathVector(_Dirf[0*3+0], _Dirf[0*3+1], _Dirf[0*3+2]);
  else
#endif
    return CATMathVector(_Dir [0*3+0], _Dir [0*3+1], _Dir [0*3+2]);
}

//------------------------------------------------------------------------------
CATMathVector CATMathOBBBase::VDir() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathVector(_Dirf[1*3+0], _Dirf[1*3+1], _Dirf[1*3+2]);
  else
#endif
    return CATMathVector(_Dir [1*3+0], _Dir [1*3+1], _Dir [1*3+2]);
}

//------------------------------------------------------------------------------
CATMathVector CATMathOBBBase::WDir() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathVector(_Dirf[2*3+0], _Dirf[2*3+1], _Dirf[2*3+2]);
  else
#endif
    return CATMathVector(_Dir [2*3+0], _Dir [2*3+1], _Dir [2*3+2]);

}

//------------------------------------------------------------------------------
CATMathPoint CATMathOBBBase::CenterPoint() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathPoint(_Centerf[0], _Centerf[1], _Centerf[2]);
  else
#endif
    return CATMathPoint(_Center [0], _Center [1], _Center [2]);
}

//------------------------------------------------------------------------------
CATMathVector CATMathOBBBase::BoxDiagonal() const
{
#ifdef DEPRECATED_FloatBehavior
  if(!_DoubleOption)
    return CATMathVector(_Diagf[0], _Diagf[1], _Diagf[2]);
  else
#endif
    return CATMathVector(_Diag [0], _Diag [1], _Diag [2]);
}

#endif
