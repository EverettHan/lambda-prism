// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CAT2DIndexPointsList.h
//
//===================================================================
//
// Usage notes: 
//
//===================================================================
//
// August 2009  Creation: ZFI
//===================================================================

#ifndef CAT2DIndexPointsList_H
#define CAT2DIndexPointsList_H


#include "PolyMathContainers.h"

#include "CATPolyBuckets_T.h"

#include "CATErrorDef.h"
#include "CATMathPoint2D.h"
#include "CATBoolean.h"

class ExportedByPolyMathContainers CAT2DIndexPoint
{
public:
  CAT2DIndexPoint(){_X=0;_Y=0;_PolyIndex=0;}
  ~CAT2DIndexPoint(){}

public:
  CAT2DIndexPoint(double x, double y, int index) {_X=x;_Y=y;_PolyIndex=index;}
  void Set(double x, double y, int index) {_X=x;_Y=y;_PolyIndex=index;}
  void SetPosition(double x, double y) {_X=x;_Y=y;}
  double GetX() const{return _X;}
  double GetY() const{return _Y;}
  int GetIndex()const{return _PolyIndex;}

  //Assignement Operator=
  CAT2DIndexPoint& operator=(const CAT2DIndexPoint &iPC)
  {
    _PolyIndex = iPC._PolyIndex;
    _X=iPC._X;
    _Y=iPC._Y;
    return *this;
  }

private:
  int _PolyIndex;
  double _X,_Y;
};
  
class ExportedByPolyMathContainers Specialize_CATPolyBuckets_T(CAT2DIndexPointsList, CAT2DIndexPoint);

#endif
