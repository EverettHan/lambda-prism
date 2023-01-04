/*
VB7 - W11 2015
*/
#ifndef CATGMLiveInputDataManager_h
#define CATGMLiveInputDataManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATEdge.h"
#include "CATBoolean.h"
#include "CATMathFP.h"
#include "ListPOfCATManifoldParameter.h"
#include "ListPOfCATManifoldBaseParameter.h"
#include "CATListOfCATSurfaces.h"
#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATPersistentBodies.h"
#include "ListPOfCATFace.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
class CATBoneFillet;
class CATlsoAgentInputDataCarrier;
class CATPersistentExtTopOperator;
class CATMathTransformation;
class CATCellManifold;
class CATGeoFactory;
class CATCGMJournalList;
class CATDeclarativeManifoldAgent;
class CATHVertex;
class CATLiveBody;
class CATDeclarativeManifold;
class CATBody;
class CATPersistentBody;
class CATCell;
class CATGMLiveInputDataFilletManager;
class CATCellManifoldGroup;
class CATGMLiveInputDataCMGManager;
class CATGMLiveInputDataCylinderManager;
class CATSoftwareConfiguration;
class CATGMLiveInputDataSphereManager;
class CATGMLiveInputDataButtonManager;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATGMLiveInputDataManager : public CATCGMVirtual
{
public:

  //constructors
  CATGMLiveInputDataManager();
  CATGMLiveInputDataManager(CATGMLiveInputDataManager * iInputDataManager);
  CATGMLiveInputDataManager(CATCellManifoldsManager * iManifoldsManager, CATDeclarativeManifold * iDeclarativeManifold, ListPOfCATCellManifold & iResultCMList);
  CATGMLiveInputDataManager(CATCellManifoldsManager * iManifoldsManager, CATCellManifoldGroup * iCellManifoldGroup, ListPOfCATCellManifold & iResultCMList);
  CATGMLiveInputDataManager(CATPersistentCellInfra  * iPersistentCellInfra, const CATlsoAgentInputDataCarrier * iAgentInputDataCarrier, CATPersistentBody * iCurrentPBody, CATDeclarativeManifold * iDeclarativeManifold, ListPOfCATEdge & iResultEdgeList);
  CATGMLiveInputDataManager(CATPersistentCellInfra  * iPersistentCellInfra, const CATlsoAgentInputDataCarrier * iAgentInputDataCarrier, CATPersistentBody * iCurrentPBody, ListPOfCATCellManifold & iCellManifoldList, ListPOfCATEdge & iResultEdgeList);

  //destructors
  virtual ~CATGMLiveInputDataManager();

  // Get a duplicatation of Tranfo. To be free after use.
  CATMathTransformation * GetTransfo(CATBoolean iContextMode = FALSE);
  // Get a pointer to the Transfo. Do not delete it !
  const CATMathTransformation * GetTransfoWithoutDuplication() const;

  // Get a pointer to the transfo
  const CATMathTransformation * GetGlobalTransfo() const;

  CATBoolean              GetIsOffset() const;

  int                     IsFromCreationOrder() const;

  CATBoolean              HasTransformation();

  CATBoolean              HasTransformationWithoutDuplication() const;

  CATBoolean              HasGlobalTransformation() const;

  virtual CATGMLiveInputDataFilletManager   * GetAsInputDataFilletManager();
  virtual CATGMLiveInputDataCMGManager      * GetAsInputDataCMGManager();
  virtual CATGMLiveInputDataCylinderManager * GetAsInputDataCylinderManager();
  virtual CATGMLiveInputDataSphereManager   * GetAsInputDataSphereManager();
  virtual CATGMLiveInputDataButtonManager   * GetAsInputDataButtonManager();

  CATBoolean HaveTheCATSurfacesChanged();
  void CreateListOfInputCATSurfaceList(CATLISTP(CATSurface) & oInputCATSurfaceList);
  void CreateListOfResultCATSurfaceList(CATLISTP(CATSurface) & oResultCATSurfaceList);
  

protected:

  const CATlsoAgentInputDataCarrier * GetAgentInputDataCarrier() const;

  CATMathTransformation       * GetTransfo(ListPOfCATCellManifold & iInputCellManifoldList) ;
  const CATMathTransformation * GetTransfoFromInput(ListPOfCATCellManifold & iInputCellManifoldList) const ;
  CATMathTransformation       * GetTransfoForDuplication(const CATMathTransformation & iTransfo, int iNumInstance) const;

  double GetOffsetValue(ListPOfCATCellManifold & iInputCellManifoldList) const;
  double GetOffsetValue() const;

  CATBoolean          HasParameters(CATLONG32 iKey) const;
  CATBoolean          HasCMGParameters(CATLONG32 iKey) const;
  void                GetParameters(CATLONG32 iKey, ListPOfCATManifoldBaseParameter & oParameterList) const;
  double              GetToleranceForRelativeTest() const;

  CATBody                  * GetInputBody() const;
  CATPersistentBody        * GetInputPersistentBody() const;
  void                       GetAllInputPersistentBody(ListPOfCATPersistentBodies & oPersistentBodyList) const;
  CATLiveBody              * GetOutputLiveBody() const;
  CATBody                  * GetOuputPBody() const;
  CATSoftwareConfiguration * GetSoftwareConfiguration() const;

  CATDeclarativeManifold      * _InputDeclarativeManifold;
  CATCellManifoldGroup        * _InputCellManifoldGroup;
  ListPOfCATCellManifold      * _InputCellManifoldList;
  ListPOfCATCellManifold        _ResultCMList;
  ListPOfCATEdge                _ResultEdgeList;
  CATPersistentBody           * _CurrentPBody;
  
private:

  void InitMembers();

  void CreateListOfCATSurfaceList(ListPOfCATCellManifold iCellManifoldList, CATLISTP(CATSurface) & oCATSurfaceList);
  void GetPersistentFacesFromFaces(ListPOfCATFace & iFaceList, ListPOfCATPersistentFaces & oPersistentFaceList) const;

  int                 GetCreationOrder();
  int                 GetTypeForOffset() const;
  CATGeoFactory     * GetFactory()       const;
  CATBoolean          GetOffsetValueFromParameter(double & oOffsetValue) const;

  CATPersistentCellInfra      * _PersistentCellInfra;
  CATCellManifoldsManager     * _ManifoldsManager;
  const CATlsoAgentInputDataCarrier * _AgentInputDataCarrier;

  int                           _CreationOrder;

};

#endif
