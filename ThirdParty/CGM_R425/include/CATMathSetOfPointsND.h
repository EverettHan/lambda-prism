#ifndef CATMathSetOfPointsND_H
#define CATMathSetOfPointsND_H
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
class CATMathSetOfLongs;
class CATMathVector2D;
class CATMathStream;


#include "YN000FUN.h"
#include "CATIAV5Level.h"
#include "CATMathDef.h"
#include "CATCGMStreamVersion.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"
#include "CATIACGMLevel.h"
#if defined ( CATIACGMV5R21 )
#include "CATMathInline.h"
#endif

/**
 * Class defining a set of points in <tt>R^n</tt>.
 */
class ExportedByYN000FUN CATMathSetOfPointsND : public CATCGMVirtual
{
 public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  //---------------------------------------------------------------------------
  // Object Management.
  //---------------------------------------------------------------------------
   /** 
   * Constructs a CATMathSetOfPointsND.
   * @param iN
   * The dimension of the points of the set.
   * @param iNumberOfPoints
   * The size of the set.
   */
                                 CATMathSetOfPointsND (const CATLONG32              iN            ,
                                                       const CATLONG32              iNumberOfPoint);

   /**
   * Copy constructor.
   */
                                       CATMathSetOfPointsND (const CATMathSetOfPointsND & iToCopy       ) ;
  virtual                             ~CATMathSetOfPointsND ();

  /**
   * Assignment operator.
   */
  virtual       CATMathSetOfPointsND & operator =           (const CATMathSetOfPointsND & iS            );

  //---------------------------------------------------------------------------
  // Information methods
  //---------------------------------------------------------------------------
  //  virtual CATMathClassId IsA() const ;
/**
 * Tests the class of <tt>this</tt> CATMathSetOfPointsND.
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathSetOfPointsND is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
*/
  virtual       CATBoolean             IsAKindOf            (const CATMathClassId         iClassId      ) const;

/**
 * Tests whether <tt>this</tt> CATMathSetOfPointsND is periodic.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathSetOfPointsND periodic,
 * <tt>FALSE</tt> otherwise.
*/
#if defined ( CATIACGMV5R21 )
  INLINE        CATLONG32              IsPeriodic           ()                                            const;
#else
                CATLONG32              IsPeriodic           ()                                            const;
#endif

/**
 * Returns the dimension of the space in which the points are defined.
 * @return
 * The dimension.
 */
#if defined ( CATIACGMV5R21 )
  INLINE        CATLONG32              GetDimension         ()                                            const;
#else
                CATLONG32              GetDimension         ()                                            const;
#endif

/**
 * Returns the number of points of <tt>this</tt> CATMathSetOfPointsND that are already set.
 * @return
 * The number of points that are already set.
 */
#if defined ( CATIACGMV5R21 )
  INLINE        CATLONG32              GetNumberOfPoints    ()                                            const;
#else
                CATLONG32              GetNumberOfPoints    ()                                            const;
#endif

 /**
 * Returns the maximum number of points of <tt>this</tt> CATMathSetOfPointsND.
 * @return
 * The maximum number of points (size of the allocation).
 */
                CATLONG32              GetMaxNumberOfPoints ()                                            const;

  // Get the current index of the point.
  // This method should be call after the Next() method.
/**
 * Returns the index of the iterator inside <tt>this</tt> CATMathSetOfPointsND.
 * @return
 * The index of the current point. This method should be called 
 * after the @href CATMathSetOfPointsND#Next method.
 */
                CATLONG32              GetCurrentIndex      ()                                            const;

  //---------------------------------------------------------------------------
  // Editing methods.
  //---------------------------------------------------------------------------
/**
 * Resets <tt>this</tt> CATMathSetOfPoints.
 * <br> The memory is not deleted and the class can be used again.
 */
  virtual       void                   Reset                ();

 /**
 * Resizes <tt>this</tt> CATMathSetOfPoints.
 * <br> The memory is adjusted, the content is lost.
 */
  virtual       void                   Resize               (const CATLONG32 iSize);

   /**
  * Packs <tt>this</tt> CATMathSetOfPoints.
  *<br> In this case, <tt>_MaxNumberOfPoint = _NumberOfPoint</tt>.
  */
  virtual       void                   Pack                 ();

