#ifndef CATMathSetOfPoints_h
#define CATMathSetOfPoints_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"

#include "YN000MAT.h"
#include "IUnknown.h"
#include "CATMathSetOf3DObjects.h"
#include "CATMathInline.h"

#include "CATTolerance.h"
#include "CATMathPoint.h"

class CATMathVector;
/**
 * Class representing a set of CATMathPoints.
 *<br>The size is defined by a number of CATMathPoints
 *<tt>NbPoints</tt>. The index of the first CATMathPoint is <tt>0</tt>.
 *<br>The <tt>SetNumberOfPoints</tt> method enlarges the memory if
 * needed, while the <tt>Compress</tt> inherited method releases the free 
 * unused memory.
 */
class ExportedByYN000MAT CATMathSetOfPoints : public CATMathSetOf3DObjects
{
 public:
/**
 * Constructs an empty CATMathSetOfPoints with no point.
 */
  CATMathSetOfPoints();

/**
 * @nodoc
 * @deprecated V5R20 SetPointNumber
 * Constructs a CATMathSetOfPoints of a given size.
 *<br>The memory is allocated, but the values of the points are not initialized.
 * Use <tt>SetPoint</tt> to initialize them.
 */
  CATMathSetOfPoints(CATLONG32 iNbPoints);

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs from an array of CATMathPoints.
 */ 
  CATMathSetOfPoints(CATLONG32 iNbPoints, const CATMathPoint iPointsToCopy[]);

/**
 * Copy constructor.
 */
  CATMathSetOfPoints(const CATMathSetOfPoints & iSetToCopy);

/**
 * Destructor.
 */
  ~CATMathSetOfPoints();

  //---------------------------------------------------------------------------
  //- Setting and getting the points.
  //---------------------------------------------------------------------------

 /**
 * Constructs from an array of CATMathPoints.
 */ 
  HRESULT Set(CATLONG32 iNbPoints, const CATMathPoint iPointsToCopy[]);


/**
 * Returns the number of points of <tt>this</tt> CATMathSetOfPoints.
 */
  CATLONG32 GetNumberOfPoints() const;

