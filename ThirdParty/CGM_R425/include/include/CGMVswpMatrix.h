// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CGMVswpMatrix_H
#define CGMVswpMatrix_H

#include "CATGMModelInterfaces.h"

#include "CATMathVector.h"
#include "CATMath.h"
#include "CATMath3x3Matrix.h"
#include "CATMathAxis.h"

#include "CATCGMContractAssert.h"


class ExportedByCATGMModelInterfaces VswpMatrix3x3 
{    
protected:

    friend class RowOrCol;
    class RowOrCol
    {
    public:

        RowOrCol( VswpMatrix3x3 * m, int i, CATBoolean r )
            : _ConstM( m ), _M( m ), _Index( i ), _IsRow( r )
        {}
        RowOrCol( VswpMatrix3x3 const * m, int i, CATBoolean r )
            : _ConstM( m ), _M( NULL ), _Index( i ), _IsRow( r )
        {}

        int Length() const
        {
            return _IsRow ? _ConstM->NumColumns() 
                : _ConstM->NumRows();
        }
        double operator[]( int i ) const
        {
            return _IsRow ? _ConstM->Elem( _Index, i )
                : _ConstM->Elem( i, _Index );
        }
        void SetElem( int i, double d )
        {
            _IsRow ? _M->SetElem( _Index, i, d )
                : _M->SetElem( i, _Index, d );
        }
        void MakeNull()
        {
            int len = Length();
            for ( int i = 0; i < len; ++i )
                SetElem( i, 0. );
        }

        double operator%( RowOrCol const& Rhs ) const
        {
            int const len = Length();
            double dot = 0.;
            for ( int i = 0; i < len; ++i )
                dot += (*this)[ i ] * Rhs[ i ];
            return dot;
        }

        double operator%( CATMathVector const& Rhs ) const
        {
            double dot = 
				( (*this)[ 0 ] * Rhs.GetX() ) +
				( (*this)[ 1 ] * Rhs.GetY() ) + 
				( (*this)[ 2 ] * Rhs.GetZ() );
            return dot;
        }

        void Pack( CATMathVector &V ) const
        {
			V.SetX( (*this)[ 0 ] );
			V.SetY( (*this)[ 1 ] );
			V.SetZ( (*this)[ 2 ] );
        }

        void UnPack( CATMathVector const &V )
        {
			SetElem( 0, V.GetX() );
			SetElem( 1, V.GetY() );
			SetElem( 2, V.GetZ() );
        }

        void Swap( RowOrCol &Other )
        {
            int len = Length();
            for ( int i = 0; i < len; ++i )
            {
                double SavedElem = (*this)[ i ];
                SetElem( i, Other[ i ] );
                Other.SetElem( i, SavedElem );
            }
        }

        void operator+=( RowOrCol const& Rhs )
        {
            int len = Length();
            for ( int i = 0; i < len; ++i )
                SetElem( i, (*this)[ i ] + Rhs[ i ] );
        }
        void operator-=( RowOrCol const& Rhs )
        {
            int len = Length();
            for ( int i = 0; i < len; ++i )
                SetElem( i, (*this)[ i ] - Rhs[ i ] );
        }

        void operator+=( CATMathVector const& Rhs )
        {
			SetElem( 0, (*this)[ 0 ] + Rhs.GetX() );
			SetElem( 1, (*this)[ 1 ] + Rhs.GetY() );
			SetElem( 2, (*this)[ 2 ] + Rhs.GetZ() );
        }
        void operator-=( CATMathVector const& Rhs )
        {
			SetElem( 0, (*this)[ 0 ] - Rhs.GetX() );
			SetElem( 1, (*this)[ 1 ] - Rhs.GetY() );
			SetElem( 2, (*this)[ 2 ] - Rhs.GetZ() );
        }
        void operator*=( double d )
        {
            int len = Length();
            for ( int i = 0; i < len; ++i )
                SetElem( i, (*this)[ i ] * d );
        }

    private:

        CATBoolean _IsRow;
        int _Index;
        VswpMatrix3x3 * _M;
        VswpMatrix3x3 const * _ConstM;
    };

public:

    VswpMatrix3x3()
        : _Transpose( FALSE ), _IsUnset( TRUE )
    {}


    VswpMatrix3x3( VswpMatrix3x3 const& Orig )
        : _Transpose( Orig._Transpose )
    {
        _IsUnset = Orig.IsUnset();
        if ( !Orig.IsUnset() )
        {
		    for ( int i = 0; i < 3; ++i )
			    for ( int j = 0; j < 3; ++j )
				    SetElem( i, j, Orig.Elem( i, j ) );
        }
    }

    VswpMatrix3x3( CATMath3x3Matrix const& Orig )
        : _Transpose( FALSE ), _IsUnset( FALSE )
    {
		double e[ 3 ][ 3 ];
		Orig.GetCoef( e[ 0 ][ 0 ], e[ 0 ][ 1 ], e[ 0 ][ 2 ],
		              e[ 1 ][ 0 ], e[ 1 ][ 1 ], e[ 1 ][ 2 ],
					  e[ 2 ][ 0 ], e[ 2 ][ 1 ], e[ 2 ][ 2 ] );

		for ( int j = 0; j < 3; ++j )
			for ( int i = 0; i < 3; ++i )
				SetElem( i, j, e[ i ][ j ] );
	}

    VswpMatrix3x3( CATMathAxis const& Axis )
        : _Transpose( FALSE ), _IsUnset( FALSE )
    {
		CATMathVector Col[ 3 ];
		Axis.GetDirections( Col[ 0 ], Col[ 1 ], Col[ 2 ] );

		for ( int j = 0; j < 3; ++j )
		{
			double Coords[ 3 ];
			Col[ j ].GetCoord( Coords );
			for ( int i = 0; i < 3; ++i )
				SetElem( i, j, Coords[ i ] );
		}
	}
    
