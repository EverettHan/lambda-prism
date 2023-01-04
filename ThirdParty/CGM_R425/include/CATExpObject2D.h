//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-05-06 - T6L : Creation
//==============================================================================================================


#ifndef CATExpObject2D_H
#define CATExpObject2D_H  

#include "CATExpEnums.h"
#include "CATExpPoint2D.h"
#include "CATExpIntersectionPredicates.h"

#include <algorithm>


/**
* Base class for CATExpArc2D and CATExpSegment2D.
*/
class ExportedByCATExpIntersectionPredicates CATExpObject2D {
public:
  CATExpObject2D(double x1, double y1, double x2, double y2) 
    : extremity1_(x1, y1), extremity2_(x2, y2) {}
  
  CATExpObject2D(CATExpPoint2D pt1, CATExpPoint2D pt2)
    : extremity1_(pt1), extremity2_(pt2) {}

  virtual ~CATExpObject2D() {}
  
  enum ObjectType { kArc = 0, kSegment = 1 };
  virtual ObjectType Type() const = 0; 

  const CATExpPoint2D &extremity1() const { return extremity1_; }
  double extr1_x() const { return extremity1_.x(); }
  double extr1_y() const { return extremity1_.y(); }
  void set_extremity1(CATExpPoint2D pt) { extremity1_ = pt; ResetCache(); }

  const CATExpPoint2D &extremity2() const { return extremity2_; }
  double extr2_x() const { return extremity2_.x(); }
  double extr2_y() const { return extremity2_.y(); }
  void set_extremity2(CATExpPoint2D pt) { extremity2_ = pt; ResetCache(); }

  double extr_x_min() const { return std::min<double>(extr1_x(), extr2_x()); }
  double extr_x_max() const { return std::max<double>(extr1_x(), extr2_x()); }
  double extr_y_min() const { return std::min<double>(extr1_y(), extr2_y()); }
  double extr_y_max() const { return std::max<double>(extr1_y(), extr2_y()); }

  virtual bool IsDegenerate() const = 0;

  void ResetCache () const
  { Reset(); }

protected:

private:
  virtual void Reset () const {}
  CATExpPoint2D extremity1_, extremity2_;
};



#endif
