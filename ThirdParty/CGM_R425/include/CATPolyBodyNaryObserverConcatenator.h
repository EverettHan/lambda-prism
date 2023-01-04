// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyNaryObserverConcatenator.h
//
//===================================================================
// February 2017 Creation: xxc
//===================================================================
#ifndef CATPolyBodyNaryObserverConcatenator_HH
#define CATPolyBodyNaryObserverConcatenator_HH

#include "PolyBodyTools.h" // Exported by.
#include "CATPolyBodyNaryObserver.h"

class CATPolyBodyUnaryObserver;
class CATPolyBodyBinaryObserver;


/** 
 * Service to concatenate calls to observers when several n-ary operators are called in sequence.
 *
 * The local n-ary observer from the concatenator can be passed as an argument to the sequence of operators.
 * It is constructed from the input n-ary observer which will be called at the end with up to date 
 * event calls about the result.
 *
 */
class ExportedByPolyBodyTools CATPolyBodyNaryObserverConcatenator : public CATPolyBodyNaryObserver
{

public:

  CATPolyBodyNaryObserverConcatenator (CATPolyBodyNaryObserver& iParentObserver);
  virtual ~CATPolyBodyNaryObserverConcatenator ();

public:

  /**
   * Returns the local unary observer to watch local events.
   */
  CATPolyBodyUnaryObserver* LocalUnaryObserver ();

  /**
   * Returns the local binary observer to watch local events.
   */
  CATPolyBodyBinaryObserver* LocalBinaryObserver ();

  /**
   * Returns the local n-ary observer to watch local events.
   */
  inline CATPolyBodyNaryObserver* LocalNaryObserver ();

  /**
   * Returns the tag of the result after a local operation.
   * The result tag is defined after a call to the Begin () method of the local observer.
   */
  int GetTagOfLocalResult () const;

  /**
   * Flushes a local operand which is no longer needed in the
   * remaining operations.
   */
  void FlushLocalOperand (const int tag);

public:

  unsigned int GetIndexOfOperandFromTag (const int iTag) const;

  void Begins (CATPolyBodyOperandIterator& iOperands);
  void Result (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);
  void Ends (HRESULT hrRun);

private:

  CATPolyBodyNaryObserver& _ParentObserver;

  CATPolyBodyUnaryObserver* _LocalUnaryObserver;
  CATPolyBodyBinaryObserver* _LocalBinaryObserver;
  CATPolyBodyNaryObserver* _LocalNaryObserver;

};

inline CATPolyBodyNaryObserver* CATPolyBodyNaryObserverConcatenator::LocalNaryObserver ()
{
  return _LocalNaryObserver;
}

#endif