 /**
 * Removes one point of <tt>this</tt> CATMathSetOfPointsND.
 * <br> The points after the removed point are shift, but the memory is not deleted 
 * (<tt>_MaxNumberOfPoint</tt> still remains the same).
 * @param iIndexToRemove
 * The index of the point to remove <tt> 0<= iIndexToRemove < NumberOfPoints </tt>.
 */
  virtual       void                   RemovePoint          (const CATLONG32              iIndexToRemove);

/**
 * Removes points of <tt>this</tt> CATMathSetOfPointsND.
 * <br> The remaining points are shift, but the memory is not deleted 
 * (<tt>_MaxNumberOfPoint</tt> still remains the same).
 * @param iPointsIndex
 * The list of the indexes of the points to remove.
 */
  virtual       void                   RemovePoints         (const CATMathSetOfLongs    & iPointIndex   );

/**
 * Sets the periodicity of <tt>this</tt >  CATMathSetOfPointsND.
 * @param iPeriodic
 * <br><b>Legal values </b>:
 * <dl><dt>1</dt><dd> Sets to periodic: in this case, the first and the last points must be the same.
 * <dt>0</dt><dd> unsets the periodicity.
 * </dl>
 */
  virtual       void                   SetPeriodic          (const CATBoolean             iPeriodic     = 1);

/**
 * Sets the value of a coordinate of a point.
 * @param iVal
 * The value to be set.
 * @param iCoordIndex
 * The index of the point coordinate (beginning at 0).
 * @param iPointIndex
 * The index of the point inside the set (beginning at 0).
 */
  virtual       void                   SetCoordAtPoint      (      double                 iVal          ,
                                                             const CATLONG32              iCoordIndex   ,
                                                             const CATLONG32              iPointIndex   );

 /**
 * Inverts the content of <tt>this</tt> CATMathSetOfPointsND.
 * @param ioResultingSet
 * The result of the inversion (must be previously allocated).
 */
  virtual       void                   Invert               (      CATMathSetOfPointsND & ioResultingSet) const;

/**
 * Swaps two points inside <tt>this</tt> CATMathSetOfPointsND.
 * @param iPointIndex1
 * The index of the first point to swap.
 * @param iPointIndex2
 * The index of the second point to swap.
 */
  virtual       void                   SwapPoints           (const CATLONG32              iPointIndex1  ,
                                                             const CATLONG32              iPointIndex2  );

/**
 * Inverts the content of <tt>this</tt> CATMathSetOfPointsND inside itself.
 */
  virtual       void                   AutoInvert           () ;

 
  /**
  * Splits a CATMathSetOfPointsND just after the point corresponding to the iIndex. 
  * The part of <tt>this</tt> CATMathSetOfPointsND before iIndex will stay in 
  * <tt>this</tt> CATMathSetOfPointsND, and the part after will go in  ioSetbis.
  * If needed, ioSetbis is reallocated,and <tt>this</tt> CATMathSetOfPointsND is disallocated.
  * @param iIndex
  * The index of the point where to split(0<=iIndex<NumberOfPoints). 
  * @param iSetbis
  * The new set after the split(must be previously allocated).
  * @param iMerge
  * The way to split.
  * <br><b>Legal values</b>: <tt>TRUE</tt> if the last point of new <tt>this</tt> CATMathSetOfPointsND. 
  * and the first point of <tt>iSetbis</tt> will be the same equal to iIndex point, <tt>FALSE</tt> if the last .
  * point of new <tt>this</tt> CATMathSetOfPointsND will be equal to iIndex point and the first point.
  * of <tt>iSetbis</tt> will be the iIndex+1  point.
  * @param iTolObject
  * The default tolerance.
  */
  virtual       void                   Split                (const CATLONG32              iIndex        ,
                                                                   CATMathSetOfPointsND & ioSetbis      ,
                                                                   CATBoolean             iMerge        ,
                                                             const CATTolerance         & iTolObject    = CATGetDefaultTolerance());

