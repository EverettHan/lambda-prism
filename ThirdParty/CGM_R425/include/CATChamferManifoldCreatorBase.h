#ifndef CATChamferManifoldCreatorBase_H
#define CATChamferManifoldCreatorBase_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATRibbonManifoldCreatorBase.h" // ajout zus
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATListPV.h"

#include "ListPOfCATDRepSeed.h"
#include "CATDRepSeedsContainer.h"

class CATCellFollower;
class CATBody;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATCellManifold;
class CATLISTP(CATCellManifold);

//------------------------------------------------------------------------------------------
class BoneChamferCMData
{
  public:
    BoneChamferCMData() {_LeftChamfer = NULL; _RightChamfer = NULL; _UniContext = FALSE; _Ctx1Used = FALSE; _Ctx2Used = FALSE ;_Size = -1; _HasLogical = FALSE;}

    CATLISTP(CATCellManifold) _Rep, _Context1, _Context2;
    BoneChamferCMData* _LeftChamfer;
    BoneChamferCMData* _RightChamfer;
    CATBoolean _UniContext, _Ctx1Used, _Ctx2Used;
    double _Size;
    CATBoolean _HasLogical;

    ~BoneChamferCMData() 
    {
      _Rep.RemoveAll();
      _Context1.RemoveAll();
      _Context2.RemoveAll();
      _LeftChamfer = NULL;
      _RightChamfer = NULL;
    }

    static void Group(BoneChamferCMData* iRandomStart, BoneChamferCMData* iEnd , CATRawCollPV &ioGroup,BoneChamferCMData* & oStart);
}; 
//------------------------------------------------------------------------------------------

class ExportedByPersistentCell CATChamferManifoldCreatorBase : public CATRibbonManifoldCreatorBase 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATChamferManifoldCreatorBase();
	
  // Destructor
  virtual ~CATChamferManifoldCreatorBase();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
 
  virtual void Dump(CATCGMOutput &os);
  virtual void GetAllSharedDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioSharedDM);


protected:
   HRESULT SortFacesImplementation(ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oRibbonPieces/*&oFilletRibbonPieces*/);

  virtual HRESULT RecognizeChamferPieces(CATBody                        &iBody, 
                                        ListPOfCATFace                 &ioFacesToBeRecognized, 
                                        CATDRepSeedsContainer &ioChamferPiecesContainer);


  virtual HRESULT CreateRibbonManifolds(CATLISTP(CATDeclarativeManifold) &ioCreatedFilletManifolds,
                                ListPOfCATDRepSeed      &iChamferPieces);

  virtual CATBoolean GetChamferParams(CATLISTP(CATCellManifold) &iBoneChamferRep, short &oChamferType, double &oLeftValue, double &oRightValue) = 0;
  
protected:

  virtual HRESULT CreateBoneChamfer(BoneChamferCMData& iData, CATLISTP(CATDeclarativeManifold) &ioCreatedChamferManifolds);

  //CATDRepSeedsContainer _ChamferPiecesContainer;

  ListPOfCATFace _FacesToBeRecognized; // DSH1 May 2017 : Faces to be recognized

private:

  HRESULT CreateBoneChamferBasedOnDependency(BoneChamferCMData* iBoneChamferCMDatas
                                            ,int iNumberOfBones
                                            ,CATLISTP(CATDeclarativeManifold) &ioCreatedChamferManifolds);

  /*HRESULT CheckForBoneChamferSupport(CATLISTP(CATCellManifold)& iBoneFilletSupports, 
                                    const short&  iChamferType,
                                    const double& iLeftValue,
                                    const double& iRightValue,
                                     CATLISTP(CATDeclarativeManifold)& ioCreatedFilletManifolds);*/


  void ProcessApproxD1D2Chamfer(CATLISTP(CATDeclarativeManifold)& ioCreatedChamferManifolds);

};

#endif
