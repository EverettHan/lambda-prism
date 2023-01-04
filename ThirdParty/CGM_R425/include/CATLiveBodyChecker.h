/* -*-C++-*- */
#ifndef CATLiveBodyChecker_H
#define CATLiveBodyChecker_H
// COPYRIGHT DASSAULT SYSTEMES 2009
//------------------------------------------------------------------------------------
//
//
//  SERVICE GEOMETRIQUE / TOPOLOGIQUE DEDIE AU CHECK DU CATLIVEBODY
//
//  Owner: ZUS
//------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATCellManifold.h"

class CATLiveBody;
class CATCellManifoldPatternNavigator;
class CATBoneFillet;
class CATPGMDRepBehavior;
class CATSoftwareConfiguration;

//----------------------------------------------------------------------------
// FOR INTERNAL USE ONLY
//----------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATLiveBodyChecker
{

public:
  // Constructor
  CATLiveBodyChecker(CATSoftwareConfiguration *ipConfig /*Mandarory*/, const CATPGMDRepBehavior * ipDRepBehavior);
  // Destructor
  virtual ~CATLiveBodyChecker();

  int CheckLiveBody     (CATLiveBody* iLiveBody, /*const CATPGMDRepBehavior * iDRepBehavior,*/ CATBoolean iForceCheckAnyways=FALSE);
  int QuickCheckLiveBody(CATLiveBody* iLiveBody);


/* Do not use*/
static void RemoveLiveBody(CATLiveBody* &ioLiveBody);
static void RemoveLiveSHMAttributes(CATLiveBody* ioLiveBody);

private:

  int CheckCellManifoldPattern (CATLiveBody* iLiveBody, CATCellManifoldPatternNavigator * iPatternNavigator, CATBoolean iQuickCheck = FALSE);
  int CheckLiveBody_Priv       (CATLiveBody* iLiveBody, CATBoolean iQuickCheck, /*const CATPGMDRepBehavior * iDRepBehavior,*/ CATBoolean iForceCheckAnyways=FALSE);
  int CheckLocalFilletRadii    (CATLiveBody* iLiveBody, CATBoneFillet* iBF, ListPOfCATFace & iAllBoneFaces, ListPOfCATFace & iAllJointFaces, double iRadiusTol);
  int CheckDRepOptions   (const CATLiveBody* iLiveBody, const CATPGMDRepBehavior * iDRepBehavior);

  //----------------------------------------------------------------------------
  // Regle 0 : Verification de la coherence des cellules des CellManifolds 
  //            - Check si les Cells des CM sont connexes et G1.
  //----------------------------------------------------------------------------
  int CheckRule0(CATLiveBody            * iLiveBody);

  //----------------------------------------------------------------------------
  // Regle 1 : Toutes les ReportingCells ont une CellManifold
  //----------------------------------------------------------------------------
  int CheckRule1(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);

  //---------------------------------------------------------------------------------------
  // Regle 2 : Verifier que les cellules des CellManifold correspondent aux ReportingCells
  //--------------------------------------------------------------------------------------- 
  int CheckRule2(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);

  //---------------------------------------------------------------------------------------
  //   Regle 3 : Verifier que les CellManifold derivent bien d'un DeclarativeManifold
  //---------------------------------------------------------------------------------------
  int CheckRule3(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);

  //--------------------------------------------------------------------------------------------------------    
  // Regle 4 : Verifier que les DeclarativeManifold donnent lieu a une representation via les CellManifold
  //--------------------------------------------------------------------------------------------------------
  int CheckRule4(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);

  //--------------------------------------------------------------------------------------------------------    
  // Regle 5 : Verifier que les DeclarativeManifold appartiennent au meme domaine topologique
  //--------------------------------------------------------------------------------------------------------
  int CheckRule5(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);

  //----------------------------------------------------------------------------------------------------------------    
  // Regle 6 : Verifier que les DeclarativeManifold de type DATUM ne sont pas representés par des formes canoniques
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule6(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);
  //----------------------------------------------------------------------------------------------------------------    
  // Regle 7 : Verifier que les donnees dans le DREP sont en accord avec la geometrie  
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule7(CATLiveBody            * iLiveBody, 
                      CATLISTP(CATCell)      & iReportingCells, 
                      ListPOfCATCell         & ioCellCheck,
                      ListPOfCATCellManifold & ioCellManifoldCheck);
  //----------------------------------------------------------------------------------------------------------------    
  // Regle 8 : Verifier les HGeometry
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule8(CATLiveBody& iLiveBody);

  //----------------------------------------------------------------------------------------------------------------    
  // Regle 9 : Verifier les CellManifoldGroup
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule9(CATLiveBody& iLiveBody);

  //----------------------------------------------------------------------------------------------------------------    
  // Regle 10 : Verifier les contextes
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule10(CATLiveBody& iLiveBody);

  //----------------------------------------------------------------------------------------------------------------    
  // Regle 11 : PatternChecker
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule11(CATLiveBody& iLiveBody);

  //----------------------------------------------------------------------------------------------------------------    
  // Regle 11 : Knowledge parameter vs Drep
  //----------------------------------------------------------------------------------------------------------------
  int CheckRule12(const CATLiveBody& iLiveBody);

  // GetSoftwareConfiguration()
  CATSoftwareConfiguration * GetSoftwareConfiguration() const { return _Config; }
  const CATPGMDRepBehavior * GetDRepBehavior()          const { return _DRepBehavior; }

  
  
  // Data Members
  //=======================================
  CATSoftwareConfiguration * _Config;
  const CATPGMDRepBehavior * _DRepBehavior;

};


#endif
