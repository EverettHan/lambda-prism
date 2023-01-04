// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CGMVswpMoveDesignDef_H
#define CGMVswpMoveDesignDef_H

// Raw data of volumetric sweep definition. 

// A five-axis machining operation involves removal of material from a blank
// body with a grinding wheel. The grinding wheel starts moving from a point
// which is usually away from the blank and eventually cuts into the blank. 
// The grinding wheel is then moved away from the blank (assuming without 
// gouging into the blank) and the removal process is re-started.

// The intent is to represent the rigid body motion of the wheel as a 
// volumetric sweep and then represent the material removal as a boolean 
// operation between the blank and the volumetric sweep. This should simulate 
// the machining process.

// A volumetric sweep definition has a blank body and multiple 'movedesign' 
// definitions describe movement of a grinding wheel in 3-space.
// Each 'movedesign' has an associated wheel definition, a 'movedesign' may 
// have multiple sequence of sweep paths.

#include "CATGMModelInterfaces.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathInterval.h"
#include "CATMathDirection.h"

#include "CATMathAxis.h"
#include "CATMathTransformation.h"

#include "CATMathPoint2D.h"
#include "CATMathVector2D.h"
#include "CATMathDirection2D.h"
#include "CATUnicodeString.h"

#include "CATCGMContractAssert.h"

#include "CGMVswpAxisymBodyDef.h"

// A path specified by special "keyframe" points, a continuous path
// must be generated from these points.

class ExportedByCATGMModelInterfaces VswpInterpPathDef 
{
public:

	// The wheel positions are similar to keyframes in animation, we can
	// store higher order derivatives too.

	class WheelPosDef 
	{
	public:		

		WheelPosDef( 
				CATMathPoint const& O, 
                                        CATMathVector const& XAx,
                                        CATMathVector const& YAx,
                                        CATMathVector const& ZAx,
				//CATMathDirection const& XAx,
				//CATMathDirection const& YAx, 
				//CATMathDirection const& ZAx,
                double Eps,
                WheelPosDef * N = NULL
				)
			: _Origin( O ), _X( XAx ), _Y( YAx ), _Z( ZAx ), _Time( 0. ),
              _Next( N ), _Epsilon( Eps ), _TimeSet( FALSE ), 
              _EulerAnglesSet( FALSE ), _XYZEulerOrder( FALSE ),_IsCorner(FALSE),_CornerIdx(0)
		{
            for ( int i = 0; i < 3; ++i )
            {
                _TransDerivsSet[ i ] = FALSE;
                _OriDerivsSet[ i ] = FALSE;
            }
        }

        // This version is for Euler angles w.r.t a reference axis.

        WheelPosDef( 
				CATMathPoint const& O, 
                                        CATMathVector const& XAx,
                                        CATMathVector const& YAx,
                                        CATMathVector const& ZAx,
				//CATMathDirection const& XAx,
				//CATMathDirection const& YAx, 
				//CATMathDirection const& ZAx,
                double const XAng,
                double const YAng,
                double const ZAng,
                CATBoolean XYZOrder,
                double Eps,
                WheelPosDef * N = NULL
				)
			: _Origin( O ), _X( XAx ), _Y( YAx ), _Z( ZAx ), 
              _XAng( XAng ), _YAng( YAng ), _ZAng( ZAng ),
              _Next( N ), _Epsilon( Eps ), _EulerAnglesSet( TRUE ),
              _Time( 0. ), _TimeSet( FALSE ), _XYZEulerOrder( XYZOrder ),_IsCorner(FALSE),
              _CornerIdx(0)         
		{
            for ( int i = 0; i < 3; ++i )
            {
                _TransDerivsSet[ i ] = FALSE;
                _OriDerivsSet[ i ] = FALSE;
            }
        }

