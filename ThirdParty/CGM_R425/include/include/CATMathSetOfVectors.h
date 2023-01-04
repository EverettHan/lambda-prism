#ifndef CATMathSetOfVectors_h
#define CATMathSetOfVectors_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathVector.h"
#include "CATMathSetOf3DObjects.h"
#include "CATMathInline.h"
#include "IUnknown.h"



/**
 * Class representing a set of CATMathVectors.
 *<br>The size is defined by a number of CATMathVectors
 *<tt>NbVectors</tt>. The index of the first CATMathVector is <tt>0</tt>.
 *<br>The <tt>SetNumberOfVectors</tt> method enlarges the memory if
 * needed, while the <tt>Compress</tt> inherited method releases the free 
 * unused memory.
 */
class ExportedByYN000MAT CATMathSetOfVectors 
: public CATMathSetOf3DObjects
{
 public:
  //---------------------------------------------------------------------------
  //- Object Management.
  //---------------------------------------------------------------------------
/**
 * Constructs an empty CATMathSetOfVectors with 0 vectors.
 */
  CATMathSetOfVectors();

/**
 * @nodoc
 * @deprecated V5R20 SetVectorNumber
 * Constructs a CATMathSetOfVectors of a given size.
 * <br>The memory is allocated, but the values of the vectors are not initialized.
 * Use <tt>SetVector</tt> to initialize them.
 */
  CATMathSetOfVectors(CATLONG32 iNbVectors);

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs from an array of CATMathVectors.
 */ 
  CATMathSetOfVectors(CATLONG32 iNbVectors, const CATMathVector VectorsToCopy[]);

/**
 * CopyConstructor.
 */
  CATMathSetOfVectors(const CATMathSetOfVectors & iCopiedSet);

/**
 * Destructor.
 */
  ~CATMathSetOfVectors();

  //---------------------------------------------------------------------------
  //- Setting and getting the vectors.
  //---------------------------------------------------------------------------
  /**
  * Constructs from an array of CATMathVectors.
  */ 
  HRESULT Set(CATLONG32 iNbVectors, const CATMathVector VectorsToCopy[]);


/** 
 * Returns the number of vetors of <tt>this</tt> CATMathSetOfVectors. 
 */    
  CATLONG32 GetNumberOfVectors() const ;

/** 
  * @nodoc
  * @deprecated V5R20 SetVectorNumber
  * Allocates the memory for <tt>this</tt> CATMathSetOfVectors.
  */
  void SetNumberOfVectors(CATLONG32 iCountVectors);

  /** 
  * Allocates the memory for <tt>this</tt> CATMathSetOfVectors.
  *@return E_FAIL if the given data is not positive, S_OK otherwise.
  */
  HRESULT SetVectorNumber(CATLONG32 iCountVectors);


/**
 * Returns the CATMathVector locating at a given index.
 *<br>The index <tt>iIndexVector</tt> starts at <tt>0</tt>.
 *<br>Use preferently the second method signature if you want to avoid an
 * useless constructor.
 */
  CATMathVector   GetVector(CATLONG32  iIndexVector) const;

/**
 * Retrieves the CATMathVector locating at a given index.
 *<br>The index <tt>iIndexVector</tt> starts at <tt>0</tt>.
 */
  void GetVector(CATLONG32 iIndexVector, CATMathVector &ioVector);
  
/**
 * Returns the array of CATMathVectors.
 *<br>Note that the returned array is used by <tt>this</tt> CATMathSetOfVectors and
 * must not be deleted.
 */
  CATMathVector * GetVectors() const;

/**
 * Initializes the values of a CATMathVector in the CATMathSetOfVectors.
 *<br>The index <tt>iIndexVector</tt> starts at <tt>0</tt>.
 */
  void SetVector(const CATMathVector & iVector, CATLONG32 iIndex);

/**
 * Use now the former signature of this method.
 */
  void SetVector(double , double , double , CATLONG32 );
};

INLINE CATLONG32 CATMathSetOfVectors::GetNumberOfVectors() const
{
  return _CountDatas;
}

INLINE HRESULT CATMathSetOfVectors::SetVectorNumber(CATLONG32 iCountVectors)
{
	 HRESULT IsOK = SetNumberOf3DElements(iCountVectors);
	return IsOK;
}
#include "CATMathAbstractSetOfVectors.h"
#endif
