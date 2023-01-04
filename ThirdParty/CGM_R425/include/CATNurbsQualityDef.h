#ifndef CATNurbsQualityDef_h_
#define CATNurbsQualityDef_h_

typedef enum 
{
  CATGeometricalNurbsDiagnostic_ArcOrPatchTooSmall,
  CATGeometricalNurbsDiagnostic_CurveOrSurfaceTooSmall,
  CATGeometricalNurbsDiagnostic_ExternalNullTangent,
  CATGeometricalNurbsDiagnostic_InnerCuspOrTwist,
  CATGeometricalNurbsDiagnostic_OuterCuspOrTwist,
  CATGeometricalNurbsDiagnostic_ControlPointsOutOfSpace,
  CATGeometricalNurbsDiagnostic_MicroCurvature,
  CATGeometricalNurbsDiagnostic_BadParametrization,
  CATGeometricalNurbsDiagnostic_PointingSurface
} CATGeometricalNurbsDiagnosticType;

typedef enum 
{
  CATGeometricalNurbsDiagnostic_Error,
  CATGeometricalNurbsDiagnostic_Warning
} CATGeometricalNurbsDiagnosticSeverity;

// hln Cusp
// NormalCheck is the default mode. Only information necessary to detect a diagnostic are searched.
// FullCheck enables search of complementary information necessary to achieve a correction of the geometry if
// requested.It is currently necessary only for the following types to correct :
// . InnerCuspOrTwist
typedef enum 
{
  CATGeometricalNurbsDiagnostic_NormalCheck,
  CATGeometricalNurbsDiagnostic_FullCheck
} CATGeometricalNurbsDiagnosticCheckMode;

#endif /* CATNurbsQualityDef_h_ */