		WheelPosDef( WheelPosDef const& Orig )
			: _Origin( Orig._Origin ), _X( Orig._X ), _Y( Orig._Y ),
			  _Z( Orig._Z ), _Time( Orig._Time ), 			  
              _Epsilon( Orig._Epsilon ), _TimeSet( Orig._TimeSet ),
              _EulerAnglesSet( Orig._EulerAnglesSet ), _Next( NULL ),
              _XYZEulerOrder( Orig._XYZEulerOrder ),_IsCorner(Orig._IsCorner),_CornerIdx(Orig._CornerIdx)
		{
             if (Orig._IsCorner)
            {
              _CornerOrigin = Orig._CornerOrigin;
              _CornerAAngle = Orig._CornerAAngle;
              _CornerBAngle = Orig._CornerBAngle;
            }
            int i;
            for ( i = 0; i < 3; ++i )
            {
                _TransDerivsSet[ i ] = Orig._TransDerivsSet[ i ];
                _OriDerivsSet[ i ] = Orig._OriDerivsSet[ i ];
            }

			if ( _TransDerivsSet[ 0 ] ) 
                SetOriginD( Orig._DOrigin[ 0 ] );
			if ( _TransDerivsSet[ 1 ] ) 
                SetOriginDD( Orig._DOrigin[ 1 ] );
            if ( _TransDerivsSet[ 2 ] ) 
                SetOriginDDD( Orig._DOrigin[ 2 ] );

            if ( !_EulerAnglesSet )
            {
                for ( i = 0; i < 3 && _OriDerivsSet[ 0 ]; ++i ) 
                    _DOriFirst[ i ] = Orig._DOriFirst[ i ];
            }
            else
            {
                _XAng = Orig._XAng;
                _YAng = Orig._YAng;
                _ZAng = Orig._ZAng;

                for ( i = 0; i < 3 && _OriDerivsSet[ i ]; ++i ) 
                {
                    _DXAng[ i ] = Orig._DXAng[ i ];
                    _DYAng[ i ] = Orig._DYAng[ i ];
                    _DZAng[ i ] = Orig._DZAng[ i ];
                }
            }
		}

        WheelPosDef &operator=( WheelPosDef const& Rhs )
        {
            if ( this != &Rhs )
            {
              _IsCorner = Rhs._IsCorner;
              _CornerIdx = Rhs._CornerIdx;
              if(_IsCorner)
              {
              _CornerOrigin = Rhs._CornerOrigin;
              _CornerAAngle = Rhs._CornerAAngle;
              _CornerBAngle = Rhs._CornerBAngle;
              }
              _Epsilon = Rhs._Epsilon;
                _Origin = Rhs._Origin;
                _X = Rhs._X;
                _Y = Rhs._Y;
			    _Z = Rhs._Z; 
                
                _TimeSet = Rhs._TimeSet;
                if ( _TimeSet ) _Time = Rhs._Time;

                int i;
                for ( i = 0; i < 3; ++i )
                {
                    _TransDerivsSet[ i ] = Rhs._TransDerivsSet[ i ];
                    _OriDerivsSet[ i ] = Rhs._OriDerivsSet[ i ];
                }
                
                if ( _TransDerivsSet[ 0 ] ) 
                    SetOriginD( Rhs._DOrigin[ 0 ] );
			    if ( _TransDerivsSet[ 1 ] ) 
                    SetOriginDD( Rhs._DOrigin[ 1 ] );
                if ( _TransDerivsSet[ 2 ] ) 
                    SetOriginDDD( Rhs._DOrigin[ 2 ] );

                _XYZEulerOrder = Rhs._XYZEulerOrder;
                if ( !_EulerAnglesSet )
                {
			        for ( i = 0; i < 3 && _OriDerivsSet[ 0 ]; ++i ) 
                        _DOriFirst[ i ] = Rhs._DOriFirst[ i ];
                }
                else
                {
                    _XAng = Rhs._XAng;
                    _YAng = Rhs._YAng;
                    _ZAng = Rhs._ZAng;

                    for ( i = 0; i < 3 && _OriDerivsSet[ i ]; ++i ) 
                    {
                        _DXAng[ i ] = Rhs._DXAng[ i ];
                        _DYAng[ i ] = Rhs._DYAng[ i ];
                        _DZAng[ i ] = Rhs._DZAng[ i ];
                    }
                }

                _Next = NULL;		

            }
            return *this;
        }

		CATBoolean IsTranslational() const 
		{ 
			return dO().Norm() > _Epsilon;
		}

		CATBoolean IsRotational() const
		{
			return dX().Norm() > _Epsilon ||
				   dY().Norm() > _Epsilon ||
				   dZ().Norm() > _Epsilon;
		}

