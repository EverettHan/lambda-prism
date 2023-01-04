// COPYRIGHT DASSAULT SYSTEMES 2014

#ifndef CGMVswpAxisymBodyDef_H
#define CGMVswpAxisymBodyDef_H

// Raw data for axisymmetric profile used by volumetric sweeping. 

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

// The axis of rotation of an axisymmetric body.

class ExportedByCATGMModelInterfaces VswpAxisOfRotation 
{
public:

    // An axis of rotation defined with a Root point, axis of
    // symmetry and a profile axis defining the plane on which
    // all the profile curves would lie.

    VswpAxisOfRotation(                     
                double const eps,
                CATMathPoint const& Root = 
                    CATMathPoint( 0., 0., 0. ),
                CATMathDirection const& RotAxis = 
                    CATMathDirection( 1., 0., 0. ), 
                CATMathDirection const& ProfileAxis =
                    CATMathDirection( 0., 1., 0. )                
                )
        : _Root( Root ), _RotAxis( RotAxis ), 
          _ProfileAxis( ProfileAxis ), _Epsilon( eps )
    {
        _ProfileNormal = _RotAxis ^ _ProfileAxis;
        _ProfileNormal.Normalize();
    }


    CATMathPoint const& Root() const { return _Root; }
    CATMathDirection const& RotationAxis() const
    {
        return _RotAxis;
    }

    // This is the Other axis defining the plane on which the
    // profile sections would be defined.

    CATMathDirection const& ProfileAxis() const
    {
        return _ProfileAxis;
    }

    // The normal to the profile plane.

    CATMathDirection const& ProfileNormal() const 
    { 
        return _ProfileNormal; 
    }

    CATBoolean OnAxis( CATMathPoint2D const& uv ) const
    {
        double V = uv.GetY();
        return V < _Epsilon;
    }

    // Get the transformation from the local coordinate system
    // of the rotation axes to the WCS.

    CATMathTransformation GetTransform() const
    {
        CATMathAxis Ax;
        Ax.Set( _Root, _RotAxis, _ProfileAxis, _ProfileNormal );

        CATMathTransformation Trf;
        Trf.SetFromOIJKToAxis( Ax );
        return Trf;
    }

    // Map from profile plane parameter space to object
    // space and vice versa.
    
    CATMathPoint Eval( CATMathPoint2D const& UV ) const
    {
        CATMathPoint P = _Root + UV.GetX() * _RotAxis +
            UV.GetY() * _ProfileAxis;
        return P;
    }

    CATMathDirection Eval( CATMathDirection2D const& DUV ) const
    {
        CATMathDirection P = DUV.GetX() * _RotAxis +
            DUV.GetY() * _ProfileAxis;
        return P;
    }

	// Map to positive half plane of rotation. The 'u' direction
    // corresponds to the rotation axis, 'v' is the radial
    // direction. 

    CATMathPoint2D Invert( CATMathPoint const& P ) const
    {
        double U = ( P - _Root ) * _RotAxis;
        CATMathVector radial = ( P - _Root ) - U * _RotAxis;
        double V = radial.Norm();
        return CATMathPoint2D( U, V );
    }

private:

    double _Epsilon;
    CATMathPoint _Root;
    CATMathDirection _RotAxis, _ProfileAxis, _ProfileNormal;
};


// A rotational surface ( blank or wheel ) is composed of rotational 
// sections that are spun about the x-axis.

class ExportedByCATGMModelInterfaces VswpRotSurfDef 
{
public:

	class RotSectionDef 
	{
	public:

		RotSectionDef()
			: _Circular( FALSE ), _Chamfer( FALSE ), _CW( TRUE ), 
			  _Start(0,0), _End(0,0),
			  _Radius( 0. ), _SAngle( 0. ), _EAngle( 0. ),
			  _RoiSection( FALSE ), _Next( NULL )
		{}

		RotSectionDef( 
				CATMathPoint2D const& Start, 
				CATMathPoint2D const& End, 					
				CATBoolean RoiSect,
				CATBoolean Chamfer
				)
			: _Circular( FALSE ), _Chamfer( Chamfer ), _CW( TRUE ), 
			  _Start( Start ), _End( End ),
			  _Radius( 0. ), _SAngle( 0. ), _EAngle( 0. ),
			  _RoiSection( RoiSect ), _Next( NULL )
		{}

