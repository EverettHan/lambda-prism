#ifndef CATCellNode_h
#define CATCellNode_h

#include "CATDataType.h"
#include <CATListOfCATCellNode.h>
#include  "ExportedByGeometricObjects.h"

class ExportedByGeometricObjects CATCellNode
{
public:

  enum CellType { Vertex, Edge, Face };

  CATCellNode(CATLONG32 iTag, CellType iType);
  ~CATCellNode();

  CATLONG32 GetTag();
  CellType GetType();

  void AddConstructedFrom(CATCellNode * iNode);
  void AddModifiedFrom(CATCellNode * iNode);

  CATLISTP(CATCellNode) * GetConstructedFrom();
  CATLISTP(CATCellNode) * GetModifiedFrom();
  CATLISTP(CATCellNode) * GetConstructedInto();
  CATLISTP(CATCellNode) * GetModifiedInto();

  void SetInfo(CATLONG32 iInfo);
  CATLONG32 * GetInfo();

private:

  CATLONG32 _Tag;
  CellType _Type;

  CATLONG32 * _Info;

  CATLISTP(CATCellNode) _ConstructedFrom;
  CATLISTP(CATCellNode) _ModifiedFrom;
  CATLISTP(CATCellNode) _ConstructedInto;
  CATLISTP(CATCellNode) _ModifiedInto;
};

#endif
