//===================================================================
// COPYRIGHT Microsoft 2013/09/09
//===================================================================
// CATMidSurfaceAttr.h
// Header definition of class CATMidSurfaceAttr
//===================================================================


#ifndef CATMidSurfaceAttr_H
#define CATMidSurfaceAttr_H

#include "CATCGMStreamAttribute.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATGeoFactory.h"

class CATFace;


class ExportedByCATGMOperatorsInterfaces CATMidSurfaceAttr : public CATCGMStreamAttribute
{
public:

    CATCGMDeclareAttribute (CATMidSurfaceAttr, CATCGMStreamAttribute);

    // Constructor / destructor
    //-------------------------
    static HRESULT AttachThicknessAttribute(CATFace* iMidSurface, const double iMinThickness, const double iMaxThickness, const double iAverageThickness, const double iOrientedOffset);
    CATMidSurfaceAttr();
    virtual ~CATMidSurfaceAttr();

    //-----------------------------------------------------------------
    //
    // Application dedicated methods
    //
    //-----------------------------------------------------------------

    /**
    *  Get the mid-surface thickness.
    * @param oMinThickness
    * Output : the minimum thickness.
    * @param oMaxThickness
    * Output : the maximum thickness.
    * @param oAverageThickness
    * Output : the average thickness.
    * @return
    *     HRESULT
    */
    HRESULT GetThicknesses (double & oMinThickness, double & oMaxThickness, double & oAverageThickness);

    /**
    *  Get the mid-surface oriented offset. Convention : the value sign is 
    * accorded to CATFace orientation, and points to the offseted face.
    * @param oOrientedOffset
    * Output : the oriented offset.
    * @return
    *     HRESULT    
    */
    HRESULT GetOrientedOffset (double & oOrientedOffset);

    //-----------------------------------------------------------------
    //
    // Internal methods
    //
    //-----------------------------------------------------------------

    /**
    *  Set the mid-surface thickness.
    * @param iMinThickness
    * Input : the minimum thickness.
    * @param iMaxThickness
    * Input : the maximum thickness.
    * @param iAverageThickness
    * Input : the average thickness.
    * @return
    *     void
    */
    void SetThicknesses (double iMinThickness, double iMaxThickness, double iAverageThickness);

    /**
    *  Set the mid-surface oriented offset.
    * @param iOrientedOffset
    * The oriented offset value.
    * @return
    *     void
    */
    void SetOrientedOffset (double iOrientedOffset);

    /**
    *  Set the factory.
    * @param ipFactory
    * The geometric factory.
    * @return
    *     void
    */
    void SetFactory (CATGeoFactory * ipFactory);

    /**
    * Stream / Unstream 
    * Mandatory methods, inherited from CATCGMStreamAttribute.
    */
    void Stream   (CATCGMStream & ioStream) const;
    void UnStream (CATCGMStream & ioStream);

    /**
    * For debug (inherited from CATCGMAttribute).
    */
    void Dump (CATCGMOutput & os);

protected :
    /**
    * For == operator (inherited from CATCGMAttribute).
    * Used in CGMReplay (bodies mapping).
    */
    CATLONG32 Compare(const CATCGMAttribute & iToCompare);

    //CATLONG32 IsEquivalentTo(const CATCGMAttribute & iToCompare, CATGeoFactory * iFactory);

    HRESULT GetEpsilonForComparison( double & oEpsilon );

private:
    // Copy constructor and equal operator
    //------------------------------------
    CATMidSurfaceAttr(const CATMidSurfaceAttr&);
    CATMidSurfaceAttr& operator = (const CATMidSurfaceAttr&);

    // Data members
    //-------------
    short              _streamVersion;
    double             _minThickness;
    double             _maxThickness;
    double             _averageThickness;
    double             _orientedOffset;
    CATGeoFactory *    _factory; // To retrieve tolerance
};

#endif
