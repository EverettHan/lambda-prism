// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CGMVswpQCurve_H
#define CGMVswpQCurve_H

#include "CATGMModelInterfaces.h"

#include "CATMathInterval.h"
#include "CGMVswpRotation.h"
#include "CATLISTV_CATMathVector.h"
#include "CGMVswpKeyframeDef.h"
#include "CGMVswpKeyframesCache.h"

class CATTolerance;
class VswpKeyframeDef;
class VswpQuaternionCurve;

// An interface for piecewise continuous curve on the Quaternion unit 
// hypersphere.

class VswpQuaternionCurve
{
public:
	
	// Constructor to share the cache with the BodyMotionImpl.

    VswpQuaternionCurve( 
                    VswpKeyframesCacheIter &KeyframesIterator, 
                    CATTolerance const& iTolObj,                     
                    double Epsilon 
                    );

	// Constructor to manage the cache of the Curve internally.

	VswpQuaternionCurve( 
                    VswpKeyframeDef * iFrames, 
                    CATTolerance const& iTolObj,                     
                    double Epsilon 
                    );

    virtual ~VswpQuaternionCurve();

    // Evaluate the interpolated translational component of motion.

    CATMathPoint EvaluateTranslation(
                                double t,  
                                int nDeriv = 0,                            
                                CATBoolean EvalBelow = TRUE,
                                CATMathVector const ** Derivs = NULL
                                ) const;

    // Evaluate the interpolated rotational component of motion.

    virtual VswpRotationXform const& EvaluateOrientation( 
                                            double t,     
                                            int nDeriv = 0,                               
                                            CATBoolean EvalBelow = TRUE ,
                                            const CATMathAxis* pRefAxis = NULL//CATBoolean KeepInitRef = FALSE 
                                            ) const = 0;

protected:

    // Get the rotations at the start and end of the time span containing
    // the given time instant.

	CATMathInterval GetRotationXforms( 
		                        double iTime, 
		                        int nDerivs, 
		                        CATBoolean iEvalBelow,
		                        VswpRotationXform & oQ0, 
		                        VswpRotationXform & oQ1
                                ) const;

	CATTolerance const& _TolObj;

    // The result of orientation evaluation.

    mutable VswpRotationXform _Xform;

    // Variables for cached evaluations.
    
	mutable VswpKeyframesCacheIter _KeyframesIterator;
    mutable CATMathVector _DO[ 3 ];

	// Internal cache (may or may not be used).

	VswpKeyframesCache _KeyframesCache;
};


// A C0 continuous curve based on K. Shoemake's slerp formulation.

class VswpSlerpCurve : public VswpQuaternionCurve
{
    // A geodesic arc based on K. Shoemake's SLERP construction.

    class QArcSlerp 
    {
    public:

	    QArcSlerp( 
		        VswpRotationXform const& Q0, 
		        VswpRotationXform const& Q1,
		        CATMathInterval const& R,
                int nDeriv
		        );

	    // The relative rotation between Q0 and Q1 is, Q0_inv x Q1.
	    // The geodesic segment between Q0 and Q1 can then be 
        // parameterized as,
	    //      C( t ) = Q0 x ( ( Q0_inv x Q1 )^t ) 
        //
        // Note that quaternions multiplications are not commutative,
        // so the multiplication of the components should be setup
        // with care.

	    void Evaluate( double T, VswpRotationXform& Xform ) const;

    private:

        int _nDeriv;
	    CATMathInterval _TRange;
	    VswpUnitQuaternion _Q0, _Q0InvQ1;
    };

public:

	// Constructor to share the cache with the BodyMotionImpl.

    VswpSlerpCurve( 
                VswpKeyframesCacheIter &KeyframesIterator, 
                CATTolerance const& iTolObj,                 
                double Epsilon 
                );

	// Constructor to manage the cache of the Curve internally.

	VswpSlerpCurve( 
            VswpKeyframeDef * iFrames, 
            CATTolerance const& iTolObj,             
            double Epsilon 
            );

