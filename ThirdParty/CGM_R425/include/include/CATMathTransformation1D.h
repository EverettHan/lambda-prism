#ifndef CATMathTransformation1D_H
#define CATMathTransformation1D_H
// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"
#include "CATMathInline.h"
#include "CATIACGMLevel.h"
#include "CATErrorDef.h"
/**
 * Class defining a transformation in a 1D space.
 * <br><tt> t(x) = a*x + b</tt>.
 */
class  ExportedByCATMathematics CATMathTransformation1D
{
public:
	//---------------------------------------------------------------------------
	//- Constructor
	//---------------------------------------------------------------------------
  /**
   * Constructs the identity 1D transformation.
   * <br><tt>t(x) = x </tt>.
   */
  CATMathTransformation1D();
  /**
   * Constructs a 1D transformation.
   * <br><tt> t(x) = iA*x + iB</tt>.
   * @param iA
   * The scale coefficient.
   * @param iB
   * The shift coefficient.
   */
  CATMathTransformation1D(double iA, double iB);

  /**
   * Constructs a 1D transformation.
   * <br><tt> t(x) = iArray[0]*x + iArray[1]</tt>.
   * @param iArray
   * The array of the scale and shift coefficient.
   */
  CATMathTransformation1D(double *iArray);

  /**
   * Copy constructor.
   */
  CATMathTransformation1D(const CATMathTransformation1D &iTransfo1DToCopy);

  //---------------------------------------------------------------------------
  //- Set
  //---------------------------------------------------------------------------

  /** 
  * @deprecated V5R20 Set
  * Creates the linear transformation that transforms <tt>ix0</tt> into <tt>ifx0</tt> 
  * and <tt>ix1</tt> into <tt>ifx1</tt>. 
  * <br><tt>ix0</tt> must be different from <tt>ix1</tt>, but this is not checked.
  */
  CATMathTransformation1D(const double iX0, const double iFx0,
                          const double iX1, const double iFx1);

 /** 
  * Creates the linear transformation that transforms <tt>iX0</tt> into <tt>iFx0</tt> 
  * and <tt>iX1</tt> into <tt>iFx1</tt>. 
  * @param iX0
  * Double.
  * @param iFx0
  * Image of <tt>iX0</tt>  by the requested transformation.
  * @param iX1
  * Double.
  * @param iFx1
  * Image of <tt>iX1</tt>  by the requested transformation.
  * @return
  * <tt>E_FAIL</tt> if <tt>iX0</tt> is equal to <tt>iX1</tt> but not <tt>iFx0</tt> and <tt>iFx1</tt>, 
  * otherwise <tt>S_OK</tt>
  * In case of failure, the computed transformation is the identity.
  */
   HRESULT Set(const double iX0, const double iFx0,
                          const double iX1, const double iFx1);

#ifndef CATIACGMV5R23
  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  ~CATMathTransformation1D();
#endif

  //---------------------------------------------------------------------------
  //- Write
  //---------------------------------------------------------------------------
  /**
   * Modifies the coefficients.
   * @param iNewCoef
   * The array of the new coefficients.
   */
  void SetCoef(const double iNewCoef[]);

  //---------------------------------------------------------------------------
  //- Read--
  //-------------------------------------------------------------------------
  /**
   * Retrieves the coefficients.
   * @param ioCoef
   * The array (that must be already allocated).
   * <br><tt> t(x) = ioCoef[0]*x + ioCoef[1]</tt>.
   */
  void GetCoef(double ioCoef[]) const;

  /**
   * Returns the scale coefficient.
   * @return
   * The scale coefficient.
   */
#ifdef CATIACGMV5R23
  INLINE double GetMatrix1D() const;
#else
  double GetMatrix1D() const;
#endif

  /**
   * Returns the shift coefficient.
   * @return
   * The shift coefficient.
   */
#ifdef CATIACGMV5R23
  INLINE double GetVector1D() const;
#else
  double GetVector1D() const;
#endif

  /** 
  * Transforms a double.
  * @param iParamToTransform
  * The double to transform.
  * @return
  * The result of the transformation.
  */
  double Apply(double iParamToTransform) const;

  //---------------------------------------------------------------------------
  //- Overloaded operators
  //---------------------------------------------------------------------------
  /** 
   * Returns the composition of two 1D transformations.
   * @param it1
   * The first transformation.
   * @param it2
   * The second transformation.
   * @return
   * <br><tt>transfo.a = it1.a * it2.a;
   *         transfo.b = it1.a * it2.b + it1.b;</tt>
  */
  friend ExportedByCATMathematics CATMathTransformation1D operator * 
			(const CATMathTransformation1D &it1, const CATMathTransformation1D &it2);

private:

  double a;
  double b;
};

#ifdef CATIACGMV5R23
//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

//------------------------------------------------------------------------------
INLINE double CATMathTransformation1D::GetMatrix1D() const
//------------------------------------------------------------------------------
{
	return (a);
}
//------------------------------------------------------------------------------
INLINE double CATMathTransformation1D::GetVector1D() const
//------------------------------------------------------------------------------
{
	return (b);
}
#endif

#endif
