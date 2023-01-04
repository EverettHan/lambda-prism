#ifndef CATMathSetOfPointsNDTwoTangents_H
#define CATMathSetOfPointsNDTwoTangents_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathSetOfPointsND.h"
#include "CATMathDef.h"

class CATMathSetOfLongs;
class CATMathStream;

/**
 * Class defining a set of points in <tt>R^n</tt> with two extremal tangents.
 */
class ExportedByYN000FUN CATMathSetOfPointsNDTwoTangents : public CATMathSetOfPointsND
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
   * Constructs a CATMathSetOfPointsNDTwoTangents.
   * @param iN
   * The dimension of the space.
   * @param iNumberOfPoint
   * The size of the set.
   * @param iTangent0
   * The array [N] of the coordinates of the first tangente.
   * @param iTangent1
   * The array [N] of the coordinates of the second tangente.
   */
                                 CATMathSetOfPointsNDTwoTangents
                                                      (const CATLONG32              iN            ,
                                                       const CATLONG32              iNumberOfPoint,
                                                       const double              *  iTangent0     ,
                                                       const double              *  iTangent1     );

  /** 
   * Constructs a CATMathSetOfPointsNDTwoTangents.
   * @param iN
   * The dimension of the space.
   * @param iNumberOfPoint
   * The size of the set.
   * @param iTangent
   * The array [2*N] of the coordinates of the two tangents, one after the other.
   */
                                 CATMathSetOfPointsNDTwoTangents
                                                      (const CATLONG32              iN            ,
                                                       const CATLONG32              iNumberOfPoint,
                                                       const double              *  iTangent      );


  /** 
   * Constructs a CATMathSetOfPointsNDTwoTangents.
   * <br>The tangents are initialized by the null vector.
   * @param iN
   * The dimension of the space.
   * @param iNumberOfPoint
   * The size of the set.
   */
                                 CATMathSetOfPointsNDTwoTangents
                                                      (const CATLONG32              iN            ,
                                                       const CATLONG32              iNumberOfPoint);

  /**
   * Copy constructor.
   */
                                 CATMathSetOfPointsNDTwoTangents
                                                      (const CATMathSetOfPointsNDTwoTangents & iToCopy);

  /**
   *  Destructor.
   */
  virtual                       ~CATMathSetOfPointsNDTwoTangents();

  /**
   * Assignment operator.
   */
         CATMathSetOfPointsNDTwoTangents & operator = (const CATMathSetOfPointsNDTwoTangents & iS);
  
  //---------------------------------------------------------------------------
  // Information methods.
  //---------------------------------------------------------------------------
/**
 * Returns the class name .
 * @return
 * CATMathSetOfPointsNDTwoTangents.
 */
                CATMathClassId         IsA()                                                              const;

  /**
 * Tests the class of <tt>this</tt> CATMathSetOfPointsNDTwoTangents.
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathSetOfPointsNDTwoTangents is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
*/
                CATBoolean             IsAKindOf            (const CATMathClassId         iClassId      ) const;

  //---------------------------------------------------------------------------
  // Edition methods.
  //---------------------------------------------------------------------------
 /**
 * Sets the periodicity of <tt>this</tt >  CATMathSetOfPointsNDTwoTangents.
 * @param iPeriodic
 * <br><b>Legal values </b>:
 * <dl><dt>1</dt><dd> Sets to periodic: in this case, the first and the last points must be the same.
 * <dt>0</dt><dd> unsets the periodicity.
 * </dl>
 */
                void                   SetPeriodic          (const CATBoolean             iPeriodic     = 1);

 /**
 * Resets <tt>this</tt> CATMathSetOfPointsTwoTangents (the points and the tangents).
 * <br> The memory is not deleted and the class can be used again.
 */
  virtual       void                   Reset                ();
 /**
 * Removes one point of <tt>this</tt> CATMathSetOfPointsNDTwoTangents.
 * <br> The points after the removed point are shift, but the memory is not deleted 
 * (<tt>_MaxNumberOfPoint</tt> still remains the same).
 * @param iIndexToRemove
 * The index of the point to remove <tt> 0<= iIndexToRemove < NumberOfPoints </tt>.
 */
                void                   RemovePoint          (const CATLONG32              iIndexToRemove);
 
 /**
 * Removes points of <tt>this</tt> CATMathSetOfPointsNDTwoTangents.
 * <br> The remaining points are shift, but the memory is not deleted 
 * (<tt>_MaxNumberOfPoint</tt> still remains the same).
 * @param iPointsIndex
 * The list of the indexes of the points to remove.
 */
                void                   RemovePoints         (const CATMathSetOfLongs    & iPointsIndex  );

  /**
 * Inverts the content of <tt>this</tt> CATMathSetOfPointsNDTwoTangents.
 * @param ioResultingSet
 * The result of the inversion (must be previously allocated). The tangents are also inverted.
 */
                void                   Invert          (CATMathSetOfPointsNDTwoTangents & ioResultingSet) const;

 /**
 * Inverts the content of <tt>this</tt> CATMathSetOfPointsNDTwoTangents inside itself.
 * <br>The tangents are also inverted.
 */
                void                   AutoInvert           () ;

 
    /**
 * Splits a CATMathSetOfPointsNDTwoTangents just after the point corresponding to the iIndex. 
 * The part of <tt>this</tt> CATMathSetOfPointsNDTwoTangents before iIndex will stay in 
 * <tt>this</tt> CATMathSetOfPointsNDTwoTangents, and the part after will go in  ioSetbis.
 * If needed, ioSetbis is reallocated,and <tt>this</tt> CATMathSetOfPointsNDTwoTangents is disallocated.
 * @param iIndex
 * The index of the point where to split(0<=iIndex<NumberOfPoints). 
 * @param iSetbis
 * The new set after the split(must be previously allocated).
 * @param iMerge
 * The way to split.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the last point of new <tt>this</tt> CATMathSetOfPointsNDTwoTangents. 
 * and the first point of <tt>iSetbis</tt> will be the same equal to iIndex point, <tt>FALSE</tt> if the last .
 * point of new <tt>this</tt> CATMathSetOfPointsNDTwoTangents will be equal to iIndex point and the first point.
 * of <tt>iSetbis</tt> will be the iIndex+1  point.
 * @param iTolObject
 * The default tolerance.
  */
  virtual       void                   Split                (const CATLONG32              iIndex        ,
                                                        CATMathSetOfPointsNDTwoTangents & ioSetbis      ,
                                                                   CATBoolean             iMerge        ,
                                                             const CATTolerance         & iTolObject    = CATGetDefaultTolerance());