 /**
 * Concatenates a CATMathSetOfPointsND just after the last point of <tt>this</tt> CATMathSetOfPointsND.
   * If needed, <tt>this</tt> CATMathSetOfPointsND is reallocated.
 * @param iSetToConcatenate
 * The set to concatenate.
 * @param iMerge
 * The way to concatenate.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the last point of <tt>this</tt> CATMathSetOfPointsND 
 * and the first point of <tt>iSetToConcatenate</tt> must be merged, <tt>FALSE</tt> otherwise.
  */
  virtual       void                   AddSet               (const CATMathSetOfPointsND & iSetToConcatenate,
                                                                   CATBoolean             iMerge        );

/**
 * Resets the iterator to read the points again.
 * <br>Call <tt>Next</tt> after this method to make the first point as current.
 */
#if defined ( CATIACGMV5R21 )
  INLINE       void                    Beginning ();
#else
               void                    Beginning ();
#endif

/**
 * Skips to the next point of <tt>this</tt> CATMathSetOfPointsND.
 * <br>This next point becomes the current one. To read the first point, first call the <tt>Beginning</tt>
 * method, then call <tt>Next</tt>.
 */
                CATLONG32              Next      ();

/**
 * Returns the array of the coordinates of the all the points.
 * @return
 * The array of point coordinates. Must not be deleted as part of CATMathSetOfPointsND.
 */
#if defined ( CATIACGMV5R21 )
  INLINE const double                * GetPoints() const;
#else
         const double                * GetPoints() const;
#endif

/**
 * Retrieves the array of the coordinates of the current point.
 * @param ioPoint
 * The pointer to the coordinates, previously allocated to iN doubles (iN is the dimension of the points of the set). 
 */
               void                   GetPoint             (      double              *  ioPoint       ) const;

 /**
 * Retrieves the coordinates of a specific point of <tt>this</tt> CATMathSetOfPointsND.
 * @param iPointIndex 
 * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
 * @param ioPoint
 * The pointer to the coordinates, previously allocated to iN doubles (iN is the dimension of the points of the set).
 */
               void                   GetPoint             (const CATLONG32              iPointIndex   ,
                                                                  double              *  ioPoint       ) const;

  // Set the current point : replace the current.
/**
 * Replaces the coordinates of the current point.
 * @param iPoint
 * The array of the new coordinates. 
 */
               void                   ReplacePoint         (const double              *  iPoint        );

 /**
 * Replaces the coordinates of a specific point.
 * @param iPointIndex 
 * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
 * @param iPoint
 * The array of the new coordinates. 
 */
               void                   ReplacePoint         (const CATLONG32              iPointIndex   ,
                                                            const double              *  iPoint        );

   /**
   * Sets the coordinates of all the points.
   * If needed, <tt>this</tt> CATMathSetOfPointsND is reallocated.
   * @param iSize
   * The number of points that are set. 
   * @param iPoints
   * The coordinates of all the points.
  */
               void                   ReplacePoints        (const CATLONG32              iSize         ,
                                                            const double              *  iPoints       );

  /**
   * Inserts a  point at a specific position.
   * If needed, <tt>this</tt> CATMathSetOfPointsND is reallocated.
   * @param iPoint
   * The array of the new coordinates.
   * @param iPointIndex 
   * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
   */
  virtual      void                   InsertPoint          (const double              *  iPoint        ,
                                                            const CATLONG32              iPointIndex   );

    /**
   * Appends a  point at the end of the set.
   * If needed, <tt>this</tt> CATMathSetOfPointsND is reallocated.
   * @param iPoint
   * The array of the coordinates.
   */
  virtual      void                   AddPoint             (const double              *  iPoint        );

  /**
   * Appends a point at the end of the set if it is different from the last point.
   * If needed, <tt>this</tt> CATMathSetOfPointsND is reallocated.
   * @param iPoint
   * The array of the coordinates.
   * @param iTol
   * The tolerance of confusion.
   */
               CATLONG32              AddNewPoint          (const double              *  iPoint        ,
                                                            const double                 iTol          );

