// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBoxf.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// March 2010 Creation: JXO
// May   2013 Modification JXO: double migration for large scale
// June  2013 Modification JXO: POLY_NEXT/PREV_FLOAT macros
// Mai   2018 Add new method "GetMathBox" for performance ( with force inline )
//===================================================================
#ifndef CATPolyBoxf_h
#define CATPolyBoxf_h

#include "BVHObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

// Math
#include "CATMathInline.h"
#include "CATMathPoint.h"
#include "CATMathPointf.h"
#include "CATMathBox.h"
#include "CATMath.h"
#include "CATTolerance.h"

// System
#include "CATDataType.h"

// To use double precision:
// #define POLY_USE_DOUBLE

#ifdef POLY_USE_DOUBLE
typedef double polycoordstype;
#else
typedef float polycoordstype;
#endif

#define POLY_NEXT_FLOAT(f) \
  { \
  CATLONG32 & floatint = (*((CATLONG32 *)&(f))); \
  if(floatint>0){++floatint;}else if((f)==0.){floatint=0x00000001;}else if(floatint<0){--floatint;} \
  }
#define POLY_PREV_FLOAT(f) \
  { \
  CATLONG32 & floatint = (*((CATLONG32 *)&(f))); \
  if(floatint>0){--floatint;}else if((f)==0.){floatint=0x80000001;}else if(floatint<0){++floatint;} \
  }

#ifdef POLY_USE_DOUBLE
#define BOXF_NEXT_FLOAT(f)
#define BOXF_PREV_FLOAT(f)
#else
#define BOXF_NEXT_FLOAT(f) POLY_NEXT_FLOAT(f)
#define BOXF_PREV_FLOAT(f) POLY_PREV_FLOAT(f)
#endif

class ExportedByBVHObjects CATPolyBoxf
{
public:
  CATPolyBoxf(const double xmin
#ifdef POLY_USE_DOUBLE
              = 1.
#endif
              , const double xmax
#ifdef POLY_USE_DOUBLE
              = -1.
#endif
              , const double ymin
#ifdef POLY_USE_DOUBLE
              = 1.
#endif
              , const double ymax
#ifdef POLY_USE_DOUBLE
              = -1.
#endif
              , const double zmin
#ifdef POLY_USE_DOUBLE
              = 1.
#endif
              , const double zmax
#ifdef POLY_USE_DOUBLE
              = -1.
#endif
              )
  {
    _XMin = (polycoordstype)xmin;
    _YMin = (polycoordstype)ymin;
    _ZMin = (polycoordstype)zmin;
    _XMax = (polycoordstype)xmax;
    _YMax = (polycoordstype)ymax;
    _ZMax = (polycoordstype)zmax;
    BOXF_PREV_FLOAT(_XMin);
    BOXF_PREV_FLOAT(_YMin);
    BOXF_PREV_FLOAT(_ZMin);
    BOXF_NEXT_FLOAT(_XMax);
    BOXF_NEXT_FLOAT(_YMax);
    BOXF_NEXT_FLOAT(_ZMax);
  }
#ifndef POLY_USE_DOUBLE
  CATPolyBoxf(const polycoordstype xmin = 1.f, const polycoordstype xmax = -1.f,
              const polycoordstype ymin = 1.f, const polycoordstype ymax = -1.f, 
              const polycoordstype zmin = 1.f, const polycoordstype zmax = -1.f)
  {
    _XMin = xmin;
    _YMin = ymin;
    _ZMin = zmin;
    _XMax = xmax;
    _YMax = ymax;
    _ZMax = zmax;
  }
#endif
  ~CATPolyBoxf(){}

  /**
   * Copy Constructor.
   */
  CATPolyBoxf(const CATPolyBoxf &iBoxToCopy);
  /**
   * Constructor from a CATMathBox.
   */
  CATPolyBoxf(const CATMathBox &iBoxToCopy);

