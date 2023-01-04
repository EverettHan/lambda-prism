#ifndef CATRibbonSeedsSharedSorter_H
#define CATRibbonSeedsSharedSorter_H

#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "CATCGMNewClassArray.h"

#include "CATDeclarativeManifoldAgent.h"
#include "CATRibbonManifoldCreatorBase.h"
#include "CATDRepSeedsContainer.h"
#include "CATBoolean.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATDRepSeed.h"

class CATSoftwareConfiguration;

class ExportedByPersistentCell CATRibbonSeedsSharedSorter : public CATCGMVirtual
{
public:
  CATCGMNewClassArrayDeclare; // pool allocation

  //------------------------------------------------------------
  // Public methods
  //------------------------------------------------------------
  static CATRibbonSeedsSharedSorter* CATCreateRibbonSeedsSharedSorter(CATSoftwareConfiguration *iConfig);

  // attach/detach shared sorter to an agent
  HRESULT AttachToAgent(CATDeclarativeManifoldAgent *iRibbonAgent);
  HRESULT DetachFromAgent(CATDeclarativeManifoldAgent *iRibbonAgent);

  // retrieve ribbon pieces associated to a given agent
  HRESULT GetRibbonPiecesForAgent(CATDeclarativeManifoldAgent *iRibbonAgent, ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oRecognizedDRepSeeds);

  // retrieve ribbon container associated to a given agent
  CATDRepSeedsContainer& GetDRepsSeedsContainerForAgent(CATDeclarativeManifoldAgent *iRibbonAgent);

  // lifecycle management
  void AddRef();
  void Release();

private:
  //------------------------------------------------------------
  // Enum RibbonTypeIndex
  //------------------------------------------------------------
  enum RibbonSeedsSharedSorter_RibbonType
  {
    RibbonSeedsSharedSorter_UnknownType = -1,
    RibbonSeedsSharedSorter_FilletType = 0,
    RibbonSeedsSharedSorter_ChamferType,
    RibbonSeedsSharedSorter_DraftType,
    RibbonSeedsSharedSorter_TypeSize
  };

  //------------------------------------------------------------
  // Private methods
  //------------------------------------------------------------
  CATRibbonSeedsSharedSorter(CATSoftwareConfiguration *iConfig); // constructor
  CATRibbonSeedsSharedSorter(); // default contrusctor not avaialable
  ~CATRibbonSeedsSharedSorter(); // destructor not available --> use release
  
  HRESULT SortRibbonFaces(RibbonSeedsSharedSorter_RibbonType iRibbonType, ListPOfCATFace &iFacesToRecognize);
  HRESULT SingleSortRibbonFaces(RibbonSeedsSharedSorter_RibbonType iRibbonType, ListPOfCATFace &iFacesToRecognize);

  RibbonSeedsSharedSorter_RibbonType GetAgentType(CATDeclarativeManifoldAgent *iRibbonAgent);
  CATBoolean IsRibbonTypeOK(RibbonSeedsSharedSorter_RibbonType iRibbonType);

  //------------------------------------------------------------
  // Data
  //------------------------------------------------------------
  int _RefCount;

  CATSoftwareConfiguration *_Config;

  CATRibbonManifoldCreatorBase *_RibbonAgents[RibbonSeedsSharedSorter_TypeSize];
  CATDRepSeedsContainer _RibbonContainers[RibbonSeedsSharedSorter_TypeSize];
  CATBoolean _AlreadyRun[RibbonSeedsSharedSorter_TypeSize];
};

#endif
