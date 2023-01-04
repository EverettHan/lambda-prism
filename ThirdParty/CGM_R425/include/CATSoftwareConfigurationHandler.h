#ifndef CATSoftwareConfigurationHandler_H
#define CATSoftwareConfigurationHandler_H
// COPYRIGHT DASSAULT SYSTEMES 2013
//==========================================================================
//
// CATSoftwareConfigurationHandler: handler for CATSoftwareConfiguration object
// (ensures the objet remains alive as long as the handler is alive)
//
// Allows automatic and secure cycle life handling of CATSoftwareConfiguration for classes
// which, for example, do not implement fully and consistently copy constructors
//
//==========================================================================
//
// Usage notes:
//
//==========================================================================
// 07/03/13 NLD Creation
//=============================================================================
#include "ExportedByCATMathStream.h"


class CATSoftwareConfiguration;

class ExportedByCATMathStream CATSoftwareConfigurationHandler
  {
   private:
           CATSoftwareConfiguration* _SoftwareConfiguration;
   public:
                                     CATSoftwareConfigurationHandler             (                                                                     );
                                     CATSoftwareConfigurationHandler             (      CATSoftwareConfiguration       *  iSoftwareConfiguration       );
                                     CATSoftwareConfigurationHandler             (const CATSoftwareConfigurationHandler & iSoftwareConfigurationHandler);
                                     CATSoftwareConfigurationHandler& operator = (const CATSoftwareConfigurationHandler & iSoftwareConfigurationHandler);
   virtual                          ~CATSoftwareConfigurationHandler             (                                                                     );
           void                      SetSoftwareConfiguration                    (      CATSoftwareConfiguration       *  iSoftwareConfiguration       );
           CATSoftwareConfiguration* GetSoftwareConfiguration                    (                                                                     ) const;

  };
#endif
