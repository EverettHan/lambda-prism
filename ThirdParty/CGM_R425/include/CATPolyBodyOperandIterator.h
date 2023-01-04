#ifndef CATPolyBodyOperandIterator_H
#define CATPolyBodyOperandIterator_H

#include "PolyBodyTools.h"

class CATPolyBody;
class CATMathTransformation;


/**
 * Give a struct with operand information
 * Might be useful for vector based container.
 */
struct ExportedByPolyBodyTools CATPolyBodyOperandInfo
{
  CATPolyBodyOperandInfo(const CATPolyBody & iPolyBody, const CATMathTransformation * iTransfo, int iTag = 0) : _polyBody(iPolyBody), _transfo(iTransfo), _tag(iTag) {};
  const CATPolyBody & _polyBody;
  const CATMathTransformation * _transfo;
  int _tag;
};


/**
 * Iterator through an ordered set of operands.
 * An operand consists of a CATPolyBody and an optional position matrix.
 * Each operand has a tag which unambiguously identifies the operand.
 *
 * @see CATPolyBodyOperandContainer
 */
class ExportedByPolyBodyTools CATPolyBodyOperandIterator
{

public:

  virtual ~CATPolyBodyOperandIterator () {}

public:

  virtual CATPolyBodyOperandIterator& Begin () = 0;
  virtual bool End () = 0;
  virtual CATPolyBodyOperandIterator& operator++ () = 0;

public:

  virtual const CATPolyBody* GetPolyBody () const = 0;
  virtual const CATMathTransformation* GetPosition () const = 0;

  /**
   * Returns the tag of the operand,
   * The tag unambiguously identifies the operand.
   */
  virtual int GetTag () const = 0;

};


/**
* Basic implementation of the operand iterator for unary or binary operators.
*/
class ExportedByPolyBodyTools CATPolyBodyOperandIteratorOne : public CATPolyBodyOperandIterator
{

public:

  /**
  * Construction of the operand iterator for unary operators.
  */
  inline CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0, const int tag0);

  inline CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0);

  /**
  * Construction of the operand iterator for binary operators.
  */
  inline CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0, const int tag0,
                                        const CATPolyBody& pb1, const CATMathTransformation* pos1, const int tag1);

  inline CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0,
                                        const CATPolyBody& pb1, const CATMathTransformation* pos1);

public:

  CATPolyBodyOperandIterator& Begin () { _Index = _PolyBody[0] ? 0 : 1; return *this; }
  bool End () { return _Index >= _Size; }
  CATPolyBodyOperandIterator& operator++ () { ++_Index; return *this; }

public:

  virtual const CATPolyBody* GetPolyBody () const { return _PolyBody[_Index]; }
  virtual const CATMathTransformation* GetPosition () const { return _Position[_Index]; }
  virtual int GetTag () const { return _Tag[_Index]; }

  /**
   * Returns the index of the operand: 0 or 1
   */
  inline unsigned int Index () const { return _Index; }

private:

  const CATPolyBody* _PolyBody[2];
  const CATMathTransformation* _Position[2];
  int _Tag[2];
  unsigned int _Index;
  unsigned int _Size;

};

inline CATPolyBodyOperandIteratorOne::CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0, const int tag0) :
  _Index (0),
  _Size (1)
{
  _PolyBody[0] = &pb0;
  _Position[0] = pos0;
  _Tag[0] = tag0;
  _PolyBody[1] = 0;
  _Position[1] = 0;
  _Tag[1] = 1;
}

inline CATPolyBodyOperandIteratorOne::CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0) :
  _Index (0),
  _Size (1)
{
  _PolyBody[0] = &pb0;
  _Position[0] = pos0;
  _Tag[0] = 0;
  _PolyBody[1] = 0;
  _Position[1] = 0;
  _Tag[1] = 1;
}

inline CATPolyBodyOperandIteratorOne::CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0, const int tag0,
                                                                     const CATPolyBody& pb1, const CATMathTransformation* pos1, const int tag1) :
  _Index (0),
  _Size (2)
{
  _PolyBody[0] = &pb0;
  _Position[0] = pos0;
  _Tag[0] = tag0;
  _PolyBody[1] = &pb1;
  _Position[1] = pos1;
  _Tag[1] = tag1;
}

inline CATPolyBodyOperandIteratorOne::CATPolyBodyOperandIteratorOne (const CATPolyBody& pb0, const CATMathTransformation* pos0,
                                                                     const CATPolyBody& pb1, const CATMathTransformation* pos1) :
  _Index (0),
  _Size (2)
{
  _PolyBody[0] = &pb0;
  _Position[0] = pos0;
  _Tag[0] = 0;
  _PolyBody[1] = &pb1;
  _Position[1] = pos1;
  _Tag[1] = 1;
}

#endif
