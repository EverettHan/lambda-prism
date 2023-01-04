#ifndef CATMergedCurve_h
#define CATMergedCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Interface representing the aggregating curve of two curves.
 *<br> The CATMergedCurve is created by the <tt>CreateMergedCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface.
 * The two curves are geometrically confused but may have different limits
 * or parametrizations. If they have the same limits and parametrization,
 * you had better to use the <tt>CATSimCurve</tt> class.
 */

#include "CATEdgeCurve.h"

class CATMathSetOfPointsND;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATMergedCurve ;
#else
extern "C" const IID IID_CATMergedCurve ;
#endif

class ExportedByCATGMGeometricInterfaces CATMergedCurve : public CATEdgeCurve
{
  CATDeclareInterface;

public:
  //------------------------------------------------------------------------
  // A MergedCurve is defined by two Curves ( inc EdgeCurve ).
  // The Curves do not have linear mapping of their parametrization
  // ( if they have, you'd rather use SimCurve ).
  // Merge can be done on only a part of the input curves.
  // Check MergeCurve limits to analyze whether Merge covered the whole curves.
  //------------------------------------------------------------------------
/**
 * Replaces the two curves of a CATMergedCurve.
 * The CATCurve's current limits to use for the aggregation is to be specified.
 * The aggregation takes the intersection of the two intervals.
 */
   virtual void Set( const CATCurve* iC1, const CATCrvLimits & iLim1,
		     const CATCurve* iC2, const CATCrvLimits & iLim2 ) = 0 ;

  //------------------------------------------------------------------------
  // A MergedCurve is defined by two Curves ( inc EdgeCurve ) and a mapping
  // between their respective parameters (the maximum gap value between
  // the curves has also to be provided).
  // The Curves do not have linear mapping of their parametrization
  // ( if they have, you'd rather use SimCurve ).
  // Merge can be done on only a part of the input curves.
  // Check MergeCurve limits to analyze whether Merge covered the whole curves.
  //------------------------------------------------------------------------
/**
 * Replaces the two curves of a CATMergedCurve.
 * The CATCurve's current limits to use for the aggregation is to be specified.
 * The aggregation takes the intersection of the two intervals.
 * Mapping between curve parameters, as well as a maximum gap value have to be
 * provided.
 */
   virtual void Set( const CATCurve* iC1, const CATCrvLimits & iLim1,
	     const CATCurve* iC2, const CATCrvLimits & iLim2,
		   const CATMathSetOfPointsND & iParamMapping,
                   const CATPositiveLength      iMaxGap ) = 0 ;  
 
  /** @nodoc */
  virtual void MiseAJourMapX(CATBoolean & oValideMC) = 0;

};

CATDeclareHandler(CATMergedCurve,CATEdgeCurve);

#endif
