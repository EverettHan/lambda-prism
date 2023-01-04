#ifndef CATlsoUpToDatePannier_H
#define CATlsoUpToDatePannier_H

#include "CATCGMNewArray.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATCellManifold.h"


// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATlsoUpToDatePannier
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATlsoUpToDatePannier();
  virtual ~CATlsoUpToDatePannier();

public :

  void AppendUpToDateCellManifoldList(ListPOfCATCellManifold & iUpToDateCMList);
  void AppendNotUpToDateCellManifoldList(ListPOfCATCellManifold & iNotUpToDateCMList);
  void AppendInCollisionCellManifoldList(ListPOfCATCellManifold & iInCollisionCM);
  void AppendAlreadyTreatedCMList(ListPOfCATCellManifold & iAlreadyTreatedCMList);

  void AppendUpToDateCellManifold(CATCellManifold * iUpToDateCM);
  void AppendNotUpToDateCellManifold(CATCellManifold * iNotUpToDateCM);
  void AppendInCollisionCellManifold(CATCellManifold * iInCollisionCM);

  void GetUpToDateCMList(ListPOfCATCellManifold & oUpToDateCMList);
  void GetNotUpToDateCMList(ListPOfCATCellManifold & oNotUpToDateCMList);
  void GetCollisionCMList(ListPOfCATCellManifold & oCollisionCMList);
  void GetImpactedCMList(ListPOfCATCellManifold & oImpactedCMList);
  
  CATBoolean IsAlreadyTreatedCM(CATCellManifold * iCM);
  CATBoolean IsInCollision(CATCellManifold * iCM);

private:
  ListPOfCATCellManifold _UpToDateCellManifoldList;
  ListPOfCATCellManifold _NotUpToDateCellManifoldList;
  ListPOfCATCellManifold _InCollisionCMList;
  ListPOfCATCellManifold _AlreadyTreatedCMList;
};

#endif 

