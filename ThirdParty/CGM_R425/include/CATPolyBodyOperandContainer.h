#ifndef CATPolyBodyOperandContainer_H
#define CATPolyBodyOperandContainer_H

#include "PolyBodyTools.h"
#include "CATListPV.h"
#include "CATListOfInt.h"
#include "CATPolyBodyOperandIterator.h"

class CATPolyBody;
class CATMathTransformation;


/**
 * A container of CATPolyBody operands (including optional positions).
 * The reference count of the CATPolyBody added to the container is incremented
 * and a copy of the position is made.
 * The range of the operands is 0 to Size () - 1.
 *
 * @see CATPolyBodyOperandIterator
 */
class ExportedByPolyBodyTools CATPolyBodyOperandContainer
{

public:

  inline CATPolyBodyOperandContainer (unsigned int iEstimatedSize = 0);

  CATPolyBodyOperandContainer (const CATPolyBodyOperandContainer& rhs);

  CATPolyBodyOperandContainer (CATPolyBodyOperandIterator& it);

  ~CATPolyBodyOperandContainer ();

  CATPolyBodyOperandContainer& operator = (const CATPolyBodyOperandContainer& rhs);

public:

  /**
   * Appends an operand.
   * @param iPolyBody
   *   The input CATPolyBody
   * @param iPosition
   *   The option position of the input CATPolyBody.
   * @param iTag
   *   An optional tag to identify the operand.  
   *   To define a tag use any integer different from 0.  
   *   If define, it should unambiguously identify the operand.
   */
  void Append (const CATPolyBody& iPolyBody, const CATMathTransformation* iPosition = 0,
               const int iTag = 0);

  /**
   * Appends a sequence of operands.
   */
  void Append (CATPolyBodyOperandIterator& it);

  /**
   * Returns the number of operands.
   */
  inline unsigned int Size () const;

  /**
   * Returns the operand given an index ranging from 0 to Size () - 1.
   */
  inline const CATPolyBody* GetPolyBody (unsigned int k) const;

  /**
   * Returns the position of an operand given an index ranging from 0 to Size () - 1.
   */
  inline const CATMathTransformation* GetPosition (unsigned int k) const;

  /**
   * Returns the tag of an operand given an index ranging from 0 to Size () - 1.
   * A valid tag should be unique to an operand and different from 0.
   */
  inline int GetTag (unsigned int k) const;

  /**
   * Returns the index of an operand, given its tag.
   * This assumes that operands were added to the container with a uniquely identifying tag.
   */
  inline unsigned int GetIndex (const int iTag) const;

  /**
   * Remove all operands from the container.
   */
  void RemoveAll ();

public:

  /**
   * Iterator through the ordered operands from the container.
   */
  class Iterator : public CATPolyBodyOperandIterator
  {
  public:

    Iterator (const CATPolyBodyOperandContainer& operands) :
      _Operands (operands),
      _Index (0),
      _Size (operands.Size ()) {}

    CATPolyBodyOperandIterator& Begin () { _Index = 0; return *this; }
    bool End () { return _Index >= _Size; }
    CATPolyBodyOperandIterator& operator++ () { ++_Index; return *this; }

    const CATPolyBody* GetPolyBody () const { return _Operands.GetPolyBody (_Index); }
    const CATMathTransformation* GetPosition () const { return _Operands.GetPosition (_Index); }
    int GetTag () const { return _Operands.GetTag (_Index); }

    /**
     * Returns the index of the operand: From 0 to N-1 where N is the number of operands.
     */
    inline unsigned int Index () const { return _Index; }

  private:

    const CATPolyBodyOperandContainer& _Operands;
    unsigned int _Index;
    unsigned int _Size;

  };

private:

  CATListPV _Container;
  CATListOfInt _Tags;

};

inline CATPolyBodyOperandContainer::CATPolyBodyOperandContainer (unsigned int iEstimatedNbOperands) : 
  _Container (2 * iEstimatedNbOperands),
  _Tags (iEstimatedNbOperands)
{}

inline unsigned int CATPolyBodyOperandContainer::Size () const
{
  return _Container.Size () / 2;
}

inline const CATPolyBody* CATPolyBodyOperandContainer::GetPolyBody (unsigned int k) const
{
  return (const CATPolyBody*) _Container[2 * k + 1];
}

inline const CATMathTransformation* CATPolyBodyOperandContainer::GetPosition (unsigned int k) const
{
  return (const CATMathTransformation*) _Container[2 * k + 2];
}

inline int CATPolyBodyOperandContainer::GetTag (unsigned int k) const
{
  return _Tags[k + 1];
}

inline unsigned int CATPolyBodyOperandContainer::GetIndex (const int iTag) const
{
  return _Tags.Locate (iTag) - 1;
}

#endif
