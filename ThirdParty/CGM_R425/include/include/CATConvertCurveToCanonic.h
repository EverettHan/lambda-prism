#ifndef CATConvertCurveToCanonic_H
#define CATConvertCurveToCanonic_H

// COPYRIGHT DASSAULT SYSTEMES  2001

/**
* @level Protected
* @usage U1
*/ 

#include "Y30UIUTI.h"

#include "CATBoolean.h"
#include "CATSkillValue.h"

#include "CATGeoOperator.h"

class CATCurveToCanonic;

class CATGeoFactory;

class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCurve;
class CATCrvLimits;
class CATCrvParam;
class CATPCurve;

//#ifdef CATIAV5R14

#include "CATCreateConvertCurveToCanonic.h"
class CATSoftwareConfiguration;

//#endif


/**
* Class representing the geometric operator to compute the most approaching canonical
* curve of a given curve.
* 
 *<ul>
 *<li>The CATConvertCurveToCanonic operator is created with the <tt>CATCreateConvertCurveToCanonic</tt> global function and 
 * directly deleted with the usual C++ <tt>delete</tt> operator.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>GetResult</tt> method, that 
 * can return <tt>NULL</tt>, if no approaching canonic is found.
 *</ul>
*/
class ExportedByY30UIUTI CATConvertCurveToCanonic : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATConvertCurveToCanonic);
public :
	
	//=========================================================
	//- Object management 
	//=========================================================

//#ifdef CATIAV5R14
	/**
	* @nodoc
	* Use the <tt>CreateConvertCurveToCanonic</tt> global methods.
	*/
	CATConvertCurveToCanonic(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
	                         CATEdgeCurve * iEdgeCurve,
	                         CATPointOnEdgeCurve * iStartPOEC,
	                         CATPointOnEdgeCurve * iEndPOEC,
	                         CATSurface * iSupport=NULL);
	
	/**
	* @nodoc
	* Use the <tt>CreateConvertCurveToCanonic</tt> global methods.
	*/
	CATConvertCurveToCanonic(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
	                         CATCurve * iCurve,
	                         CATCrvLimits & iLimits,
	                         CATSurface * iSupport=NULL);
	
	/**
	* @nodoc
	* Use the <tt>CreateConvertCurveToCanonic</tt> global methods.
	*/
	CATConvertCurveToCanonic(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
	                         CATLONG32 iNbCrv,
	                         CATCurve ** iTabCrv,
	                         CATCrvParam * iStartParam,
	                         CATCrvParam * iEndParam,
	                         CATSurface * iSupport=NULL);


//#endif

	/**
	* @nodoc
	* Use the <tt>CreateConvertCurveToCanonic</tt> global methods.
	*/
	CATConvertCurveToCanonic(CATGeoFactory * iFactory,
	                         CATEdgeCurve * iEdgeCurve,
	                         CATPointOnEdgeCurve * iStartPOEC,
	                         CATPointOnEdgeCurve * iEndPOEC,
	                         CATSurface * iSupport=NULL);
	
	/**
	* @nodoc
	* Use the <tt>CreateConvertCurveToCanonic</tt> global methods.
	*/
	CATConvertCurveToCanonic(CATGeoFactory * iFactory,
	                         CATCurve * iCurve,
	                         CATCrvLimits & iLimits,
	                         CATSurface * iSupport=NULL);
	
	/**
	* @nodoc
	* Use the <tt>CreateConvertCurveToCanonic</tt> global methods.
	*/
	CATConvertCurveToCanonic(CATGeoFactory * iFactory,
	                         CATLONG32 iNbCrv,
	                         CATCurve ** iTabCrv,
	                         CATCrvParam * iStartParam,
	                         CATCrvParam * iEndParam,
	                         CATSurface * iSupport=NULL);
	
	/**
	* Destructor.
	*/
	~CATConvertCurveToCanonic();
	
	//=========================================================
	//- Public Methods
	//=========================================================
	
	/**
	* Runs <tt>this</tt> operator.
	*/
	int Run();
	
	/**
	* Returns the pointer to the created canonical curve.
	* @param ioLimits
	* The limits of the created curve.
	* @return
	* The pointer to the created canonical curve, or <tt>NULL</tt> if no result was found.
	* If you do not want to keep it, you must remove it with the @href CATICGMContainer#Remove method.
	*/
	CATCurve * GetResult(CATCrvLimits & ioLimits);
	
	/**
	* Returns the pointer to the created canonical curve, as a CATPCurve.
	* To use when the input curve is a CATEdgeCurve. In this case, a CATSurface
	* must be set at the operator creation.
	* @param ioOrientation
	* The orientation of the created curve, with regards to the input CATEdgeCurve.
	* @param ioLimits
	* The limits of the created curve.
	* @return
	* The pointer to the created canonical CATPCurve, or <tt>NULL</tt> if no result was found.
	* If you do not want to keep it, you must remove it with the @href CATICGMContainer#Remove method.
	*/
	CATPCurve * GetPResult(CATLONG32 & ioOrientation,
	                       CATCrvLimits & ioLimits);
	
	
	/**
	* Defines the recognition mode.
	* @param iMode
    * The recognition mode.
	* <br><b>Legal values</b>:
	*<dl><dt><tt>TRUE</tt> </dt><dd> Exact recognition: the input curve must exactly fit a canonical curve.
	*    <dt><tt>FALSE</tt> </dt><dd> Approximated recognition.
	*</dl>
	*/
	void SetRecognitionMode(CATBoolean iMode=TRUE);

	/**
	* Defines the tolerance to fit the input curve, in case of approximated recognition mode.
	* @param iTolerance
	* The tolerance used in case of an approximated recognition.
	*/
	void SetTolerance(double iTolerance);
	
private:
	CATCurveToCanonic * _CurveToCanonicOper;
};


/**
 * @deprecated V5R14
 * Use CATCreateConvertCurveToCanonic with CATSoftwareConfiguration.
 */ 
ExportedByY30UIUTI
CATConvertCurveToCanonic * CATCreateConvertCurveToCanonic(CATGeoFactory * iFactory,
                                                       CATEdgeCurve * iEdgeCurve,
                                                       CATPointOnEdgeCurve * iStartPOEC,
                                                       CATPointOnEdgeCurve * iEndPOEC,
                                                       CATSurface * iSupport=NULL,
                                                       CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R14
 * Use CATCreateConvertCurveToCanonic with CATSoftwareConfiguration.
 */ 
ExportedByY30UIUTI
CATConvertCurveToCanonic * CATCreateConvertCurveToCanonic(CATGeoFactory * iFactory,
                                                       CATCurve * iCurve,
                                                       CATCrvLimits & iLimits,
                                                       CATSurface * iSupport=NULL,
                                                       CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R14
 * Use CATCreateConvertCurveToCanonic with CATSoftwareConfiguration.
 */ 
ExportedByY30UIUTI
CATConvertCurveToCanonic * CATCreateConvertCurveToCanonic(CATGeoFactory * iFactory,
                                                       CATLONG32 iNbCrv,
                                                       CATCurve ** iTabCrv,
                                                       CATCrvParam * iStartParam,
                                                       CATCrvParam * iEndParam,
                                                       CATSurface * iSupport=NULL,
                                                       CATSkillValue iMode = BASIC);


#endif

