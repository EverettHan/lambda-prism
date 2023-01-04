#ifndef CATBodyDatumiserCheckStatus_h_
#define CATBodyDatumiserCheckStatus_h_
// COPYRIGHT DASSAULT SYSTEMES 1999
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
/** @nodoc 
  * Try to Estimate if the import may be successfull just before computing the run process
  *  CATBodyDatumiserCheckStatus_Undefined     = only for initialization;
  *  CATBodyDatumiserCheckStatus_CheckError    = obvious
  *  CATBodyDatumiserCheckStatus_EmptyResult   = no expected solution
  *  CATBodyDatumiserCheckStatus_MayBeClipped  = obvious    
  *  CATBodyDatumiserCheckStatus_FullResult    = no clipping will be done after import
  *  CATBodyDatumiserCheckStatus_NoCheck       = no check done (input scale and output scale are equal ) 
*/
enum CATBodyDatumiserCheckStatus  
{
  CATBodyDatumiserCheckStatus_Undefined     = 0x00 // only for initialization;
 ,CATBodyDatumiserCheckStatus_CheckError    = 0x01 // obvious. Throw if operator run is requested 
 ,CATBodyDatumiserCheckStatus_EmptyResult   = 0x02 // no expected solution. NULL ptr for result if run operator is requested 
 ,CATBodyDatumiserCheckStatus_MayBeClipped  = 0x04 // obvious      
 ,CATBodyDatumiserCheckStatus_FullResult    = 0x08 // no clipping will be done after effective import 
 ,CATBodyDatumiserCheckStatus_NoCheck       = 0x10 // no check done (input scale and output scale are equal )  
 ,CATBodyDatumiserCheckStatus_ToleranceError= 0x20 // Output Factory Tolerance values do not allow the operation. Throw during operator run 
 ,CATBodyDatumiserCheckStatus_ScaleError    = 0x40 // Output Factory ScaleCategory value does not allow the operation. Throw during operator run  
};
#endif
