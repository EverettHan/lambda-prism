// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCurveSupport.h
//
//===================================================================
// March 2010  Creation: NDO
// December 2018  Update JXO: GetID
//===================================================================
#ifndef CATPolyMathCurveSupport_H
#define CATPolyMathCurveSupport_H

#include "PolySupports.h"
#include "CATIPolyCurveSupport.h"
#include "CATBoolean.h"

class CATIPolyCurve;


class ExportedByPolySupports CATPolyMathCurveSupport : public CATIPolyCurveSupport
{

public:

  /**
   * Constructs a CATPolyMathCurveSupport by absorption of CATPolyMathCurve.
   */
  inline static CATPolyMathCurveSupport* New (CATPolyMathCurve* iMathCurve);

  CATIPolySupport* Clone () const;

public:

  static const CATPolyMathCurveSupport* Cast (const CATIPolyLayer*);
  static CATPolyMathCurveSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  virtual Type GetType () const;

  /**
   * Casts the support as a CATPolyMathCurveSupport.
   */
  const CATPolyMathCurveSupport* CastAsMathCurve () const;

  /**
   * Casts the support as a CATPolyMathCurveSupport.
   */
  CATPolyMathCurveSupport* CastAsMathCurve ();

public:

  /**
   * Returns the math Curve.  
   * The returned object should not be released.
   */
  inline const CATPolyMathCurve* GetCurve () const;

  /**
   * Returns the math Curve.  
   * The returned object should not be released.
   */
  inline CATPolyMathCurve* GetCurve ();

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
  virtual HRESULT GetID (unsigned int& oID) const;

public:

  HRESULT GetNewMathCurve (CATPolyMathCurve*& oCurve) const;

private:

	CATPolyMathCurve* _MathCurve;
  unsigned int _ID;

protected:

  virtual ~CATPolyMathCurveSupport ();

public:  // Should be private.
//private:

  inline CATPolyMathCurveSupport (CATPolyMathCurve* iMathCurve = 0);  // Absorbs CATPolyMathCurve (destructor releases it.)

};

inline CATPolyMathCurveSupport::CATPolyMathCurveSupport (CATPolyMathCurve* iMathCurve) :
  _MathCurve (iMathCurve), _ID(0)
{
}

inline CATPolyMathCurveSupport* CATPolyMathCurveSupport::New (CATPolyMathCurve* iMathCurve)
{
  return iMathCurve ? new CATPolyMathCurveSupport (iMathCurve) : 0;
}

inline const CATPolyMathCurve* CATPolyMathCurveSupport::GetCurve () const
{
  return _MathCurve;
}

inline CATPolyMathCurve* CATPolyMathCurveSupport::GetCurve ()
{
  return _MathCurve;
}

inline void CATPolyMathCurveSupport::SetID (const unsigned int id)
{
  _ID = id;
}

inline unsigned int CATPolyMathCurveSupport::GetID () const
{
  return _ID;
}

#endif // !CATPolyMathCurveSupport_H
