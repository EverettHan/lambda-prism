#ifndef CATPolyBodyOperandCells_H
#define CATPolyBodyOperandCells_H

#include "CATListPV.h"
#include "CATDataType.h"
#include "CATPolyBodyOperandCellIterator.h"

class CATPolyBody;
class CATPolyCell;


/**
 * A list of cells from various CATPolyBody operands (including tags to identify the operands.)
 * The range of the cells is 0 to Size () - 1.
 */
class CATPolyBodyOperandCells
{

public:

  inline CATPolyBodyOperandCells (unsigned int iEstimatedSize = 0);

  inline CATPolyBodyOperandCells (const CATPolyBodyOperandCells& rhs);

  inline CATPolyBodyOperandCells (CATPolyBodyOperandCellIterator& it);

  inline CATPolyBodyOperandCells& operator = (const CATPolyBodyOperandCells& rhs);

public:

  /**
   * Appends a cell from an operand.
   * @param iTag
   *   The tag identifying the operand.
   * @param iOrientation
   *   The orientation of the cell
   */
  inline void Append (const CATPolyBody* iPolyBody, const CATPolyCell* iCell, const int iTag, const int iOrientation=1);

  /**
   * Appends the cells returned by the operand-cell iterator.
   * iRelOrientation
   *   Apply this relative orientation to the one contains in the iterator. 
   */
  inline void Append (CATPolyBodyOperandCellIterator& it, const int iRelOrientation =1);

  /**
   * Returns the number of cells.
   */
  inline unsigned int Size () const;

  /**
   * Returns the operand given an index ranging from 0 to Size () - 1.
   */
  inline const CATPolyBody* GetPolyBody (unsigned int k) const;

  /**
   * Returns the cell of the operand given an index ranging from 0 to Size () - 1.
   */
  inline const CATPolyCell* GetCell (unsigned int k) const;

  /**
   * Returns the tag of the operand given an index ranging from 0 to Size () - 1.
   */
  inline int GetTag (unsigned int k) const;

  /**
   * Returns the orientation of the cell of the operand given an index ranging from 0 to Size () - 1.
   */
  inline int GetOrientation(unsigned int k) const;

  /**
   * Remove all cells from the list.
   */
  inline void RemoveAll ();

public:

  /**
   * Iterator through the cells.
   */
  class Iterator : public CATPolyBodyOperandCellIterator
  {
  public:

    Iterator (const CATPolyBodyOperandCells& cells) :
      _Cells (cells),
      _Index (0),
      _Size (cells.Size ()) {}

    CATPolyBodyOperandCellIterator& Begin () { _Index = 0; return *this; }
    bool End () { return _Index >= _Size; }
    CATPolyBodyOperandCellIterator& operator++ () { ++_Index; return *this; }

    const CATPolyBody* GetPolyBody () const { return _Cells.GetPolyBody (_Index); }
    const CATPolyCell* GetCell () const { return _Cells.GetCell (_Index); }
    int GetTag () const { return _Cells.GetTag (_Index); }
    int GetOrientation() const { return _Cells.GetOrientation(_Index); }

  private:

    const CATPolyBodyOperandCells& _Cells;
    unsigned int _Index;
    unsigned int _Size;

  };

private:

  CATListPV _List;

};

inline CATPolyBodyOperandCells::CATPolyBodyOperandCells (unsigned int iEstimatedSize) : _List (4 * iEstimatedSize) {}

inline CATPolyBodyOperandCells::CATPolyBodyOperandCells (const CATPolyBodyOperandCells& rhs)
{
  _List = rhs._List; 
}

inline CATPolyBodyOperandCells::CATPolyBodyOperandCells (CATPolyBodyOperandCellIterator& it)
{
  for (it.Begin (); !it.End (); ++it)
  {
    Append (it.GetPolyBody (), it.GetCell (), it.GetTag ());
  }
}


inline CATPolyBodyOperandCells& CATPolyBodyOperandCells::operator = (const CATPolyBodyOperandCells& rhs)
{
  if (this != &rhs)
    _List = rhs._List;
  return *this;
}

inline void CATPolyBodyOperandCells::Append (const CATPolyBody* iPolyBody, const CATPolyCell* iCell, const int iTag, const int iOrientation)
{
  if (iPolyBody && iCell)
  {
    _List.Append ((void *) iPolyBody);
    _List.Append ((void*) iCell);
    _List.Append (CATINT32ToPtr (iTag));
    _List.Append(CATINT32ToPtr(iOrientation));
  }
}

inline void CATPolyBodyOperandCells::Append (CATPolyBodyOperandCellIterator& it, const int iRelOrientation)
{
  for (it.Begin (); !it.End (); ++it)
  {
    Append (it.GetPolyBody (), it.GetCell (), it.GetTag (), it.GetOrientation()*iRelOrientation);
  }
}

inline unsigned int CATPolyBodyOperandCells::Size () const
{
  return _List.Size () / 4;
}

inline const CATPolyBody* CATPolyBodyOperandCells::GetPolyBody (unsigned int k) const
{
  return (const CATPolyBody*) _List[4 * k + 1];
}

inline const CATPolyCell* CATPolyBodyOperandCells::GetCell (unsigned int k) const
{
  return (const CATPolyCell*) _List[4 * k + 2];
}

inline int CATPolyBodyOperandCells::GetTag (unsigned int k) const
{
  return CATPtrToINT32 (_List[4 * k + 3]);
}

inline int CATPolyBodyOperandCells::GetOrientation(unsigned int k) const
{
  return CATPtrToINT32(_List[4 * k + 4]);
}

inline void CATPolyBodyOperandCells::RemoveAll ()
{
  _List.RemoveAll ();
}

#endif
