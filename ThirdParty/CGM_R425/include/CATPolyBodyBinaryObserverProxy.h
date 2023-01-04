#ifndef CATPolyBodyBinaryObserverProxy_H
#define CATPolyBodyBinaryObserverProxy_H

#include "PolyBodyTools.h"
#include "CATPolyBodyNaryObserver.h"
#include "CATPolyBodyBinaryObserver.h"


/**
 * Binary-proxy observer for a n-ary observer.
 * This enables the use of a CATPolyBodyNaryObserver in an operator requiring a CATPolyBodyBinaryObserver observer.
 */
class ExportedByPolyBodyTools CATPolyBodyBinaryObserverProxy : public CATPolyBodyBinaryObserver
{

public:

  inline CATPolyBodyBinaryObserverProxy (CATPolyBodyNaryObserver& obs);

public:

  bool RequestGeometryEvents ();

  unsigned int GetIndexOfOperandFromTag (const int iTag) const;

  void Begins (CATPolyBodyOperandIterator& it);

  void Begins (const CATPolyBody& iPolyBody0, const CATMathTransformation* iPosition0, const int iTag0,
               const CATPolyBody& iPolyBody1, const CATMathTransformation* iPosition1, const int iTag1);

  void Begins (const CATPolyBody& iPolyBody0, const CATMathTransformation* iPosition0,
               const CATPolyBody& iPolyBody1, const CATMathTransformation* iPosition1);

  void Result (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);

  void Ends (HRESULT hrRun);

public:

  void BeginVertex (const CATPolyCellPoint* iPoint0, const CATPolyCellPoint* iPoint1);

  void EndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells);
  void EndVertex (CATPolyVertex* vertex, CATPolyCell* iCellOperand0, CATPolyCell* iCellOperand1);

public:

  void BeginEdge ();

  void AppendCurveVertex (const int cv, const CATPolyCellPoint* iPoint0, const CATPolyCellPoint* iPoint1);

  void EndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells);
  void EndEdge (CATPolyEdge* edge, CATPolyCell* iCellOperand0, CATPolyCell* iCellOperand1);

public:

  void BeginFace ();

  void AddSurfaceVertex (const int sv, const CATPolyCellPoint* iPoint0, const CATPolyCellPoint* iPoint1);

  void AddTriangle (const int t, CATPolyFace* iFace, const int iFaceTriangle);

  void EndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells);
  void EndFace (CATPolyFace* face, CATPolyFace* iFaceOperand0, CATPolyFace* iFaceOperand1);

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
  const CATPolyBody* _PolyBody[2];
  int _Tag[2];

};

inline CATPolyBodyBinaryObserverProxy::CATPolyBodyBinaryObserverProxy (CATPolyBodyNaryObserver& obs) :
  _NaryObserver (obs)
{
  _PolyBody[0] = 0;
  _PolyBody[1] = 0;
  _Tag[0] = 0;
  _Tag[1] = 1;
}

#endif
