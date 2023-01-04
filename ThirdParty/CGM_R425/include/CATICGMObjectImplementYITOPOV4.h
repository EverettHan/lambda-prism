#ifndef CATICGMObjectImplementYITOPOV4_H
#define CATICGMObjectImplementYITOPOV4_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//============================================================================
//      Dedicated to INTERNAL CGM USE
//  Macro-Definition for Default interface-implementation of CATICGMObject
//============================================================================
#include "CATICGMObject.h"
#include "CATTolerance.h"

#ifndef CATICGMObjectImplementYITOPOV4
#define CATICGMObjectImplementYITOPOV4(CLASS) \
  \
void                CLASS::CompletedFreeze(CATCGMOperator *iOperator) \
{ \
} \
  \
void                CLASS::Completed(CATBoolean IsNoMoreModifiable, \
                                     const char IdentityBuildOperator[], const CATTopData  * iData) \
{ \
} \
  \
ULONG __stdcall     CLASS::CATAddRefFrom(void *iForDebug, CATBoolean iLockEquation) \
{ \
  return AddRef(); \
} \
  \
ULONG __stdcall     CLASS::CATReleaseFrom(void *iForDebug, CATBoolean iLockEquation) \
{ \
  return Release(); \
} \
  \
void *              CLASS::GetImplementCGM(CATGeometricType iTypeReference)  const \
{ \
  return NULL; \
} \
  \
void *              CLASS::IsCGMV5()  const \
{ \
  return NULL; \
} \
  \
int                 CLASS::IsSameTypeAs(CATICGMUnknown * iOtherObject)  const \
{ \
  return 0; \
} \
const CATTolerance& CLASS::GetToleranceObject() const \
{ \
  return ::CATGetDefaultTolerance();  \
} \
int                 CLASS::IsImplementCGMRemoved(const CATGeometricType iTypeReference)  const \
{ \
  return 0; \
} \
  \
CATBoolean          CLASS::IsModifiable() \
{ \
  return FALSE; \
} \
  \
CATBoolean          CLASS::HasBeenCompletedAsNoMoreModifiable() const  \
{ \
  return TRUE; \
} \
  \
CATBoolean          CLASS::HasBeenLoaded() const  \
{ \
  return TRUE; \
} \
  \
CATULONG32          CLASS::GetUseCount(CATCGMUseCountType iUseType) const \
{ \
  CATULONG32 UseCount = 0; \
  return UseCount; \
} \
  \
CATULONG32          CLASS::GetPersistentTag() const \
{ \
  CATULONG32 tag = GetJele(); \
  return tag; \
} \
  \
CATGeoFactory *     CLASS::GetContainer(CATBoolean iThrowOnNullFactory, CATCGMMode iMode) \
{ \
  CATGeoFactory *ptr = GetContainerV4(); \
  return ptr ; \
} \
  \
void                CLASS::SetMode(CATCGMMode iMode) \
{ \
} \
  \
CATLONG32           CLASS::IsExplicit() const  \
{ \
  return 0; \
} \
  \
int                 CLASS::IsATypeOf(CATGeometricType iTypeReference)const  \
{ \
  return 0; \
} \
  \
void                CLASS::GetLinks(CATLISTP(CATICGMObject) &oLinks, CATCGMLinkType iLinkType, \
                                    CATRCOLL(int)* oSharedStatus, CATLISTV(CATString)* oLinksString  ) \
{ \
} \
  \
void                CLASS::GetAllLinks(CATLISTP(CATGeometry) &oLinks) \
{ \
} \
  \
int                 CLASS::Check() \
{ \
  return 0; \
} \
  \
CATLONG32           CLASS::PutAttribute(CATCGMAttribute * iNewAttr) \
{ \
  return 0; \
} \
  \
CATCGMAttribute *   CLASS::GetAttribute(const CATCGMAttrId* iAttrId) \
{ \
  return NULL; \
} \
  \
CATLONG32           CLASS::ReleaseAttribute(CATCGMAttribute * iAttrId) \
{ \
  return 0; \
} \
  \
void                CLASS::GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr, \
                                            const CATCGMAttrId* iAttrId) \
{ \
} \
  \
void                CLASS::GetNextAttribute(CATCGMAttribute * iPrevAttr,  \
                                            CATCGMAttribute *& ioNextAttr) \
{ \
} \
  \
CATICGMObject*      CLASS::Clone(CATCloneManager& iCloneManager) const  \
{ \
  return NULL; \
} \
  \
void                CLASS::SetExplicit() \
{ \
} \
  \
int                 CLASS::PutAttribute(const int iKey,void * iBuffer, \
                                        const int iLength,  const int iControl) \
{ \
  return 0; \
} \
  \
const void *        CLASS::GetAttribute( const int iKey, int& oLength) \
{ \
  return NULL; \
} \
  \
int                 CLASS::DeleteAttribute( const int iKey ) \
{ \
  return 0; \
} \
  \
void                CLASS::PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) { } \
void                CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery ) { } \
void                CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery ) { } \
  \
void                CLASS::DeleteAllAttribute () \
{ \
} \
  \
int                 CLASS::GetAdvancedBoundingBox(CATMathAdvancedBox &oBox) const  \
{ \
  return -1; \
} \
  \
CATBoolean          CLASS::IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const \
{ \
  return FALSE; \
} \
  \
int                 CLASS::GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
} \
  \
int                 CLASS::GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
} \
  \
int                 CLASS::GetInternalMaxAdvancedBoundingBox(CATLONG32 iu, CATLONG32 iv, CATMathAdvancedBox &oBox) const \
{ \
  return -1; \
} \

#endif
#endif
