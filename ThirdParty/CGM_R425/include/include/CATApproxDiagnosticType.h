#ifndef CATApproxDiagnosticType_H
#define CATApproxDiagnosticType_H

// Allow to understand the output bitmask of GetDiagnostic

// if (Approx.GetDiagnostic() & CATApproxDiagnostic_VerticalTangencyDetected)
// a vertical tangency has been found

// if (Approx.GetDiagnostic() & CATApproxDiagnostic_SegmentTooSmall)
// a small segment has benn detected

// if (Approx.GetDiagnostic() & CATApproxDiagnostic_MaxNumberOfSegmentReached) 
// the max number of segment has been reached

// if (Approx.GetDiagnostic() & CATApproxDiagnostic_TooManyVerticalTangencies) 
// more than 2 vertical tangents have been detected and the max number of segment
// is at least 64 (R14 level)


 enum CATApproxDiagnostic{
  CATApproxDiagnostic_NoInfo = 0, 
  CATApproxDiagnostic_VerticalTangencyDetected = 1, 
  CATApproxDiagnostic_SegmentTooSmall = 2, 
  CATApproxDiagnostic_MaxNumberOfSegmentReached = 4,
  CATApproxDiagnostic_TooManyVerticalTangencies = 8
};

#endif
