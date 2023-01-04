#ifndef CATPolyBodyUnaryObserverProxy_H
#define CATPolyBodyUnaryObserverProxy_H

#include "PolyBodyTools.h"
#include "CATPolyBodyNaryObserver.h"
#include "CATPolyBodyUnaryObserver.h"


/**
 * Unary-proxy observer for a n-ary observer.
 * This enables the use of a CATPolyBodyNaryObserver in an operator requiring a CATPolyBodyUnaryObserver observer.
 */
class ExportedByPolyBodyTools CATPolyBodyUnaryObserverProxy : public CATPolyBodyUnaryObserver
{

public:

  inline CATPolyBodyUnaryObserverProxy (CATPolyBodyNaryObserver& obs);

public:

  bool RequestGeometryEvents ();

  unsigned int GetIndexOfOperandFromTag (const int iTag) const;

  void Begins (CATPolyBodyOperandIterator& it);
  void Begins (const CATPolyBody& iPolyBody, const CATMathTransformation* iPosition, const int iTag);
  void Begins (const CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);

  void Result (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);

  void Ends (HRESULT hrRun);

public:

  void BeginVertex (const CATPolyCellPoint* iPoint);

  void EndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells);
  void EndVertex (CATPolyVertex* vertex, CATPolyCell* iCellOperand);

public:

  void BeginEdge ();

  void AppendCurveVertex (const int cv, const CATPolyCellPoint* iPoint);

  void EndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells);
  void EndEdge (CATPolyEdge* edge, CATPolyCell* iCellOperand);

public:

  void BeginFace ();

  void AddSurfaceVertex (const int sv, const CATPolyCellPoint* iPoint);

  void AddTriangle (const int t, CATPolyFace* iFace, const int iFaceTriangle);

  void EndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells);
  void EndFace (CATPolyFace* face, CATPolyFace* iFaceOperand);

public:

  void UneditedSurface (CATPolyFace& iResultFace, 
                        const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                        int iOrientation, const CATMapOfIntToInt* iVertexMap);

  void UneditedCurves (CATPolyEdge& iResultEdge, 
                       const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                       int iOrientation);

  void UneditedPoints (CATPolyVertex& iResultVertex, 
                       const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag);

private:

  CATPolyBodyNaryObserver& _NaryObserver;
  const CATPolyBody* _PolyBody;
  int _Tag;

};

inline CATPolyBodyUnaryObserverProxy::CATPolyBodyUnaryObserverProxy (CATPolyBodyNaryObserver& obs) :
  _NaryObserver (obs),
  _PolyBody (0),
  _Tag (0)
{
}

#endif
