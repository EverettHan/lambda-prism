// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOf3DoublesToInt.h
//
//===================================================================
// February 2012  Creation: NDO
// May      2013  Modification JXO: Added some useful getters
// August   2015  Modification JXO: Iterator
//===================================================================
#ifndef CATMapOf3DoublesToInt_h
#define CATMapOf3DoublesToInt_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATSetOf3Doubles.h"
#include "CATMapOfPtrToInt.h"

class CATCGMOutput;


/**
 * Map of triplets of doubles to integers.
*/
class ExportedByPolyMathContainers CATMapOf3DoublesToInt
{

public:

  CATMapOf3DoublesToInt () {}
  ~CATMapOf3DoublesToInt () {}

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
   *   A pointer to a triplet of doubles representing the coordinates of a point. 
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
  HRESULT Insert (const double* d, const int value);

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
  HRESULT Insert (const double* d, const int data, Handle& oHandle);

  /**
   * Removes the pointer from the map.
   */
  HRESULT Remove (const double* d);

  /**
   * Updates the integer value associated to the doubles in the map.
   * The method returns S_OK if the value is successfully updated, 
   * S_FALSE if the doubles are not found in the map, and an error otherwise.
   */
  HRESULT Update (const double* d, const int value);

  /**
   * Returns TRUE and the integer value associated to three doubles.  
   * Returns FALSE if the three doubles are not found in the map.
   */
  CATBoolean Locate (const double* d, int& value) const;

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
  inline const double* GetPosition (Handle iHandle) const;

  /** 
   * Returns the integer value given a handle.
   */
  inline int GetIndex (Handle iHandle) const;

public:

  // Iterator to cycle through all the elements in the map.
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATMapOf3DoublesToInt& map) : _SetOfDoubles (map._SetOfDoubles), _It (map._MapHandleToValue) {}
    ~Iterator () {}

    void GetDoubles (double& x, double& y, double& z) const
    {
      const double * dd = _SetOfDoubles.Get ((CATSetOf3Doubles::Handle) _It.GetKey ());
      if(dd)
      {
        x = dd[0];
        y = dd[1];
        z = dd[2];
      }
    }
    int GetData () const {return _It.GetData ();}

    Iterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    Iterator& operator++ () {++_It; return *this;}

  private:
    const CATSetOf3Doubles& _SetOfDoubles;
    CATMapOfPtrToInt::Iterator _It;
  };

  friend class Iterator;

private:

  CATSetOf3Doubles _SetOfDoubles;
  CATMapOfPtrToInt _MapHandleToValue;

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

  /**
   * Returns the set of points stored in the map.
   */
  CATSetOf3Doubles & GetSetOf3Doubles(){return _SetOfDoubles;}

  /**
   * Given a handle for a point, returns the value associated to this point.
   * The handle is returned by the iterator through the set of points.
   */
  inline CATBoolean Fetch (CATSetOf3Doubles::Handle h, int& oValue) const;
};


inline int CATMapOf3DoublesToInt::Size () const
{
  return _SetOfDoubles.Size ();
}

inline HRESULT CATMapOf3DoublesToInt::RemoveAll ()
{
  _SetOfDoubles.RemoveAll ();
  return _MapHandleToValue.RemoveAll ();
}

inline const double* CATMapOf3DoublesToInt::GetPosition (Handle iHandle) const
{
  CATSetOf3Doubles::Handle handle = (CATSetOf3Doubles::Handle) _MapHandleToValue.GetKey (iHandle);
  return _SetOfDoubles.Get (handle);
}

inline int CATMapOf3DoublesToInt::GetIndex (Handle iHandle) const
{
  return _MapHandleToValue.GetData (iHandle);
}

inline CATBoolean CATMapOf3DoublesToInt::Fetch (CATSetOf3Doubles::Handle h, int& oValue) const
{
  return _MapHandleToValue.Locate (h, oValue);
}


#endif