    CATBoolean IsCorner() const
    {
      return _IsCorner;
    }

    void SetCorner(CATBoolean iIsCorner)
    {
      _IsCorner = iIsCorner;
    }
	void SetRelativeOrigin(const CATMathPoint& iRelativeOrigin)
	{
		_RelativeOrigin = iRelativeOrigin;
	}
	CATMathPoint GetRelativeOrigin() const
	{
		return _RelativeOrigin;
	}
    //This corresponds to the Origin point given as an input
    //which is different from the one actually computed in the corner case
    void SetCornerOrigin(CATMathPoint Origin)
    {
      _CornerOrigin = Origin;
    }

    CATMathPoint  GetCornerOrigin()const
    {
      return _CornerOrigin;
    }

    void SetCornerAAngle(double angle)
    {
      _CornerAAngle = angle;
    }
    double GetCornerAAngle() const
    {
      return _CornerAAngle;
    }

    void SetCornerBAngle(double angle)
    {
      _CornerBAngle = angle;
    }

    double GetCornerBAngle() const
    {
      return _CornerBAngle;
    }
    //CornerIdx = 1 if it is the first point of the corner, 
    //            2 if this is the second, 
    //            0 if not a corner
    void SetCornerIndex(int idx)
    {
      _CornerIdx = idx;
    }

    int  GetCornerIdx()const
    {
      return _CornerIdx;
    }
		// The placement of the moving frame in global coordinates.
        // For euler angles based specification, this is the reference
        // axis system.

		CATMathPoint const& Origin() const { return _Origin; }
		/*CATMathDirection*/CATMathVector const& X() const { return _X; }
		/*CATMathDirection*/CATMathVector const& Y() const { return _Y; }
		/*CATMathDirection*/CATMathVector const& Z() const { return _Z; }

        void SetOrigin( CATMathPoint const& O ) { _Origin = O; }

		// First derivatives of the frame origin w.r.t time.

		CATMathVector const& dO() const 
        { 
            CATCGMContractAssert( _TransDerivsSet[ 0 ] );
            return _DOrigin[ 0 ]; 
        }

        void SetOriginD( CATMathVector const& D )
        {
            _TransDerivsSet[ 0 ] = TRUE;
            _DOrigin[ 0 ] = D;
        }
        CATBoolean TransFirstDerivSet() const 
        { 
            return _TransDerivsSet[ 0 ]; 
        } 

        // First derivatives of the frame axes w.r.t time.

        CATMathVector const& dX() const 
        { 
            CATCGMContractAssert( _OriDerivsSet[ 0 ] );
            return _DOriFirst[ 0 ]; 
        }
		CATMathVector const& dY() const 
        { 
            CATCGMContractAssert( _OriDerivsSet[ 0 ] );
            return _DOriFirst[ 1 ]; 
        }
		CATMathVector const& dZ() const 
        { 
            CATCGMContractAssert( _OriDerivsSet[ 0 ] );
            return _DOriFirst[ 2 ]; 
        }

		void SetOriFirstDerivs( CATMathVector const D[ 3 ] )
		{
			_OriDerivsSet[ 0 ] = TRUE;
			for ( int i = 0; i < 3; ++i ) 
                _DOriFirst[ i ] = D[ i ];
		}
        CATBoolean OriFirstDerivSet() const 
        { 
            return _OriDerivsSet[ 0 ]; 
        } 

		// Second derivatives of the frame origin w.r.t time.

		CATBoolean TransSecondDerivSet() const 
        { 
            return _TransDerivsSet[ 1 ]; 
        }
		CATMathVector const& OriginDD() const 
        { 
            CATCGMContractAssert( _TransDerivsSet[ 1 ] );
            return _DOrigin[ 1 ]; 
        }
		void SetOriginDD( CATMathVector const& ddO ) 
		{
			_TransDerivsSet[ 1 ] = TRUE;
			_DOrigin[ 1 ] = ddO; 
		}

        // Third derivatives of the frame origin w.r.t time.

