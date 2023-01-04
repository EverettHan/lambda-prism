/* -*-c++-*- */
#ifndef CATTopBooleanOperator_h
#define CATTopBooleanOperator_h
/* -*-c++-*- */
//===========================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1999
//
// DESCRIPTION : Topological toolkit : suite de CATTopologicalOperator.
//               Separe uniquement pour minimiser les impacts de build.
// 
//=============================================================================

#include "BOOPER.h"
#include "CATTopologicalOperator.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "CATListOfDouble.h"
#include "CATListOfCATPoints.h"

class CATBody;
class CATGeoFactory;
class CATCGMJournalList;
class CATDomain;
class CATFace;
class CATLoop;
class CATEdge;
class CATTopData;

class CATPCurve;
class CATEdgeCurve;
class CATMapX;
class CATMathDirection;
class CATListPOfCATCell;
class CATLISTP(CATCGMJournal);

class ExportedByBOOPER CATTopBooleanOperator : public CATTopologicalOperator
{
  CATCGMVirtualDeclareClass(CATTopBooleanOperator);
 public:

   CATTopBooleanOperator(CATGeoFactory* iFactory, CATTopData* iData, CATBody* iCreationBody);
   CATTopBooleanOperator(CATGeoFactory* iFactory, CATCGMJournalList* iReport=NULL, CATBody* iCreationBody=NULL);
   ~CATTopBooleanOperator();

   // Operations booleennes
   CATBody * Compatible (CATBody* iBody1, CATBody* iBody2);
   CATBody * IntersectBodies (CATBody* iBody1, CATBody* iBody2);
   CATBody * RelimitBody(CATBody* iTrimmingBody, CATBody* iRelimitedBody, int iSideToKeep);
   CATBody * RelimitBodyInternal(CATBody* iTrimmingBody, CATBody* iRelimitedBody, int iSideToKeep);

   // Activation du mode MultiThread
   //   iNbThreads : (>1)         nombre de threads
   //                defaut (-1)  on choisit le nombre de processeurs
   //                0            inactivation du multithread
   static void SetMultiThreadMode(int iNbThreads=-1); 
   static int  GetMultiThreadMode();

   // remise a jour du journal pour Split et Sewing de skin
   static void RattrapJournal (CATCGMJournalList* iJournal, 
                               CATBody*           iSplitBody,
                               CATBody*           iResultBody = (CATBody*)0,
                               CATBoolean         iIgnoreAbsorptionOrder = FALSE);
  
   static void RattrapJournal (CATTopData * iTopData, 
                               CATBody    * iSplitBody,
                               CATBody    * iResultBody = (CATBody*)0,
                               CATBoolean   iIgnoreAbsorptionOrder = FALSE);

   // duplication des return 1 if b1 has been duplicated , 0 if not
   int ActivateBodies(CATBody*& ioB1, CATBody* iB2, CATDomain*& ioDom1, CATDomain* iDom2, 
                      CATLISTP(CATCell)* oAncestorTouchedCell = 0 , CATLISTP(CATCell)* oImageTouchedCell = 0);
   int ActivateBodiesAndJournal(CATBody*& ioB1, CATBody* iB2, CATDomain*& ioDom1, CATDomain* iDom2, CATLONG32 JournalOnVertex);

   // extraction d'un resultat surfacique a partir d'un body Wires limitant une zone 
   // de confusion face/face (genere par IntersectShells)
   CATBody* BuildFaceConfusion(CATBody* iCutBody, CATBody* iCuttingBody);
   
   // Recherche de confusion entre shells :
   // --> 2 : si le shell candidat a au moins 1 contact avec le shell support
   // --> 1 : si le shell candidat est confondu avec le shell support
   // --> 0 : si le shell candidat n'a pas de contact avec le shell support
   short IsTotallyConfused(CATBody* iBodyCandidat,CATShell* iShellCandidat,CATBody* iBodySupport,CATShell* iShellSupport);

   // Relimitation de iCurve par iFace1 et iFace2
   void RelimitCurveOnFaces(CATEdgeCurve        * iCurve, 
                            CATPCurve           * iPCurveOnFace1,
                            CATPCurve           * iPCurveOnFace2,
                            CATFace             * iFace1,
                            CATFace             * iFace2,
                            CATBody             * iFace1Body,
                            CATBody             * iFace2Body,
                            CATLISTP(CATEdge)   & oIntersectionEdges,
                            CATLISTP(CATVertex) & oIntersectionVertices);

   // Fermeture de la cicatrice, en vue de la decoupe d'un shell, sur une edge bordante
   void ReportOnEdge(CATBody * iShellBody, CATShell * iShell, CATEdge * iEdge);

   // Fermeture de la cicatrice, en vue de la decoupe d'un shell, sur un vertex de iVertexBody
   void ReportOnVertex(CATBody * iVertexBody, CATVertex * iVertex);
  
