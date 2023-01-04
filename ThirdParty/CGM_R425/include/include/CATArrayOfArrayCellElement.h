//===================================================================
// COPYRIGHT Dassault Systemes 2019
//===================================================================
// CATArrayOfArrayCellElement.cpp
// Header definition of class CATArrayOfArrayCellElement
//===================================================================
//
// Usage notes:
// Array of array of cell elements
// Example of use: content for a voxel grid.
//
//===================================================================
// 07/19 - F1Z - Creation
// MM/YY
//===================================================================

#ifndef CATArrayOfArrayCellElement_H
#define CATArrayOfArrayCellElement_H

#include "PolyMathContainers.h"
#include "CATPoly.h"

/**
 * Container for cell element
 * Each voxel has an associated array to store the cell element
 * Cost: O(1) to insert, O(N) to remove.
 * It is possible to have severals time the same triangle in a voxel.
 */
class ExportedByPolyMathContainers CATArrayOfArrayCellElement
{
public:
  CATArrayOfArrayCellElement() : _arrayElem(0), _nbArray(0) {};
  virtual ~CATArrayOfArrayCellElement();

  void Initialize(const int iNbArray);

  inline Poly::CellElement * operator[](int iIdArray) { return _arrayElem[iIdArray] ? &(_arrayElem[iIdArray][2])      : 0; };
  inline Poly::CellElement * Get(int iIdArray)        { return _arrayElem[iIdArray] ? &(_arrayElem[iIdArray][2])      : 0; };
  inline int                 GetSize(int iIdArray)    { return _arrayElem[iIdArray] ? _arrayElem[iIdArray][1].Index() : 0; };

  HRESULT Add   (const Poly::CellElement & iToAdd   , const int iIdArray);
  HRESULT Remove(const Poly::CellElement & iToRemove, const int iIdArray);

  class Iterator
  {
  public:
    Iterator(const CATArrayOfArrayCellElement & iContainer, int iIdArray) : _arrayElem(((CATArrayOfArrayCellElement&)iContainer)._arrayElem[iIdArray]), _id(2) {};
    virtual ~Iterator() { _arrayElem = 0; };

    Iterator                & Begin()      { _id = 2;  return *this; };
    Iterator                & operator++() { ++_id; return *this; };
    bool                      End()        { return (_arrayElem) ? _id >= _arrayElem[1].Index()+2 : true; };
    const Poly::CellElement & operator*()  { return (!End()) ? _arrayElem[_id] : _arrayElem[0]; };

  private:
    Poly::CellElement * _arrayElem;
    int _id;
  };

private:
  Poly::CellElement ** _arrayElem;
  int                  _nbArray;
};

/**
 * Inheritance for element type cast
 */
template<typename CellElementType>
class CATArrayOfArrayOf : public CATArrayOfArrayCellElement
{
public:
  CATArrayOfArrayOf() : CATArrayOfArrayCellElement() {};
  ~CATArrayOfArrayOf(){};

  inline CellElementType * operator[](int iIdArray) { return (CellElementType*)CATArrayOfArrayCellElement::operator[](iIdArray); };
  inline CellElementType * Get(int iIdArray) { return (CellElementType*)CATArrayOfArrayCellElement::Get(iIdArray); };
};

#endif
