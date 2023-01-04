#ifndef CATCellManifoldPatternNavigator_H
#define CATCellManifoldPatternNavigator_H

#include "CATPersistentCell.h"

#include "CATTopDefine.h"
#include "CATCollecRoot.h"
#include "CATMathOBBCloud.h"   
#include "CATCellManifoldGroupNavigator.h"
#include "CATListOfShort.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATLISTP_CATMathTransformation.h"
#include "CATCollec.h"
#include "CATDRepNavigator.h"
#include "ListPOfCATCellManifoldPatternAdvancedNavigator.h"
#include "CATCellManifoldPatternNavigatorInterface.h"
#include "CATPatternType.h"
#include "CATVariationalPatternParameters.h"
#include "CATPatternActivationStatus.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATPatternBuildingType.h"
#include "ListPOfCATPatternReferenceManifoldAttribute.h"

class CATLiveBody;
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATCellManifoldGroup;
class CATPatternManifoldSpecificationAttribute;
class CATMathTransfromation;
class CATMathLine;
class CATLISTPV;
class CATCellHashTable;
class CATCGMHashTableWithAssoc;
class CATManifoldAttribute;
class CATGeometry;
class CATCellManifoldPatternAdvancedNavigator;
class CATCellManifoldHashTableWithAttributeAssoc;
class CATCell;
class CATInstancesNavigator;
class CATLISTP(CATCell);
class CATCellManifoldGroupCarrier;
class CATlsoDataCache;
class CATPersistentCellInfra;
class CATGMSpecInfra;
class CATCellManifoldPatternNavigator2;


