#ifndef CATMATHGRIDOFVECTORS_H
#define CATMATHGRIDOFVECTORS_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MAT.h"
#include "CATMathGrid.h"

#include "CATMathVector.h"
#include "CATMathInline.h"


class CATMathTransformation;

/**
 * Class representing a bi-dimensionnal grid of CATMathVectors.
 *<br>The size is defined by a number of rows <tt>NbRows</tt> and a 
 * number of columns <tt>NbColumns</tt>.
 *<br>The <tt>SetNumberOfVectors</tt> method enlarges the memory if
 * needed, while the <tt>Compress</tt> inherited method releases the free 
 * unused memory.
 */
class ExportedByYN000MAT CATMathGridOfVectors : public CATMathGrid
{

 public:

//=============================================================================
//- CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs an empty CATMathGridOfVectors with 0 row and 0 column.
 */
  CATMathGridOfVectors();

/**
 * @nodoc
 * @deprecated V5R20 SetVectorNumber
 * Constructs a CATMathGridOfVectors of a given size.
 *<br>The memory is allocated, but the values of the vectors are not initialized.
 * Use <tt>SetVector</tt> to initialize them.
 */
  CATMathGridOfVectors(CATLONG32 iNbRows, CATLONG32 iNbColumns);

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs from an array of CATMathVectors, assuming it is ordered row
 * after row.
 */ 
  CATMathGridOfVectors(CATLONG32 iNbRows, CATLONG32 iNbColumns,
	                                      const CATMathVector iArrayVector[]);

/**
 * Copy constructor.
 */
  CATMathGridOfVectors(const CATMathGridOfVectors & iGridToCopy);

/**
 * Destructor
 */
  virtual ~CATMathGridOfVectors();

//=============================================================================
//- READING AND SETTING METHODS
//=============================================================================

  /**
 * Modifies the set from an array of CATMathVectors, assuming it is ordered row
 * after row.
 * @return E_FAIL if the given indexes are inconsistent, S_OK otherwise.
 */ 
  HRESULT Set(CATLONG32 iNbRows, CATLONG32 iNbColumns,
	                       const CATMathVector iArrayVector[]);

 /**
 * @nodoc
 * @deprecated V5R20 SetVectorNumber
 * Sets a new size to <tt>this</tt> CATMathGridOfVectors.
 */
  void SetNumberOfVectors(CATLONG32 iCountRows, CATLONG32 iCountColumns); 

  /**
  * Sets a new size to <tt>this</tt> CATMathGridOfVectors.
  * @return E_FAIL if the given indexes are not positive, S_OK otherwise.
  */
  HRESULT SetVectorNumber(CATLONG32 iCountRows, CATLONG32 iCountColumns); 

  /**
  * @nodoc
  * @deprecated V5R20 GetOneVector
  * Returns the CATMathVector locating at a given row and column.
  *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
  *<br>Use preferently the second method signature if you want to avoid an
  * useless constructor.
  */
  CATMathVector  GetVector(CATLONG32  iRow, CATLONG32 iColumn) const;

/**
 * @nodoc
 * @deprecated V5R20 GetOneVector
 * Retrieves the CATMathVector locating at a given row and column.
 * <br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 */
  void GetVector(CATLONG32  iRow, CATLONG32 iColumn, CATMathVector &ioVector) const;

  /**
 * Retrieves the CATMathVector locating at a given row and column.
 * <br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 * @return E_FAIL if the given indexes are uncompatible, S_OK otherwise.
 */
   HRESULT GetOneVector(CATLONG32  iRow, CATLONG32 iColumn, CATMathVector &ioVector) const;
 
  /**
 * Returns the array of CATMathVectors sorted row by row.
 *<br>A CATMathVector at the <tt>(iRow,iColumn)</tt> location is accessed
 * using the formula  <tt>iRow*NbRows+iColumn</tt> in the returned array.
 *<br>Note that the returned array is used by the CATMathGridOfVectors and
 * must not be deleted.
 */
  CATMathVector * GetVectors() const;

  /**
  * @nodoc
  * @deprecated V5R20 SetOneVector
  * Initializes the values of a CATMathVector in the CATMathGridOfVectors.
  *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
  */
  void SetVector(const CATMathVector & iVector, CATLONG32  iRow, CATLONG32 iColumn);
 
  /**
 * Initializes the values of a CATMathVector in the CATMathGridOfVectors.
 *<br>The indexes <tt>iRow</tt> and <tt>iColumn</tt> start at <tt>0</tt>.
 * @return E_FAIL if the given indexes are uncompatible, S_OK otherwise.
 */
HRESULT SetOneVector(const CATMathVector & iVector, CATLONG32  iRow, CATLONG32 iColumn);

/**
 * Transforms the CATMathVectors of a CATMathGridOfVectors.
 */
  virtual void ApplyTransformation(const CATMathTransformation &iTransfo);


/**
 * @nodoc
 * @deprecated V5R20 GetOneVector
 */
  CATMathVector  GetVector(CATLONG32 n) const;

/**
 * @nodoc
 * @deprecated V5R20 SetOneVector
 */
  void SetVector(const CATMathVector & P, CATLONG32 n);

/**
 * @nodoc
 * @deprecated V5R20 SetOneVector
 */
  void SetVector(double iX, double  iY, double iZ, 
                CATLONG32 iRow, CATLONG32 iColumn);

/**
 * @nodoc
 * @deprecated V5R20 SetOneVector
 */
  void SetVector(double iX, double iY, double iZ, CATLONG32 n);

/**
 * @nodoc
 * @deprecated V5R20.
 */
  CATLONG32 GetNumberOfVectors() const;
};

INLINE HRESULT CATMathGridOfVectors::SetVectorNumber(CATLONG32 CountRows, CATLONG32 CountColumns)
{
	 HRESULT IsOK = SetNumberOfGridElements(CountRows, CountColumns);
	return IsOK;
}



#include "CATMathAbstractGridOfVectors.h"
#endif