  /**
   * Modifies <tt>this</tt> CATPolyBoxf by forcing a CATMathPoint to belong to it.
   */
	inline void AddInside(const CATMathPoint &iPointToAdd);
  /**
   * Modifies <tt>this</tt> CATPolyBoxf by forcing a CATMathPointf to belong to it.
   */
  inline void AddInside(const CATMathPointf &iPointToAdd);
  /**
   * Modifies <tt>this</tt> CATPolyBoxf by forcing a CATPolyBoxf to belong to it.
   */
  inline void AddInside(const CATPolyBoxf &iBoxToAdd);
  /**
   * Modifies <tt>this</tt> CATPolyBoxf by forcing a CATMathBox to belong to it.
   */
  inline void AddInside(const CATMathBox &iBoxToAdd);

#ifndef POLY_USE_DOUBLE
  /**
   * Retrieves the extremities of <tt>this</tt> CATPolyBoxf.
   * @return 
   * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
   */
  inline HRESULT GetLimits(polycoordstype &ioXMin, polycoordstype &ioXMax,
	                         polycoordstype &ioYMin, polycoordstype &ioYMax,
	                         polycoordstype &ioZMin, polycoordstype &ioZMax) const;
#endif
  /**
   * Retrieves the extremities of <tt>this</tt> CATPolyBoxf.
   * @return 
   * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
   */
  inline HRESULT GetLimits(double &ioXMin, double &ioXMax,
	                         double &ioYMin, double &ioYMax,
	                         double &ioZMin, double &ioZMax) const;

  inline polycoordstype GetXMin() const
  {
    return _XMin;
  }
  inline polycoordstype GetXMax() const
  {
    return _XMax;
  }
  inline polycoordstype GetYMin() const
  {
    return _YMin;
  }
  inline polycoordstype GetYMax() const
  {
    return _YMax;
  }
  inline polycoordstype GetZMin() const
  {
    return _ZMin;
  }
  inline polycoordstype GetZMax() const
  {
    return _ZMax;
  }

  /**
   * Retrieves the low extremity of <tt>this</tt> CATPolyBoxf.
   * @return 
   * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
   */
  HRESULT GetLowLimit(CATMathPoint &ioLowPoint) const;
  /**
   * Retrieves the high extremity of <tt>this</tt> CATPolyBoxf.
   * @return 
   * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
   */
  HRESULT GetHighLimit(CATMathPoint &ioHighPoint) const;
  /**
   * Sets the extremities of <tt>this</tt> CATPolyBoxf.
   *<br>No verification is done.
   */
  inline void SetExtremities(const polycoordstype iXMin, const polycoordstype iXMax,
                             const polycoordstype iYMin, const polycoordstype iYMax,
                             const polycoordstype iZMin, const polycoordstype iZMax);
  /**
   * Resets <tt>this</tt> CATPolyBoxf to an empty one.
   */
  inline void SetToEmpty();
  /**
   * Tests if <tt>this</tt> CATPolyBoxf is empty.
   * @return
   * <tt>TRUE</tt> if the CATPolyBoxf is empty, <tt>FALSE</tt> otherwise.
   */
  inline CATBoolean IsEmpty() const;

  /**
   * Returns <tt>TRUE</tt> if <tt>this</tt> CATPolyBoxf is intersecting an another one.
   * The test takes a given tolerance into account (the result is equivalent
   * to inflating one of the box of iTol and to compute IsIntersecting with
   * no tolerance.
   *<br> Note that if the intersection is a point or a line, the
   * result is true.
   */
  inline CATBoolean IsIntersecting(const CATPolyBoxf &iBox, polycoordstype iTol = 0.) const;


  /**
   * Test intersection between two polyboxf with and without tolerance.
   * These functions assume that the two bounding boxes are not empty
   */
  inline CATBoolean FastIsIntersecting(const CATPolyBoxf & iBox) const;
  inline CATBoolean FastIsIntersecting(const CATPolyBoxf &iBox, polycoordstype iTol) const;

  enum IntersectionTestOrder
  {
    XYZ,
    XZY,
    YXZ,
    YZX,
    ZXY,
    ZYX
  };

  /**
   * Returns the optimum order of the axis to speed up the intersection tests with 
   * another bounding box.  (From axis with smallest range to axis with largest range.)
   */
  inline IntersectionTestOrder GetAxisTestOrder () const;

  /**
   * Test intersections between two polyboxf and specify in which order the test must be performed
   * (for example YZX means that Y will be tested first, then Z and then X.
   */
  inline CATBoolean UltraFastIsIntersecting(IntersectionTestOrder order, const CATPolyBoxf & iBox) const;

  /**
   * Returns <tt>TRUE</tt> if <tt>this</tt> CATPolyBoxf is intersecting a CATMathBox.
   * The test takes a given tolerance into account (the result is equivalent
   * to inflating one of the box of iTol and to compute IsIntersecting with
   * no tolerance.
   *<br> Note that if the intersection is a point or a line, the
   * result is true.
   */
  inline CATBoolean IsIntersecting(const CATMathBox &iBox, double iTol =0.) const;

