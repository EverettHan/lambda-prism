#ifndef CATPersistentShell_H
#define CATPersistentShell_H
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
#include "CATOwnedByPersistentCellFactory.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"

#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATPersistentFaces.h"
#include "CATListOfInt.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"

class CATAutoBaseColor;
class CATPersistentFace;
class CATPersistentBody;

class ExportedByPersistentCell CATPersistentShell : public CATOwnedByPersistentCellFactory
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentShell)

  CATPersistentShell(CATPersistentCellFactory &iFactory);
  virtual ~CATPersistentShell();

  void AddPersistentFace(CATPersistentFace *iPersistentFace, int iOrientation);
  void AddPersistentFacesFromList(const ListPOfCATPersistentFaces &iPersistentFace, const CATListOfInt &iOrientations);

  CATBoolean Owns(CATPersistentFace * iPersistentFace);
  // returns first persistent face - NULL if shell is empty
  CATPersistentCell *ReadFirstPersistentFace();

  void GetPersistentFaces(ListPOfCATPersistentCells &oPersistentCells, CATListOfInt *oOrientations = 0);
  void GetPersistentFaces(ListPOfCATPersistentFaces &oPersistentFaces, CATListOfInt *oOrientations = 0);

  void GetEdges(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iPersistentBody, ListPOfCATEdge &oEdges);
  void GetVertices(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iPersistentBody, ListPOfCATVertex &oVertices);
  void Dump(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iPersistentBody, CATCGMOutput &iOutput);

  void SetColor(CATAutoBaseColor &iColor);

  CATBoolean IsInside(CATPersistentCell *iCell);

private:
  ListPOfCATPersistentCells _PersistentCells;
  CATListOfInt _Orientations;
};

#endif
