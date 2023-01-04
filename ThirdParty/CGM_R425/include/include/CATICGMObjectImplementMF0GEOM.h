#ifndef CATICGMObjectImplementMF0GEOM_H
#define CATICGMObjectImplementMF0GEOM_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//============================================================================
//      Dedicated to INTERNAL CGM USE
//  Macro-Definition for Default interface-implementation of CATICGMObject
//============================================================================
#include "CATICGMObject.h"
#include "CATGetTolerance.h"

#ifndef CATICGMObjectImplementMF0GEOM



#define CATICGMObjectImplementMF0GEOM(CLASS,MFTRACE,ImpossibleOperation,NotYetImplemented)                            \
  \
 void               CLASS::Completed(CATBoolean IsNoMoreModifiable,           \
                                      const char IdentityBuildOperator[],const CATTopData  * iData)       \
{ \
  ImpossibleOperation; \
} \
  \
 void               CLASS::CompletedFreeze(CATCGMOperator *iOperator)       \
{ \
  ImpossibleOperation; \
} \
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
  MFTRACE; \
  ImpossibleOperation; \
  return 0; \
} \
  \
 CATBoolean         CLASS::HasBeenCompletedAsNoMoreModifiable() const                 \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return FALSE; \
} \
  \
 CATBoolean         CLASS::HasBeenLoaded() const                                      \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return FALSE; \
} \
  \
 CATULONG32       CLASS::GetUseCount(CATCGMUseCountType iUseType) const \
{ \
  MFTRACE; \
  ImpossibleOperation; \
  return 0; \
} \
  \
 CATULONG32       CLASS::GetPersistentTag() const                                   \
{ \
  MFTRACE; \
  ImpossibleOperation; \
  return 0; \
} \
  \
 CATGeoFactory*     CLASS::GetContainer(CATBoolean iThrowOnNullFactory, CATCGMMode iMode)      \
{ \
  MFTRACE; \
  return NULL; \
} \
  \
 void               CLASS::SetMode(CATCGMMode iMode)                                  \
{ \
  MFTRACE; \
  ImpossibleOperation; \
} \
  \
 CATLONG32               CLASS::IsExplicit() const                                         \
{ \
  MFTRACE; \
  ImpossibleOperation; \
  return 0; \
} \
  \
 int                CLASS::IsATypeOf(CATGeometricType iTypeReference)const            \
{ \
  MFTRACE; \
  ImpossibleOperation; \
  return 0; \
} \
  \
 void               CLASS::GetLinks(CATLISTP(CATICGMObject) &oLinks ,            \
                                     CATCGMLinkType          iLinkType     ,     \
                                     CATRCOLL(int)*          oSharedStatus ,     \
                                     CATLISTV(CATString)*    oLinksString  )     \
{ \
  MFTRACE; \
  ImpossibleOperation; \
} \
  \
void              CLASS::GetAllLinks(CATLISTP(CATGeometry) &oLinks) \
{ \
  MFTRACE; \
  ImpossibleOperation; \
} \
  \
int                CLASS::Check()                                                     \
{ \
  ImpossibleOperation; \
  return 0; \
} \
  \
 CATLONG32               CLASS::PutAttribute(CATCGMAttribute * iNewAttr)                    \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return 0; \
} \
  \
 CATCGMAttribute *  CLASS::GetAttribute(const CATCGMAttrId* iAttrId)                   \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return NULL; \
} \
  \
 CATLONG32               CLASS::ReleaseAttribute(CATCGMAttribute * iAttrId)                 \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return 0; \
} \
  \
 void               CLASS::GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr,   \
                                             const CATCGMAttrId* iAttrId)         \
{ \
  MFTRACE; \
  NotYetImplemented; \
} \
  \
 void               CLASS::GetNextAttribute(CATCGMAttribute * iPrevAttr,               \
                                             CATCGMAttribute *& ioNextAttr)            \
{ \
  MFTRACE; \
  NotYetImplemented; \
} \
  \
 CATICGMObject*     CLASS::Clone(CATCloneManager& iCloneManager) const                 \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return NULL; \
} \
  \
 void               CLASS::SetExplicit()                                               \
{ \
  MFTRACE; \
  ImpossibleOperation; \
} \
  \
 int                CLASS::PutAttribute(const int iKey, void* iBuffer,                 \
                                         const int iLength,  const int iControl)       \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return 0; \
} \
  \
 const void*        CLASS::GetAttribute( const int iKey, int& oLength)                 \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return NULL; \
} \
  \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) { NotYetImplemented; } \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery ) { NotYetImplemented; } \
void CLASS::PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery ) { NotYetImplemented; } \
  \
 int                CLASS::DeleteAttribute( const int iKey )                           \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return 0; \
} \
  \
 void               CLASS::DeleteAllAttribute()                                        \
{ \
  MFTRACE; \
  NotYetImplemented; \
} \
int CLASS::GetAdvancedBoundingBox(CATMathAdvancedBox &oBox) const \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return -1; \
} \
CATBoolean CLASS::IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return FALSE; \
} \
int CLASS::GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return -1; \
} \
int CLASS::GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &oBox) const \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return -1; \
} \
int CLASS::GetInternalMaxAdvancedBoundingBox(CATLONG32 iu, CATLONG32 iv, CATMathAdvancedBox &oBox) const \
{ \
  MFTRACE; \
  NotYetImplemented; \
  return -1; \
}


#endif
#endif




