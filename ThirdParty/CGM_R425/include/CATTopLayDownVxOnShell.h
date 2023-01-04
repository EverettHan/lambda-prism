// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation EDS,ICE,XDT  16/09/2002
//
//  Cf. CATCreateLayDownWiresOnShell.h
//
//=============================================================================

#ifndef __CATTopLayDownVxOnShell_h__
#define __CATTopLayDownVxOnShell_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "CATListOfDouble.h"

class CATShell;
class CATWire;
class CATDomain;
class CATCGMOutput;

class ExportedByCATTopologicalObjects CATTopLayDownVxOnShell: public CATTopOperator
{
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopLayDownVxOnShell(CATGeoFactory * iFactory, CATTopData * iTopData);      

   public:

      virtual ~CATTopLayDownVxOnShell();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      virtual double      GetTolerance()                      const  = 0;
      virtual CATShell  * GetShellSupport()                   const  = 0;

//      virtual CATBoolean  IsFullyTouchedDown()                       = 0;

      // a n'utiliser que si SetCheckLayDown a ete utilise avant le Run
      // On retourne TRUE si le posage est complet a la Tolerance. 
//      virtual CATBoolean GetEdgesAndGaps(CATLISTP(CATEdge)& ioEdges, CATListOfDouble& ioGaps) = 0 ; 

      virtual void       SetCoveredFaces(CATLISTP(CATFace) * iCoveredFaces)  = 0;
      virtual void       SetTolerance(double iTolerance)                     = 0; // la Tolerance par defaut est la resolution
      virtual void       SetCheckJournal(CATBoolean iCheckMode)              = 0;
      virtual void       SetShellSupport(CATShell * iShell)                  = 0;
      virtual void       SetDomainToProject(CATDomain* iDomain)              = 0; 
  
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

      virtual int  Run() = 0;
      virtual void Dump(CATCGMOutput & iOutStream) const = 0;
      
      virtual CATBody * GetResult() = 0;
};

ExportedByCATTopologicalObjects 
CATTopLayDownVxOnShell *
CATCreateTopLayDownVxOnShell(CATGeoFactory * iFactory,
                             CATTopData       * iTopData,
//                             CATMathDirection * iDirection,
                             CATBody          * iWiresBody,
                             CATBody          * iShellBody);

#endif
