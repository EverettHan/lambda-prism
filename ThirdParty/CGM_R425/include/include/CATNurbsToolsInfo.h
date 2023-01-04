#ifndef CATNurbsToolsInfo_H
#define CATNurbsToolsInfo_H

// COPYRIGHT DASSAULT SYSTEMES  2002

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATGMModelInterfaces.h"

/**
 * Defines all type of information that can be returned by @href CATNurbsCurveTools methods
 * when a fatal error is detected, all methods return this fatal error: 
 * an Error is returned only by the current method,
 * an Info is returned if a particular information is detected, 
 * but the method has completed without any problem.
 * @param Info_InvalidTolConfusion
 * The confusion tolerance is lower than the resolution. The resolution is used.
 * @param Info_InternalContinuity
 * The internal continuity must greater or equal to C2.
 * @param Info_ConfusedKnots
 * Two knots are confused.
 * @param Info_KnotValueOnAKnot
 * The input parameter corresponds to an existent knot.
 * @param Info_NoModification
 * No modification between input and output of this method.
 * @param Info_KnotValueOnTwoKnots
 * The value corresponds to two knots.
 * @param Info_NotAKnot
 * The value is not corresponding to any knot.
 * @param Info_OK
 * No info. It is OK.
 * @param Error_KnotRankOutLimits
 * The input rank is lower than 1 or greater than number of knots.
 * @param Error_ExtremityKnot
 * An extremity knot can not be modified or removed.
 * @param Error_KnotValueOutLimits
 * The input value is lower than the first knot value or greater than the last knot value.
 * @param Error_KnotValueOnAKnot
 * The input knot value is corresponding to an existent knot.
 * @param Error_InvalidMultiplicity
 * The input multiplicity is lower than 1 or greater than [Degree-2].
 * @param Error_InvalidDegree
 * The input degree is lower than 1 or greater than 11.
 * @param Error_InvalidContinuity
 * The input continuity is lower than 0 or greater than 2.
 * @param Error_UncompContinuities
 * [2 + startcontinuity + endcontinuity] must be lower or equal to the number of control points.
 * @param Error_InvalidMaxDegree
 * The max degree is lower than 3 or greater than 15.
 * @param Error_RunAlreadyCalled
 * The Run method must be called once.
 * @param Error_NoResultWithoutRun
 * You must call the Run method before the GetResult method.
 * @param Error_InputPtrNull
 * An input pointer is null.
 * @param Error_PtrNull
 * A pointer is null.
 * @param Error_Algorithm
 * Unexpected configuration in the algorithm.
 * @param Error_InputNotNurbs
 * The input must be a Nurbs.
 * @param Error_InconsistentInput
 * The input is inconsistent.
 * @param Fatal_PtrNull
 * A pointer is null.
 * @param Fatal_PtrInputFactoryNull
 * The factory pointer is null.
 * @param Fatal_PtrInputNull
 * The input pointer is null.
 * @param Fatal_InputNotNurbs
 * The input must be a Nurbs.
*/
enum CATNurbsToolsInfo
{
  Info_InvalidTolConfusion  =  -7, 
  Info_InternalContinuity   =  -6, 
  Info_ConfusedKnots        =  -5,  
  Info_KnotValueOnAKnot     =  -4, 
  Info_NoModification       =  -3, 
  Info_KnotValueOnTwoKnots  =  -2, 
  Info_NotAKnot             =  -1, 
  Info_OK                   =   0, 
  Error_KnotRankOutLimits   =   1, 
  Error_ExtremityKnot       =   2, 
  Error_KnotValueOutLimits  =   3, 
  Error_KnotValueOnAKnot    =   4, 
  Error_InvalidMultiplicity =   5, 
  Error_InvalidDegree       =   6, 
  Error_InvalidContinuity   =   7, 
  Error_UncompContinuities  =   8, 
  Error_InvalidMaxDegree    =   9, 
  Error_RunAlreadyCalled    =  20, 
  Error_NoResultWithoutRun  =  21, 
  Error_InputPtrNull        =  50, 
  Error_PtrNull             =  51, 
  Error_Algorithm           =  52, 
  Error_InputNotNurbs       =  53, 
  Error_InconsistentInput   =  54, 
  Fatal_PtrNull             = 100, 
  Fatal_PtrInputFactoryNull = 101, 
  Fatal_PtrInputNull        = 102, 
  Fatal_InputNotNurbs       = 103  
};

/**
 * Determines whether the info is a fatal error.
 * @param iInfo
 * The info.
 * @return
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>the info is not a fatal error.
 *     <dt><tt>1</tt> <dd>the info is a fatal error.</dl>
 */
ExportedByCATGMModelInterfaces int IsFatal (CATNurbsToolsInfo iInfo);

/**
 * Determines whether the info is an error.
 * @param iInfo
 * The info.
 * @return
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>the info is not an error.
 *     <dt><tt>1</tt> <dd>the info is an error.</dl>
 */
ExportedByCATGMModelInterfaces int IsError (CATNurbsToolsInfo iInfo);

/**
 * Determines whether the info is OK.
 * @param iInfo
 * The Info.
 * @return
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>the info is not OK (error or info).
 *     <dt><tt>1</tt> <dd>the info is OK.</dl>
 */
ExportedByCATGMModelInterfaces int IsOK    (CATNurbsToolsInfo iInfo);

/**
 * Determines whether the CATNurbsToolsInfo is an information.
 * @param iInfo
 * The info.
 * @return
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>the CATNurbsToolsInfo is not information.
 *     <dt><tt>1</tt> <dd>the CATNurbsToolsInfo is an information.</dl>
 */
ExportedByCATGMModelInterfaces int IsInfo  (CATNurbsToolsInfo iInfo);


#endif
