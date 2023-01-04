#ifndef CATIPGMTopBooleanOperator_h_
#define CATIPGMTopBooleanOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopologicalOperator.h"

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATEdge;
class CATEdgeCurve;
class CATFace;
class CATGeoFactory;
class CATListPOfCATCell;
class CATLoop;
class CATMapX;
class CATMathDirection;
class CATPCurve;
class CATTopData;
class CATLISTP(CATPoint);
class CATLISTP(CATCGMJournal);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopBooleanOperator;

class ExportedByCATGMModelInterfaces CATIPGMTopBooleanOperator: public CATIPGMTopologicalOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopBooleanOperator();

  // Operations booleennes
  virtual CATBody *Compatible(
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATBody *IntersectBodies(CATBody *iBody1, CATBody *iBody2) = 0;

  virtual CATBody *RelimitBody(
    CATBody *iTrimmingBody,
    CATBody *iRelimitedBody,
    int iSideToKeep) = 0;

  virtual CATBody *RelimitBodyInternal(
    CATBody *iTrimmingBody,
    CATBody *iRelimitedBody,
    int iSideToKeep) = 0;

  // Activation du mode MultiThread
  //   iNbThreads : (>1)         nombre de threads
  //                defaut (-1)  on choisit le nombre de processeurs
  //                0            inactivation du multithread
  static void SetMultiThreadMode(int iNbThreads = -1);

  static int GetMultiThreadMode();

  // remise a jour du journal pour Split et Sewing de skin
  static void RattrapJournal(
    CATCGMJournalList *iJournal,
    CATBody *iSplitBody,
    CATBody *iResultBody = (CATBody*)0,
    CATBoolean iIgnoreAbsorptionOrder = FALSE);

  static void RattrapJournal(
    CATTopData *iTopData,
    CATBody *iSplitBody,
    CATBody *iResultBody = (CATBody*)0,
    CATBoolean iIgnoreAbsorptionOrder = FALSE);

  // duplication des return 1 if b1 has been duplicated , 0 if not
  virtual int ActivateBodies(
    CATBody *&ioB1,
    CATBody *iB2,
    CATDomain *&ioDom1,
    CATDomain *iDom2,
    CATLISTP(CATCell) *oAncestorTouchedCell = 0,
    CATLISTP(CATCell) *oImageTouchedCell = 0) = 0;

  virtual int ActivateBodiesAndJournal(
    CATBody *&ioB1,
    CATBody *iB2,
    CATDomain *&ioDom1,
    CATDomain *iDom2,
    CATLONG32 JournalOnVertex) = 0;

  // extraction d'un resultat surfacique a partir d'un body Wires limitant une zone 
  // de confusion face/face (genere par IntersectShells)
  virtual CATBody *BuildFaceConfusion(CATBody *iCutBody, CATBody *iCuttingBody) = 0;

  // Recherche de confusion entre shells :
  // --> 2 : si le shell candidat a au moins 1 contact avec le shell support
  // --> 1 : si le shell candidat est confondu avec le shell support
  // --> 0 : si le shell candidat n'a pas de contact avec le shell support
  virtual short IsTotallyConfused(
    CATBody *iBodyCandidat,
    CATShell *iShellCandidat,
    CATBody *iBodySupport,
    CATShell *iShellSupport) = 0;

  // Relimitation de iCurve par iFace1 et iFace2
  virtual void RelimitCurveOnFaces(
    CATEdgeCurve *iCurve,
    CATPCurve *iPCurveOnFace1,
    CATPCurve *iPCurveOnFace2,
    CATFace *iFace1,
    CATFace *iFace2,
    CATBody *iFace1Body,
    CATBody *iFace2Body,
    CATLISTP(CATEdge) &oIntersectionEdges,
    CATLISTP(CATVertex) &oIntersectionVertices) = 0;

  // Fermeture de la cicatrice, en vue de la decoupe d'un shell, sur une edge bordante
  virtual void ReportOnEdge(CATBody *iShellBody, CATShell *iShell, CATEdge *iEdge) = 0;

  // Fermeture de la cicatrice, en vue de la decoupe d'un shell, sur un vertex de iVertexBody
  virtual void ReportOnVertex(CATBody *iVertexBody, CATVertex *iVertex) = 0;

  // Relimitation de la projection de iEdgeToProject appartenant a iWireOfEdge sur iTarget
  virtual void RelimitWireProjection(
    CATEdge *iEdgeToProject,
    CATWire *iWireOfEdge,
    CATFace *iTarget,
    CATPCurve *iProjectionPCurve,
    CATEdgeCurve *iProjectionEdgeCurve,
    CATPointOnEdgeCurve *iProjectionStartPOEC,
    CATPointOnEdgeCurve *iProjectionEndPOEC,
    CATMathDirection *iProjectionDirection,
    CATOrientation iProjectionVsEdgeToProject,
    CATMapX **ioProjectionMapping,
    CATLISTP(CATEdge) &oEdges,
    CATLISTP(CATVertex) &oVertices,
    CATListOfDouble &oEdgesDistance) = 0;

  // insertion et mise en correspondance de la projection degeneree avec son edge initiale
  virtual void InsertDegenerateWireProjection(
    CATEdge *iEdgeToProject,
    CATWire *iWireOfEdge,
    CATFace *iTarget,
    CATVertex *iDegenerateResult,
    CATMathDirection *iProjectionDirection) = 0;

  virtual void FlattenVertexInFace(CATVertex *iVertexToFlatten, CATFace *iFaceRef) = 0;

  // Activation d'une session de travail entre 2 Bodies relativement a un body de travail
  virtual void ActivateBodiesInSession(CATBody *iBody1, CATBody *iBody2) = 0;

  // Retourne le parametre surfacique d'un point "milieu" de la face donnee en entree
  // Si aucun point satisfaisant n'a pu etre trouve, la fonction renvoie FALSE
  // Usage typique : trouver un point avant d'appeler un positionnement point/volume
  virtual CATBoolean ReturnPointInside(CATFace *iFace, CATSurParam &oSurParam) = 0;

  // transfert des IEs confused d'une face a l'autre
  virtual void TransferConfusedIEFromFace(
    CATEdge *iInEdge,
    CATFace *iSourceFace,
    CATFace *iTargetFace) = 0;

  virtual void AddInScar(CATShell *iTheShell, CATEdge *iTheEdge) = 0;

  virtual void TransfertLyingOn(
    CATBody *iCuttingBody,
    CATLISTP(CATCell) *iCurrentUnderLyingCells,
    CATBody *iCurrentBody,
    CATLISTP(CATCell) *iTargetUnderLyingCells,
    CATBody *iTargetBody) = 0;

  virtual CATLoop *RetrieveLoop(CATEdge *iEdge, CATFace *iFace) = 0;

  // Retourne 1 si iIntersectionBody, Body1D, issu d'une intersection Body-Body (dont iCutBody),
  // contient des edges qui limitent une zone de confusion sur iCutBody
  // 0 sinon
  virtual short IsInterBodyRelimitingAConfusionOn(
    CATBody *iIntersectionBody,
    CATBody *iCutBody) = 0;

  virtual void RetrieveLyingOnOrCuttingPoint(
    CATVertex *iVertex,
    CATLISTP(CATPoint) &oCuttingPoints) = 0;

  virtual void LayDownPointOnFace(
    const CATSurParam &iOnFaceParam,
    CATFace *iFace,
    const CATCrvParam *iOnEdge,
    CATEdge *iEdge,
    CATBody *iBodySupport,
    CATVertex *&oVtx) = 0;

  virtual void LayDownPointOnEdge(
    const CATCrvParam *iOnEdge,
    CATEdge *iEdge,
    CATBody *iBodySupport,
    CATVertex *&oVtx) = 0;

  // CATBoolean Manifolder(CATBody * iBody, CATLISTP(CATBody) * oResultBodies, CATLISTP(CATCGMJournal) * oResultReports);
  virtual CATShell *FullCleanerForShell(
    CATShell *iShell,
    CATBody *iInputBody,
    CATBody *iOutputBody,
    CATLISTP(CATCell) *iFacesToIsolate = NULL,
    CATLISTP(CATCell) *oSeparatedFaces = NULL) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopBooleanOperator(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopBooleanOperator *CATPGMCreateTopBooleanOperator(
  CATGeoFactory *iFactory,
  CATCGMJournalList *iReport = NULL,
  CATBody *iCreationBody = NULL);

// Create
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopBooleanOperator *CATPGMCreateTopBooleanOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iCreationBody);

#endif /* CATIPGMTopBooleanOperator_h_ */
