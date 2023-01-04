// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CGMVswpRotation_H
#define CGMVswpRotation_H

#include "CATGMModelInterfaces.h"

#include "CATMath.h"
#include "CATMathDirection.h"

#include "CGMVswpMatrix.h"

#include "CATCGMContractAssert.h"

class CATTolerance;
class VswpUnitQuaternion;

typedef VswpMatrix3x3 VswpRotationMatrix;

// Rotatioin defined abOut an axis. 

class VswpRotationVector 
{
public:

	VswpRotationVector( double const Epsilon )
        : _Epsilon( Epsilon )
	{}

	VswpRotationVector( double mag, CATMathDirection const& Ax, 
        double const Epsilon );

	VswpRotationVector( CATMathVector const& Ax, double const Epsilon );

	// Create a rotation vector from a rotation vswp_Matrix.

	VswpRotationVector( VswpRotationMatrix const& M, double const Epsilon );

    VswpRotationVector &operator=( VswpRotationVector const& Rhs );

	double Magnitude() const { return _Mag; }
	CATMathDirection const& Axis() const { return _Axis; }

    operator CATMathVector() const 
    {
        return _Axis * _Mag;
    }

	// Get the cross-vswp_Matrix for the rotation vswp_Matrix.

	VswpMatrix3x3 CrossMatrix() const;
	void SetCrossMatrix( VswpMatrix3x3 const& Cx );

	// This assumes that the object corresponds to a rotation abOut an axis.

	void Rotate( CATMathVector &V ) const;

private:

    double const _Epsilon;
	double _Mag;
	CATMathDirection _Axis;
};

inline double VswpSafeSqrt( double const& a, double const& ZeroTol )
{
	if ( a >= 0. )
		return CATSqrt( a );
	else if ( a < 0. && a > -ZeroTol )
		return 0.0;
	else
	{
		CATCGMContractAssert( FALSE );
		return 0.0;
	}
}

// A VswpQuaternion representing an orientation.

class ExportedByCATGMModelInterfaces VswpQuaternion 
{
public:

	// Create a VswpQuaternion corresponding to identity transform.

	VswpQuaternion()
	{}

	explicit VswpQuaternion( double real )
		: _R( real ), _i( 0., 0., 0. )
	{}

	explicit VswpQuaternion( CATMathVector const& i, double r = 0. )
		: _R( r ), _i( i )
	{}

	// We are exposing these but hopefully there won't be a need to
	// access them directly.

	double Real() const { return _R; }
	CATMathVector const& Imaginary() const { return _i; }

    double NormSq() const { return _R * _R + _i.SquareNorm(); }

	// Conjugation and inverse is similar to complex numbers.

	VswpQuaternion Conjugate() const { return VswpQuaternion( -_i, _R ); }

	VswpQuaternion Inverse() const;

	// Quaternions form a projective space when { q } is identified with
	// { -q } to represent SO[ 3 ], so the negation doesn't really change
	// the rotation.

	void Negate();

	// Arithmetic operations on quaternions. 

	VswpQuaternion operator+( VswpQuaternion const& Rhs ) const;

	VswpQuaternion operator-( VswpQuaternion const& Rhs ) const;

    void operator+=( VswpQuaternion const& Rhs );

	// Multiplication is not commutative!

	VswpQuaternion operator*( VswpQuaternion const& Rhs ) const;

	VswpQuaternion operator*( double d ) const;
	
	VswpQuaternion operator/( double d ) const;

    double operator%( VswpQuaternion const& Rhs ) const;

	// Some handy functions.

	VswpQuaternion Pow( double t ) const;
	VswpQuaternion NaturalLog() const;

protected:	

	double _R;
	CATMathVector _i;
};

// Normalise a VswpQuaternion.

VswpUnitQuaternion Normalise( VswpQuaternion const& Q, CATTolerance const& iTolObj );

// Natural log of a unit Quaternion.

CATMathVector QLog( VswpUnitQuaternion const& Q );

// Exponent of an purely imaginary Quaternion.

VswpUnitQuaternion QExp( CATMathVector const& V );

// The normalised version of a VswpQuaternion. This form is preferred when
// generating curves on unit hypersphere.

class VswpUnitQuaternion : public VswpQuaternion
{
public:

	VswpUnitQuaternion()
		: _ThetaSet( FALSE )
	{}

    VswpUnitQuaternion( VswpUnitQuaternion const& Orig )
        : VswpQuaternion( Orig ), _ThetaSet( Orig._ThetaSet )
    {
        if ( _ThetaSet ) _Theta = Orig._ThetaSet;
    }

	// Create a VswpQuaternion from an orientation defined as a rotation
	// by an angle abOut an axis.

	VswpUnitQuaternion( double theta, CATMathDirection const& U );

	// Create a VswpQuaternion from a rotation vswp_Matrix. 

