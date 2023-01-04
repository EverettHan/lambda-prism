//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-05-06 - T6L : Creation
//==============================================================================================================


#ifndef CATExpArc2D_H
#define CATExpArc2D_H  
#include "CATExpIntersectionPredicates.h"
#include "CATExpObject2D.h"
#include "CATExpBoundingBox.h"
#include "CATExpEnums.h"


namespace CATMathExp {

//class ComputeArcOrientation;
class ComputeArcConvexity;
template <template <typename> class GeomEqn> class ComputeBoundingBox;
template <typename NT> class CircleEquation;

} // namespace CATMathExp

/**
* An arc is defined by 3 non-aligned points.
*/
class ExportedByCATExpIntersectionPredicates CATExpArc2D : public CATExpObject2D
{
  //friend struct CATMathExp::ComputeOrientation;
  template <typename NT> friend class CATMathExp::CircleEquation;
  friend class CATMathExp::ComputeArcConvexity;
  friend class CATMathExp::ComputeBoundingBox<CATMathExp::CircleEquation>;
  //template <template <typename> class GeomEqn> friend struct CATMathExp::ComputeBoundingBox;

public:

  // Construct an arc from (x1, y1) to (x3, y3) on the circle defined by the three points
  // If iMidPoint = true, (x2, y2) is lying inside the arc otherwise outside
  CATExpArc2D(double x1, double y1, double x2, double y2, double x3, double y3, bool iMidPoint = true)
  : CATExpObject2D(x1, y1, x3, y3)
  , third_point_(x2, y2)
  , is_mid_point_(iMidPoint)
  { Reset(); }

  CATExpArc2D(CATExpPoint2D pt1, CATExpPoint2D pt2, CATExpPoint2D pt3, bool iMidPoint = true)
  : CATExpObject2D(pt1, pt3)
  , third_point_(pt2)
  , is_mid_point_(iMidPoint)
  { Reset(); }

  const CATExpPoint2D &mid_point() const { return third_point_; }
  double mid_x() const { return third_point_.x(); }
  double mid_y() const { return third_point_.y(); }
  void set_mid_point(CATExpPoint2D const &pt) { third_point_ = pt; ResetCache(); }
  bool is_mid_point() const { return is_mid_point_; }

  virtual ObjectType Type() const { return kArc; }
  static const ObjectType kType = kArc;
  static const int kNbInputPoints = 3;

  virtual bool IsDegenerate() const;
  
  bool IsCounterclockwise() const
  { return Orientation() == CATExpPOSITIVE; }
  
  bool IsConvex() const;

  CATExpBoundingBox ComputeBoundingBox() const;

private:  
  CATExpSign_t Orientation () const;

  virtual void Reset () const
  {
    orientation_ = convexity_ = CATExpSIGNUNDEF;
    //north_ = east_ = south_ = west_ = CATExpSIGNUNDEF;
    //x1_vs_xc_ = x2_vs_xc_ = y1_vs_yc_ = y2_vs_yc_ = CATExpSIGNUNDEF;
    //bounding_box_.x_lb = bounding_box_.y_lb = - DBL_MAX;
    //bounding_box_.x_ub = bounding_box_.y_ub = DBL_MAX;
    //valid_bounding_box_ = false;
  }
  
  CATExpPoint2D third_point_;
  bool is_mid_point_;

  /// guaranteed but not strict lower and upper bounds on the object's coordinates
  //mutable CATExpBoundingBox bounding_box_;

  /// orientation_ == CATExpPOSITIVE means counterclockwise  
  mutable CATExpSign_t orientation_;

  /// convexity_ == CATExpPOSITIVE means convex  
  mutable CATExpSign_t convexity_;

  /** 
  * Does the arc cross the corresponding axes?
  *   - CATExpPOSITIVE means yes
  *   - CATExpNEGATIVE means no
  *   - CATExpZERO means that one of the arc's extremities lies on the axis
  *   - CATExpSIGNUNDEF means that we don't know
  *
  mutable CATExpSign_t north_, east_, south_, west_;

  /// Cache the comparisons between the extremities' and the center's coordinates; (used to compute north_ and east_)
  mutable CATExpSign_t x1_vs_xc_, x2_vs_xc_, y1_vs_yc_, y2_vs_yc_;

  mutable bool valid_bounding_box_;
  */
};



#endif
