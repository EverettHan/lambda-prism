// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATGeoOpDebug:
//  - Debug class for geometric operators
//=============================================================================
//=============================================================================
// Usage notes:
//  set GeopTrace=EXTCRV=3,ALL=2,SSGEN=4
//=============================================================================
// 22/08/12 R1Y Added additional debug functionality.
// 02/10/12 Q48 Functionality to activate debug functions from environment
// 11/10/12 Q48 Added utility functions to convert to string
// 30/01/13 XMH Add FIL category
// 08/02/13 Q48 Move global variables to public enum scoped by class
// 19/02/13 R1Y Added the PLSINT category. 
// 14/06/13 R1Y Added the SSVOB category for visual debug.
// 19/06/13 R1Y Added CurveType() and SurfaceType().
// 28/06/13 R1Y Added the CSINT category for visual debug and GEOPDEBUG_IF_TYPE_CMD.
// 18/07/13 Q48 Added PCrvPCrvINT trace category
// 23/08/13 Q48 Added SSINT_DumpPrecision function category to increase precision in replays
// 30/08/13 Q48 Added COUNT level for trace
// 02/09/13 Q48 Added GeopTracePrecision flag to set the default number of trace decimal places 
// 01/10/13 Q48 Added trace functions for int
// 09/10/13 Q48 Moved static (debug) GetIntersectionSignString from CATSurSurResultPoint
// 10/10/13 Q48 Added COUNT mechanism to print number of operator calls
// 15/10/13 XMH Add point plotting functions
// 24/10/13 R1Y Added the category DENV, and the macros GEOPDEBUG_GET_INTEGER_ENV_VAR and GEOPDEBUG_GET_DOUBLE_ENV_VAR
// 30/10/13 Q48 Added visual debug and operator count for SSGEN
// 31/10/13 Q48 Added visual utility functions
// 17/12/13 Q48 Added utility methods, trace and function categories and methods for printing tags
// 13/02/14 Q48 Rearchitecture to avoid string comparison, add utilities for workbench and add output to file
// 17/03/14 Q48 Added APPROX trace category for JSX
// 11/04/14 Q48 Added ASINT categories for self-intersection
// 02/05/14 R1Y Added DrawSurfaceLimits() and EXTSUR categories for extrapolating surfaces.
// 19/05/14 R1Y Removed SSTAN_ReplaceTangentOp (IR-279026)
// 18/06/14 Q48 Add trace functions
// 10/07/14 R1Y Added the CSPROJ category for F1Z.
// 22/07/14/R1Y Added DrawPointOnCurve() and DrawPointAndTangentOnPCurve().
// 25/11/14 F1Z Added CPLPROJ trace category and macros for shift display
// 22/01/14 R1Y Added functions for printing sets of points with tangents and vectors
// 30/07/15 R1Y Added PrintArrayOfMarchingDiagnostics()
// 27/08/15 XMH Added CLASH2D_UseGenericIntersectors
// 02/12/15 XMH Added DrawBox. CLASH2D visual categories.
// 07/12/15 XMH Added CLASH2D env var
// 21/04/17 PKC compilation warning
// 02/04/19 Q48 Added mechanism to capture specific replay
// 04/07/19 Q48 Added cache of versioning flag set in environment CGM_Versionning
// 04/07/19 Q48 Moved constructors to protected - only access via GetGeoOpDebug
// 04/07/19 Q48 Added summary mechanism - to print a summary of an object (eg CATMathSetOfPointsND)
// 08/07/19 Q48 Performance of manual versioning mechanism (now use class not strings)
// 17/12/20 R1Y Added DrawArrowOnPCurve().
// 06/05/22 NLD Lines split to maximum column range for macros readability/maintainability
// 13/09/22 R1Y Added the trace category THINLOOP.
//=============================================================================
#ifndef CATGeoOpDebug_H
#define CATGeoOpDebug_H

//=============================================================================
// The main define to activate the debug trace
//=============================================================================
#include "CATGeoOpDebugDeclare.h" // N.B activation in level 2 file CATGeoOpDebugSwitch.h

//=============================================================================

// ExportedBy
#include "Y3DYNOPE.h"

// System
#include "CATTrace.h"
#include "CATUnicodeString.h"

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATString.h"

// Stream
#include "CATCGMStream.h"

// Mathematics
#include "CATTolerance.h"
#include "CATCGMVirtual.h"
#include "CATCGMOutput.h" 
#include "CATMathODT.h"
#include "CATMathDiagnostic.h"
#include "CATMathStopDiagnostic.h"
#include "CATThrowForNullPointer.h"
#include "CATMathSetOfLongs.h"
class CATMathFunctionX;
class CATMathInterval;
class CATMathInterval2D;
class CATMathIntervalND;
class CATMathPoint;
class CATMathPoint2D;
class CATMathDirection;
class CATMathDirection2D;
class CATMathVector;
class CATMathVector2D;
class CATMathCurve;
class CATMathCircle;
class CATMathLine;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDTwoTangents;
class CATMathSetOfPointsNDWithVectors;
class CATMathNxNFullMatrix;
class CATMathTransformation2D;
class CATMathBox;
class CATMathAABB;
class CATMathOBB;
class CATMathOBBCloud;
class CATMathOBB2D;
class CATMathPlane;

class CATMathImplicitSystem;

// Geometric Objects
#include "CATGeometry.h"
#include "CATSurface.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATIsoParameter.h"
class CATCartesianPoint;
class CATVirtualCurve;
class CATCurve;
class CATLine;
class CATCircle;
class CATNurbsCurve;
class CATSplineCurve;
class CATPLine;
class CATPCurve;
class CATPCircle;
class CATPSpline;
class CATPNurbs;
class CATEdgeCurve;
class CATVirtualCurve;
class CATOffsetSurface;
class CATNurbsSurface;
class CATSweepSurface;
class CATChamferSurface;
class CATFilletSurface;
class CATGenericFillet;
class CATGenericRuledSurface;
//class CATCrvParam;
class CATCrvLimits;
class CATVirtualCrvParam;
class CATSurLimits;
class CATSetOfCrvParams;
class CATSetOfSurParams;
class CATPoint;
class CATPointOnCurve;
class CATPointOnSurface;
class CATCGMOperator;

// Geometric Operators
class CATGeoOperator;
#include "CATCivilCurveDefProtected.h"
#include "CATCivilCurveDef.h"
#include "CATClash2D.h"

// Lists
#include "CATListOfInt.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATSurfaces.h"

// GMModelInterfaces
#include "CATIntersectionSign.h"

// Geometric Operators
#include "CATGeoOpAllTimers.h"

// Visual Interactive Debug
#include "CATCGMDebugUI.h"
class CATCGMDocument;
class CATTrace;
class CATCGMActivateDebug;

// Call stack debug
#include "CATCompactCallStackManager.h"

#ifdef GEOPDEBUG
#define CHECK_DEBUGACTIVE(Type, Category, Level)          (tra && tra->DebugActive(CATGeoOpDebug::TYPE::Type,                          \
                                                                                   CATGeoOpDebug::Type::Category,                      \
                                                                                   CATGeoOpDebug::Type::Level))                        //

#define GETGEOPDEBUG(Var)                                 CATGeoOpDebug * Var = CATGeoOpDebug::GetGeoOpDebug()                         //

#define GEOPDEBUG_ENDL(Category, Level)                   { if (CHECK_DEBUGACTIVE(TRACE, Category, Level))                             \
                                                            {  tra->OutputBlankLine(CATGeoOpDebug::TRACE::Category,                    \
                                                                                    CATGeoOpDebug::TRACE::Level); } }                  //
#define GEOPDEBUG_IF_ENDL(Category, Level, Cond)          { if (Cond) GEOPDEBUG_ENDL(Category, Level) }                                //
#define GEOPDEBUG_END_HEAD(Category, Level)               { if (CHECK_DEBUGACTIVE(TRACE, Category, Level))                             \
                                                            { tra->OutputHeaderLine(CATGeoOpDebug::TRACE::Category,                    \
                                                                                    CATGeoOpDebug::TRACE::Level   ,                    \
                                                                                    CATGeoOpDebug::HeaderLevel1, TRUE); } }            //
#define GEOPDEBUG_IF_END_HEAD(Category, Level, Cond)      { if (Cond) GEOPDEBUG_END_HEAD(Category, Level) }                            //
#define GEOPDEBUG_END_SUBHEAD(Category, Level)            { if (CHECK_DEBUGACTIVE(TRACE, Category, Level))                             \
                                                            { tra->OutputHeaderLine(CATGeoOpDebug::TRACE::Category,                    \
                                                                                    CATGeoOpDebug::TRACE::Level   ,                    \
                                                                                    CATGeoOpDebug::HeaderLevel2, TRUE); } }            //
#define GEOPDEBUG_IF_END_SUBHEAD(Category, Level, Cond)   { if (Cond) GEOPDEBUG_END_SUBHEAD(Category, Level) }                         //
#define GEOPDEBUG_TXT(Category, Level, Text)              { if (CHECK_DEBUGACTIVE(TRACE, Category, Level))                             \
                                                            { tra->_StrOut << Text;                                                    \
                                                              tra->OutputTrace(CATGeoOpDebug::TRACE::Category,                         \
                                                              CATGeoOpDebug::TRACE::Level); } }                                        //
#define GEOPDEBUG_SUMMARY(Category, Level, iObj)          { GEOPDEBUG_LEV_CMD(Category, Level,                                         \
                                                                              tra->PrintSummary(CATGeoOpDebug::TRACE::Category,        \
                                                                                                CATGeoOpDebug::TRACE::Level, iObj)); } //
#define GEOPDEBUG_DUMP(Category, Level, iGeom)            { GEOPDEBUG_LEV_CMD(Category, Level,                                          \
                                                                              tra->DumpGeometry(CATGeoOpDebug::TRACE::Category,         \
                                                                                                CATGeoOpDebug::TRACE::Level, iGeom)); } //
#define GEOPDEBUG_HEAD(Category, Level, Text)             { if (CHECK_DEBUGACTIVE(TRACE, Category, Level))                              \
                                                            { tra->_StrOut << Text; tra->OutputTrace(CATGeoOpDebug::TRACE::Category,    \
                                                                                                     CATGeoOpDebug::TRACE::Level,       \
                                                                                                     CATGeoOpDebug::HeaderLevel1); } }  //
#define GEOPDEBUG_IF_HEAD(Category, Level, Cond, Text)    { if (Cond) GEOPDEBUG_HEAD(Category, Level, Text) }                           //
#define GEOPDEBUG_SUBHEAD(Category, Level, Text)          { if (CHECK_DEBUGACTIVE(TRACE, Category, Level))                              \
                                                            { tra->_StrOut << Text; tra->OutputTrace(CATGeoOpDebug::TRACE::Category,    \
                                                                                                     CATGeoOpDebug::TRACE::Level,       \
                                                                                                     CATGeoOpDebug::HeaderLevel2); } }  //
#define GEOPDEBUG_IF_SUBHEAD(Category, Level, Cond, Text) { if (Cond)  GEOPDEBUG_SUBHEAD(Category, Level, Text) }                       //
#define GEOPDEBUG_IF_TXT(Category, Level, Cond, Text)     { if (Cond) GEOPDEBUG_TXT(Category, Level, Text) }                            //
#define GEOPDEBUG_IF_TXT_LEV(Category, Cond, Level1, Level2, Text) { if (Cond) { GEOPDEBUG_TXT(Category, Level1, Text); }               \
                                                                     else      { GEOPDEBUG_TXT(Category, Level2, Text); } }             //

