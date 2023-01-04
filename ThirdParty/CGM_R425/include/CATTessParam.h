//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessParam
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef CATTessParam_H
#define CATTessParam_H

#include "TessCacheObjects.h"
#include "CATMathInline.h"
#include "CATMathConstant.h"
#include "CATMathLimits.h"
#include "CATBoolean.h"
#include "CATMathFP.h"

class CATCGMStream;

// See CATTessSettings for the default values.
#define CATTessParam_Step_Default (float) CATMathInfinite
#define CATTessParam_MaxAngle_Default (float) (CATPI * 0.25)
#define CATTessParam_ComputeIsopar_Default 0
#define CATTessParam_NbIsoparU_Default 2
#define CATTessParam_NbIsoparV_Default 3

#define CATTessParam_OutputMode_Default CATTessParam::MIXED_MODE


class ExportedByTessCacheObjects CATTessParam
{
public:

  // These Customs Definitions give predefined meaning to the tess params.
  //
  // STANDARD:
  //    Sag = 0.2, Step = Infinite, MaxAngle = PI/4 (Visu. defaults), OutputMode = CATTessParam_OutputMode_Default (defined above)
  // DENSE:
  //    Sag = CellBoxSize/200.0, Step = CellBoxSize/4.0, MaxAngle = PI/8, OutputMode = ISOLATED_TRIANGLES_MODE
  // SPARSE:
  //    Sag = CellBoxSize/200.0, Step = Infinite, MaxAngle = PI/8, OutputMode = ISOLATED_TRIANGLES_MODE
  // UV:
  //    Sag = user given, Step = Infinite, MaxAngle = PI/8, OutputMode = ISOLATED_TRIANGLES_MODE
  // UNKNOWN: (for internal use)
  //    Sag, Step, MaxAngle, OutputMode as given by user

  enum CustomDefinition
  {
    UNKNOWN, // (for internal use)
    STANDARD,
    DENSE,
    SPARSE,
    UV
  };

public:

  // Tessellation Output Modes

  enum OutputMode
  {
    UNKNOWN_MODE,            // (for internal use)
    MIXED_MODE,              // Stripes, Fans and isolated triangles
    ISOLATED_TRIANGLES_MODE, // Only isolated triangles
    STRIPS_MODE              // Only stripes
  };

public:

  // Construct CATTessParam with explicit parameter values

  INLINE CATTessParam(
            float iSag, 
            float iStep = CATTessParam_Step_Default, 
            float iMaxAngle = CATTessParam_MaxAngle_Default,
            OutputMode iOutputMode = CATTessParam_OutputMode_Default);

  // Construct CATTessParam with a custom definition

  INLINE CATTessParam(CustomDefinition iCustomDefn); // Don't pass UNKNOWN or UV

  
  // Construct CATTessParam for UV

  INLINE CATTessParam(float iTargetSagForMesh0, unsigned short iTargetRefinementLevelForMesh0);

  
  // Returns TRUE if the other CATTessParam is practically same as this one

  CATBoolean IsEqualTo(
            const CATTessParam& iOther, 
            float iLengthTol, 
            float iAngleTol) const;

public:

/** @name Set methods
    @{ */

  /**
   * Sets a specific sag for the tessellation of curves. 
   */
  INLINE void SetSag1D (float iSag);

  /**
   * Sets a specific sag for the tessellation of surfaces. 
   */
  INLINE void SetSag2D (float iSag);

  /**
   * Sets the step size. 
   */
  INLINE void SetStep (float iSag);

  /**
   * Sets the maximum angle. 
   */
  INLINE void SetMaxAngle (float iMaxAngle);

  /**
   * Do compute isoparametric lines.
   * @see CATTessSettings
   */
  INLINE void DoComputeIsopar (unsigned short iIsoparSetting);

  /**
   * Sets the number of isoparametric lines (u parameter).
   */
  INLINE void SetNbIsoparU (unsigned short iNbIsoU);
  
