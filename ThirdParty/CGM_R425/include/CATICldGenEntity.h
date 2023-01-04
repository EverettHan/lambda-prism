//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// File: CATICldGenEntity.h
//==============================================================================================================
// Creation: JLH - 30-Jun-2006
//==============================================================================================================

#ifndef CATICldGenEntity_h
#define CATICldGenEntity_h

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"

#include "CATBooleanDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICldGenEntity ;
#else
extern "C" const IID IID_CATICldGenEntity ;
#endif

/**
 * General interface for the entities managing clouds of points.<br>
 * The architecture of such entities is as following :
 * <pre>
 * CATICldGenEntity
 *  |
 *  +-- CATICldBody - Set of CATICldCell
 *  |
 *  +-- CATICldCell - Unitary cell
 *       |
 *       +-- CATICldCloud   - Unordered cloud of points
 *       |
 *       +-- CATICldScan    - 1D-ordered cloud of points
 *       |
 *       +-- CATICldPolygon - Tessellation of a cloud of points
 * </pre>
 * The reason of such architecture is to preserve the topological semantic of the digitalization files.
 */

class ExportedByCATGMGeometricInterfaces CATICldGenEntity : public CATBaseUnknown
{
  CATDeclareInterface ;
public:

  /**
   * Declares that the entity creation is achieved.
   *
   * @return
   * TRUE if succeed, FALSE otherwise.
   */
  virtual CATBoolean EndOfCreation() = 0 ;

  /**
   * Declares that the entity modification is achieved.
   *
   * @return
   * TRUE if succeed, FALSE otherwise.
   */
  virtual CATBoolean EndOfModification() = 0 ;

  /**
   * Compacts the CATICldGenEntity.
   * o  For a CATICldBody, removes the references to the null or removed cells and calls recursively
   *    the method for each cell.
   * o  For a CATICldCell, the removed points are deleted.
   * o  For a CATICldPolygon, the removed triangles are also deleted.
   */
  virtual void Compact() = 0 ;

} ;

CATDeclareHandler (CATICldGenEntity, CATBaseUnknown) ;

#endif
