#ifndef __CATCGMGeometricObjectsBridgeImplImpl__
#define __CATCGMGeometricObjectsBridgeImplImpl__

#include "CATCGMGeometricObjectsBridgeImpl.h"
//#include "CATCGMInterruptDef.h"

class CATCGMOperatorRunTransaction;
class CATGeoFactory;


class CATCGMGeometricObjectsBridgeImpl : public CATCGMGeometricObjectsBridge
{
public:
   // -----------
   // Ctor & Dtor
   // -----------
   CATCGMGeometricObjectsBridgeImpl();
   virtual ~CATCGMGeometricObjectsBridgeImpl();
   
protected:
   // -----------
   // Services
   // -----------

   HRESULT _CATCGMCATechExt_CleanGenericData(CATLISTV(CATBaseUnknown_var)&   ioReloadedObjects, CATLISTV(CATBaseUnknown_var)&  iToNotCLose);
         
private:
   // ---------------
   // Forbidden Ctors
   // ---------------
   CATCGMGeometricObjectsBridgeImpl(const CATCGMGeometricObjectsBridgeImpl& iGeometricObjectsBridgeImpl);
   CATCGMGeometricObjectsBridgeImpl& operator = (const CATCGMGeometricObjectsBridgeImpl& iGeometricObjectsBridgeImpl);
};

#endif

