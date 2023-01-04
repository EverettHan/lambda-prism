#ifndef CATICGMObjectImplementCGMV5Interop_H
#define CATICGMObjectImplementCGMV5Interop_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//============================================================================
//      Dedicated to INTERNAL CGM USE
//  Macro-Definition for Default interface-implementation of CATICGMObject
//============================================================================
#include "CATICGMObject.h"
#include "CATTolerance.h"

#define CATICGMObjectImplementCGMV5InteropGetToleranceObject(i) i->GetToleranceObject() 

#ifndef CATICGMObjectImplementCGMV5Interop
#define CATICGMObjectImplementCGMV5Interop(CLASS,implementation,ImpossibleOperation) \
  \
 void               CLASS::Completed(CATBoolean IsNoMoreModifiable,         \
                                      const char IdentityBuildOperator[], const CATTopData  * iData)   \
{ \
  implementation->Completed(IsNoMoreModifiable,IdentityBuildOperator,iData); \
} \
  \
 void               CLASS::CompletedFreeze(CATCGMOperator *iOperator)       \
{ \
  implementation->CompletedFreeze(iOperator); \
} \
  \
  \
ULONG __stdcall CLASS::CATAddRefFrom(void *iForDebug, CATBoolean iLockEquation) \
{ \
  return AddRef(); \
} \
  \
ULONG __stdcall CLASS::CATReleaseFrom(void *iForDebug, CATBoolean iLockEquation) \
{ \
  return Release(); \
} \
  \
 void*     CLASS::GetImplementCGM(CATGeometricType iTypeReference)  const \
{ \
  return NULL; \
} \
  \
 void*     CLASS::IsCGMV5()  const \
{ \
  return NULL; \
} \
  \
int     CLASS::IsSameTypeAs(CATICGMUnknown * iOtherObject)  const \
{ \
  return 0; \
} \
const CATTolerance &     CLASS::GetToleranceObject() const \
{ \
  return CATICGMObjectImplementCGMV5InteropGetToleranceObject(implementation) ;  \
} \
 int       CLASS::IsImplementCGMRemoved(const CATGeometricType iTypeReference)  const \
{ \
  return 0; \
} \
  \
 CATBoolean         CLASS::IsModifiable()      \
{ \
  ImpossibleOperation; \
  return FALSE; \
} \
  \
 CATBoolean         CLASS::HasBeenCompletedAsNoMoreModifiable() const   \
{ \
  return TRUE; \
} \
  \
 CATBoolean         CLASS::HasBeenLoaded() const  \
{ \
  return FALSE; \
} \
  \
 CATULONG32       CLASS::GetUseCount(CATCGMUseCountType iUseType) const  \
{ \
  return implementation->GetUseCount(iUseType); \
} \
  \
 CATULONG32       CLASS::GetPersistentTag() const \
{ \
  return implementation->GetPersistentTag(); \
} \
  \
 CATGeoFactory*     CLASS::GetContainer(CATBoolean iThrowOnNullFactory, CATCGMMode iMode) \
{ \
  return implementation->GetContainer(iThrowOnNullFactory,iMode); \
} \
  \
 void               CLASS::SetMode(CATCGMMode iMode)  \
{ \
  ImpossibleOperation; \
  implementation->SetMode(iMode); \
} \
  \
 CATLONG32               CLASS::IsExplicit() const  \
{ \
  return implementation->IsExplicit(); \
} \
  \
 int                CLASS::IsATypeOf(CATGeometricType iTypeReference) const  \
{ \
  return 1; \
} \
  \
 void               CLASS::GetLinks(CATLISTP(CATICGMObject) &oLinks ,            \
                                     CATCGMLinkType          iLinkType     ,     \
                                     CATRCOLL(int)*          oSharedStatus ,     \
                                     CATLISTV(CATString)*    oLinksString  )     \
{ \
  implementation->GetLinks(oLinks,iLinkType,oSharedStatus,oLinksString); \
} \
  \
void              CLASS::GetAllLinks(CATLISTP(CATGeometry) &oLinks) \
{ \
  ImpossibleOperation; \
} \
  \
int                CLASS::Check()  \
{ \
  return implementation->Check(); \
} \
  \
 CATLONG32               CLASS::PutAttribute(CATCGMAttribute * iNewAttr)  \
{ \
  return 0; \
} \
  \
 CATCGMAttribute *  CLASS::GetAttribute(const CATCGMAttrId* iAttrId)  \
{ \
  return NULL; \
} \
  \
 CATLONG32               CLASS::ReleaseAttribute(CATCGMAttribute * iAttrId) \
{ \
  return 0; \
} \
  \
 void               CLASS::GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr, \
                                             const CATCGMAttrId* iAttrId)         \
{ \
} \
  \
 void               CLASS::GetNextAttribute(CATCGMAttribute * iPrevAttr,     \
                                             CATCGMAttribute *& ioNextAttr)  \
{ \
  ioNextAttr = NULL; \
} \
  \
 CATICGMObject*     CLASS::Clone(CATCloneManager& iCloneManager) const  \
{ \
  return implementation->Clone(iCloneManager); \
} \
  \
 void               CLASS::SetExplicit()  \
{ \
  ImpossibleOperation; \
} \
  \
 int                CLASS::PutAttribute(const int iKey, void* iBuffer,     \
                                         const int iLength,  const int iControl) \
{ \
  ImpossibleOperation; \
  return 0; \
} \
  \
 const void*        CLASS::GetAttribute( const int iKey, int& oLength)  \
{ \
  return implementation->GetAttribute(iKey,oLength); \
} \
  \
 int                CLASS::DeleteAttribute( const int iKey )  \
{ \
  ImpossibleOperation; \
  return 0; \
} \
  \
  \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) { ImpossibleOperation; } \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery ) { ImpossibleOperation; } \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery ) { ImpossibleOperation; } \
  \
 void               CLASS::DeleteAllAttribute()  \
{ \
  ImpossibleOperation; \
} \
int CLASS::GetAdvancedBoundingBox(CATMathAdvancedBox &oBox) const \
{ \
  ImpossibleOperation; \
  return -1; \
} \
CATBoolean CLASS::IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const \
{ \
  ImpossibleOperation; \
  return FALSE; \
} \
int CLASS::GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  ImpossibleOperation; \
  return -1; \
} \
int CLASS::GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  ImpossibleOperation; \
  return -1; \
} \
int CLASS::GetInternalMaxAdvancedBoundingBox(CATLONG32 iu, CATLONG32 iv, CATMathAdvancedBox &oBox) const \
{ \
  ImpossibleOperation; \
  return -1; \
}
  

#endif
#endif