/**
 * Concatenates a CATMathSetOfPointsNDTwoTangents just after the last point of <tt>this</tt> CATMathSetOfPointsNDTwoTangents.
 * If needed, <tt>this</tt> CATMathSetOfPointsNDTwoTangents is reallocated.
 * @param iSetToConcatenate
 * The set to concatenate.
 * @param iMerge
 * The way to concatenate.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the last point of <tt>this</tt> CATMathSetOfPointsNDTwoTangents. 
 * and the first point of <tt>iSetToConcatenate</tt> must be merged, <tt>FALSE</tt> otherwise.
 */
                void                   AddSet    (const CATMathSetOfPointsNDTwoTangents & iSetToConcatenate,
                                                                   CATBoolean             iMerge        );

  /**
   * Returns the first tangent of <tt>this</tt > CATMathSetOfPointsNDTwoTangents.
   * @return
   * The array [N] of coordinates. Must be previously allocated.
   */
          const double               * GetFirstTangent      ()                                            const;

   /**
   * Returns the last tangent of <tt>this</tt > CATMathSetOfPointsNDTwoTangents.
   * @return
   * The array [N] of coordinates. Must be previously allocated.
   */
  virtual const double               * GetLastTangent       ()                                            const;

  /**
   * Modifies the first tangent of <tt>this</tt > CATMathSetOfPointsNDTwoTangents.
   * @param iA
   * The array [N] of coordinates. 
   */
                void                   SetFirstTangent      (const double              *  iA            );

   /**
   * Modifies the last tangent of <tt>this</tt > CATMathSetOfPointsNDTwoTangents.
   * @param iB
   * The array [N] of coordinates. 
   */
  virtual       void                   SetLastTangent       (const double              *  iB            );

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
   * @param iTolObject
   * The default tolerance.
   * @return
   * The result diagnosis.
   * <tt>1</tt> if a line has been found, <tt>0</tt> otherwise.
   */
  virtual      CATLONG32              IsLinear             (const CATLONG32              iNumCoord     ,
                                                            const CATLONG32           *  iCoordIndex   ,
//                                                          const double                 iTol          = 0., // ????
                                                            const CATTolerance         & iTolObject    = CATGetDefaultTolerance()) const;

  //---------------------------------------------------------------------------
  // Other methods
  //---------------------------------------------------------------------------
   /**
   * Computes the tangent in each point of <tt>this</tt> CATMathSetOfPointsND.
   * @param iParameters
   * The distance of each successive interval. To be filled by the 
   * <tt>CATMathSetOfPointsND::InitializeParameters</tt> method.
   * @param ioTangents
   * The array of the tangents. Must be previously allocated to <tt>NumberOfPoints</tt>.
   */
               void                   ComputeTangents      (const double              *  iParameters   ,
                                                                  double              *  ioTangents    ) const;



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

protected:
  double     * _Vectors;


public:
                                 CATMathSetOfPointsNDTwoTangents
                                                      (const CATLONG32              iN            ,
                                                       const CATLONG32              iNumberOfPoint,
                                                       const CATLONG32              iNumberOfTangent);

  /**
   * @nodoc
   */
  virtual      void                   Stream               (      CATMathStream        & Str           ,
                                                            const char                   iLabelReserved[] = ""  ) const;
   /**
   * @nodoc
   */   
  static       void                   UnStream             (      CATMathStream        & Str           ,
                                                       CATMathSetOfPointsNDTwoTangents*& oSetOfPointsND,
                                                            const char                   iLabelReserved[] = ""   );


   /**
   * @nodoc
   */   
  virtual      CATBoolean             IsStreamable         (const CATCGMStreamVersion    iTargetVersion,
                                                                  CATBoolean           & ioReversible  ) const;
};

#endif
