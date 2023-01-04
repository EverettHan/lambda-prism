//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldMultiCell
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldMultiCell_H
#define CATCldMultiCell_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldCell.h"
class CATCldUniCell ;

#include "CATListOfCATCldCells.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldMultiCell ;
#else
extern "C" const IID IID_CATCldMultiCell ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldMultiCell</tt>.<br>
 * A <tt>CATCldMultiCell</tt> is composed of <tt>CATCldUniCell</tt> of the same type.
 * @see CATCldGenEntity, CATCldCell
 */
class ExportedByCATGMGeometricInterfaces CATCldMultiCell : public CATCldCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// Sub-elements management
//==============================================================================================================

  /**
   * Returns the number of sub-cells.
   */
  virtual int GetNbSubCells () const = 0 ;

  /**
   * Returns the <tt>iNoSubCell</tt>'th sub-cell.
   */
  virtual CATCldUniCell* GetSubCell (const int iNoSubCell) const = 0 ;

  /**
   * Returns the list of all the sub-cells.<br>
   * <b>CAUTION:</b> The list will be cleared by the method before use.
   */
  virtual void GetSubCells (CATLISTP(CATCldCell) &ioSubCells) const = 0 ;

  /**
   * Removes the <tt>iNoSubCell</tt>'th sub-cell.
   */
  virtual void RemoveSubCell (const int iNoSubCell) = 0 ;

  /**
   * Removes the given sub-cell.
   */
  virtual void RemoveSubCell (const CATCldUniCell* iSubCell) = 0 ;

} ;

CATDeclareHandler (CATCldMultiCell, CATCldCell) ;

#endif