class ExportedByPersistentCell CATCellManifoldPatternNavigator : public CATCellManifoldPatternNavigatorInterface
{
public:
  enum PatternType {Linear, Circular, User};

  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATCellManifoldPatternNavigator, CATCellManifoldPatternNavigatorInterface);
  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  //CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATCellManifoldPatternNavigator(const CATTopData &iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup); 
  CATCellManifoldPatternNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup* iNetworkGroup); 
  CATCellManifoldPatternNavigator(CATCellManifoldPatternNavigator * iPatternNavigator);

  // DO NOT USE : For Unstream Only
  CATCellManifoldPatternNavigator();



  // Destructor
  virtual ~CATCellManifoldPatternNavigator();

  // @nocgmitf
  CATCellManifoldPatternNavigator * GetAsPatternNavigator();

  //-------------------------------------------------------------------------------------------------------
  // Options
  //-------------------------------------------------------------------------------------------------------
  // _EditionMode = 1 si on tient compte des infos des parameters.
  void SetEditionMode(CATBoolean iEditionMode = TRUE);
  CATBoolean GetEditionMode();

  //-------------------------------------------------
  //    Methodes globales  
  //-------------------------------------------------


  // Renvoie le group qui contient tout le pattern. 
  // (used by appli)
  //------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup)const ;

  // Renvoie un point qui permet de visualiser le centre de la reference. 
  // (used by appli)
  //----------------------------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetOriginPoint(CATMathPoint & oOriginPoint) const;

  // Renvoie le type du pattern (Linear, Circular, ...)
  // (used by appli)
  //-----------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetPatternType(CATPatternType &oType) const;
  
  // Renvoie la transformation qui permet de passer d'une instance l'instance suivante.
  // (used by appli)
  // @nocgmitf
  //-------------------------------------------------------------------------------------
  virtual HRESULT GetUnitaryTransformation(CATMathTransformation &ioUnitaryTransfo) const;
  HRESULT GetUnitaryTransfo(CATMathTransformation &ioUnitaryTransfo) const;
  HRESULT GetUnitaryTransformation(CATMathTransformation &ioUnitaryTransfo, CATBoolean iEditionContext) const;
  // @nocgmitf
  HRESULT GetPatternType(PatternType &oType) const;
  // @nocgmitf
  HRESULT GetTranslationVector(CATMathVector &ioTranslationVector, CATBoolean & oVectorIsEdited) const;
  // 1 : Depression
  // 2 : Protrusion
  // 3 : Unknown
  // @nocgmitf
  CATLONG32 GetExplicitType() const;

  // @nocgmitf
  HRESULT GetCurrentNumberOfInstances(short &oNbInstances) const;
  // @nocgmitf
  HRESULT GetNumberOfReferenceCellManifolds(short &oNbRefCM);
   // @nocgmitf
  HRESULT GetFather(CATGeometry * iSon, CATCellManifoldGroup *& oFatherGroup);
  // @nocgmitf
  CATBoolean PatternEditorContext();
  // @nocgmitf
  CATBoolean PatternVariationalContext();
  // @nocgmitf
  CATBoolean PatternIsBeingModified();
  // @nocgmitf
  CATLiveBody* GetLiveBody() const;
  // @nocgmitf
  CATLiveBody* CreateOldReferenceLiveBody() const;
  // @nocgmitf
  // HRESULT GetUnitaryTransfo(CATMathTransformation &oUnitaryTransfo) const;
  // Renvoie TRUE si le domain est entierement inclus dans le pattern.
  //CATBoolean BelongsToPattern(CATDomain * iDomain);

  // @nocgmitf
  void DiGraphDump(CATCGMOutput& Output);
  // @nocgmitf
  CATBoolean ReferenceIsBeingEdited();
  // @nocgmitf
  void SetVariationalPatternParameters(CATVariationalPatternParameters * iVariationalPatternParameters);
  // @nocgmitf - edit _VarUnitaryTransfo
  void SetManifoldParameters(const ListPOfCATManifoldParameter &iManifoldParamList); 
  // @nocgmitf 
  void SetManifoldParameters(const CATGMSpecInfra *ipSpecInfra, int iNumOperatorId);

  // @nocgmitf
  //CATBoolean MovePattern() const;
  // @nocgmitf
  CATBoolean IsInCollision();
  // @nocgmitf
  CATBoolean Locate(CATCellManifoldGroup * iGroup);
  // @nocgmitf
  HRESULT GetSupportCellManifolds(CATLISTP(CATCellManifold) &oSupportManifolds);

  // Check si le model est coherent
  // Si oErrorOutput est donné, le CheckModel ne fait pas de Throw et renvoie les traces d'erreurs.
  // @nocgmitf
  //-------------------------------------------------------------------------------------
  HRESULT CheckModel(int & oError, CATCGMOutput *oErrorOutput=NULL);


  
  //return TRUE if iCells cover all the group. Could be overloaded (as in Pattern)
  // @nocgmitf
  virtual CATBoolean IsFullyCoveredByCells(const ListPOfCATCellManifold &iCellManifolds);
  
  //return TRUE if this group is modifiable with CATManifoldEditor
  // @nocgmitf
  virtual CATBoolean IsEditable() const;


  //-------------------------------------------------
  //    Methodes traitant de la reference
  //-------------------------------------------------

   // Renvoie les CellManifold des Faces de reference
  // @nocgmitf
  HRESULT GetReferenceCellManifolds(CATLISTP(CATCellManifold) &ioReferenceCellManifolds) const;

  // Renvoie les CellManifoldGroup de la reference
  // @nocgmitf
  HRESULT GetReferenceCellManifoldGroups(CATLISTP(CATCellManifoldGroup) &ioReferenceCellManifoldGroups, const CATCellManifoldGroupLayer * iCMGLayer) const;

  // Renvoie les CellManifold des Edges bord de la reference s'il y en a.
  // @nocgmitf
  HRESULT GetReferenceEdgeManifolds(CATLISTP(CATCellManifold) &ioReferenceEdgeManifolds) const;


  // @nocgmitf
  CATLiveBody* CreateReferenceLiveBody() const;


  // @nocgmitf
  void GetReferenceTransformation(CATMathTransformation & oResultTansfo, CATBoolean iEditionContext = TRUE) const;


  



  //-------------------------------------------------
  //     Methodes traitants des Cell Manifolds  
  //-------------------------------------------------


  // Renvoie les CellManifolds qui ont la meme CellManifold de reference que iCellManifold
  // (used by appli)
  // @nocgmitf
  //----------------------------------------------------------------------------------------
  virtual HRESULT GetSisterCellManifolds(CATCellManifold * iCellManifold, ListPOfCATCellManifold & oSisterCellManifolds);

  // Renvoie les CellManifolds / Cell de l'instance iInstance (commence a 0)
  // (used by appli)
  //-------------------------------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetInstanceCellManifolds(int iInstance, CATLISTP(CATCellManifold) &oInstanceCellManifolds);
  // @nocgmitf
  virtual HRESULT GetInstanceCells(int iInstance, CATLISTP(CATCell) &oCells);
  // @nocgmitf
  HRESULT GetInstanceCells(int iInstance, CATLISTP(CATCell) &oCells, int iDim);
  // @nocgmitf
  virtual HRESULT GetAllInstanceCells(int iInstance, CATLISTP(CATCell) & oCellList); // une ancienne methode, a supprimer si non utilisee.

  // Renvoie toutes les CellManifolds / Cell du pattern
  // (used by appli)
  //----------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold) & oCellManifolds) const;
  // @nocgmitf
  virtual HRESULT GetAllCells(CATLISTP(CATCell) & oCellList);

  // Renvoie  CellManifolds / Cell bord
  //----------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetBorderCellManifolds(CATLISTP(CATCellManifold) & oCellManifolds);
  // @nocgmitf
  virtual HRESULT GetBorderEdges(CATLISTP(CATCell) & oCellList);

  // Test si la CellManifold / Cell appartient au pattern, et renvoie son instance 
  // ( -1 pour une CM/Cell qui est partagee entre plusieurs instances, 0 ... NbInstance - 1 si appartient a une instance)
  // (used by appli)
  // @nocgmitf
  //-----------------------------------------------------------------------------------------------------------------------
  virtual CATBoolean BelongsToPattern(CATCellManifold * iCM, short & oInstance);
  // @nocgmitf
  virtual CATBoolean BelongsToPattern(CATCell * iCell, short & oInstance);
  // @nocgmitf
  CATBoolean BelongsToPattern(CATCell * iCell, short & oInstance,  CATBoolean iCollisionAllowed);


   /*
   * -1 <= iRefCM < GetNumberOfReferenceCellManifolds()
   * -1 <= iInstance < GetNumberOfInstances() :
   *    -  Si iInstance == -1, ioImageCellManifolds contient eventuellement une liste de CellManifold equivalentes a iorefCellManifold, globalement invariantes par la transfo unitaire du pattern,
   *                          en collision qui correspondent donc a plusieurs instances
   *    -  Si 0 <= iInstance < GetNumberOfInstances(), ioImageCellManifolds contient eventuellement une liste de CellManifold equivalentes a iorefCellManifold dans l'instance iInstance
   */
  // @nocgmitf
  HRESULT GetReferenceCellManifoldImages(short                       iRefCM, 
                                         short                       iInstance, 
                                         CATCellManifold*          & iorefCellManifold, 
                                         CATLISTP(CATCellManifold) & ioImageCellManifolds);

  // @nocgmitf
  HRESULT GetReferenceCellManifold(CATCellManifold* &iImageCellManifold, CATCellManifold* &oRefCellManifold) const;

  // Retourne toutes les instances de iRefCellManifold
  // @nocgmitf
  HRESULT GetReferenceCellManifoldImages(CATCellManifold *           iRefCellManifold, 
                                         CATLISTP(CATCellManifold) & oImageCellManifolds, 
                                         CATListOfInt              & oTypes);

  // @nocgmitf
  HRESULT GetReferenceCellManifoldImages(CATCellManifold *        iReferenceCellManifold, 
                                         short                    iInstanceNumber, 
                                         ListPOfCATCellManifold & oReferenceCellManifoldImages);

  // @nocgmitf
  HRESULT GetReferenceCellManifoldGroupImages(CATCellManifoldGroup *         iRefCellManifoldGroup,
                                              CATLISTP(CATCellManifoldGroup) & oImageCellManifolds);

  // Renvoie toutes les faces du body adjacentes aux faces pattern.
  // @nocgmitf
  HRESULT GetNeighbourFaces(CATCellHashTable *& oCellHT);

  // @nocgmitf
  static HRESULT GetInstanceReferenceAndAttributs(CATCellManifoldGroup * iInstanceGroup, CATCellManifoldHashTableWithAttributeAssoc *& ioRefCMWithAssocAttr);

  // @nocgmitf
  HRESULT GetCollisionCM(CATLISTP(CATCellManifold) &ioCollisionCM);

  // @nocgmitf
  HRESULT GetRefGroup(CATCellManifold * iCM, CATCellManifoldGroup *& oRefGroup);

  //-------------------------------------------------
  //     Methods for DeclarativeManifolds
  //-------------------------------------------------


  // Renvoie les CellManifolds qui ont la meme CellManifold de reference que iCellManifold
  // (used by appli)
  // @nocgmitf
  //----------------------------------------------------------------------------------------
  virtual HRESULT GetSisterDeclarativeManifolds(CATDeclarativeManifold * iDM, ListPOfCATDeclarativeManifold & oSisterDM);

  // Retourne toutes les instances de iRefCellManifold
  // @nocgmitf
  HRESULT GetReferenceDeclarativeManifoldImages(CATDeclarativeManifold               *    iRefDM, 
                                                ListPOfCATDeclarativeManifold &    oImageDM);

  //-------------------------------------------------
  //     Methods for DeclarativeManifoldGroups
  //-------------------------------------------------

  HRESULT GetCollisionCMGroups(CATLISTP(CATCellManifoldGroup) &ioCollisionCMGroups);

  

  //-------------------------------------------------
  //     Methodes traitant des Instances   
  //-------------------------------------------------


  // Renovie le nombre d'instances 
  // (used by appli)
  // @nocgmitf
  //-------------------------------
  virtual HRESULT GetNumberOfInstances(short &oNbInstances) const;

  // Return the transformation from reference to the instance InstanceTransfo.
  // iInstance == 0 for the first instance.
  // (used by appli)
  // @nocgmitf
  //--------------------------------------------------------------------------------
  virtual HRESULT GetInstanceTransformation(short iInstance, CATMathTransformation &oInstanceTransfo) const;

  // Renvoie la transformation qui permettrait de passer de la reference si on changeait la transfo unitaire par iTransfoToTest .
  // Necessaire dans le cas pattern de pattern.
  // (used by appli)
  // @nocgmitf
  //--------------------------------------------------------------------------------------------------------------------------------
  virtual HRESULT ComputeInstanceTransformationWithChangedUnitaryTransfo(short iInstance, CATMathTransformation &iUnitaryTransfo, CATMathTransformation &oInstanceTransfo) const;

  // Renvoie la transformation secondaire qui decale une instance par rapport a la position qu'elle devrait avoir normalement.
  // (used by appli)
  // @nocgmitf
  //--------------------------------------------------------------------------------------------------------------------------
  virtual HRESULT GetSecondaryTransformation(short iInstance, CATMathTransformation &oInstanceTransfo) const;

  // Renvoie la liste des numeros d'instances actives
  // (used by appli)
  // @nocgmitf
  //---------------------------------------------------
  virtual HRESULT GetActiveInstances(CATListOfShort &oActiveInstances) const;
  HRESULT GetActiveInstances_EditionMode(CATListOfShort &oActiveInstances, CATBoolean EditionMode = TRUE) const;

  // Renvoie les instances inactivees et le type de desactivation associe ( User, System, ... )
  // (used by appli)
  //---------------------------------------------------------------------------------------------
  virtual HRESULT GetActivationStatus(CATListOfShort & InactivatedInstances, CATListOfShort & InactivationTypes);
  HRESULT GetActivationStatusWithoutParameters(CATListOfShort & InactivatedInstances, CATListOfShort & InactivationTypes);


  // Renvoie le status d'activation de l'instance
  // (used by appli)
  // @nocgmitf
  //------------------------------------------------
  HRESULT GetActivationStatus(int iInstance, CATPatternActivationStatus & oActivationStatus);

  // Renvoie la transformation qui va deplacer l'instance.
  // @nocgmitf
  //------------------------------------------------
  HRESULT GetEditionTransformation(int iInstance, CATMathTransformation & oTransformation,CATBoolean iHaveToRecomputeAnyway=FALSE);

  // @nocgmitf
  HRESULT GetInstanceOBBCloud(int iInstance, CATMathOBBCloud &oInstanceOBBCloud) const;
   // @nocgmitf
  HRESULT GetInstancesToReconstruct(CATListOfShort &oActiveInstances) const;
  // @nocgmitf
  HRESULT GetAutomaticallyDesactivatedInstances(CATListOfShort &oAutoInactiveInstances) const;
  // @nocgmitf
  HRESULT GetSecondaryTransfoData(CATListOfShort & oInstanceWithSecondaryTransformations, CATLISTP(CATMathTransformation) & oSecondaryTransformations);
   // @nocgmitf
  HRESULT GetEditedSecondaryTransfoData(CATListOfShort & oInstanceWithEditedSecondaryTransformations, CATLISTP(CATMathTransformation) & oEditedSecondaryTransformations);
  // Renvoie la transfo qui va de iInstance1 a iInstance2.
  HRESULT GetTransformation(short iInstance1, short iInstance2, CATMathTransformation &oTransfo) const;
  // @nocgmitf
  HRESULT CheckActivationStatus(CATListOfShort & oInactivatedInstancesSeenAsActivated, CATListOfShort & oActivatedInstancesSeenAsInactivated);
  // @nocgmitf
  HRESULT GetInstanceGroup(int iInstance, CATCellManifoldGroup *& oInstanceGroup);
  // @nocgmitf
  CATBoolean IsComplete(int iInstance);
  // @nocgmitf
  CATBoolean IsActive(int iInstance);

  // Check if the CM in the list have common edges with the instances
  // @nocgmitf
  HRESULT TouchInstances(CATLISTP(CATCellManifold) & iCMList, CATListOfShort & oTouchedInstances);


  //-------------------------------------------------
  //    Methodes pour pattern lineaire   
  //-------------------------------------------------
  
  // Renvoie le vecteur de la l'unitary transformation
  // (used by appli)
  // @nocgmitf
  //-----------------------------------------------------
  virtual HRESULT GetTranslationVector(CATMathVector &ioTranslationVector) const;


  INLINE CATlsoDataCache * GetDataCache();


  //-------------------------------------------------
  //    Methodes pour pattern circulaire   
  //-------------------------------------------------

  // Renvoie le vecteur de la l'unitary transformation
  // (used by appli)
  // @nocgmitf
  //-----------------------------------------------------
  virtual HRESULT GetRotationData(CATMathLine &ioRotationAxis, double &ioRotationAngle) const;

  // Test si le pattern est complet (les instances sont equireparties autour de l'axe de rotation)
  // (used by appli)
  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
  virtual CATBoolean IsPatternComplete();

  CATBoolean GetExtendMode();

  CATPatternBuildingType GetPatternBuildingType();

  CATGeoFactory * GetFactory();

  CATSoftwareConfiguration * GetSoftwareConfiguration();

  // @nocgmitf
  void GetPatternReferenceManifoldAttributes(ListPOfCATPatternReferenceManifoldAttribute & oReferenceManifoldAttributeList);


  virtual CATCellManifoldPatternNavigator2 * IsCATCellManifoldPatternNavigator2();


  void CleanDataForMultiRun();

  //-------------------------------------------------
  //   Stream / Unstream 
  //-------------------------------------------------

  
  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
   void Stream(CATCGMStream& ioStr,CATICGMContainer * iFactory) const;
   void UnStream(CATCGMStream& ioStr,CATICGMContainer * iFactory);

  

