#ifndef __CATCGMTopologicalObjectsBridgeImpl__
#define __CATCGMTopologicalObjectsBridgeImpl__

#include "CATCGMTopologicalObjectsBridge.h"
//#include "CATCGMInterruptDef.h"

class CATCGMOperatorRunTransaction;
class CATGeoFactory;

//void INIT_CATCGMTopologicalObjectsBridge();

class CATCGMTopologicalObjectsBridgeImpl : public CATCGMTopologicalObjectsBridge
{
public:
   // -----------
   // Ctor & Dtor
   // -----------
   CATCGMTopologicalObjectsBridgeImpl();
   virtual ~CATCGMTopologicalObjectsBridgeImpl();
   
protected:
   // -----------
   // Services
   // -----------

   CATCGMOperatorRunTransaction *_CATCGMCreateRunOperatorTransaction(CATGeoFactory *piFactory);

   CATCGMOperatorRunTransaction *_CATCGMCreateRunOperatorTransaction(CATGeoFactory *piFactory, CATCGMInterruptFunction piInterruptFunction);
   
   CATBoolean _BodyHasInfiniteGeometry(CATICGMObject* piObject);

   // Check if Factory is flagged with New Imprint Attribute
   virtual CATBoolean _HasImprintCellAttribute(CATGeoFactory *piGeoFactory);

private:
   // ---------------
   // Forbidden Ctors
   // ---------------
   CATCGMTopologicalObjectsBridgeImpl(const CATCGMTopologicalObjectsBridgeImpl& iTopologicalObjectsBridge);
   CATCGMTopologicalObjectsBridgeImpl& operator = (const CATCGMTopologicalObjectsBridgeImpl& iTopologicalObjectsBridge);
};

#endif

