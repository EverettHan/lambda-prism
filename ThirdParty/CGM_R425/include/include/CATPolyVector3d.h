//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Vector of 3 doubles.
//
//=============================================================================
// 2007-11-29   BPG: New
//=============================================================================
#ifndef CATPolyVector3d_H
#define CATPolyVector3d_H

class CATPolyVector3d
{
public:
  inline CATPolyVector3d(double X, double Y, double Z): _X(X), _Y(Y), _Z(Z) {}
  inline CATPolyVector3d(): _X(0.0), _Y(0.0), _Z(0.0) {}
  inline CATPolyVector3d(const CATPolyVector3d &iRHS): _X(iRHS._X), _Y(iRHS._Y), _Z(iRHS._Z) {}

public:
  inline CATPolyVector3d &operator=(const CATPolyVector3d &iRHS) { _X = iRHS._X; _Y = iRHS._Y; _Z = iRHS._Z; return *this; }

public:
  inline double GetX() const { return _X; }
  inline void SetX(double X) { _X = X; }

  inline double GetY() const { return _Y; }
  inline void SetY(double Y) { _Y = Y; }

  inline double GetZ() const { return _Z; }
  inline void SetZ(double Z) { _Z = Z; }

  inline void SetXYZ(double X, double Y, double Z) { _X = X; _Y = Y; _Z = Z; }

protected:
  double _X;
  double _Y;
  double _Z;
};

#endif // !CATPolyVector3d_H
