#ifndef CATICGMEdgeCurveComputation_h_
#define CATICGMEdgeCurveComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"

class CATCrvLimits;
class CATCrvParam;
class CATEdgeCurve;
class CATMapX;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMEdgeCurveComputation;

/**
* Class defining the operator to create an edge curve. This operator is to be preferred to
* the methods offered by CATGeoFactory as 
* it manages non linear parameterization of curves.
* <ul>
* <li>The CATICGMEdgeCurveComputation operator is created with the <tt>CATCGMCreateEdgeCurveComputation</tt> method and 
* directly released with the <tt>Release</tt> method. It is is not streamable. 
* <li>It can be used in two modes:
* <ul>
* <li>the <tt>BASIC</tt> mode, the operation is automatically performed at the operator creation. 
* <li>the <tt>ADVANCED</tt> mode, options can be specified with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
* </ul>
* </ul>
*/
class ExportedByCATGMModelInterfaces CATICGMEdgeCurveComputation: public CATICGMOperator
{
public:
	/**
	* Constructor
	*/
	CATICGMEdgeCurveComputation();

	/**
	* Returns the created edge curve. 
	* @return 
	* The pointer to the created edge curve, <tt>NULL</tt> if the initial curves cannot be merged.
	*/
	virtual CATEdgeCurve *GetEdgeCurve() const = 0;

	/**
	* Defines the domains of the curves to be used for the edge curve computation (<tt>ADVANCED mode</tt>).
	* <br>
	* The start and end CATCrvParam for each curve specify a relative direction
	* which do not affect the relative orientation of the input curves within the edge curve.
	* @param iStartParam1
	* The parameter of the start limit of the first curve.
	* @param iEndParam1
	* The parameter of the end limit of the first curve.
	* @param iStartParam2
	* The parameter of the start limit of the second curve. 
	* @param iEndParam2
	* The parameter of the end limit of the second curve.
	*/
	virtual void SetParams(
		const CATCrvParam &iStartParam1,
		const CATCrvParam &iEndParam1,
		const CATCrvParam &iStartParam2,
		const CATCrvParam &iEndParam2) = 0;

	/**
	* Defines the domains of the curves to take into account (<tt>ADVANCED mode</tt>).
	* <br>The relative orientation (start-end of each curve) is not specified.
	* @param iLimits1
	* The limits of the first curve.
	* @param iLimits2
	* The limits of the second curve.
	*/
	virtual void SetLimits(
		const CATCrvLimits &iLimits1,
		const CATCrvLimits &iLimits2) = 0;

	/**
	* Defines the maximum gap between the initial curves above which the edge curve cannot be created
	*(<tt>ADVANCED mode</tt>).
	* @param iMaxGap
	* The maximum gap value. By default, a gap around 1mm is allowed.
	*/
	virtual void SetMaxGap(const double iMaxGap) = 0;

protected:
	/**
	* Destructor
	*/
	virtual ~CATICGMEdgeCurveComputation(); // -> delete can't be called
};

#endif /* CATICGMEdgeCurveComputation_h_ */
