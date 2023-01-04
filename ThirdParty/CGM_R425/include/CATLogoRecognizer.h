#ifndef CATLogoRecognizer_H
#define CATLogoRecognizer_H

#include "CATLogoManifoldCreatorBase.h"

#include "CATDRepSeedsContainer.h"
#include "CATBoolean.h"

class CATLISTP(CATCell);
class CATLISTP(CATCellManifold);
class CATDeclarativeManifoldAgent;
class CATBody;
class CATLISTP(CATFace);
class CATDRepSeedsContainer;

class ExportedByPersistentCell CATLogoRecognizer : public CATLogoManifoldCreatorBase
{
public:
  CATCGMDeclareManifoldAgent(CATLogoRecognizer, CATLogoManifoldCreatorBase)
	
	// Constructor
  CATLogoRecognizer();
	
  // Destructor
	virtual ~CATLogoRecognizer();

  INLINE virtual CATLogoRecognizer * GetAsLogoRecognizer();

  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority();
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

protected:
  virtual HRESULT RecognizeLogoCandidates(
    ListPOfCATFace                 & iFacesToRecognize);
};

INLINE CATLogoRecognizer * CATLogoRecognizer::GetAsLogoRecognizer()
{
  return this;
}
INLINE CATDeclarativeManifoldAgent* CATLogoRecognizer::Clone()
{
  return new CATLogoRecognizer();
}
INLINE CATBoolean CATLogoRecognizer::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return TRUE;
}


#endif