   // Relimitation de la projection de iEdgeToProject appartenant a iWireOfEdge sur iTarget
   void RelimitWireProjection(CATEdge              *  iEdgeToProject,
                              CATWire              *  iWireOfEdge,
                              CATFace              *  iTarget,
                              CATPCurve            *  iProjectionPCurve,
                              CATEdgeCurve         *  iProjectionEdgeCurve,
                              CATPointOnEdgeCurve  *  iProjectionStartPOEC,
                              CATPointOnEdgeCurve  *  iProjectionEndPOEC,
                              CATMathDirection     *  iProjectionDirection,
                              CATOrientation          iProjectionVsEdgeToProject,
                              CATMapX              ** ioProjectionMapping,
                              CATLISTP(CATEdge)    &  oEdges,
                              CATLISTP(CATVertex)  &  oVertices,
                              CATListOfDouble      &  oEdgesDistance);
   // insertion et mise en correspondance de la projection degeneree avec son edge initiale
   void InsertDegenerateWireProjection(CATEdge     *  iEdgeToProject,
     CATWire              *  iWireOfEdge,
     CATFace              *  iTarget,
     CATVertex            *  iDegenerateResult,
     CATMathDirection     *  iProjectionDirection);

   void FlattenVertexInFace(CATVertex* iVertexToFlatten, CATFace* iFaceRef);
  
   // Activation d'une session de travail entre 2 Bodies relativement a un body de travail
   void ActivateBodiesInSession(CATBody * iBody1, CATBody * iBody2);

   // Retourne le parametre surfacique d'un point "milieu" de la face donnee en entree
   // Si aucun point satisfaisant n'a pu etre trouve, la fonction renvoie FALSE
   // Usage typique : trouver un point avant d'appeler un positionnement point/volume
   CATBoolean ReturnPointInside(CATFace            *iFace,
                                CATSurParam        &oSurParam);

   // transfert des IEs confused d'une face a l'autre
   void TransferConfusedIEFromFace(CATEdge* iInEdge, CATFace* iSourceFace, CATFace* iTargetFace);
   
   void AddInScar(CATShell * iTheShell, CATEdge * iTheEdge);

   void TransfertLyingOn(CATBody* iCuttingBody, CATLISTP(CATCell)* iCurrentUnderLyingCells, CATBody* iCurrentBody,
                         CATLISTP(CATCell)* iTargetUnderLyingCells,CATBody* iTargetBody);

   CATLoop* RetrieveLoop(CATEdge * iEdge, CATFace * iFace);
  
   // Retourne 1 si iIntersectionBody, Body1D, issu d'une intersection Body-Body (dont iCutBody),
   // contient des edges qui limitent une zone de confusion sur iCutBody
   // 0 sinon
   short IsInterBodyRelimitingAConfusionOn(CATBody * iIntersectionBody, CATBody * iCutBody);  

   void  RetrieveLyingOnOrCuttingPoint(CATVertex          * iVertex,
                                       CATLISTP(CATPoint) & oCuttingPoints);
   
   void LayDownPointOnFace(const CATSurParam & iOnFaceParam,CATFace * iFace,const CATCrvParam * iOnEdge,CATEdge * iEdge,
                           CATBody * iBodySupport, CATVertex *& oVtx);
   void LayDownPointOnEdge( const CATCrvParam  * iOnEdge, CATEdge * iEdge, CATBody * iBodySupport,  CATVertex *& oVtx);

   // CATBoolean Manifolder(CATBody * iBody, CATLISTP(CATBody) * oResultBodies, CATLISTP(CATCGMJournal) * oResultReports);
   CATShell * FullCleanerForShell( CATShell * iShell, 
                                   CATBody  * iInputBody, 
                                   CATBody  * iOutputBody, 
                                   CATLISTP(CATCell) * iFacesToIsolate = NULL, 
                                   CATLISTP(CATCell) * oSeparatedFaces = NULL);
 private:
   
   // interne du ActivateBodiesAndJournal
   void LogDuplicatedExtremities(CATWire * iDuplicatedWire, CATCGMJournalList * iLocalJournal);
   void ReportCreationOnDuplicatedBody(CATBody * iDuplicatedBody, CATCGMJournalList * iLocalJournal, CATLONG32 JournalOnVertex);
   void ReportCreationOnDuplicatedDomain(CATWire* iDuplicatedWire, CATCGMJournalList* iLocalJournal, CATLONG32 JournalOnVertex);
   // internes du RelimitBody
   void GetRegularBodies(CATBody*  iHybridBody,
                         CATBody*& oLumpsBody, CATBody*& oShellsBody,
                         CATBody*& oWiresBody, CATBody*& oVIVBody);

   CATBody* UniteBodies(CATBody* iB1, CATBody* iB2, int iDestructive);
   CATBody* UniteBodies(CATBody* iB1, CATBody* iB2, CATBody* iB3, CATBody* iB4, CATBody* iB5, int iDestructive);

   CATBody*  SkinsRelimitSkins(CATBody* iB1, CATBody* iB2);
   CATBody*  SkinsRelimitWires(CATBody* iB1, CATBody* iB2);
   void      SkinRelimitWire(CATBody*& ioResult, CATBody* iB1, CATDomain* iDom1, CATBody* iB2, CATDomain* iDom2, CATBoolean iActivateDone = FALSE);

   // Methode partagee entre Compatible et IntersectBodies
   CATBody * UnionOrIntersection (CATBody* iBody1, CATBody* iBody2, CATBoolean iComputeIntersection);
};

// Create
ExportedByBOOPER CATTopBooleanOperator* CATCreateTopBooleanOperator(CATGeoFactory*     iFactory,
                                                                    CATTopData*        iData,
                                                                    CATBody*           iCreationBody);

#endif
