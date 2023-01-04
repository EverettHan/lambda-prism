// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyNaryObservers.h
// 
// Encapsulate severals NaryObserver into one
// Useful if the operator takes only one observer but you want to provide several.
//
//===================================================================
// April 2022 : F1Z : Creation
//===================================================================
#pragma once

// PolyhedralObjects
#include "CATPolyBodyNaryObserver.h"

// std
#include <vector>
#include <memory>

class ExportedByPolyBodyTools CATPolyBodyNaryObservers : public CATPolyBodyNaryObserver
{

public:

  ~CATPolyBodyNaryObservers();

public:
  void Push_Back(std::shared_ptr<CATPolyBodyNaryObserver> iObs);
  void Remove(std::shared_ptr<CATPolyBodyNaryObserver> iObs);

public:

  bool RequestGeometryEvents();

  unsigned int GetIndexOfOperandFromTag(const int iTag) const;

public:

  void Begins(CATPolyBodyOperandIterator & iOperands);

  void Result(CATPolyBody & iPolyBody, const CATMathTransformation * iPosition);

  void Ends(HRESULT hrRun);


public:

/** @name CATPolyVertex Events
    @{ */

  void BeginVertex(CATPolyCellPointIterator * iCellPoints);

  void EndVertex(CATPolyVertex * vertex, CATPolyBodyOperandCellIterator * iOperandCells);

/** @} */

public:

/** @name CATPolyEdge Events
    @{ */

  void BeginEdge();

  void AppendCurveVertex(const int cv, CATPolyCellPointIterator * iCellPoints);

  void EndEdge(CATPolyEdge * edge, CATPolyBodyOperandCellIterator * iOperandCells);

/** @} */

public:

/** @name CATPolyFace Events
    @{ */

  void BeginFace();

  void AddSurfaceVertex(const int sv, CATPolyCellPointIterator * iCellPoints);

  void AddTriangle(const int t, CATPolyFace * iFace, const int iFaceTriangle);

  void EndFace(CATPolyFace * face, CATPolyBodyOperandCellIterator * iOperandCells);

/** @} */

  /** @} */

public:

  /** @name CATPolyVolume Events
      @{ */

  void BeginVolume();

  void EndVolume(CATPolyVolume * volume, CATPolyBodyOperandCellIterator * iOperandCells);

  /** @} */

public:

/** @name Unedited Cell Events
    @{ */

  void UneditedSurface(CATPolyFace & iResultFace,
                       const CATPolyFace & iInputFace, const CATPolyBody & iInputBody, const int iInputTag,
                       int iOrientation, const CATMapOfIntToInt * iVertexMap);

  void UneditedCurves(CATPolyEdge & iResultEdge,
                      const CATPolyEdge & iInputEdge, const CATPolyBody & iInputBody, const int iInputTag,
                      int iOrientation);

  void UneditedPoints(CATPolyVertex & iResultVertex,
                      const CATPolyVertex & iInputVertex, const CATPolyBody & iInputBody, const int iInputTag);

/** @} */

public:
  /** @name Method to help for code factorisation. Not virtual
    @{ */
  void End(CATPolyVertex * iVertex, CATPolyBodyOperandCellIterator * iOperandCells);
  void End(CATPolyEdge * iEdge, CATPolyBodyOperandCellIterator * iOperandCells);
  void End(CATPolyFace * iFace, CATPolyBodyOperandCellIterator * iOperandCells);
  void End(CATPolyVolume * iVol, CATPolyBodyOperandCellIterator * iOperandCells);
/** @} */

public:
  // We can't cast it as a unary/binary observer.
  inline CATPolyBodyUnaryObserver* CastAsUnaryObserver () { return 0; }
  inline CATPolyBodyBinaryObserver* CastAsBinaryObserver () { return 0; }

private:
  std::vector<std::shared_ptr<CATPolyBodyNaryObserver> > _naryObs;
};

