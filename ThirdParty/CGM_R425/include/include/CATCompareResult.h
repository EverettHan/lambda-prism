//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// CATCompareResult:
//
//=============================================================================
// Usage notes:
//=============================================================================
// June 2011     Creation                                               R1Y/XMH
// Feb. 2012     Modification to implement debug functions                  Q48
// Dec. 2016     Added outcomes for extrapolated surfaces.                  R1Y
// Sep. 2017     Added member data and functions for extrapolated surfaces. R1Y
// Feb. 2018     Added the function UpdateForCachedResult().                R1Y
// Apr. 2020     Added an overload of UpdateForCachedResult().              R1Y
//=============================================================================
#ifndef CATCompareResult_H
#define CATCompareResult_H

#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
#include "CATCGMOutput.h"

// Use the DEBUG_COMPAREGEOMETRY pre-processor flag to turn on/off debug of CompareGeometry
// Note: this is also used in CATCompareGeometry.h

//#define DEBUG_COMPAREGEOMETRY

#ifdef DEBUG_COMPAREGEOMETRY
// -----------------------------------------------
// Definition of a debug class for CompareGeometry
// -----------------------------------------------
class DebugCompareGeometry
{
public:
  
   DebugCompareGeometry();
   ~DebugCompareGeometry();
   
   int GetNumCalls() const;
   void IncrementNumCalls();
  
   void ResetNumCalls();
  
   void BlockReset(int);
   
private:
  
  int _numSetOutcomeCall; // count number of calls to CATCompareResult SetOutcome
  
  CATBoolean _locked; // stop the counter being reset
  int _numToReleaseLock;
};
#endif // DEBUG_COMPAREGEOMETRY

// --------------------------
// The CATCompareResult class
// --------------------------

 typedef enum { 
    CATCompare_Unknown,
    CATCompare_Same,
    CATCompare_Different,
    CATCompare_Smaller,
    CATCompare_Larger,
    CATCompare_NotImplemented,
    CATCompare_Error} CATCompareGeometryOutcome;

class ExportedByGeometricObjects CATCompareResult
{
public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  // Constructors
  INLINE CATCompareResult();
  INLINE CATCompareResult(const CATCompareGeometryOutcome & iOutcome);
  INLINE CATCompareResult(const CATBoolean iAllowSmaller,
                          const CATBoolean iAllowLarger);

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  INLINE CATCompareGeometryOutcome GetOutcome() const;
  CATBoolean SetOutcome(const CATCompareGeometryOutcome iOutcome);
  CATBoolean SetOutcome(const CATBoolean iAllowSame);
  INLINE void SetAllowSmaller(const CATBoolean iAllowSmaller);
  INLINE void SetAllowLarger(const CATBoolean iAllowLarger);
  INLINE void SetAllowSmallerAndLarger(const CATBoolean iAllowSmallerAndLarger);
  INLINE void SetEncounteredSmaller(const CATBoolean iEncounteredSmaller);
  INLINE void SetEncounteredLarger(const CATBoolean iEncounteredLarger);
  INLINE CATBoolean IsSame() const;
  INLINE CATBoolean IsSmallerStillAllowed() const;
  INLINE CATBoolean IsLargerStillAllowed() const;
  INLINE CATBoolean GetEncounteredSmaller() const;
  INLINE CATBoolean GetEncounteredLarger() const;
  void UpdateForSmallerAndLarger();
  CATBoolean UpdateForDependentOutcomes(const CATCompareResult & iResult);
  CATBoolean UpdateForCachedResult();
  CATBoolean UpdateForCachedResult(const CATCompareGeometryOutcome & iCachedOutcome);

private:

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------  
  CATCompareGeometryOutcome _Outcome;             // the overall outcome
  CATBoolean                _AllowSmaller;        // indicates whether an outcome of CATCompare_Smaller is currently permitted
  CATBoolean                _AllowLarger;         // indicates whether an outcome of CATCompare_Larger is currently permitted
  CATBoolean                _EncounteredSmaller;  // indicates whether an outcome of CATCompare_Smaller has been obtained in a comparison
  CATBoolean                _EncounteredLarger;   // indicates whether an outcome of CATCompare_Larger has been obtained in a comparison

#ifdef DEBUG_COMPAREGEOMETRY
  //-----------------------------------------------------------------------
  // DEBUG utility
  //-----------------------------------------------------------------------
public:
   
  void Debug_Reset();
  void Debug_SingleBlockReset();
  void Debug_TripleBlockReset();

private:
  static DebugCompareGeometry _Debug;

#endif // DEBUG_COMPAREGEOMETRY
};

//-----------------------------------------------------------------------
// Inline functions.
//-----------------------------------------------------------------------

INLINE CATCompareResult::CATCompareResult() :
_Outcome(CATCompare_Unknown),
_AllowSmaller(FALSE), _AllowLarger(FALSE),
_EncounteredSmaller(FALSE), _EncounteredLarger(FALSE)
{
}

INLINE CATCompareResult::CATCompareResult(const CATCompareGeometryOutcome & iOutcome) :
_Outcome(iOutcome),
_AllowSmaller(FALSE), _AllowLarger(FALSE),
_EncounteredSmaller(FALSE), _EncounteredLarger(FALSE)
{
}

INLINE CATCompareResult::CATCompareResult(const CATBoolean iAllowSmaller,
                                          const CATBoolean iAllowLarger) :
_Outcome(CATCompare_Unknown),
_AllowSmaller(iAllowSmaller), _AllowLarger(iAllowLarger),
_EncounteredSmaller(FALSE), _EncounteredLarger(FALSE)
{
}

INLINE CATCompareGeometryOutcome CATCompareResult::GetOutcome() const
{
  return _Outcome;
}

INLINE void CATCompareResult::SetAllowSmaller(const CATBoolean iAllowSmaller)
{
  _AllowSmaller = iAllowSmaller;
}

INLINE void CATCompareResult::SetAllowLarger(const CATBoolean iAllowLarger)
{
  _AllowLarger = iAllowLarger;
}

INLINE void CATCompareResult::SetAllowSmallerAndLarger(const CATBoolean iAllowSmallerAndLarger)
{
  _AllowSmaller = iAllowSmallerAndLarger;
  _AllowLarger  = iAllowSmallerAndLarger;
}

INLINE void CATCompareResult::SetEncounteredSmaller(const CATBoolean iEncounteredSmaller)
{
  _EncounteredSmaller = iEncounteredSmaller;
}

INLINE void CATCompareResult::SetEncounteredLarger(const CATBoolean iEncounteredLarger)
{
  _EncounteredLarger = iEncounteredLarger;
}

INLINE CATBoolean CATCompareResult::IsSame() const
{
  return (_Outcome == CATCompare_Same);
}

INLINE CATBoolean CATCompareResult::IsSmallerStillAllowed() const
{
  return (_AllowSmaller && !_EncounteredLarger);
}

INLINE CATBoolean CATCompareResult::IsLargerStillAllowed() const
{
  return (_AllowLarger && !_EncounteredSmaller);
}

INLINE CATBoolean CATCompareResult::GetEncounteredSmaller() const
{
  return _EncounteredSmaller;
}

INLINE CATBoolean CATCompareResult::GetEncounteredLarger() const
{
  return _EncounteredLarger;
}
#endif
