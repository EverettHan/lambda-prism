// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyConcatenateUnaryObserver.h
//
//===================================================================
// April 2018 Creation: JXO
//===================================================================
#ifndef CATPolyBodyConcatenateUnaryObserver_H
#define CATPolyBodyConcatenateUnaryObserver_H

// ExportedBy
#include "PolyBodyTools.h"

// Poly
#include "CATPolyBodyUnaryObserver.h"

// System
#include "CATErrorDef.h"   // For the definition of HRESULT.
#include "CATBoolean.h"
#include "CATListPV.h"

/**
 * Helper class in case you have an operator that calls several other operators but you were given a single Unary observer by the caller/application.
 * In this case you have to chain the calls to the operators with this Unary observer, call NextRun between each call, and call Concatenate at the end.
 * For example:
 * void A::Run(CATPolyBodyUnaryObserver & iObs)
 * {
 *   CATPolyBodyConcatenateUnaryObserver concatobserver(iObs);
 *   B::Run(concatobserver);
 *   concatobserver.NextRun();
 *   C::Run(concatobserver);
 *   concatobserver.Concatenate();
 * }
 */
class ExportedByPolyBodyTools CATPolyBodyConcatenateUnaryObserver : public CATPolyBodyUnaryObserver
{
public:
  CATPolyBodyConcatenateUnaryObserver(CATPolyBodyUnaryObserver & iObs);
  ~CATPolyBodyConcatenateUnaryObserver();
  /**
   * Call this in between two operator calls
   * Note that if no Begins event has been called on this CATPolyBodyConcatenateUnaryObserver (it may be outside of your control),
   * you have to call NextRun to fire-up the observer before any operator call.
   */
  void NextRun();
  /**
   * Call that to be called back on all the events on iObs.
   * @param iBodyEvents
   *        Set that to FALSE if iObs already reports CATPolyBody events (Begins, Result and Ends) without your control.
   *        Default is TRUE.
   */
  void Concatenate(CATBoolean iBodyEvents = TRUE);

  /** CATPolyBodyUnaryObserver implementations: */
  /** Note: currently the geometry events are not treated!! */
  bool RequestGeometryEvents ();
  void Begins (const CATPolyBody& iOperand, const CATMathTransformation* iPosition, const int iTag);
  void Result (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);
  void Ends (HRESULT hrRun);
  void BeginVertex (const CATPolyCellPoint* iPoint);
  void EndVertex (CATPolyVertex* vertex, CATPolyCell* iCellOperand);
  void BeginEdge ();
  void AppendCurveVertex (const int cv, const CATPolyCellPoint* iPoint);
  void EndEdge (CATPolyEdge* edge, CATPolyCell* iCellOperand);
  void BeginFace ();
  void AddSurfaceVertex (const int sv, const CATPolyCellPoint* iPoint);
  void AddTriangle (const int t, CATPolyFace* iFace, const int iFaceTriangle);
  void EndFace (CATPolyFace* face, CATPolyFace* iFaceOperand);

  void UneditedSurface (CATPolyFace& iResultFace,
                        const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                        int iOrientation, const CATMapOfIntToInt* iVertexMap);

  void UneditedCurves (CATPolyEdge& iResultEdge,
                       const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                       int iOrientation);

  void UneditedPoints (CATPolyVertex& iResultVertex,
                       const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag);

private:
  struct CurrentRun;
  CurrentRun * m_cur;
  CurrentRun * m_prev;
  CATPolyBodyUnaryObserver & m_obs;
  bool m_RequestGeometryEvents;
};

#endif
