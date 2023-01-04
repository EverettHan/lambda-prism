#ifndef CATVoBContactCheck_h_
#define CATVoBContactCheck_h_

#include "CheckOperators.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATListPOfListPOfCATCell.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATListOfCATSurParams.h"
#include "CATSurParam.h"

enum VoBContactType
{
  EdgeContactBetweenFaceFace = 1,
  EdgeContactBetweenFaceEdge = 2,
  VertexContactBetweenFaceFace = 3,
  VertexContactBetweenFaceEdge = 4,
  VertexContactBetweenFaceVertex = 5
};


class ExportedByCheckOperators CATVoBContactCheck
{
public:

  CATVoBContactCheck();
  ~CATVoBContactCheck();

  CATBoolean IsContactCheckActive();

  void SetVoBContactCells(CATLISTP(CATCell) * iContactCells);
  CATLISTP(ListPOfCATCell) * GetVoBContactCells();

  void AddContactType(VoBContactType iContactType);
  void GetContactTypes(CATListOfInt & oContactTypes);

  void SetContactCellParam(CATCell * iContactCell, CATLISTP(CATSurParam) * iSurParams);
  CATCGMHashTableWithAssoc * GetContactCellsWithParamsHT();

  CATBoolean IsContactCellAdded(CATCell * iContactCell);


private:

  CATBoolean                    _ContactCheck;
  CATLISTP(ListPOfCATCell) *    _ContactCells;
  CATCGMHashTableWithAssoc *    _ContactCellsWithParamsHT;

  CATListOfInt                  _ContactTypes;

};



#endif