protected:

  // Used by Application
//  HRESULT GetAllInstanceCells(int iInstance, CATLISTP(CATCell) & oCellList);

  void Init(const CATTopData* iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup, CATDRepNavigator * iDRepNavigator);
  void EndInit();
  void GetReferenceCellManifolds();
  

  enum GroupType
  {
    CATGroupTypeNetwork,
    CATGroupTypeInstance,
    CATGroupTypeReference
  };
  CATBoolean IsType(CATCellManifoldGroup * iGroup, GroupType iType) const;
  CATBoolean IsType(CATCellManifoldGroup * iGroup, GroupType iType, CATManifoldAttribute *& oAttribute) const;

  void GetCollisionCM(CATCellManifoldGroup * iNetworkGroup, CATLISTP(CATCellManifold) &ioCollisionCM);
  void GetInstanceGroups(CATCellManifoldGroup * iNetworkGroup, CATLISTP(CATCellManifoldGroup) &ioInstanceGroups);
  CATPatternManifoldSpecificationAttribute ** GetPatternSpecReferences(int & oNumberOfLevels) const;
  HRESULT GetSubLevelNavigator(int iInstance, CATCellManifoldPatternAdvancedNavigator *& oNavigator) const; 

  // Renvoie la transformation qui permet de passer de la reference a l'instance,
  // sans tenir compte de l'edition en cours.
  // @nocgmitf
  //--------------------------------------------------------------------------------
  virtual HRESULT GetInstanceTransformationWithoutEdition(short iInstance, CATMathTransformation &oInstanceTransfo) const;

  virtual HRESULT GetInstanceTransformation(short iInstanceNumber, CATMathTransformation &oTransfoFromReference, CATBoolean iEditionContext) const;

  virtual HRESULT GetSecondaryTransformation(short iInstance, CATMathTransformation &oInstanceTransfo, CATBoolean iEditionContext) const;

  virtual HRESULT GetActivationStatus(CATListOfShort & InactivatedInstances, CATListOfShort & InactivationTypes, CATBoolean iEditionContext);

  CATBoolean TransfoGivenByVariational() const;

  CATBoolean IsTransfoEdition(CATBoolean iHaveToRecomputeAnyway=FALSE);


