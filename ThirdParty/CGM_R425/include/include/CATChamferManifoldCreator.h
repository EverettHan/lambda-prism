#ifndef CATChamferManifoldCreator_H
#define CATChamferManifoldCreator_H

#include "PersistentCell.h"
#include "CATChamferManifoldCreatorBase.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATBoneChamfer.h"
#include "CATMathInline.h"

class CATCellFollower;
class CATBody;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCGMJournalList;


class ExportedByPersistentCell CATChamferManifoldCreator : public CATChamferManifoldCreatorBase 
{
public:
  CATCGMDeclareManifoldAgent(CATChamferManifoldCreator, CATChamferManifoldCreatorBase);

  // Constructor
  CATChamferManifoldCreator(CATLiveTypeChamfer iChamferType, double iLeftValue, double iRightValue);
  CATChamferManifoldCreator();
	
  // Destructor
  virtual ~CATChamferManifoldCreator();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);

  virtual HRESULT CreateImageManifolds();

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  virtual void Stream(CATCGMStream& Str) const; 
  virtual void UnStream (CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig); 

  virtual void Dump(CATCGMOutput &os);

protected:
  virtual CATBoolean GetChamferParams(CATLISTP(CATCellManifold) &iBoneChamferRep, short &oChamferType, double &oLeftValue, double &oRightValue);

private :
  CATLiveTypeChamfer _ChamferType;
  double _LeftValue;
  double _RightValue;
};

INLINE CATDeclarativeManifoldAgent* CATChamferManifoldCreator::Clone()
{
  return new CATChamferManifoldCreator(_ChamferType,_LeftValue,_RightValue);
}

#endif
