#ifndef CATMathGrid_h
#define CATMathGrid_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MAT.h"
#include "CATMathExtendableSet.h"
#include "CATMathInline.h"

//class CATMathMxNFullMatrix;
class CATMathSetOf3DObjects;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class handling the allocation of grids of CATMathGridOfPoints
 * and CATMathGridOfVectors.
 *<br>The size is defined by a number of rows <tt>NbRows</tt> and a 
 * number of columns <tt>NbColumns</tt> of elements of 3 doubles.
 *<br>The <tt>SetNumberOfElements</tt> method enlarges the memory if
 * needed, while the <tt>Compress</tt> inherited method releases the free 
 * unused memory.
 */
class ExportedByYN000MAT CATMathGrid : public CATMathExtendableSet
{
  friend class CATMathMxNMatrix;
 protected: 
/**
 * Constructs an empty CATMathGrid with 0 row and 0 column.
 */
  CATMathGrid();

/**
 * @nodoc
 * @deprecated V5R20 SetNumberOfGridElements
 * Constructs from the number of lines and rows.
 */
  CATMathGrid(CATLONG32 iNbRows, CATLONG32 iNbColumns);

/**
 * @nodoc
 * @deprecated V5R20 ExtractSubGrid
 * Constructs by extracting a smaller grid from another one.
 */
  CATMathGrid(const CATMathGrid & iSourceGrid,
	                     CATLONG32 iStartRow   , CATLONG32 iEndRow,
	                     CATLONG32 iStartColumn, CATLONG32 iEndColumn);

  /**
  * Extracting a smaller grid from another one.
  */
  HRESULT ExtractSubGrid(const CATMathGrid & iSourceGrid,
	                                          CATLONG32 iStartRow   , CATLONG32 iEndRow,
	                                          CATLONG32 iStartColumn, CATLONG32 iEndColumn);

  /**
  * @nodoc
  * @deprecated V5R20 ConvertFrom3DSet
  * Constructs from a CATMathSetOf3DObjects, assuming it is ordered column 
  * after column.
  */
  CATMathGrid(const CATMathSetOf3DObjects  & iSourceSet,
	                     CATLONG32 iNbRows, 
	                     CATLONG32 iNbColumns );

/**
 * Constructs from a CATMathSetOf3DObjects, assuming it is ordered column 
 * after column.
 */
HRESULT ConvertFrom3DSet(const CATMathSetOf3DObjects  & iSourceSet,
	                                                CATLONG32 iNbRows, 
	                                                CATLONG32 iNbColumns );

/**
 * Copy constructor.
 */
  CATMathGrid(const CATMathGrid &iGridToCopy);

 public:
/**
 * Defines the affectation operator.
 */
  const CATMathGrid & operator = (const CATMathGrid & iGridToCopy); 

/**
 * Destructor.
 */
  virtual ~CATMathGrid();

  //---------------------------------------------------------------------------
  //- Set and get methods.
  //---------------------------------------------------------------------------

/**
 * @nodoc
 * @deprecated V5R20 SetNumberOfGridElements
 * Modifies the dimension of a CATMathGrid.
 *<br>Re-allocates the memory if necessary.
 */
  virtual void SetNumberOfElements(CATLONG32 iNbRows, CATLONG32 iNbColumns);

/**
 * Modifies the dimension of a CATMathGrid.
 *<br>Re-allocates the memory if necessary.
 * @Return E_FAIL if the given data are not positive, S_OK otherwise.
 */
virtual HRESULT SetNumberOfGridElements(CATLONG32 iNbRows, CATLONG32 iNbColumns);

/**
 * Returns the number of rows of a CATMathGrid.
 */
  INLINE CATLONG32 GetNumberOfRows()    const;

/**
 * Returns the number of columns of a CATMathGrid.
 */
  INLINE CATLONG32 GetNumberOfColumns() const;


