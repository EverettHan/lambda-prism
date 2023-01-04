//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldSetOfGrids
//==============================================================================================================
// Creation: JLH - ??-???-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldSetOfGrids_H
#define CATCldSetOfGrids_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldMultiCell.h"

class CATCldGrid ;
class CATMathAxis ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldSetOfGrids ;
#else
extern "C" const IID IID_CATCldSetOfGrids ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldSetOfGrids</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATCldSetOfGrids : public CATCldMultiCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldSetOfGrids characteristics.
//==============================================================================================================

  /**
   * Tests if all the <tt>CATCldGrid</tt>s of the <tt>CATCldSetOfGrids</tt>
   * have a probe axis and have the same one and retusns it.<br>
   * The axis are told the same if their respective directions are parallel.<br>
   * <b>CAUTION:</b> <tt>ioAxis</tt> could be changed even if the method returns <tt>FALSE</tt>.
   */
  virtual CATBoolean HasAProbeAxis (CATMathAxis& ioAxis) const = 0 ;

//==============================================================================================================
// Sub-elements management
//==============================================================================================================

  /**
   * Returns the number of scans in the <tt>CATCldSetOfGrids</tt>.
   */
  virtual int GetNbGrids () const = 0 ;

  /**
   * Returns the <tt>iNoGrid</tt>'th <tt>CATCldGrid</tt>.
   */
  virtual CATCldGrid* GetGrid (int iNoGrid) const = 0 ;

  /**
   * Returns the list of the contained <tt>CATCldGrid</tt>s.
   */
  virtual void GetGrids (CATLISTP(CATCldCell) &ioGrids) const = 0 ;

  /**
   * Adds the given <tt>CATCldGrid</tt>.
   */
  virtual void AddGrid (CATCldGrid* iGrid) = 0 ;

  /**
   * Insert the given <tt>CATCldGrid</tt> at a given position.
   */
  virtual void InsertGridAt (CATCldGrid* iGrid,
                             const int   iNoPosition) = 0 ;

  /**
   * Removes the <tt>iNoGrid</tt>'th <tt>CATCldGrid</tt>.
   */
  virtual void RemoveGrid (int iNoGrid) = 0 ;

  /**
   * Removes the given <tt>CATCldGrid</tt>.
   */
  virtual void RemoveGrid (CATCldGrid* iGrid) = 0 ;

} ;

CATDeclareHandler (CATCldSetOfGrids, CATCldMultiCell) ;

#endif