    // Evaluate the interpolated rotational component of motion.

    VswpRotationXform const& EvaluateOrientation( 
                                            double t,                                     
                                            int nDeriv = 0,
                                            CATBoolean EvalBelow = TRUE,
                                            const CATMathAxis* pRefAxis = NULL//CATBoolean KeepInitRef = FALSE
                                            ) const;
};

// A C1 continuous curve based on Kim, Kim, Shin's hermite Quaternion 
// formulation.

class VswpCubicHermiteQCurve : public VswpQuaternionCurve
{
    typedef VswpUnitQuaternion UnitQuaternion;
    typedef VswpQuaternion Quaternion;

    class QArcHermite
    {
    public:

	    QArcHermite( 
		        VswpRotationXform const& Q0, 
		        VswpRotationXform const& Q1,
		        CATMathInterval const& R,
                int nDeriv
		        );

        // Note that quaternion multiplication is associative but
        // not commutative, so the multiplication of the components 
        // should be set up with care.

	    void Evaluate( double par, VswpRotationXform& Xform ) const;

    private:

        class CumulativeBasis3
        {
        public:

            CumulativeBasis3( int index )
                : _Index( index )
            {}

            double F( double t ) const;
            double dF( double t ) const;
            double ddF( double t ) const;
            double dddF( double t ) const;

        private:

            int _Index;
        };

        UnitQuaternion BS0( double t, int i ) const;
        Quaternion BS1( double t, int i ) const;
        Quaternion BS2( double t, int i ) const;

        int _nDeriv;
	    CATMathInterval _TRange;
	    
        UnitQuaternion _Q0, _Q3;
        CATMathVector _W[ 3 ];
    };

public:

	// Constructor to share the cache with the BodyMotionImpl.

    VswpCubicHermiteQCurve( 
                    VswpKeyframesCacheIter &KeyframesIterator, 
                    CATTolerance const& iTolObj,                     
                    double Epsilon 
                    );

	// Constructor to manage the cache of the Curve internally.

	VswpCubicHermiteQCurve( 
                    VswpKeyframeDef * iFrames, 
                    CATTolerance const& iTolObj,                     
                    double Epsilon 
                    );

    // Evaluate the interpolated rotational component of motion.

    VswpRotationXform const& EvaluateOrientation( 
                                            double t,                                     
                                            int nDeriv = 0,
                                            CATBoolean EvalBelow = TRUE,
                                            const CATMathAxis* pRefAxis = NULL//CATBoolean  KeepInitRef = FALSE
                                            ) const;
};

// A C2 continuous curve based on Kim, Kim and Shin's Quaternion hermite 
// formulation.

class VswpQuinticHermiteQCurve : public VswpQuaternionCurve
{
	class QArcQuinticHermite
	{
	public:

		QArcQuinticHermite( 
			            VswpRotationXform const& Q0, 
			            VswpRotationXform const& Q1,
			            CATMathInterval const& R,
			            int nDeriv
			            );

		// Note that Quaternion multiplication is associative but
		// not commutative, so the multiplication of the components 
		// should be set up with care.

		void Evaluate( double par, VswpRotationXform& Xform ) const;

	private:

		class CumulativeBasis5
		{
		public:

			CumulativeBasis5( int index )
				: _Index( index )
			{}

			double F( double t ) const;
			double dF( double t ) const;
			double ddF( double t ) const;

		private:

			int _Index;
		};

		VswpUnitQuaternion BS0( double t, int i ) const;
		VswpQuaternion BS1( double t, int i ) const;
		VswpQuaternion BS2( double t, int i ) const;

		int _nDeriv;
		CATMathInterval _TRange;
		VswpUnitQuaternion _Q0, _Q5;
		CATMathVector _W[ 5 ];
	};


public:

	// Constructor to share the cache with the BodyMotionImpl.