//#define GEOPDEBUG_INCREMENT(Category, Level) { if (CHECK_DEBUGACTIVE(TRACE, Category, Level)) \
//{ tra->IncrementShift(CATGeoOpDebug::TRACE::Category); } }
//#define GEOPDEBUG_DECREMENT(Category, Level) { if (CHECK_DEBUGACTIVE(TRACE, Category, Level)) \
//{ tra->DecrementShift(CATGeoOpDebug::TRACE::Category); } }
//#define GEOPDEBUG_FUNCTION_START(Category, Text) GETGEOPDEBUG(tra); \
//{ if (CHECK_DEBUGACTIVE(TRACE, Category, ALL)) \
// { GEOPDEBUG_TXT(Category, ALL, "+++ " << Text << " +++") GEOPDEBUG_INCREMENT(Category, ALL); }}
//#define GEOPDEBUG_FUNCTION_END(Category, Text) \
// {if (CHECK_DEBUGACTIVE(TRACE, Category, ALL)) \
// { GEOPDEBUG_DECREMENT(Category, ALL); GEOPDEBUG_TXT(Category, ALL, "--- " << Text << " ---") }}
#define GEOPDEBUG_FUNCTION_START(Category, Text)          CATGeoOpDebug::CATGeoOpDebugFunctionObj localFuncObj(CATGeoOpDebug::TRACE::Category, \
                                                                                                               Text);                          \
                                                          GETGEOPDEBUG(tra);                                                                   //
#define GEOPDEBUG_OPERATOR_START(Category, FuncText, ...) CATGeoOpDebug::CATGeoOpDebugOperatorObj localOperObj(CATGeoOpDebug::TRACE::Category, \
                                                                                                               CATGeoOpDebug::OPER::Category,  \
                                                                                                               FuncText, __VA_ARGS__);         \
                                                          GETGEOPDEBUG(tra);                                                                   //
#define GEOPDEBUG_FUNCTION_END(Category, Text)            // until all calls are removed

#define GEOPDEBUG_ENDL_INT()             { OutputBlankLine(_CurrentCategory, _CurrentLevel); }
#define GEOPDEBUG_TXT_INT(Text)          { _StrOut << Text; OutputTrace(); }
#define GEOPDEBUG_SUBHEAD_INT(Text)      { _StrOut << Text; OutputTrace(_CurrentCategory, _CurrentLevel, CATGeoOpDebug::HeaderLevel2); }
#define GEOPDEBUG_END_SUBHEAD_INT()      { OutputHeaderLine(_CurrentCategory, _CurrentLevel, CATGeoOpDebug::HeaderLevel2); }

#define GEOPDEBUG_STACK(Category, Level) {tra->DumpCallStack(CATGeoOpDebug::TRACE::Category, CATGeoOpDebug::TRACE::Level);}

//#define OBJ(Obj, ...) tra->_StrOut._OutObj.Print(Obj, __VA_ARGS__)
#define OBJ(Obj, ...) tra->_StrOut.Print(Obj, __VA_ARGS__)

//#define GEOPDEBUG_CMD(Cmd) Cmd;
#define GEOPDEBUG_IARG(Arg)                                         Arg
#define GEOPDEBUG_ARG(Arg)                                          , Arg
#define GEOPDEBUG_INIT(Cmd)                                         Cmd
#define GEOPDEBUG_INIT_MULTI(Cmd)                                   Cmd,
#define GEOPDEBUG_TYPE_LEV_CMD(Type, Category, Level, Cmd)          { if (CHECK_DEBUGACTIVE(Type, Category, Level)) {Cmd;} }
#define GEOPDEBUG_LEV_CMD(Category, Level, Cmd)                     GEOPDEBUG_TYPE_LEV_CMD(TRACE, Category, Level, Cmd)
#define GEOPDEBUG_TYPE_CMD(Type, Category, Cmd)                     GEOPDEBUG_TYPE_LEV_CMD(Type, Category, ON, Cmd)
#define GEOPDEBUG_IF_TYPE_CMD(Type, Category, Cond, Cmd)            { if (Cond) GEOPDEBUG_TYPE_CMD(Type, Category, Cmd); }
#define GEOPDEBUG_IF_TYPE_LEV_CMD(Type, Category, Level, Cond, Cmd) { if (Cond) GEOPDEBUG_TYPE_LEV_CMD(Type, Category, Level, Cmd); }
#define GEOPDEBUG_IF_CMD(Cond, Cmd)                                 { if (Cond) {Cmd;} }
#define GEOPDEBUG_IF_LEV_CMD(Category, Level, Cond, Cmd)            { if (Cond) GEOPDEBUG_LEV_CMD(Category, Level, Cmd) }


#define GEOPDEBUG_VERSION(Flag)                                     ((CHECK_DEBUGACTIVE(VERS, Flag, ON))                            \
                                                                        ? tra->GetVersioningLevelFromFlag(CATGeoOpDebug::VERS::Flag)\
                                                                        : 32000)                                                    //

#define GEOPDEBUG_GET_COUNT(Category) tra->GetOperatorCount(CATGeoOpDebug::OPER::Category)
#define GEOPDEBUG_ADD_COUNT(Category) tra->IncrementOperatorCount(CATGeoOpDebug::OPER::Category)

#define GEOPDEBUG_GET_ENV_VAR(iEnvironmentVariable, ioValue, iInterval) tra->SetValueFromEnvVar(CATGeoOpDebug::ENV_VAR::iEnvironmentVariable, \
                                                                                                ioValue,                                      \
                                                                                                iInterval)                                    //

#define GEOPDEBUG_TIMER_RESET(Category) tra->ResetTimer(CATGeoOpDebug::TIMER::Category)
#define GEOPDEBUG_TIMER_START(Category) tra->StartTimer(CATGeoOpDebug::TIMER::Category)
#define GEOPDEBUG_TIMER_STOP(Category)  tra->StopTimer(CATGeoOpDebug::TIMER::Category)
#define GEOPDEBUG_TIMER_WRITE(Category) tra->WriteTimer(CATGeoOpDebug::TIMER::Category)

#define GEOPDEBUG_SET_TOL(iObject) tra->SetToleranceObject(iObject)

#else

#define GETGEOPDEBUG(Var) CATGeoOpDebug * Var = NULL;

#define GEOPDEBUG_ENDL(Category, Level) {}
#define GEOPDEBUG_IF_ENDL(Category, Level, Cond) {}
#define GEOPDEBUG_END_HEAD(Category, Level) {}
#define GEOPDEBUG_IF_END_HEAD(Category, Level, Cond) {}
#define GEOPDEBUG_END_SUBHEAD(Category, Level) {}
#define GEOPDEBUG_IF_END_SUBHEAD(Category, Level, Cond) {}
#define GEOPDEBUG_TXT(Category, Level, Text) {}
#define GEOPDEBUG_SUMMARY(Category, Level, iObj) {}
#define GEOPDEBUG_DUMP(Category, Level, iObj) {}
#define GEOPDEBUG_HEAD(Category, Level, Text) {}
#define GEOPDEBUG_IF_HEAD(Category, Level, Cond, Text) {}
#define GEOPDEBUG_SUBHEAD(Category, Level, Text) {}
#define GEOPDEBUG_IF_SUBHEAD(Category, Level, Cond, Text) {}
#define GEOPDEBUG_IF_TXT(Category, Level, Cond, Text) {}
#define GEOPDEBUG_IF_TXT_LEV(Category, Cond, Level1, Level2, Text) {}
#define GEOPDEBUG_INCREMENT(Category, Level) {}
#define GEOPDEBUG_DECREMENT(Category, Level) {}

#define GEOPDEBUG_FUNCTION_START(Category, Text) {}
#define GEOPDEBUG_OPERATOR_START(Category, FuncText, ...)
#define GEOPDEBUG_FUNCTION_END(Category, Text) {} // until all calls are removed

#define GEOPDEBUG_ENDL_INT() {}
#define GEOPDEBUG_TXT_INT(Text) {}
#define GEOPDEBUG_SUBHEAD_INT(Text) {}
#define GEOPDEBUG_END_SUBHEAD_INT() {}

#define GEOPDEBUG_STACK(Category, Level) {}

#define OBJ(Obj, ...)

//#define GEOPDEBUG_CMD(Cmd)
#define GEOPDEBUG_IARG(Arg)
#define GEOPDEBUG_ARG(Arg)
#define GEOPDEBUG_INIT(Cmd)
#define GEOPDEBUG_INIT_MULTI(Cmd)
#define GEOPDEBUG_LEV_CMD(Category, Level, Cmd)
#define GEOPDEBUG_TYPE_CMD(Type, Category, Cmd)
#define GEOPDEBUG_IF_TYPE_CMD(Type, Category, Cond, Cmd)
#define GEOPDEBUG_TYPE_LEV_CMD(Type, Category, Level, Cmd)
#define GEOPDEBUG_IF_TYPE_LEV_CMD(Type, Category, Level, Cond, Cmd)
#define GEOPDEBUG_IF_CMD(Cond, Cmd) {}
#define GEOPDEBUG_IF_LEV_CMD(Category, Level, Cond, Cmd) {}

#define GEOPDEBUG_VERSION(Flag) { CATMathODT::ExitForODT(138); }

#define GEOPDEBUG_GET_COUNT(Category)
#define GEOPDEBUG_ADD_COUNT(Category)

#define GEOPDEBUG_GET_ENV_VAR(iEnvironmentVariable, ioValue, iInterval)

#define GEOPDEBUG_TIMER_RESET(Category)
#define GEOPDEBUG_TIMER_START(Category)
#define GEOPDEBUG_TIMER_STOP(Category)
#define GEOPDEBUG_TIMER_WRITE(Category)

#define GEOPDEBUG_SET_TOL(iObject)

#endif

// Replay capture
// --------------

// For geometries: activated via GeopReplayTags
// For strings   : activated via GeopReplayTypes

#define GEOPDEBUG_IF_REPLAY(iCond, iType) if (iCond) { CATGeoOpDebug::CheckAndActivateCGMReplay(iType); }
#define GEOPDEBUG_REPLAY(iType) CATGeoOpDebug::CheckAndActivateCGMReplay(iType)

// X-scale macros
// --------------

#define GeopScale(iPower) CATGeoOpDebug::_Scale##iPower

// Function header / footer macros
// -------------------------------

#define GEOP_RETURN(Category, Text, Value)      { GEOPDEBUG_FUNCTION_END(Category, Text); return Value; }
#define GEOP_RETURN_VOID(Category, Text)        { GEOPDEBUG_FUNCTION_END(Category, Text); return; }

#define GEOP_THROW(Category, Text, Err)         { GEOPDEBUG_TXT(Category, ERR, Text << " : throw error");                          \
                                                  GEOPDEBUG_FUNCTION_END(Category, Text); CATThrow(Err); }                         //
#define GEOP_THROW_NULL_RET(Category, Text, RC) { GEOPDEBUG_TXT(Category, ERR, Text << " : throw for null pointer");               \
                                                  GEOPDEBUG_FUNCTION_END(Category, Text); CATThrowForNullPointerReturnValue(RC); } //
#define GEOP_THROW_NULL_VOID(Category, Text)    { GEOPDEBUG_TXT(Category, ERR, Text << " : throw for null pointer");               \
                                                  GEOPDEBUG_FUNCTION_END(Category, Text);                                          \
                                                  CATThrowForNullPointer(); }                                                      //

#define GEOP_CATCH(Category, Text)              { GEOPDEBUG_TXT(Category, ERR, Text << " : caught error"); }

// Assert macros
// -------------

#define GEOP_ASSERT(Cond, Str) if (Cond) { CATGeoOpDebug::MakeAssert(__FILE__, __LINE__, Str); }

// Trace macros
// ------------

#define CHECK_INPUT_CATEGORY(Type, Category) ((Category > Type::START) && (Category < Type::MAX_NUM))

