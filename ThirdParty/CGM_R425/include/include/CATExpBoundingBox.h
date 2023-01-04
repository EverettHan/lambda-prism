//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2014-04-24 - T6L : Creation
//==============================================================================================================


#ifndef CATExpBoundingBox_H
#define CATExpBoundingBox_H  
//#include "CATExpIntersectionPredicates.h"
#include <cfloat>
#include <algorithm>

class CATExpObject2D;

struct CATExpBoundingBox
{
	
  CATExpBoundingBox ()
  : x_lb(- DBL_MAX), x_ub(DBL_MAX), y_lb(- DBL_MAX), y_ub(DBL_MAX) {}
  
  CATExpBoundingBox (double xl, double xu, double yl, double yu)
  : x_lb(xl), x_ub(xu), y_lb(yl), y_ub(yu) {}
  
  void SetValues (double xl, double xu, double yl, double yu)
  { x_lb = xl; x_ub = xu; y_lb = yl; y_ub = yu; }

  void SetValues (const CATExpObject2D &object);

  void SetEmpty ()
  {
    x_lb = y_lb = DBL_MAX;
    x_ub = y_ub = - DBL_MAX;
  }

  template <class Number>
  void TakeIntoAccount (const Number &x, const Number &y)
  {
    x_lb = std::min<double>(x_lb, LowerBound(x));
    x_ub = std::max<double>(x_ub, UpperBound(x));
    y_lb = std::min<double>(y_lb, LowerBound(y));
    y_ub = std::max<double>(y_ub, UpperBound(y));
  }

  void TakeIntoAccount (const CATExpBoundingBox &b)
  {
    x_lb = std::min<double>(x_lb, b.x_lb);
    x_ub = std::max<double>(x_ub, b.x_ub);
    y_lb = std::min<double>(y_lb, b.y_lb);
    y_ub = std::max<double>(y_ub, b.y_ub);
  }

  // lower and upper bounds on coordinates x and y
  double x_lb, x_ub, y_lb, y_ub;
};

inline bool Overlap (const CATExpBoundingBox &bb1, const CATExpBoundingBox &bb2)
{ return ! (bb1.x_lb > bb2.x_ub || bb2.x_lb > bb1.x_ub || bb1.y_lb > bb2.y_ub || bb2.y_lb > bb1.y_ub); }


#endif