  /**
   * Sets the number of isoparametric lines (v parameter).
   */
  INLINE void SetNbIsoparV (unsigned short iNbIsoV);

  INLINE void SetTargetRefinementLevelForMesh0 (unsigned short iLevel);  // Should this be exposed in this class? -NDO

  /**
   * Sets the CGM level (obtained from a CATSoftwareConfiguration.)
   */
  INLINE void SetCGMLevel (const short iCGMLevel);

/** @} */

public:

/** @name Query methods
    @{ */

  /**
   * Returns the sag for the tessellation of surfaces. 
   */
  INLINE float GetSag() const;

  /**
   * Returns the sag for the tessellation of curves. 
   */
  INLINE float GetSag1D () const;

  /**
   * Returns the sag for the tessellation of surfaces. 
   */
  INLINE float GetSag2D () const;

  /**
   * Returns the step size. 
   */
  INLINE float GetStep() const;

  /**
   * Returns the angle not to be exceeded. 
   */
  INLINE float GetMaxAngle() const;

  /**
   * Returns the setting for the computation of the isoparametric lines.
   */
  INLINE unsigned short GetIsoparSetting () const;

  /**
   * Returns the number of isoparametric lines (u parameter).
   */
  INLINE unsigned short GetNbIsoparU() const;

  /**
   * Returns the number of isoparametric lines (v parameter).
   */
  INLINE unsigned short GetNbIsoparV() const;

  INLINE float GetTargetSagForMesh0() const;            // Should this be exposed in this class? -NDO
  INLINE int GetTargetRefinementLevelForMesh0() const;  // Should this be exposed in this class? -NDO

  /**
   * Returns the CGM level (for setting a CATSoftwareConfiguration.)
   */
  INLINE short GetCGMLevel () const;

  INLINE CustomDefinition GetCustomDefinition() const;

  INLINE OutputMode GetOutputMode() const;

/** @} */

public:

  INLINE CATTessParam(); // default constructor (creates a STANDARD definition)
  INLINE ~CATTessParam();

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:
  
  CustomDefinition _CustomDefn;
  OutputMode _OutputMode;

  // The following members are not used if _CustomDefn is set to STANDARD, DENSE or SPARSE
  // They are used only if _CustomDefn is set to UNKNOWN
  float _Sag1D;  // Sag for the tessellation of curves.
  float _Sag2D;  // Sag for the tessellation of surfaces.
  float _Step;
  float _MaxAngle;

  unsigned short _IsoparSetting;
  unsigned short _NbIsoparU;
  unsigned short _NbIsoparV;

  // The following is used when _CustomDefn is UV
  unsigned short _TargetRefinementLevelForMesh0;

  short _CGMLevel;  // The level from the CATSoftwareConfiguration.

  // Note to future developer(s): If data members in this class are changed/added/removed, in future,
  // then do not forget to update the CATTessParamAttribute::Stream/UnStream code appropriately.
};

INLINE 
CATTessParam::CATTessParam(CustomDefinition iCustomDefn)
:
_Sag1D(0.0f), 
_Sag2D (0), 
_Step(0.0f), 
_MaxAngle(0.0f),
_IsoparSetting (0),
_NbIsoparU (0),
_NbIsoparV (0),
_TargetRefinementLevelForMesh0 (0),
_CGMLevel (0),
_OutputMode(UNKNOWN_MODE),
_CustomDefn(iCustomDefn)
{
}

INLINE 
CATTessParam::CATTessParam(float iSag, float iStep, float iMaxAngle, OutputMode iOutputMode)
:
_Sag1D(iSag), 
_Sag2D (iSag),
_Step(iStep), 
_MaxAngle(iMaxAngle),
_IsoparSetting (CATTessParam_ComputeIsopar_Default),
_NbIsoparU (CATTessParam_NbIsoparU_Default),
_NbIsoparV (CATTessParam_NbIsoparV_Default),
_TargetRefinementLevelForMesh0 (0),
_CGMLevel (0),
_OutputMode(iOutputMode),
_CustomDefn(UNKNOWN)
{
}