// Trace categories
// ----------------

/*
ECC = EdgeCurveComputation
FIL = Connect (aka Fillet)
MGI = MultiGridIntersection
*/

#define GEOP_TRACE_CATEGORIES GEOP_DEF_CS(START)\
                              GEOP_DEF(EMPTY)\
                              GEOP_DEF(TIMER)\
                              GEOP_DEF(DENV)\
                              GEOP_DEF(STR)\
                              GEOP_DEF(UTILS)\
                              GEOP_DEF(GEOMETRY)\
                              GEOP_DEF(GEOP)\
                              GEOP_DEF(MODEL)\
                              GEOP_DEF(KVEC)\
                              GEOP_DEF(XSCALE)\
                              GEOP_DEF(EXTCRV)\
                              GEOP_DEF(EXTECRV)\
                              GEOP_DEF(EXTSUR)\
                              GEOP_DEF(CHK_ECRV)\
                              GEOP_DEF(CHK_SUR)\
                              /*GEOP_DEF(CONF_CRVCRV)*/\
                              GEOP_DEF(CONF_PTSPTS)\
                              GEOP_DEF(SSTG)\
                              GEOP_DEF(SSTG_Input)\
                              GEOP_DEF(SSTG_Output)\
                              GEOP_DEF(SSWI)\
                              GEOP_DEF(SSGEN)\
                              GEOP_DEF(SSINT)\
                              GEOP_DEF(PLSINT)\
                              GEOP_DEF(PPINT)\
                              GEOP_DEF(SSINT_MarchedPoints)\
                              GEOP_DEF(SSINT_InterpolPoints)\
                              GEOP_DEF(ASINT)\
                              GEOP_DEF(ASINT_SUBDIV)\
                              GEOP_DEF(ASINT_INT)\
                              GEOP_DEF(ASINT_FILTER)\
                              GEOP_DEF(ASINT_PROC)\
                              GEOP_DEF(SSVOB)\
                              GEOP_DEF(CSINT)\
                              GEOP_DEF(CSINT_MarchedPoints)\
                              GEOP_DEF(CCINT)\
                              GEOP_DEF(FIL)\
                              GEOP_DEF(SSINT_EQS)\
                              GEOP_DEF(SSINT_INTPL)\
                              GEOP_DEF(XGM)\
                              GEOP_DEF(XGM_OUT)\
                              GEOP_DEF(XGM_LIFE)\
                              GEOP_DEF(XGM_MEM)\
                              GEOP_DEF(XGM_VERSION)\
                              GEOP_DEF(XGM_MLK)\
                              GEOP_DEF(XGM_BLEND)\
                              GEOP_DEF(XGM_NURBS)\
                              GEOP_DEF(XGM_VIS)\
                              GEOP_DEF(MSINT)\
                              GEOP_DEF(MSINT_BACK)\
                              GEOP_DEF(MSINT_MEM)\
                              GEOP_DEF(MSINT_Output)\
                              GEOP_DEF(MSCUB)\
                              GEOP_DEF(MATH)\
                              GEOP_DEF(PCrvPCrvINT)\
                              GEOP_DEF(INC_PTCRV)\
                              GEOP_DEF(INC_PTSUR)\
                              GEOP_DEF(INC_PTMS)\
                              GEOP_DEF(DIST_PTSUR)\
                              GEOP_DEF(DIST_SURSUR)\
                              GEOP_DEF(SSSINT)\
                              GEOP_DEF(SSTAN)\
                              GEOP_DEF(APPROX)\
                              GEOP_DEF(CLASH2D)\
                              GEOP_DEF(CIVIL)\
                              GEOP_DEF(CIVIL_SOLVE)\
                              GEOP_DEF(CIVIL_EVAL)\
                              GEOP_DEF(CIVIL_APX)\
                              GEOP_DEF(CIVIL_TSCST)\
                              GEOP_DEF(CIVIL_ITF)\
                              GEOP_DEF(PROJ_CS)\
                              GEOP_DEF(PROJ_PTCRV)\
                              GEOP_DEF(PROJ_CPL)\
                              GEOP_DEF(INTCRVRED)\
                              GEOP_DEF(ECC)\
                              GEOP_DEF(LDCS)\
                              GEOP_DEF(MGI)\
                              GEOP_DEF(MGI_Res)\
                              GEOP_DEF(TWIST)\
                              GEOP_DEF_CP(HOMOTOPY)\
                              GEOP_DEF_CP(THINLOOP)\
                              GEOP_DEF_CE(MAX_NUM)

#define GEOP_TRACE_LEVELS GEOP_DEF_TLS(OFF)\
                          GEOP_DEF(COUNT)\
                          GEOP_DEF(ERR)\
                          GEOP_DEF(WARN)\
                          GEOP_DEF(INFO)\
                          GEOP_DEF(VERB)\
                          GEOP_DEF_LP(ALL)\
                          GEOP_DEF_LE(MAX_LEVEL)

// Function categories
// -------------------

#define GEOP_FUNCTION_CATEGORIES GEOP_DEF_CS(START)\
                                 GEOP_DEF(TRACE_WARN_MakeAssert)\
                                 GEOP_DEF(ODT_Exit)\
                                 GEOP_DEF(SSINT_SurfSwap)\
                                 GEOP_DEF(SSINT_ConeApex)\
                                 GEOP_DEF(SSINT_DumpPrecision)\
                                 GEOP_DEF(SSINT_NoCleanCurves)\
                                 GEOP_DEF(SSGEN_SurfSwap)\
                                 GEOP_DEF(SSGEN_LoopInitFilter)\
                                 GEOP_DEF(SSWI_SurfSwap)\
                                 GEOP_DEF(SSWI_TwoInitDeformation)\
                                 GEOP_DEF(SSWI_SplitIntersectingCurves)\
                                 GEOP_DEF(PPINT_AdmissibleTol)\
                                 GEOP_DEF(PCrvPCrvINT_NoCleanPoints)\
                                 GEOP_DEF(MSINT_NoBackwardsBackup)\
                                 GEOP_DEF(MSINT_InitExitSwap)\
                                 GEOP_DEF(MSINT_CurveThroughProjectedHelpPoints)\
                                 GEOP_DEF(MSINT_OnBorder3D)\
                                 GEOP_DEF(MSINT_InterpolModeTrue)\
                                 GEOP_DEF(MSINT_InterpolModeFalse)\
                                 GEOP_DEF(CSINT_AdvBox)\
                                 GEOP_DEF(ASINT_OpKO_ForCaptureReplays)\
                                 GEOP_DEF(SSINT_EQS_ValidateCubic_PerpTgt)\
                                 GEOP_DEF(SSINT_EQS_ValidateCubic_ExtraRoots)\
                                 GEOP_DEF(EXTECRV_ConsistentMarchInterpol)\
                                 GEOP_DEF(XGM_Blend_NoSimplifySpine)\
                                 GEOP_DEF(XGM_CreateOnInit)\
                                 GEOP_DEF(CONF_CRVCRV_GeomPackReplays)\
                                 GEOP_DEF_CP(CONF_PTSPTS_ForceOp)\
                                 GEOP_DEF_CE(MAX_NUM)

#define GEOP_FUNCTION_LEVELS GEOP_DEF_LS(OFF)\
                             GEOP_DEF_LP(ON)\
                             GEOP_DEF_LE(MAX_LEVEL)

// Visual categories
// -----------------


#define GEOP_VISUAL_CATEGORIES GEOP_DEF_CS(START)\
                               GEOP_DEF(ASINT_ALL)\
                               GEOP_DEF(ASINT_SUBDIV)\
                               GEOP_DEF(ASINT_FILTER)\
                               GEOP_DEF(SSWI)\
                               GEOP_DEF(SSGEN)\
                               GEOP_DEF(SSTG)\
                               GEOP_DEF(EXTCRV)\
                               GEOP_DEF(EXTSUR)\
                               GEOP_DEF(SSINT_MarchedPoints)\
                               GEOP_DEF(SSINT_InterpolPoints)\
                               GEOP_DEF(MSINT)\
                               GEOP_DEF(SSVOB)\
                               GEOP_DEF(CSINT)\
                               GEOP_DEF(CSINT_MarchedPoints)\
                               GEOP_DEF(CLASH2D_Regions)\
                               GEOP_DEF(CLASH2D_Boxes)\
                               GEOP_DEF(CLASH2D_PenData)\
                               GEOP_DEF(XGM_INT_Extrap)\
                               GEOP_DEF(XGM_CGM_CreateCurve)\
                               GEOP_DEF(XGM_CGM_CreateSurf)\
                               GEOP_DEF(CIVIL_APX)\
                               GEOP_DEF(FIL_Init)\
                               GEOP_DEF(FIL_Piece)\
                               GEOP_DEF(FIL_RadiusLaw)\
                               GEOP_DEF(FIL_Cutter)\
                               GEOP_DEF(FIL_Computer)\
                               GEOP_DEF(FIL_G1Def)\
                               GEOP_DEF_CP(FIL_PointingDeform)\
                               GEOP_DEF_CE(MAX_NUM)

#define GEOP_VISUAL_LEVELS GEOP_DEF_LS(OFF)\
                           GEOP_DEF_LP(ON)\
                           GEOP_DEF_LE(MAX_LEVEL)

// Version categories
// ------------------

#define GEOP_VERSION_CATEGORIES GEOP_DEF_CS(START)\
                                GEOP_DEF_CP(Flag0)\
                                GEOP_DEF_CE(MAX_NUM)

#define GEOP_VERSION_LEVELS GEOP_DEF_LS(OFF)\
                            GEOP_DEF_LP(ON)\
                            GEOP_DEF_LE(MAX_LEVEL)

// Operator categories
// -------------------

//#define GEOP_OPERATORS GEOP_DEF_CS(START)\
//                       GEOP_DEF(EMPTY)\
//                       GEOP_DEF(GEOP)\
//                       GEOP_DEF(EXTCRV)\
//                       GEOP_DEF(EXTECRV)\
//                       GEOP_DEF(ASINT)\
//                       GEOP_DEF(SSINT)\
//                       GEOP_DEF(SSWI)\
//                       GEOP_DEF(SSGEN)\
//                       GEOP_DEF(SSTG)\
//                       GEOP_DEF(XGM)\
//                       GEOP_DEF(MSINT)\
//                       GEOP_DEF(MSINT_BACK)\
//                       GEOP_DEF(PLSINT)\
//                       GEOP_DEF(PPINT)\
//                       GEOP_DEF(SSSINT)\
//                       GEOP_DEF(CCINT)\
//                       GEOP_DEF(CSINT)\
//                       GEOP_DEF(PROJ_PTCRV)\
//                       GEOP_DEF(PCrvPCrvINT)\
//                       GEOP_DEF_CP(INC_PTMS)\
//                       GEOP_DEF_CE(MAX_NUM)

#define GEOP_OPERATORS GEOP_TRACE_CATEGORIES

// Timer categories
// ----------------

#define GEOP_TIMERS GEOP_DEF_CS(START)\
                    GEOP_DEF(EMPTY)\
                    GEOP_DEF(XGM)\
                    GEOP_DEF(XGM_GLOBAL)\
                    GEOP_DEF(CIVIL)\
                    GEOP_DEF(ASINT)\
                    GEOP_DEF(ASINT_INT)\
                    GEOP_DEF_CP(ASINT_PROC)\
                    GEOP_DEF_CE(MAX_NUM)

#define GEOP_TIMER_LEVELS GEOP_DEF_LS(OFF)\
                          GEOP_DEF_LP(ON)\
                          GEOP_DEF_LE(MAX_LEVEL)

// Environment variable settings
// -----------------------------

