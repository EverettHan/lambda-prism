//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// File: CATICldBody.h
//==============================================================================================================
// Creation: JLH - 30-Jun-2006
//==============================================================================================================

#ifndef CATICldBody_h
#define CATICldBody_h

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATICldGenEntity.h"

class CATICldCell ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICldBody ;
#else
extern "C" const IID IID_CATICldBody ;
#endif

/**
 * Interface for the entity <tt>CATICldBody</tt>.<br>
 * @see CATICldGenEntity
 */
class ExportedByCATGMGeometricInterfaces CATICldBody : public CATICldGenEntity
{
  CATDeclareInterface ;
public:

  /**
   * Returns the number of cells.
   *
   * @return
   * The number of cells.
   */
  virtual int GetNbCells() const = 0 ;

  /**
   * Returns the iNoCell'th cell.
   *
   * @param iNoCell
   * The index of the cell to retreive.
   * It should be in the range [1,GetNbCells()].
   *
   * @return
   * The desired cell.
   */
  virtual CATICldCell* GetCell (const int iNoCell) const = 0 ;

  /**
   * Adds a CATICldCell.
   *
   * @param iCell
   * The cell to add.
   *
   * @return
   * If positive, the index of the added cell (the first is equal to 1).
   * If null or negative, the cell was not added.
   */
  virtual int AddCell (CATICldCell* iCell) = 0 ;

  /**
   * Removes the iNoCell'th cell.
   *
   * @param iNoCell
   * The index of the cell to remove.
   * It should be in the range [1,GetNbCells()].
   */
  virtual void RemoveCell (const int iNoCell) = 0 ;
} ;

CATDeclareHandler (CATICldBody, CATICldGenEntity) ;

#endif
