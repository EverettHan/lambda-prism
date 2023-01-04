#ifndef CATMathSetOf3DObjects_H
#define CATMathSetOf3DObjects_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MAT.h"
#include "CATMathExtendableSet.h"
#include "CATMathInline.h"
#include "IUnknown.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class handling the allocation of sets of CATMathSetOfPoints
 * and CATMathSetOfVectors.
 *<br>The size is defined by a number of objects of 3 doubles 
 *<tt>NbObjects</tt>.
 *<br>The <tt>SetNumberOfElements</tt> method enlarges the memory if
 * needed, while the <tt>Compress</tt> inherited method releases the free 
 * unused memory.
 */
class ExportedByYN000MAT CATMathSetOf3DObjects: public CATMathExtendableSet
{
//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
protected:
/**
 * Constructs an empty CATMathSetOf3DObjects with 0 object.
 */
  CATMathSetOf3DObjects();

/**
 * @nodoc
 * @deprecated V5R20 SetNumberOf3DElements
 * Constructs from the number of objects.
 */
  CATMathSetOf3DObjects(CATLONG32 iNbObjects);

/**
 * Copy constructor.
 */
  CATMathSetOf3DObjects(const CATMathSetOf3DObjects &SetToCopy);

public: 
/**
 * Destructor.
 */
  virtual ~CATMathSetOf3DObjects();

/**
 * Defines the affectation operator.
 */
  const CATMathSetOf3DObjects & operator = (const CATMathSetOf3DObjects & iSetToCopy);

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * @nodoc
 * @deprecated V5R20 SetNumberOf3DElements
 * Modifies the dimension of a CATMathSetOf3DObjects.
 *<br>This method re-allocates the memory if necessary.
 */
  virtual void SetNumberOfElements(CATLONG32 iNbObjects);

/**
 * Modifies the dimension of a CATMathSetOf3DObjects.
 * <br>This method re-allocates the memory if necessary.
 * @return E_FAIL if the given number is not positive, S_OK otherwise.
 */
  virtual HRESULT SetNumberOf3DElements(CATLONG32 iNbObjects);

/**
 * Returns the number of objects of a CATMathSetOfObjects.
 */
INLINE CATLONG32 GetNumberOfElements() const;

/**
 * @nodoc
 * Dumps a CATMathSetOf3DObjects.
 * <br>This writes the following lines on the ostream if <tt>iLevel = 1</tt>:
 *<pre>
 *   Set(1) = ( FirstCoord_1 , SecondCoord_1 , ThirdCoord_1 )
 *   Set(2) = ( FirstCoord_2 , SecondCoord_2 , ThirdCoord_2 )
 *   ...
 *   Set(n) = ( FirstCoord_n , SecondCoord_n , ThirdCoord_n )</pre>
 * Only outputs the number of objects if <tt>iLevel = 0</tt>.
 * @param iStream  
 * A pointer to the output. If <tt>0L</tt>, the method dumps 
 * on the <tt>cout</tt> output.
 * @param iDebugLevel
 * The debug level.
 * <dl><dt><tt>0</tt><dd> 
 * for writing the number of objects.
 *     <dt><tt>1</tt><dd> 
 * for writing the coordinates of the objects.</dl>
 */
  virtual void Dump(CATLONG32 iDebugLevel=0, ostream * iStream = 0L) const;

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
  CATLONG32  _CountDatas;

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATLONG32 CATMathSetOf3DObjects::GetNumberOfElements() const
{
  return _CountDatas;
}

#endif

