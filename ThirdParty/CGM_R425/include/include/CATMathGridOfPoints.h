#ifndef CATMATHGRIDOFPOINTS_H
#define CATMATHGRIDOFPOINTS_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MAT.h"
#include  "CATMathGrid.h"

#include "CATMathPoint.h"


class CATMathSetOfPoints;
class CATMathTransformation;
/**
 * Class representing a bi-dimensionnal grid of CATMathPoints.
 *<br>The size is defined by a number of rows <tt>NbRows</tt> and a 
 * number of columns <tt>NbColumns</tt>. The index of the fisrt 
 * CATMathPoints are <tt>(0,0)</tt>.
 *<br>The <tt>SetNumberOfPoints</tt> method enlarges the memory if
 * needed, while the <tt>Compress</tt> inherited method releases the free 
 * unused memory.
 */
class ExportedByYN000MAT CATMathGridOfPoints : public CATMathGrid
{

 public:

//=============================================================================
//- CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs an empty CATMathGridOfPoints with 0 row and 0 column.
 */
  CATMathGridOfPoints();

/**
 * @nodoc
 * @deprecated V5R20 SetNumberOfGridElements
 * Constructs a CATMathGridOfPoints of a given size.
 *<br>The memory is allocated, but the values of the points are not initialized.
 * Use <tt>SetPoint</tt> to initialize them.
 */
  CATMathGridOfPoints(CATLONG32 iNbRows, CATLONG32 iNbColumns);

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs from an array of CATMathPoints, assuming it is ordered row
 * after row.
 */ 
  CATMathGridOfPoints(CATLONG32 iNbRows, CATLONG32 iNbColumns,
	                                    const CATMathPoint iArrayPoint[]);
/**
 * Copy constructor.
 */
  CATMathGridOfPoints(const CATMathGridOfPoints & iGridToCopy);

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs by extracting a smaller grid from another one.
 */
  CATMathGridOfPoints(const CATMathGridOfPoints & iSourceGrid,
		                                CATLONG32 iStartRow   , CATLONG32 iEndRow,
		      		      		        CATLONG32 iStartColumn, CATLONG32 iEndColumn);

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs from a CATMathSetOfPoints, assuming it is ordered column 
 * after column.
 */
  CATMathGridOfPoints(const CATMathSetOfPoints  & iSourceSet,
		      CATLONG32 iNbRows, 
		      CATLONG32 iNbColumns );
/**
 * Destructor
 */
  virtual ~CATMathGridOfPoints();


//=============================================================================
//- READING AND SETTING METHODS
//=============================================================================

  /**
  * Modifies a CATMAthGridOfPoints from an array of CATMathPoints, assuming it is ordered row
  * after row.
  * @return E_FAIL if the given indexes are inconsistent, S_OK otherwise.
  */ 
  HRESULT Set(CATLONG32 iNbRows, CATLONG32 iNbColumns,
	                       const CATMathPoint iArrayPoint[]);

  /**
  * Modifies a CATMAthGridOfPoints by extracting a smaller grid from another one.
  * @return E_FAIL if the given indexes are inconsistent, S_OK otherwise.
  */

  HRESULT Set(const CATMathGridOfPoints & iSourceGrid,
	                       CATLONG32 iStartRow   , CATLONG32 iEndRow,
	                       CATLONG32 iStartColumn, CATLONG32 iEndColumn);

  /**
  * Modifies a CATMAthGridOfPoints from a CATMathSetOfPoints, assuming it is ordered column 
  * after column.
  * @return E_FAIL if the given indexes are inconsistent, S_OK otherwise.
  */
 HRESULT Set(const CATMathSetOfPoints  & iSourceSet,
		                 CATLONG32 iNbRows, 
		                 CATLONG32 iNbColumns);


/**
 * @nodoc
 * @deprecated V5R20 GetOnePoint
 * Returns the CATMathPoint locating at a given row and column.
 *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 *<br>Use preferently the second method signature if you want to avoid an
 * useless constructor.
 */
  CATMathPoint  GetPoint(CATLONG32  iRow, CATLONG32 iColumn) const;

/**
 * @nodoc
 * @deprecated V5R20 GetOnePoint
 * Retrieves the CATMathPoint locating at a given row and column.
 *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 */
  void GetPoint(CATLONG32  iRow, CATLONG32 iColumn, CATMathPoint &ioPoint) const;


/**  
 * Retrieves the CATMathPoint locating at a given row and column.
 * <br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 * @return E_FAIL if the given indexes are inconsistent, S_OK otherwise.
 */
  HRESULT GetOnePoint(CATLONG32  iRow, CATLONG32 iColumn, CATMathPoint &ioPoint) const;


/**
 * Returns the array of CATMathPoints sorted row by row.
 *<br>A CATMathPoint at the <tt>(iRow,iColumn)</tt> location is accessed
 * using the formula  <tt>iRow*NbRows+iColumn</tt> in the returned array.
 *<br>Note that the returned array is used by the CATMathGridOfPoints and
 * must not be deleted.
 */
  CATMathPoint * GetPoints() const;

/**
 * @nodoc
 * @deprecated V5R20 SetOnePoint
 * Initializes the values of a CATMathPoint in <tt>this</tt> CATMathGridOfPoints.
 *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 */
  void SetPoint(const CATMathPoint & iPoint, CATLONG32  iRow, CATLONG32 iColumn);


