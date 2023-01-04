#ifndef CATPersistentVertex_H
#define CATPersistentVertex_H
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
#include "ListPOfCATPersistentVertices.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATVertex.h"

class CATVertex;
class CATPersistentImplVertex;
class CATCGMOutput;

class ExportedByPersistentCell CATPersistentVertex : public CATPersistentCell
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentVertex)

  CATPersistentVertex(CATPersistentCellFactory &iFactory, CATPersistentImplCell *iImplCell);
  virtual ~CATPersistentVertex();

// cas particulier de GetRepresentationInContainer quand this ne correspond qu'a une seule CATVertex
// dans iContainer.
// renvoie le CATVertex correspondante et NULL si plusieurs CATVertex representent this
  CATVertex *GetVertexRepresentation(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer);
  void GetVertexRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, 
    CATPersistentBody *iContainer, ListPOfCATVertex &oVertices);

  static void GetListPOfPersistentVerticesRepresentation(const CATAutoBaseThreadContext      &iThreadContext, 
                                                         const ListPOfCATPersistentVertices  &iListOfPersistentVertices, 
                                                         CATPersistentBody                   &iContainer,
                                                         ListPOfCATVertex                    &oListOfCATVertices);

  virtual CATPersistentVertex *GetAsPersistentVertex();
  static void GetPersistentVertexListFromCATVertex(const CATAutoBaseThreadContext &iThreadContext,CATPersistentCellFactory *iPersistentCellFactory,
    CATVertex *iVertex, ListPOfCATPersistentVertices &oPersistentVertices,CATPersistentBody *iContainer=NULL);
  static CATPersistentVertex *GetUniquePersistentVertexFromCATVertex(CATPersistentCellFactory *iPersistentCellFactory, 
    CATCell *iVertex, CATBoolean iAnyPersistentCellIsOk);
#ifdef ALLOW_GetPersistentCellFromCATCell
  static CATPersistentVertex *GetPersistentVertexFromCATVertex(CATPersistentCellFactory *iPersistentCellFactory, CATVertex *iVertex);
#endif

  virtual int GetDimension();

  virtual void Dump(CATCGMOutput &oOutput, const CATAutoBaseThreadContext &iThreadContext);
};

#endif
