// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation JHN,ICE  16/06/2004
//
//  Cf. CATCreateTopProjectWiresOnShell.h
//
//=============================================================================

#ifndef __CATTopProjectWiresOnShell_h__
#define __CATTopProjectWiresOnShell_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATExtTopOperator.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "CATListOfDouble.h"

class CATShell;
class CATWire;
class CATMathDirection;

class ExportedByCATTopologicalObjects CATTopProjectWiresOnShell: public CATTopOperator
{
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopProjectWiresOnShell(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtOpe=NULL);      

   public:

      virtual ~CATTopProjectWiresOnShell();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      virtual CATBoolean  GetSuppressFlattenedWires()         const  = 0;
      virtual CATBoolean  GetSimplificationMode()             const  = 0;
      virtual CATWire   * GetWireToProject()                  const  = 0;
      virtual CATShell  * GetShellSupport()                   const  = 0;
      virtual double      GetMaxDistance()                    const  = 0;
      virtual int         GetSmartSolution()                  const  = 0;

      virtual void       SetMaxDistance(double iDistance)                    = 0;
      virtual void       SetSimplificationMode(CATBoolean iSimplification)   = 0;
      virtual void       SetSuppressFlattenedWires(CATBoolean iSuppressMode) = 0;
      virtual void       SetCoveredFaces(CATLISTP(CATFace) * iCoveredFaces)  = 0;
      virtual void       SetWireToProject(CATWire * iWire)                   = 0;
      virtual void       SetShellSupport(CATShell * iShell)                  = 0;
      virtual void       SetWorkingBody(CATBody   * iWorkingBody)            = 0;
      virtual void       SetSmartSolution(int iNearestSolution)              = 0;
      virtual void       SetInit(CATBody * iInitShell, CATBody * iInitWire)  = 0;
      virtual void       SetRemoveArtefacts(int iRemoveArtefacts)            = 0;
  
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

//      virtual void Dump(ostream & iOutStream) const = 0;
      
      virtual CATBody * GetResult() = 0;
      virtual CATBody * GetResult(CATCGMJournalList * iJournal) = 0;
      virtual void GetCellsData(ListPOfCATCell  & oResultList,
                                ListPOfCATCell  & oReferenceList,
                                ListPOfCATCell  & oSupportList,
                                CATListOfDouble & oDistanceList) = 0;
};

ExportedByCATTopologicalObjects CATTopProjectWiresOnShell *
CATCreateTopProjectWiresOnShell(CATGeoFactory * iFactory,
                             CATTopData       * iTopData,
                             CATMathDirection * iDirection,
                             CATBody          * iWiresBody,
                             CATBody          * iShellBody);

#endif
