#ifndef CATTopOpEnvironment_h
#define CATTopOpEnvironment_h

#include "CATBoolean.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATDataType.h"

class CATOneComputedElement;
class CATCell;
class CATSubdOccurence;
class CATSubdArrayOccurenceP;
class CATSubdInitialisation;

class ExportedByCATTopologicalObjects CATTopOpEnvironment 
{
public :
  CATTopOpEnvironment (CATLONG32 iMaxCell);
  ~CATTopOpEnvironment ();
  CATBoolean IsInserted(CATCell * iCell1, CATCell * iCell2);
  void Append (CATCell * iCell1,CATCell * iCell2);
  void StoreSolutions(const CATSubdArrayOccurenceP * iSupports,CATSubdArrayOccurenceP* Results, CATLONG32 iAlready=1);
  CATBoolean HasSolutions (const CATSubdArrayOccurenceP * iSupports, CATSubdArrayOccurenceP* oResults, CATLONG32 & oAlready);
  void SetDeletedSolution(CATSubdOccurence * iSolution);
  CATLONG32 DeletedSolutionsAuthorised(CATLONG32 iAuthorised);
  void SetSolutions(CATSubdArrayOccurenceP * SetofSolutions, CATLONG32 iToSet);
  void SetInitialisation(CATSubdInitialisation * iInits, CATLONG32 iToSet);
private :
  int SearchSolutions(CATSubdArrayOccurenceP * SetOfSolutions);
  void RemoveSolutions(int IsPresent);
  void AddSolutions(CATSubdArrayOccurenceP * SetOfSolutions);
  int SearchInitialisation(CATSubdInitialisation * iInit);
  void RemoveInitialisation(int IsPresent);
  void AddInitialisation(CATSubdInitialisation * iInit);
  void FromOccurenceToSortCell (const CATSubdArrayOccurenceP * iSupports, CATCell **& iSortTabCell);
  CATBoolean OperationComputed (const CATSubdArrayOccurenceP * iSupports, CATOneComputedElement *& oOperation);

  CATTopOpEnvironment ();
  CATTopOpEnvironment (const CATTopOpEnvironment & iEnviron);
  int _NbMaxElement;
  int _NbRealElement;
  CATOneComputedElement ** _StoredElements;

  CATLONG32 _NbSetted;
  CATLONG32 _MaxSetted;
  CATSubdArrayOccurenceP ** _CurSolutions;

  CATLONG32 _NbInit;
  CATLONG32 _MaxInit;
  CATSubdInitialisation ** _CurInits;

  CATLONG32 _AuthorizedDeletion;


  void AppendTabCell (CATLONG32 iNbCells, CATCell ** iTabCell, CATSubdArrayOccurenceP * oResult, CATLONG32 iAlready);
  CATULONG32 ComputeKey(CATLONG32 iNbCells, CATCell ** iTabCell);
  void SortTabCell(CATLONG32 iNbCells, CATCell ** iTabCell, CATCell **& iSortTabCell);
};

#endif
