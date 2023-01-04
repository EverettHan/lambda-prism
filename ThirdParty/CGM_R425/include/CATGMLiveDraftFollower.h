#ifndef CATGMLiveDraftFollower_H
#define CATGMLiveDraftFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "CATGMLiveContextualFeatureFollower.h"
#include "CATDraftManifold.h"
#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATPersistentEdges.h"

class CATDraftManifold;
class CATPersistentBody;
class CATBody;
class CATPersistentCellInfra;
class CATPersistentCells;

class CATCGMStream;
class CATGeoFactory;
class CATFace;

class ExportedByPersistentCell CATGMLiveDraftFollower : public CATGMLiveContextualFeatureFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveDraftFollower(CATDraftManifold               &iBoneToFollow, 
                         CATPersistentBody              &iDraftedBody,
                         CATPersistentCellInfra         &iInfra,
                         ListPOfCATPersistentFaces      &iFacesToDraft,
                         ListPOfCATPersistentFaces      &iFacesNeutral,
                         CATPersistentBody              &iBodyWithoutDraft);

   CATGMLiveDraftFollower(CATDraftManifold              &iBoneToFollow, 
                         CATPersistentBody              &iDraftedBody,
                         CATPersistentCellInfra         &iInfra,
                         ListPOfCATPersistentFaces      &iFacesToDraft,
                         ListPOfCATPersistentEdges      &iEdgesNeutral,
                         CATPersistentBody              &iBodyWithoutDraft);
  
  //used in removeDraft
  CATGMLiveDraftFollower(CATDraftManifold               &iBoneToFollow, 
                         CATPersistentBody              &iDraftedBody,
                         CATPersistentCellInfra         &iInfra);

 //FOR UNSTREAL ONLY
  CATGMLiveDraftFollower(CATPersistentCellInfra         &iInfra);

  // Destructor
  ~CATGMLiveDraftFollower();

  //
  virtual HRESULT Merge(CATGMLiveContextualFeatureFollower& iFollower);

  CATContextualManifold & GetContextualManifold() const;
  CATDraftManifold & GetDraftManifold() const;
  virtual CATGMLiveDraftFollower*    GetAsDraftFollower();
  void GetFacesToDraft(ListPOfCATPersistentFaces &oFacesToDraft) const;
  void GetFacesNeutral(ListPOfCATPersistentFaces &oFacesNeutral) const;
  void GetEdgesNeutral(ListPOfCATPersistentEdges &oEdgesNeutral) const;

  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
  void GetDeclarativeManifoldsInInputBody(ListPOfCATDeclarativeManifold &iInputDeclarativeManifolds) const;

private:
  CATDraftManifold    *_BoneToFollow;
  ListPOfCATPersistentFaces _FacesToDraft;
  ListPOfCATPersistentFaces _FacesNeutral; //neutral faces
  ListPOfCATPersistentEdges _EdgesNeutral; //free border edges (of faces to draft) 
};

#endif