#define GEOP_ENV_VARS GEOP_DEF_CS(START)\
                      GEOP_DEF_ENV(DOUBLE, XGM_ExtrapSafetyFactor)\
                      GEOP_DEF_ENV(DOUBLE, XGM_ExtrapActiveRegionSafetyFactor)\
                      GEOP_DEF_ENV(DOUBLE, XGM_TolSmallNURBS)\
                      GEOP_DEF_ENV(INT   , XGM_MemFreq)\
                      GEOP_DEF_ENV(INT   , XGM_InitSampleEval)\
                      GEOP_DEF_ENV(INT   , MSINT_MaxLoop)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_GenericFilletLimit)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_ExtrapolFrac)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_ExtendPercentVal_Inclusion)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_ExtendPercentVal_Extrapolation)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_HelpPointOnCurve_MaxDistFactor)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_SingularTangentAngleFactor)\
                      GEOP_DEF_ENV(DOUBLE, MSINT_Propagate_TangentTol)\
                      GEOP_DEF_ENV(DOUBLE, SSTG_SmoothSharp_Singular)\
                      GEOP_DEF_ENV(DOUBLE, SSINT_AnalyticPole_AngleTol)\
                      GEOP_DEF_ENV(INT   , SSGEN_LoopInitNumSamplePts)\
                      GEOP_DEF_ENV(DOUBLE, SSGEN_MarchingSagFactor)\
                      GEOP_DEF_ENV(INT   , SSWI_InterOp_SecondOrderSingular)\
                      GEOP_DEF_ENV(INT   , SSWI_Default_SecondOrderSingular)\
                      GEOP_DEF_ENV(DOUBLE, SSWI_MinStep_SmallDomainFactor)\
                      GEOP_DEF_ENV(INT   , ASINT_MergeMaxIterations)\
                      GEOP_DEF_ENV(DOUBLE, ASINT_MergeThresholdAngle)\
                      GEOP_DEF_ENV(INT   , ASINT_ApplyPointFilters)\
                      GEOP_DEF_ENV(INT   , ASINT_ApplyCurveFilters)\
                      GEOP_DEF_ENV(DOUBLE, SSINT_EQS_CurvIsFlatThreshold)\
                      GEOP_DEF_ENV(DOUBLE, SSINT_EQS_CurvIsSimilar)\
                      GEOP_DEF_ENV(DOUBLE, SSINT_EQS_ThirdDerivIsNull)\
                      GEOP_DEF_ENV(DOUBLE, SSINT_EQS_ThirdDerivIsSimilar)\
                      GEOP_DEF_ENV(INT,    CLASH2D_ReplayCapturePenetrationData)\
                      GEOP_DEF_ENV(INT,    CLASH2D_UseGenericIntersectors)\
                      GEOP_DEF_ENV(INT,    CLASH2D_TurnOffTaskBoxTest)\
                      GEOP_DEF_ENV(INT,    CLASH2D_ForceFilterBody1)\
                      GEOP_DEF_ENV(INT,    CLASH2D_ForceFilterBody2)\
                      GEOP_DEF_ENV(DOUBLE, CIVIL_InitValueCSC)\
                      GEOP_DEF_ENV(DOUBLE, CIVIL_Solver_Dump)\
                      GEOP_DEF_ENV(DOUBLE, CSINT_IsSingularAngularTol)\
                      GEOP_DEF_ENV(DOUBLE, CSINT_SignatureTol)\
                      GEOP_DEF_ENV_CP(DOUBLE, CSINT_IntersectLineTab_TolFactor)\
                      GEOP_DEF_CE(MAX_NUM)

// Utility macros (re-defined in CATGeoOpDebug.cpp)
// ------------------------------------------------

// Define for category start / penultimate / end element in enum
#define GEOP_DEF_CS(x) x = -1,
#define GEOP_DEF_CP(x) x,
#define GEOP_DEF_CE(x) x

// Define for level start / penultimate / end element in enum
#define GEOP_DEF_LS(x) x = 0,
#define GEOP_DEF_LP(x) x,
#define GEOP_DEF_LE(x) x

// Define for trace level starting element in enum
#define GEOP_DEF_TLS(x) x = -1,

// Define for generic element in enum
#define GEOP_DEF(x) x,

// Define macro for environment variables
#define GEOP_DEF_ENV_CP(x, y) y,
#define GEOP_DEF_ENV(x, y) y,

class ExportedByY3DYNOPE CATGeoOpDebug : public CATCGMVirtual
{
public:

  struct TYPE
  {
    /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
    enum DEBUG_TYPES{ UNKNOWN = -1, TRACE = 0, FUNC, VIS, VERS, TIMER }; // Type of debug
  };
  
  // An easier way to this might be to use enum class TraceNames : CategoryClass { XX, YY, ZZ }
  // but these are not available yet.

  struct TRACE
  {
    enum TRACE_NAMES { GEOP_TRACE_CATEGORIES };

    enum TRACE_LEVELS { GEOP_TRACE_LEVELS };

  };

  struct FUNC
  {
    enum FUNC_NAMES { GEOP_FUNCTION_CATEGORIES };

    enum FUNC_LEVELS { GEOP_FUNCTION_LEVELS };
                       
  };

  struct VIS
  {
    enum VIS_NAMES { GEOP_VISUAL_CATEGORIES };

    enum VIS_LEVELS{ GEOP_VISUAL_LEVELS };
  };

  struct VERS
  {
    enum VERS_NAMES { GEOP_VERSION_CATEGORIES };

    enum VERS_LEVELS { GEOP_VERSION_LEVELS };
  };

  struct OPER
  {
    enum OPER_CATEGORIES { GEOP_OPERATORS };
  };

  struct TIMER
  {
    enum TIMER_CATEGORIES { GEOP_TIMERS };
    enum TIMER_LEVELS { GEOP_TIMER_LEVELS };
  };

  struct ENV_VAR
  {
    enum ENV_VAR_CATEGORIES { GEOP_ENV_VARS };
  };

  class GeopEnvVar
  {
  public:
    /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
    enum TYPE { UNKNOWN = -1, DOUBLE, INT };

    GeopEnvVar();
    GeopEnvVar(const CATUnicodeString& iVar, const TYPE iType);
    ~GeopEnvVar();

    CATBoolean GetValue(int&) const;
    CATBoolean GetValue(double&) const;

    const CATUnicodeString * const GetEnvVar() const;

    void InitValue();

  private:
    
    CATUnicodeString _EnvVar;
    CATBoolean _Active;

    TYPE _Type;

    int _ValueInt;
    double _ValueDouble;
  };

  class ExportedByY3DYNOPE CATGeoOpDebugFunctionObj
  {
  public:
    CATGeoOpDebugFunctionObj(const int                iTrCategory,
                             const CATUnicodeString & iFunctionName,
                             const CATBoolean         iPrintOnConstruction = TRUE);

    ~CATGeoOpDebugFunctionObj();

  protected:

    void Print() const;

    const int _TrCategory;
    const CATUnicodeString _FunctionName;
  };

  class ExportedByY3DYNOPE CATGeoOpDebugOperatorObj : CATGeoOpDebugFunctionObj
  {
  public:
      CATGeoOpDebugOperatorObj(const int                iTrCategory,
                               const int                iOpCategory,
                               const CATUnicodeString & iFunctionName);

      CATGeoOpDebugOperatorObj(const int                iTrCategory,
                               const int                iOpCategory,
                               const CATUnicodeString & iFunctionName,
                               const CATUnicodeString & iOpFooterStr);

    ~CATGeoOpDebugOperatorObj();

  private:

    void PrintOpHeader(const CATUnicodeString * iOpFooterStr) const;

    const int _OpCategory;
    //const CATGeoOpDebugFunctionObj _FunctionObj;
  };

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  enum HeaderLevel { HeaderLevel0 = 0, HeaderLevel1, HeaderLevel2 };

  class XscaleLevel
  {
  public:

    /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
    enum XscaleLevels { ScaleInvalid = -1,
                        ScaleUnknown = 0,
                        ScaleInvSqSqLen,
                        ScaleInvSqLen,
                        ScaleInvLen,
                        ScaleInvSqrtLen,
                        ScaleZero,
                        ScaleSqrtLen,
                        ScaleLen,
                        ScaleSqLen,
                        ScaleVol
                      };

                              XscaleLevel       ();
                              XscaleLevel       (const XscaleLevels);
                             ~XscaleLevel       ();

                 void         DecreaseScalePower();
                 void         IncreaseScalePower();
    
           const XscaleLevels GetLevel() const;
           const double       GetScalePower() const;

    static const XscaleLevels ConvertLongToXscale(const CATLONG32);

  private:

                 double       ConvertScaleToValue() const;

    XscaleLevels _Level;
  };

  //class CATGeoOpDebugOutput;

  //class ExportedByY3DYNOPE CATGeoOpDebugOutputObject
  //{
  // private:

  //  friend class CATGeoOpDebugOutput;
  //  CATGeoOpDebugOutputObject();
  //
  //public:
  //  virtual ~CATGeoOpDebugOutputObject();
  //
  //};

  class ExportedByY3DYNOPE CATGeoOpDebugOutput
  {
  private:
    friend class CATGeoOpDebug;

    CATGeoOpDebugOutput(CATCGMOutput::Mode iMode);

  public:

    virtual ~CATGeoOpDebugOutput();

    // Compatibility with CATCGMOutput
    void Get(CATUnicodeString & oStr);
    void Flush();

  public:

    // Overload operators for simple types
    //   - anything requiring more than one arugment (eg array / options)
    //     will need to use the OBJ mechanism to modify the
    //     CATGeoOpDebugOutputObject _OutObj

    CATGeoOpDebugOutput & operator << (const CATBoolean);

    //CATGeoOpDebugOutput & operator << (const HRESULT); // type-def to long --> cannot overload

    // It is better to have the native types to avoid build errors on 32/64 bit
    //CATGeoOpDebugOutput & operator << (const CATULONG32);
    //CATGeoOpDebugOutput & operator << (const CATLONG32); // build error on 64-bit
    
    CATGeoOpDebugOutput & operator << (const short);
    CATGeoOpDebugOutput & operator << (const int);
    CATGeoOpDebugOutput & operator << (const unsigned int);
    CATGeoOpDebugOutput & operator << (const long);
    CATGeoOpDebugOutput & operator << (const unsigned long);
    CATGeoOpDebugOutput & operator << (const double);
    CATGeoOpDebugOutput & operator << (const char *);

    CATGeoOpDebugOutput & operator << (const CATUnicodeString &);

    // Maths
    CATGeoOpDebugOutput & operator << (const CATMathInterval &);

    // Geometry
    CATGeoOpDebugOutput & operator << (const CATGeometry * iGeom);

    // Space saving implementations
    CATGeoOpDebugOutput & operator << (const CATCrvParam & iParam);
    CATGeoOpDebugOutput & operator << (const CATSurParam & iParam);
    CATGeoOpDebugOutput & operator << (const CATCrvLimits & iLim);
    CATGeoOpDebugOutput & operator << (const CATSurLimits & iLim);
    CATGeoOpDebugOutput & operator << (const CATMathPoint2D & iP);
    CATGeoOpDebugOutput & operator << (const CATMathPoint & iP);
    CATGeoOpDebugOutput & operator << (const CATMathVector2D & iV);
    CATGeoOpDebugOutput & operator << (const CATMathVector & iV);
    CATGeoOpDebugOutput & operator << (const CATMathDirection2D & iV);
    CATGeoOpDebugOutput & operator << (const CATMathDirection & iV);

    // Civil road
    CATGeoOpDebugOutput & operator << (const CATCivilCurveDef::CheckParamValue & iV);
    CATGeoOpDebugOutput & operator << (const CATCivilCurveDef::CATCivilRunStatus & iStatus);
    CATGeoOpDebugOutput & operator << (const CATCivilCurveDef::ParamType & iType);
    CATGeoOpDebugOutput & operator << (const CATCivilCurveType & iType);
    CATGeoOpDebugOutput & operator << (const CATCivilInput_ClockOrientation & iType);

