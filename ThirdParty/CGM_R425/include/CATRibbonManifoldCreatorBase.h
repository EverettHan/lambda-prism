#ifndef CATRibbonManifoldCreatorBase_H
#define CATRibbonManifoldCreatorBase_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"

#include "CATMathInline.h"

#include "ListPOfCATDRepSeed.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "CATGMLiveShapeUtilities.h"
#include "ListPOfCATGMLiveBoneFollowers.h"
#include "CATDRepSeedsContainer.h"

class CATLISTP(CATDeclarativeManifold);
class CATGMLiveBoneFollower;
class CATRibbonSeedsSharedSorter;

class ExportedByPersistentCell CATRibbonManifoldCreatorBase : public CATDeclarativeManifoldAgent  
{

  friend class CATRibbonManifoldCreatorInfraContextUtilities;
  friend class CATRibbonSeedsSharedSorter;

public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATRibbonManifoldCreatorBase();
  // Destructor
  virtual ~CATRibbonManifoldCreatorBase();

  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual void GetAllSharedDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioSharedDM) = 0;

  CATRibbonManifoldCreatorBase * GetAsRibbonManifoldCreatorBase();

protected:
  // Face by face recognition to create seeds
  // You must : implement SortFacesImplementation and call SortFacesInterface
  HRESULT SortFacesInterface(ListPOfCATFace & iFacesToRecognize, ListPOfCATDRepSeed & oRibbonPieces);
  virtual HRESULT SortFacesImplementation(ListPOfCATFace & iFacesToRecognize, ListPOfCATDRepSeed & oRibbonPieces) = 0;

  CATDRepSeedsContainer& GetDRepSeedsContainer();

  // Advanced processes (compute ribbons etc.) + DeclarativeManifoldCreation
  virtual HRESULT CreateRibbonManifolds(CATLISTP(CATDeclarativeManifold) & ioCreatedFilletManifolds, ListPOfCATDRepSeed   & iFilletPieces) = 0;

  HRESULT CheckForBoneChamferSupport(CATLISTP(CATCellManifold) & iBoneFilletSupports, CATLISTP(CATDeclarativeManifold) & ioCreatedFilletManifolds);
  HRESULT MatchFollowerOnBone(CATLISTP(CATCellManifold) iSupports[2], CATGMLiveBoneFollower& iFollower, CATPersistentBody& iPBody);
  void FindMatchingFollowerOnBone(ListPOfCATCellManifold iBoneFilletReps, CATLISTP(CATCellManifold) iSupports[2], ListPOfCATGMLiveContextualFeatureFollowers &iCandidates, CATPersistentBody& iPBody,ListPOfCATGMLiveBoneFollowers &oMatchingFollowers);
  virtual void FindMatchingFollowerOnBoneUsingRibbonTracker(ListPOfCATCellManifold iBoneReps,ListPOfCATGMLiveBoneFollowers &ioMatchingFollowers);

private:
  //------------------------------------------------------------
  // Internal data
  //------------------------------------------------------------
  CATRibbonSeedsSharedSorter *_RibbonSeedsSharedSorter;
  CATDRepSeedsContainer _LocalDRepSeedsContainer;
};


#endif