		CATBoolean TransThirdDerivSet() const 
        { 
            return _TransDerivsSet[ 2 ]; 
        }
		CATMathVector const& OriginDDD() const 
        { 
            CATCGMContractAssert( _TransDerivsSet[ 2 ] );
            return _DOrigin[ 2 ]; 
        }
		void SetOriginDDD( CATMathVector const& dddO ) 
		{
			_TransDerivsSet[ 2 ] = TRUE;
			_DOrigin[ 2 ] = dddO; 
		}

        // The orientation and derivatives in terms of euler angles.

        CATBoolean EulerAnglesSet() const { return _EulerAnglesSet; }       
        CATBoolean IsXYZEulerOrder() const { return _XYZEulerOrder; }

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
            CATCGMContractAssert( _EulerAnglesSet && NthDeriv < 3 &&
                _OriDerivsSet[ NthDeriv ] == TRUE );

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
            _OriDerivsSet[ NthDeriv ] = TRUE;
		}

        // Whether the higher order orientation derivatives are set.

        CATBoolean OriSecondDerivSet() const 
        { 
            return _OriDerivsSet[ 1 ]; 
        }

        CATBoolean OriThirdDerivSet() const 
        { 
            return _OriDerivsSet[ 2 ]; 
        }

        CATBoolean OriDerivSet( int NthDeriv ) const
        {
            CATCGMContractAssert( NthDeriv <= 3 );
            return _OriDerivsSet[ NthDeriv ]; 
        }

        // The time instant associated with the keyframe.

        CATBoolean IsTimeSet() const { return _TimeSet; }
		void SetTime( double t ) 
        { 
            _Time = t; 
            _TimeSet = TRUE;
        }
		double GetTime() const { return _Time; }

		CATBoolean operator==( WheelPosDef const& Other ) const
		{
            // The equality test needs to be refined with more 
            // appropriate tolerances.

			CATBoolean Equals = FALSE;
        Equals =  _IsCorner == Other._IsCorner ;
        if (Equals && _IsCorner)
        {
         Equals = Equals && (_CornerOrigin -Other._CornerOrigin).Norm() < _Epsilon 
          && _CornerIdx == Other._CornerIdx 
          && (_CornerAAngle -Other._CornerAAngle)<_Epsilon 
           && (_CornerBAngle -Other._CornerBAngle)<_Epsilon;
        }
			Equals = Equals &&
			    ( _Origin - Other._Origin ).Norm() < _Epsilon && 
                ( _X - Other._X ).Norm() < _Epsilon && 
                ( _Y - Other._Y ).Norm() < _Epsilon && 
                ( _Z - Other._Z ).Norm() < _Epsilon;
            if ( _EulerAnglesSet )
            {
                Equals = Equals && 
                    CATFabs( _XAng - Other._XAng ) < _Epsilon &&
                    CATFabs( _YAng - Other._YAng ) < _Epsilon &&
                    CATFabs( _ZAng - Other._ZAng ) < _Epsilon;
                Equals = Equals &&
                    _XYZEulerOrder == Other._XYZEulerOrder;
            }
            if ( _TimeSet ) Equals = Equals && 
                _TimeSet == Other._TimeSet &&
                CATFabs( _Time - Other._Time ) < _Epsilon;

            int i;
            for ( i = 0; i < 3 && Equals; ++i )
            {
                if ( _TransDerivsSet[ i ] != Other._TransDerivsSet[ i ] )
                    Equals = FALSE;
                else if ( _TransDerivsSet[ i ] )
                    Equals = Equals && ( _DOrigin[ i ] - 
                        Other._DOrigin[ i ] ).Norm() < _Epsilon;
            }

            for ( i = 0; i < 3 && Equals; ++i )
            {
                if ( _OriDerivsSet[ i ] != Other._OriDerivsSet[ i ] )
                    Equals = FALSE;
                else if ( _OriDerivsSet[ i ] )
                {
                    if ( _EulerAnglesSet )
                    {
                        Equals = Equals && CATFabs( 
                            _DXAng[ i ] - Other._DXAng[ i ] ) < _Epsilon;
                        Equals = Equals && CATFabs( 
                            _DYAng[ i ] - Other._DYAng[ i ] ) < _Epsilon;
                        Equals = Equals && CATFabs( 
                            _DZAng[ i ] - Other._DZAng[ i ] ) < _Epsilon;
                    }
                    else
                    {
                        Equals = Equals && ( _DOriFirst[ 0 ] - 
                            Other._DOriFirst[ 0 ] ).Norm() < _Epsilon && 
			            ( _DOriFirst[ 1 ] - 
                            Other._DOriFirst[ 1 ] ).Norm() < _Epsilon &&
			            ( _DOriFirst[ 2 ] - 
                            Other._DOriFirst[ 2 ] ).Norm() < _Epsilon;            
                    }
                }
            }   

			return Equals;
		}