  /*
  * Initializes the values of a CATMathPoint in <tt>this</tt> CATMathGridOfPoints.
 *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 *@return E_FAIL if the given indexes are inconsistent, S_OK otherwise.
  */
 HRESULT SetOnePoint(const CATMathPoint & iPoint, CATLONG32  iRow, CATLONG32 iColumn);


/**
 * Transforms the CATMathPoints of <tt>this</tt> CATMathGridOfPoints.
 */
  virtual void ApplyTransformation(const CATMathTransformation &iTransfo);

/** 
  * Returns the distance between a CATMathPoint and 
  * a point of <tt>this</tt> CATMathGridOfPoints.
  * @param iP
  * The point to which the distance is computed.
  * @param iRow
  * The row (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iColumn
  * The column (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  */
  double DistanceTo (const CATMathPoint & iP, CATLONG32 & iRow, CATLONG32 & iColumn) const ;

/** 
  *  Returns the square distance between a CATMathPoint and 
  * a point of <tt>this</tt> CATMathGridOfPoints.
  * @param iP
  * The point to which the distance is computed.
  * @param iRow
  * The row (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iColumn
  * The column (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  */
  double SquareDistanceTo (const CATMathPoint & iP, CATLONG32 & iRow,
                                               CATLONG32 & iColumn) const ;

/** 
  *  Returns the distance between a point of a CATMathSetOfPoints and 
  * a point of <tt>this</tt> CATMathGridOfPoints.
  * @param iSetOfPoints2
  * The set of points which the second point belongs to.
  * @param iRow1
  * The row (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iColumn1
  * The column (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iIndex2
  * The index (beginning at <tt>0</tt>) of the second point in its set to which
  * the distance is computed.
  */
  double DistanceTo(const CATMathSetOfPoints * iSetOfPoints2,
                                  CATLONG32 & iRow1, CATLONG32 & iColumn1, CATLONG32 & iIndex2) const;
/** 
  *  Returns the square distance between a point of a CATMathSetOfPoints and 
  * a point of <tt>this</tt> CATMathGridOfPoints.
   * @param iSetOfPoints2
  * The set of points which the second point belongs to.
  * @param iRow1
  * The row (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iColumn1
  * The column (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iIndex2
  * The index (beginning at <tt>0</tt>) of the second point in its set to which
  * the distance is computed.
  */
  double SquareDistanceTo(const CATMathSetOfPoints * iSetOfPointst2,
                                              CATLONG32 & iRow1, CATLONG32 & iColumn1, CATLONG32 & iIndex2) const;
//
//- Distance and SquareDistance between two grid of points
//
/** 
  *  Returns the distance between  
  * a point of <tt>this</tt> CATMathGridOfPoints and
  * a point of another CATMathGridOfPoints.
  * @param iGridOfPoints2
  * The other grid of points which the second point belongs to.
  * @param iRow1
  * The row (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iColumn1
  * The column (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
 * @param iRow2
  * The row (beginning at <tt>0</tt>) of the point of the second grid of points
  * to which the distance is computed.
  * @param iColumn2
  * The column (beginning at <tt>0</tt>) of the point of the second grid of points
  * to which the distance is computed.
  */
  double DistanceTo(const CATMathGridOfPoints * iGridOfPoints2,
                                  CATLONG32 & iRow1, CATLONG32 & iColumn1, CATLONG32 & iRow2, CATLONG32 & Column2) const;

/** 
  *  Returns the square distance between  
  * a point of <tt>this</tt> CATMathGridOfPoints and
  * a point of another CATMathGridOfPoints.
  * @param iGridOfPoints2
  * The other grid of points which the second point belongs to.
  * @param iRow1
  * The row (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
  * @param iColumn1
  * The column (beginning at <tt>0</tt>) of the point of <tt>this</tt>
  * to which the distance is computed.
 * @param iRow2
  * The row (beginning at <tt>0</tt>) of the point of the second grid of points
  * to which the distance is computed.
  * @param iColumn2
  * The column (beginning at <tt>0</tt>) of the point of the second grid of points
  * to which the distance is computed.
  */
  double SquareDistanceTo(const CATMathGridOfPoints * iGridOfPoints2,
                                              CATLONG32 & iRow1, CATLONG32 & iColumn1, 
                                              CATLONG32 & iRow2, CATLONG32 & iColumn2) const;


/**
 * @nodoc
 * @deprecated V5R20 GetOnePoint
 */
  CATMathPoint  GetPoint(CATLONG32 n) const;

/**
 * @nodoc
 * @deprecated V5R20 SetOnePoint
 */
  void SetPoint(const CATMathPoint & P, CATLONG32 n);

/**
 * @nodoc
 * @deprecated V5R20 SetOnePoint
 */
  void SetPoint(double iX, double  iY, double iZ, 
                CATLONG32 iRow, CATLONG32 iColumn);
/**
 * @nodoc
 * @deprecated V5R20 SetOnePoint
 */
  void SetPoint(double iX, double iY, double iZ, CATLONG32 n);

/**
 * @nodoc
 * @deprecated V5R20.
 */
  CATLONG32 GetNumberOfPoints() const;


};

#include "CATMathAbstractGridOfPoints.h"
#endif
