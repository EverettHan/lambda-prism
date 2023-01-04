//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// File: CATICldCell.h
//==============================================================================================================
// Creation: JLH - 30-Jun-2006
//==============================================================================================================

#ifndef CATICldCell_h
#define CATICldCell_h

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATICldGenEntity.h"

#include "CATBooleanDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICldCell ;
#else
extern "C" const IID IID_CATICldCell ;
#endif

/**
 * Interface for the entity <tt>CATICldCell</tt>.<br>
 * @see CATICldGenEntity
 */
class ExportedByCATGMGeometricInterfaces CATICldCell : public CATICldGenEntity
{
  CATDeclareInterface ;
public:

  /**
   * Returns the number of points.
   *
   * @return
   * The number of points.
   */
  virtual int GetNbPoints() = 0 ;
  
  /**
   * Adds a point given by its coordinates.
   *
   * @param iCoords
   * The coordinates of the point to add.
   *
   * @return
   * If positive, the index of the added point (the first is equal to 1).
   * If null or negative, the point was not added.
   */
  virtual int AddPoint (const float iCoords[3]) = 0 ;

  /**
   * Adds a point given by its coordinates.
   *
   * @param iCoords
   * The coordinates of the point to add.
   *
   * @return
   * If positive, the index of the added point (the first is equal to 1).
   * If null or negative, the point was not added.
   */
  virtual int AddPoint (const double iCoords[3]) = 0 ;

  /**
   * Returns the coordinates of the iNoPoint'th point.
   *
   * @param iNoPoint
   * The index of the point.
   * It should be in the range [1,GetNbPoints()].
   *
   * @param oCoords
   * The desired coordinates.
   */
  virtual void GetCoords (const int iNoPoint,
                          float     oCoords[3]) const = 0 ;

  /**
   * Returns the coordinates of the iNoPoint'th point.
   *
   * @param iNoPoint
   * The index of the point.
   * It should be in the range [1,GetNbPoints()].
   *
   * @param oCoords
   * The desired coordinates.
   */
  virtual void GetCoords (const int iNoPoint,
                          double    oCoords[3]) const = 0 ;
  
  /**
   * Removes the iNoPoint'th point.
   *
   * @param iNoPoint
   * The index of the point to remove.
   * It should be in the range [1,GetNbPoints()].
   */
  virtual void RemovePoint (const int iNoPoint) = 0 ;

  /**
   * Updates the coordinates of the iNoPoint'th point.
   *
   * @param iNoPoint
   * The index of the point.
   * It should be in the range [1,GetNbPoints()].
   *
   * @param iCoords
   * The new coordinates.
   */
  virtual void SetCoords (const int iNoPoint,
                          float     iCoords[3]) const = 0 ;

  /**
   * Updates the coordinates of the iNoPoint'th point.
   *
   * @param iNoPoint
   * The index of the point.
   * It should be in the range [1,GetNbPoints()].
   *
   * @param iCoords
   * The new coordinates.
   */
  virtual void SetCoords (const int iNoPoint,
                          double    iCoords[3]) const = 0 ;
  
  /**
   * Tests if the iNoPoint'th point is valid ie. not removed.
   *
   * @param iNoPoint
   * The index of the point to check.
   * It should be in the range [1,GetNbPoints()].
   *
   * @return
   * TRUE if the point is valid, FALSE otherwise.
   */
  virtual CATBoolean IsAValidPoint (const int iNoPoint) const = 0 ;

  /**
   * Tests if the iNoPoint'th point is selected.
   * This tag is managed by an interactive way.
   *
   * @param iNoPoint
   * The index of the point to check.
   * It should be in the range [1,GetNbPoints()].
   *
   * @return
   * TRUE if the point is selected, FALSE otherwise.
   */
  virtual CATBoolean IsASelectedPoint (const int iNoPoint) const = 0 ;

  /**
   * Tests if the iNoPoint'th point is filtered.
   * This tag is managed by an interactive way.
   *
   * @param iNoPoint
   * The index of the point to check.
   * It should be in the range [1,GetNbPoints()].
   *
   * @return
   * TRUE if the point is filtered, FALSE otherwise.
   */
  virtual CATBoolean IsAFilteredPoint (const int iNoPoint) const = 0 ;

  /**
   * Tests if the iNoPoint'th point is active ie is selected and unfiltered.
   * This tag is managed by an interactive way.
   *
   * @param iNoPoint
   * The index of the point to check.
   * It should be in the range [1,GetNbPoints()].
   *
   * @return
   * TRUE if the point is active, FALSE otherwise.
   */
  virtual CATBoolean IsAnActivePoint (const int iNoPoint) const = 0 ;

} ;

CATDeclareHandler (CATICldCell, CATICldGenEntity) ;

#endif