		CATBoolean operator!=( WheelPosDef const& Other ) const
		{
			return !( *this == Other );
		}

        // Wheel position list management.

        WheelPosDef const * Next() const { return _Next; }
        WheelPosDef * Next() { return _Next; }
        void SetNext( WheelPosDef * n ) { _Next = n; }

        void Debug() const
        {
            printf( "Time     : %lf\n\n", _Time );
            printf( "Origin   : %lf %lf %lf\n", 
                _Origin.GetX(), _Origin.GetY(), _Origin.GetZ() );
            printf( "\nFrame Orientation : \n" );
            printf( "X-Axis   : %lf %lf %lf\n", 
                _X.GetX(), _X.GetY(), _X.GetZ() );
            printf( "Y-Axis   : %lf %lf %lf\n", 
                _Y.GetX(), _Y.GetY(), _Y.GetZ() );
            printf( "Z-Axis   : %lf %lf %lf\n", 
                _Z.GetX(), _Z.GetY(), _Z.GetZ() );

            if ( _TransDerivsSet[ 0 ] )
                printf( "dOrigin  : %lf %lf %lf\n", _DOrigin[ 0 ].GetX(), 
                    _DOrigin[ 0 ].GetY(), _DOrigin[ 0 ].GetZ() );
            if ( _TransDerivsSet[ 1 ] )
                printf( "ddOrigin : %lf %lf %lf\n", _DOrigin[ 1 ].GetX(), 
                    _DOrigin[ 1 ].GetY(), _DOrigin[ 1 ].GetZ() );
            if ( _TransDerivsSet[ 2 ] )
                printf( "dddOrigin : %lf %lf %lf\n", _DOrigin[ 2 ].GetX(), 
                    _DOrigin[ 2 ].GetY(), _DOrigin[ 2 ].GetZ() );
        }

	private:

        // The current frame location and orientation.

		CATMathPoint _Origin;
		/*CATMathDirection*/CATMathVector _X, _Y, _Z;

        // The higher order derivatives of the frame.

        CATBoolean _TransDerivsSet[ 3 ];
        CATMathVector _DOrigin[ 3 ];

        // Only the first derivatives of the frame orientation can be set 
        // for now, unless euler angles are used.

        CATBoolean _OriDerivsSet[ 3 ];
		CATMathVector _DOriFirst[ 3 ];

        // The Euler angles and higher order derivatives.

        CATBoolean _EulerAnglesSet, _XYZEulerOrder;
        double _XAng, _YAng, _ZAng;
        double _DXAng[ 3 ], _DYAng[ 3 ], _DZAng[ 3 ];

        // The time instant associated with the frame.

        CATBoolean _TimeSet;
		double _Time;

        double _Epsilon;
        WheelPosDef * _Next;

        CATBoolean _IsCorner;
        int _CornerIdx;
        CATMathPoint _CornerOrigin;
        double _CornerBAngle,_CornerAAngle;
		CATMathPoint _RelativeOrigin;
	};

public:

    class ConstIterator
    {
    public:

        ConstIterator( WheelPosDef const * Def = NULL )
            : _Curr( Def )
        {}

        WheelPosDef const * operator*() const { return _Curr; }
        WheelPosDef const * operator->() const { return _Curr; }

        CATBoolean operator!=( ConstIterator const& Rhs ) const
        {
            return !( *this == Rhs );
        }
        CATBoolean operator==( ConstIterator const& Rhs ) const
        {
            return _Curr == Rhs._Curr;
        }

        ConstIterator& operator++() 
        {
            if ( _Curr != NULL ) _Curr = _Curr->Next();
            return *this;
        }

    private:

        WheelPosDef const * _Curr;
    };