  /**
	 * Returns TRUE if this CATMathBox
	 * is containing a CATMathPoint.
	 */
  inline CATBoolean IsContaining(const CATMathPoint &iPoint) const;

  /**
   * Returns the geometric volume included in <tt>this</tt> CATPolyBoxf.
   */
  double Volume() const ;

  /**
   * Replaces <tt>this</tt> CATPolyBoxf with the union of two
   * other CATPolyBoxf.
   */
  void SetToUnion(const CATPolyBoxf &iBox1, const CATPolyBoxf &iBox2);

  /**
   * Constructs a CATMathBox based on this CATPolyBoxf
   */
  inline CATMathBox GetMathBox() const;
  
  /**
   * Constructs a CATMathBox based on this CATPolyBoxf ( for performance )
   */
  INLINE void GetMathBox(CATMathBox & iBox) const;

  /**
   * Set the extremities from a CATMathBox
   */
  inline void SetBox(const CATMathBox &iBox);

  /**
	 * Modifies <tt>this</tt> CATPolyBoxf by adding a given thickness on each direction.
	 *<br>Hence,  the low extremity of the box becomes 
	 *(<tt>XMin-iThickness, YMin-iThickness, ZMin-iThickness</tt>) and the high
	 * extremity becomes
	 *(<tt>XMax+iThickness, YMax+iThickness, ZMax+iThickness</tt>).
	 *<br>This method does not apply on an empty box, but no error is thrown in this case.
	*/
	inline void Inflate(double iThickness);


private:
  polycoordstype _XMin, _YMin, _ZMin, _XMax, _YMax, _ZMax;
};

inline void CATPolyBoxf::AddInside(const CATMathPoint &iPointToAdd)
{
  if(_XMin > _XMax) // Empty
  {
    _XMax = (polycoordstype)iPointToAdd.GetX();
    _XMin = (polycoordstype)iPointToAdd.GetX();
    _YMax = (polycoordstype)iPointToAdd.GetY();
    _YMin = (polycoordstype)iPointToAdd.GetY();
    _ZMax = (polycoordstype)iPointToAdd.GetZ();
    _ZMin = (polycoordstype)iPointToAdd.GetZ();
    BOXF_PREV_FLOAT(_XMin);
    BOXF_NEXT_FLOAT(_XMax);
    BOXF_PREV_FLOAT(_YMin);
    BOXF_NEXT_FLOAT(_YMax);
    BOXF_PREV_FLOAT(_ZMin);
    BOXF_NEXT_FLOAT(_ZMax);
  }
  else
  {
    double X, Y, Z;
		iPointToAdd.GetCoord(X, Y, Z);
    if(_XMin > X)
    {
      _XMin = (polycoordstype)X;
      BOXF_PREV_FLOAT(_XMin);
    }
    else if(_XMax < X)
    {
      _XMax = (polycoordstype)X;
      BOXF_NEXT_FLOAT(_XMax);
    }
    if(_YMin > Y)
    {
      _YMin = (polycoordstype)Y;
      BOXF_PREV_FLOAT(_YMin);
    }
    else if(_YMax < Y)
    {
      _YMax = (polycoordstype)Y;
      BOXF_NEXT_FLOAT(_YMax);
    }

    if(_ZMin > Z)
    {
      _ZMin = (polycoordstype)Z;
      BOXF_PREV_FLOAT(_ZMin);
    }
    else if(_ZMax < Z)
    {
      _ZMax = (polycoordstype)Z;
      BOXF_NEXT_FLOAT(_ZMax);
    }
  }
}

inline void CATPolyBoxf::AddInside(const CATMathPointf &iPointToAdd)
{
  if(_XMin > _XMax) // Empty
  {
    _XMax = _XMin = iPointToAdd.x;
    _YMax = _YMin = iPointToAdd.y;
    _ZMax = _ZMin = iPointToAdd.z;
  }
  else
  {
    if(_XMin > iPointToAdd.x)
      _XMin = iPointToAdd.x;
    else if(_XMax < iPointToAdd.x)
      _XMax = iPointToAdd.x;

    if(_YMin > iPointToAdd.y)
      _YMin = iPointToAdd.y;
    else if(_YMax < iPointToAdd.y)
      _YMax = iPointToAdd.y;

    if(_ZMin > iPointToAdd.z)
      _ZMin = iPointToAdd.z;
    else if(_ZMax < iPointToAdd.z)
      _ZMax = iPointToAdd.z;
  }
}

