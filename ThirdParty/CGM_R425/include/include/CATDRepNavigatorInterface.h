#ifndef CATDRepNavigatorInterface_H
#define CATDRepNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATManifoldNavigator.h"
#include "ListPOfCATCellManifoldPatternNavigatorInterface.h"
#include "ListPOfCATManifoldRibbonNavigatorInterface.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"
#include "ListPOfCATIPGMDRepGroup.h"
#include "CATErrorDef.h"
#include "CATListOfULONG32.h"
#include "ListPOfCATManifold.h"
#include "ListPOfCATGMLiveShapeButtonNavigatorInterface.h"
#include "ListPOfCATManifoldParamId.h"
class CATHVertex;
class CATCellManifold;
class CATTechnologicalLayer;
class CATManifold;

class ExportedByCATGMModelInterfaces CATDRepNavigatorInterface : public CATManifoldNavigator
{
public:
  
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATDRepNavigatorInterface();


  //-------------------------------------------------
  // Get Navigators (do not delete after use, owned by this)
  //-------------------------------------------------
  virtual HRESULT GetCellManifoldPatternNavigatorsItf(ListPOfCATCellManifoldPatternNavigatorInterface& oPatternNavigators);
  virtual HRESULT GetManifoldRibbonNavigatorsItf(ListPOfCATManifoldRibbonNavigatorInterface& oRibbonNavigators);
  virtual HRESULT GetSpecificManifoldRibbonNavigatorsItf(CATCellManifold * iCMToScan, ListPOfCATManifoldRibbonNavigatorInterface& oRibbonNavigators);
  virtual HRESULT GetGroupNavigators(ListPOfCATCellManifoldGroupNavigator& oGroupNavigators);
  virtual HRESULT GetButtonManifoldNavigatorsItf(ListPOfCATGMLiveShapeButtonNavigatorInterface& oButtonNavigators);
  // New !
  virtual HRESULT GetDraftManifoldNavigatorsItf(ListPOfCATManifoldRibbonNavigatorInterface& oDraftNavigators);

  // ----------------------------------------------------------------------------------------------
  // Read typed DRepGroups, they must not be deleted after use. Release() is already called on them when DRepNavigator is deleted.
  // Use AddRef if you need to keep a valid pointer on them. 
  // @param iTechnicalGroupLayer is Mandatory
  // @param oPGMDRepGroupList is cleaned before processing
  // ----------------------------------------------------------------------------------------------
  virtual HRESULT GetPGMDRepGroupsFromCellManifold(CATCellManifold * iCellManifoldToScan, const CATTechnologicalLayer &iTechnicalGrouplLayer, CATLISTP(CATIPGMDRepGroup) &oPGMDRepGroupList);
  virtual HRESULT GetAllPGMDRepGroups(const CATTechnologicalLayer &iTechnicalGrouplLayer, CATLISTP(CATIPGMDRepGroup) &oPGMDRepGroupList);

  //-------------------------------------------------
  // HVertex exploration
  //-------------------------------------------------
  virtual HRESULT GetHVertexPosition(CATHVertex *iHVertex, CATMathPoint &oPosition);


  // --------------------------------------------------------------------------------------------------------------
  //  ** Publishable & Published DRep **
  // --------------------------------------------------------------------------------------------------------------
  // DRep Access
  virtual HRESULT GetPublishableManifolds(CATCellManifold * ipCellManifold, ListPOfCATManifold & oPublishableManifolds);
  // Get ManifoldList from geometry type
  virtual HRESULT GetManifoldFromGeometryType(const CATListOfULONG32 & iGeometryTypes, ListPOfCATManifold & oManifoldToFollow) const;

  //-------------------------------------------------
  // Implementation
  //-------------------------------------------------
protected :

  CATDRepNavigatorInterface* GetAsDRepNavigatorInterface();
  
  CATDRepNavigatorInterface(); 
  

  //-------------------------------------------------
};


#endif
