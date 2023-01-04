// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CGMVswpKeyframeDef_H
#define CGMVswpKeyframeDef_H

#include "CATGMModelInterfaces.h"

#include "CATMathInterval.h"
#include "CATMath3x3Matrix.h"
#include "CGMVswpRotation.h"
#include "CATLISTV_CATMathVector.h"
#include "CATCGMContractAssert.h"

class CATNurbsCurve;
class CATGeoFactory;
class VswpKeyframeDef;
class VswpKeyframesCache;
class VswpMotionCvec;
class CATBodyMotionImpl;
class VswpKeyframes;
class CATCurve;

// The points that would be used by numerical quadrature routines.

class ExportedByCATGMModelInterfaces VswpQuadraturePoints
{
    static const int MAX_DERIV = 3;

public:

    VswpQuadraturePoints(
					CATTolerance const& iTolObj, 
                    CATMathInterval const& Dm,
					CATBoolean Fwd,
                    int const NumStages,
                    double const * Pts,
                    VswpKeyframeDef const * Span
                    )
        : _Dm( Dm ), _NumStages( NumStages ), _QPts( Pts ), 
          _Span( Span ), _Next( NULL ), _Fwd( Fwd ),
          _Defined( FALSE ), _NumDerivs( 0 ), 
          _O( NULL ), _DO( NULL ), _Ori( NULL )
    {
        CATCGMContractAssert( NumStages > 0 && Span != NULL && Pts != NULL );
        _O = new CATMathPoint [ _NumStages ];
        _DO = new CATMathVector * [ _NumStages ];
        for ( int i = 0; i < _NumStages; ++i ) 
            _DO[ i ] = new CATMathVector [ MAX_DERIV ];
        _Ori = new VswpRotationXform* [ _NumStages ];
		for ( int ii=0; ii< _NumStages; ii++ )
		{
			_Ori[ii] = new VswpRotationXform(iTolObj);
		}
    }

    ~VswpQuadraturePoints()
    {
        if ( _O != NULL ) delete [] _O;
        _O = NULL;
        if ( _DO != NULL )
        {
            for ( int i = 0; i < _NumStages; ++i ) delete [] _DO[ i ];
            delete [] _DO;
        }
        _DO = NULL;
        if ( _Ori != NULL )
		{
			for (int ii=0; ii<_NumStages; ii++)
			{
				delete _Ori[ii];
				_Ori[ii] = NULL;
			}
			delete [] _Ori;
		}
			
        _Ori = NULL;
    }

    // The points corresponding to stages of the quadrature method.
    
    int NumStages() const { return _NumStages; }
    double StagePar( int i ) const 
    { 
        CATCGMContractAssert( i >= 0 && i < _NumStages );
        if ( _QPts != NULL ) return _Fwd ? _QPts[ i ] : 1. - _QPts[ i ]; 
        return 0.;
    }

    // The domain of evaluation and its corresponding keyframe span.
    // The domain cannot straddle multiple spans.

    CATMathInterval const& GetDomain() const { return _Dm; }
    VswpKeyframeDef const * GetSpan() const { return _Span; }

    CATBoolean Compare( 
                    CATMathInterval const& Dm, 
					CATBoolean Fwd,
                    int NumStages, 
                    double const * Pts,
                    double const Tol
                    ) const
    {
        if ( CATFabs( _Dm.GetMin() - Dm.GetMin() ) < Tol &&
             CATFabs( _Dm.GetMax() - Dm.GetMax() ) < Tol &&
             NumStages == _NumStages && Pts == _QPts && Fwd == _Fwd )
             return TRUE;
        return FALSE;
    }

    // Whether the evaluation cache is defined.

    CATBoolean IsDefined() const { return _Defined; }

    // Get the next quadrature cache in the list.

    VswpQuadraturePoints const * Next() const { return _Next; }
    VswpQuadraturePoints * Next() { return _Next; }
    void SetNext( VswpQuadraturePoints * N ) { _Next = N; }

    // List management functions.

    void RemoveAll()
    {
        for ( VswpQuadraturePoints * N = this; N != NULL; )
        {
            VswpQuadraturePoints * Next = N->Next();
            delete N;
            N = Next;
        }
    }

    CATMathVector GetAngularV() const
    {
        return _AngularV;
    }

    void SetAngularV(CATMathVector const & iAngV)
    {
        _AngularV = iAngV;
    }

private:

    friend class CATBodyMotionImpl;
    friend class VswpMotionCvec;

    // Access to the cache for position and orientation at the quadrature 
    // points.    

    // The frame origin cache.

    void Origin( int QuadPt, CATMathPoint & O ) const
    {
        if ( _O == NULL ) CATThrowForNullPointer();
        CATCGMContractAssert( QuadPt >= 0 && QuadPt < _NumStages );
        O = _O[ QuadPt ];
    }

    // The frame origin derivative cache.

