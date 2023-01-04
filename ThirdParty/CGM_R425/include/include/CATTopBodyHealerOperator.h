//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation 01/03/2001                          I. Dupont, X. Dupont, E. Dupuis
//
// Operateur Reparation et nettoyage de bodys (implementation)
//=============================================================================

#ifndef __CATTopBodyHealerOperator_h__
#define __CATTopBodyHealerOperator_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATFace.h"

class ExportedByCATTopologicalObjects CATTopBodyHealerOperator: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopBodyHealerOperator);
   public: // Methodes a usage externe
     
  //============================
  // Constucteur et destructeurs
  //============================
  
   CATTopBodyHealerOperator(CATGeoFactory     * iFactory,
                            CATTopData        * iData,
                            CATExtTopOperator * iExtensible);
  
   ~CATTopBodyHealerOperator();
   
   virtual int Run()=0;                         
   
   virtual CATBoolean GetComputeInteriorHealing()=0;
   
   virtual void SetComputeInteriorHealing(CATBoolean iCompute)=0;
   virtual void SetFacesToHeal(CATLISTP(CATFace) *iFacesToHeal)=0;
   virtual void SetHealDomains(CATBoolean iHealDomains)=0; // Healing de chaque domaine independemment
                                                           // Cette option n'est valide que pour les bodys composes uniquement de wires. 
   virtual void SetHealBody(CATBoolean iHealBody)=0;       // Healing du body: chaque domaine est confronte aux autres domains du body mais pas a lui meme.
                                                           // N'est implemente que pour un body constitue que de wires
   virtual void SetRegularizatorMode(CATBoolean iRegulMode) = 0;

   virtual void SetStabilizeConfusion(CATBoolean iStabilize) = 0; // stabilisation des confusions potentiellement instables dans l'intersection PCrv/PCrv

   virtual void EliminateInitialFatGeometry(CATBoolean iEliminate) = 0;
  
   virtual void DetectDeadEnd(CATBoolean iDeadEnd)=0;
   
   virtual void SetResolution(double iResolution)=0; // resolution seuil 

   virtual void RegularizeSmallEdgeOnly(CATBoolean iSmallEdge)=0; // ne traitre que les intersections dus aux small edges wire/loop interne/loop externe, body wire/shell/volume

  /** @nodoc @nocgmitf */
   void Dump(CATCGMOutput & iOutStream) = 0;

   virtual ListPOfCATBody * GetResultBodies()=0;
   virtual CATBody        * GetResult()=0;
};


#endif
