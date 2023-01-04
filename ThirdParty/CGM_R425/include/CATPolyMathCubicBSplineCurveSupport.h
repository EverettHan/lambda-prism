// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCubicBSplineCurveSupport.h
//
//===================================================================
// March 2009  Creation: TPG
//===================================================================
#ifndef CATPolyMathCubicBSplineCurveSupport_H
#define CATPolyMathCubicBSplineCurveSupport_H

#include "PolySupports.h"
#include "CATPolyMathCurveSupport.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

class CATPolyMathCubicBSplineCurve;
class CATPolyCubicBSplineSurfaceSupport;


class ExportedByPolySupports CATPolyMathCubicBSplineCurveSupport : public CATPolyMathCurveSupport
{

public:

  // from CATPolyMathCubicBSplineCurve
  CATPolyMathCubicBSplineCurveSupport (const CATPolyMathCubicBSplineCurve * iMathCubicBSplineCurve);

  // from CATPolyCubicBSplineSurfaceSupport
  //  
  //                              CubicBSplineSurface                      
  //                              ------------------                     
  //
  //                      A         Side 3
  //               v [j] /  Corner4             Corner3                          
  //                    /    x-----x-----x-----x 
  //                        /     /     /     /                
  //                       /     /     /     /               
  //                      x---P[1][2]-x-----x                
  //                     /     /     /     /                 
  //            Side 4  /     /     /     /  Side 2                  
  //                   x-----x-----x-----x               
  //                  /     /     /     /                
  //                 /_____/____ /_____/                  
  //             Corner1               Corner2
  //                        Side 1     --> u [i]
  //
  // iSide : 1,2,3,4 (see figure above)
  CATPolyMathCubicBSplineCurveSupport (const CATPolyCubicBSplineSurfaceSupport * iSurfaceSupport, int iSide);

  virtual ~CATPolyMathCubicBSplineCurveSupport ();

public:

  static const CATPolyMathCubicBSplineCurveSupport* Cast (const CATIPolyLayer*);
  static CATPolyMathCubicBSplineCurveSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  Type GetType () const;
  const CATPolyMathCubicBSplineCurveSupport* CastAsCubicBSplineCurve () const;

  /*
   * Return a CATPolyMathCurve.  The object returned is not supposed to be deleted.
   * Its life cycle is managed by this class.
   */
  HRESULT GetMathCurve (const CATPolyMathCurve*& oCurve) const;
  HRESULT GetMathCurve (CATPolyMathCurve*& oCurve);

  inline const CATPolyMathCubicBSplineCurve * GetMathCubicBSplineCurve () const;

public:

  // Make a copy of itself.  Instance is to be deleted.
  CATIPolySupport* Clone () const;

private:

  CATPolyMathCubicBSplineCurve* _MathCubicBSplineCurve;

};

inline const CATPolyMathCubicBSplineCurve * CATPolyMathCubicBSplineCurveSupport::GetMathCubicBSplineCurve () const
{
  return _MathCubicBSplineCurve;
}

#endif // !CATPolyMathCubicBSplineCurveSupport_H
