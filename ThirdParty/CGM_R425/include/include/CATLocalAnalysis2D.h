#ifndef CATLocalAnalysis2D_H
#define CATLocalAnalysis2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y30UIUTI.h"

class CATSurface;
class CATMathDirection2D;
#include "CATSurParam.h"
#include "CATMathVector.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

//#ifdef CATIAV5R14
#include "CATCreateLocalAnalysisD.h"
class CATSoftwareConfiguration;
//#endif

class CATLocalAnalysis2DImpl;

/**
 * Class defining the local analysis on a point of a CATSurface.
 *<br>It performs curvature, torsion,
 * main normal and binormal on a point of a CATSurface. This class is not streamable.
 * The point where the analysis is done can be changed by @href CATLocalAnalysis2D#SetParam.
 */
class ExportedByY30UIUTI CATLocalAnalysis2D : public CATCGMVirtual
{
   CATCGMVirtualDeclareClass(CATLocalAnalysis2D);
public :
   /**
   * Creates a local analyzer on a point of a CATSurface.
   * @param iSupport
   * The surface on which the analysis is done.
   * @param iPointToAnalyze
   * The parameter on <tt>iSupport</tt> of the point to analyze.
   */   
   CATLocalAnalysis2D (const CATSurface               *  iSurface       ,
                       const CATSurParam               & iPointToAnalyze);
   
   //#ifdef CATIAV5R14
   /**
   * Creates a local analyzer on a point of a CATSurface.
   * @param iConfig
   * The level of code (Versionning).
   * @param iSupport
   * The surface on which the analysis is done.
   * @param iPointToAnalyze
   * The parameter on <tt>iSupport</tt> of the point to analyze.
   */   
   CATLocalAnalysis2D (      CATSoftwareConfiguration *  iConfig        ,
                       const CATSurface               *  iSurface       ,
                       const CATSurParam               & iPointToAnalyze);
   //#endif
   
   /**
   * Destructor.
   */
   virtual ~CATLocalAnalysis2D () ;
   
   /**
   * Copy Constructor.
   */
   CATLocalAnalysis2D (const CATLocalAnalysis2D &iAnalysisToCopy ) ;
   
   /**
   * Assignment operator.
   */
   CATLocalAnalysis2D& operator=(const CATLocalAnalysis2D &iAnalysisToAffect) ;
   
   /**
   * Retrieves the first fondamental form at the point of <tt>this</tt> CATLocalAnalysis2D.
   * @param ioE
   * The first coordinate: <tt>ioE = FirstDerivU.Norm() ^ 2</tt>, where <tt>FirstDerivU</tt> is
   * the first derivative with regards to the first parameter.
   * @param ioF
   * The second coordinate: <tt>ioF = FirstDerivU * FirstDerivV</tt>, where <tt>*</tt> is the dot product.
   * @param ioE
   * The third coordinate: <tt>ioG = FirstDerivV.Norm() ^ 2</tt>, where <tt>FirstDerivV</tt> is
   * the first derivative with regards to the second parameter.
   */ 	 
   virtual void    GetFirstFundamentalForm (double &ioE, double &ioF, double &ioG);
   
   /**
   * Retrieves the second fondamental form at the point of <tt>this</tt> CATLocalAnalysis2D.
   * <br>Let <tt>H = (FirstDerivU ^ FirstDerivV) / (FirstDerivU ^ FirstDerivV).Norm()</tt>.
   * @param ioL
   * The first coordinate: <tt>ioL = SecondDerivU2 * H</tt>, where <tt>SecondDerivU2</tt> is
   * the second derivative with regards to the first parameter and <tt>*</tt> the dot product.
   * @param ioM
   * The second coordinate: <tt>ioM = SecondDerivUV * H</tt>,  where <tt>SecondDerivUV</tt> is
   * the second derivative with regards to the first parameter and second parameters, 
   * and <tt>*</tt> the dot product.
   * @param ioN
   * The third coordinate: <tt>ioN = SecondDerivU2 * H</tt>,  where <tt>SecondDerivV2</tt> is
   * the second derivative with regards to the second parameter and <tt>*</tt> the dot product.
   */
   virtual void    GetSecondFundamentalForm (double &ioL, double &ioM, double &ioN);
   
   /**
   * Returns the gaussian curvature at the point of <tt>this</tt> CATLocalAnalysis2D.
   * @return
   * The Gaussian curvature = <tt>Cmin*Cmax</tt>, where <tt>Cmin</tt> is the minium curvature
   * and <tt>Cmax</tt> the maximum curvature at the point of <tt>this</tt> analysis.
   */
   virtual double  GetGaussianCurvature ();
   
   /**
   * Returns the mean curvature at the point of <tt>this</tt> CATLocalAnalysis2D.
   * @return
   * The mean curvature: <tt> = 0.5*(Cmin+Cmax) </tt>.
   */
   virtual double  GetMeanCurvature ();
   
