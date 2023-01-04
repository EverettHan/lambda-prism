// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  15/11/2000
//
// Operateur de check d'intersection wire/wire (interface).
//=============================================================================

#ifndef __CATWireIntersectionChecker_h__
#define __CATWireIntersectionChecker_h__

#include "CheckOperators.h"
#include "CATIntersectionChecker.h"

class CATCXWireIntersectionChecker;
class CATSurface;
class CATWire;


class ExportedByCheckOperators CATWireIntersectionChecker: public CATIntersectionChecker
{
  CATCGMVirtualDeclareClass(CATWireIntersectionChecker);
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATWireIntersectionChecker(CATGeoFactory                * iFactory,
                                 CATTopData                   * iData,
                                 CATCXWireIntersectionChecker * iImplementation);
      
      virtual ~CATWireIntersectionChecker();


      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================


      //====================================
      // Parametrisation de l'operateur
      //====================================

      void SetWiresToCheck(CATWire * iWire1, CATWire * iWire2 = (CATWire*)0);
      void SetSurface(CATSurface * iSurface);

};

#endif
