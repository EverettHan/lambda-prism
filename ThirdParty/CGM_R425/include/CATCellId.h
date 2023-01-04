// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCellId
//
//===================================================================
// 2011-03-25   JXO
//      * New
//===================================================================
#ifndef CATCellId_H
#define CATCellId_H

// Poly
#include "PolyBodyBVH.h"
#include "CATPolyRefCounted.h"

// Math
#include "CATBoolean.h"


// Possible ids:
class CATPolyCellId;
class CATExactCellId;


/**
 * This defines an id for cells in a CATPolyBody or a CATBody
 */
class ExportedByPolyBodyBVH CATCellId : public CATPolyRefCounted
{
public:
  /**
   * Constructor.
   */
  CATCellId ();

public:
  /**
   * Cast to priviledged type: const CATPolyCellId.
   */
  virtual const CATPolyCellId * CastAsPolyCellId() const {return 0;}
  /**
   * Cast to priviledged type: const CATExactCellId.
   */
  virtual const CATExactCellId * CastAsExactCellId() const {return 0;}
  /**
   * Cast to priviledged type: CATPolyCellId.
   */
  virtual CATPolyCellId * CastAsPolyCellId() {return 0;}
  /**
   * Cast to priviledged type: CATExactCellId.
   */
  virtual CATExactCellId * CastAsExactCellId() {return 0;}
  /**
   * Check wether this id is equal to another id (i.e. points to the same object.)
   */
  virtual CATBoolean operator == (CATCellId & ) = 0;





  /**
   * Concrete check.
   */
  virtual CATBoolean IsEqualTo(CATPolyCellId&){return FALSE;}
  /**
   * Concrete check.
   */
  virtual CATBoolean IsEqualTo(CATExactCellId&){return FALSE;}

protected:
  virtual ~CATCellId(){}


};



#endif

