#ifndef CATDeclarativeManifoldCarrierBase_H
#define CATDeclarativeManifoldCarrierBase_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATHGeometry.h"
#include "CATCollec.h"
#include "CATMathInline.h"
#include "CATDrawerCollector.h"
#include "CATHashTableWithIntAssoc.h"

class CATCellManifoldsManager;
class CATBody;
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATCell;
class CATLISTP(CATCell);
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMHashTableWithAssoc;


class ExportedByPersistentCell CATDeclarativeManifoldCarrierBase : public CATDeclarativeManifoldAgent
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDeclarativeManifoldCarrierBase();
	
  // Destructor
	virtual ~CATDeclarativeManifoldCarrierBase();

  INLINE void ForceParentSearch();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  void FilterForAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();

  void SetTypeChangeAllowedDeclarativeManifolds(ListPOfCATDeclarativeManifold &iDeclarativeManifolds);
  INLINE virtual CATBoolean IsAllowedToCarryDeclarativeManifold(CATDeclarativeManifold * iDeclarativeManifoldToCarry);

  void GetHGeometryImageListWithOrders(CATHGeometry* iHGeometry, CATLiveBody& iOutputLiveBody, ListPOfCATHGeometry & oImageHGeometryList, CATListOfInt & oOrderList);
  CATHGeometry* GetHGeometryImage(CATHGeometry* iHGeometry, CATLiveBody& iOutputLiveBody, CATLONG32 iOrder=-2);
  CATHGeometry* GetHGeometryImage(CATHGeometry* iHGeometry, CATLiveBody& iOutputLiveBody, ListPOfCATCellManifold & iBoneImageCMList);
  void GetCellManifoldImageThroughOrderType(CATCellManifold* iMother, ListPOfCATCellManifold &ioChildren);
  void GetCellManifoldImageThroughOrderType(const ListPOfCATCellManifold &iMothers, ListPOfCATCellManifold &ioChildren);

  //get created CM if only creation order.
  void GetCreatedCellManifoldList(CATCellManifold* iMother, ListPOfCATCellManifold &ioChildren);

  CATLiveBody* GetInputBodyFromDM(const CATDeclarativeManifold* iDM);

private:
  void PropagateDeclarativeManifoldsToCarry(CATLISTP(CATDeclarativeManifold) &ioDeclarativeManifoldsToCarry, CATLISTP(CATCellManifold) &ioImageCellManifolds);
  CATBoolean DoesFaceAnalyzerAgreeWithType(CATFace *iFaceToAnalyse,ListPOfCATCellManifold oTypedFaceAnalyserContext[2]);

protected:
  void CreateHGeometryImages(CATLiveBody& iInputLiveBody, CATLiveBody& iOutputLiveBody, CATCGMJournalList* oJournal=NULL);

  void CreateImageDeclarativeManifoldsFromManifoldImage(CATLISTP(CATDeclarativeManifold) &iParentDeclarativeManifolds,
    CATLISTP(CATCellManifold) &iImageCellManifolds);

  void TransferDeclarativeReference(CATLISTP(CATDeclarativeManifold) &iParentDeclarativeManifolds,
                                    CATLISTP(CATCellManifold)        &iImageCellManifolds);

  void UpdateDeclarativeManifolds();
  void UpdateDeclarativeManifolds_OLDMETHOD();

private:
  ListPOfCATDeclarativeManifold _TypeChangeAllowedDeclarativeManifolds;
  ListPOfCATDeclarativeManifold _CreatedDM;
  CATBoolean _ForceParentSearch;
  ListPOfCATHGeometry _HGeometries[2];
  CATDrawerCollector _HGeometriesHT; //instead of previous data (_HGeometries) - VB7 03072014
  CATHashTableWithIntAssoc _HGeometriesOrderHT;

  // ListPOfCATManifold       _PublishManifoldList; // Naming
};

INLINE void CATDeclarativeManifoldCarrierBase::ForceParentSearch()
{
  _ForceParentSearch = TRUE;
}

INLINE CATBoolean CATDeclarativeManifoldCarrierBase::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return FALSE;
}
INLINE CATBoolean CATDeclarativeManifoldCarrierBase::IsAllowedToCarryDeclarativeManifold(CATDeclarativeManifold * iDeclarativeManifoldToCarry)
{
  return !_TypeChangeAllowedDeclarativeManifolds.Locate(iDeclarativeManifoldToCarry);
}
#endif