public:

	// Create a path from a sequence of keyframes.

	VswpInterpPathDef( WheelPosDef * seq )
		: _PosDefs( seq ), _Size( 0 )
	{
        for ( WheelPosDef const * D = _PosDefs; D; D = D->Next() )
            ++_Size;
    }

	
	VswpInterpPathDef()
		: _PosDefs( NULL ), _Size( 0 )
	{}

	VswpInterpPathDef( VswpInterpPathDef const& iOther )
		: _PosDefs( NULL ), _Size( 0 )
	{
		CopyPathDefs( iOther );
	}

	VswpInterpPathDef& operator=( VswpInterpPathDef const& iOther )
	{
		ClearPathDefs();
		CopyPathDefs( iOther );
		return *this;
	}

    ~VswpInterpPathDef()
    {
		ClearPathDefs();
    }

	// The sequence of "keyframes" of the wheel sweep path.

	ConstIterator Begin() const { return ConstIterator( _PosDefs ); }
	ConstIterator End() const { return ConstIterator(); }

	int Size() const { return _Size; }
	WheelPosDef const& PosDef( int pos_index ) const 
	{ 
        WheelPosDef const * curr = _PosDefs;
        for ( int i = 0; i < pos_index; ++i ) curr = curr->Next();
        return *curr;
	}

	// To avoid unnecessary copy with operator=

	void SetPosDef( WheelPosDef * Seq )
	{
		ClearPathDefs();
		_PosDefs = Seq;
		_Size = 0;
        for ( WheelPosDef const * D = _PosDefs; D; D = D->Next() )
            ++_Size;
	}

	// Get the time span associated with the sweep definition.

	CATMathInterval GetParamRange() const
	{
		WheelPosDef const& PosDef0 = PosDef( 0 );
		WheelPosDef const& PosDefn = PosDef( Size() - 1 );
		CATMathInterval Dm( PosDef0.GetTime(), PosDefn.GetTime() );
        return Dm;
	}

	// Merge two Cr continuous paths.

	void Merge( VswpInterpPathDef& NextPath )
	{
		// Move past the first keyframe and add the rest to the
        // end of this sequence. The next path loses ownership of
        // these position definitions.

        if ( NextPath._PosDefs != NULL && 
             NextPath._PosDefs->Next() != NULL )
        {
            WheelPosDef * CurrLast = _PosDefs;
            while ( CurrLast->Next() != NULL ) 
                CurrLast = CurrLast->Next();

            WheelPosDef * NewPos = NextPath._PosDefs->Next();
            CurrLast->SetNext( NewPos );
            NextPath._PosDefs->SetNext( NULL );

            for ( ; NewPos; NewPos = NewPos->Next() ) ++_Size;
        }
	}

    void Debug() const
    {
        printf( "Num keyframes : %d\n", Size() );
    }

private:

	void ClearPathDefs()
	{
		for ( WheelPosDef * D = _PosDefs; D != NULL; )
		{
			WheelPosDef * DNext = D->Next();
			delete D;
			D = DNext;
		}
	}

	void CopyPathDefs( VswpInterpPathDef const& iOther )
	{
		_Size = iOther.Size();
		_PosDefs = NULL;

		if ( _Size > 0 )
		{
			WheelPosDef const * CurrOther = &iOther.PosDef( 0 );
			_PosDefs = new WheelPosDef( *CurrOther );
			WheelPosDef * Curr = _PosDefs;
			while ( WheelPosDef const* NextOther = CurrOther->Next() )
			{
				WheelPosDef * Next = new WheelPosDef( *NextOther );
				Curr->SetNext( Next );
				Curr = Next;
				CurrOther = NextOther;
			}
		}
	}

private:

	// The sequence of "keyframes"

    int _Size;
	WheelPosDef * _PosDefs;
};


// A specialized version for wheels swept along a circular path. 

class ExportedByCATGMModelInterfaces VswpCircularPathDef 
{
public:

    // Create a path for a wheel rotating about an axis.

	VswpCircularPathDef( VswpRotSurfDef * Def )
		: _RotSf( Def )
	{}

    ~VswpCircularPathDef() { delete _RotSf; }

    // The swept region defined as circularly swept planar profile.

