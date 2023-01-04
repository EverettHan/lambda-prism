#ifndef CATMathExtraDistanceTools_h
#define CATMathExtraDistanceTools_h

#include "YN000FUN.h"
#include "CATBoolean.h"

class CATMathCircle;
class CATMathLine;
class CATMathPoint;
class CATSoftwareConfiguration;
class CATMathVector;
class CATTolerance;

class ExportedByYN000FUN CATMathExtraDistanceTools
{
public:
  CATMathExtraDistanceTools(CATSoftwareConfiguration * iConfig, const CATTolerance &iTolerance);
  ~CATMathExtraDistanceTools();

  int DistanceMinForCircleLineOnSamePlane(CATMathCircle & iCircle,double & iCircleStart,double & iCircleEnd,
    CATMathLine & iLine, double  iLineStart,double  iLineEnd,
    double *  oDist,CATMathPoint * oPoint1,CATMathPoint * oPoint2);

   int DistanceMaxForCircleLineOnSamePlane(CATMathCircle & iCircle,double & iCircleStart,double & iCircleEnd,
    CATMathLine & iLine, double  iLineStart,double  iLineEnd,
    double *  oDist,CATMathPoint * oPoint1,CATMathPoint * oPoint2, CATBoolean iAllMax=FALSE);

  CATMathVector ComponentNormalTo(CATMathVector & iVec, CATMathVector & iNormal);

  CATBoolean IsOnCircleAndOnLine(CATMathPoint & iPtOnCircle, CATMathCircle & iCircle, double & iCircleStart,double & iCircleEnd,
                                CATMathPoint & iPtOnLine, CATMathLine & iLine, double  iLineStart,double  iLineEnd);

private:
  CATSoftwareConfiguration *_Config;
  const CATTolerance                    &  _TolObject;
  double                                   _Tol;

  CATMathExtraDistanceTools(const CATMathExtraDistanceTools &iObject); // Prohibited
  CATMathExtraDistanceTools &operator=(const CATMathExtraDistanceTools &iObject); // Prohibited
};


#endif /* CATMathExtraDistanceTools_h */