  /**
  * @nodoc
  * @deprecated V5R20 SetPointNumber
  * Allocates the memory for <tt>this</tt> CATMathSetOfPoints.
  */
  void SetNumberOfPoints(CATLONG32 iCountPoints);  

/**
  * Allocates the memory for <tt>this</tt> CATMathSetOfPoints.
  * @return E_FAIL if the given data is not positive, S_OK otherwise.
  */
  HRESULT SetPointNumber(CATLONG32 iCountPoints);  

/**
 * Returns the CATMathPoint locating at a given row and column.
 *<br>The index <tt>iIndexPoint</tt> starts at <tt>0</tt>.
 *<br>Use preferently the second method signature if you want to avoid an
 * useless constructor.
 */
  CATMathPoint   GetPoint(CATLONG32  iIndexPoint) const;

/**
 * Retrieves the CATMathPoint locating at a index.
 *<br>The index <tt>iIndexPoint</tt> starts at <tt>0</tt>.
 */
  void GetPoint(CATLONG32 iIndexPoint, CATMathPoint &ioPoint);
  
/**
 * Returns the array of CATMathPoints.
 *<br>Note that the returned array is used by the CATMathSetOfPoints and
 * must not be deleted.
 */
  CATMathPoint * GetPoints() const;

/**
 * Initializes the values of a CATMathPoint in the CATMathSetOfPoints.
 * <br>The index <tt>iIndexPoint</tt> starts at <tt>0</tt>.
 */
  void SetPoint(const CATMathPoint & iPoint, CATLONG32 iIndex);

/**
 * @nodoc
 * Use now the former signature of this method.
 */
  void SetPoint(double , double , double , CATLONG32 );

  
//
//- Distance and SquareDistance between a set of points and a point
//
/** 
 * Returns the distance between a CATMathPoint and 
 * <tt>this</tt> CATMathSetOfPoints.
 * @param iP
 * The point to which the distance is computed.
 * @param ioIndex
 * The index (beginning at <tt>0</tt>) of a point of <tt>this</tt>
 * to which the distance is minimum.
 */
  double       DistanceTo (const CATMathPoint & iP, CATLONG32 & ioIndex) const ;

/** 
 * Returns the square distance between a CATMathPoint and 
 * <tt>this</tt> CATMathSetOfPoints.
 * @param iP
 * The point to which the distance is computed.
 * @param ioIndex
 * The index (beginning at <tt>0</tt>) of the point of <tt>this</tt>
 * to which the distance is minimum.
 */
  double SquareDistanceTo (const CATMathPoint & iP, CATLONG32 & ioIndex) const ;

//
//- Distance and SquareDistance between two sets of points
//
/** 
 * Returns the distance between  
 * <tt>this</tt> CATMathSetOfPoints and another CATMathSetOfPoints.
 * @param iSetOfPoints2
 * The other set of points.
 * @param ioIndex1
 * The index (beginning at <tt>0</tt>) of the point of <tt>this</tt>
 * to which the distance is minimum.
 * @param ioIndex2
 * The index (beginning at <tt>0</tt>) of the point of <tt>iSetOfPoints2</tt>
 * to which the distance is minimum.
 */
  double DistanceTo(const CATMathSetOfPoints * iSetOfPoints2,
                          CATLONG32          & ioIndex1     ,
                          CATLONG32          & ioIndex2     ) const;

/** 
 * Returns the square distance between  
 * <tt>this</tt> CATMathSetOfPoints and another CATMathSetOfPoints.
 * @param iSetOfPoints2
 * The other set of points.
 * @param ioIndex1
 * The index (beginning at <tt>0</tt>) of the point of <tt>this</tt>
 * to which the distance is minimum.
 * @param ioIndex2
 * The index (beginning at <tt>0</tt>) of the point of <tt>iSetOfPoints2</tt>
 * to which the distance is minimum.
 */
  double SquareDistanceTo(const CATMathSetOfPoints * iSetOfPoints2,
                                CATLONG32          & ioIndex1     ,
                                CATLONG32          & ioIndex2     ) const;

/**
 * Defines the type of space generated by a set of points.
 * @param POINT
 * All the points are at the same position.
 * @param LINE
 * The points are aligned on a line.
 * @param PLANE
 * The points are lying on a plane.
 * @param SPACE
 * The points represent the space .
 */
  enum AffineSpace { POINT, LINE, PLANE, SPACE };

/**
 * @nodoc
 * @deprecated V5R20 ComputeAffineSupport
 * Throws an error if an error occurs
 * Returns the type of the mean affine sub-space generated by <tt>this</tt> set of points.
 * Note that it does not return the type of the affine space of the smallest dimension passing through 
 * the points. The SPACE type is returned in very specific cases. The LINE and POINT types
 * are returned in cases of degeneracy. In a general case, the PLANE type is returned and 
 * this is the mean plane which is calculated.
 * <br>
 *  @param oAffineSpace
 * The type of space generated by the set of points. According to it, different types
 * of data are computed:
 * <dl>
 *  <dt>POINT </dt> <dd> Only the oOrigin is valued.
 *  <dt>LINE  </dt> <dd> The oOrigin and the oVector1 are valuated.
 *  <dt>PLANE </dt> <dd> The oOrigin and the first two vectors are
 *          valuated.
 *  <dt>SPACE </dt> <dd> The oOrigin and the three vectors are valuated.
 * </dl>
 *  
 */
  void GetAffineSpace    ( const CATTolerance&                     iTolObject   ,
                                 CATMathPoint                    & oOrigin      ,
                                 CATMathVector                   & oVector1     ,
                                 CATMathVector                   & oVector2     ,
                                 CATMathVector                   & oVector3     ,
                                 CATMathSetOfPoints::AffineSpace & oAffineSpace );
/**
 * @nodoc
 * @deprecated V5R15 GetAffineSpace above, ComputeAffineSupport
 */
  void GetAffineSpace    (       CATMathPoint                    & oOrigin      ,
                                 CATMathVector                   & oVector1     ,
                                 CATMathVector                   & oVector2     ,
                                 CATMathVector                   & oVector3     ,
                                 CATMathSetOfPoints::AffineSpace & oAffineSpace );

/**
 * @nodoc
 * @deprecated V5R15 ComputeAffineSupport
 * Throws an error if an error occurs
 * Returns the type of the mean affine sub-space generated by <tt>this</tt> set of points.
 * Note that it does not return the type of the affine space of the smallest dimension passing through 
 * the points. The SPACE type is returned in very specific cases. The LINE and POINT types
 * are returned in cases of degeneracy. In a general case, the PLANE type is returned and 
 * this is the mean plane which is calculated.
 * <br>
 *  @param oAffineSpace
 * The type of space generated by the set of points. According to it, different types
 * of data are computed:
 * <dl>
 *  <dt>POINT </dt> <dd> Only the oOrigin is valued.
 *  <dt>LINE  </dt> <dd> The oOrigin and the oVector1 are valuated.
 *  <dt>PLANE </dt> <dd> The oOrigin and the first two vectors are valuated.
 *  <dt>SPACE </dt> <dd> The oOrigin and the three vectors are valuated.
 * </dl>
 *  @param iTol
 *  geometrical tolerance to decide if the set of points are in the affine support
 *  @param iWeights
 *  array of weights of the Points in the Set used to compute an inertial matrix and the centre of mass.
 *  if not NULL (if NULL, all weigths are taken equal to 1.0)
 */

