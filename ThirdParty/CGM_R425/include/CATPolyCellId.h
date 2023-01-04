// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCellId
//
//===================================================================
// 2011-03-25   JXO
//      * New
//===================================================================
#ifndef CATPolyCellId_H
#define CATPolyCellId_H

// Poly
#include "PolyBodyBVH.h"
#include "CATCellId.h"

class CATPolyCell;

/**
 * This defines an id for cells in a CATPolyBody.
 */
class ExportedByPolyBodyBVH CATPolyCellId : public CATCellId
{
public:
  /**
   * Constructor.
   */
  CATPolyCellId (CATPolyCell & cell, int index = -1);

public:
  /**
   * Cast to priviledged type: const CATPolyCellId.
   */
  virtual const CATPolyCellId * CastAsPolyCellId() const {return this;}
  /**
   * Cast to priviledged type: CATPolyCellId.
   */
  virtual CATPolyCellId * CastAsPolyCellId() {return this;}

  /**
   * Return CATPolyCell pointed by this id.
   */
  CATPolyCell & GetCell();
  /**
   * Return index.
   */
  int GetIndex();
  /**
   * Check wether this id is equal to another id.
   */
  virtual CATBoolean operator == (CATCellId & id){return id.IsEqualTo(*this);}

  /**
   * Concrete check
   */
  virtual CATBoolean IsEqualTo(CATPolyCellId & pid){return (&m_cell == &pid.m_cell);}

protected:
  ~CATPolyCellId();


private:
  CATPolyCell & m_cell;
  int m_i;
};



#endif

