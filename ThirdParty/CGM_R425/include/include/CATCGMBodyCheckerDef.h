#ifndef __CATCGMBodyCheckerDef_h__
#define __CATCGMBodyCheckerDef_h__

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

// Enumerations for Body Check Operator

/**
* enum CATCGMBodyCheckMode::CheckMode
* <br>Defines <b>Check Mode</b> for the body check operation.
* @param BodyChkModeLight
* <br>This is the <tt><b>default</b></tt> check mode for the operator, unless set by <tt>SetCheckMode</tt> method.
* <br>With this mode, all the <b>Light</b> rules would be checked during operator run.
* @param BodyChkModeFull
* <br>With this mode, <b>all</b> the published rules (i.e. Light + Full) would be checked during operator run.
* @param BodyChkModeUser
* <br>This mode comes into effect when one uses <tt>SetCheckRules</tt> method.
* <br>With this mode, only the <b>Set</b> rules (set by <tt>SetCheckRules</tt>) would be checked during operator run.
* @param BodyChkModeLightPlus
* <br>Use this mode if one wishes to check additional rules (in addition to <tt>Light</tt> rules).
* <br>For using this, first set addition rules to check by using <tt>SetCheckRules</tt> method, 
* and then set the operator check mode using <tt>SetCheckMode</tt> method to <tt>BodyChkModeLightPlus</tt>.
*/
enum CATCGMBodyCheckMode
{
  CATCGMBodyChkModeLight       = 0,
  CATCGMBodyChkModeFull        = 1,
  CATCGMBodyChkModeUser        = 2,
  CATCGMBodyChkModeLightPlus   = 3
};

/**
* enum CATCGMBodyChecker::CheckRuleID
* <br>Defines <b>Check Rules</b> for the body check operation.
* @param BodyChkRuleUndefined
* <br>Not to be used.
* @param BodyChkRuleCurvatureCurve
* <br>This rule is active in <b>Light</b> check mode.
* <br>With this rule, all the curves present in the input body (unless <tt>SetCheckCells</tt> is used) would be checked for following rule:
* <br>The "evaluated" minimum curvature radius for a curve MUST BE GREATER THAN "allowed" minimum curvature radius.
* <br>Here, "allowed" minimum curvature radius is µ (i.e. 1 micron).
* @param BodyChkRuleCurvatureSurface
* <br>This rule is active in <b>Full</b> check mode.
* <br>With this rule, all the surfaces present in the input body (unless <tt>SetCheckCells</tt> is used) would be checked for following rule:
* <br>The "evaluated" minimum curvature radius for a surface MUST BE GREATER THAN "allowed" minimum curvature radius.
* <br>Here, "allowed" minimum curvature radius is µ (i.e. 1 micron).
*/
// Pay attention: this enum is the mirror of CATCGMBodyCheckRuleID in CATCGMBodyCheckerDef.h
enum CATCGMBodyCheckRuleID
{
  // An undefined rule
  CATCGMBodyChkRuleUndefined              = 0,

  // Rules for Geometry
  CATCGMBodyChkRuleCurvatureCurve         = 1,
  CATCGMBodyChkRuleCurvatureSurface       = 2,

  // Rules for Topology
  CATCGMBodyChkRuleSelfIntersectionShell  = 31
  ,CATCGMBodyChkRuleSelfIntersectionWire   = 32,
  CATCGMBodyChkRuleTopologicalEdgeLength  = 33
};

#endif // __CATCGMBodyCheckerDef_h__
