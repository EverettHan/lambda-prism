//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2019-06-14 : RNO : Compil Linux
// 2013-05-06 - T6L : Creation
//==============================================================================================================


#ifndef CATExpPoint2D_H
#define CATExpPoint2D_H  


#include <utility>
#include <functional> //for hash (RNO)
		
/**
* A point is defined by 2 coordinates.
*/
class CATExpPoint2D
{
public:

  CATExpPoint2D() : coords_(666., 666.) {}

  CATExpPoint2D(double x, double y) : coords_(x, y) {}

  double x() const { return coords_.first; }
  double y() const { return coords_.second; }
  const std::pair<double, double> &coords() const { return coords_; }

  void set_x(double x) { coords_.first = x; }
  void set_y(double y) { coords_.second = y; }

private:
  std::pair<double, double> coords_;
};

inline bool operator== (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return (pt1.coords() == pt2.coords()); }

inline bool operator!= (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return (pt1.coords() != pt2.coords()); }

inline bool operator< (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return (pt1.coords() < pt2.coords()); }

inline bool operator<= (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return (pt1.coords() <= pt2.coords()); }

inline bool operator> (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return (pt1.coords() > pt2.coords()); }

inline bool operator>= (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return (pt1.coords() >= pt2.coords()); }

template <> struct std::hash<CATExpPoint2D>
{
  std::size_t operator() (const CATExpPoint2D &pt)
  { 
    std::hash<double> hasher;
    return hasher(pt.x()) + hasher(pt.y());
  }
};

inline double SquaredDistance(const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ 
  double dx = pt2.x() - pt1.x(); 
  double dy = pt2.y() - pt1.y(); 
  return dx * dx + dy * dy;
}


inline CATExpPoint2D operator+ (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
{ return CATExpPoint2D(pt1.x() + pt2.x(), pt1.y() + pt2.y()); }

//inline CATExpPoint2D operator- (const CATExpPoint2D &pt1, const CATExpPoint2D &pt2)
//{ return CATExpPoint2D(pt1.x() - pt2.x(), pt1.y() - pt2.y()); }
//
//inline CATExpPoint2D operator- (const CATExpPoint2D &pt1)
//{ return CATExpPoint2D(- pt1.x(), - pt1.y()); }
//
//inline CATExpPoint2D operator* (double lambda, const CATExpPoint2D &pt1)
//{ return CATExpPoint2D(lambda * pt1.x(), lambda * pt1.y()); }



#endif
