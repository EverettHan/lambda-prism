#ifndef CATGeometryImpl_h
#define CATGeometryImpl_h
/**
 *  Default implementation for CATGeometry Interface
 */

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATGeometry.h"
#include "CATCGMExtGeometry.h"
#include "CATGeometricObjectsInternalError.h"
#include "CATGeometricObjectsErrors.h"
class CATICGMObject;

class ExportedByYP00IMPL CATGeometryImpl : public CATCGMExtGeometry
{
public:
  CATGeometryImpl();
  virtual ~CATGeometryImpl();

  // Interface CATICGMObject
  //------------------------------------------------------------------------------------------
  virtual int            PutAttribute       ( const int Key, 
	   			              void* Buffer, const int Length, 
				              const int Control) ;
  virtual const void*    GetAttribute       ( const int Key, int& Length) ;
  virtual int            DeleteAttribute    ( const int Key ) ;
  virtual void           DeleteAllAttribute () ;
  virtual CATLONG32         PutAttribute(CATCGMAttribute * NewAttr) ;
  virtual CATCGMAttribute * GetAttribute(const CATCGMAttrId*) ;
  virtual CATLONG32 ReleaseAttribute(CATCGMAttribute * NewAttr) ;
  virtual void        GetListAttribute(CATLISTP(CATCGMAttribute) &,const CATCGMAttrId* AttrId=NULL);
  virtual void        GetNextAttribute(CATCGMAttribute * PrevAttr,
    CATCGMAttribute *& NextAttr);


  virtual void CompletedFreeze(CATCGMOperator *iOperator); 

  virtual void Completed(CATBoolean IsNoMoreModifiable = FALSE, const char IdentityBuildOperator[] = "",
                         const CATTopData  * iData = NULL);

  virtual int Check();
  virtual CATBoolean HasBeenCompletedAsNoMoreModifiable() const ;
  virtual CATBoolean HasBeenLoaded() const;

  virtual void *GetImplementCGM(CATGeometricType iTypeReference) const; 
  virtual void *IsCGMV5() const;
  virtual int  IsImplementCGMRemoved(const CATGeometricType iTypeReference=CATGeometryType) const;

};


#define CGMThrowUnavailableMethod(methodname)                     \
CATGeometricObjectsInternalError *Error =                         \
new CATGeometricObjectsInternalError (GBIntEUnavailableMethod);   \
Error->SetParameters(1, #methodname);                             \
CATThrow (Error)

#endif
