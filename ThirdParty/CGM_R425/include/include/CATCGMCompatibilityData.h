#ifndef CATCGMCompatibilityData_h_
#define CATCGMCompatibilityData_h_

#include "CATBoolean.h"
#include "CATListOfCATICGMObjects.h"
#include "ExportedByCATCGMFusion.h"

class ExportedByCATCGMFusion CATCGMCompatibilityData
{
public:
                           CATCGMCompatibilityData();
                          ~CATCGMCompatibilityData();

   void                    AppendIncompatibleObjects(CATLISTP(CATICGMObject) & iIncompatibleObjects);
   void                    AppendConvertedObjects   (CATLISTP(CATICGMObject) & iConvertedObjects);
   void                    GetIncompatibleObjects   (CATLISTP(CATICGMObject) & oIncompatibleObjects);
   void                    GetConvertedObjects      (CATLISTP(CATICGMObject) & oConvertedObjects);

   CATBoolean              IsBackSaveCompatible();
   CATBoolean              HasBeenConverted();

private:

   CATLISTP(CATICGMObject) _IncompatibleObjects;
   CATLISTP(CATICGMObject) _ConvertedObjects;

};

#endif

