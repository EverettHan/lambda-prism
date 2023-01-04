#ifndef CATCGMBoundedCellGroup_H
#define CATCGMBoundedCellGroup_H

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "ListPOfCATCell.h"

class ExportedByCATGMModelInterfaces CATCGMBoundedCellGroup
{
public :

	//===========================================================================
	// CONSTRUCTORS / DESTRUCTOR
	//===========================================================================

	// Constructors
	CATCGMBoundedCellGroup();
	// Destructor
	virtual ~CATCGMBoundedCellGroup();

	//===========================================================================
    //  Add METHODS
    //===========================================================================
	void AddBoundedCell(CATLISTP(CATCell) & iCellList);
	void AddBoundedEdges(CATLISTP(CATCell) & iEdgeList);
	void SetStableOrder(CATBoolean iStableOrder);

	//===========================================================================
	//  Get METHODS
	//===========================================================================	
	void GetBoundedCells(CATLISTP(CATCell) & oCellList) const;
	void GetBoundedEdges(CATLISTP(CATCell) & oCellList) const;	
	CATBoolean IsStableOrder() const;

private:
	CATLISTP(CATCell) _BoundedCells;
	CATLISTP(CATCell) _BoundedEdges;
	CATBoolean        _StableOrder;

};

#endif
