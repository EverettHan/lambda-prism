//=============================================================================
// COPYRIGHT Dassault Systemes 2016
//=============================================================================
//
// CATProgressCallbackAdapter.h
//
//=============================================================================
// 2016-02-18   JXO
//      * New
//=============================================================================

#ifndef CATProgressCallbackAdapter_h
#define CATProgressCallbackAdapter_h

// ExportedBy
#include "PolyBodyTools.h"

// Math
#include "CATProgressCallback.h"
#include "CATCGMProgressBar.h"

// System
#include "CATBoolean.h"


/**
 * Class to have a CATProgressCallback from a CATCGMProgressBar
 */
class ExportedByPolyBodyTools CATProgressCallbackAdapter : public CATProgressCallback
{
public :
  /**
   * Constructs a CATProgressCallback.
   */
  CATProgressCallbackAdapter (CATCGMProgressBar & iBar);

  /** Destructor */
  virtual ~CATProgressCallbackAdapter ();


  CATBoolean SetProgress (const double       iValue,
                          const double       iTotalValue         = 100.0);

private:
  CATCGMProgressBar & m_bar;

};

/** Odd implementation for those who do not want to add CATMathStream
 * in their framework prereqs (but has PolyhedralObjects in it).
 */
class ExportedByPolyBodyTools CATPolyProgressCallback : public CATProgressCallback
{
public :
  /**
   * Constructs a CATProgressCallback.
   */
  CATPolyProgressCallback (CATProgressCallback * iParentProgressBar = 0, const double iStartPercentage = 0.0, const double iEndPercentage = 100.0);

  /** Destructor */
  virtual ~CATPolyProgressCallback ();

  virtual CATBoolean Callback (const double iProgressPercentage = 0.);
  virtual CATBoolean SetProgress (const double       iValue,
                                  const double       iTotalValue         = 100.0);

  void SetMinimumStep (const double iMinimumStep);
  void AddRef () const;
  void Release () const;
};


#endif