    VswpRotSurfDef const * RotSf() const { return _RotSf; }

	// Get the time span associated with the sweep definition.

	CATMathInterval GetParamRange() const
	{
        CATMathInterval Dm( 0., 2. * CATPI );
        return Dm;
	}

    void Debug() const
    {}

private:

    // The swept region definition.

	VswpRotSurfDef * _RotSf;

};



// The path followed by a wheel. It's defined by a sequence of "keyframes"
// at certain instants of time. The wheel position is defined in terms of 
// current position and orientation of an orthogonal frame. The definition 
// may contain derivatives of the axes of the frame.

// Note that the wheel is defined as a profile spun about a certain axis. 
// The wheel position of any "keyframe" can be identified by applying a 
// coordinate transform on this initial wheel position.

class ExportedByCATGMModelInterfaces VswpWheelSweepDef 
{
public:

	// Create a path from a sequence of keyframes.

	VswpWheelSweepDef( 
			    VswpAxisymBodyDef const * WheelDef,
                VswpInterpPathDef::WheelPosDef * Seq,
			    CATUnicodeString const& L,                
                VswpWheelSweepDef * N = NULL
			    )
		: _WheelDef( WheelDef ), _Label( L ),
		  _Color( 0., 0., 0. ), _Next( N ), _CircularPath( NULL )
	{
        _InterpPath = new VswpInterpPathDef( Seq );
    }

	// Create a circular path.

	VswpWheelSweepDef( 
			    VswpAxisymBodyDef const * WheelDef,			    
                VswpRotSurfDef * R,
                CATUnicodeString const& L,
                VswpWheelSweepDef * N = NULL
			    )
		: _WheelDef( WheelDef ), _Label( L ),
		  _Color( 0., 0., 0. ), _Next( N ), _InterpPath( NULL )
	{
        _CircularPath = new VswpCircularPathDef( R );
    }


    ~VswpWheelSweepDef() 
    {
        delete _InterpPath;
        delete _CircularPath;
    }

	// The descriptive label and color attributes attached to the path.

	CATUnicodeString const& Label() const { return _Label; }
	CATMathVector const& Color() const { return _Color; }
	void SetColor( CATMathVector const& C ) { _Color = C; }

    // This is not a well-defined interface at the moment.

    VswpCircularPathDef const * CircularPath() const 
    { 
        return _CircularPath; 
    }
    VswpInterpPathDef const * InterpPath() const 
    { 
        return _InterpPath; 
    }
    VswpInterpPathDef * InterpPath() { return _InterpPath; }

    // Merge two Cr continuous paths.

	void Merge( VswpWheelSweepDef& NextPath )
    {
        if ( _InterpPath && NextPath._InterpPath )
            _InterpPath->Merge( *( NextPath._InterpPath ) );
    }

    // Wheel path list management.

    VswpWheelSweepDef const * Next() const { return _Next; }
    VswpWheelSweepDef * Next() { return _Next; }
    void SetNext( VswpWheelSweepDef * n ) { _Next = n; }

    void Debug() const
    {
        if ( _InterpPath ) _InterpPath->Debug();
        if ( _CircularPath ) _CircularPath->Debug();
    }

private:

    VswpWheelSweepDef( VswpWheelSweepDef const& Orig ) {}
    void operator=( VswpWheelSweepDef const& Rhs ) {}

	// Miscellaneous attributes.

	CATUnicodeString _Label;
	CATMathVector _Color;

	// Multiple path definitions can share one wheel definition.

	VswpAxisymBodyDef const * _WheelDef;

    // The supported path definitions.

    VswpCircularPathDef * _CircularPath;
    VswpInterpPathDef * _InterpPath;

    // The next path in the movedesign.

    VswpWheelSweepDef * _Next;
};


// The machining operation is a sequence of 'movedesign' operations. Each
// 'movedesign' has an associated wheel definition; a 'movedesign' may have 
// multiple sequences of sweeps. 

class ExportedByCATGMModelInterfaces VswpMoveDesignDef 
{
public:

    class ConstIterator
    {
    public:

        ConstIterator( VswpWheelSweepDef const * Def = NULL )
            : _Curr( Def )
        {}