    // Clash2D
    CATGeoOpDebugOutput & operator << (const CATClash2D::CATClash2DClassification & iClassification);

    // Generic object to print
    //CATGeoOpDebugOutput & operator << (const CATGeoOpDebug::CATGeoOpDebugOutputObject & iObj);
    
    // Wrappers to CATGeoOpDebug methods
    static CATUnicodeString Print(const CATBoolean    iValueB,
                                  const short         iPrintMode = 0);
    
    static CATUnicodeString Print(const double        iValueD,
                                  const XscaleLevel & iXscaleLevel,
                                  const int           iDecPt = -1);

    static CATUnicodeString Print(const CATBoolean  * iArrayB,
                                  const CATLONG32     iArraySize,
                                  const short         iPrintMode = 0);

    static CATUnicodeString Print(const CATLONG32   * iArrayI,
                                  const CATLONG32     iArraySize);

    static CATUnicodeString Print(const double      * iArrayD,
                                  const CATLONG32     iArraySize,
                                  const XscaleLevel & iXscaleLevel,
                                  const int           iDecPt = -1);

    static CATUnicodeString Print(const CATGeometry * iGeom,
                                  const CATBoolean    iLong = FALSE);
    
    static CATUnicodeString Print(const CATCrvParam & iPar,
                                  const short         iPrintMode = 0,
                                  const int           iDecPt = -1);

    static CATUnicodeString Print(const CATSurParam & iPar,
                                  const short         iPrintMode = 0,
                                  const int           iDecPt = -1);

  public:

    //CATGeoOpDebugOutputObject _OutObj;

  private:

    CATCGMOutput _OutStr;
  };

  // -------------
  // Public access
  // -------------

  static CATGeoOpDebug*  GetGeoOpDebug();

  virtual ~CATGeoOpDebug();

  CATGeoOpDebugOutput _StrOut;

  static void HideObject();
  static void ExposeObject();

protected:

  //-----------------------------
  // Constructors and destructors
  //-----------------------------

  CATGeoOpDebug();
  //CATGeoOpDebug(const CATGeoOpDebug &);
  //CATGeoOpDebug & operator=(const CATGeoOpDebug &);

  //short   GetCheck();

//protected:

  //CATTrace   _Check;

public:

  // Public methods for CGM replays
  static CATBoolean IsUnderCGMReplay(CATCGMOperator * iOper);

  static void Dump_CGMReplay_OperatorInfo(CATGeoOperator           * iOper,
                                          CATCGMOutput             & ioOutput,
                                          CATSoftwareConfiguration * iConfigOper);

  static void Dump_CGMReplay_OperatorInfo(CATCGMOperator           * iOper,
                                          CATCGMOutput             & ioOutput,
                                          CATSoftwareConfiguration * iConfigOper);

private:

  static void Dump_CGMReplay_OperatorInfoCommon(CATCGMOperator           * iOper,
                                                CATCGMOutput             & ioOutput,
                                                CATSoftwareConfiguration * iConfigOper);

public:

  static CATGeoOpAllTimers * GetAllTimers();
  static void SetAllTimers(CATBoolean iAllTimersOn=1);
  static void AddTimer(CATGeoOpTimer * iTimer);

  // Public methods to check if debug / trace is active
  // --------------------------------------------------

  CATBoolean DebugActive(const TYPE::DEBUG_TYPES iType,
                         const int               iCategory,
                         const int               iLevel) const;

  // Public methods to output trace
  // ------------------------------

  void OutputBlankLine(const int iCategory,
                       const int iLevel);

  void OutputTrace(const int         iCategory,
                   const int         iLevel,
                   const HeaderLevel iHeaderLevel = HeaderLevel0);

  void OutputHeaderLine(const int         iCategory,
                        const int         iLevel,
                        const HeaderLevel iHeaderLevel,
                        const CATBoolean  iEndHeader = FALSE);
public:

  // Public methods for counting operators
  // -------------------------------------

  void IncrementOperatorCount(const int iOpCategory);
  CATLONG32 GetOperatorCount (const int iOpCategory) const;

  void ResetCounters();

  // Public method for activating / deactivating specific trace
  // ----------------------------------------------------------

  void ActivateOperatorTrace(const int iOpCategory);
  void DeactivateOperatorTrace(const int iOpCategory);

  // Public method for shift trace
  // -----------------------------

  void IncrementShift(const int iCategory);
  void DecrementShift(const int iCategory);

  // Timer functions
  // ---------------

  void       ResetTimer(const int iCategory);
  CATBoolean StartTimer(const int iCategory);
  CATBoolean StopTimer (const int iCategory, const CATBoolean iWasStarted = TRUE);
  void       WriteTimer(const int iCategory);
  void       ResetTimers();

  // Utilities for debug options windows
  // -----------------------------------

  CATLONG32 GetCurrentDebugLevel(const TYPE::DEBUG_TYPES, const CATLONG32) const;
  void      SetCurrentDebugLevel(const TYPE::DEBUG_TYPES, const CATLONG32, const int);

  int GetTracePrecision() const;
  void SetTracePrecision(const int);

  CATUnicodeString GetTraceOutputPath() const;
  void SetTraceOutputPath(const CATUnicodeString&);

  static CATBoolean GetTraceNoTags();
  void SetTraceNoTags(const CATBoolean);

  static CATBoolean GetTraceNoAddr();
  void SetTraceNoAddr(const CATBoolean);

  static CATBoolean GetTraceXScale();
  void SetTraceXScale(const CATBoolean);

  // Debug functions
  // ---------------

  static void MakeAssert(const CATUnicodeString & iAssertFile,
                         const int                iAssertLine,
                         const CATUnicodeString & iAssertStr);

  static void MakeAssert();

  static void ExitForODT(const CATLONG32);

  // Utility functions for streaming
  // -------------------------------

  static CATUnicodeString PeekStr(      CATCGMStream     & iStream,
                                  const CATUnicodeString & iHeader,
                                        short            & ioCounter);

  // Utility functions for geometry objects
  // --------------------------------------

  static CATGeometry* HasParent(CATGeometry * iGeom);

  static CATGeometry* HasParent_PCurve(CATPCurve * iPC);

  // Please add specific types below (see private utilities for geometry trace)
  void DumpGeometry(const int           iCategory,
                    const int           iLevel,
                    const CATGeometry * iGeom);
  
  void DumpGeometry(const int            iCategory,
                    const int            iLevel,
                    const CATMathCurve * iMathCurve);
  
  void DumpGeometry(const int                  iCategory,
                    const int                  iLevel,
                    const CATMathAdvancedBox * iBox);
  
  void DumpGeometry(const int                  iCategory,
                    const int                  iLevel,
                    const CATKnotVector      * iKV);

  // Utility functions for operators
  // -------------------------------

  static void OperatorHeader(CATCGMOperator * iOp, const CATLONG32 iCount, CATLONG32 & ioIndent);
  static void OperatorFooter(CATCGMOperator * iOp, const CATLONG32 iCount,CATLONG32 & ioIndent);

  static CATUnicodeString StringFromOperatorID(CATCGMOperator * iOp);
  static CATUnicodeString GetIndent(const CATLONG32 iNumSpaces);

  // Utility functions for trace
  // ---------------------------

  static CATUnicodeString LevelStr(CATSoftwareConfiguration * iConfig);

  static void PrintKnotVectorCache(const CATSurface * iSurface);
  static void PrintKnotVectorCache(const CATCurve   * iCurve);

  static CATUnicodeString StringFromStatus(const HRESULT iStatus);

  static CATUnicodeString StringFromIntersectionSign     (const CATSurface*, const CATIntersectionSign);
  static CATUnicodeString StringFromIntersectionSign     (const CATIntersectionSign);
  static CATUnicodeString StringFromIntersectionCrossing (const CATSurface*, const CATIntersectionCrossing);
  static CATUnicodeString StringFromIntersectionCrossing (const CATIntersectionCrossing);
  
  static CATUnicodeString StringFromCivilCurveType       (const CATCivilCurveType & iType);
  static CATUnicodeString StringFromCivilCurveOrientation(const CATCivilInput_ClockOrientation & iOrientation);
  static CATUnicodeString StringFromCivilCurveParamType  (const CATCivilCurveDef::ParamType & iType, const CATBoolean iFixedLength = TRUE);
  static CATUnicodeString StringFromCivilCurveStatus     (const CATCivilCurveDef::CATCivilRunStatus & iStatus);

  static CATUnicodeString StringFromClashClassification(const CATClash2D::CATClash2DClassification & iClassification);

  static CATUnicodeString StringForID(const CATGeometry*, const CATBoolean iLong = FALSE);

  static CATUnicodeString GetTag(const CATGeometry*);
  static CATUnicodeString GetTag(const CATULONG32);
  static CATUnicodeString GetAddr(const void*);

  static CATUnicodeString StringFromFactoryScale(const CATGeoFactory*);

  static CATUnicodeString StringFromString(const CATUnicodeString, const int);

  static CATUnicodeString StringFromAngle(const CATAngle);
  static CATUnicodeString StringFromAngleArray(const CATAngle[], const CATLONG32);

  static CATUnicodeString StringFromDoubleArraySpaced(const double[], const CATLONG32, const CATLONG32, const XscaleLevel & iScalePower   ,
                                                      const int iDecPt = -1);
  static CATUnicodeString StringFromDoubleArraySpaced(const double[], const CATLONG32, const CATLONG32, const XscaleLevel   iScalePowers[],
                                                      const int iDecPt = -1);

  static CATUnicodeString StringFromDoubleArray(const double[], const CATLONG32, const XscaleLevel & iScalePower   , const int iDecPt = -1);
  static CATUnicodeString StringFromDoubleArray(const double[], const CATLONG32, const XscaleLevel   iScalePowers[], const int iDecPt = -1);

  static CATUnicodeString StringFromDouble(const double , const XscaleLevel & iScalePower, const int iDecPt = -1);
  static CATUnicodeString StringFromDouble(const double*, const XscaleLevel & iScalePower, const int iDecPt = -1);

  static CATUnicodeString StringFromShortArray(const short[], const CATLONG32, const char* iFormat = NULL);
  static CATUnicodeString StringFromShort(const short, const char* iFormat = NULL);

  static CATUnicodeString StringFromIntArray(const int[], const CATLONG32);
  static CATUnicodeString StringFromInt(const int);
  static CATUnicodeString StringFromIntList(const CATListOfInt & iIntList);

  static CATUnicodeString StringFromIntPtrArray(const CATINTPTR[], const CATLONG32);
  static CATUnicodeString StringFromIntPtr(const CATINTPTR);

  static CATUnicodeString StringFromUIntArray(const unsigned int[], const CATLONG32, const char* iFormat = NULL);
  static CATUnicodeString StringFromUInt(const unsigned int, const char* iFormat = NULL);

  static CATUnicodeString StringFromLongArray(const long[], const CATLONG32);
  static CATUnicodeString StringFromLong(const long);

  static CATUnicodeString StringFromULongArray(const unsigned long[], const CATLONG32, const char* iFormat = NULL);
  static CATUnicodeString StringFromULong(const unsigned long, const char* iFormat = NULL);

  static CATUnicodeString StringFromCATLONG32Array(const CATLONG32[], const CATLONG32);
  static CATUnicodeString StringFromCATLONG32(const CATLONG32);

  static CATUnicodeString StringFromCATULONG32Array(const CATULONG32[], const CATLONG32);
  static CATUnicodeString StringFromCATULONG32(const CATULONG32);

