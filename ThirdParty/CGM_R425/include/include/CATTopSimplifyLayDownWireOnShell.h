// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation ICE,XDT  19/12/2002
//
//  Cf. CATCreateSimplifyLayDownWireOnShell.h
//
//=============================================================================

#ifndef __CATTopSimplifyLayDownWireOnShell_h__
#define __CATTopSimplifyLayDownWireOnShell_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

class CATShell;
class CATWire;
class CATCGMOutput;

class ExportedByCATTopologicalObjects CATTopSimplifyLayDownWireOnShell: public CATTopOperator
{
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopSimplifyLayDownWireOnShell(CATGeoFactory * iFactory, CATTopData * iTopData);      

   public:

      virtual ~CATTopSimplifyLayDownWireOnShell();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      virtual CATBoolean  GetCheckJournal()                   const  = 0;
      virtual CATBoolean  GetSimplificationDone()             const  = 0;
      virtual CATWire   * GetWireToSimplify()                 const  = 0;
      virtual CATShell  * GetSupportShell()                   const  = 0;

      virtual void       SetCheckJournal(CATBoolean iCheckMode) = 0;
      virtual void       SetWireToSimplify(CATWire * iWire)     = 0;
      virtual void       SetSupportShell(CATShell * iShell)     = 0;
  
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

      virtual int  Run() = 0;
      virtual void Dump(CATCGMOutput & iOutStream) const = 0;
      
      virtual CATBody * GetResult() = 0;
};

#endif