  void ComputeAffineSpace     ( const CATTolerance&                     iTolObject   ,
                                      double                            iTol         ,
                                      double                          * iWeights     ,
                                      CATMathPoint                    & oOrigin      ,
                                      CATMathVector                   & oVector1     ,
                                      CATMathVector                   & oVector2     ,
                                      CATMathVector                   & oVector3     ,
                                      CATMathSetOfPoints::AffineSpace & oAffineSpace ,
                                      double                          & oDistance    );

/**
 * @nodoc
 * @deprecated V5R15 ComputeAffineSupport (ComputeAffineSpace above XScale compliant)
 */
  void ComputeAffineSpace           ( CATMathPoint                    & oOrigin      ,
                                      CATMathVector                   & oVector1     ,
                                      CATMathVector                   & oVector2     ,
                                      CATMathVector                   & oVector3     ,
                                      CATMathSetOfPoints::AffineSpace & oAffineSpace ,
                                      double                          & oDistance    ,
                                      double                            iTol         ,
                                      double                          * iWeights     = NULL);

/**
 * Returns the type of the mean affine sub-space generated by <tt>this</tt> set of points.
 * Note that it does not return the type of the affine space of the smallest dimension passing through 
 * the points. The SPACE type is returned in very specific cases. The LINE and POINT types
 * are returned in cases of degeneracy. In a general case, the PLANE type is returned and 
 * this is the mean plane which is calculated.
 * <br>
 *  @param oAffineSpace
 * The type of space generated by the set of points. According to it, different types
 * of data are computed:
 * <dl>
 *  <dt>POINT </dt> <dd> Only the oOrigin is valued.
 *  <dt>LINE  </dt> <dd> The oOrigin and the oVector1 are valuated.
 *  <dt>PLANE </dt> <dd> The oOrigin and the first two vectors are valuated.
 *  <dt>SPACE </dt> <dd> The oOrigin and the three vectors are valuated.
 * </dl>
 *  @param iTol
 *  geometrical tolerance to decide if the set of points are in the affine support
 *  @param iWeights
 *  array of weights of the Points in the Set used to compute an inertial matrix and the centre of mass.
 *  if not NULL (if NULL, all weigths are taken equal to 1.0)
 * @return 
 * <tt>E_FAIL</tt> if an error occurs , <tt>S_OK</tt> otherwise. 
 */
  HRESULT ComputeAffineSupport( const CATTolerance&                     iTolObject   ,
                                      double                            iTol         ,
                                      double                          * iWeights     ,
                                      CATMathPoint                    & oOrigin      ,
                                      CATMathVector                   & oVector1     ,
                                      CATMathVector                   & oVector2     ,
                                      CATMathVector                   & oVector3     ,
                                      CATMathSetOfPoints::AffineSpace & oAffineSpace ,
                                      double                          & oDistance    );
/**
 * @nodoc
 * @deprecated V5R15 ComputeAffineSupport above
 */
  HRESULT ComputeAffineSupport( CATMathPoint                    & oOrigin      ,
                                CATMathVector                   & oVector1     ,
                                CATMathVector                   & oVector2     ,
                                CATMathVector                   & oVector3     ,
                                CATMathSetOfPoints::AffineSpace & oAffineSpace ,
                                double                          & oDistance    ,
                                double                            iTol         ,
                                double                          * weights      = NULL);
};

INLINE CATLONG32 CATMathSetOfPoints::GetNumberOfPoints() const
{
  return _CountDatas;
}

INLINE HRESULT CATMathSetOfPoints::SetPointNumber(CATLONG32 iCountPoints)
{
    HRESULT IsOK = SetNumberOf3DElements(iCountPoints);
   return IsOK;
}


//typedef CATMathSetOfPoints setpt;

#include "CATMathAbstractSetOfPoints.h"
#endif