  static CATUnicodeString StringFromCATBooleanArray(const CATBoolean[], const CATLONG32, const short iMode = 0);
  static CATUnicodeString StringFromCATBoolean(const CATBoolean, const short iMode = 0);

  static CATUnicodeString StringFromMathPoint(const CATMathPoint & iPoint, const int iDecPt = -1);
  static CATUnicodeString StringFromMathPoint(const double iCoord[], const int iDecPt = -1);
  static CATUnicodeString StringFromMathPoint2D(const CATMathPoint2D & iPoint, const int iDecPt = -1);
  static CATUnicodeString StringFromMathPoint2D(const double iCoord[], const int iDecPt = -1);
  static CATUnicodeString StringFromCartesianPoint(const CATCartesianPoint* iPoint, const int iDecPt = -1);

  static CATUnicodeString StringFromDirection(const CATMathDirection & iDir, const int iDecPt = -1);
  static CATUnicodeString StringFromDirection(const CATMathVector & iVec, const int iDecPt = -1);
  static CATUnicodeString StringFromDirection2D(const CATMathDirection2D & iDir, const int iDecPt = -1);
  static CATUnicodeString StringFromDirection2D(const CATMathVector2D & iVec, const int iDecPt = -1);
  
  static CATUnicodeString StringFromVector(const CATMathVector & iVec, const int iDecPt = -1); // typically scale as length
  static CATUnicodeString StringFromVector(const CATMathVector & iVec, const XscaleLevel & iScalePower, const int iDecPt = -1);

  static CATUnicodeString StringFromVector2D(const CATMathVector2D & iVec, const int iDecPt = -1); // typically scale as length
  static CATUnicodeString StringFromVector2D(const CATMathVector2D & iVec, const XscaleLevel & iScalePower, const int iDecPt = -1);

  static CATUnicodeString StringFromMathInterval(const CATMathInterval&, const XscaleLevel & iScalePower, const int iDecPt = -1);

  static CATUnicodeString StringFromMathBox(const CATMathBox&, const short, const int iDecPt = -1);
  static CATUnicodeString StringFromMathPlane(const CATMathPlane &, const short iMode);

  static CATUnicodeString StringFromSetOfLongs(const CATMathSetOfLongs*);
  static CATUnicodeString StringFromSetOfCrvParams(const CATSetOfCrvParams*);

  static CATUnicodeString StringFromSetOfPointsND(const CATMathSetOfPointsND &, const CATLONG32, const XscaleLevel &, const int iDecPt = -1);
  static CATUnicodeString StringFromSetOfPointsNDStart(const CATMathSetOfPointsND &, const XscaleLevel &, const int iDecPt = -1);
  static CATUnicodeString StringFromSetOfPointsNDEnd(const CATMathSetOfPointsND &, const XscaleLevel &, const int iDecPt = -1);
         
  void PrintMathInterval             (const CATMathInterval2D&, const XscaleLevel & iScalePower, const int iDecPt = -1);
  void PrintMathIntervalND           (const CATMathIntervalND&, const XscaleLevel & iScalePower, const int iDecPt = -1);

  void PrintSetOfPointsND            (const CATMathSetOfPointsND*, const XscaleLevel & iScalePower   , const CATLONG32 iDim = -1);
  void PrintSetOfPointsND            (const CATMathSetOfPointsND*, const XscaleLevel   iScalePowers[], const CATLONG32 iDim = -1);

  void PrintSetOfPointsNDTwoTangents (const CATMathSetOfPointsNDTwoTangents*, const XscaleLevel & iScalePower, const CATLONG32 iDim = -1);
  void PrintSetOfPointsNDWithVectors (const CATMathSetOfPointsNDWithVectors*, const XscaleLevel & iScalePower, const CATLONG32 iDim = -1);

  void PrintSetsOfPointsND           (const CATMathSetOfPointsND**, const CATLONG32 iNumSets, const XscaleLevel & iScalePower   ,
                                      const CATLONG32 iDim = -1);
  void PrintSetsOfPointsND           (const CATMathSetOfPointsND**, const CATLONG32 iNumSets, const XscaleLevel   iScalePowers[],
                                      const CATLONG32 iDim = -1);

  void PrintSetsOfPointsNDTwoTangents(const CATMathSetOfPointsNDTwoTangents**, const CATLONG32 iNumSets, const XscaleLevel & iScalePower,
                                      const CATLONG32 iDim = -1);
  void PrintSetsOfPointsNDWithVectors(const CATMathSetOfPointsNDWithVectors**, const CATLONG32 iNumSets, const XscaleLevel & iScalePower,
                                      const CATLONG32 iDim = -1);

  void PrintSummary(const int iCategory, const int iLevel, const CATMathSetOfPointsND * iSet);

  void PrintMatrix(const CATMathNxNFullMatrix*, const XscaleLevel & iScalePower);
  void PrintMatrix(const double*, const CATLONG32, const CATLONG32, const XscaleLevel & iScalePower);

  void PrintTransformation(const CATMathTransformation2D & iTransfo);

  void PrintArrayOfMarchingDiagnostics(const CATLONG32 iNumDiags, const CATMathStopDiagnostic           iDiags[]);
  void PrintArrayOfMarchingDiagnostics(const CATLONG32 iNumDiags, const CATMathStopDiagnostic * const * iDiags);

  // Surface
  static CATUnicodeString StringFromSurParam(const CATSurface*, const double, const double, const short iMode = 0, const int iDecPt = -1);
  static CATUnicodeString StringFromSurParam(const CATSurParam &, const short iMode = 0, const int iDecPt = -1);
  static CATUnicodeString StringFromSurParamSet(const CATSetOfSurParams &, const CATLONG32, const short iMode = 0, const int iDecPt = -1);
  static CATUnicodeString StringFromSurLimits(const CATSurLimits &, const short iMode = 0, const int iDecPt = -1);
  static CATUnicodeString StringFromSurLimits(const CATSurLimits *, const short iMode = 0, const int iDecPt = -1);

  // Curve
  static CATUnicodeString StringFromCurveParam(const CATCrvParam & iParam,
                                               const short         iMode = 0,
                                               const int           iDecPt = -1);

  static CATUnicodeString StringFromCurveParam(const CATVirtualCrvParam & iParam,
                                               const CATVirtualCurve    & iCrv,
                                               const short                iMode = 0,
                                               const int                  iDecPt = -1);

  static CATUnicodeString StringFromCurveLimits(const CATCrvLimits&, const int iDecPt = -1);
  static CATUnicodeString StringFromCurveLimits(const CATCrvLimits*, const int iDecPt = -1);
  static CATUnicodeString StringFromCurveLimits(const CATCurve*);
  static CATUnicodeString StringFromCurveLimits(const CATVirtualCurve&);

  static CATUnicodeString StringFromCurveLimitsEval(const CATLISTP(CATCurve)*);
  static CATUnicodeString StringFromCurveLimitsEval(const CATCurve*);
  static CATUnicodeString StringFromCurveLimitsEval(const CATCurve*, const CATBoolean);

  // P-curve
         //CATUnicodeString StringFromPCurveType(const CATPCurve*) const;
  static CATUnicodeString StringFromPCurveLimitsUV(const CATPCurve*);
  static CATUnicodeString StringFromPCurveParamUV(const CATPCurve*, const CATCrvParam&);

  static CATUnicodeString StringFromMathDiagnostic(const CATMathDiagnostic iDiag);
  static CATUnicodeString StringFromMarchingDiagnostic(const CATMathStopDiagnostic * iDiag);
  static CATUnicodeString StringFromMarchingDiagnostic(const CATMathStopDiagnostic   iDiag);
  static CATUnicodeString StringFromMarchingDiagnostic(/*const*/ CATMathImplicitSystem * iSystem);

  static CATUnicodeString StringFromIsoPar(const CATIsoParameter);

  //static CATUnicodeString CurveType(const CATCurve * const iCurve);
  //static CATUnicodeString SurfaceType(const CATSurface * const iSurface);

  // CGM replay functions
  //--------------------------------------------------------------------------------------------
public:

  static void CheckAndActivateCGMReplay(const CATGeometry * iGeom);
  static void CheckAndActivateCGMReplay(const CATUnicodeString & iType);

private:

  void DoCheckAndActivateCGMReplay(const CATGeometry* iGeom) const;
  void DoCheckAndActivateCGMReplay(const CATUnicodeString & iType) const;


  // Call stack
  //--------------------------------------------------------------------------------------------

public:

  void DumpCallStack(const int iCategory,
                     const int iLevel);
  
private:

  void DumpCallStack();

  // Utility functions for X-scale
  //--------------------------------------------------------------------------------------------

public:

  void SetToleranceObject(const CATTolerance*);
  void SetToleranceObject(const CATGeoFactory*);
  const CATTolerance* GetToleranceObject() const;

  // Utility functions
  //--------------------------------------------------------------------------------------------
  
public:

  static CATBoolean SurParamFromPointOnSurface(const CATPointOnSurface*, CATSurParam &, const CATSurface* = NULL);
  static CATBoolean SurParamFromPointOnPCurve(const CATPointOnCurve*   , CATSurParam &, const CATSurface* = NULL);
  
  static CATSurface* FindSupportSurface(CATGeoFactory * iFactory, const CATSurLimits         & iLimits);
  static CATSurface* FindSupportSurface(CATGeoFactory * iFactory, const CATSurParam          & iParam);
  static CATSurface* FindSupportSurface(CATGeoFactory * iFactory, const CATSurParamReference * iParamRef);

  static void SwapBooleans(CATBoolean &, CATBoolean &);
  static void SwapSurfacePointers(CATSurface*&, CATSurface*&);
  static void SwapMathPointPointers(CATMathPoint*&, CATMathPoint*&);
  static void SwapSurfaceLimits(CATSurLimits&, CATSurLimits&);
  static void SwapMathBoxes(CATMathBox&, CATMathBox&);
  static void SwapSetOfSurParams(CATSetOfSurParams&, CATSetOfSurParams&);

  // Function to print out 2D points and two axes to an NCGM file.
  // In a command window, specify the output directory for the NCGM file; e.g.,
  //     set CATCX_NCGM=1,home=D:\NCGM_Files
  CATBoolean Plot2DPointsInNCGMFile(const CATString         &       iNCGMFileName,  // without the ".NCGM" extension
                                    const int                       iNumPoints,
                                    const double            * const iParams,
                                    const double            * const iValues,
                                    const double                    iAxisOffset     = 1.0,
                                    const CATPositiveLength         iUnitInMetres   = 0.001) const;

  // Utility functions for ODT debug
  //--------------------------------------------------------------------------------------------

  static CATBoolean SaveFactory(const CATUnicodeString & iFileName, // without the .NCGM extension
                                      CATGeoFactory    * iFactory);
  
  // Utility functions for factory
  //--------------------------------------------------------------------------------------------

  static void GetAllSurfaces(CATGeoFactory * iFactory, CATLISTP(CATSurface) & oList);

  // Utility funcions for visual debug
  //--------------------------------------------------------------------------------------------

  static void Hide(CATGeometry*);
  static void ShowAndExplicit(CATGeometry*, const int* = NULL);
  static void PutColour(CATGeometry*, const int*);

  static void SetToMaxLimits(CATGeometry* iGeom, const short iLevelRecursion);

  static CATCurve*          DrawCurve(      CATCurve         *, const int* = NULL);

  // Draw tangent / normal at a point
  static void DrawCurveData(const CATCurve    * iCurve,
                            const CATCrvParam & iParam,
                            const int         * iRGB = NULL);

