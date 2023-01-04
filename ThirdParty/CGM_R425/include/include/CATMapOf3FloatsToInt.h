// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOf3FloatsToInt.h
//
//===================================================================
//
// March 2009  Creation: NDO
//===================================================================
#ifndef CATMapOf3FloatsToInt_h
#define CATMapOf3FloatsToInt_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATSetOf3Floats.h"
#include "CATMapOfPtrToInt.h"

class CATCGMOutput;


/**
 * Map of triplets of floats to integers.
*/
class ExportedByPolyMathContainers CATMapOf3FloatsToInt
{

public:

  CATMapOf3FloatsToInt () {}
  ~CATMapOf3FloatsToInt () {}

  /**
   * A handle to an element in the hash table.
   * A handle provides direct access to the element.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATULONGPTR* Handle;

public:

  /**
   * Inserts a pointer to a 3D position and maps it to an integer value.
   * @param d
   *   A pointer to a triplet of floats representing the coordinates of a point. 
   *   The pointer must remain valid throughout its use in the map.
   * @param value
   *   The integer value associated to the position.  One and only one value can be associated to a 3D position.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> The 3D position and its integer value is inserted in the map.
   *   <li> <tt>S_FALSE</tt> The 3D position is already in the map and the integer values match.
   *   <li> <tt>E_FAIL</tt> The 3D position cannot be inserted in the map because the integer values do not match or some other error.
   * </ul>
   */
  HRESULT Insert (const float* d, const int value);

  /**
   * Inserts a pointer to a 3D position and maps it to an integer value.
   * @param d
   *   A pointer to a triplet of doubles representing the coordinates of a point. 
   *   The pointer must remain valid throughout its use in the map.
   * @param value
   *   The integer value associated to the position.  One and only one value can be associated to a 3D position.
   * @param oHandle
   *   The handle to a pair (position, value) stored in the map.  
   *   This is an output parameter which is set to a valid handle even when the method fails because a different 
   *   integer value is already stored in the map for this position.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> The 3D position and its integer value is inserted in the map.
   *   <li> <tt>S_FALSE</tt> The 3D position is already in the map and the integer values match.
   *   <li> <tt>E_FAIL</tt> The 3D position cannot be inserted in the map because the integer values do not match.
   *                        In this case, a valid handle is set.  Otherwise for any other error (memory allocation failure for example)
   *                        the handle returned is invalid.
   * </ul>
   */
  HRESULT Insert (const float* d, const int data, Handle& oHandle);

  /**
   * Removes the pointer from the map.
   */
  HRESULT Remove (const float* d);

  /**
   * Updates the integer value associated to the floats in the map.
   * The method returns S_OK if the value is successfully updated, 
   * S_FALSE if the floats are not found in the map, and an error otherwise.
   */
  HRESULT Update (const float* d, const int value);

  /**
   * Returns TRUE and the integer value associated to three floats.  
   * Returns FALSE if the three floats are not found in the map.
   */
  CATBoolean Locate (const float* d, int& value) const;

public:

  /**
   * Returns the number of elements in the map.
   */
  inline int Size () const;

  inline HRESULT RemoveAll ();

public:

  /** 
   * Returns the 3D position given a handle.
   */
  inline const float* GetPosition (Handle iHandle) const;

  /** 
   * Returns the integer value given a handle.
   */
  inline int GetIndex (Handle iHandle) const;

private:

  CATSetOf3Floats _SetOfFloats;
  CATMapOfPtrToInt _MapHandleToValue;

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

};

inline int CATMapOf3FloatsToInt::Size () const
{
  return _SetOfFloats.Size ();
}

inline HRESULT CATMapOf3FloatsToInt::RemoveAll ()
{
  _SetOfFloats.RemoveAll ();
  return _MapHandleToValue.RemoveAll ();
}

inline const float* CATMapOf3FloatsToInt::GetPosition (Handle iHandle) const
{
  CATSetOf3Floats::Handle handle = (CATSetOf3Floats::Handle) _MapHandleToValue.GetKey (iHandle);
  return _SetOfFloats.Get (handle);
}

inline int CATMapOf3FloatsToInt::GetIndex (Handle iHandle) const
{
  return _MapHandleToValue.GetData (iHandle);
}

#endif
