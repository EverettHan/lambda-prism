// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurfaceSupport.h
//
//===================================================================
// March 2010  Creation: NDO
// December 2018  Update JXO: GetID
//===================================================================
#ifndef CATPolyMathSurfaceSupport_H
#define CATPolyMathSurfaceSupport_H

#include "PolySupports.h"
#include "CATIPolySurfaceSupport.h"
#include "CATBoolean.h"

class CATIPolySurface;


class ExportedByPolySupports CATPolyMathSurfaceSupport : public CATIPolySurfaceSupport
{

public:

  /**
   * Constructs a CATPolyMathSurfaceSupport by absorption of CATPolyMathSurface.
   */
  inline static CATPolyMathSurfaceSupport* New (CATPolyMathSurface* iMathSurface);

  /**
   * Constructs a CATPolyMathSurfaceSupport by absorption of CATPolyMathSurface.
   * During the construction, it computes the orientation of the support and check if the surface is trimmed along isopars.
   */
  static CATPolyMathSurfaceSupport* New (const CATIPolySurface& iPolySurface, CATPolyMathSurface* iMathSurface);

  CATIPolySupport* Clone () const;

public:

  static const CATPolyMathSurfaceSupport* Cast (const CATIPolyLayer*);
  static CATPolyMathSurfaceSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  /**
   * Gets the type of the support.
   */
  virtual Type GetType () const;

  /**
   * Casts the support as a CATPolyMathSurfaceSupport.
   */
  const CATPolyMathSurfaceSupport* CastAsMathSurface () const;

  /**
   * Casts the support as a CATPolyMathSurfaceSupport.
   */
  CATPolyMathSurfaceSupport* CastAsMathSurface ();

public:

  /**
   * Returns TRUE is the surface support is planar and FALSE otherwise.
   */
  virtual CATBoolean IsPlanar () const;

public:

  HRESULT GetMathSurface (const CATPolyMathSurface*& oSurface) const;
	HRESULT GetMathSurface (CATPolyMathSurface*& oSurface);

  /**
   * Returns the math surface.
   * The returned object should not be released.
   */
  inline const CATPolyMathSurface* GetSurface () const;

  /**
   * Returns the math surface.
   * The returned object should not be released.
   */
  inline CATPolyMathSurface* GetSurface ();

public:

  /**
   * Sets an ID to the support.
   */
  inline void SetID (const unsigned int id);

  /**
   * Gets the ID from the support.
   */
  inline unsigned int GetID () const;

  /**
   * Gets the ID or CGM ID associated to the support if available.
   * The method returns S_FALSE if no ID is available and S_OK if an ID is available.
   */
  HRESULT GetID (unsigned int& oID) const;

  /**
   * Sets the orientation of the support.
   * @param iOrientation
   *   Valid argument value is:
   *   <ul>
   *      <li> +1: Positive
   *      <li>  0: Undefined
   *      <li> -1: Negative
   *   </ul>
   */
  inline void SetOrientation (const int iOrientation);

  /**
   * Returns the orientation of the support.
   * @return
   *   <ul>
   *      <li> +1: Positive
   *      <li>  0: Undefined
   *      <li> -1: Negative
   *   </ul>
   */
  inline int GetOrientation () const;

  /**
   * If the surface is trimmed along isoparametric curves only along its outer boundary, then the method
   * returns the isopar limits and <tt>S_OK</tt>; otherwise it returns <tt>S_FALSE</tt>.
   * The isopar limits define the range of the <tt>u</tt> and <tt>v</tt> parameters that can be applied
   * to the Evaluate methods to compute coordinates of points and normals to the surface.
   * @param uMin
   *   The output lower limit of the isopars.
   * @param uMax
   *   The output upper limit of the isopars.
   * @param vMin
   *   The output lower limit of the isopars.
   * @param vMax
   *   The output upper limit of the isopars.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the surface is trimmed along isopars. (No inner boundaries.)
   *   <li> <tt>S_FALSE</tt> otherwise.
   * </ul>
   */
  inline HRESULT GetIsoparLimits (double& uMin, double& uMax, double& vMin, double& vMax) const;
  /**
   * Indicates if the surface is trimmed along isoparametric curves
   * only along its outer boundary.
   */
  inline CATBoolean HasIsoparLimits() const;

  /**
   * Sets the isopar limits.
   */
  inline void SetIsoparLimits (const double uMin, const double uMax, const double vMin, const double vMax);

public:

  HRESULT GetNewMathSurface (CATPolyMathSurface*& oSurface) const;

private:

  CATPolyMathSurface* _MathSurface;

  unsigned int _ID;
  int _Orientation;

  double _UMin;
  double _UMax;
  double _VMin;
  double _VMax;

protected:

  virtual ~CATPolyMathSurfaceSupport ();

public:  // Should be private.
//private:

  inline CATPolyMathSurfaceSupport (CATPolyMathSurface* iMathSurface = 0);  // Absorbs CATPolyMathSurface (destructor releases it.)

};

inline CATPolyMathSurfaceSupport::CATPolyMathSurfaceSupport (CATPolyMathSurface* iMathSurface) :
  _MathSurface (iMathSurface),
  _ID (0),
  _Orientation (0),
  _UMin (1),
  _UMax (-1),
  _VMin (1),
  _VMax (-1)
{
}

inline CATPolyMathSurfaceSupport* CATPolyMathSurfaceSupport::New (CATPolyMathSurface* iMathSurface)
{
  return iMathSurface ? new CATPolyMathSurfaceSupport (iMathSurface) : 0;
}

inline const CATPolyMathSurface* CATPolyMathSurfaceSupport::GetSurface () const
{
  return _MathSurface;
}

inline CATPolyMathSurface* CATPolyMathSurfaceSupport::GetSurface ()
{
  return _MathSurface;
}

inline void CATPolyMathSurfaceSupport::SetID (const unsigned int id)
{
  _ID = id;
}

inline unsigned int CATPolyMathSurfaceSupport::GetID () const
{
  return _ID;
}

inline void CATPolyMathSurfaceSupport::SetOrientation (const int iOrientation)
{
  if (iOrientation > 0)
    _Orientation = +1;
  else if (iOrientation > 0)
    _Orientation = -1;
  else
    _Orientation = 0;
}

inline int CATPolyMathSurfaceSupport::GetOrientation () const
{
  return _Orientation;
}


inline HRESULT CATPolyMathSurfaceSupport::GetIsoparLimits (double& uMin, double& uMax, double& vMin, double& vMax) const
{
  if (_UMin <= _UMax && _VMin <= _VMax)
  {
    uMin = _UMin;
    uMax = _UMax;
    vMin = _VMin;
    vMax = _VMax;
    return S_OK;
  }
  return S_FALSE;
}

inline CATBoolean CATPolyMathSurfaceSupport::HasIsoparLimits() const
{
  return ((_UMin <= _UMax) && (_VMin <= _VMax)) ? TRUE : FALSE;
}

inline void CATPolyMathSurfaceSupport::SetIsoparLimits (const double uMin, const double uMax, const double vMin, const double vMax)
{
  _UMin = uMin;
  _UMax = uMax;
  _VMin = vMin;
  _VMax = vMax;
}

#endif // !CATPolyMathSurfaceSupport_H