inline CATBoolean CATPolyBoxf::IsIntersecting(const CATPolyBoxf &iBox, polycoordstype iTol) const
{
  if(_XMin > _XMax || iBox._XMin > iBox._XMax) // Empty
  {
    return FALSE;
  }
  return (_XMin <= iBox._XMax+iTol) && (iBox._XMin <= _XMax+iTol) &&
         (_YMin <= iBox._YMax+iTol) && (iBox._YMin <= _YMax+iTol) &&
         (_ZMin <= iBox._ZMax+iTol) && (iBox._ZMin <= _ZMax+iTol);
}

inline CATBoolean CATPolyBoxf::FastIsIntersecting(const CATPolyBoxf & iBox) const
{
  return (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax) &&
         (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax) &&
         (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax);
}

inline CATBoolean CATPolyBoxf::FastIsIntersecting(const CATPolyBoxf &iBox, polycoordstype iTol) const
{
  return (_XMin <= iBox._XMax+iTol) && (iBox._XMin <= _XMax+iTol) &&
         (_YMin <= iBox._YMax+iTol) && (iBox._YMin <= _YMax+iTol) &&
         (_ZMin <= iBox._ZMax+iTol) && (iBox._ZMin <= _ZMax+iTol);
}


inline CATPolyBoxf::IntersectionTestOrder CATPolyBoxf::GetAxisTestOrder () const
{
  const double xRange = _XMax - _XMin;
  const double yRange = _YMax - _YMin;
  const double zRange = _ZMax - _ZMin;
  if (xRange <= yRange)
  {
    if (yRange <= zRange)
      return XYZ;
    else if (xRange <= zRange)
      return XZY;
    else
      return ZXY;
  }
  else 
  {
    if (xRange <= zRange)
      return YXZ;
    else if (yRange <= zRange)
      return YZX;
    else
      return ZYX;
  }
}


inline CATBoolean CATPolyBoxf::UltraFastIsIntersecting(IntersectionTestOrder order, const CATPolyBoxf & iBox) const
{
  switch (order)
  {
    case XYZ:
      return (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax) &&
             (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax) &&
             (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax);
    case XZY:
      return (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax) &&
             (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax) &&
             (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax);
    case ZXY:
      return (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax) &&
             (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax) &&
             (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax);
    case ZYX:
      return (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax) &&
             (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax) &&
             (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax);
    case YXZ:
      return (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax) &&
             (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax) &&
             (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax);
    case YZX:
      return (_YMin <= iBox._YMax) && (iBox._YMin <= _YMax) &&
             (_ZMin <= iBox._ZMax) && (iBox._ZMin <= _ZMax) &&
             (_XMin <= iBox._XMax) && (iBox._XMin <= _XMax);
    default:
      return FALSE;
  }
}

inline CATBoolean CATPolyBoxf::IsContaining(const CATMathPoint & iPoint) const
{
  // return no if the box is empty
	if (_XMin > _XMax )
  {
    // Empty
		return FALSE;
  }

	return (iPoint.GetX() >= _XMin) && (iPoint.GetX() <= _XMax) &&
		     (iPoint.GetY() >= _YMin) && (iPoint.GetY() <= _YMax) &&
		     (iPoint.GetZ() >= _ZMin) && (iPoint.GetZ() <= _ZMax);
}

inline CATBoolean CATPolyBoxf::IsIntersecting(const CATMathBox &iBox, double iTol) const
{
  if(_XMin > _XMax || iBox.IsEmpty()) // Empty
  {
    return FALSE;
  }
  double ioXMin = 0., ioXMax = 0., ioYMin = 0., ioYMax = 0., ioZMin = 0., ioZMax = 0;
  iBox.GetLimits(ioXMin, ioXMax, ioYMin, ioYMax, ioZMin, ioZMax);
  polycoordstype ioXMaxf = (polycoordstype)(ioXMax+iTol);
  polycoordstype ioXMinf = (polycoordstype)(ioXMin-iTol);
  polycoordstype ioYMaxf = (polycoordstype)(ioYMax+iTol);
  polycoordstype ioYMinf = (polycoordstype)(ioYMin-iTol);
  polycoordstype ioZMaxf = (polycoordstype)(ioZMax+iTol);
  polycoordstype ioZMinf = (polycoordstype)(ioZMin-iTol);
  return (_XMin <= ioXMaxf) && (ioXMinf <= _XMax) &&
         (_YMin <= ioYMaxf) && (ioYMinf <= _YMax) &&
         (_ZMin <= ioZMaxf) && (ioZMinf <= _ZMax);
}