   /**
   * Returns the min and max curvatures at the point of <tt>this</tt> CATLocalAnalysis2D.
   * @param ioCmin
   * The minimum curvature.
   * @param ioCmax
   * The maximum curvature: <tt>ioCmin < ioCmax</tt>.
   *  .
   */
   virtual void  GetMinMaxCurvature (double & ioCmin, double & ioCmax);
   
   //#ifdef CATIAV5R13
   /**
   * Returns the min and max curvatures at the point of <tt>this</tt> CATLocalAnalysis2D,
   * along with the associated principal curvature directions.
   * The returned 3d and 2d vectors represent directions: no assumption can be made
   * regarding the orientation of the vectors. Likewise, the directions are unspecified
   * at umbilical points (when min curvature = max curvature).
   * @param ioCmin
   * The minimum curvature.
   * @param ioCmax
   * The maximum curvature: <tt>ioCmin < ioCmax</tt>.
   * @param ioDirMin2D
   * The principal curvature direction associated to the minimal curvature,
   * expressed as a linear combination of the partial derivatives.
   * @param ioDirMax2D
   * The principal curvature direction associated to the maximal curvature.
   * expressed as a linear combination of the partial derivatives.
   * @param ioDirMin3D
   * The principal curvature direction associated to the minimal curvature,
   * expressed in 3D.
   * @param ioDirMax3D
   * The principal curvature direction associated to the maximal curvature,
   * expressed in 3D.
   *  .
   */
   virtual void GetMinMaxCurvaturesAndDirections
      (double & ioCmin, double & ioCmax, CATMathVector2D & ioDirMin2D, CATMathVector2D & ioDirMax2D,
       CATMathVector & ioDirMin3D, CATMathVector & ioDirMax3D);
   //#endif
   
   /**
   * Returns the curvature along a direction of the surface.
   * @param iX
   * The first coordinate of the direction in the space of the surface.
   * @param iY
   * The second coordinate of the direction in the space of the surface.
   * @return 
   * The curvature.
   * <tt>C(iX,iY) = (L.iX^2 + 2M.iX.iY + N.iY^2) / (E.iX^2 + 2F.iX.iY + G.iY^2)</tt>, where <tt>L,M,N</tt> are
   * the coordinates of the second fundamental form and <tt>E, F, G</tt> the coordinates of the
   * first fundamental form
   */
   virtual double  GetCurvatureAlongDirection (const double &iX, const double &iY);
   
   /**
   * Returns the 2D coordinates of the projection of the 3d vector <tt>iVector</tt> on the
   * surface. 
   * <br> These coordinates are such that: <tt>iVector = ioX*FirstDerivU + ioY*FirstDerivV</tt>,
   * where <tt>FirstDerivU</tt> and <tt>FirstDerivV</tt> are the first derivatives with respect to
   * the first and second surface parameters, and <tt>*</tt> is the dot product.
   * @param ioX
   * The coordinate along the first derivative with regards to the first surface parameter.
   * @param ioY
   * The coordinate along the first derivative with regards to the second surface parameter.
   * @return
   * The regularity of the point.
   *<dl><dt><tt> 0 </tt> <dd> if it is not regular (<tt>ioX</tt> and <tt>ioY</tt> are not calculated)
   *    <dt><tt> 1 </tt> <dd> if it is regular</dl>
   */
   virtual CATLONG32 ProjectVector (CATMathVector & iVector, double &ioX, double &ioY);
   
   /**
   * @nodoc
   * "Small" (=resolution) modification of the point <tt>iPar</tt> on the surface, the modified
   * point is <tt>ioPar</tt>.
   */
   virtual void MovePoint (const CATSurParam & iPar, CATSurParam & ioPar) ;
   
   /**
   * Tests whether the point of <tt>this</tt> CATLocalAnalysis2D is regular.
   *<br>A point is non regular when the partial derivative of one of its coordinate 
   * is null.
   * @return
   * The result of the test.
   * <br><b>Legal values</b>:
   *<dl><dt><tt> 0 </tt> <dd> if it is not regular
   *    <dt><tt> 1 </tt> <dd> if it is regular</dl>
   */
   virtual CATLONG32 IsARegularParam ()    ;
   
   /**
   * Modifies the point where <tt>this</tt> CATLocalAnalysis2D is performed.
   *<br>The analysis is automatically done.
   * @param iNewParamToAnalyze
   * The parameter of the new point to analyze.
   */
   virtual void SetParam (const CATSurParam &iNewParamToAnalyze) ;
   
protected :
   /** @nodoc */
   virtual void AreFirstAndSecondDerivOK ();
   /** @nodoc */
   const CATSurface               * _Surface;
   /** @nodoc */
         CATSurParam                _Param;
   /** @nodoc */
         CATMathVector              _DU,
                                    _DV,
                                    _DU2,
                                    _DUDV,
                                    _DV2;
   /** @nodoc */
         CATLONG32                  _FirstDeriv,
                                    _SecondDeriv;
   //#ifdef CATIAV5R14
         CATSoftwareConfiguration * _Config;
   //#endif
         CATLocalAnalysis2DImpl   * _LocalAnal2DOpe;
};
    
#endif 
