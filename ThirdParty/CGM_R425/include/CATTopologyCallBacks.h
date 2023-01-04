#ifndef CATTopologyCallBacks_H
#define CATTopologyCallBacks_H
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
//
// CATTopologyCallBacks:
// Utility for topology calls from GeometricOperators
//
//                                                    Nicolas LOCHARD
//=============================================================================
// Usage notes:
//
// classe virtuelle à instancier au niveau topologique
// puis transmettre un objet de la classe à l'operateur geometrique concerné
//=============================================================================
// 28 01 05 NLD Creation par extraction depuis CATFrFTopologyCallBacks
//              ConstructsBodyFromGeometry()
// 28 01 05 NLD Ajout AddDiagnosis() et CreateTopOpInError()
// 08 08 05 JSX Ajout de AddWarning()
// 11 10 06 NLD Ajout de GetWarning() qui descend de CATFrFTopologyCallBacks
// 28/03/13 NLD Ajout de AddRef(), Release()
//              Le destructeur n'est plus accessible (il faut utiliser Release())
// 03/07/19 NLD Ajout CurvesReduction()
// 11/07/19 NLD Définition des méthodes statiques de création/destruction de CallBacks
//=============================================================================

#define CATTopologyCallBacks_ImplementAutomaticCallBacks "EN COURS NLD110719"

class CATBody ;
class CATGeoFactory ;
class CATGeometry ;
class CATSoftwareConfiguration ;
class CATTopOpInError ;
class CATError ;
class CATCGMDiagnosis;

#include <CATCollec.h> // pour CATListPV
#include <CATListPV.h>
class CATLISTP(CATCrvLimits);
class CATLISTP(CATCurve);

#include "CATGMModelInterfaces.h"
#include <CATListOfCATGeometries.h>
#include <CATCGMVirtual.h>
#include "CATDataType.h"

class ExportedByCATGMModelInterfaces CATTopologyCallBacks : public CATCGMVirtual
{
 protected:
 
   virtual ~CATTopologyCallBacks()
   {
   } ;
 
 public:
 
   // Construction d'un body à partir d'un element geometrique
   // Voir implementation pour types acceptes
   // rend un body nul si type non accepté
 
   virtual void              ConstructsBodyFromGeometry(      CATGeoFactory            *  iFactory,
                                                              CATSoftwareConfiguration *  iConfig ,
                                                              CATGeometry              *  iGeom   ,
                                                              CATBody                  *& oBody   ) =0;
   /*
   // Ajout de listes de bodies de localisation et de contexte a une erreur
   // via l'ajout d'un CATCGMDiagnosis
   virtual void  AddDiagnosis             (CATTopOpInError* iTopError, 
                                           CATLISTP(CATBody) iLocationList,
                                           CATLISTP(CATBody) iContextList)=0 ; 

   // Creation d'une erreur de type CATTopOpInError
   virtual CATError* CreateTopOpInError(const char *msgId)=0;
   */

   // Creation d'une erreur de type CATTopOpInError
   // arguments supplementaires optionnels pour aide au diagnostic
   // les geometries sont converties en bodies
   virtual CATError*         CreateTopOpInError        (const char                     *  msgId         ,
                                                              CATGeoFactory            *  iFactory      = NULL,
                                                              CATSoftwareConfiguration *  iConfig       = NULL,
                                                              CATLISTP(CATGeometry)    *  iLocationList = NULL,
                                                              CATLISTP(CATGeometry)    *  iContextList  = NULL) =0;

   // Ajout d'un warning 
   // Il peut ensuite etre transmis a l'operateur topologique
   // C'est ce dernier qui le detruira 
   // Pour l'instant seul le premier warning est utilisé
   virtual void              AddWarning                (      CATCGMDiagnosis          *  iDiag         )=0;
   
   // Recuperation d'un warning
   virtual CATCGMDiagnosis * GetWarning                ()=0;

