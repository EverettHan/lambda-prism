//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// File: CATICldScan.h
//==============================================================================================================
// Creation: JLH - 30-Jun-2006
//==============================================================================================================

#ifndef CATICldScan_h
#define CATICldScan_h

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATICldCell.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICldScan ;
#else
extern "C" const IID IID_CATICldScan ;
#endif

/**
 * Interface for the entity <tt>CATICldScan</tt>.<br>
 * The <tt>CATICldScan</tt> corresponds to an <i>ordered</i> set of points.<br>
 * @see CATICldGenEntity, CATICldCell
 */
class ExportedByCATGMGeometricInterfaces CATICldScan : public CATICldCell
{
  CATDeclareInterface ;

public:

  /**
   * Inserts a point given by its coordinates at a given position.
   *
   * @param iCoords
   * The coordinates of the point to insert.
   *
   * @param iNoPosition
   * The position index at which the point is inserted.
   * It should be in the range [1,GetNbPoints()].
   *
   * @return
   * If positive, the index of the inserted point (should be equal to iNoPosition).
   * If null or negative, the point was not added.
   */
  virtual int InsertPointAt (const float iCoords[3],
                             const int   iNoPosition) = 0 ;

  /**
   * Inserts a point given by its coordinates at a given position
   *
   * @param iCoords
   * The coordinates of the point to insert.
   *
   * @param iNoPosition
   * The position index at which the point is inserted.
   * It should be in the range [1,GetNbPoints()].
   *
   * @return
   * If positive, the index of the inserted point (should be equal to iNoPosition).
   * If null or negative, the point was not added.
   */
  virtual int InsertPointAt (const double iCoords[3],
                             const int    iNoPosition) = 0 ;

} ;

CATDeclareHandler (CATICldScan, CATICldCell) ;

#endif
