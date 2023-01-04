// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation 31/01/2001               I. Dupont, X. Dupont, E. Dupuis, N. Valet
//
// Operateur de calcul de trous
//=============================================================================

#ifndef __CATTopComputeGap_h__
#define __CATTopComputeGap_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

#include "ListPOfCATVertex.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATCell.h"

class CATDomain;
class CATCell;

class ExportedByCATTopologicalObjects CATTopComputeGap: public CATTopOperator
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATTopComputeGap(CATGeoFactory * iFactory,
                         CATTopData    * iData);
  
      ~CATTopComputeGap();
      
      virtual double GetGap()=0;	
      virtual double GetGap(CATCell * iReference)=0;	
      virtual double GetMaxEdgeGap()=0;
      virtual double GetMaxVertexGap()=0;
      virtual void   AnalyseGaps()=0; 
      virtual void   RetrieveVerticesBiggerThan(CATDomain* iDomainRef, double iThreshold, CATLISTP(CATVertex)& oVertices)=0;
      virtual void   RetrieveEdgesBiggerThan(CATDomain* iDomainRef, double iThreshold, CATLISTP(CATEdge)& oEdges)=0;

      virtual void VisuEdgesGaps(double Threshold)=0;
      virtual void VisuVerticesGaps(double Threshold)=0;

      virtual void SetComputeMode(int iComputeMode)=0; // 0: discretisation 1: cheminement
      virtual void SetOnlyCell(int iOnly)=0; // 0: calcul global sur les domaines 1: calcul restreint a une liste de cellules
      virtual void SetCellsToMesure(CATLISTP(CATCell) * iCells)=0; 
      
      virtual int Run()=0;                   

      
};


#endif
