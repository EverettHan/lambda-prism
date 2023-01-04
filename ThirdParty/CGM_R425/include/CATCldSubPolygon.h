//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2008
//==============================================================================================================
// CATCldSubPolygon
//==============================================================================================================
// 19-Nov-2008 - JLH - Création.
//==============================================================================================================

#include "CATIACGMLevel.h"


#ifndef CATCldSubPolygon_H
#define CATCldSubPolygon_H

#include "CATCldPolygon.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldSubPolygon ;
#else
extern "C" const IID IID_CATCldSubPolygon ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldSubPolygon</tt>.<br>
 * @see CATCldGenEntity, CATCldCell, CATCldUniCell, CATCldPolygon
 */

class ExportedByCATGMGeometricInterfaces CATCldSubPolygon : public CATCldPolygon
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldSubPolygon characteristics.
//==============================================================================================================

  /**
   * Gets the reference cell.
   */
  virtual const CATCldPolygon* GetSupport() = 0 ;

//==============================================================================================================
// Specific triangles management for the CATCldSubPolygon.
//==============================================================================================================

  /**
   * Adds the <tt>iNoRef</tt>'th triangle of the reference polygon.<br>
   * @return
   * The relative address into the sub-polygon. <tt>0</tt> if problem.
   */
  virtual int AddRefTriangle (const int iNoRef) = 0 ;

  /**
   * Removes the triangle corresponding to the <tt>iNoRef</tt>'th triangle of the reference polygon.
   */
  virtual void RemoveRefTriangle (const int iNoRef) = 0 ;

  /**
   * Locates the <tt>iNoRef</tt>'th triangle of the reference polygon.<br>
   * @return
   * Returns the relative address into the sub-polygon. <tt>0</tt> if problem.
   */
  virtual int LocateRefTriangle (const int iNoRef) = 0 ;

  /**
   * Returns the reference address of the <tt>iNoTri</tt>'th triangle of the sub-polygon.<br>
   * @return
   * Returns the reference address. <tt>0</tt> if problem.
   */
  virtual int GetRefTriangle (const int iNoTri) = 0 ;

} ;

CATDeclareHandler (CATCldSubPolygon, CATCldPolygon) ;


#endif // 
