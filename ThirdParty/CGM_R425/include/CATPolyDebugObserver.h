//=============================================================================
// COPYRIGHT Dassault Systemes 2017
//=============================================================================
//
// CATPolyDebugObserver.h
//
//=============================================================================
// 2017-10-04   JXO
//      * New
//=============================================================================
#ifndef CATPolyDebugObserver_H
#define CATPolyDebugObserver_H

#include "PolyMathUtils.h"

// Poly math
#include "CATPolyObserver.h"

// Math
class CATMathPoint;

/**
 * Implement this class and register your implementation with Poly::RegisterDebugObserver.
 */
class ExportedByPolyMathUtils CATPolyDebugObserver : public CATPolyObserver<CATPolyDebugObserver>
{
public:
  /** Will be called back as soon a point is captured */
  virtual void CapturePoint(const CATMathPoint & iPoint, int index, const char * iLabel, int iGroup) = 0;
  /** Will be called back as soon a point is captured */
  virtual void CaptureSegment(const CATMathPoint & iPoint1, const CATMathPoint & iPoint2, int index, const char * iLabel, int iGroup) = 0;
  /** Will be called back as soon a point is captured */
  virtual void CaptureTriangle(const CATMathPoint & iPoint1, const CATMathPoint & iPoint2, const CATMathPoint & iPoint3, int index, const char * iLabel, int iGroup) = 0;

protected:
  CATPolyDebugObserver();
  ~CATPolyDebugObserver();
public:
  /** @nodoc
   Don't use */
  void PrivateCapturePoint(const CATMathPoint & iPoint, int index, const char * iLabel, int iGroup);
  /** @nodoc
  Don't use */
  void PrivateCaptureSegment(const CATMathPoint & iPoint1, const CATMathPoint & iPoint2, int index, const char * iLabel, int iGroup);
  /** @nodoc
  Don't use */
  void PrivateCaptureTriangle(const CATMathPoint & iPoint1, const CATMathPoint & iPoint2, const CATMathPoint & iPoint3, int index, const char * iLabel, int iGroup);
};
#endif

