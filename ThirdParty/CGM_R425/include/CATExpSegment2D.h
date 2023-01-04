//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-05-06 - T6L : Creation
//==============================================================================================================


#ifndef CATExpSegment2D_H
#define CATExpSegment2D_H  

#include "CATExpObject2D.h"
#include "CATExpPoint2D.h"
struct CATExpBoundingBox;


/**
* A segment is defined by 2 different points.
*/
class CATExpSegment2D : public CATExpObject2D
{
public:

  CATExpSegment2D(double x1, double y1, double x2, double y2) : CATExpObject2D(x1, y1, x2, y2) {}

  CATExpSegment2D(CATExpPoint2D pt1, CATExpPoint2D pt2) : CATExpObject2D(pt1, pt2) {}

  ObjectType Type() const { return kSegment; }
  static const ObjectType kType = kSegment;
  static const int kNbInputPoints = 2;

  virtual bool IsDegenerate () const
  { return extremity1() == extremity2(); }

  ExportedByCATExpIntersectionPredicates CATExpBoundingBox ComputeBoundingBox() const;
};

#endif
