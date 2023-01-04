#ifndef CATMATHINTERVAL2D_H
#define CATMATHINTERVAL2D_H

// COPYRIGHT DASSAULT SYSTEMES 1999
/** @CAA2Required */ 
/**
 * Use now the CATMathIntervalND class.
 */

#include "YN000FUN.h"
#include "CATMathPoint2D.h"
#include "CATMathInterval.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"


class ExportedByYN000FUN CATMathInterval2D : public CATCGMVirtual
{
 private:
  CATMathInterval x, y;
 public:
  CATMathInterval2D();

  CATMathInterval2D(const CATMathPoint2D & p, const CATMathPoint2D & P):
    x(p.GetX(),P.GetX()), y(p.GetY(),P.GetY())
      {};
  
  CATMathInterval2D(const CATMathInterval & _x, const CATMathInterval & _y):
    x(_x), y(_y)
      {};

  CATMathInterval2D(const CATMathInterval2D & i):
    x(i.x), y(i.y)
      {};

  CATMathInterval GetX() const { return x; };
  CATMathInterval GetY() const { return y; };
  CATMathPoint2D GetMax() const;
  CATMathPoint2D GetMin() const;

  void SetX(const CATMathInterval & i);
  void SetY(const CATMathInterval & i);

  CATLONG32 IsEmpty() const;
  double DistanceTo(const CATMathPoint2D & i) const;
  CATMathPoint2D Center() const;

//
//- Operators
//
//  Intersection
  friend ExportedByYN000FUN CATMathInterval2D operator &&
    (const CATMathInterval2D & i1,const CATMathInterval2D & i2)
      { return CATMathInterval2D(i1.x&&i2.x, i1.y&&i2.y); }

//  Union
  friend ExportedByYN000FUN CATMathInterval2D operator ||
    (const CATMathInterval2D & i1, const CATMathInterval2D & i2)
      { return CATMathInterval2D(i1.x||i2.x, i1.y||i2.y); }

//  Addition
  friend ExportedByYN000FUN CATMathInterval2D operator +
    (const CATMathInterval2D & i1, const CATMathInterval2D & i2)
      { return CATMathInterval2D(i1.x+i2.x, i1.y+i2.y); }

//  Substraction
  friend ExportedByYN000FUN CATMathInterval2D operator -
    (const CATMathInterval2D & i1, const CATMathInterval2D & i2)
      { return CATMathInterval2D(i1.x-i2.x, i1.y-i2.y); }

//  Multiplication
  friend ExportedByYN000FUN CATMathInterval2D operator *
    (const CATMathInterval2D & i1, const CATMathInterval2D & i2)
      { return CATMathInterval2D(i1.x*i2.x, i1.y*i2.y); }

//  Division
  friend ExportedByYN000FUN CATMathInterval2D operator /
    (const CATMathInterval2D & i1, const CATMathInterval2D & i2)
      { return CATMathInterval2D(i1.x/i2.x, i1.y/i2.y); }

//  Opposite
  friend ExportedByYN000FUN CATMathInterval2D operator -
    (const CATMathInterval2D & i)
      { return CATMathInterval2D(-i.x, -i.y); }

//  Scalar Addition
  friend ExportedByYN000FUN CATMathInterval2D operator +
    (const CATMathPoint2D & d, const CATMathInterval2D & i)
      { return CATMathInterval2D(d.GetX()+i.x, d.GetY()+i.y); }
  friend ExportedByYN000FUN CATMathInterval2D operator +
    (const CATMathInterval2D & i, const CATMathPoint2D & d)
      { return CATMathInterval2D(i.x+d.GetX(), i.y+d.GetY()); }

//  Scalar Substraction
  friend ExportedByYN000FUN CATMathInterval2D operator -
    (const CATMathPoint2D & d, const CATMathInterval2D & i)
      { return CATMathInterval2D(d.GetX()-i.x, d.GetY()-i.y); }
  friend ExportedByYN000FUN CATMathInterval2D operator -
    (const CATMathInterval2D & i, const CATMathPoint2D & d)
      { return CATMathInterval2D(i.x-d.GetX(), i.y-d.GetY()); }

//  Scalar Multiplication
  friend ExportedByYN000FUN CATMathInterval2D operator *
    (const CATMathPoint2D & d, const CATMathInterval2D & i)
      { return CATMathInterval2D(d.GetX()*i.x, d.GetY()*i.y); }
  friend ExportedByYN000FUN CATMathInterval2D operator *
    (const CATMathInterval2D & i, const CATMathPoint2D & d)
      { return CATMathInterval2D(i.x*d.GetX(), i.y*d.GetY()); }

//  Scalar Division
  friend ExportedByYN000FUN CATMathInterval2D operator /
    (const CATMathPoint2D & d, const CATMathInterval2D & i)
      { return CATMathInterval2D(d.GetX()/i.x, d.GetY()/i.y); }
  friend ExportedByYN000FUN CATMathInterval2D operator /
    (const CATMathInterval2D & i, const CATMathPoint2D & d)
      { return CATMathInterval2D(i.x/d.GetX(), i.y/d.GetY()); }

};

#endif
