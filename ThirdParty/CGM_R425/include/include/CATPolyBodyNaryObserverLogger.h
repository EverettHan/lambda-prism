// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyNaryObserverLogger.cpp
//
//===================================================================
// March 2019 Creation: ndo
//===================================================================
#ifndef CATPolyBodyNaryObserverLogger_H
#define CATPolyBodyNaryObserverLogger_H

#include "PolyBodyTools.h"
#include "CATPolyBodyNaryObserver.h"
#include "CATUnicodeString.h"

#include <iostream>
class CATPolyCellPoint;
class CATPolyCellPointIterator;


/**
 * Logger of binary-observer events into a file.
 */
class ExportedByPolyBodyTools CATPolyBodyNaryObserverLogger : public CATPolyBodyNaryObserver
{

public:

  CATPolyBodyNaryObserverLogger (const CATUnicodeString& iFileName, CATPolyBodyNaryObserver* obs = 0);

  ~CATPolyBodyNaryObserverLogger ();

  bool RequestGeometryEvents ();

public:

  void Begins (CATPolyBodyOperandIterator& iOperands);

  void Result (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);

  void Ends (HRESULT hrRun);

public:
  
  void BeginVertex(CATPolyCellPointIterator * iCellPoints);
  void EndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells);

public:

  void BeginEdge ();
  void AppendCurveVertex(const int cv, CATPolyCellPointIterator * iCellPoints);
  void EndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells);

public:

  void BeginFace ();
  void AddSurfaceVertex(const int sv, CATPolyCellPointIterator * iCellPoints);
  void EndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells);

public:

  void UneditedSurface (CATPolyFace& iResultFace,
                        const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                        int iOrientation, const CATMapOfIntToInt* iVertexMap);

  void UneditedCurves (CATPolyEdge& iResultEdge,
                       const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                       int iOrientation);

  void UneditedPoints (CATPolyVertex& iResultVertex,
                       const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag);

public:
  unsigned int GetIndexOfOperandFromTag (const int iTag) const;

private:

  CATPolyBodyNaryObserver* _Observer;
  std::ostream* _OStream;
  int _Tag[2];
  int _Flags;

private:

  enum Masks
  {
    /** */     eBeginCell      = 0x01,
    /** */     eEndCell        = 0x02,
    /** */     eUneditedCell   = 0x04,
    /** */     eGeometryEvents = 0x08
  };

  inline std::ostream* Stream () { return _OStream; }

  friend class CATPolyBodyBinaryObserverLogger;

private:

  void LogRequestGeometryEvents (bool request);

  void LogBegins (CATPolyBodyOperandIterator& iOperands);

  void LogBegins (const CATPolyBody& iPolyBody0, const CATMathTransformation* iPosition0, const int iTag0,
                  const CATPolyBody& iPolyBody1, const CATMathTransformation* iPosition1, const int iTag1);

  void LogResult (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);

  void LogEnds (HRESULT hrRun);

  void LogBeginVertex (CATPolyCellPointIterator * iCellIterator);

  void LogEndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells);

  void LogBeginEdge ();

  void LogAppendCurveVertex (const int cv, CATPolyCellPointIterator * iCellPoints);

  void LogEndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells);

  void LogBeginFace ();

  void LogAddSurfaceVertex (const int sv, CATPolyCellPointIterator * iCellPoints);

  void LogAddTriangle (const int t, CATPolyFace* iFace, const int iFaceTriangle);

  void LogEndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells);

  void LogUneditedSurface (CATPolyFace& iResultFace,
                           const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                           int iOrientation, const CATMapOfIntToInt* iVertexMap);

  void LogUneditedCurves (CATPolyEdge& iResultEdge,
                          const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                          int iOrientation);

  void LogUneditedPoints (CATPolyVertex& iResultVertex,
                          const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag);

};

#endif // !CATPolyBodyNaryObserverLogger_H