    VswpQuinticHermiteQCurve( 
                        VswpKeyframesCacheIter &KeyframesIterator, 
                        CATTolerance const& iTolObj,                         
                        double Epsilon 
                        );

	// Constructor to manage the cache of the Curve internally.

	VswpQuinticHermiteQCurve( 
                        VswpKeyframeDef * iFrames, 
                        CATTolerance const& iTolObj,                         
                        double Epsilon 
                        );

    // Evaluate the interpolated rotational component of motion.

	VswpRotationXform const& EvaluateOrientation( 
		                                    double t,                                     
		                                    int nDeriv = 0,
		                                    CATBoolean EvalBelow = TRUE,
                                        const CATMathAxis* pRefAxis = NULL//CATBoolean KeepInitRef = FALSE
		                                    ) const;
};

// A C3 continuous curve based on Kim, Kim and Shin's Quaternion hermite 
// formulation.

class VswpSepticHermiteQCurve : public VswpQuaternionCurve
{
	class QArcSepticHermite
	{
	public:

		QArcSepticHermite( 
			        VswpRotationXform const& Q0, 
			        VswpRotationXform const& Q1,
			        CATMathInterval const& r,
			        int nDeriv
			        );

		// Note that Quaternion multiplication is associative but
		// not commutative, so the multiplication of the components 
		// should be set up with care.

		void Evaluate( double par, VswpRotationXform& Xform ) const;

	private:

		class CumulativeBasis7
		{
		public:

			CumulativeBasis7( int index )
				: _Index( index )
			{}

			double F( double t ) const;
			double dF( double t ) const;
			double ddF( double t ) const;
            double dddF( double t ) const;

		private:

			int _Index;
		};

		VswpUnitQuaternion BS0( double t, int i ) const;
		VswpQuaternion BS1( double t, int i ) const;
		VswpQuaternion BS2( double t, int i ) const;
        VswpQuaternion BS3( double t, int i ) const;

		int _nDeriv;
		CATMathInterval _TRange;
		VswpUnitQuaternion _Q0, _Q7;
		CATMathVector _W[ 7 ];
	};


public:

	// Constructor to share the cache with the BodyMotionImpl.

    VswpSepticHermiteQCurve( 
                        VswpKeyframesCacheIter & KeyframesIterator, 
                        CATTolerance const& iTolObj,                         
                        double Epsilon 
                        );

	// Constructor to manage the cache of the Curve internally.

	VswpSepticHermiteQCurve( 
                        VswpKeyframeDef * iFrames, 
                        CATTolerance const& iTolObj,                         
                        double Epsilon 
                        );

    // Evaluate the interpolated rotational component of motion.

	VswpRotationXform const& EvaluateOrientation( 
		                                double t,                                     
		                                int nDeriv = 0,
		                                CATBoolean EvalBelow = TRUE,
                                    const CATMathAxis* pRefAxis = NULL//CATBoolean KeepInitRef = FALSE
		                                ) const;
};

// A hermite interpolation of the euler angles of the keyframes. This
// assumes that euler angle derivatives up to the maximum order (3) are
// known at the keyframes.

class VswpEulerHermiteQCurve : public VswpQuaternionCurve
{
public:

	// Constructor to share the cache with the BodyMotionImpl.

    VswpEulerHermiteQCurve( 
                        VswpKeyframesCacheIter & KeyframesIterator, 
                        CATTolerance const& iTolObj,                         
                        double Epsilon 
                        );

	// Constructor to manage the cache of the Curve internally.

	VswpEulerHermiteQCurve( 
                        VswpKeyframeDef * iFrames, 
                        CATTolerance const& iTolObj,                         
                        double Epsilon 
                        );

    // Evaluate the interpolated rotational component of motion.

	VswpRotationXform const& EvaluateOrientation( 
		                                double t,                                     
		                                int nDeriv = 0,
		                                CATBoolean EvalBelow = TRUE,
                                    const CATMathAxis* pRefAxis = NULL//CATBoolean KeepInitRef = FALSE
		                                ) const;
};

#endif 