	explicit VswpUnitQuaternion( 
                            VswpRotationMatrix const& R, 
                            CATTolerance const& iTolObj  
                            );

    // Conjugation and inverse is similar to complex numbers.

	VswpUnitQuaternion UnitConjugate() const;

	// Unit VswpQuaternion multiplication is closed under multiplication.

	VswpUnitQuaternion operator*( VswpUnitQuaternion const& Rhs ) const;

    VswpQuaternion operator*( VswpQuaternion const& Rhs ) const;

	// Rotate a CATMathVector.

	void Rotate( CATMathVector &V ) const;

	// Some handy functions.

	VswpUnitQuaternion Pow( double t ) const;
	VswpUnitQuaternion NaturalLog() const;

	// Normalise a VswpQuaternion.

	friend VswpUnitQuaternion Normalise( 
                                    VswpQuaternion const& Q, 
                                    CATTolerance const& iTolObj 
                                    );

    // Natural log of a unit Quaternion.

    friend CATMathVector QLog( VswpUnitQuaternion const& Q );

    // Exponent of an purely imaginary Quaternion.

    friend VswpUnitQuaternion QExp( CATMathVector const& V );

private:

	VswpUnitQuaternion( CATMathVector const& i, double r );

	// Copy over the sign of y to x.

	inline double CopySign( double x, double y ) const;

	// For a unit VswpQuaternion, 
	//	q = { cos( theta ), sin( theta ) * UCap }
	// where, UCap is a unit vector for the imaginary part.

	// Cache this so that a function like, g( t ) = Pow( q, f( t ) ) 
    // can be evaluated and differentiated efficiently.

	void SetupTheta() const;

	mutable double _Theta;
	mutable CATBoolean _ThetaSet;
};


// Encapsulate the three different ways of representing a rotation and its
// derivatives. We will ignore the euler angles form. This class will take
// care of mapping between the forms as long as derivative information in
// any one form is available.

class VswpRotationXformRep 
{			
public:

	VswpRotationXformRep( 
                    CATTolerance const& _TolObj, 
                    double const Epsilon 
                    );

	CATBoolean Empty() const;
    void SetEmpty();

    // The tolerance used for the transformations.

    double Epsilon() const { return _Epsilon; }

	// The VswpQuaternion form. 

	VswpQuaternion &Q();
	void SetQ( VswpQuaternion const& Q );

	// The rotation vswp_Matrix form.

	ExportedByCATGMModelInterfaces VswpRotationMatrix &Mat();
	void SetMat( VswpRotationMatrix const& M );

	// The rotation axis form.

	VswpRotationVector &RotAxis();
	void SetRotAxis( VswpRotationVector const& R );

    // Copy over the state to the other object.

    void CloneState( VswpRotationXformRep & Other ) const
    {
        Other._QSet = _QSet;
        if ( _QSet ) Other._Q = _Q;
        Other._AxisSet = _AxisSet;
        if ( _AxisSet ) Other._RotAxis = _RotAxis;
        Other._MatSet = _MatSet;
        if ( _MatSet ) Other._Mat = _Mat;
    }

protected:

	// Copy over the sign of y to x.

	inline double CopySign( double x, double y ) const;

	// Derived classes know the transformation process from
	// one form to Other.

	virtual void SetupQ() = 0;
	virtual void SetupMat() = 0;
	virtual void SetupRotAxis() = 0;

	// The meaning of these terms depends on the order of the
	// rotation derivative.

	CATBoolean _QSet, _AxisSet, _MatSet;
	VswpQuaternion _Q;
	VswpRotationMatrix _Mat;
	VswpRotationVector _RotAxis;

    double const _Epsilon;
	CATTolerance const& _TolObj;
};


// The rotation transform. 

class ZerothOrderRotationXformRep : public VswpRotationXformRep
{
public:

	ZerothOrderRotationXformRep( 
                            CATTolerance const& iTolObj, 
                            double const Epsilon 
                            )
        : VswpRotationXformRep( iTolObj, Epsilon )
	{}

	virtual void SetupQ();
	virtual void SetupMat();
	virtual void SetupRotAxis();
};


// The angular velocity of the rotational transform.

class FirstOrderRotationXformRep : public VswpRotationXformRep
{
public:

	FirstOrderRotationXformRep( 
                        CATTolerance const& iTolObj, 
                        ZerothOrderRotationXformRep &Z,
                        double const Epsilon
                        )
		: _Z( Z ), VswpRotationXformRep( iTolObj, Epsilon )
	{}

	virtual void SetupQ();
	virtual void SetupMat();
	virtual void SetupRotAxis();

private:

	ZerothOrderRotationXformRep &_Z;
};


// The angular acceleration of the rotational transform.

class SecondOrderRotationXformRep : public VswpRotationXformRep
{
public:

