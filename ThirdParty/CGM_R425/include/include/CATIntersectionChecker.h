// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
//
// Interface de l'operateur de check d'intersection de topologies au sein 
// d'un meme body (classe de base pour les checks de wire, de shell et de
// bord de face).
//=============================================================================

#ifndef __CATIntersectionChecker_h__
#define __CATIntersectionChecker_h__

#include "CATChecker.h"
#include "CheckOperators.h"
#include "CATTopOperator.h"
#include "CATListPOfCATCheckDiagnoses.h"

class CATCXIntersectionChecker;


class ExportedByCheckOperators CATIntersectionChecker: public CATChecker
{
  CATCGMVirtualDeclareClass(CATIntersectionChecker);
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATIntersectionChecker(CATGeoFactory            * iFactory,
                             CATTopData               * iData,
                             CATCXIntersectionChecker * iImplementation);
      
      virtual ~CATIntersectionChecker();
      

      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

      //====================================
      // Acces aux parametres de l'operateur
      //====================================

      CATBoolean GetCheckOnlySelfIntersection() const;
      CATBoolean GetCheckOnlyDomainsIntersection() const;
      CATBoolean GetTopologicalResultMode() const;
      CATBoolean GetToleranceRestrictedMode() const;


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      void SetCheckOnlySelfIntersection();
      void SetCheckOnlyDomainsIntersection();
      void SetTopologicalResultMode(CATBoolean iTopologicalResultMode);
      void SetToleranceRestrictedMode(CATBoolean iToleranceRestrictedMode);
};

#endif
