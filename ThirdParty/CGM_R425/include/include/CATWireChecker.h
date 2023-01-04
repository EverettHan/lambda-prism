// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation NVT  23/02/2001
//
// Operateur de check de wire (SubdCheck, auto-intersection)
//=============================================================================

#ifndef __CATWireChecker_h__
#define __CATWireChecker_h__

#include "CATChecker.h"
#include "CheckOperators.h"

class CATGeoFactory;
class CATTopData;
class CATCXWireChecker;
class CATWire;


class ExportedByCheckOperators CATWireChecker: public CATChecker
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATWireChecker(CATGeoFactory    * iFactory,
                     CATTopData       * iData,
                     CATCXWireChecker * iImplementation);
      
      virtual ~CATWireChecker();


      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================


      //====================================
      // Parametrisation de l'operateur
      //====================================

      void SetWireToCheck(CATWire * iWireToCheck);
};

#endif
