#ifndef CATFilletManifoldCreator_H
#define CATFilletManifoldCreator_H

#include "PersistentCell.h"
#include "CATFilletManifoldCreatorBase.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"

class CATCellFollower;
class CATBody;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCGMJournalList;


class ExportedByPersistentCell CATFilletManifoldCreator : public CATFilletManifoldCreatorBase 
{
public:
  CATCGMDeclareManifoldAgent(CATFilletManifoldCreator, CATFilletManifoldCreatorBase)

	// Constructor
  CATFilletManifoldCreator(double iRadius);
  CATFilletManifoldCreator();
	
  // Destructor
  virtual ~CATFilletManifoldCreator();

  virtual HRESULT CreateImageManifolds();

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();

  virtual void Stream(CATCGMStream& Str) const;  
  virtual void UnStream (CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig); 
  virtual CATRibbonManifoldCreatorInfraContextUtilities * GetUtilities();

protected:

  virtual CATBoneFillet* GetRadiusAndType(CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], CATPersistentBody& iPBody, ListPOfListPOfCATCellManifolds& iAllBoneAndJoint, double &ioRadius, CATSurfaceRecognizer::SurfaceType &oType);
  virtual CATBoneFillet* GetRadiusAndType(CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], CATLiveBody& iLiveBody, ListPOfListPOfCATCellManifolds& iAllBoneAndJoint, double &ioRadius, CATSurfaceRecognizer::SurfaceType &oType);

  // ST5 Wk32:
  virtual void RecognizeJointAndDefineType(CATLiveBody &iLiveBody,
                                           CATGMLiveRibbonSorter &iRibbonSorter,
                                           int iJointIndex,
                                           ListPOfCATCellManifold &iJointFilletRep, 
                                           ListPOfCATCellManifold &iConnectedBoneFilletList,
                                           CATListOfInt &oResultDefineType);

  virtual void RepairBoneContextsInStepFillet(CATLiveBody              * iLiveBody,
                                              CATBoneFillet            * iBoneFillet,
                                              ListPOfCATCellManifold   & iBoneFilletRep,
                                              ListPOfCATCellManifold     ioBoneFilletSupport[2]);

private :

  double _Radius;
};

#endif
