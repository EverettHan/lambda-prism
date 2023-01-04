#ifndef CATPolyBodyOperandCellIterator_H
#define CATPolyBodyOperandCellIterator_H

#include "PolyBodyTools.h"

class CATPolyBody;
class CATPolyCell;


/**
 * Iterator through a subset of cells from an ordered set of operands.
 * An operand consists of a CATPolyBody and an optional position matrix.
 * The iterator cycles through a subset of cells from the operands.
 * The operands range from 0 to N - 1 where N is the total number of operands.
 *
 * @see CATPolyBodyOperandIterator
 */
class ExportedByPolyBodyTools CATPolyBodyOperandCellIterator
{

public:

  virtual ~CATPolyBodyOperandCellIterator () {}

public:

  virtual CATPolyBodyOperandCellIterator& Begin () = 0;
  virtual bool End () = 0;
  virtual CATPolyBodyOperandCellIterator& operator++ () = 0;

public:

  /**
   * Return the CATPolyBody containing the cell.
   */
  virtual const CATPolyBody* GetPolyBody () const = 0;

  /**
   * Return the cell.
   */
  virtual const CATPolyCell* GetCell () const = 0;

  /**
  * Return the orientation of the cell.
  */
  virtual int GetOrientation() const = 0;

  /**
  * Returns the tag of the operand,
  * The tag unambiguously identifies the operand.
  */
  virtual int GetTag () const = 0;

};


/**
 * Basic implementation of the operand-cell iterator for unary or binary operators.
 */
class ExportedByPolyBodyTools CATPolyBodyOperandCellIteratorOne : public CATPolyBodyOperandCellIterator
{

public:

  /**
   * Construction of the operand-cell iterator for unary operators.
   */
  inline CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0, const int iTag0);

  inline CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0);

  /**
   * Construction of the operand-cell iterator for binary operators.
   */
  inline CATPolyBodyOperandCellIteratorOne(const CATPolyBody * pb0, CATPolyCell * cell0,
                                           const CATPolyBody * pb1, CATPolyCell * cell1);

  inline CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0, const int iTag0,
                                            const CATPolyBody* pb1, CATPolyCell* cell1, const int iTag1);

  inline CATPolyBodyOperandCellIteratorOne(const CATPolyBody * pb0, CATPolyCell * cell0, const int iTag0, const int iOrientation0,
                                           const CATPolyBody * pb1, CATPolyCell * cell1, const int iTag1, const int iOrientation1);

public:

  CATPolyBodyOperandCellIterator& Begin () { _Index = _PolyBody[0] ? 0 : 1; return *this; }
  bool End () { return _Index >= _Size; }
  CATPolyBodyOperandCellIterator& operator++ () { ++_Index; return *this; }

public:

  virtual const CATPolyBody* GetPolyBody () const { return _PolyBody[_Index]; }
  virtual const CATPolyCell* GetCell () const { return _PolyCell[_Index]; }
  virtual int GetTag () const { return _Tag[_Index]; }
  virtual int GetOrientation() const { return _Orientation[_Index]; }

  /**
   * Returns the index of the operand: 0 or 1
   */
  inline unsigned int Index () const { return _Index; }

private:

  const CATPolyBody* _PolyBody[2];
  const CATPolyCell* _PolyCell[2];
  int _Tag[2];
  int _Orientation[2];
  unsigned int _Index;
  unsigned int _Size;

};

inline CATPolyBodyOperandCellIteratorOne::CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0, const int tag0) :
  _Index (0),
  _Size (0)
{
  _PolyBody[0] = 0;
  _PolyBody[1] = 0;
  _PolyCell[0] = 0;
  _PolyCell[1] = 0;
  _Tag[0] = 0;
  _Tag[1] = 1;
  _Orientation[0] = 1;
  _Orientation[1] = 1;
  if (pb0 && cell0)
  {
    _PolyBody[0] = pb0;
    _PolyCell[0] = cell0;
    _Tag[0] = tag0;
    _Size = 1;
  }
}

inline CATPolyBodyOperandCellIteratorOne::CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0) :
  _Index (0),
  _Size (0)
{
  _PolyBody[0] = 0;
  _PolyBody[1] = 0;
  _PolyCell[0] = 0;
  _PolyCell[1] = 0;
  _Tag[0] = 0;
  _Tag[1] = 1;
  _Orientation[0] = 1;
  _Orientation[1] = 1;
  if (pb0 && cell0)
  {
    _PolyBody[0] = pb0;
    _PolyCell[0] = cell0;
    _Size = 1;
  }
}

inline CATPolyBodyOperandCellIteratorOne::CATPolyBodyOperandCellIteratorOne(const CATPolyBody * pb0, CATPolyCell * cell0, const int iTag0, const int iOrientation0,
                                                                            const CATPolyBody * pb1, CATPolyCell * cell1, const int iTag1, const int iOrientation1) :
  _Index(0),
  _Size(0)
{
  _PolyBody[0] = 0;
  _PolyBody[1] = 0;
  _PolyCell[0] = 0;
  _PolyCell[1] = 0;
  _Tag[0] = 0;
  _Tag[1] = 1;
  _Orientation[0] = 1;
  _Orientation[1] = 1;
  if (pb0 && cell0)
  {
    _PolyBody[0] = pb0;
    _PolyCell[0] = cell0;
    _Tag[0] = iTag0;
    _Orientation[0] = iOrientation0;
    _Size = 1;
  }
  if (pb1 && cell1)
  {
    _PolyBody[_Size] = pb1;
    _PolyCell[_Size] = cell1;
    _Tag[_Size] = iTag1;
    _Orientation[_Size] = iOrientation1;
    ++_Size;
  }
}


inline CATPolyBodyOperandCellIteratorOne::CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0, const int tag0,
                                                                             const CATPolyBody* pb1, CATPolyCell* cell1, const int tag1) :
  _Index (0),
  _Size (0)
{
  _PolyBody[0] = 0;
  _PolyBody[1] = 0;
  _PolyCell[0] = 0;
  _PolyCell[1] = 0;
  _Tag[0] = 0;
  _Tag[1] = 1;
  _Orientation[0] = 1;
  _Orientation[1] = 1;
  if (pb0 && cell0)
  {
    _PolyBody[0] = pb0;
    _PolyCell[0] = cell0;
    _Tag[0] = tag0;
    _Size = 1;
  }
  if (pb1 && cell1)
  {
    _PolyBody[_Size] = pb1;
    _PolyCell[_Size] = cell1;
    _Tag[_Size] = tag1;
    ++_Size;
  }
}

inline CATPolyBodyOperandCellIteratorOne::CATPolyBodyOperandCellIteratorOne (const CATPolyBody* pb0, CATPolyCell* cell0,
                                                                             const CATPolyBody* pb1, CATPolyCell* cell1) :
  _Index (0),
  _Size (0)
{
  _PolyBody[0] = 0;
  _PolyBody[1] = 0;
  _PolyCell[0] = 0;
  _PolyCell[1] = 0;
  _Tag[0] = 0;
  _Tag[1] = 1;
  _Orientation[0] = 1;
  _Orientation[1] = 1;
  if (pb0 && cell0)
  {
    _PolyBody[0] = pb0;
    _PolyCell[0] = cell0;
    _Size = 1;
  }
  if (pb1 && cell1)
  {
    _PolyBody[_Size] = pb1;
    _PolyCell[_Size] = cell1;
    ++_Size;
  }
}

#endif