#ifndef POLY_USE_DOUBLE
inline HRESULT CATPolyBoxf::GetLimits(polycoordstype &ioXMin, polycoordstype &ioXMax,
                                      polycoordstype &ioYMin, polycoordstype &ioYMax,
                                      polycoordstype &ioZMin, polycoordstype &ioZMax) const
{
  if(_XMin > _XMax) // Empty
  {
    return E_FAIL;
  }
  ioXMin = _XMin;
  ioYMin = _YMin;
  ioZMin = _ZMin;
  ioXMax = _XMax;
  ioYMax = _YMax;
  ioZMax = _ZMax;
  return S_OK;
}
#endif
inline HRESULT CATPolyBoxf::GetLimits(double &ioXMin, double &ioXMax,
                                      double &ioYMin, double &ioYMax,
                                      double &ioZMin, double &ioZMax) const
{
  if(_XMin > _XMax) // Empty
  {
    return E_FAIL;
  }
  ioXMin = _XMin;
  ioYMin = _YMin;
  ioZMin = _ZMin;
  ioXMax = _XMax;
  ioYMax = _YMax;
  ioZMax = _ZMax;
  return S_OK;
}
inline void CATPolyBoxf::SetExtremities(const polycoordstype iXMin, const polycoordstype iXMax,
                                        const polycoordstype iYMin, const polycoordstype iYMax,
                                        const polycoordstype iZMin, const polycoordstype iZMax)
{
  _XMin = iXMin;
  _YMin = iYMin;
  _ZMin = iZMin;
  _XMax = iXMax;
  _YMax = iYMax;
  _ZMax = iZMax;
}

inline void CATPolyBoxf::SetToEmpty()
{
  _XMin = 1.f;
  _YMin = 1.f;
  _ZMin = 1.f;
  _XMax = -1.f;
  _YMax = -1.f;
  _ZMax = -1.f;
}

inline void CATPolyBoxf::Inflate(double Thickness)
{
  if(_XMin > _XMax) // Empty
  {
    return;
  }
	_XMin -= (polycoordstype)Thickness;
	_YMin -= (polycoordstype)Thickness;
	_ZMin -= (polycoordstype)Thickness;
	_XMax += (polycoordstype)Thickness;
	_YMax += (polycoordstype)Thickness;
	_ZMax += (polycoordstype)Thickness;
  BOXF_PREV_FLOAT(_XMin);
  BOXF_PREV_FLOAT(_YMin);
  BOXF_PREV_FLOAT(_ZMin);
  BOXF_NEXT_FLOAT(_XMax);
  BOXF_NEXT_FLOAT(_YMax);
  BOXF_NEXT_FLOAT(_ZMax);
}

inline void CATPolyBoxf::SetBox(const CATMathBox &iBox)
{
  _XMin = 1.f;
  _YMin = 1.f;
  _ZMin = 1.f;
  _XMax = -1.f;
  _YMax = -1.f;
  _ZMax = -1.f;
	if(!iBox.IsEmpty())
	{
    double ioXMin, ioXMax, ioYMin, ioYMax, ioZMin, ioZMax;
    iBox.GetLimits(ioXMin, ioXMax, ioYMin, ioYMax, ioZMin, ioZMax);
		_XMin = (polycoordstype)ioXMin;
		_XMax = (polycoordstype)ioXMax;
		_YMin = (polycoordstype)ioYMin;
		_YMax = (polycoordstype)ioYMax;
		_ZMin = (polycoordstype)ioZMin;
		_ZMax = (polycoordstype)ioZMax;
    BOXF_PREV_FLOAT(_XMin);
    BOXF_PREV_FLOAT(_YMin);
    BOXF_PREV_FLOAT(_ZMin);
    BOXF_NEXT_FLOAT(_XMax);
    BOXF_NEXT_FLOAT(_YMax);
    BOXF_NEXT_FLOAT(_ZMax);
	}
}

inline CATPolyBoxf::CATPolyBoxf(const CATPolyBoxf &Box)
{
  _XMin = 1.f;
  _YMin = 1.f;
  _ZMin = 1.f;
  _XMax = -1.f;
  _YMax = -1.f;
  _ZMax = -1.f;
	if(!Box.IsEmpty())
	{
		_XMin = Box._XMin;
		_XMax = Box._XMax;
		_YMin = Box._YMin;
		_YMax = Box._YMax;
		_ZMin = Box._ZMin;
		_ZMax = Box._ZMax;
	}
}