  // Draw construction data
  static CATBoolean DrawCurveConstructionData(const CATCurve * iCurve);
  static CATBoolean DrawCurveConstructionData_KnotVec(const CATCurve * iCurve, const CATKnotVector * iKnotVec);
  static CATBoolean DrawCurveConstructionData_Nurbs(const CATNurbsCurve * iCurve);
  static CATBoolean DrawCurveConstructionData_Spline(const CATSplineCurve * iCurve);
  static CATBoolean DrawCurveConstructionData_Circle(const CATCircle * iCurve);

  static CATBoolean DrawCurveConstructionData_PCurve(const CATPCurve * iCurve);
  static CATBoolean DrawCurveConstructionData_PNurbs(const CATPNurbs * iCurve);
  static CATBoolean DrawCurveConstructionData_PSpline(const CATPSpline * iCurve);
  static CATBoolean DrawCurveConstructionData_PCircle(const CATPCircle * iCurve);


  static CATBoolean DrawSurfaceConstructionData(const CATSurface * iSurface);
  static CATBoolean DrawSurfaceConstructionData_Nurbs(const CATNurbsSurface * iNurbs);
  static CATBoolean DrawSurfaceConstructionData_Fillet(const CATGenericFillet * iFillet);
  static CATBoolean DrawSurfaceConstructionData_Ruled(const CATGenericRuledSurface * iRuledSurf);

  static void DrawSurfaceLimits(const CATSurface   * iSurface,
                                const CATSurLimits & iSurLimits,
                                const int          * iRGB = NULL);

  static void DrawCurveLimits(const CATCurve     * iCurve,
                              const CATCrvLimits & iCrvLimits,
                              const int          * iRGB = NULL);

  static void             DrawPointAndTangentOnSurfaces(      CATSurface const * const iSurfs[],
                                                        const double                   iPt[],
                                                        const double                   iTgt[],
                                                        const int              *       iRGB = NULL);

  static CATMathDirection DrawPointAndTangentOnSurface(const CATSurface * iSurf,
                                                       const double       iPt[],
                                                       const double       iTgt[],
                                                       const int        * iRGB = NULL);

  static CATMathDirection DrawPointAndNormalOnSurface(const CATSurface * iSurf,
                                                      const double       iPt[],
                                                      const int        * iRGB = NULL);

  static CATMathDirection DrawPointAndDerivOnSurface(const CATSurface      * iSurf,
                                                     const double            iPt[],
                                                     const CATIsoParameter   iDir,
                                                     const int             * iRGB = NULL);

  static CATPointOnSurface* DrawPointOnSurface(const CATSurface     * iSurf,
                                               const CATMathPoint2D & iPt,
                                               const int            * iRGB = NULL);

  static CATPointOnSurface* DrawPointOnSurface(const CATSurface * iSurf,
                                               const double       iPt[],
                                               const int        * iRGB = NULL);

  static CATPointOnSurface* DrawPointOnSurface(const CATSurface  * iSurf,
                                               const CATSurParam & iSurParam,
                                               const int         * iRGB = NULL);
  
  static CATLine*           DrawTangent       (const CATSurface * iSurf,
                                               const double       iPt[],
                                               const double       iTgt[],
                                               const int        * iRGB = NULL);

  static CATLine*           DrawTangent       (const CATSurface      * iSurf,
                                               const CATSurParam     & iSurParam,
                                               const CATMathVector2D & iTgt,
                                               const int             * iRGB = NULL);

  static CATCartesianPoint* DrawPoint         (      CATGeoFactory    * iFactory,
                                               const CATMathPoint     & iPt,
                                               const int              * iRGB = NULL);

  static CATCartesianPoint* DrawPoint         (      CATCartesianPoint * iPt,
                                               const int               * iRGB = NULL);

  static CATLine*           DrawLine          (      CATGeoFactory    * iFactory,
                                               const CATMathPoint     & iOrigin,
                                               const CATMathDirection & iDir,
                                               const int              * iRGB = NULL);

  static CATLine*           DrawLine          (      CATGeoFactory * iFactory,
                                               const CATMathPoint  & iOrigin,
                                               const CATMathVector & iDir,
                                               const short           iMode,
                                               const int           * iRGB = NULL);

  static CATLine*           DrawLine          (      CATGeoFactory * iFactory,
                                               const CATMathPoint  & iPt1, 
                                               const CATMathPoint  & iPt2,
                                               const int           * iRGB = NULL);
  
  static CATPLine*          DrawPLine         (const CATSurface     * iSurface,
                                               const CATMathPoint2D & iPt1,
                                               const CATMathPoint2D & iPt2,
                                               const int            * iRGB = NULL);

  static CATPLine*          DrawPLine         (const CATSurface  * iSurface,
                                               const CATSurParam & iPar1,
                                               const CATSurParam & iPar2,
                                               const int         * iRGB = NULL);

  static void               DrawBox           (      CATGeoFactory           * iFactory,
                                               const CATMathBox              & iBox,
                                               const int                     * iRGB = NULL);

  static void               DrawBox           (      CATGeoFactory           * iFactory,
                                               const CATMathBox              & iBox,
                                                     CATLISTP(CATICGMObject) & oListObjDrawn,
                                               const int                     * iRGB = NULL);

  static void               DrawBox           (      CATGeoFactory           * iFactory,
                                               const CATMathOBB              & iOBB,
                                                     CATLISTP(CATICGMObject) & oListObjDrawn,
                                               const int                     * iRGB= NULL);

  static void               DrawBox           (      CATGeoFactory           *,
                                               const CATMathOBB2D            & iOBB,
                                                     CATLISTP(CATICGMObject) & oListObjDrawn,
                                               const int                     * iRGB = NULL);

  void                      Visual_DrawLine   (CATGeoFactory*, const CATMathPoint&,   const CATMathPoint&,   char *, const int* = NULL );
  void                      Visual_DrawLine   (CATGeoFactory*, const CATMathPoint2D&, const CATMathPoint2D&, char *, const int* = NULL );
  
  static void SetCurveLimits(CATCurve*, const double);
  static void SetCurveLimits(CATCurve*, const double, const double);

  static CATPointOnCurve* DrawPointOnCurve(const CATCurve      * iCurve,
                                           const CATCrvParam   & iCrvParam,
                                           const int           * iRGB = NULL);

  static CATPointOnCurve* DrawPointOnCurve(const CATCurve      * iCurve,
                                           const double          iCrvParamValue,
                                           const int           * iRGB = NULL);

  static CATPointOnCurve* DrawPointAndTangentOnCurve(const CATCurve    * iCurve,
                                                     const CATCrvParam & iCrvParam,
                                                     const int         * iRGB = NULL);

  static CATPointOnCurve* DrawPointAndTangentOnCurve(const CATCurve * iCurve,
                                                     const double     iCrvParamValue,
                                                     const int      * iRGB = NULL);

  static CATPointOnCurve* DrawPointOnPCurve(const CATPCurve      * iPCurve,
                                            const CATCrvParam   & iCrvParam,
                                            const int           * iRGB = NULL);

  static CATPointOnCurve* DrawPointOnPCurve(const CATPCurve      * iPCurve,
                                            const CATMathPoint2D & iPt,
                                            const int            * iRGB = NULL);

  static CATPointOnCurve* DrawPointAndTangentOnPCurve(const CATPCurve * iPCurve,
                                                      const double      iCrvParamValue,
                                                      const int       * iRGB = NULL);

  static CATPointOnCurve* DrawPointAndTangentOnPCurve(const CATPCurve   * iPCurve,
                                                      const CATCrvParam & iCrvParam,
                                                      const int         * iRGB = NULL);

  static void DrawArrowOnPCurve(const CATPCurve  * const iPCurve,
                                const CATBoolean         iDrawAtStart,
                                const int        * const iRGB = NULL);

  // Visual debug
  static void DrawSetOfPoints(const CATMathSetOfPointsND * iPoints,
                              const CATGeometry          * iGeom,
                              const CATLONG32              iDim);

  static void DrawSetOfPoints(const CATMathSetOfPointsND * iPoints,
                              const CATGeometry          * iGeom1,
                              const CATGeometry          * iGeom2,
                              const CATLONG32              iDim1,
                              const CATLONG32              iDim2);

  // Plot all the points in an CATMathSetOfPointsND at dimension index iDimIndex, with colour RGB = (iRed, iGreen, iBlue) 
  static void Plot3DPoints(CATGeoFactory        * iFactory, 
                           CATMathSetOfPointsND * iPoints,
                           CATLONG32              iDimIndex,
                           short                  iRed,
                           short                  iGreen,
                           short                  iBlue);

  // Plot the point in an CATMathSetOfPointsND at index iIndex, dimension index iDimIndex, with colour RGB = (iRed, iGreen, iBlue) 
  static void Plot3DPoint(CATGeoFactory        * iFactory, 
                          CATMathSetOfPointsND * iPoints,
                          CATLONG32              iIndex,
                          CATLONG32              iDimIndex,
                          short                  iRed,
                          short                  iGreen,
                          short                  iBlue);

  // Plot the 3D point (iPoint[0], iPoint[1], iPoint[2]), with colour RGB = (iRed, iGreen, iBlue)
  static void Plot3DPoint(      CATGeoFactory * iFactory,
                          const double  * iPoint,
                                short           iRed,
                                short           iGreen,
                                short           iBlue);

  static void PlotFunction3D(      CATGeoFactory    *       iFactory,
                             const CATMathFunctionX * const iFunc[],
                             const CATMathInterval  &       iRange,
                             const CATLONG32                iNumSample = 100,
                             const int              *       iRGB = CATGeoOpDebug::_Colour_Green);

  private:

  static void DoPlotFunction3D(      CATGeoFactory    *       iFactory,
                               const CATMathFunctionX * const iFunc[],
                               const CATMathInterval  &       iRange,
                               const CATLONG32                iNumSample,
                               const int              *       iRGB);

  public:

  // Set variables from environment
  //--------------------------------------------------------------------------------------------

  void SetValueFromEnvVar(const int               iCategory,
                                CATLONG32       & ioValue,
                          const CATMathInterval & iInterval) const;

  void SetValueFromEnvVar(const int         iCategory,
                                CATLONG32 & ioValue,
                          const CATLONG32 * iMinValue = NULL,
                          const CATLONG32 * iMaxValue = NULL) const;
  
  void SetValueFromEnvVar(const int               iCategory,
                                double          & ioValue,
                          const CATMathInterval & iInterval) const;

  void SetValueFromEnvVar(const int      iCategory,
                                double & ioValue,
                          const double * iMinValue = NULL,
                          const double * iMaxValue = NULL) const;

  void SetValueFromEnvVar(const int          iCategory,
                                CATBoolean & ioValue,
                          const CATBoolean * iNotUsed = NULL) const; // the last argument is simply to make the macro overloading works=


public:

  // Versionning functions
  //--------------------------------------------------------------------------------------------

  short GetVersioningLevelFromFlag(const int iCategory) const;

public:

  // Visual Interactive Debug
  //--------------------------------------------------------------------------------------------

  static CATCGMDocument* GetDocumentCGM(const CATGeometry* iGeom);
  static CATBoolean CheckDocumentIsActive(const CATGeometry * iGeom);

  CATCGMActivateDebug * GetVisual();
  void                  MakeCheckPoint(const CATString &);

  void RemoveVisual();

  static void UpdateView(CATGeoFactory*);
  static void UpdateView(CATGeometry*);

  static CATPointOnCurve * CreateSymbol(      CATCurve                  * iCurve, 
                                        const CATCrvParam               & iParam,
                                              CATCGMDebugUI::SymbolType   iSymbol,
                                              int                         iRed,
                                              int                         iGreen,
                                              int                         iBlue );

  static void CreateSymbol(      CATGeoFactory             * iFactory, 
                           const CATPoint                  * iPoint,
                                 CATCGMDebugUI::SymbolType   iSymbol,
                                 int                         iRed,
                                 int                         iGreen,
                                 int                         iBlue );

