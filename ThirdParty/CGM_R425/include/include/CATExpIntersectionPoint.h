//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-05-13 - T6L : Creation
//==============================================================================================================


#ifndef CATExpIntersectionPoint_H
#define CATExpIntersectionPoint_H  

#include <cstddef>

#include "CATExpEnums.h"
#include "CATExpPoint2D.h"
#include <string>
#include <array>
#include <iostream>
// forward declarations
class CATExpObject2D;
namespace CATMathExp { 
  struct ToCATExpIntersectionPoint;
  struct ToCATExpIntersectionPointWithSwap;
} // namespace CATMathExp


/**
* Intersection point between two CATExpObject2D.
*/
class CATExpIntersectionPoint
{
  friend struct CATMathExp::ToCATExpIntersectionPoint;
  friend struct CATMathExp::ToCATExpIntersectionPointWithSwap;

public:
  CATExpIntersectionPoint()
  : object1_(NULL), object2_(NULL), index1_(666), index2_(666),
    position_on_object1_(CATExpPOSUNDEF), position_on_object2_(CATExpPOSUNDEF),
    left_crossing_(CATExpBOOLUNDEF), valid_(false), input_(false), tangent_(false), degenerate_(false) {}

  const CATExpObject2D *object1() const { return object1_; }
  const CATExpObject2D *object2() const { return object2_; }

  std::size_t index1() const { return index1_; }
  std::size_t index2() const { return index2_; }

  const CATExpPoint2D &coordinates() const { return coordinates_; }
  double x() const { return coordinates_.x(); }
  double y() const { return coordinates_.y(); }

  CATExpPosition_t position_on_object1() const { return position_on_object1_; }
  CATExpPosition_t position_on_object2() const { return position_on_object2_; }

  /// is it a trivial input common point?
  bool input() const { return input_; }

  /// is it a tangent point?
  bool tangent() const { return tangent_; }

  /// is it a degenerate point? (extremity of an overlapping area)
  bool degenerate() const { return degenerate_; }

  /// does the 2nd object go out of the 1st one leftwards? 
  CATExpBool_t left_crossing() const { return left_crossing_; }

  /// is it a valid intersection point?
  bool valid() const { return valid_; }

  bool extremal() const
  {
    if (((position_on_object1_ == CATExpEXTREMITY1 || position_on_object1_ == CATExpEXTREMITY2)
        && position_on_object2_ != CATExpOUTSIDE) 
     || ((position_on_object2_ == CATExpEXTREMITY1 || position_on_object2_ == CATExpEXTREMITY2) 
        && position_on_object1_ != CATExpOUTSIDE)) return true;
    else return false;
  }

private:
  CATExpIntersectionPoint
  (
    const CATExpObject2D *object1, const CATExpObject2D *object2, std::size_t index1, std::size_t index2,
    double x, double y,
    CATExpPosition_t position_on_object1, CATExpPosition_t position_on_object2,
    CATExpSign_t left_crossing, bool valid, bool input, bool tangent, bool degenerate
  )
  : object1_(object1), object2_(object2), index1_(index1), index2_(index2), coordinates_(x, y),
    position_on_object1_(position_on_object1), position_on_object2_(position_on_object2),
    valid_(valid), input_(input), tangent_(tangent), degenerate_(degenerate)
  {
    switch (left_crossing)
    {
    case CATExpNEGATIVE: left_crossing_ = CATExpFALSE; break;
    case CATExpPOSITIVE: left_crossing_ = CATExpTRUE; break;
    default: left_crossing_ = CATExpBOOLUNDEF; break;
    }
  }

  const CATExpObject2D *object1_, *object2_;
  std::size_t index1_, index2_;
  //double x_, y_;
  CATExpPoint2D coordinates_;
  CATExpPosition_t position_on_object1_, position_on_object2_;

  CATExpBool_t left_crossing_;

  bool valid_, input_, tangent_, degenerate_;
};


inline void Print (const CATExpIntersectionPoint &pt)
{ 
//RNO No char * cast in ISO C++ !!!
  //static char *position[] = {"extremity1", "inside", "extremity2"};
  //static char *crossing[] = {"right", "left"};
  const std::array<std::string,3> position = {"extremity1", "inside", "extremity2"};
  const std::array<std::string,2> crossing = {"right", "left"};
  if(pt.valid())
  { 
    printf("Intersection point: x = %f\t y = %f;\t", pt.x(), pt.y());
    if (pt.extremal())
      std::cout<< position[pt.position_on_object1()]<<"\t"<<position[pt.position_on_object2()];
    if (pt.left_crossing() != CATExpBOOLUNDEF)
      std::cout<<" Crossing %s;\t", crossing[pt.left_crossing()];
    if (pt.input()) std::cout<<"Input;\t";
    if (pt.tangent()) std::cout<<"Tangent;\t";
    if (pt.degenerate()) std::cout<<"Degenerate;\t";
    std::cout<<std::endl;
  }
}


inline double SquaredDistance(const CATExpIntersectionPoint &pt1, const CATExpIntersectionPoint &pt2)
{ 
  double dx = pt2.x() - pt1.x(); 
  double dy = pt2.y() - pt1.y(); 
  return dx * dx + dy * dy;
}

#endif
