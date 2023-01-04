#ifndef CATICGMObjectImplementYP002PR4_H
#define CATICGMObjectImplementYP002PR4_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//============================================================================
//      Dedicated to INTERNAL CGM USE
//  Macro-Definition for Default interface-implementation of CATICGMObject
//============================================================================
#include "CATICGMObject.h"
#include "CATGetTolerance.h"

#ifndef CATICGMObjectImplementYP002PR4
#define CATICGMObjectImplementYP002PR4(CLASS)                            \
  \
 void               CLASS::Completed(CATBoolean IsNoMoreModifiable,           \
                                      const char IdentityBuildOperator[], const CATTopData  * iData)       \
{ \
} \
  \
 void               CLASS::CompletedFreeze(CATCGMOperator *iOperator)       \
{ \
} \
  \
ULONG __stdcall CLASS::CATAddRefFrom(void *iForDebug, CATBoolean iLockEquation ) \
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
  return ::CATGetDefaultTolerance();   \
} \
  \
 int       CLASS::IsImplementCGMRemoved(const CATGeometricType iTypeReference)  const \
{ \
  return 0; \
} \
  \
 CATBoolean         CLASS::IsModifiable()                                             \
{ \
  return FALSE; \
} \
  \
 CATBoolean         CLASS::HasBeenCompletedAsNoMoreModifiable() const                 \
{ \
  return TRUE; \
} \
  \
 CATBoolean         CLASS::HasBeenLoaded() const                                      \
{ \
  return TRUE; \
} \
  \
 CATULONG32       CLASS::GetUseCount(CATCGMUseCountType iUseType) const \
{ \
  CATULONG32  toto = 0; \
  return toto; \
} \
  \
 CATULONG32       CLASS::GetPersistentTag() const                                   \
{ \
  CATULONG32  toto = 0; \
  return toto; \
} \
  \
 CATGeoFactory*     CLASS::GetContainer(CATBoolean iThrowOnNullFactory, CATCGMMode iMode)    \
{ \
  return NULL; \
} \
  \
 void               CLASS::SetMode(CATCGMMode iMode)                                  \
{ \
} \
  \
 CATLONG32               CLASS::IsExplicit() const                                         \
{ \
  return 0; \
} \
  \
 int                CLASS::IsATypeOf(CATGeometricType TypeReference) const            \
{ \
  if ( TypeReference == CATGeometryType          ||\
       TypeReference == CATPointType             ||\
       TypeReference == CATPointOnSurfaceType    ) {\
    return 1;\
  }\
  return 0;\
} \
  \
 void               CLASS::GetLinks(CATLISTP(CATICGMObject) &oLinks ,            \
                                     CATCGMLinkType          iLinkType     ,     \
                                     CATRCOLL(int)*          oSharedStatus ,     \
                                     CATLISTV(CATString)*    oLinksString  )     \
{ \
} \
  \
void              CLASS::GetAllLinks(CATLISTP(CATGeometry) &oLinks) \
{ \
} \
  \
int                CLASS::Check()                                                     \
{ \
  return 0; \
} \
  \
 CATLONG32               CLASS::PutAttribute(CATCGMAttribute * iNewAttr)                    \
{ \
  return 0; \
} \
  \
 CATCGMAttribute *  CLASS::GetAttribute(const CATCGMAttrId* iAttrId)                   \
{ \
  return NULL; \
} \
  \
 CATLONG32               CLASS::ReleaseAttribute(CATCGMAttribute * iAttrId)                 \
{ \
  return 0; \
} \
  \
 void               CLASS::GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr,   \
                                             const CATCGMAttrId* iAttrId)         \
{ \
} \
  \
 void               CLASS::GetNextAttribute(CATCGMAttribute * iPrevAttr,               \
                                             CATCGMAttribute *& ioNextAttr)            \
{ \
} \
  \
 CATICGMObject*     CLASS::Clone(CATCloneManager& iCloneManager) const                 \
{ \
  return NULL; \
} \
  \
 void               CLASS::SetExplicit()                                               \
{ \
} \
  \
 int                CLASS::PutAttribute(const int iKey, void* iBuffer,                 \
                                         const int iLength,  const int iControl)       \
{ \
  return 0;\
} \
  \
 const void*        CLASS::GetAttribute( const int iKey, int& oLength)                 \
{ \
  return NULL; \
} \
  \
 int                CLASS::DeleteAttribute( const int iKey )                           \
{ \
  return 0; \
} \
  \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) {  } \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery ) {  } \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery ) {  } \
  \
  \
 void               CLASS::DeleteAllAttribute()                                        \
{ \
} \
int CLASS::GetAdvancedBoundingBox(CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
} \
CATBoolean CLASS::IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const \
{ \
  return FALSE; \
} \
int CLASS::GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
} \
int CLASS::GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
} \
int CLASS::GetInternalMaxAdvancedBoundingBox(CATLONG32 iu, CATLONG32 iv, CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
}


#endif
#endif