  //**************************************************************************/
  // The two following methods should disappear :
  // use preferently the two previous (the difference is the 's' at the end).
/**
 * @nodoc
 * @deprecated V5R20 GetNumberOfRows.
 */
  CATLONG32 GetNumberOfRow() const;

/**
 * @nodoc
 * @deprecated V5R20 GetNumberOfColumns
 */
  CATLONG32 GetNumberOfColumn() const;
  //**************************************************************************/


/**
 * @nodoc
 * Dumps a CATMathGrid.
 * <br>This writes the following lines on the ostream if <tt>iLevel = 1</tt>:
 *<pre>
 *   Set(1,1) = ( FirstCoord_11 , SecondCoord_11 , ThirdCoord_11 )
 *   Set(1,2) = ( FirstCoord_12 , SecondCoord_12 , ThirdCoord_12 )
 *   ...
 *   Set(1,n) = ( FirstCoord_1n , SecondCoord_1n , ThirdCoord_1n )
 *   Set(2,1) = ( FirstCoord_21 , SecondCoord_21 , ThirdCoord_21 )
 *   ...
 *   Set(m,n) = ( FirstCoord_mn , SecondCoord_mn , ThirdCoord_mn )</pre>
 * Only outputs the number of rows and columns if <tt>iLevel = 0</tt>.
 * @param iStream  
 * A pointer to the output. If <tt>0L</tt>, the method dumps 
 * on the <tt>cout</tt> output.
 * @param iDebugLevel
 * The debug level.
 * <dl><dt><tt>0</tt><dd> 
 * for writing the number of lines and columns.
 *     <dt><tt>1</tt><dd> 
 * for writing the coordinates of the objects.</dl>
 */
  virtual void Dump(CATLONG32 iDepth=0, ostream * iStream = 0L) const;
  
  //---------------------------------------------------------------------------
  // Methods that moves the elements of a grid
  //---------------------------------------------------------------------------

/**
 * @nodoc
 * @deprecated V5R20 CopyGrid
 * Copies a smaller grid into a subgrid of a larger one.
 * <br>Throws an error if the dimensions between the grids are not consistent.
 */
  void CopyIntoGrid(const CATMathGrid & iSmallerGrid,
		                         CATLONG32 iStartRow, CATLONG32 iColStartColumn);

/**
 * Copies a smaller grid into a subgrid of a larger one.
 * @return E_FAIL  if the dimensions between the grids are not compatible.
 */
  HRESULT CopyGrid(const CATMathGrid & iSmallerGrid,
		                             CATLONG32 iStartRow, CATLONG32 iColStartColumn);

/**
 * Exchanges the rows and columns.
 */
  void TransposeGrid() ;

/**
 * Vertical reverse of the grid.
 *<br> The last column becomes the first one, and so one.
 */
  void ReverseColumnsOfGrid();

/**
 * Horizontal reverse of the grid.
 *<br> The last row becomes the first one, and so one.
 */
  void ReverseRowsOfGrid();

/**
 * @nodoc
 * @deprecated V5R20 ResizeTheGrid
 * Changes the number of rows and columns, without changing the total number of
 * elements.
 *<br> If <tt> NbRows * NbColumns</tt> does not remain constant, an exception
 * is arised.
 * <br>Throws an error if at least one of the given data is negative.
 */
  void ResizeGrid(CATLONG32 iCountRows, CATLONG32 iCountColumns);

  /**
 * Changes the number of rows and columns, without changing the total number of
 * elements.
 *<br> If <tt> NbRows * NbColumns</tt> does not remain constant, an exception
 * is arised.
  * <br>Return E_FAIL if at least one of the given data is negative, S_OK otherwise.
 */
  HRESULT ResizeTheGrid(CATLONG32 iCountRows, CATLONG32 iCountColumns);

 protected:
  //---------------------------------------------------------------------------
  //- Internal data.
  //---------------------------------------------------------------------------
  // Dimensions of the grid.
  CATLONG32 _CountRows, _CountColumns;

  // Size of a row (in double) : should be the number of columns time 3.
  CATLONG32 _SizeRow;
};

//-----------------------------------------------------------------------------
//- INLINE Implementations.
//-----------------------------------------------------------------------------
INLINE CATLONG32 CATMathGrid::GetNumberOfColumns() const
{ return _CountColumns; }

INLINE CATLONG32 CATMathGrid::GetNumberOfRows() const
{ return _CountRows; }

#endif