    void DOrigin( int QuadPt, int nDeriv, CATMathVector const *& V ) const
    {
        if ( _DO == NULL ) CATThrowForNullPointer();
        CATCGMContractAssert( QuadPt >= 0 && QuadPt < _NumStages );
        CATCGMContractAssert( nDeriv >= 0 && nDeriv < _NumDerivs );
        V = &( _DO[ QuadPt ][ nDeriv ] );
    }

    // The orientation cache.

    void Orientation( int QuadPt, VswpRotationXform const *& Xform ) const
    {
        if ( _Ori == NULL ) CATThrowForNullPointer();
        CATCGMContractAssert( QuadPt >= 0 && QuadPt < _NumStages );
        Xform = ( _Ori[ QuadPt ] );
    }

private:

    CATBoolean _Defined;

    // Translation cache.

    CATMathPoint * _O;
    CATMathVector ** _DO;

    // Orientation cache.

    VswpRotationXform* *_Ori;
    int _NumDerivs;

    CATMathVector _AngularV;

    // The evaluation domain and the quadrature points.

	CATBoolean _Fwd;
    CATMathInterval const _Dm;

    int const _NumStages;
    double const * _QPts;

    // The parent keyframe span that owns this cache.

    VswpKeyframeDef const * _Span;

    // The next cache in the parent keyframe span.

    mutable VswpQuadraturePoints * _Next;
};


// An interface representing a snapshot of rigid body motion of an
// arbitrary object. Stores the position, orientation of the object
// and instantaneous derivatives.

class VswpKeyframeDef
{
public:

    // A keyframe definition based on a moving frame and its derivatives
    // w.r.t time.

	VswpKeyframeDef( 
				double iTime,
				CATMathPoint const& iOrigin,
				CATLISTV(CATMathVector) const& iOriginDerivs,
				CATMath3x3Matrix const& iOrientation,
				CATBoolean iOrientationDerivSet,
				CATMath3x3Matrix const& iOrientationDeriv,
                double Tol,
				CATTolerance const& iTolObj, 
                VswpKeyframeDef * N = NULL
                );

    // A version of the above based on Euler angles w.r.t a fixed
    // reference axis.

	VswpKeyframeDef( 
				double iTime,
				CATMathPoint const& iOrigin,
				CATLISTV(CATMathVector) const& iOriginDerivs,
				CATMath3x3Matrix const& iRefOrientation,
                int const NumOriDerivs,
                double const * XAngAndDerivs,
                double const * YAngAndDerivs,
                double const * ZAngAndDerivs,
                CATBoolean XYZOrder,
                double Tol,
				CATTolerance const& iTolObj, 
                VswpKeyframeDef * N = NULL
                );
  //Swme version with no associated time
  	VswpKeyframeDef( 
				CATMathPoint const& iOrigin,
				CATLISTV(CATMathVector) const& iOriginDerivs,
				CATMath3x3Matrix const& iRefOrientation,
                int const NumOriDerivs,
                double const * XAngAndDerivs,
                double const * YAngAndDerivs,
                double const * ZAngAndDerivs,
                CATBoolean XYZOrder,
                double Tol,
				CATTolerance const& iTolObj, 
                VswpKeyframeDef * N = NULL
                );

    // A simpler version for a reference frame not associated to a time
    // instant.

    VswpKeyframeDef( 
				CATMathPoint const& iOrigin,
				CATMath3x3Matrix const& iOrientation,
                double Tol,
				CATTolerance const& iTolObj, 
                VswpKeyframeDef * N = NULL
                );

    // A version of the above based on Euler angles w.r.t a fixed
    // reference axis.

	VswpKeyframeDef( 
				CATMathPoint const& iOrigin,
				CATMath3x3Matrix const& iRefOrientation,
                double const& XAng,
                double const& YAng,
                double const& ZAng,
                CATBoolean XYZOrder,
                double Tol,
				CATTolerance const& iTolObj, 
                VswpKeyframeDef * N = NULL
                );

    ~VswpKeyframeDef();

    // The time instant associated with the keyframe.

    CATBoolean IsTimeSet() const { return _TimeSet; }
    double GetTime() const { return _Time; }
    void SetTime( double T )
    {
        _TimeSet = TRUE;
        _Time = T;
    }    

    // Get the moving frame Origin location (and higher derivatives).

    virtual int NumTranslationDerivs() const;
    virtual CATMathPoint const& O() const { return _O; }
    virtual CATMathVector const& Ot() const 
    { 
        CATCGMContractAssert( _NumTranslationDerivs >= 1 );
        return _dO; 
    }
    virtual CATMathVector const& Ott() const 
    { 
        CATCGMContractAssert( _NumTranslationDerivs >= 2 );
        return _ddO; 
    }
    virtual CATMathVector const& Ottt() const 
    { 
        CATCGMContractAssert( _NumTranslationDerivs >= 3 );
        return _dddO; 
    }

    // Set any missing translation derivatives.

    void SetTranslationDeriv( CATMathVector const& dO, int nDeriv )
    {
        if ( nDeriv == 1 ) _dO = dO;
        else if ( nDeriv == 2 ) _ddO = dO;
        else if ( nDeriv == 3 ) _dddO = dO;
        else
        {
            CATCGMContractAssert( FALSE );
        }
        if ( _NumTranslationDerivs < nDeriv ) 
            _NumTranslationDerivs = nDeriv;
    }