 /**
  * Builds the convex contour of a given two-dimensional set.
  * <br>The created contour is ordered, but its orientation is undefined.
  * @param iChoice 
  * A way to tune the result.
  * <b>Legal values</b>:
  * <dl><dt>0</dt><dd> for the convex contour stricto sensu
  *      <dt>1</dt><dd>  for a more convenient size of the result
  *              ( less points for a bit bigger area )
  * </dl>
  * @ param iTol    
  * The tolerance of confusion between 2 points.
  * @param ioConvex  
  * The convex contour.
  * <br>It must be previously allocated,
  *              by using the CATMathSetOfPointsND constructor, such as:
  *  <pre>oConvex ( this.GetDimension (), this.GetNumberOfPoints () + 1 )</pre>
  *   ( +1 is necessary for algorithm efficiency ).
  *           If the method failed, <tt>oConvex.GetNumberOfPoints</tt> reurns 0.
  */
               void                   ConvexContour        (const CATLONG32              iChoice       ,
                                                            const double                 iTol          ,
                                                                  CATMathSetOfPointsND & ioConvex      ) const;

  /**
   * Builds the marginless bounding box.
   * @param ioBox
   * The bounding box. Must be previously allocated <tt>ioBox[2][GetDimension ()]</tt>.
   */
               void                   BoundingBox          (      double              *  ioBox         ) const;

  //---------------------------------------------------------------------------
  // Analysis methods
  //---------------------------------------------------------------------------
  /**
  * Returns the length of the polyline in RN defined by the set of points.
  * @return
  * The length.
  */
               double                 Length               () const;

  // Find a polyline in RN defined by the set of points is increasing
  // or decreasing or nothing, on a specific coordonate
  // coor, such that 1<=coord<=Dim.
  /**
  * The monotony of a function.
  * @param Constant
  * The function is constant.
  * @param Increasing
  * The function is increasing.
  * @param Decreasing
  * The function is decreasing.
  * @param NoMonotonous
  * Otherwise.
  */
  enum MonotonyDiagnostic { Constant    ,
                            Increasing  ,
                            Decreasing  ,
                            NoMonotonous};