		RotSectionDef(
				CATMathPoint2D const& Start, 
				CATMathPoint2D const& End, 
				CATBoolean RoiSect,
				CATMathPoint2D const& Center,
				double Rad,
				double SAng,
				double EAng,
				CATBoolean CW
			    )
			: _Circular( TRUE ), _Chamfer( FALSE ), _CW( CW ), 
			  _Start( Start ), _End( End ), _Center( Center ),
			  _Radius( Rad ), _SAngle( SAng ), _EAngle( EAng ),
			  _RoiSection( RoiSect ), _Next( NULL )
		{}

		RotSectionDef( RotSectionDef const& Orig )
			: _Circular( Orig._Circular ), _Chamfer( Orig._Chamfer ),
			  _CW( Orig._CW ), _Start( Orig._Start ), _End( Orig._End ),
			  _Radius( Orig._Radius ), _SAngle( Orig._SAngle ),
			  _EAngle( Orig._EAngle ), _RoiSection( Orig._RoiSection ),
              _Next( NULL )
		{}

		// A section can be flat (i.e a line perpendicular to x-axis) 
		// or a chamfer (any Other straight line) or round.

		CATBoolean IsFlat() const { return !_Circular && !_Chamfer; }
		CATBoolean IsCircular() const { return _Circular; }
		CATBoolean IsChamfer() const { return _Chamfer; }

		// The end points of the profile section.

		CATMathPoint2D const& Start() const { return _Start; }
		double StartAngle() const { return _SAngle; }
		CATMathPoint2D const& End() const { return _End; }
		double EndAngle() const { return _EAngle; }

		// Additional data for round sections.
		
		CATMathPoint2D const& Center() const { return _Center; }
		double Radius() const { return _Radius; }

		// For round sections, to pick one of the two possible arcs for
		// the given end points.

		CATBoolean IsClockwise() const { return _CW; }

		// Whether this section represents the portion of the wheel
		// that actually grinds the blank.

		CATBoolean IsRotSection() const { return _RoiSection; }
        CATBoolean IsRoiSection() const { return _RoiSection; }
        void SetRoiSection( CATBoolean Roi ) { _RoiSection = Roi; }

        // Reverse the orientation.

        void Reverse()
        {
            CATMathPoint2D SavedStart = _Start;
            _Start = _End;
            _End = SavedStart;

            if ( _Circular )
            {
                _CW = _CW == TRUE ? FALSE : TRUE;
                double SavedSAngle = _SAngle;
                _SAngle = _EAngle;
                _EAngle = SavedSAngle;
            }
        }

        // Sections list management.

        RotSectionDef const * Next() const { return _Next; }
        RotSectionDef * Next() { return _Next; }
        void SetNext( RotSectionDef * n ) { _Next = n; }

	private:

		CATMathPoint2D _Start, _End;

		CATBoolean _Circular, _Chamfer, _CW, _RoiSection;
		double _Radius, _SAngle, _EAngle;
		CATMathPoint2D _Center;

        RotSectionDef * _Next;
	};

public:

    class ConstIterator
    {
    public:

        ConstIterator( RotSectionDef const * Def = NULL )
            : _Curr( Def )
        {}

        RotSectionDef const * operator*() const { return _Curr; }
        RotSectionDef const * operator->() const { return _Curr; }

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

        RotSectionDef const * _Curr;
    };

public:

    class Iterator
    {
    public:

        Iterator( RotSectionDef * Def = NULL )
            : _Curr( Def )
        {}

        RotSectionDef * operator*() { return _Curr; }
        RotSectionDef * operator->() { return _Curr; }

        CATBoolean operator!=( Iterator const& Rhs ) const
        {
            return !( *this == Rhs );
        }
        CATBoolean operator==( Iterator const& Rhs ) const
        {
            return _Curr == Rhs._Curr;
        }

        Iterator& operator++() 
        {
            if ( _Curr != NULL ) _Curr = _Curr->Next();
            return *this;
        }

    private:

        RotSectionDef * _Curr;
    };

public:

