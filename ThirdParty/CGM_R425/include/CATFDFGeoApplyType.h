#ifndef CATFDFGeoApplyType_H
#define CATFDFGeoApplyType_H
//=======================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=======================================================================


/**
* various type of approximation in the power deformation.
*
* <br><b>Role</b>: For choose an algorithm of approximation
* @param CATFDFFUVType
*   Approximation in the L2 sens, with spectral analysis.
* @param CATFDFGlobDefType
*   Fitting of point and normal.
*
* @see @href CATTopDeformation
*/
typedef enum
{
  CATFDFFUVType     = 1,
  CATFDFGlobDefType = 2,
  CATFDFByPlateFeType = 3
}CATFDFGeoApplyType;
#endif




