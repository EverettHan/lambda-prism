#ifndef CATTopDomainBoundingCells_H
#define CATTopDomainBoundingCells_H
//---------------------------------------------------------------------------------------------------------
//      Very UseFull To Identify Cell that must be given into CATCGMJournalList
//
//	Returns the list of CATCell bounded by 0 or 1 CATCell of totally greater dimension.
//
//	- The dimension of the CATCell returned is <iDimension>. 
//       If	<iDimension> is set to -1, all the CATCell are returned.
//	- The CATCell returned are attached to <iDomain>. 
//       If <iDomain> is set to NULL, returns the CATCell of all CATDomain.
//
//	-> <oListOfCell> is ordered by CATDomain indexes and then dimension. (?)
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 19 12 2000  Creation pour supprimer CATTopBodyTools.h
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"

#include "ListPOfCATCell.h"
class CATBody;
class CATDomain;

ExportedByCATTopologicalObjects 
void CATTopDomainBoundingCells(CATBody *iBody, CATLISTP(CATCell) &oListOfCell, short iDimension, CATDomain *iDomain);


#endif