        VswpWheelSweepDef const * operator*() const { return _Curr; }
        VswpWheelSweepDef const * operator->() const { return _Curr; }

        CATBoolean operator!=( ConstIterator const& Rhs ) const
        {
            return !( *this == Rhs );
        }
        CATBoolean operator==( ConstIterator const& Rhs ) const
        {
            return _Curr == Rhs._Curr;
        }

        ConstIterator& operator++() 
        {
            if ( _Curr != NULL ) _Curr = _Curr->Next();
            return *this;
        }

    private:

        VswpWheelSweepDef const * _Curr;
    };

public:

	VswpMoveDesignDef( 
                VswpAxisymBodyDef * Wh, 
		        VswpWheelSweepDef * Swps, 
                CATUnicodeString const& L,
                VswpMoveDesignDef * N = NULL
                )
		: _Wheel( Wh ), _Sweeps( Swps ), _Label( L ), 
          _Size( 0 ), _Next( N )
	{
        for ( VswpWheelSweepDef const * S = _Sweeps; S; S = S->Next() )
            ++_Size;
    }

    ~VswpMoveDesignDef()
    {
        for ( VswpWheelSweepDef * S = _Sweeps; S != NULL; )
        {
            VswpWheelSweepDef * SNext = S->Next();
            delete S;
            S = SNext;
        }

        delete _Wheel;
    }

	// The descriptive label and color attributes attached to the movedesign.

	CATUnicodeString const& Label() const { return _Label; }

	// The grinding wheel and the sweep paths associated with the movedesign. 

	VswpAxisymBodyDef const& Wheel() const { return *_Wheel; }
    VswpAxisymBodyDef& Wheel() { return *_Wheel; }

	// The paths usually join with C0 continuity. The movedesign usually 
	// starts with the wheel placed away from the blank. The first path moves
	// the wheel very close to the blank. The subsequent path definitions do
	// the actual material removal. The last path definition usually moves
	// the wheel away from the blank without gouging.

	ConstIterator Begin() const { return ConstIterator( _Sweeps ); }
	ConstIterator End() const { return ConstIterator(); }

	// Random access interface.

	int Size() const { return _Size; }
	VswpWheelSweepDef const& SweepDef( int PosIndex ) const 
	{ 
        VswpWheelSweepDef const * Curr = _Sweeps;
        for ( int i = 0; i < PosIndex; ++i ) Curr = Curr->Next();
        return *Curr;
	}

    // Movedesign list management.

    VswpMoveDesignDef const * Next() const { return _Next; }
    VswpMoveDesignDef * Next() { return _Next; }
    void SetNext( VswpMoveDesignDef * N ) { _Next = N; }

    // Remove degenerate sweep path definitions.

    int RemoveDegenerateDefs()
    {
        int NumRemoved = 0;
        VswpWheelSweepDef * pLast = NULL;
        for ( VswpWheelSweepDef * pSwp = _Sweeps; pSwp != NULL; )
        {
            VswpWheelSweepDef * pNext = pSwp->Next();
            VswpInterpPathDef const * pInterp = pSwp->InterpPath();
            if ( pInterp == NULL || pInterp->Size() >= 2 )
                pLast = pSwp;
            else
            {
                ++NumRemoved;
                --_Size;

                if ( pLast == NULL ) _Sweeps = pNext;
                else pLast->SetNext( pNext );
                delete pSwp;
            }
            pSwp = pNext;
        }
        return NumRemoved;
    }

    void Debug() const
    {
        for ( VswpMoveDesignDef::ConstIterator P = Begin();
			    P != End(); ++P )
            P->Debug();
        
        printf( "Num sweeps : %d\n", Size() );
    }

private:

    VswpMoveDesignDef( VswpMoveDesignDef const& Orig ) {}
    void operator=( VswpMoveDesignDef const& Rhs ) {}

	// Miscellaneous attributes.

	CATUnicodeString _Label;	

	// The grinding wheel associated with this movedesign.

	VswpAxisymBodyDef * _Wheel;

	// A movedesign may be composed of multiple sweep paths. 

    int _Size;
	VswpWheelSweepDef * _Sweeps;

    // The next one in the movedesign sequence.

    VswpMoveDesignDef * _Next;
};

#endif 

