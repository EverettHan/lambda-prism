#ifndef BoundingOfDomain_H
#define BoundingOfDomain_H

// COPYRIGHT DASSAULT SYSTEMES 1999

class CATDomain;
#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATCell.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class ExportedByCATTopologicalObjects BoundingOfDomain : public CATCGMVirtual
{
 private:
  CATDomain * _Domaine;
  int _NombreDeCellsBords;
  ListPOfCATCell _CellulesBords;
  int _ClefAttribut;

// count number of bounding cells of a cell
  void CountBoundingOfCell(int iDimDomain, CATCell * iCell,
                           int &total, int &pasbord,
                           CATBoolean iCellsAreInDomain = TRUE);

// compute bounding of one cell
  void BoundingOfCell(int iDimDomain, CATCell * iCell);

// Check for free border
  void CheckForFreeBorder(CATCell *iCell, int iDimDomainLessOne);
  
// destruction of attributes on cells
  void DeleteAttributes();
  
 public:
// constructor without attributes
  BoundingOfDomain(CATDomain * iDomain);

// constructor with attribute key
 // BoundingOfDomain(CATDomain * iDomain, int &ioKeyAttBoundingCells);

// destructor
  ~BoundingOfDomain() ;

// Runs a BoundingOfDomain operator
  void Run();

// run with given cells 
  void Run(ListPOfCATCell &iListCell);

// returns the number of bounding cells
  INLINE int GetNumberOfCells();

// returns the bounding cells
  INLINE void GetCells(ListPOfCATCell &oVertices);

};

// ------------------------------------------------------------------------------------------------------
// INLINE
// ------------------------------------------------------------------------------------------------------

// read the number of bounding cells
// ---------------------------------
INLINE int BoundingOfDomain::GetNumberOfCells()
{
  return(_NombreDeCellsBords);
}

// read the bounding cells
// -----------------------
INLINE void BoundingOfDomain::GetCells(ListPOfCATCell& oVertices)
{
  oVertices.Append(_CellulesBords);
}

#endif

