//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation 01/03/2001         I. Chauvigne, X. Dupont, E. Dupuis, N. Valet
//
// Operateur Reparation et nettoyage de body MonoShell MonoFace (implementation)
//=============================================================================

#ifndef __CATTopFaceHealerOperator_h__
#define __CATTopFaceHealerOperator_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"


class ExportedByCATTopologicalObjects CATTopFaceHealerOperator: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopFaceHealerOperator);
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATTopFaceHealerOperator(CATGeoFactory * iFactory,
                               CATTopData    * iData);
  
      ~CATTopFaceHealerOperator();

      virtual int Run()=0;                   

      
};


#endif
