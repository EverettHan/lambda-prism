//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//=============================================================================
//
// CATPolyBodyBoundingEdgesChecker
//
// Check that surfaces have their bounding edges
//
//=============================================================================
// 2016-05-12 JXO: New.
//=============================================================================
#ifndef CATPolyBodyBoundingEdgesChecker_H
#define CATPolyBodyBoundingEdgesChecker_H

#include "PolyBodyTools.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATPolyBody;
class CATPolyFace;
class CATPolyBodyBoundingEdgesCheckerObserver;
class CATPolyBodyDiagnosis;


/**
 * This class checks that surfaces have their bounding edges.
 * It does not make the CATPolyBody invalid not to have edges,
 * but it would prevent it from being imported as a polyhedral CATBody.
 */
class ExportedByPolyBodyTools CATPolyBodyBoundingEdgesChecker
{
public:

/** @name Main Method
    @{ */

  /**
   * Performs the check.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *          The CATPolyBody has bounding edges.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          One or more surface has at least one free bar that is not bounding by a CATPolyEdge
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody
   *          or the check could not be completed.
   *   </ul>
   */
  static HRESULT Check (const CATPolyBody& iBody, CATPolyBodyBoundingEdgesCheckerObserver * pObserver = 0);

/** @} */

public:

/** @name Face Check
    @{ */

  /**
   * Performs the check for one face.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyFace passes this test.
   *          The CATPolyFace has bounding edges.
   *     <li> <tt>S_FALSE</tt> The CATPolyFace fails this test. 
   *          One or more free bar is not bounding by a CATPolyEdge
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyFace
   *          or the check could not be completed.
   *   </ul>
   */
  static HRESULT Check (const CATPolyFace& iFace, CATPolyBodyBoundingEdgesCheckerObserver * pObserver = 0, CATPolyBodyDiagnosis * pDiag = 0);

/** @} */


protected:
  CATPolyBodyBoundingEdgesChecker ();
  ~CATPolyBodyBoundingEdgesChecker ();

};

#endif // !CATPolyBodyBoundingEdgesChecker_H