inline CATPolyBoxf::CATPolyBoxf(const CATMathBox &Box)
{
  SetBox(Box);
}

inline CATBoolean CATPolyBoxf::IsEmpty() const
{
  return (_XMin > _XMax);
}

inline double CATPolyBoxf::Volume() const 
{
	if(IsEmpty())
		return 0.;
	return (double(_XMax)-double(_XMin))*(double(_YMax)-double(_YMin))*(double(_ZMax)-double(_ZMin));
}

inline CATMathBox CATPolyBoxf::GetMathBox() const
{
  if(IsEmpty())
  {
    return CATMathBox();
  }
  return CATMathBox(_XMin, _XMax, _YMin, _YMax, _ZMin, _ZMax);
}

INLINE void CATPolyBoxf::GetMathBox(CATMathBox & iBox) const
{
  if(IsEmpty())
  {
    return iBox.SetToEmpty();
  }
  return iBox.SetExtremities(_XMin, _XMax, _YMin, _YMax, _ZMin, _ZMax);
}

inline void CATPolyBoxf::SetToUnion(const CATPolyBoxf &Box1,
                                    const CATPolyBoxf &Box2)
{
	if (Box1.IsEmpty())
	{
		*this = Box2;
		return;
	}
	if (Box2.IsEmpty())
	{
		*this = Box1;
		return;
	}

	_XMin = CATMin(Box1._XMin,Box2._XMin);
	_XMax = CATMax(Box1._XMax,Box2._XMax);
	_YMin = CATMin(Box1._YMin,Box2._YMin);
	_YMax = CATMax(Box1._YMax,Box2._YMax);
	_ZMin = CATMin(Box1._ZMin,Box2._ZMin);
	_ZMax = CATMax(Box1._ZMax,Box2._ZMax);
}

inline HRESULT CATPolyBoxf::GetHighLimit(CATMathPoint &HighPoint) const
{
	if(IsEmpty())
		return E_FAIL;

	HighPoint.SetCoord(_XMax, _YMax, _ZMax);
	return S_OK;
}

inline HRESULT CATPolyBoxf::GetLowLimit(CATMathPoint &LowPoint) const
{
	if(IsEmpty())
		return E_FAIL;
	LowPoint.SetCoord(_XMin, _YMin, _ZMin);
	return S_OK;
}

inline void CATPolyBoxf::AddInside(const CATPolyBoxf &Box)
{
	if (Box.IsEmpty())
	{
		return;
	}
	if(IsEmpty())
	{
		*this = Box;
		return;
	}
	// Assigns the extremities if necessary
	if (_XMin > Box._XMin)
	{
		_XMin = Box._XMin;
	}
	if (_XMax < Box._XMax)
	{
		_XMax = Box._XMax;
	}
	if (_YMin > Box._YMin)
	{
		_YMin = Box._YMin;
	}
	if (_YMax < Box._YMax)
	{
		_YMax = Box._YMax;
	}
	if (_ZMin > Box._ZMin)
	{
		_ZMin = Box._ZMin;
	}
	if (_ZMax < Box._ZMax)
	{
		_ZMax = Box._ZMax;
	}
}

inline void CATPolyBoxf::AddInside(const CATMathBox &Box)
{
	if (Box.IsEmpty())
	{
		return;
	}
	if(IsEmpty())
	{
		*this = CATPolyBoxf(Box);
		return;
	}
	// Assigns the extremities if necessary
  double iXMin, iXMax, iYMin, iYMax, iZMin, iZMax;
  Box.GetLimits(iXMin, iXMax, iYMin, iYMax, iZMin, iZMax);
	if (_XMin > iXMin)
	{
		_XMin = (polycoordstype)iXMin;
    BOXF_PREV_FLOAT(_XMin);
	}
	if (_XMax < iXMax)
	{
		_XMax = (polycoordstype)iXMax;
    BOXF_NEXT_FLOAT(_XMax);
	}
	if (_YMin > iYMin)
	{
		_YMin = (polycoordstype)iYMin;
    BOXF_PREV_FLOAT(_YMin);
	}
	if (_YMax < iYMax)
	{
		_YMax = (polycoordstype)iYMax;
    BOXF_NEXT_FLOAT(_YMax);
	}
	if (_ZMin > iZMin)
	{
		_ZMin = (polycoordstype)iZMin;
    BOXF_PREV_FLOAT(_ZMin);
	}
	if (_ZMax < iZMax)
	{
		_ZMax = (polycoordstype)iZMax;
    BOXF_NEXT_FLOAT(_ZMax);
	}
}

#endif

