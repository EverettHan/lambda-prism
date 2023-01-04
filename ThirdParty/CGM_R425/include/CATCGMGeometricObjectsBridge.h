#ifndef __CATCGMGeometricObjectsBridge__
#define __CATCGMGeometricObjectsBridge__

//#include "CATCGMInterruptDef.h"

#include "CATMathematics.h"
#include "CATCollec.h"
#include "CATLISTV_CATBaseUnknown.h"

//class CATGeoFactory;
//class CATLISTV;
//class CATCollec;

class ExportedByCATMathematics CATCGMGeometricObjectsBridge
{
public:
   // -----------
   // Ctor & Dtor
   // -----------
   CATCGMGeometricObjectsBridge();
   virtual ~CATCGMGeometricObjectsBridge();

   // -----------
   // Services
   // -----------

   static HRESULT CATCGMCATechExt_CleanGenericData(CATLISTV(CATBaseUnknown_var)&  ioReloadedObjects, CATLISTV(CATBaseUnknown_var)& iToNotCLose);


protected:
   // -----
   // Data
   // -----
   static CATCGMGeometricObjectsBridge *_pGeometricObjectsBridge;

   // -------------
   // Internal Use
   // -------------
   virtual HRESULT _CATCGMCATechExt_CleanGenericData(CATLISTV(CATBaseUnknown_var)&  ioReloadedObjects, CATLISTV(CATBaseUnknown_var)&  iToNotCLose) = 0;

private:

   // -------------
   // Internal Use
   // -------------
   static void Init();

   // ---------------
   // Forbidden Ctors
   // ---------------
   CATCGMGeometricObjectsBridge(const CATCGMGeometricObjectsBridge& iGeometricObjectsBridge);
   CATCGMGeometricObjectsBridge& operator = (const CATCGMGeometricObjectsBridge& iGeometricObjectsBridge);
};

#endif