  static CATUnicodeString ConcatStrings(const CATUnicodeString & iTextToAdd,
                                        const CATUnicodeString & iTextToAppend);

  static CATUnicodeString ConcatStrings(const CATUnicodeString & iTextToAdd,
                                        const CATLONG32          iNumToAppend);
  
  static CATUnicodeString ConcatStrings(const CATUnicodeString & iTextToAdd,
                                        const CATUnicodeString & iTextToAppend,
                                        const CATLONG32          iNumToAppend);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                                CATGeoFactory    * iFactory,
                          const CATLONG32        & iTag,
                          const int              * iRGB = NULL);
  
  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATLONG32          iNumToAppend,
                          const CATGeometry      * iGeometry,
                          const int              * iRGB = NULL);
  
  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATGeometry      * iGeometry,
                          const int              * iRGB = NULL);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATPoint         * iPoint,
                          const int              * iRGB = NULL);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATCurve         * iCurve,
                          const int              * iRGB = NULL);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATCurve         * iCurve,
                          const double             iFractionLimits,
                          const int              * iRGB = NULL);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATCurve         * iCurve,
                          const CATCrvParam      & iCurvePar,
                          const int              * iRGB = NULL);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                          const CATSurface       * iSurface,
                          const int              * iRGB = NULL);

  static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                          const CATUnicodeString & iTextToAdd,
                                CATGeoFactory    * iFactory,
                          const CATMathOBB       & iBox,
                          const int              * iRGB = NULL);

  private:

    static void CreateLabel(const CATUnicodeString & iOperatorLabel,
                            const CATUnicodeString & iTextToAdd,
                            const CATGeometry      * iGeometry,
                            const CATMathPoint     & iPoint,
                            const int              * iRGB = NULL);

    void PrintSetOfPointsNDAsDoubles(const CATMathSetOfPointsND * iSetOfPoints,
                                     const XscaleLevel          & iScalePower,
                                     const CATLONG32              iDim = -1);

    static void GetSetOfPointsDims(const CATMathSetOfPointsND * iSetOfPoints,
                                   const CATLONG32            & iDim,
                                         CATLONG32            & oSetDim,
                                         CATLONG32            & oDimToPrint);

  // Static Data
  // -----------
protected:
  static CATGeoOpAllTimers _TheGeoOpTimers;
  static CATBoolean        _AllTimersOn;
  
  static CATGeoOpDebug   * _TheGeoOpDebug;
         CATBoolean        _Hide;

private:

  // Initialisation
  // --------------

  void CommonInitialize();

  void InitialiseTrace();
  void InitialiseFunction();
  void InitialiseVisual();
  void InitialiseVersion();
  void InitialiseCounters();
  void InitialiseEnvironmentVars();
  void InitialiseTimers();
  void InitialiseCGMReplay();
  void InitialiseCGMReplayTags();
  void InitialiseCGMReplayTypes();

  // Private utilities for this class
  // --------------------------------

  void ReadOutputFilePath();
  void InitializeOutputStream();

  // Private utilities for trace
  // ---------------------------

  enum GeopDebugEnvSearchType{ NotSet = -1, SetDefault, SetSpecific };

  static GeopDebugEnvSearchType GetDebugLevel(const TYPE::DEBUG_TYPES         iType,
                                              const CATUnicodeString  &       iCategory,
                                              const char              * const iEnvValue,
                                              int                     &       oLevel);

  int       GetDebugLevel(const TYPE::DEBUG_TYPES iType,
                          const int               iCategory) const;

  // Use _CurrentCategory and _CurrentLevel
  void      OutputPrompt(CATCGMOutput & iOS);
  void      OutputShift(CATCGMOutput & iOS);

  void      UpdateInternalTraceCache(const int iCategory,
                                     const int iLevel);

  CATLONG32 OutputTrace(const char * iTrace = NULL); // use _CurrentCategory and _CurrentLevel
  void      OutputTrace(CATCGMOutput & iOS, const CATUnicodeString iTrace, const CATBoolean iNewLine);

  // Private utilities for X-scale trace
  // -----------------------------------

  static const double GetScale();
  static const CATBoolean XScaleCompare(const XscaleLevel &);
  static const double UnscaleValue(const double, const XscaleLevel &);

  // Private utilities for geometry trace
  // ------------------------------------

  CATBoolean DumpGeometryData    (const CATGeometry * iGeom, const short iIndent);

  CATBoolean DumpSurfaceData     (const CATSurface             * iSurface  , const short iIndent);
  CATBoolean DumpOffsetData      (const CATOffsetSurface       * iOffset   , const short iIndent);
  CATBoolean DumpNurbsData       (const CATNurbsSurface        * iNurbs    , const short iIndent);
  CATBoolean DumpSweepData       (const CATSweepSurface        * iSweep    , const short iIndent);
  CATBoolean DumpChamferData     (const CATChamferSurface      * iChamfer  , const short iIndent);
  CATBoolean DumpGenericRuledData(const CATGenericRuledSurface * iRuledSurf, const short iIndent);

  CATBoolean DumpCurveData(const CATCurve * iCurve, const short iIndent);
  CATBoolean DumpEdgeCurveData(const CATEdgeCurve * iEC, const short iIndent);
  CATBoolean DumpLineData(const CATLine * iLine, const short iIndent);
  CATBoolean DumpCircleData(const CATCircle * iCircle, const short iIndent);
  CATBoolean DumpNurbsData(const CATNurbsCurve * iNurbs, const short iIndent);
  CATBoolean DumpSplineData(const CATSplineCurve * iSpline, const short iIndent);

  CATBoolean DumpPCurveData(const CATPCurve * iPCurve, const short iIndent);
  CATBoolean DumpPLineData(const CATPLine * iPLine, const short iIndent);
  CATBoolean DumpPCircleData(const CATPCircle * iPCircle, const short iIndent);
  CATBoolean DumpPNurbsData(const CATPNurbs * iPNurbs, const short iIndent);
  CATBoolean DumpPSplineData(const CATPSpline * iPSpline, const short iIndent);

  CATBoolean DumpMathCircleData(const CATMathCircle * iMathCircle);
  CATBoolean DumpMathLineData(const CATMathLine * iMathLine);

  CATBoolean DumpAABBData(const CATMathAABB * iBox);
  CATBoolean DumpOBBData(const CATMathOBB * iBox, const short iIndex = -1);
  CATBoolean DumpOBBCloudData(const CATMathOBBCloud * iBoxCloud);
  CATBoolean Dump2DOBBData(const CATMathOBB2D * iBoxUV);

  CATBoolean DumpKnotVector(const CATKnotVector    * iKV,
                            const CATUnicodeString & iLabel);

  // Private utilities for debug options windows
  // -------------------------------------------

  int GetTraceLevel(const CATLONG32) const;
  void SetTraceLevel(const CATLONG32, const int);

  int GetVisualLevel(const CATLONG32) const;
  void SetVisualLevel(const CATLONG32, const int);

  int GetFunctionLevel(const CATLONG32) const;
  void SetFunctionLevel(const CATLONG32, const int);

  int GetVersionLevel(const CATLONG32) const;
  void SetVersionLevel(const CATLONG32, const int, const int);

  // Private utilities for timers
  // ----------------------------

  CATGeoOpTimer* GetTimer(const int iCategory) const;


  // Private utilities for other debug
  // ---------------------------------

  static void Remove2DPointsForNCGMFile(const CATLONG32                     iNumGeometries,
                                        const CATLISTP(CATGeometry) &       iGeometryList,
                                              CATGeoFactory         * const ioFactory);

  // Private data
  // ------------

  static CATUnicodeString _OutputPath;
  CATCGMOutput* _OutputStream; // used to output to file

  //CATCGMOutput _TmpOut; // used for internal purposes only

public:

  static const CATUnicodeString _TraceCategories[TRACE::MAX_NUM];
  static const CATUnicodeString _TraceLevelNames[TRACE::MAX_LEVEL + 1];

  static const CATUnicodeString _FunctionCategories[FUNC::MAX_NUM];
  static const CATUnicodeString _FunctionLevelNames[FUNC::MAX_LEVEL];

  static const CATUnicodeString _VisualCategories[VIS::MAX_NUM];
  static const CATUnicodeString _VisualLevelNames[VIS::MAX_LEVEL];

  static const CATUnicodeString _VersionCategories[VERS::MAX_NUM];
  static const CATUnicodeString _VersionLevelNames[VERS::MAX_LEVEL];

  static const CATUnicodeString _OperatorCategories[OPER::MAX_NUM];

  static const CATUnicodeString _TimerCategories[TIMER::MAX_NUM];

  // Colours
  // -------

  static const int _Colour_Red[3];
  static const int _Colour_RedMuted[3];
  static const int _Colour_Green[3];
  static const int _Colour_GreenMuted[3];
  static const int _Colour_Blue[3];
  static const int _Colour_BlueMuted[3];
  static const int _Colour_Yellow[3];
  static const int _Colour_YellowMuted[3];
  static const int _Colour_Turqoise[3];
  static const int _Colour_TurqoiseMuted[3];
  static const int _Colour_Magenta[3];
  static const int _Colour_MagentaMuted[3];

  static const int _Colour_Black[3];

  // X-scale levels
  // --------------

  static const XscaleLevel _ScaleInvSqSqLen;
  static const XscaleLevel _ScaleInvSqLen;
  static const XscaleLevel _ScaleInvLen;
  static const XscaleLevel _ScaleInvSqrtLen;
  static const XscaleLevel _ScaleZero;
  static const XscaleLevel _ScaleSqrtLen;
  static const XscaleLevel _ScaleLen;
  static const XscaleLevel _ScaleSqLen;
  static const XscaleLevel _ScaleVol;

private:
  
  static const XscaleLevel _ScaleUnknown;

  CATCompactCallStackManager _StackManager;

  const CATTolerance* _TolObject;

  // Current settings
  // ----------------

  int   _TraceLevels      [TRACE::MAX_NUM];
  int   _TraceNumberShifts[TRACE::MAX_NUM];
  int   _FunctionLevels   [FUNC::MAX_NUM];
  int   _VisualLevels     [VIS::MAX_NUM];
  int   _VersionLevels    [VERS::MAX_NUM];
  short _VersionValues    [VERS::MAX_NUM];
  
  CATLONG32 _OperatorCount[OPER::MAX_NUM];

  int               _OperatorTraceID;  // The index of the operator (eg MSINT)
  CATMathSetOfLongs _OperatorTraceIDs; // The replays numbers for that operator (eg 2, 5, 11)
  
  CATBoolean _TraceActive;

  CATGeoOpTimer* _TimerObjects[TIMER::MAX_NUM];

  // Variables for capturing CGM replays
  // -----------------------------------

  CATBoolean _SpecificCGMReplayCapture;
  CATMathSetOfLongs _ReplayTags; // to activate CGM replay for these geometries
  CATUnicodeString  _ReplayTypes; // to activate CGM replay for some cases (matching sub-strings)

  // Variables to read from the environment
  // --------------------------------------

  static GeopEnvVar _EnvironmentVariableData[ENV_VAR::MAX_NUM];

  static int _TraceDecPt;

  int        _CurrentCategory;
  int        _CurrentLevel;

  int        _PreviousCategory;
  int        _PreviousLevel;

  CATLONG32  _HeaderLength;
  CATLONG32  _SubHeaderLength;

  CATBoolean _PrintCount;
  CATBoolean _PrintTags;
  CATBoolean _PrintAddr;
  CATBoolean _XscaleCompare;
  
  // Other objects
  // -------------

  CATTrace            * _VisualTrace;
  CATCGMActivateDebug * _VisualInteractive;
};
#endif // CATGeoOpDebug_H
