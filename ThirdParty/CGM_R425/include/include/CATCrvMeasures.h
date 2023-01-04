//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//===================================================================
//
//===================================================================
// Usage notes:
//
//===================================================================
//   Forked from CATCrvLengths 11/16 to support more measures
//   Simplified interface to support CATBodyFromLengthOnWire reqs.
//===================================================================

#ifndef CATCrvMeasures_H  
#define CATCrvMeasures_H 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include <stdlib.h>
#include "CATMathInline.h"

#include "CATString.h"
#include "CATDataType.h"
#include "CATListPV.h"
#include "CATListOfInt.h"

#include "CATSkillValue.h"

#include "CATCurve.h" 
#include "CATCGMVirtual.h"
#include "CATGeoFactory.h"
class CATLaw;
class CATCurve ; 
class CATSoftwareConfiguration;


#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
#include "CATBodyFromLengthOnWireMeasureType.h"
//#include "CATCGMOperatorDebug.h"

// class CATCrvLengthsDebug;
class CATCrvMeasuresImpl;

class ExportedByY30UIUTI CATCrvMeasures   : public CATGeoOperator

{    
  CATCGMVirtualDeclareClass(CATCrvMeasures);

 public:

	 /**
	 * Creator ...
	 */
	 static  CATCrvMeasures * Create(
									  CATSoftwareConfiguration * iConfig,
									  const CATCurve *iCRV, 
									  CATBodyFromLengthOnWireMeasureType iType ) ;  

  virtual ~CATCrvMeasures();

/**
 * Set relative tolerance w.r.t factory resolution: 
 * Default value is "Factory Resolution". 
 */  
  virtual void SetRelativeTolerance ( double iTOL );

/**
 * use the existing engine on a new curve ...
 */  
  virtual void SetCurve( const CATCurve *iCRV );

/**
 * Set curve interval: Default values are the iCRV limits. Empty
 * argument, i.e. (1.0, 0.0), returns to the iCRV limits.
 * params are reset if SetCurve is used.
 */
  virtual void SetCurveInterval( double iLowParam  = 1.0,
                         double iHighParam = 0.0 );
  /**
  * Return the type of measure used:
  * Arc length (0) or  Integrated turning angle (1)
  */
  virtual int  GetMeasureType() const;

/**
 * Run
 */  
  virtual int Run();

/**
 * @nodoc @nocgmitf (internal) RunOperator ... Executes the set methods above.
 */  
  virtual int RunOperator();

/**
 * The measure from iCRV(iLowParam) to iCRV(iParU) will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: measure.
 * 1: the first derivative of measure with respect to the param.
 * 2: the second derivative of measure with respect to the param.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */ 
 double GetMeasureFromCurveParam ( double iParU , int iOrder = 0);

/**
 * Get measure from iCRV(iLowParam), to iParM. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the first derivative of the param with respect to the length.
 * 2: the second derivative of the param with respect to the length.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */
 double GetCurveParamFromMeasure ( double iParM , int iOrder = 0);

/**
 * Get measure from iCRV(iLowParam), to iParM. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the param and the first derivative of the param with respect to the measure.
 * 2: the param the first and the second derivative of the param with respect to the measure.
 * iParam the result allcated by caller 
 * iParam[0] : param ; iParam[1] : first derivative ; iParam[2] : second derivative
 */
 void GetCurveParamFromMeasure ( double iParM , int iOrder, double *oMeasure);

/**
 *Get total curve measure 
 */
double GetTotalCurveMeasure();

private:

/**
* iType=0 enables Arc length spacing measure which specifies the curve length between sample points.
* iType=1 enables Integrated turning spacing measure which specifies the total amount the tangent vector 
*		  changes between sample points. Jumps in the tangent vector between edges will be ignored. The 
          expectation is that at vertices, edge pairs are G1 continuous.
**/
  CATCrvMeasures( CATSoftwareConfiguration * iConfig,
	              const CATCurve* iCRV, CATBodyFromLengthOnWireMeasureType iType) ;



  CATCrvMeasuresImpl*         _Impl;

public:  

//========================================================================
// CGMReplay Implementation - SKA Creation
//========================================================================
  /** @nodoc @nocgmitf */
  virtual const CATString       * GetOperatorId();
  virtual       CATGeoOpTimer   * GetTimer();
  /** @nodoc @nocgmitf */
  virtual       CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  /** @nodoc @nocgmitf */
  virtual       void       WriteInput(CATCGMStream  & Str);
  /** @nodoc @nocgmitf */
  virtual       void       Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual       void       WriteOutput(CATCGMStream & Str);
  /** @nodoc @nocgmitf */
  virtual       void       DumpOutput(CATCGMOutput & os) ;
  /** @nodoc @nocgmitf */
  virtual       void       DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual       CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
  /** @nodoc @nocgmitf */
  virtual       CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

//========================================================================

#endif  
