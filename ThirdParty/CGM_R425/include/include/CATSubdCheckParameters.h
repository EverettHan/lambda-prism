// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
//
// Classe regroupant les parametres necessaires aux methodes de bas niveau
// traitant du check d'intersection
//=============================================================================

#ifndef __CATSubdCheckParameters_h__
#define __CATSubdCheckParameters_h__

#include "BOOLEAN.h"

#include "CATSubdBoolean.h"
#include "CATCheckDiagnosis.h"
#include "CATCheckDiagnosisList.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATCXBody;
class CATSubdArrayOccurenceP;
class CATSubdOccurence;


class ExportedByBOOLEAN CATSubdCheckParameters : public CATCGMVirtual
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATSubdCheckParameters(CATGeoFactory  * iFactory,
                             CATSubdBoolean   iDiagnosisMode         = CATSubdBooleanFalse,
                             CATSubdBoolean   iTopologicalResultMode = CATSubdBooleanFalse,
                             CATCXBody      * iResultBody            = (CATCXBody*)0);

      virtual ~CATSubdCheckParameters();
      

      //====================================
      // Acces aux parametres de l'operateur
      //====================================

      INLINE CATSubdBoolean   GetFullCheckMode() const;  
      
      INLINE CATSubdBoolean   GetDiagnosisMode() const;
      INLINE CATSubdBoolean   GetTopologicalResultMode() const;
      INLINE CATSubdBoolean   GetRepairMode() const;
      INLINE CATSubdBoolean   GetRegulOnlySmallEdgeMode() const;

      CATSubdBoolean   GetRegularizatorMode() const;

      INLINE double           GetTolerance() const;
      INLINE CATSubdBoolean   GetToleranceRestrictedMode() const;

      INLINE CATCXBody      * GetResultBody() const;

      CATTopology    * GetCurrentCheckedTopo() const;

      CATSubdBoolean GetAcceptVerticesInFace();
      CATSubdBoolean GetAcceptTangentConfigurations();

      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      INLINE void SetFullCheckMode(CATSubdBoolean iFullCheckMode);                                      

      void SetDiagnosisMode(CATSubdBoolean iDiagnosisMode);
      void SetTopologicalResultMode(CATSubdBoolean iTopologicalResultMode);
      void SetRepairMode();
      void SetRegularizatorMode(CATSubdBoolean iRegulMode);
      void SetRegulOnlySmallEdgeMode(CATSubdBoolean iRegulMode);

      INLINE void SetTolerance(double iTolerance);
      INLINE void SetToleranceRestrictedMode(CATSubdBoolean iToleranceRestrictedMode);

      void SetResultBody(CATCXBody * iResultBody);

      void SetCurrentCheckedTopo(CATTopology * iCurrentCheckedTopo);

      void SetAcceptVerticesInFace(CATSubdBoolean iAcceptVerticesInFace);
      void SetAcceptTangentConfigurations(CATSubdBoolean iAcceptTangentConfigurations);

      //====================================
      // Methodes de gestion des diagnostics
      //====================================

      CATSubdBoolean         AddDiagnosis(CATCheckDiagnosis * iDiagnosis);
      CATCheckDiagnosisList* GetDiagnosisList() const;

      CATSubdBoolean AddCheckDiagnosis(   CATCheckDiagnosis                           * ipDiagnosis,
                                          CATCheckDiagnosis::CATCheckDiagnosisTypeId    iTypeId,
                                          CATCheckDiagnosis::MessageId                  iMessageId,
                                          CATSubdBoolean                                iMustThrow,
                                          CATSubdBoolean                                iMustDump,
                                          CATSubdBoolean                                iMustStop,
                                          const char                                  * iSpecificMessage = (const char *)0,
                                          void                                        * ipAssociatedData = 0 );

      CATSubdBoolean CreateCheckDiagnosis(CATLISTP(CATGeometry)                       & ilsAssociatedGeometry,
                                          CATCheckDiagnosis::CATCheckDiagnosisTypeId    iTypeId,
                                          CATCheckDiagnosis::MessageId                  iMessageId,
                                          CATSubdBoolean                                iMustThrow,
                                          CATSubdBoolean                                iMustDump,
                                          CATSubdBoolean                                iMustStop,
                                          const char                                  * iSpecificMessage = (const char *)0,
                                          void                                        * ipAssociatedData = 0 );

      CATSubdBoolean CreateInvalidTopologicalDataCheckDiagnosis(CATGeometry                      * iGeometry,
                                                                CATCheckDiagnosis::MessageId       iMessageId,
                                                                CATSubdBoolean                     iMustThrow,
                                                                CATSubdBoolean                     iMustDump,
                                                                CATSubdBoolean                     iMustStop,
                                                                const char                       * iSpecificMessage = (const char *)0);
      
      CATSubdBoolean CreateUnaccurateTopologyCheckDiagnosis    (CATGeometry                      * iGeometry,
                                                                CATCheckDiagnosis::MessageId       iMessageId,
                                                                double                             iGap,
                                                                CATSubdBoolean                     iMustThrow,
                                                                CATSubdBoolean                     iMustDump,
                                                                CATSubdBoolean                     iMustStop,
                                                                const char                       * iSpecificMessage = (const char *)0);
      
      CATSubdBoolean CreateUnaccurateGeometryCheckDiagnosis    (CATGeometry                      * iGeometry,
                                                                CATCheckDiagnosis::MessageId       iMessageId,
                                                                CATSubdBoolean                     iMustThrow,
                                                                CATSubdBoolean                     iMustDump,
                                                                CATSubdBoolean                     iMustStop,
                                                                const char                       * iSpecificMessage = (const char *)0);
      
      CATSubdBoolean CreateInvalidDataStructureCheckDiagnosis  (CATGeometry                      * iGeometry,
                                                                CATCheckDiagnosis::MessageId       iMessageId,
                                                                CATSubdBoolean                     iMustThrow,
                                                                CATSubdBoolean                     iMustDump,
                                                                CATSubdBoolean                     iMustStop,
                                                                const char                       * iSpecificMessage = (const char *)0);
      
      CATSubdBoolean    MustReturn() const;

      //====================================
      // Methodes de gestion des coupantes
      //====================================

      void CreateCuttingList();
      void AddCutting(CATSubdOccurence * iCutting);


   protected:

      void CreateDiagnosisList();                        // Cree une liste pour conserver les diagnostics
      void DeleteDiagnosisList();                        // Detruit la liste des diagnostics

      void SetMustStop(CATSubdBoolean iMustStop);

   protected: // Donnees membres


      CATSubdBoolean   _FullCheckMode;                 // Indique si l'operateur doit determiner toutes les
                                                       // erreurs ou s'il doit s'arreter a la premiere

      // Gestion de la tolerance
      double           _Tolerance;                     // Tolerance utilisee pour les operateurs geometriques
                                                       // (arete/arete et face/face) - Bloquee a la tolerance 
      CATSubdBoolean   _ToleranceRestrictedMode;       // Indique si les recadrages au dela de la tolerance
                                                       // ne doivent pas etre executes (si True, les trous
                                                       // dans les vertex superieur a la tolerance ne sont
                                                       // pas admis)
      
      // Body contenant les elements crees lors des tests et pouvant etre federes pour
      // etre presentes comme resultats du check (wires,viv)
      CATSubdBoolean                _TopologicalResultMode;   // Indique si les elements invalides doivent etre crees
                                                              // sous forme d'objets modeles ds _TopologicalResult 
      CATCXBody                   * _TopologicalResult;       

      // Gestion des diagnostics associes aux erreurs et warnings detectes
      CATSubdBoolean                _DiagnosisMode;
      CATCheckDiagnosisList         * _DiagnosisList;

      // Reparation des faces
      CATSubdBoolean                _RepairMode;     // Mode de reparation des faces (pose de coupantes)
      CATSubdArrayOccurenceP      * _CuttingList;
      CATSubdBoolean                _RegularizatorMode;
      CATSubdBoolean                _RegulOnlySmallEdgeMode;

      // Topologie courante checkee. face||wire 
      CATCXTopology       * _CurrentCheckedTopo;          
      CATSubdBoolean        _CurrentCheckedIsInvalid;
     
      CATSubdBoolean        _MustStop;

      CATSubdBoolean _AcceptVerticesInFace;
      CATSubdBoolean _AcceptTangentConfigurations;
};