   // Add    a reference to this object (and give back reference counter)
   virtual int               AddRef                    (      void                     *  iDebugPointingObject = 0) = 0;

   // Delete a reference to this object (and give back reference counter) (delete the object if reference counter decreased to 0)
   virtual int               Release                   (      void                     *  iDebugPointingObject = 0) = 0;

   // Deformation dediée Fillet NLD pour SMT1
   // RESTRICTED USE. DEDICATED PARAMETERIZATION
   // Arguments may change according to needs
   virtual void              CurvesReduction           (      CATGeoFactory            *  iFactory              ,
                                                              CATSoftwareConfiguration* iSoftwareConfiguration,
                                                              CATLISTP(CATCurve)      & iCurves               ,
                                                              CATLISTP(CATCrvLimits)  & iLims                 ,
                                                              CATListOfInt            & iOris                 ,
                                                              double                    iG1Threshold          , // in degree
                                                              double                    iDeformationTol       ,
                                                              CATLISTP(CATCurve)      & oResultCrvs           ) = 0;

} ;




#ifdef CATTopologyCallBacks_ImplementAutomaticCallBacks

#include "CATGMModelInterfaces.h"
// Copie le 110719 depuis CATFrFTopologyCallBacks.h
// avec renommages

// TopoOpeDebugAutomaticCATTopologyCallBacks            remplace AdvTopoOpeDebugAutomaticCATFrFTopologyCallBacks
// CATTopologyCallBacks                                 remplace CATFrFTopologyCallBacks
// CATTopoOpeCallBacks                                  remplace CATAdvTopoOpeCallBacks
// TopoOpeCallBacks                                     remplace AdvTopoOpeCallBacks
// SetCreateOrRemoveDebugAutomaticCATTopoOpeCallBacks   remplace SetCreateOrRemoveDebugAutomaticCATAdvTopoCallBacks
// OkSetCreateOrRemoveDebugAutomaticCATTopoOpeCallBacks remplace OkSetCreateOrRemoveDebugAutomaticCATAdvTopoCallBacks
// CATTopologicalOperatorsDummy                         remplace CATAdvancedTopologicalOpeDummy
// SetCreateOrRemoveDebugAutomaticCATTopologyCallBacks  remplace SetCreateOrRemoveDebugAutomaticCATFrFTopologyCallBacks
// CreateOrRemoveDebugAutomaticCATTopologyCallBacks     remplace CreateOrRemoveDebugAutomaticCATFrFTopologyCallBacks
// ExportedByCATGMModelInterfaces                       remplace ExportedByFrFAdvancedObjects
// DebugAutomaticLoadTopologicalOperators               remplace DebugAutomaticLoadAdvancedTopologicalOpe
//-----------------------------------------------------------------------------
// Definition de la methode statique de creation/destruction automatique de callback topologique
// (creation si pointeur nul en entree, destruction si pointeur non nul)
//-----------------------------------------------------------------------------
extern "C" ExportedByCATGMModelInterfaces
void SetCreateOrRemoveDebugAutomaticCATTopologyCallBacks(void (*iDebugAutomaticCATFrFTopologyCallBacks)(CATTopologyCallBacks*&)) ;

//-----------------------------------------------------------------------------
// Creation ou destruction de callback topologique (si on dispose de l'adresse d'une methode
// adequate fournie au prealable par la topologie)
//-----------------------------------------------------------------------------
extern "C" ExportedByCATGMModelInterfaces
void CreateOrRemoveDebugAutomaticCATTopologyCallBacks(CATTopologyCallBacks*& ioCallBacks) ;

//-----------------------------------------------------------------------------
// Chargement dynamique de TopologicalOperators via CATTopologicalOperatorsDummy()
// rend 1 si chargement OK, 0 sinon
//-----------------------------------------------------------------------------
// pas necessaire de l'exporter, mais bon, si quelqu'un en a besoin
extern "C" ExportedByCATGMModelInterfaces
int DebugAutomaticLoadTopologicalOperators() ;

#endif

#endif 
