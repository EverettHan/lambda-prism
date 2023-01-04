#ifndef CATDraftManifold_h
#define CATDraftManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2016
#include "CATContextualManifold.h"
//#include "CATTopDefine.h"
//#include "CATMathDef.h"
//#include "CATMathConstant.h"
#include "CATIsoParameter.h"
#include "CATListOfShort.h"


#include "YI00IMPL.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATDraftManifold ;
#else
extern "C" const IID IID_CATDraftManifold ;
#endif

enum CATLiveTypeDraft
{
CATLiveTypeDraftNeutral,
CATLiveTypeDraftReflect, //not supported yet
CATLiveTypeDraftNeutralFitted, //not supported yet
CATLiveTypeDraftReflectFitted //not supported yet
};

enum CATLiveDraftGeomMode
{
CATLiveDraftGeomCone, //default
CATLiveDraftGeomSquare
};

enum CATLiveDraftPullDirBehavior
{
CATLiveDraftPullDirMoveWithNeutral, //default
CATLiveDraftPullDirFixed
};

//first context is neutral
class ExportedByYI00IMPL CATDraftManifold : public CATContextualManifold
{
  CATDeclareInterface;

public:

  virtual CATLiveTypeDraft GetDraftType() const = 0;
  virtual CATLONG32 GetNbDirections() = 0;
  virtual CATLiveDraftGeomMode GetDraftMode() const = 0;
  virtual CATLiveDraftPullDirBehavior GetPullingDirectionBehavior() const = 0;
  
  //virtual void DumpComparison(CATCGMOutput& os, CATDraftManifold & iOtherDraftManifold, double iAngleTol) = 0;
  virtual void DumpFaces(CATCGMOutput& os) = 0;  

  //for single direction and angle
  virtual void Set(const ListPOfCATCellManifold &iRepresentation,
                   const ListPOfCATCellManifold &iNeutral, 
                   const ListPOfCATCellManifold &iUnaffectedFacesToDraft, //can be empty
                   CATLiveTypeDraft   iType,
                   CATLiveDraftGeomMode iMode,
                   const CATMathDirection  &iPullingDir,
                   CATAngle iAngle,
                   CATLiveDraftPullDirBehavior iPullDirBehavior = CATLiveDraftPullDirMoveWithNeutral) = 0; // Deprecated

  virtual void AddUnAffectedFacesToDraft(ListPOfCATCellManifold &iUnaffectedFacesToDraft) = 0;
  virtual void SetNeutral(ListPOfCATCellManifold &iNeutral) = 0; 

  virtual CATBoolean GetAngle(CATAngle &oAngle) const = 0 ;
  virtual CATBoolean GetPullingDirection(CATMathDirection &oDir) const = 0;
  virtual CATBoolean GetRemoveDraftAngle(CATAngle &oAngle) const = 0;//DSH1
  virtual CATBoolean GetRemoveDraftPullingDirection(CATMathDirection &oDir) const = 0;//DSH1
  virtual CATBoolean GetNeutral(ListPOfCATCellManifold &oNeutral) const = 0; 
  virtual CATBoolean GetUnAffectedFacesToDraft(ListPOfCATCellManifold &oUnaffectedFacesToDraft) const = 0 ;
  //for multiple directions on same side, same side of parting

  //for both sides of parting
  
};
  
CATDeclareHandler(CATDraftManifold,CATContextualManifold);

#endif