protected:
  //VB7 TopData_Nav
  //CATTopData _TopData;
  CATLiveBody* _LiveBody;
  CATCellManifoldGroup* _NetworkGroup;
  CATPatternManifoldSpecificationAttribute* _PatternSpec;
  CATLISTP(CATCellManifold) *_RefCM;
  //short _NbInstances;

  int _IsInCollision;//-1 == not defined; 0 == FALSE; 1 == TRUE

  // Prise en compte de VariationalPatternParameters
  CATMathTransformation *         _VarUnitaryTransfo;
  CATMathTransformation *         _VarRefTransfo;
  CATListOfShort                  _VarSecondaryTransfoInstances;
  CATLISTP(CATMathTransformation) _VarSecondaryTransformations;
  CATLiveBody *                   _VarNewRefBody;

  CATBoolean _EditionMode;

  
  // Pour advanced : 
protected:
  CATCellManifoldPatternNavigator(const CATTopData &iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup, int iInstanceNumber); 
  HRESULT ComputeInactivatedInstances(CATListOfShort &oInactiveInstances) const;
  CATCellManifoldGroup * NextInstance(CATCellManifoldGroup * iPatternGroup = NULL) const;
  HRESULT GetSubLevelNavigators(ListPOfCATCellManifoldPatternAdvancedNavigator & oNavigators) const; 
  int GetPatternNumber(CATCellManifoldGroup * iPatternGroup) const;
  HRESULT GetAllInstances(ListPOfCATCellManifoldGroup & oInstances, CATListOfShort & oInstanceNumbers) const;
  int GetLevel() const;
  int GetInstanceNumber() const;
  HRESULT GetTotalNumberOfInstances(short &oNbInstances) const;
  //short GetSubLevelNumberOfInstances() const;
  short GetSubLevelTotalNumberOfInstances() const;

  int _InstanceNumber; // Numero de la superInstance qui contient le networkgroup de ce navigateur.

  CATDRepNavigator * _DRepNavigator;

  CATInstancesNavigator * _InstancesNavigator;
  
  CATlsoDataCache       * _lsoDataCache;
};

// --------------------------------------
// CATCreateCellManifoldPatternNavigator
// --------------------------------------
// @nocgmitf
ExportedByPersistentCell CATCellManifoldPatternNavigator * CATCreateCellManifoldPatternNavigator(const CATTopData     & iData,
                                                                                                 CATLiveBody          * iLiveBody,
                                                                                                 CATCellManifoldGroup * iNetworkGroup); 

INLINE CATlsoDataCache * CATCellManifoldPatternNavigator::GetDataCache() {
  return _lsoDataCache;
}

#endif
