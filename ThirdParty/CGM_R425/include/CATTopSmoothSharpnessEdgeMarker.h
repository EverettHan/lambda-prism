// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation HCN  10/09/2001
//
//  Cf. CATCreateSmoothSharpnessEdgeMarker.h
//
//=============================================================================

#ifndef __CATTopSmoothSharpnessEdgeMarker_h__
#define __CATTopSmoothSharpnessEdgeMarker_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

class CATLISTP(CATEdge);
class CATEdge;

class ExportedByCATTopologicalObjects CATTopSmoothSharpnessEdgeMarker: public CATTopOperator
{
   public:

     
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopSmoothSharpnessEdgeMarker(CATGeoFactory * iFactory, CATTopData * iTopData);      

   public:

      virtual ~CATTopSmoothSharpnessEdgeMarker();

      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

	  virtual int Run() = 0;
	  
      //=====================================================
      // Methodes specifiques a CATTopSmoothSharpnessEdgeMarker
      //=====================================================

	  // Recupere la liste des edges du body a analyser detectees mortes
	  virtual void GetListOfSmoothEdges(CATLISTP(CATEdge) &oListOfEdges) = 0;

	  // Recupere la liste des edges mortes dupliquees dans le body resultat
	  virtual void GetListOfDuplicatedSmoothEdges(CATLISTP(CATEdge) &oListOfEdges) = 0;

	  // Renvoie l'edge morte dupliquee
	  virtual void GetDuplicatedSmoothEdge(CATEdge* iOrigEdge, CATEdge* &oDuplicatedEdge) = 0;

	  // Recupere la liste des edges de vivicite ambigue
	  virtual void GetListOfAmbigousEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;

	  // Recupere la liste des edges de vivicite deja attribuee
	  virtual void GetListOfFixedEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;
      
};

#endif
