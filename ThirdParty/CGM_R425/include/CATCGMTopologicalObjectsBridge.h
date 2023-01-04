#ifndef __CATCGMTopologicalObjectsBridge__
#define __CATCGMTopologicalObjectsBridge__

//#include "CATCGMInterruptDef.h"
#include "CATCGMOperator.h"
#include "YP0LOGRP.h"
class CATCGMProgressBar;

class CATCGMOperatorRunTransaction;
class CATGeoFactory;
class CATICGMObject;

class ExportedByYP0LOGRP CATCGMTopologicalObjectsBridge
{
public:
   // -----------
   // Ctor & Dtor
   // -----------
   CATCGMTopologicalObjectsBridge();
   virtual ~CATCGMTopologicalObjectsBridge();

   // -----------
   // Services
   // -----------

   static CATCGMOperatorRunTransaction * CATCGMCreateRunOperatorTransaction(CATGeoFactory *piFactory);

   static CATCGMOperatorRunTransaction * CATCGMCreateRunOperatorTransaction(CATGeoFactory *piFactory, CATCGMInterruptFunction piInterruptFunction);

   // To know if a Body has infinite geometry
   static CATBoolean BodyHasInfiniteGeometry(CATICGMObject* piObject);

   // Check if Factory is flagged with New Imprint Attribute
   static CATBoolean HasImprintCellAttribute(CATGeoFactory *piGeoFactory);

protected:
   // -----
   // Data
   // -----
   static CATCGMTopologicalObjectsBridge *_pTopologicalObjectsBridge;

   // -------------
   // Internal Use
   // -------------
   virtual CATCGMOperatorRunTransaction * _CATCGMCreateRunOperatorTransaction(CATGeoFactory *piFactory) = 0;

   virtual CATCGMOperatorRunTransaction * _CATCGMCreateRunOperatorTransaction(CATGeoFactory *piFactory, CATCGMInterruptFunction piInterruptFunction) = 0;

   virtual CATBoolean _BodyHasInfiniteGeometry(CATICGMObject* piObject) = 0;

   virtual CATBoolean _HasImprintCellAttribute(CATGeoFactory *piGeoFactory) = 0;

private:

   // -------------
   // Internal Use
   // -------------
   static void Init();

   // ---------------
   // Forbidden Ctors
   // ---------------
   CATCGMTopologicalObjectsBridge(const CATCGMTopologicalObjectsBridge& iTopologicalObjectsBridge);
   CATCGMTopologicalObjectsBridge& operator = (const CATCGMTopologicalObjectsBridge& iTopologicalObjectsBridge);
};

#endif

