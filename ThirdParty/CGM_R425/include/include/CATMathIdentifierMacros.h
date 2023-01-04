//=============================================================================
/// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATMathIdentifierMacros :
// Simple macro to identify math object
// 
//==========================================================================
// Usage Notes:
//
//==========================================================================
// 14/03/17 F1Z : Creation
// DD/MM/YY
//========================================================================== 

#ifndef CATMathIdentifierMacros_H
#define CATMathIdentifierMacros_H

#include <string.h>

#define DECLARE_ABSTRACT_SIMPLE_IDENTIFIER() \
   virtual CATMathClassId IsA       ()                               const = 0;\
   virtual CATBoolean     IsAKindOf (const CATMathClassId iClassId ) const = 0;

#define DECLARE_SIMPLE_IDENTIFIER() \
   virtual CATMathClassId IsA       ()                               const;\
   virtual CATBoolean     IsAKindOf (const CATMathClassId iClassId ) const;

#define DEFINE_SIMPLE_IDENTIFIER_NOMOTHERCLASS(ClassName) \
   CATMathClassId ClassName::IsA() const { return #ClassName;} \
   CATBoolean     ClassName::IsAKindOf(const CATMathClassId iClassId) const { return (strcmp(iClassId,#ClassName)==0);}

#define DEFINE_SIMPLE_IDENTIFIER(ClassName, MotherClassName) \
   CATMathClassId ClassName::IsA() const { return #ClassName;} \
   CATBoolean     ClassName::IsAKindOf(const CATMathClassId iClassId) const { \
      CATBoolean Ok = FALSE;\
      if ((strcmp(iClassId,#ClassName)==0))\
         Ok = TRUE;\
      else if (MotherClassName::IsAKindOf(iClassId))\
         Ok = TRUE;\
      return Ok ; \
   }


#endif