  /**
   * Tests whether <tt>this</tt> CATMathSetOfPointsND is monotonous with regards to one of its
   * coordinates.
   * @param iCoordNum
   * The point coordinate number(beginning at 1).
   * @return
   * The type of monotony.
   */
               CATMathSetOfPointsND::MonotonyDiagnostic
                                      IsMonotonousAlong    (const CATLONG32              iCoordNum     ) const;

 
   /**
   * Searches for a 3D circle defined by the set of points on 3 specific coordinates.
   * @param iCoordIndex
   * The array of 3 coodinates indexes to be taken into account, such that <tt>0 <= iCoord[i] < N, i=0,1,2</tt>.
   * @param ioRadius
   * The value of the radius of the circle.
   * @param ioCenter
   * The 3D center point.
   * @param ioU
   * The first normed vector of the circle plane.
   * @param ioV
   * The second orthonormed vector of the circle plane.
   * @param iTol
   * The tolerance to match the circle. By default, the numerical tolerance is used.
   * @param iPlanarityTol
   * The tolerance to match the circle plane. By default, the numerical tolerance is used.
   * @param iTolObject
   * The default tolerance.
   * @return
   * The result diagnosis.
   * <tt>1</tt> if a circle has been found, <tt>0</tt> otherwise.
   */
  virtual      CATLONG32              FindCircle           (const CATLONG32           *  iCoordIndex   ,
                                                                  double               & ioRadius      ,
                                                                  double              *  ioCenter      ,
                                                                  double              *  ioU           ,
                                                                  double              *  ioV           ,
                                                                  double                 iTol          = 0.,
                                                                  double                 iPlanarityTol = 0.,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

    /**
   * Searches for a line defined by the set of points on specific coordinates.
   * @param iNumCoord
   * The number of coordinates to take into account.
   * @param iCoordIndex
   * The array of <tt>iNumCoord</tt> coodinates indexes to be taken into account, 
   * such that <tt>0 <= iCoord[i] < N, i=0,..,iNumCoord-1</tt>.
   * @param iTol
   * The tolerance to match the line. By default, the numerical tolerance is used.
   * @param iTolObject
   * The default tolerance.
   * @return
   * The result diagnosis.
   * <tt>1</tt> if a line has been found, <tt>0</tt> otherwise.
   */
  virtual      CATLONG32              IsLinear             (const CATLONG32              iNumCoord     ,
                                                            const CATLONG32           *  iCoordIndex   ,
                                                            const double                 iTol          = 0.,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

  /**
   * The type of mathematical configurations of a set of points.
   * @param Ellipse
   * Ellipse.
   * @param Parabole
   * Parabola.
   * @param Hyperbole
   * Hyperbola.
   * @param DegenerateEmpty
   * The set of points is empty.
   * @param DegenerateOnePoint
   * The set of points is degenerated in only one point.
   * @param DegenerateOneLine
   * The set of points is corresponds to a line.
   * @param DegenerateTwoParallelLine
   * The set of points is corresponds to two parallel lines.
   * @param DegenerateTwoCrossingLine
   * The set of points is corresponds to two crossing lines.
   * @param Unedfined
   * No particular configuration is found.  
   */
  enum ConicType { Ellipse                   ,
                   Parabole                  ,
                   Hyperbole                 ,
                   DegenerateEmpty           ,
                   DegenerateOnePoint        ,
                   DegenerateOneLine         ,
                   DegenerateTwoParallelLines,
                   DegenerateTwoCrossingLines,
                   Undefined                 };
  /**
  * Searches for a conics defined by the set of points on 2 specific coordinates.
  * @param iCoordIndex1
  * The index (beginning at 0) of the first coordinate to take into account.
  * @param iCoordIndex2
  * The index (beginning at 0) of the second coordinate to take into account.
  * @param ioEquationParameters[6]
  * The array of the parameters (<tt>A, B, C, D, E, F</tt>) of the conics, given as follows:
  *<pre> AX**2+2BXY+CY**2+2DX+2EY+F=0</pre>.
  * The array must be previously allocated.
  * @param iTol
  * The tolerance to match the conics. By default, the numerical tolerance is used.
  * @param iTolObject
  * The default tolerance.
  * @return
  * The result diagnosis.
  * <tt>1</tt> if a conics has been found, <tt>0</tt> otherwise.
  */
  virtual      CATLONG32              FindConic            (      CATLONG32              iCoordIndex1  ,
                                                                  CATLONG32              iCoordIndex2  ,
                                                                  double                 ioEquationParameters[6],
                                                            const double                 iTol          = 0.,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

  // Find a 3D conic defined by the set of points on 2 specifics coordinates
  // given by coord1 and coord2 in [0,N[
  // oCenter is a 2D point in the plane baed on coordinates coord1 and coord2
  // oE is the conic excentricity
  // oA and oB are the major axis and minor axis
  // oPhi is the angle between the major axis and the first coordinate axis
  

   /**
  * From V5R17, searches for a conics defined by the set of points on 2 specific coordinates.
  * <br>All the pointer must be previously allocated.
  * @param iCoordIndex1
  * The index (beginning at 0) of the first coordinate to take into account.
  * @param iCoordIndex2
  * The index (beginning at 0) of the second coordinate to take into account.
  * @param ioConicType
  * A pointer to the found conic type.
  * The pointer must be previously allocated.
  * @param ioCenter
  * The 2D center point. Must be previously allocated.
  * @param ioE
  * A pointer to the excentricity
  * @param ioA
  * A pointer to the major radius.
  * @param ioB
  * A pointer to the minor radius.
  * @param ioPhi
  * A pointer to the angle between the  axis of major radius and the first coordinate axis.
  * @param iTol
  * The tolerance to match the conics. By default, the numerical tolerance is used.
  * @param iTolObject
  * The default tolerance.
  * @return
  * The result diagnosis.
  * <tt>1</tt> if a conics has been found, <tt>0</tt> otherwise.
  */
  virtual      CATLONG32              FindConic            (      CATLONG32              iCoordIndex1  ,
                                                                  CATLONG32              iCoordIndex2  ,
                                                                  ConicType           *  ioConicType   ,
                                                                  double                 ioCenter   [2],
                                                                  double              *  ioE           ,
                                                                  double              *  ioA           ,
                                                                  double              *  ioB           ,
                                                                  double              *  ioPhi         ,
                                                            const double                 iTol          = 0.,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

   /**
   * From V5R17 onwards, retrieves the conics parameters from its equation parameters.
   * <p>All the pointer must be previously allocated.
   * @param iEquationParameters[6]
   * The array of the parameters (<tt>A, B, C, D, E, F</tt>) of the conics, given as follows:
   *<pre> AX**2+2BXY+CY**2+2DX+2EY+F=0</pre>.
   * @param ioCenter
   * The 2D center point. Must be previously allocated.
   * @param ioE
   * A pointer to the excentricity
   * @param ioA
   * A pointer to the major axis.
   * @param ioB
   * A pointer to the minor axis.
   * @param ioPhi
   * A pointer to the angle between the major axis and the first coordinate axis.
   * @param iTol
   * The tolerance to match the conics. By default, the numerical tolerance is used.
   * @param iTolObject
   * The default tolerance.
   * @return
   * The result diagnosis.
   * <tt>1</tt> if a conics has been found, <tt>0</tt> otherwise. 
   */
  static       CATLONG32              FindConicParameters  (      double                 iEquationParameters[6],
                                                                  ConicType           *  oConicType    ,
                                                                  double                 ioCenter[2]   ,
                                                                  double              *  ioE           ,
                                                                  double              *  ioA           ,
                                                                  double              *  ioB           ,
                                                                  double              *  ioPhi         ,
                                                            const double                 iTol          = 0.,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance());

  /**
   * Tests if a point is on the polyline defined by <tt>this</tt> CATMathSetOfPointsND.
   * @param iPoint
   * The array of N coordinates.
   * @param iTol
   * The tolerance to match the test. By default, the numerical tolerance is used.
   * @param ioPointIndex
   * The index of the closest arc of <tt>this</tt> CATMathSetOfPointsND, if not <tt>NULL</tt>.
   * @return
   * The result diagnosis.
   * <tt>1</tt> if the point belongs to the polyline, <tt>0</tt> otherwise. 
   */
               CATLONG32              IsContaining         (const double              *  iPoint        ,
                                                            const double                 iTol          ,
                                                                  CATLONG32           *  ioPointIndex  = 0) const;
 

  /**
   * Tests if a point is equal to a point of  <tt>this</tt> CATMathSetOfPointsND.
   * @param iPoint
   * The array of N coordinates.
   * @param iTol
   * The tolerance to match the test. By default, the numerical tolerance is used.
   * @param ioPointIndex
   * The index of the equal point of <tt>this</tt> CATMathSetOfPointsND, if not <tt>NULL</tt>.
   * @param iTolObject
   * The default tolerance.
   * @return
   * The result diagnosis.
   * <tt>1</tt> if the point belongs to the polyline, <tt>0</tt> otherwise. 
   */
               CATLONG32              IsIncludedIn         (const double              *  iPoint        ,
                                                            const double                 iTol          ,
                                                                  CATLONG32            & ioPointIndex  ,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

   /**
   * Retrieves the two points of the polyline in RN defined by <tt>this</tt> CATMathSetOfPointsND which are the
   * closest to a given point.
   * To be used from V5R17.
   * @param iPoint
   * The array of N coordinates.
   * @param ioPoint1
   * A pointer to the coordinates of one of the two first closest points.
   * @param ioPoint2
   * A pointer to the coordinates of the other one.
   * @param iTolObject
   * The default tolerance.

   */ 
               void                   GetClosestPoints     (const double              *  iPoint        ,
                                                                  double              *  ioPoint1      ,
                                                                  double              *  ioPoint2      ,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

  /** 
   * Retrieves the closest point of the polyline in RN defined by <tt>this</tt> CATMathSetOfPointsND
   * to a given point.
   * @param iPoint
   * The array of N coordinates.
   * @param ioIndexPoint
   * The index of the closest point in <tt>this</tt> CATMathSetOfPointsND.
   * @param iTolObject
   * The default tolerance.
   * @return
   * The distance between <tt>iPoint</tt> and <tt>this</tt> CATMathSetOfPointsND.
   */
               double                 DistanceMin          (const double              *  iPoint        ,
                                                                  CATLONG32            & ioIndexPoint  ,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

 

   /**
   * Intersects <tt>this</tt> CATMathSetOfPointsND and a segment in RN.
   * @param ioIndex
   * The intersection diagnosis.
   * <tt>1</tt> if there is an intersection point, <tt>0</tt> otherwise. 
   * @param iPoint1
   * The array of N coordinates of the first point of the segment.
   * @param iPoint2
   * The array of N coordinates of the second point of the segment.
   * @param iTol
   * The tolerance to compute the intersection. By default, the numerical tolerance is used.
   */
               CATLONG32              GetFirstPointOnSegment(     CATLONG32            & ioIndex       ,
                                                            const double              *  iPoint1       ,
                                                            const double              *  iPoint2       ,
                                                                  double                 iTol          ,
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const; 

  //---------------------------------------------------------------------------
  // Other methods
  //---------------------------------------------------------------------------
  /**
   * Computes the distance between two successive points of <tt>this</tt> CATMathSetOfPointsND.
   * @param ioParameters
   * The array of distance of each successive interval. Must be previously allocated to <tt>NumberOfPoints</tt>.
   */
  virtual      void                   InitializeParameters (      double              *  ioParameters  ) const;

  /**
   * Computes the tangent in each point of <tt>this</tt> CATMathSetOfPointsND.
   * @param iParameters
   * The distance of each successive interval. To be filled by the <tt>InitializeParameters</tt> method.
   * @param ioTangents
   * The array of the tangents. Must be previously allocated to <tt>NumberOfPoints*N</tt>.
   */
  virtual      void                   ComputeTangents      (const double              *  iParameters   ,
                                                                  double              *  ioTangents    ) const;

  /**  
   * Simpifies <tt>this</tt> CATMathSetOfPointsND.
   * This method removes the points of the set when they lie within <tt>iSag</tt>
   * of the chord between the previous and the next point.
   * @param iSag
   * The distance of simplification.
   * @param ioRemovedPoints
   * The CATMathSetOfPointsND containing the removed points. 
   * if </tt> NULL</tt>, this argument is not filled.
   */
  virtual      void                   Simplify             (const double                 iSag          ,
                                                                  CATMathSetOfLongs   *  ioRemovedPoints = 0);


  /** 
   * Removes the duplicated points of <tt>this</tt> CATMathSetOfPointsND.
   *  @param iTol
   * The tolerance of confusion. By default, the numerical tolerance is used.
   * @param iAll
   * <b>Legal values</b>: 
   * <dl><dt>0</dt><dd>The first twin point is kept.
   * <dt>0</dt><dd>All the twin points are removed
   *</dl>
   */
  virtual      void                   RemoveMultiplePoints (const double                 iTol          ,
                                                            const CATBoolean             iAll          = 0);


  /** 
   * Sorts <tt>this</tt> CATMathSetOfPointsND along coordinate index, from the smallest to 
   * the highest coordinate.
   * @param iCoordIndex
   * The index (beginning at 0) of the coordinate for the sort.
   */
  virtual      void                   Sort                 (const CATLONG32              iCoordIndex   );





  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



  // Boolean operation point / planar polygonal contour
  /** @nodoc */
               CATLONG32              PointPosition        (const double              *  iPoint        ,
                                                            const double              *  iTol          ,
                                                                  CATLONG32              iCount        = 0,
                                                                  CATLONG32              iBegin        = 0,
                                                                  CATLONG32              iFirst        = 0,
                                                                  CATLONG32              iSecond       = 1 );

  // Auxiliary results of the PointPosition method
    /** @nodoc */
               CATLONG32              IsPointVertex        (      CATLONG32            & oVertexIdx    ,
                                                                  CATLONG32            & oEdgeIdx      ,
                                                                  double               & oLengthRatio  ,
                                                                  CATLONG32            & oEdgeCount    ,
                                                                  CATLONG32            & oOrientation  ) const;


 protected:
  CATLONG32    _Dim             ,
               _NumberOfPoint   ,
               _Iterator        ,
               _Periodic        ;

  CATLONG32    _MaxNumberOfPoint;
  double    *  _Points          ;
  
  // 2 submethods of ConvexContour
  /** @nodoc */
               void                   TrivialConvex        (const double                 iTol          ,
                                                                  CATMathSetOfPointsND & oConvex       ) const;
  /** @nodoc */
               CATMathSetOfPointsND * CreateConvex         () const;

 public:

   /**
   * @nodoc
   */
  virtual      void                   Stream               (      CATMathStream        & Str           ,
                                                            const char                   iLabelReserved[] = ""  ) const;
   /**
   * @nodoc
   */
  static       void                   UnStream             (      CATMathStream        & Str           ,
                                                                  CATMathSetOfPointsND*& oSetOfPointsND,
                                                            const char                   iLabelReserved[] = ""   );

   /**
   * @nodoc
   */
  virtual      CATBoolean             IsStreamable         (const CATCGMStreamVersion    iTargetVersion,
                                                                  CATBoolean           & ioReversible  ) const;

private:
  // Compute Tangents when _Dim=1 so that the cubic extrapolation is C2 with minimal energy
  virtual      void                   ComputeTangents1D    (const double              *  Parameters    ,
                                                                  double              *  Tangents      ) const;

  // submethod of ConvexContour
               void                   ReduceGranularity    (const double                 iTol          ,
                                                                  CATMathVector2D     *  iBox          ,
                                                                  CATMathSetOfPointsND & oConvex       ) const;

  CATLONG32    _IsVertex;
  CATLONG32    _VertexIdx;
  CATLONG32    _EdgeIdx;
  CATLONG32    _EdgeCount;
  double       _LengthRatio;
  CATLONG32    _Orientation;
};

//-----------------------------------------------------------------------------
// Global Functions and Utilities.
//-----------------------------------------------------------------------------

/**
 * Computes the scalar product of two N dimensional vectors.
 * @param iN
 * The dimension.
 * @param iUOrigin
 * The array of coordinates of the origin of the first vector.
 * @param iUEnd
 * The array of coordinates of the end of the first vector.
 * @param iVOrigin
 * The array of coordinates of the origin of the second vector.
 * @param iVEnd
 * The array of coordinates of the end of the second vector.
 * @return
 * The scalar product <tt>iUEnd-iUOrigin * iVEnd-iVOrigin </tt>
 */
ExportedByYN000FUN
               double                 CATScalarProductND   (const CATLONG32              iN            ,
                                                            const double              *  iUOrigin      ,
                                                            const double              *  iUEnd         ,
                                                            const double              *  iVOrigin      ,
                                                            const double              *  iVEnd         );

//-----------------------------------------------------------------------------
/**
 * Returns the square distance between two N dimensional points.
 * @param iN
 * The dimension.
 * @param iPoint0
 * The array of the coordinates of the first point.
 * @param iPoint1
 * The array of the coordinates of the second point.
 * @return
 * The distance.
 */
ExportedByYN000FUN
               double                 CATSquareDistanceND  (const CATLONG32              iN            ,
                                                            const double              *  iPoint0       ,
                                                            const double              *  iPoint1       );

//-----------------------------------------------------------------------------
/** 
 * Projects a point on a segment in a N dimensional space.
 * @param iN
 * The dimension.
 * @param iPoint
 * The array of the coordinates of the point to project.
 * @param iSegmentStartPoint
 * The array of the coordinates of the first point of the segment.
 * @param iSegmentEndPoint
 * The array of the coordinates of the last point of the segment.
 * @param ioProjectedPoint 
 * The coordinates of the projected point on the line.
 * @param iTolObject 
 * The default tolerance.
 * @return
 * <tt>TRUE</tt> if the projected point belongs to the segment.
*/
ExportedByYN000FUN
               CATBoolean             CATProjectPointOnSegmentND
                                                           (const CATLONG32              iN                ,
                                                            const double              *  iPoint            ,
                                                            const double              *  iSegmentStartPoint,
                                                            const double              *  iSegmentEndPoint  ,
                                                                  double              *  ioProjectedPoint  ,
                                                            const CATTolerance         & iTolObject        = CATGetDefaultTolerance());

#if defined ( CATIACGMV5R21 )
//-----------------------------------------------------------------------------
//                           INLINE 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CATMathSetOfPointsND::Beginning()
{
   _Iterator = 0;
}
//-----------------------------------------------------------------------------
const double * CATMathSetOfPointsND::GetPoints () const
{
   return _Points;
}
//-----------------------------------------------------------------------------
CATLONG32 CATMathSetOfPointsND::IsPeriodic() const
{
   return _Periodic;
}

//-----------------------------------------------------------------------------
CATLONG32 CATMathSetOfPointsND::GetDimension() const
{
   return _Dim;
}

//-----------------------------------------------------------------------------
CATLONG32 CATMathSetOfPointsND::GetNumberOfPoints () const
{
   return _NumberOfPoint;
}
#endif

#endif