	VswpRotSurfDef( 
            RotSectionDef * Sects,
            VswpAxisOfRotation const& Axis
            )
		: _Axis( Axis ), _SectDefs( Sects ), _Size( 0 )
	{
        for ( RotSectionDef const * d = _SectDefs; d; d = d->Next() )
            ++_Size;
    }

    ~VswpRotSurfDef()
    {
        for ( RotSectionDef * d = _SectDefs; d != NULL; )
        {
            RotSectionDef * d_next = d->Next();
            delete d;
            d = d_next;
        }
    }

	// The sequence of cross-sections of the section profile, going in 
	// anti-clockwise sense..

	ConstIterator Begin() const { return ConstIterator( _SectDefs ); }
	ConstIterator End() const { return ConstIterator( NULL ); }
	int Size() const { return _Size; }
	
	// The axis of rotation of the body.

    VswpAxisOfRotation const& RotAxis() const { return _Axis; }
    void SetRotAxis( VswpAxisOfRotation const& Ax ) { _Axis = Ax; }

    // Find the region of the wheel that would actually come into contact 
    // with the blank body. We expect to see chains of smooth corners 
    // separated by single linear segments.

    void ExtractRoi( 
                ConstIterator &SectBegin, 
                ConstIterator &SectEnd 
                ) const
    {
        SectBegin = End();
        for ( ConstIterator i = Begin(); i != End(); ++i )
        {
            if ( !i->IsRoiSection() ) continue;

            // Move to the start of the first smooth corner.
            
            if ( i->IsCircular() ) 
            {
                if ( SectBegin == End() ) SectBegin = i;
                SectEnd = ExtractRoi( SectBegin, FALSE );
                break;
            }
            SectBegin = i;
        }
        CATCGMContractAssert( SectBegin != End() )
    }

private:

    // Propagate to the end of the smooth corner chain.

    ConstIterator ExtractRoi( 
                        ConstIterator RoiSect,
                        CATBoolean PrevCircular 
                        ) const
    {
        CATBoolean SectCircular = RoiSect->IsCircular();
        VswpRotSurfDef::ConstIterator NextSect = RoiSect;
        ++NextSect;
        if ( NextSect == End() ) return End();

        CATBoolean Propagate = ( NextSect->IsRoiSection() &&
                 ( NextSect->IsCircular() || SectCircular ) );
        return Propagate ? 
            ExtractRoi( NextSect, SectCircular ) : ++RoiSect;
    }

    VswpRotSurfDef( VswpRotSurfDef const& Orig ) 
        : _Axis( Orig._Axis )
    {}
    void operator=( VswpRotSurfDef const& Rhs ) {}

	VswpAxisOfRotation _Axis;

    int _Size;
	RotSectionDef * _SectDefs;
};

// The wheel ( and usually the blank ) is an axi-symmetric body.

class ExportedByCATGMModelInterfaces VswpAxisymBodyDef 
{
public:

	VswpAxisymBodyDef()
        : _RotSf(NULL), _Color( 0., 0., 0. )
	{}

	VswpAxisymBodyDef( VswpRotSurfDef * R, 
		CATUnicodeString const& N, CATUnicodeString const& T )
		: _RotSf( R ), _Name( N ), _Type( T ),
		  _Color( 0., 0., 0. )
	{}

    ~VswpAxisymBodyDef() { delete _RotSf; }

	// The Name/Type identifier associated with the body. Usually the
	// wheel has a specific Name associated with it.

	CATUnicodeString const& GetName() const { return _Name; }
	CATUnicodeString const& GetType() const { return _Type; }

	// The color attribute in RGB.

	CATMathVector const& Color() const { return _Color; }
	void SetColor( CATMathVector const& c ) { _Color = c; }

	// The geometry associated with the body.

	VswpRotSurfDef const &RotSf() const { return *_RotSf; }
    VswpRotSurfDef &RotSf() { return *_RotSf; }

	void operator=( VswpAxisymBodyDef const& Rhs ) {}

private:

    VswpAxisymBodyDef( VswpAxisymBodyDef const& Orig ) {}

	// Miscellaneous attributes.

	CATUnicodeString _Name, _Type;
	CATMathVector _Color;

	// The geometry definition.

	VswpRotSurfDef * _RotSf;
};

#endif 
