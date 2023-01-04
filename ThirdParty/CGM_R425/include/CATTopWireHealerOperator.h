//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation 01/03/2001         I. Chauvigne, X. Dupont, E. Dupuis, N. Valet
//
// Operateur Reparation et nettoyage de bodys (implementation)
//=============================================================================

#ifndef __CATTopWireHealerOperator_h__
#define __CATTopWireHealerOperator_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"


class ExportedByCATTopologicalObjects CATTopWireHealerOperator: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopWireHealerOperator);
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATTopWireHealerOperator(CATGeoFactory * iFactory,
                               CATTopData    * iData);
  
      ~CATTopWireHealerOperator();

      virtual int Run()=0;                   
      virtual void DetectDeadEnd(CATBoolean iDeadEnd)=0;
      
};


#endif
