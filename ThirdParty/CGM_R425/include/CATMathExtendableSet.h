#ifndef CATMathExtendableSet_H
#define CATMathExtendableSet_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MAT.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATIACGMLevel.h"
#include "IUnknown.h"

class CATMathTransformation;
/**
 * Class handling the allocation for a set or grid
 * of points or vectors.
 *<br>This class contains an array of pointers, and is derived to specialize
 * the type of pointers and the operations that can be done.
 */
class ExportedByYN000MAT CATMathExtendableSet : public CATCGMVirtual 
{
public:

//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs an empty CATMathExtendableSet of null size.
 */
  CATMathExtendableSet();

  /**
  * @nodoc
  * @deprecated V5R20 Initialize
  * Constructs a CATMathExtendableSet of a given size.
  * <br>Throws an error if the given size is not positive.
  */
  CATMathExtendableSet(CATLONG32 iSizeInDouble);
 
/**
 * Destructor.
 */
  virtual ~CATMathExtendableSet();

//=============================================================================
// SET AND GET METHODS
//=============================================================================
  /**
  * Initializes a CATMathExtendableSet of a given size.
  * <br>Return E_FAIL if the given size is not positive, S_OK otherwise.
  */
  HRESULT Initialize(CATLONG32 iSizeInDouble);


  /**
  * Releases the unused memory according to the last specified size.
  *<br>This is particulary useful after a modification of a derived object.
  */
  virtual void Compress();

/**
 * Gets all coef. 
 *<br>The array is a part of "this" and must not be deallocated.
 */
  const double * GetAllCoef () const { return _ArrayDatas ; } ; 

  /** @nodoc  */
  virtual size_t  GetStaticMemoryBytes() const;
  
  /** @nodoc  */
  virtual size_t  GetDynamicMemoryBytes() const;   

protected:

/**
 * @nodoc
 * @deprecated V5R20 SetExtendableSetSize
 * Modifies the size of the CATMathExtendableSet.
 * <br>Throws an error if the new size is not positive.
 */
  void SetSize(CATLONG32 iNewSizeInDouble);

  /**
 * Modifies the size of the CATMathExtendableSet.
 * <br>Return E_FAIL if the given size is not positive, S_OK otherwise.
 */
  HRESULT SetExtendableSetSize(CATLONG32 iNewSizeInDouble);


/**
 * Copies the data of another CATMathExtendableSet.
 *<br>The memory is enlarge if necessary.
 */
  void CopyDatas(const CATMathExtendableSet &iSetToCopy);

/**
 * Applies a transformation to the data, assumimg they are points.
 */
  void ApplyTransfoToPoints(const CATMathTransformation & iTransfo, 
	                                           CATLONG32 iNbPointsToTransfo);

/**
 * Applies a transformation to the data, assumimg they are vectors.
 *<br>In this case, the translation is not tacken into account.
 */
  void ApplyTransfoToVectors(const CATMathTransformation & iTransfo,
	                       CATLONG32 iNbVectorsToTransfo);

protected:
// Size of the array (expressed in double)
  CATLONG32     _Size;

// Array of double that is containing the datas
  double * _ArrayDatas;

private:
// Size of llocated memory for the array ( expressed in double)
  CATLONG32     _Allocated;

};

#endif



