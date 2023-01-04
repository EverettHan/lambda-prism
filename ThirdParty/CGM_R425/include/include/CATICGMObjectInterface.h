#ifndef CATICGMObjectInterface_H
#define CATICGMObjectInterface_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//============================================================================
//      Dedicated to INTERNAL CGM USE
//  Macro-Definition for Default interface-implementation of CATICGMObject
//============================================================================
#include "CATICGMObject.h"
#include "CATGetTolerance.h"

class CATSurLimits;
class CATCrvLimits;
class CATCGMQueryManager;


#ifndef CATICGMObjectInterface

#define CATICGMObjectInterface                                                         \
  virtual void              Completed(CATBoolean IsNoMoreModifiable = FALSE,           \
                                      const char IdentityBuildOperator[] = "", const CATTopData  * iData = NULL ); \
  virtual void              CompletedFreeze(CATCGMOperator *iOperator); \
  virtual CATBoolean        IsModifiable();                                            \
  virtual CATBoolean        HasBeenCompletedAsNoMoreModifiable() const;                \
  virtual CATBoolean        HasBeenLoaded() const;                                     \
  virtual CATULONG32      GetUseCount(CATCGMUseCountType iUseType =CatCGMUseCountAllCATICGMObject) const; \
  virtual CATULONG32      GetPersistentTag() const;                                  \
  virtual CATGeoFactory*    GetContainer(CATBoolean iThrowOnNullFactory = TRUE, CATCGMMode iMode = CatCGMExplicit);       \
  virtual void              SetMode(CATCGMMode iMode);                                 \
  virtual CATLONG32              IsExplicit() const;                                        \
  virtual int               IsATypeOf(CATGeometricType iTypeReference)const;           \
  virtual void              GetLinks(CATLISTP(CATICGMObject) &oLinks,                  \
                                     CATCGMLinkType          iLinkType     = CatCGMDependancies,      \
                                     CATRCOLL(int)*          oSharedStatus = NULL,     \
                                     CATLISTV(CATString)*    oLinksString  = NULL);    \
  virtual int               Check();                                                   \
  virtual CATLONG32              PutAttribute(CATCGMAttribute * iNewAttr);                  \
  virtual CATCGMAttribute * GetAttribute(const CATCGMAttrId* iAttrId);                 \
  virtual CATLONG32              ReleaseAttribute(CATCGMAttribute * iAttrId);               \
  virtual void              GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr,  \
                                             const CATCGMAttrId* iAttrId=NULL);        \
  virtual void              GetNextAttribute(CATCGMAttribute * iPrevAttr,              \
                                             CATCGMAttribute *& ioNextAttr);           \
  virtual CATICGMObject*    Clone(CATCloneManager& iCloneManager) const;               \
  virtual void              GetAllLinks(CATLISTP(CATGeometry) &oLinks);                \
  virtual void              SetExplicit();                                             \
  virtual int               PutAttribute(const int iKey, void* iBuffer,                \
                                         const int iLength,  const int iControl);      \
  virtual const void*       GetAttribute( const int iKey, int& oLength);               \
  virtual int               DeleteAttribute( const int iKey );                         \
  virtual void *GetImplementCGM(CATGeometricType iTypeReference) const;                \
  virtual void *IsCGMV5() const;                                                       \
  virtual int   IsSameTypeAs(CATICGMUnknown * iOtherObject) const;             \
  virtual const CATTolerance & GetToleranceObject() const;             \
  virtual int  IsImplementCGMRemoved(const CATGeometricType iTypeReference=CATGeometryType) const;\
  virtual ULONG __stdcall   CATAddRefFrom(void *iForDebug, CATBoolean iLockEquation = FALSE);   \
  virtual ULONG __stdcall   CATReleaseFrom(void *iForDebug, CATBoolean iLockEquation = FALSE);  \
  virtual void PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) ; \
  virtual void PropagateQuery(CATICGMUnknown *iFrom, const CATSurLimits & iLimits, CATCGMQueryManager &iQuery ) ; \
  virtual void PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery ) ; \
  virtual void              DeleteAllAttribute();                                                                         \
  virtual int               GetAdvancedBoundingBox(CATMathAdvancedBox &oBox) const;                                       \
  virtual CATBoolean        IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const;                       \
  virtual int               GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &oBox) const;                  \
  virtual int               GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &oBox) const;                  \
  virtual int               GetInternalMaxAdvancedBoundingBox(CATLONG32 iu, CATLONG32 iv, CATMathAdvancedBox &oBox) const;




#endif
#endif




