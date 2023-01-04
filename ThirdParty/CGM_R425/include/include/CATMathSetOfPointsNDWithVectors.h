#ifndef CATMathSetOfPointsNDWithVectors_H
#define CATMathSetOfPointsNDWithVectors_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathSetOfPointsNDTwoTangents.h"
#include "CATMathDef.h"
#include "CATTolerance.h"
#include "CATIACGMLevel.h"

class CATMathSetOfLongs;
/**
 * Class defining a set of points in <tt>R^n</tt> with associated vectors.
 */
class ExportedByYN000FUN CATMathSetOfPointsNDWithVectors :
public CATMathSetOfPointsNDTwoTangents
{
 public:
  //---------------------------------------------------------------------------
  // Object Management.
  //---------------------------------------------------------------------------
      /** 
        * Constructs a CATMathSetOfPointsNDTwoTangents.
        * <br>The tangents are initialized by the null vector.
        * @param iN
        * The dimension of the space.
        * @param iNumberOfPoint
        * The size of the set.
        */
                                 CATMathSetOfPointsNDWithVectors
                                                      (const CATLONG32              iN            ,
                                                       const CATLONG32              iNumberOfPoint);

  
        /**
        * Copy constructor.
        */
                                 CATMathSetOfPointsNDWithVectors(
                                                       const CATMathSetOfPointsNDWithVectors & iToCopy);


                                ~CATMathSetOfPointsNDWithVectors();

        /**
        * Assignment operator.
        */
         CATMathSetOfPointsNDWithVectors & operator = (const CATMathSetOfPointsNDWithVectors & iS);

  //---------------------------------------------------------------------------
  // Information methods.
  //---------------------------------------------------------------------------
 /**
 * Returns the class name .
 * @return
 * CATMathSetOfPointsNDWithVectors.
 */
                CATMathClassId         IsA()                                                              const;

 /**
 * Tests the class of <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathSetOfPointsNDTWithVectors 
 * is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
 */
                CATBoolean             IsAKindOf            (const CATMathClassId         iClassId      ) const;

  //---------------------------------------------------------------------------
  // Edition methods.
  //---------------------------------------------------------------------------
  /**
  * Packs <tt>this</tt> CATMathSetOfPointsWithVectors.
  *<br> In this case, <tt>_MaxNumberOfPoint = _NumberOfPoint</tt>.
  */
                void                   Pack                 ();

 /**
 * Removes one point of <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * <br> The points after the removed point are shift, but the memory is not deleted 
 * (<tt>_MaxNumberOfPoint</tt> still remains the same).
 * @param iIndexToRemove
 * The index of the point to remove <tt> 0<= iIndexToRemove < NumberOfPoints </tt>.
 */
                void                   RemovePoint          (const CATLONG32              iIndexToRemove);
 
 /**
 * Removes points of <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * <br> The remaining points are shift, but the memory is not deleted 
 * (<tt>_MaxNumberOfPoint</tt> still remains the same).
 * @param iPointsIndex
 * The list of the indexes of the points to remove.
 */
                void                   RemovePoints         (const CATMathSetOfLongs    & iPointsIndex  );

 /**
 * Resets <tt>this</tt> CATMathSetOfPointsTwoTangents (the points, the vectors and tangents).
 * <br> The memory is not deleted and the class can be used again.
 */
                void                   Reset                ();

 /**
  * Appends a  point at the end of the set.
  * If needed, <tt>this</tt> CATMathSetOfPointsNDWithVectors is reallocated.
  * @param iPoint
  * The array of the coordinates.
  */
                void                   AddPoint             (const double              *  iPoint        );

 /**
  * Inserts a  point at a specific position.
  * If needed, <tt>this</tt> CATMathSetOfPointsNDWithVectors is reallocated.
  * @param iPoint
  * The array of the new coordinates.
  * @param iPointIndex 
  * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
  */
                void                   InsertPoint          (const double              *  iPoint        ,
                                                             const CATLONG32              iPointIndex   );

 /**
 * Sets the periodicity of <tt>this</tt >  CATMathSetOfPointsNDWithVectors.
 * @param iPeriodic
 * <br><b>Legal values </b>:
 * <dl><dt>1</dt><dd> Sets to periodic: in this case, the first and the last points must be the same.
 * <dt>0</dt><dd> unsets the periodicity.
 * </dl>
 */
                void                   SetPeriodic          (const CATBoolean             iPeriodic     = 1);

 /**
 * Inverts the content of <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * @param ioResultingSet
 * The result of the inversion (must be previously allocated). The tangents and the vectors are also inverted.
 */
                void                   Invert          (CATMathSetOfPointsNDWithVectors & iResultingSet ) const;

 /**
 * Inverts the content of <tt>this</tt> CATMathSetOfPointsNDWithVectors inside itself.
 * <br>The tangents and the vectors are also inverted.
 */
                void                   AutoInvert           ();

 /**
 * Swaps two points inside <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * @param iPointIndex1
 * The index of the first point to swap.
 * @param iPointIndex2
 * The index of the second point to swap.
 */
                void                   SwapPoints           (const CATLONG32              iPointIndex1  ,
                                                             const CATLONG32              iPointIndex2  );

 
/**
 * Concatenates a CATMathSetOfPointsNDWithVectors just after the last point 
 * of <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * If needed, <tt>this</tt> CATMathSetOfPointsNDWithVectors is reallocated.
 * @param iSetToConcatenate
 * The set to concatenate.
 * @param iMerge
 * The way to concatenate.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the last point of <tt>this</tt> CATMathSetOfPointsNDWithVectors. 
 * and the first point of <tt>iSetToConcatenate</tt> must be merged, <tt>FALSE</tt> otherwise.
 */
                void                   AddSet               (const CATMathSetOfPointsNDWithVectors & iSetToConcatenate,
                                                                   CATBoolean             iMerge        );

  
/**
 * Splits a CATMathSetOfPointsNDWithVectors just after the point corresponding to the iIndex. 
 * The part of <tt>this</tt> CATMathSetOfPointsNDWithVectors before iIndex will stay in 
 * <tt>this</tt> CATMathSetOfPointsNDWithVectors, and the part after will go in  ioSetbis.
 * If needed, ioSetbis is reallocated,and <tt>this</tt> CATMathSetOfPointsNDWithVectors is disallocated.
 * @param iIndex
 * The index of the point where to split(0<=iIndex<NumberOfPoints). 
 * @param iSetbis
 * The new set after the split(must be previously allocated).
 * @param iMerge
 * The way to split.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the last point of new <tt>this</tt> CATMathSetOfPointsNDWithVectors. 
 * and the first point of <tt>iSetbis</tt> will be the same equal to iIndex point, <tt>FALSE</tt> if the last .
 * point of new <tt>this</tt> CATMathSetOfPointsNDWithVectors will be equal to iIndex point and the first point.
 * of <tt>iSetbis</tt> will be the iIndex+1  point.
 * @param iTolObject
 * The default tolerance.
 */
                void                   Split                (const CATLONG32              iIndex        ,
                                                        CATMathSetOfPointsNDWithVectors & ioSetbis      ,
                                                                   CATBoolean             iMerge        ,
                                                             const CATTolerance         & iTolObject    = CATGetDefaultTolerance());

/**
 * Returns the coordinates of the vector associated with the current point.
 * @return
 * A pointer to the vectors.
 */
          const double               * GetVectors           () const;

 /**
 * Retrieves the coordinates of the vector associated with the current point.
 * @param oVector
 * A pointer to the the coordinates . 
 */
                void                   GetVector            (      double              *  oVector       ) const;

 
        /**
 * Retrieves the vector associated with a specific point of <tt>this</tt> CATMathSetOfPointsNDWithVector.
 * @param iPointIndex 
 * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
 * @param oVector
 * A pointer to the coordinates. 
 */
                void                   GetVector            (const CATLONG32              iPointIndex   ,
                                                                   double              *  oVector       ) const;

 /**
 * Retrieves the coordinates of a specific point and its associated vector .
 * @param iPointIndex 
 * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>).
 * @param oPoint
 * A pointer to the coordinates of the point. 
 * @param oVector
 * A pointer to the coordinates of the vector. 
 */
                void                   GetPointWithVector   (const CATLONG32              iPointIndex   ,
                                                                   double              *  oPoint        ,
                                                                   double              *  oVector       ) const;


 /**
 * Replaces the coordinates of vector associated with the current point.
 * @param iVector
 * The array of the new coordinates. 
 */
                void                   ReplaceVector        (const double              *  iVector       );

 /**
 * Replaces the coordinates of the vector associated with a specific point.
 * @param iPointIndex 
 * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
 * @param iVector
 * The array of the new coordinates. 
 */
                void                   ReplaceVector        (const CATLONG32              iPointIndex   ,
                                                             const double              *  iVector       );

 /**
 * Appends a  point and its associated vector at the end of the set.
 * If needed, <tt>this</tt> CATMathSetOfPointsNDWithVectors is reallocated.
 * @param iPoint
 * The array of the coordinates of the point.
 * @param iVector
 * The array of the coordinates of the vector.
 */
                void                   AddPointWithVector   (const double              *  iPoint        ,
                                                             const double              *  iVector       );

 /**
 * Appends a  point and its associated vector at the end of the set, if the point is different from the last one.
 * If needed, <tt>this</tt> CATMathSetOfPointsNDWithVectors is reallocated.
 * @param iPoint
 * The array of the coordinates of the point.
 * @param iVector
 * The array of the coordinates of the vector.
 * @param iTol
 * The tolerance of confusion. If 0, the numerical tolerance is used.
 */
                CATLONG32              AddNewPointWithVector(const double              *  iPoint        ,
                                                             const double              *  iVector       ,
                                                             const double                 iTol          );

/**
 * Inserts a  point and its associated vector at a specific position.
 * If needed, <tt>this</tt> CATMathSetOfPointsNDWithVectors is reallocated.
 * @param iPoint
 * The array of the new coordinates.
 * @param iVector
 * The array of the coordinates of the vector.
 * @param iPointIndex 
 * The index of the point (<tt>0<= iPointIndex < NumberOfPoints</tt>). 
 */
                void                   InsertPointWithVector(const double              *  iPoint        ,
                                                             const double              *  iVector       ,
                                                             const CATLONG32              iPointIndex   );
/**
 * Returns the last tangent of <tt>this</tt > CATMathSetOfPointsNDWithVectors.
 * @return
 * The array [N] of coordinates. Must be previously allocated.
 */
          const double               * GetLastTangent      () const;

/**
 * Modifies the last tangent of <tt>this</tt > CATMathSetOfPointsNDWithVectors.
 * @param iB
 * The array [N] of coordinates. 
 */
                void                   SetLastTangent      (const double               *  iB            );

  //---------------------------------------------------------------------------
  // Analysis methods
  //---------------------------------------------------------------------------
  
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
 * @return
 * The result diagnosis.
 * <tt>1</tt> if a line has been found, <tt>0</tt> otherwise.
 */
               CATLONG32              IsLinear             (const CATLONG32              iNumCoord     ,
                                                            const CATLONG32           *  iCoordIndex   ,
//                                                          const double                 iTol          = 0., // ????
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

  //---------------------------------------------------------------------------
  // Other methods.
  //---------------------------------------------------------------------------
  /**
 * Computes the distance between two successive points of <tt>this</tt> CATMathSetOfPointsNDWithVectors.
 * @param ioParameters
 * The array of distance of each successive interval. Must be previously allocated to <tt>NumberOfPoints-1</tt>.
 */
               void                   InitializeParameters (      double              *  ioParameters  ) const;

};

#endif
