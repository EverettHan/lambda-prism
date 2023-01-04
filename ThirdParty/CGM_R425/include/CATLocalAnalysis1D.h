#ifndef CATLocalAnalysis1D_H
#define CATLocalAnalysis1D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */

#include "CATIACGMLevel.h"

#include "Y30UIUTI.h"
#include <math.h>
#include "CATCurve.h"
#include "CATCrvParam.h"
#include "CATMathVector.h"

#include "CATCGMVirtual.h"
#include "CATCreateLocalAnalysisD.h"
class CATSoftwareConfiguration;

class CATLocalAnalysis1DImpl;

/**
 * Class defining the local analysis on a point of a CATCurve.
 *<br>It performs curvature, torsion,
 * main normal and binormal on a point of a CATCurve. This class is not streamable.
 * The point where the analysis is done can be changed by @href CATLocalAnalysis1D#SetParam.
 */
class ExportedByY30UIUTI CATLocalAnalysis1D : public CATCGMVirtual  
{
  CATCGMVirtualDeclareClass(CATLocalAnalysis1D);
    public :

/**
 * Creates a local analyzer on a point of a CATCurve.
 * @param iSupport
 * The curve on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 */    
     CATLocalAnalysis1D(const CATCurve                 * iSupport       ,
                        const CATCrvParam              & iPointToAnalyze);

/**
 * Creates a local analyzer on a point of a CATCurve.
 * @param iConfig
 * The level of code (Versionning).
 * @param iSupport
 * The curve on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 */    
     CATLocalAnalysis1D(      CATSoftwareConfiguration * iConfig,
                        const CATCurve                 * iSupport,
                        const CATCrvParam              & iPointToAnalyze);

/**
 * Destructor.
 */
     virtual ~CATLocalAnalysis1D() ;

/**
 * Copy Constructor.
 */
     CATLocalAnalysis1D(const CATLocalAnalysis1D& iAnalysisToCopy ) ;

/**
 * Assignment operator.
 */
     CATLocalAnalysis1D& operator = (const CATLocalAnalysis1D& iAnalysisToAffect ) ;

/**
 * Returns the curvature at the point of <tt>this</tt> CATLocalAnalysis1D.
 * @return
 * The curvature : the norm of the cross product of the first derivative and the second derivative 
 * divided by the cube of the norm of the first derivative.
 * <br><tt>Curvature = (FirstDeriv^SecondDeriv).Norm() / (FirstDeriv.Norm())^3</tt>.
 */    
     virtual double        GetCurvature()       ;

/**
 * Returns the torsion at the point of <tt>this</tt> CATLocalAnalysis1D.
 * @return
 * The torsion: Let <tt>V = FirstDeriv ^ SecondDeriv</tt>. Then,
 * <br><tt>Torsion = V*ThirdDeriv / V*V</tt>, where <tt>*</tt> is the dot product and <tt>^</tt> the cross 
 * product.
 */
     virtual double        GetTorsion()         ;

/**
 * Tests whether the point of <tt>this</tt> CATLocalAnalysis1D is regular.
 *<br>A point is non regular when the partial derivative of one of its coordinate 
 * is null.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt><tt> 0 </tt> <dd> if it is not regular
 *    <dt><tt> 1 </tt> <dd> if it is regular</dl>
 */
     virtual CATLONG32     IsARegularParam()    ;

/**
 * Returns the main normal at the point of <tt>this</tt> CATLocalAnalysis1D.
 * @return
 * The main normal: Let <tt>V = FirstDeriv ^ SecondDeriv</tt>. Then,
 * <br><tt>MainNormal = (V / V.Norm() ) ^ FirstDeriv / FirstDeriv.Norm() </tt>, where <tt>^</tt> is the cross 
 * product.
 */
     virtual CATMathVector GetMainNormal()      ;

/**
 * Returns the binormal at the point of <tt>this</tt> CATLocalAnalysis1D.
 * @return
 * The binormal: Let <tt>V = FirstDeriv ^ SecondDeriv</tt>. Then,
 * <br><tt>BiNormal = V / V.Norm() </tt>, where <tt>^</tt> is the cross 
 * product.
 */
     virtual CATMathVector GetBiNormal()        ;

/**
 * Modifies the point where <tt>this</tt> CATLocalAnalysis1D is performed.
 *<br>The analysis is automatically done.
 * @param iNewParamToAnalyze
 * The parameter of the new point to analyze.
 */
     virtual void          SetParam(CATCrvParam& iNewParamToAnalyze)     ;
    
    protected :

/** @nodoc */
     virtual void          AreFirstAndSecondDerivOK();

     const CATCurve                 * Curve_ptr ;
           CATCrvParam                Param    ;
           CATMathVector              FirstDeriv,  SecondDeriv,  ThirdDeriv ;
           CATLONG32                  F_FirstDeriv, F_SecondDeriv, F_ThirdDeriv;
           CATSoftwareConfiguration * _Config;

           CATLocalAnalysis1DImpl   * _LocalAnal1DOpe;
};
    
#endif 
