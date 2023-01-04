#ifndef CATPersistentEdge_H
#define CATPersistentEdge_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATPersistentCell.h"
#include "ListPOfCATPersistentEdges.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATEdge.h"

class CATEdge;
class CATPersistentImplEdge;

class ExportedByPersistentCell CATPersistentEdge : public CATPersistentCell
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentEdge);

  CATPersistentEdge(CATPersistentCellFactory &iFactory, CATPersistentImplCell *iImplCell);
  virtual ~CATPersistentEdge();

// cas particulier de GetRepresentationInContainer quand this ne correspond qu'a une seule CATEdge
// dans iContainer.
// renvoie la CATEdge correspondante et NULL si plusieurs CATEdge representent this
  CATEdge *GetEdgeRepresentation(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer, int *oOrientation);
  void GetEdgeRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer, 
                                        ListPOfCATEdge &oEdges, CATListOfInt *oOrientations);
  static void GetListPOfPersistentEdgesRepresentation(const CATAutoBaseThreadContext &iThreadContext, 
                                                      const ListPOfCATPersistentEdges      &iListOfPersistentEdges, 
                                                      CATPersistentBody              &iContainer,
                                                      ListPOfCATEdge                 &oListOfCATEdges,
                                                      CATListOfInt                   *oListOfOrientation=NULL);

  virtual CATPersistentEdge *GetAsPersistentEdge();

  static void GetPersistentEdgeListFromCATEdge(CATPersistentCellFactory *iPersistentCellFactory, 
    CATEdge *iEdge, ListPOfCATPersistentEdges &oPersistentEdges);
  static CATPersistentEdge *GetUniquePersistentEdgeFromCATEdge(CATPersistentCellFactory *iPersistentCellFactory,
    CATCell *iEdge, CATBoolean iAnyPersistentCellIsOk);
#ifdef ALLOW_GetPersistentCellFromCATCell
  static CATPersistentEdge *GetPersistentEdgeFromCATEdge(CATPersistentCellFactory *iPersistentCellFactory, CATEdge *iEdge);
#endif

  virtual int GetDimension();
};

#endif
