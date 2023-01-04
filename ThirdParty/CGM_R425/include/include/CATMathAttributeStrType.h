#ifndef CATMathAttributeStrType_H
#define CATMathAttributeStrType_H

// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
//
//     Advanced mathematics operators attributes for specific parameterizations: stream types
//
//=============================================================================
// 28/07/09 NLD Creation
//=============================================================================

// N.B No value modification should be done, since these values describe stream data that must
//     still be readable in any software version
#define CATMathAttributeStrTypeNone               0
#define CATMathAttributeStrTypeIntegerValue       1
#define CATMathAttributeStrTypeDoubleValue        2
#define CATMathAttributeStrTypeString             3

/* memento: CATMathAttribute superclasses, as of July 2009
ClassName   SourceName 
CATMathAttrDecomposition AdvancedMathematics/ProtectedInterfaces/CATMathAttrDecomposition.h (l.24) 
CATMathAttrDoubleArray AdvancedMathematics/ProtectedInterfaces/CATMathAttrDoubleArray.h (l.10) 
CATMathAttrDoubleValue AdvancedMathematics/ProtectedInterfaces/CATMathAttrDoubleValue.h (l.12) 
CATMathAttrExclusion2D AdvancedMathematics/ProtectedInterfaces/CATMathAttrExclusion2D.h (l.11) 
CATMathAttrIntegerValue AdvancedMathematics/ProtectedInterfaces/CATMathAttrIntegerValue.h (l.10) 
CATMathAttrMultipleDomain AdvancedMathematics/ProtectedInterfaces/CATMathAttrMultipleDomain.h (l.24) 
CATMathAttrPointerValue AdvancedMathematics/ProtectedInterfaces/CATMathAttrPointerValue.h (l.10) 
CATMathAttrRepartition AdvancedMathematics/ProtectedInterfaces/CATMathAttrRepartition.h (l.26) 
CATMathAttrScaleOption AdvancedMathematics/ProtectedInterfaces/CATMathAttrScaleOption.h (l.19) 
CATMathAttrString AdvancedMathematics/ProtectedInterfaces/CATMathAttrString.h (l.14) 
CATMathAttrTolObject AdvancedMathematics/ProtectedInterfaces/CATMathAttrTolObject.h (l.22) 
CATMathConstraint AdvancedMathematics/ProtectedInterfaces/CATMathConstraint.h (l.13)   <--- with superclasses
CATMathConstraintOption AdvancedMathematics/ProtectedInterfaces/CATMathConstraintOption.h (l.12)   <--- with superclasses
CATMathMetric AdvancedMathematics/ProtectedInterfaces/CATMathMetric.h (l.12)   <--- with superclasses
CATMathSingularity AdvancedMathematics/ProtectedInterfaces/CATMathSingularity.h (l.12)  <--- with superclasses
*/

#endif