INLINE 
CATTessParam::CATTessParam(float iTargetSagForMesh0, unsigned short iTargetRefinementLevelForMesh0)
:
_Sag1D(iTargetSagForMesh0), 
_Sag2D (iTargetSagForMesh0), 
_Step(CATTessParam_Step_Default), 
_MaxAngle(CATTessParam_MaxAngle_Default),
_IsoparSetting (CATTessParam_ComputeIsopar_Default),
_NbIsoparU (CATTessParam_NbIsoparU_Default),
_NbIsoparV (CATTessParam_NbIsoparV_Default),
_TargetRefinementLevelForMesh0 (iTargetRefinementLevelForMesh0),
_CGMLevel (0),
_OutputMode(ISOLATED_TRIANGLES_MODE),
_CustomDefn(UV)
{
}

INLINE 
CATTessParam::CATTessParam()
:
_Sag1D(0.0f), 
_Sag2D (0), 
_Step(0.0f), 
_MaxAngle(0.0f),
_IsoparSetting (0),
_NbIsoparU (0),
_NbIsoparV (0),
_TargetRefinementLevelForMesh0 (0),
_CGMLevel (0),
_OutputMode(UNKNOWN_MODE),
_CustomDefn(STANDARD)
{
}

INLINE 
CATTessParam::~CATTessParam()
{
}

INLINE CATTessParam::CustomDefinition 
CATTessParam::GetCustomDefinition() const
{
  return _CustomDefn;
}

INLINE void CATTessParam::SetSag1D (float iSag)
{
  _Sag1D = iSag;
}

INLINE void CATTessParam::SetSag2D (float iSag)
{
  _Sag2D = iSag;
}

INLINE void CATTessParam::SetStep (float iStep)
{
  _Step = iStep;
}

INLINE void CATTessParam::SetMaxAngle (float iMaxAngle)
{
  _MaxAngle = iMaxAngle;
}

INLINE void CATTessParam::DoComputeIsopar (unsigned short iIsoparSetting)
{
  _IsoparSetting = iIsoparSetting;
}

INLINE void CATTessParam::SetNbIsoparU (unsigned short iNbIsoU)
{
  _NbIsoparU = iNbIsoU;
}

INLINE void CATTessParam::SetNbIsoparV (unsigned short iNbIsoV)
{
  _NbIsoparV = iNbIsoV;
}

INLINE void CATTessParam::SetTargetRefinementLevelForMesh0 (unsigned short iTargetLevel)
{
  _TargetRefinementLevelForMesh0 = iTargetLevel;
}

INLINE void CATTessParam::SetCGMLevel (const short iCGMLevel)
{
  _CGMLevel = iCGMLevel;
}

INLINE float 
CATTessParam::GetSag() const
{
  return _Sag2D;
}

INLINE float 
CATTessParam::GetSag1D() const
{
  return _Sag1D;
}

INLINE float 
CATTessParam::GetSag2D() const
{
  return _Sag2D;
}

INLINE float 
CATTessParam::GetStep() const
{
  return _Step;
}

INLINE float 
CATTessParam::GetMaxAngle() const
{
  return _MaxAngle;
}

INLINE unsigned short CATTessParam::GetIsoparSetting () const
{
  return _IsoparSetting;
}

INLINE unsigned short CATTessParam::GetNbIsoparU() const
{
  return _NbIsoparU;
}

INLINE unsigned short CATTessParam::GetNbIsoparV() const
{
  return _NbIsoparV;
}

INLINE float 
CATTessParam::GetTargetSagForMesh0() const
{
  return _Sag2D;
}

INLINE int 
CATTessParam::GetTargetRefinementLevelForMesh0() const
{
  return _TargetRefinementLevelForMesh0;
}

INLINE short CATTessParam::GetCGMLevel () const
{
  return _CGMLevel;
}

INLINE CATTessParam::OutputMode 
CATTessParam::GetOutputMode() const
{
  return _OutputMode;
}

#endif // !CATTessParam_H

