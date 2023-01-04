#ifndef CATChamferRecognizer_H
#define CATChamferRecognizer_H

#include "CATChamferManifoldCreatorBase.h"


#include "ListPOfCATDRepSeed.h"
#include "CATDRepSeedsContainer.h"
#include "CATMathInline.h"

class ExportedByPersistentCell CATChamferRecognizer : public CATChamferManifoldCreatorBase
{
public:

  CATCGMDeclareManifoldAgent(CATChamferRecognizer, CATChamferManifoldCreatorBase)
	
	// Constructor
  CATChamferRecognizer();
	
  // Destructor
	virtual ~CATChamferRecognizer();
  INLINE virtual CATChamferRecognizer* GetAsChamferRecognizer();
  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority();
  virtual int GetPriorityWithConfig(CATSoftwareConfiguration *iConfig);
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

protected:
  virtual CATBoolean GetChamferParams(CATLISTP(CATCellManifold) &iBoneChamferRep, short &oChamferType, double &oLeftValue, double &oRightValue);

  virtual HRESULT RecognizeChamferPieces(CATBody                        &iBody, 
                                        ListPOfCATFace                 &ioFacesToBeRecognized, 
                                        CATDRepSeedsContainer &ioChamferPiecesContainer);
};

INLINE CATChamferRecognizer* CATChamferRecognizer::GetAsChamferRecognizer()
{
  return this;
}

INLINE CATDeclarativeManifoldAgent* CATChamferRecognizer::Clone()
{
  return new CATChamferRecognizer();
}

#endif
