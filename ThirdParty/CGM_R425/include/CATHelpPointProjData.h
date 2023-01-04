#ifndef CATHelpPointProjData_H
#define CATHelpPointProjData_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATHelpPointProjData:
//    Header file for the CATHelpPointProjData class.
//    This class relates to the projection of a help point onto two
//    multi-surfaces.
//    The global U- and V-parameter values for a multi-surface are the same as
//    the corresponding local parameter values.
//
//=============================================================================
// Usage notes:
//=============================================================================
// 26/06/17 : R1Y : Creation.
//=============================================================================

// The enumeration for projection states.
// Note that the order must be preserved, as it used in streaming.
enum CATHelpPointProjState { NotProjected = 0,
                             ProjectionSucceeded,
                             ProjectionFailed };

// The class that relates to the projection of a help point onto two multi-surfaces.
class CATHelpPointProjData
{
private:
  // Default constructor.
  CATHelpPointProjData();

public:
  // Standard constructor.
  INLINE CATHelpPointProjData(const CATHelpPointProjState iProjState1,
                              const CATHelpPointProjState iProjState2,
                              const double                iParamU1,
                              const double                iParamV1,
                              const double                iParamU2,
                              const double                iParamV2,
                              const CATLONG32             iIndexU1,
                              const CATLONG32             iIndexV1,
                              const CATLONG32             iIndexU2,
                              const CATLONG32             iIndexV2);

  // Function to get the projection state of the help point for the first multi-surface.
  INLINE CATHelpPointProjState GetProjState1() const;

  // Function to get the projection state of the projected point for the second multi-surface.
  INLINE CATHelpPointProjState GetProjState2() const;

  // Function to get the U-parameter value of the projected point for the first multi-surface.
  INLINE double GetParamU1() const;

  // Function to get the V-parameter value of the projected point for the first multi-surface.
  INLINE double GetParamV1() const;

  // Function to get the U-parameter value of the projected point for the second multi-surface.
  INLINE double GetParamU2() const;

  // Function to get the V-parameter value of the projected point for the second multi-surface.
  INLINE double GetParamV2() const;

  // Function to get the U-parameter index of the projected point for the first multi-surface.
  INLINE CATLONG32 GetIndexU1() const;

  // Function to get the V-parameter index of the projected point for the first multi-surface.
  INLINE CATLONG32 GetIndexV1() const;

  // Function to get the U-parameter index of the projected point for the second multi-surface.
  INLINE CATLONG32 GetIndexU2() const;

  // Function to get the V-parameter index of the projected point for the second multi-surface.
  INLINE CATLONG32 GetIndexV2() const;

private:
  CATHelpPointProjState _ProjState1;  // the projection state of the help point for the first multi-surface
  CATHelpPointProjState _ProjState2;  // the projection state of the help point for the second multi-surface
  double                _ParamU1;     // the U-parameter value of the projected point for the first multi-surface
  double                _ParamV1;     // the V-parameter value of the projected point for the first multi-surface
  double                _ParamU2;     // the U-parameter value of the projected point for the second multi-surface
  double                _ParamV2;     // the V-parameter value of the projected point for the second multi-surface
  CATLONG32             _IndexU1;     // the U-parameter index of the projected point for the first multi-surface
  CATLONG32             _IndexV1;     // the V-parameter index of the projected point for the first multi-surface
  CATLONG32             _IndexU2;     // the U-parameter index of the projected point for the second multi-surface
  CATLONG32             _IndexV2;     // the V-parameter index of the projected point for the second multi-surface
};

//-----------------------------------------------------------------------------------------
// Standard constructor.
//-----------------------------------------------------------------------------------------
INLINE CATHelpPointProjData::CATHelpPointProjData(const CATHelpPointProjState iProjState1,
                                                  const CATHelpPointProjState iProjState2,
                                                  const double                iParamU1,
                                                  const double                iParamV1,
                                                  const double                iParamU2,
                                                  const double                iParamV2,
                                                  const CATLONG32             iIndexU1,
                                                  const CATLONG32             iIndexV1,
                                                  const CATLONG32             iIndexU2,
                                                  const CATLONG32             iIndexV2) :
_ProjState1(iProjState1), _ProjState2(iProjState2),
_ParamU1(iParamU1), _ParamV1(iParamV1), _ParamU2(iParamU2), _ParamV2(iParamV2),
_IndexU1(iIndexU1), _IndexV1(iIndexV1), _IndexU2(iIndexU2), _IndexV2(iIndexV2)
{
}

//-----------------------------------------------------------------------------------------
// Function to get the projection state of the help point for the first multi-surface.
//-----------------------------------------------------------------------------------------
INLINE CATHelpPointProjState CATHelpPointProjData::GetProjState1() const
{
  return _ProjState1;
}

//-----------------------------------------------------------------------------------------
// Function to get the projection state of the help point for the second multi-surface.
//-----------------------------------------------------------------------------------------
INLINE CATHelpPointProjState CATHelpPointProjData::GetProjState2() const
{
  return _ProjState2;
}

//-----------------------------------------------------------------------------------------
// Function to get the U-parameter value of the projected point for the first multi-surface.
//-----------------------------------------------------------------------------------------
INLINE double CATHelpPointProjData::GetParamU1() const
{
  return _ParamU1;
}

//-----------------------------------------------------------------------------------------
// Function to get the V-parameter value of the projected point for the first multi-surface.
//-----------------------------------------------------------------------------------------
INLINE double CATHelpPointProjData::GetParamV1() const
{
  return _ParamV1;
}

//-----------------------------------------------------------------------------------------
// Function to get the U-parameter value of the projected point for the second multi-surface.
//-----------------------------------------------------------------------------------------
INLINE double CATHelpPointProjData::GetParamU2() const
{
  return _ParamU2;
}

//-----------------------------------------------------------------------------------------
// Function to get the V-parameter value of the projected point for the second multi-surface.
//-----------------------------------------------------------------------------------------
INLINE double CATHelpPointProjData::GetParamV2() const
{
  return _ParamV2;
}

//-----------------------------------------------------------------------------------------
// Function to get the U-parameter index of the projected point for the first multi-surface.
//-----------------------------------------------------------------------------------------
INLINE CATLONG32 CATHelpPointProjData::GetIndexU1() const
{
  return _IndexU1;
}

//-----------------------------------------------------------------------------------------
// Function to get the V-parameter index of the projected point for the first multi-surface.
//-----------------------------------------------------------------------------------------
INLINE CATLONG32 CATHelpPointProjData::GetIndexV1() const
{
  return _IndexV1;
}

//-----------------------------------------------------------------------------------------
// Function to get the U-parameter index of the projected point for the second multi-surface.
//-----------------------------------------------------------------------------------------
INLINE CATLONG32 CATHelpPointProjData::GetIndexU2() const
{
  return _IndexU2;
}

//-----------------------------------------------------------------------------------------
// Function to get the V-parameter index of the projected point for the second multi-surface.
//-----------------------------------------------------------------------------------------
INLINE CATLONG32 CATHelpPointProjData::GetIndexV2() const
{
  return _IndexV2;
}

#endif