    // The interpolating curve for the translation component of motion.

    CATCurve const * GetTranslationCurve() const { return _TCu; }
    void SetTranslationCurve( CATCurve * pCu );

    // Get the moving frame rotation and higher derivatives.

    int NumRotationDerivs() const;
    virtual VswpRotationXform const& Xform( int nDerivs ) const 
    {
        return _Xform;
    }
    VswpRotationXform& Xform() { return _Xform; }

    // We are not using the frame orientation derivatives from the
    // definition files yet so these need to be setup separately.

    void SetAngularVelocity( VswpRotationVector const& AngV );
    void SetAngularAcceleration( VswpRotationVector const& AngA );
    void SetAngularJerk( VswpRotationVector const& AngJ );
    
    // The orientation and derivatives in terms of euler angles.

    CATBoolean EulerAnglesSet() const { return _EulerAnglesSet; }       
    CATBoolean IsXYZEulerOrder() const { return _XYZEulerOrder; }

    void SetCorner(CATBoolean iIsCorner){_IsCorner = iIsCorner;};
    CATBoolean IsCorner() const{return _IsCorner;};

    void GetEulerAngles( double & XAng, 
            double & YAng, double & ZAng ) const
    {
        CATCGMContractAssert( _EulerAnglesSet );

        XAng = _XAng;
        YAng = _YAng;
        ZAng = _ZAng;
    }

    void GetEulerDerivs( int NthDeriv, double & DXAng, 
        double & DYAng, double & DZAng ) const
	{
        CATCGMContractAssert( _EulerAnglesSet && 
            NthDeriv < _NumRotationDerivs );

        DXAng = _DXAng[ NthDeriv ];
        DYAng = _DYAng[ NthDeriv ];
        DZAng = _DZAng[ NthDeriv ];
	}

    void SetEulerDerivs( int NthDeriv, double const& DXAng, 
        double const& DYAng, double const& DZAng )
	{
        CATCGMContractAssert( _EulerAnglesSet && NthDeriv < 3 );

        _DXAng[ NthDeriv ] = DXAng;
        _DYAng[ NthDeriv ] = DYAng;
        _DZAng[ NthDeriv ] = DZAng;
        if ( NthDeriv > ( _NumRotationDerivs - 1 ) ) 
            _NumRotationDerivs = NthDeriv + 1;
	}

    // The interpolating curve for the rotation component of motion if
    // the keyframes are based on euler angles.

    CATCurve const * GetEulerAngleCurve() const { return _RCu; }
    void SetEulerAngleCurve( CATCurve * pCu );

    // Keyframe list management.

    void SetNext( VswpKeyframeDef * n ) { _Next = n; }
    VswpKeyframeDef * Next() { return _Next; }
    VswpKeyframeDef const * Next() const { return _Next; }

    void SetOwner( VswpKeyframesCache * ipOwner );
    VswpKeyframesCache const* GetOwner() const;

    // The cache of quadrature evaluation results of the span bounded
    // by this keyframe and the next.

    VswpQuadraturePoints const * FetchCache(
                                        CATMathInterval const& Dm,
										CATBoolean Fwd,
                                        int const NumStages,
                                        double const * Pts
                                        ) const;    

private:

    // Remove the interpolation for the translation component.

    void RemoveTransCurve();	

    // Remove the interpolation for the rotation component.

    void RemoveEulerCurve();	

    // An evaluation cache for numerical quadrature. This is setup as
    // a list for now, we can switch to a binary tree when we switch to
    // uniform subdivision.

    typedef VswpQuadraturePoints QuadPoints;
    mutable QuadPoints * _QuadPts;

    // The time instant associated with this keyframe.

    CATBoolean _TimeSet;
    double _Time;
        
    // The translation component specified at the origin of the moving
    // frame and its derivatives.

    int _NumTranslationDerivs;
	CATMathPoint _O;
	CATMathVector _dO, _ddO, _dddO;

    // The interpolated translation curve for this span.

    CATCurve * _TCu;        

    // The rotation component and its (first) derivative.

	CATMath3x3Matrix _R, _dR;

    // The Euler angles and higher order derivatives.

    CATBoolean _EulerAnglesSet, _XYZEulerOrder;
    double _XAng, _YAng, _ZAng;
    double _DXAng[ 3 ], _DYAng[ 3 ], _DZAng[ 3 ];

    // The interpolated euler angle curve for this span.

    CATCurve * _RCu;        

    // The representation of the orientation component at the keyframe.

    int _NumRotationDerivs;
    VswpRotationXform _Xform;

    // The cache object that owns this keyframe

    VswpKeyframesCache * _pOwner;

    // The next keyframe in the sequence.

    VswpKeyframeDef * _Next;

    // The tolerance object for the evaluations.

    CATTolerance const& _TolObj;

    CATBoolean _IsCorner;
};



#endif 
