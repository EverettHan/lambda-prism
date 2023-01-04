// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation EDS,ICE,XDT  25/06/2002
//
//  Cf. CATCreateTouchDownSkin.h
//
//=============================================================================

#ifndef __CATTopTouchDownSkin_h__
#define __CATTopTouchDownSkin_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATCGMOutput.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "CATListOfDouble.h"

class CATEdge;

class ExportedByCATTopologicalObjects CATTopTouchDownSkin: public CATTopOperator
{
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopTouchDownSkin(CATGeoFactory * iFactory, CATTopData * iTopData);      

   public:

      virtual ~CATTopTouchDownSkin();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      virtual void       SetCoveredFaces(CATLISTP(CATFace) * iCoveredFaces) = 0;
      virtual void       SetTouchDownTolerance(double iTolerance) = 0;
      virtual void       NoGeometricProjection(CATBoolean iNoGeometry) = 0;
      virtual void       SetFollowEdgesCreation(CATBoolean iFollow) = 0;
  
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

      virtual int  Run() = 0;
      virtual void Dump(CATCGMOutput & iOutStream) const = 0;

      //======================================
      // Resultats de l'operateur
      //======================================

      virtual void        GetFreeEdgesAndGaps(CATLISTP(CATEdge)& ioEdges, CATListOfDouble& ioGaps) = 0 ;
      virtual void        GetTouchDownTolerance(double &iTolerance) = 0;
      virtual void        GetTouchDownEdges(int       * oNbListOfEdges, 
                                            CATEdge *** oTouchDownEdges,
                                            int      ** oNbEdgesInList) = 0;
  
      virtual CATBoolean  IsFullyTouchDown() = 0;
  
};

#endif