INLINE CATSubdBoolean CATSubdCheckParameters::GetFullCheckMode() const
{
   return _FullCheckMode;
}

INLINE double CATSubdCheckParameters::GetTolerance() const
{
   return _Tolerance;
}

INLINE CATSubdBoolean CATSubdCheckParameters::GetToleranceRestrictedMode() const
{
   return _ToleranceRestrictedMode;
}

INLINE CATSubdBoolean CATSubdCheckParameters::GetDiagnosisMode() const
{
   return _DiagnosisMode;
}

INLINE CATSubdBoolean CATSubdCheckParameters::GetTopologicalResultMode() const
{
   return _TopologicalResultMode;
}

INLINE CATSubdBoolean CATSubdCheckParameters::GetRepairMode() const
{
   return _RepairMode;
}

INLINE CATSubdBoolean CATSubdCheckParameters::GetRegulOnlySmallEdgeMode() const
{
   return _RegulOnlySmallEdgeMode;
}


INLINE CATCXBody * CATSubdCheckParameters::GetResultBody() const
{
   return _TopologicalResult;
}

INLINE void CATSubdCheckParameters::SetTolerance(double iTolerance)
{
   _Tolerance = iTolerance;
}

INLINE void CATSubdCheckParameters::SetToleranceRestrictedMode(CATSubdBoolean iToleranceRestrictedMode)
{
   _ToleranceRestrictedMode = iToleranceRestrictedMode;
}

INLINE void CATSubdCheckParameters::SetFullCheckMode(CATSubdBoolean iFullCheckMode)
{
   _FullCheckMode = iFullCheckMode;
}

#endif
