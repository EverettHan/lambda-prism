//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldSetOfScans
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldSetOfScans_H
#define CATCldSetOfScans_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldMultiCell.h"

class CATCldScan ;
class CATMathPlane ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldSetOfScans ;
#else
extern "C" const IID IID_CATCldSetOfScans ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldSetOfScans</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATCldSetOfScans : public CATCldMultiCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldSetOfScans characteristics.
//==============================================================================================================

///**
// * Tests if the <tt>CATCldSetOfScans</tt> is planar within the given tolerance and
// * returns the computed plane.
// */
//virtual CATBoolean IsPlanar (const float iTolerance,
//                             CATMathPlane &oPlane) = 0 ;

  /**
   * Tests if all the <tt>CATCldScan</tt>s of the <tt>CATCldSetOfScans</tt>
   * are planar and have the same plane and returns it.<br>
   * The planes are told the same if their respective directions are parallel.<br>
   * <b>CAUTION:</b> <tt>ioPlane</tt> could be changed even if the method returns <tt>FALSE</tt>.
   */
  virtual CATBoolean IsPlanar (CATMathPlane &ioPlane) const = 0 ;

//==============================================================================================================
// Sub-elements management
//==============================================================================================================

  /**
   * Returns the number of scans in the <tt>CATCldSetOfScans</tt>.
   */
  virtual int GetNbScans () const = 0 ;

  /**
   * Returns the <tt>iNoScan</tt>'th <tt>CATCldScan</tt>.
   */
  virtual CATCldScan* GetScan (int iNoScan) const = 0 ;

  /**
   * Returns the list of the contained <tt>CATCldScan</tt>s.
   */
  virtual void GetScans (CATLISTP(CATCldCell) &ioScans) const = 0 ;

  /**
   * Adds the given <tt>CATCldScan</tt>.
   */
  virtual void AddScan (CATCldScan* iScan) = 0 ;

  /**
   * Insert the given <tt>CATCldScan</tt> at a given position.
   */
  virtual void InsertScanAt (CATCldScan* iScan,
                             const int   iNoPosition) = 0 ;

  /**
   * Removes the <tt>iNoScan</tt>'th <tt>CATCldScan</tt>.
   */
  virtual void RemoveScan (int iNoScan) = 0 ;

  /**
   * Removes the given <tt>CATCldScan</tt>.
   */
  virtual void RemoveScan (CATCldScan* iScan) = 0 ;

} ;

CATDeclareHandler (CATCldSetOfScans, CATCldMultiCell) ;

#endif
