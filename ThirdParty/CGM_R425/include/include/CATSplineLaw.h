#ifndef CATSplineLaw_h
#define CATSplineLaw_h
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATLaw.h"
#include "CATMathDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSplineLaw ;
#else
extern "C" const IID IID_CATSplineLaw ;
#endif

/**
 * Interface representing a linear law.
 *<br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
 * <tt>[iTmin,iTmax]</tt>. A spline law is a spline interpolation function between points with
 * imposed tangents.
 */
class ExportedByCATGMGeometricInterfaces CATSplineLaw : public CATLaw
{
  CATDeclareInterface;

public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Returns the constraint parameters.
 * <br>The internal values are copied into the output array.
 * @param ioNumberOfConstraints
 * The index (beginning at <tt>0</tt>) of the constraint parameter.
 * @param oT
 * The array of the constraint parameter values. The array is allocated by the method, and
 * must be deallocated by the caller. If <tt>ioNumberOfConstraints==0</tt>, the array is not
 * allocated.
 * @param oValue
 * The array of the corresponding law values. The array is allocated by the method, and
 * must be deallocated by the caller. If <tt>ioNumberOfConstraints==0</tt>, the array is not
 * allocated.
 */
  virtual void GetConstraints (CATLONG32 & ioNbrOfConstraint,
			       double * &oT,
			       double * &oValue) const = 0;  

 /**
 * Returns the a constraint parameter.
 * @param iIndex
 * The index (beginning at <tt>0</tt>) of the constraint parameter.
 * @param ioT
 * The constraint parameter value. 
 * @param oValue
 * The corresponding law value.
 */
  virtual void GetOneConstraint (const CATLONG32 iIndex,
				 double & ioT,
				 double & ioValue) const = 0 ;










  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //-------------------------------------------------------------------------
  //- Read whether the Constraint has Slope defined.
  // If yes, gives the Slope.   
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual CATBoolean HasSlopeDefined(const CATLONG32 iIndex,
				     double & oSlope) const =0 ;
  //-------------------------------------------------------------------------
  //- Read whether the Constraint has SecondDerivative defined.
  // If yes, gives the SecondDerivative.   
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual CATBoolean HasSecondDerivativeDefined(const CATLONG32 iIndex,
				     double & oSecondDerivative) const =0 ;

  //-------------------------------------------------------------------------
  //- Change one Constraint.
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual void SetConstraint (const CATLONG32   iIndex,
			      const double iNewT,
			      const double iNewValue) = 0 ;

  //-------------------------------------------------------------------------
  //- Change one parameter.
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual void SetParameter (const CATLONG32   iIndex,
			     const double iNewT) = 0 ;

  //-------------------------------------------------------------------------
  //- Change one Value.
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual void SetValue (const CATLONG32   iIndex,
			 const double iNewValue) = 0 ;

  //-------------------------------------------------------------------------
  //- Change one Slope.
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual void SetSlope (const CATLONG32   iIndex,
			 const double iNewSlope) = 0 ;

  //-------------------------------------------------------------------------
  //- Change one SecondDerivative.
  //-------------------------------------------------------------------------
			/** @nodoc */
  virtual void SetSecondDerivative (const CATLONG32   iIndex,
			 const double iNewSecondDerivative) = 0 ;

  //-------------------------------------------------------------------------
  //- Insert a new Constraint.
  // Returns the index of this Constraint. 
  //-------------------------------------------------------------------------
		/** @nodoc */
  virtual CATLONG32 InsertConstraint (const double iNewT,
				 const double iNewValue) = 0;

  //-------------------------------------------------------------------------
  //- Remove a Constraint (and Slope and SecondDerivative if defined)
  //-------------------------------------------------------------------------
		/** @nodoc */
  virtual void RemoveConstraint (const CATLONG32 iIndex) = 0 ;

  //-------------------------------------------------------------------------
  //- Remove a Slope.
  //-------------------------------------------------------------------------
		/** @nodoc */
  virtual void RemoveSlope (const CATLONG32 iIndex) = 0 ;

  //-------------------------------------------------------------------------
  //- Remove a SecondDerivative.
  //-------------------------------------------------------------------------
		/** @nodoc */
  virtual void RemoveSecondDerivative (const CATLONG32 iIndex) = 0 ;

  //-------------------------------------------------------------------------
  //- Read whether the Law is closed.
  //-------------------------------------------------------------------------  
	/** @nodoc */
  virtual CATBoolean IsClosed() const = 0;

  //-------------------------------------------------------------------------
  //- Change the closure attribute.
  // iClosureAttribute = 0 --> open law
  // iClosureAttribute = 1 --> closed law
  //-------------------------------------------------------------------------  
	/** @nodoc */
  virtual void SetClosureAttribute(const CATLONG32 iClosureAttribute = 1) = 0;

};
CATDeclareHandler(CATSplineLaw,CATLaw);

#endif