	SecondOrderRotationXformRep( 
                            CATTolerance const& iTolObj, 
                            ZerothOrderRotationXformRep &Z, 
		                    FirstOrderRotationXformRep &F,
                            double const Epsilon
                            )
		: _Z( Z ), _F( F ), VswpRotationXformRep( iTolObj, Epsilon )
	{}

	virtual void SetupQ();
	virtual void SetupMat();
	virtual void SetupRotAxis();

private:

	ZerothOrderRotationXformRep &_Z;
	FirstOrderRotationXformRep &_F;
};


// The angular jerk of the rotational transform.

class ThirdOrderRotationXformRep : public VswpRotationXformRep
{
public:

	ThirdOrderRotationXformRep( 
                            CATTolerance const& iTolObj, 
                            ZerothOrderRotationXformRep &Z, 
		                    FirstOrderRotationXformRep &F,
                            SecondOrderRotationXformRep &S,
                            double const Epsilon
                            )
		: _Z( Z ), _F( F ), _S( S ), VswpRotationXformRep( iTolObj, Epsilon )
	{}

	virtual void SetupQ();
	virtual void SetupMat();
	virtual void SetupRotAxis();

private:

	ZerothOrderRotationXformRep &_Z;
	FirstOrderRotationXformRep &_F;
    SecondOrderRotationXformRep &_S;
};



// A class to represent a rotation (and its time derivatives) in 3d.  
// The rotation can be represented as a VswpQuaternion, rotation vswp_Matrix,
// or axis of rotation and angle. 

class ExportedByCATGMModelInterfaces VswpRotationXform 
{
	typedef ZerothOrderRotationXformRep ZeroOrderRep;
	typedef FirstOrderRotationXformRep FirstOrderRep;
	typedef SecondOrderRotationXformRep SecondOrderRep;
    typedef ThirdOrderRotationXformRep ThirdOrderRep;

public:

	// Create a rotation trasnform, specifying the number of derivatives
	// it is supposed to handle.

	VswpRotationXform( 
                CATTolerance const& iTolObj, 
                int nDeriv = 2, 
                double Epsilon = -1. 
                );
	~VswpRotationXform();

    // These are not trivial.

    VswpRotationXform( VswpRotationXform const& Orig );
    VswpRotationXform &operator=( VswpRotationXform const& Rhs );

    // The number of evaluated derivatives.

    int NumDerivs() const { return _nDeriv; }

	// The rotation information in different representations.

	VswpQuaternion const& Q( int NthDeriv = 0 ) const
	{ 
		CATCGMContractAssert( NthDeriv <= _nDeriv );
		return _DReps[ NthDeriv ]->Q(); 
	}
	VswpRotationMatrix const& Mat( int NthDeriv = 0 ) const 
	{ 
		CATCGMContractAssert( NthDeriv <= _nDeriv );
		return _DReps[ NthDeriv ]->Mat(); 
	}
	VswpRotationVector const& RotAxis( int NthDeriv = 0 ) const 
	{ 
		CATCGMContractAssert( NthDeriv <= _nDeriv );
		return _DReps[ NthDeriv ]->RotAxis(); 
	}

	// Setup the rotation Xform definition.

	void Setup( VswpQuaternion const& Q, int NthDeriv ) 
	{ 
		CATCGMContractAssert( NthDeriv <= _nDeriv );
		_DReps[ NthDeriv ]->SetQ( Q );
	}
	void Setup( VswpRotationMatrix const& R, int NthDeriv ) 
	{ 
		CATCGMContractAssert( NthDeriv <= _nDeriv );
		_DReps[ NthDeriv ]->SetMat( R );
	}
	void Setup( VswpRotationVector const& RotAxis, int NthDeriv ) 
	{ 
		CATCGMContractAssert( NthDeriv <= _nDeriv );
		_DReps[ NthDeriv ]->SetRotAxis( RotAxis );
	}

    // Setup the rotation Xform definition from euler angles.

    static void Setup( 
                    VswpRotationXform & Xform,
                    VswpRotationMatrix const& RefMat,
                    double XAng,
                    double YAng,
                    double ZAng,
                    CATBoolean XYZOrder,
                    int NumDerivs = 0,
                    double * DXAng = NULL,
                    double * DYAng = NULL,
                    double * DZAng = NULL
                    );

    // Reset the evaluation cache.

    void Reset();

    // Get the tolerance used by representation mapping functions.

    CATTolerance const& GetTolerance() const { return _TolObj; }

private:

    void CloneDReps( VswpRotationXform const& Orig );    

	// The lifetime of this sub-object is actually synchronized with 
	// its parent, however keeping it on the heap helps keep it mutable.

    int _nDeriv;
	VswpRotationXformRep ** _DReps;

    CATTolerance const& _TolObj;
};

#endif 
