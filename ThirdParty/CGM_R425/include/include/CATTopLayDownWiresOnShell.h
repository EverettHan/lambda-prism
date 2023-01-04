// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation EDS,ICE,XDT  16/09/2002
//
//  Cf. CATCreateLayDownWiresOnShell.h
//
//=============================================================================

#ifndef __CATTopLayDownWiresOnShell_h__
#define __CATTopLayDownWiresOnShell_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "CATListOfDouble.h"

class CATShell;
class CATWire;
class CATCGMOutput;
class TableOriEdgeVsInitialWires;

class ExportedByCATTopologicalObjects CATTopLayDownWiresOnShell: public CATTopOperator
{
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopLayDownWiresOnShell(CATGeoFactory * iFactory, CATTopData * iTopData);      

   public:

      virtual ~CATTopLayDownWiresOnShell();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      virtual double      GetTolerance()                      const  = 0;
      virtual CATBoolean  GetCheckJournal()                   const  = 0;
      virtual CATBoolean  GetCheckLayDown()                   const  = 0;
      virtual CATBoolean  GetSuppressFlattenedWires()         const  = 0;
      virtual CATBoolean  GetSimplificationMode()             const  = 0;
      virtual CATWire   * GetWireToProject()                  const  = 0;
      virtual CATShell  * GetShellSupport()                   const  = 0;

      virtual CATBoolean  IsFullyTouchedDown()                       = 0;

      // a n'utiliser que si SetCheckLayDown a ete utilise avant le Run
      // On retourne TRUE si le posage est complet a la Tolerance. 
      virtual CATBoolean GetEdgesAndGaps(CATLISTP(CATEdge)& ioEdges, CATListOfDouble& ioGaps) = 0 ; 
      virtual void       GetLayDownResultPerWire(CATWire * iWire, CATLISTP(CATEdge)& ioEdges) = 0;
  
      virtual void       SetTolerance(double iTolerance)                     = 0; // la Tolerance par defaut est la resolution
      virtual void       SetCheckJournal(CATBoolean iCheckMode)              = 0;
      virtual void       SetCheckLayDown(CATBoolean iCheckMode)              = 0;
      virtual void       SetSimplificationMode(CATBoolean iSimplification)   = 0;
      virtual void       SetSuppressFlattenedWires(CATBoolean iSuppressMode) = 0;
      virtual void       SetCoveredFaces(CATLISTP(CATFace) * iCoveredFaces)  = 0;
      virtual void       SetWireToProject(CATWire * iWire)                   = 0;
      virtual void       SetShellSupport(CATShell * iShell)                  = 0;
      virtual void       SetRemoveArtefacts(int iRemoveArtefacts)            = 0;

      virtual void SetComputeOrientations(CATBoolean iComputeOrientations) = 0;
      virtual TableOriEdgeVsInitialWires * GetOrientationTable() = 0;
  
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

      virtual int  Run() = 0;
      virtual void Dump(CATCGMOutput& os) = 0;
      
      virtual CATBody * GetResult() = 0;
      
      // FSQ(12/01/2009): Call this function to deactivate the new journal
      virtual void ActivateOldJournal() = 0;
};

#endif
