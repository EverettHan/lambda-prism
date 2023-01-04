
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CATMapParamCrvCrv :
// Converts between global curve parameter of two curves. 
// The conversion GetParamVFromU(..) is faster.
//
//===================================================================
// Usage notes:
//
//===================================================================
// Nov 02   Creation                         D. Johansson
//===================================================================

#ifndef CATMapParamCrvCrv_H  
#define CATMapParamCrvCrv_H 

#include "CATCurve.h" 
#include "CATGMOperatorsInterfaces.h"
#include <stdlib.h>
#include "CATCGMVirtual.h"
class CATSoftwareConfiguration;

class ExportedByCATGMOperatorsInterfaces CATMapParamCrvCrv : public CATCGMVirtual

{    
 public:

/**
 * Object management
 */	

	 virtual ~CATMapParamCrvCrv ();

/**
 * Set tolerance: Default value is the 0.001*"Factory Resolution".
 */	
  virtual void SetTolerance ( double iTOL = 0.0 ) = 0 ;

/**
 * If iCRVU and iCRVV may coincide or intersect
 */	
  virtual void AcceptSmallDistances ( CATLONG32 iYes = 1 ) = 0 ;

/**
 * Set curve interval: Default values are the iCRVI limits. Empty
 * argument, i.e. (1.0, 0.0), returns to the iCRVI limits.
 */
  virtual void SetCurveInterval( double iLowParam = 1.0, double iHighParam = 0.0 ) = 0 ;

/**
 * Run ... Executes the set methods above.
 */	
  virtual void Run () = 0 ;

/**
 * Returns 1 if Run() is OK.
 */	
  virtual CATLONG32 GetDiagnosis() = 0 ; 

/**
 * If iCRVV is extrapolated *oCRVV is an extrapolated copy of *iCRVV. 
 * Otherwise oCRVV = iCRVV. The method returns 1 if extrapolated. Else 0.
 */ 
  virtual CATLONG32 GetChangedCurve ( CATCurve *&oCRVV ) = 0 ; 

/**
 * Set global curve param iParU. The length (ParL) from iCRV(iLowParam)
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the length.
 * 1: the first derivative of the length with respect to the param.
 * 2: the second derivative of the length with respect to the param.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */ 
  virtual double GetParamVFromU ( double iParU  , int iOrder = 0 ) = 0 ;
  
/**
 * Set length from iCRV(iLowParam), iParL. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the first derivative of the param with respect to the length.
 * 2: the second derivative of the param with respect to the length.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */
  //virtual double GetParamUFromV ( double iParV ) = 0 ; not yet
  
/**
 * At creation, private interpolation data might be allocated in excess. 
 * Use "Compress()" if storage size is critical.
 */
  virtual void Compress () = 0 ;
  
} ;

/**
 * Creator ...
 */
ExportedByCATGMOperatorsInterfaces  
CATMapParamCrvCrv * CreateCATMapParamCrvCrv(CATSoftwareConfiguration *iSoftwareConfiguration,const CATCurve *iCRVU, const CATCurve *iCRVV ) ;	 


//DO NOT USE ANYMORE
ExportedByCATGMOperatorsInterfaces  
CATMapParamCrvCrv * CreateCATMapParamCrvCrv(const CATCurve *iCRVU, const CATCurve *iCRVV ) ;	 

#endif  