    VswpMatrix3x3( CATMathVector const& XRow, CATMathVector const& YRow,
        CATMathVector const& ZRow )
        : _Transpose( FALSE ), _IsUnset( FALSE )
    {
        SetRow( 0, CATMathVector( XRow ) );
        SetRow( 1, CATMathVector( YRow ) );
        SetRow( 2, CATMathVector( ZRow ) );
    }
    
    VswpMatrix3x3 &operator=( VswpMatrix3x3 const& Rhs )
    {
        if ( this != &Rhs )
        {
            _IsUnset = Rhs.IsUnset();
            if ( !_IsUnset )
            {
                for ( int i = 0; i < 3; ++i )
				    for ( int j = 0; j < 3; ++j )
					    SetElem( i, j, Rhs.Elem( i, j ) );
            }
            _Transpose = Rhs._Transpose;
        }
        return *this;
    }

    // All the supported types of matrices.

    CATBoolean IsUnset() const { return _IsUnset; }
    CATBoolean IsSquare() const 
    { 
        return TRUE; 
    }
    CATBoolean IsIdentity() const 
    { 
        return FALSE; 
    }
    CATBoolean IsSymmetric() const 
    { 
        return FALSE; 
    }
    CATBoolean IsUpperTriangular() const 
    { 
        return FALSE; 
    }
    CATBoolean IsLowerTriangular() const 
    { 
        return FALSE; 
    }

    CATBoolean IsSkewSymmetric( double const Eps ) const 
    {
        CATBoolean IsSkew = TRUE;
        for ( int i = 0; i < 3 && IsSkew; ++i )
        {
            for ( int j = i; j < 3 && IsSkew; ++j )
            {
                double const &Aij = Elem( i, j );
                if ( i == j )  
                    IsSkew = CATFabs( Aij ) < Eps;
                else
                {
                    double const& Aji = Elem( j, i );
                    IsSkew = CATFabs( Aij + Aji ) < Eps;
                }
            }
        }
        return IsSkew;
    }

    // Matrix query functions.

    int NumRows() const 
    { 
        return 3; 
    }
    int NumColumns() const 
    { 
        return 3; 
    }

    double Elem( int i, int j ) const 
    { 
        CATCGMContractAssert( !IsUnset() );
        return _Transpose ? _Coeffs[ j ][ i ] : _Coeffs[ i ][ j ]; 
    }

    double Trace() const;

    // Initialize to a zero or identify matrix.

    void MakeNull();

    void MakeIdentity();

    // If possible, matrices should be created indirectly or 
    // with functions like add_covariance_vector.

    void SetElem( int i, int j, double d );

    // Access to the rows and columns of the matrix.

	void Column( int C, CATMathVector &V ) const;
	void Row( int R, CATMathVector &V ) const;

	void SetColumn( int C, CATMathVector const &V );
	void SetRow( int r, CATMathVector const &V );

    // Matrix transpose / negation.

    VswpMatrix3x3 Transpose() const;
    void Negate();

    // These are (relatively) optimized ones, preferred over
    // the const version of these binary operations.

    void operator+=( VswpMatrix3x3 const& Rhs );
    void operator-=( VswpMatrix3x3 const& Rhs );
    void operator*=( VswpMatrix3x3 const& Rhs );

    void PreMultiply( VswpMatrix3x3 const& Rhs );

    // These should be used sparingly, preferably when creating
    // a matrix that needs to be modified later.

    VswpMatrix3x3 operator+( VswpMatrix3x3 const& Rhs ) const;
    VswpMatrix3x3 operator-( VswpMatrix3x3 const& Rhs ) const;
    VswpMatrix3x3 operator*( VswpMatrix3x3 const& Rhs ) const;

    // Scale up / down the matrix.
    
    VswpMatrix3x3 operator/( double const& d ) const
    {
        CATCGMContractAssert( !IsUnset() );
        VswpMatrix3x3 Out;
        Out._IsUnset = FALSE;
        Out._Transpose = _Transpose;

        for ( int i = 0; i < 3; ++i )
            for ( int j = 0; j < 3; ++j )
                Out._Coeffs[ i ][ j ] = _Coeffs[ i ][ j ] / d;
        return Out;
    }
    
    VswpMatrix3x3 operator*( double const& d ) const
    {
        CATCGMContractAssert( !IsUnset() );
        VswpMatrix3x3 Out;
        Out._IsUnset = FALSE;
        Out._Transpose = _Transpose;

        for ( int i = 0; i < 3; ++i )
            for ( int j = 0; j < 3; ++j )
                Out._Coeffs[ i ][ j ] = _Coeffs[ i ][ j ] * d;
        return Out;
    }
    
    // Apply the transform on the given vector.

    CATMathVector operator*( CATMathVector const& V ) const;
    void Multiply( CATMathVector const& V, CATMathVector &Out ) const;

    // Convert to CGM form.

    CATMath3x3Matrix ConvertToCATMath3x3Matrix() const
	{
		CATMath3x3Matrix o3x3Matrix;
		o3x3Matrix.SetCoef( Elem( 0, 0 ), Elem( 0, 1 ), Elem( 0, 2 ),
							Elem( 1, 0 ), Elem( 1, 1 ), Elem( 1, 2 ),
							Elem( 2, 0 ), Elem( 2, 1 ), Elem( 2, 2 ) );
		return o3x3Matrix;
	}    

private:

    CATBoolean _Transpose, _IsUnset;
    double _Coeffs[ 3 ][ 3 ];
};


#endif 
