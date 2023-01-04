#ifndef CATMathTransfoTools_H
#define CATMathTransfoTools_H

//=============================================================================
// 09/18/13 KJD Creation
// 11/10/18 KJD Addition of the public static 2 methods:
//               GetEulerAngles and  ComputeMatrixFromEulerAngles 
//              and of the private ones  GetProperEulerAngles and GetTaitBryanAngles
// 12/05/21 GH7 Add GetEulerAngles for matrix and quaternion  
//=============================================================================

#include "YN000MAT.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathDebug.h"


class CATMathTransformation;
class CATMathLine;
class CATMathAxis;
class CATMath3x3Matrix;
class CATMathQuaternion;

static const int _MathTransfo_EulerAnglesHomogenenization = CATMathDebug::integerGetEnv("CATMathTransfo_EulerAnglesHomogenenization");

/**
* Services dealing with CATMathTransformation which don't need to be located in the public interface
*/ 
class ExportedByYN000MAT  CATMathTransfoTools
{
public:
 
  /**
  *Test if 2 transfo are identical within a linear and an angular tolerance
  */ 
  static CATBoolean AreMathTransfosEqual(const CATMathTransformation & iTransfo1, const CATMathTransformation & iTransfo2, const double  iLinearTol, const double iAngularTol);
  static CATBoolean AreEqual(const CATMathTransformation & iTransfo1, const CATMathTransformation & iTransfo2, const double  iLinearTol, const double iAngularTol); //deprecated
  /**
  * Transform a given transformation into an isometry. Return a diagnosis :
  * - 1 : the input matrix is nearly an isometry, thus a symmetric Newton algorithm has been used ;
  * - 2 : an orthonormalization (Schmidt) could have been performed correctly ;
  * - 3 : an orthonormalization has been performed, but the result may be far from the input matrix
  *       because this matrix is degenerated.
  * - 0 : failure (should not happen).
  */
  static CATLONG32 MakeIsometry (CATMathTransformation & iTransfo, CATMathTransformation & oIsometry);
  
  /**
  * Transform a given transformation into a similitude. Return a diagnosis :
  * - 1 : the input matrix is nearly a similitude, thus a symmetric Newton algorithm has been used ;
  * - 2 : an orthonormalization (Schmidt) could have been performed correctly ;
  * - 3 : an orthonormalization has been performed, but the result may be far from the input matrix
  *       because this matrix is degenerated.
  * - 0 : failure (should not happen).
  */
  static CATLONG32 MakeSimilitude (CATMathTransformation & iTransfo, CATMathTransformation & oSimilitude);

   /**
   * Each 3D rigid motion  can be represented as a helical transformation:
   * a rotation around some axis and a translation along this axis.
   * @param oLine the axis
   * @param oAngle rotation angle around the axis
   * @param oShift translation shift along the axis
   */
   static HRESULT GetHelicalParameters(CATMathTransformation & iTransfo, CATMathLine& oLine, double& oAngle, double& oShift, const double iTol = 0.);


  /**
  * @brief static named axis order parameter for GetEulerAngles
  * 
  * you can use it like this
  * @code 
  *   CATMathTransfoTools::GetEulerAngles( T, CATMathTransfoTools::AxisOrder::XYZ,
  *                                        xAngle, yAngle,zAngle );
  * //equivalent to 
  *   CATLONG32 RotOrder[3] = {0,1,2};
  *   CATMathTransfoTools::GetEulerAngles( T, RotOrder,
  *                                        xAngle, yAngle,zAngle );
  * @endcode 
  * */ 
  struct ExportedByYN000MAT AxisOrder
  {
    public:
    //Euler
    static const CATLONG32 ZYZ[3] ; ///< = {2,1,2} 

    //TaitBryan
    static const CATLONG32 XYZ[3] ; ///< = {0,1,2}
    static const CATLONG32 YZX[3] ; ///< = {1,2,0}
    static const CATLONG32 ZXY[3] ; ///< = {2,0,1}
    
    static const CATLONG32 ZYX[3] ; ///< = {2,1,0}
    static const CATLONG32 YXZ[3] ; ///< = {1,0,2}
    static const CATLONG32 XZY[3] ; ///< = {0,2,1}
    private:
    AxisOrder();
  };

  /**
   * Computes the Euler angles associated to the rotation of the CATMathTransformation iTransfo
   * in radian and under the provided convention iAxisOrder (0 for X, 1 for Y, 2 for Z)
   * For oAngle1 and oAngle3, the range is defined modulo 2Pi radians ([−Pi, Pi]).
   * For oAngle2, the range covers Pi radians (but can't be said to be modulo Pi).
   * For different 3 axes (Tait-Bryan angles), it is [−Pi/2, Pi/2]  and otherwise [0, Pi] (Proper Euler angles) 
   * By default, the selected one is the ZXY Euler Rotation (iAxisOrder={2;0;1})
   * oAngle1 rotate about Z (xyz) => (x'y',z)
   * oAngle2 rotate about X (x'y',z) => (x',y",z')
   * oAngle3 rotate about Y (x',y",z') => (x",y",z")
   */
  static HRESULT GetEulerAngles(const CATMathTransformation & iTransfo, const CATLONG32 iAxisOrder[3], double & oAngle1, double & oAngle2, double & oAngle3);
  static HRESULT GetEulerAngles(const CATMath3x3Matrix & iRotationMatrix, const CATLONG32 iAxisOrder[3], double & oAngle1, double & oAngle2, double & oAngle3);
  static HRESULT GetEulerAngles(const CATMathQuaternion & iRotationQuaternion, const CATLONG32 iAxisOrder[3], double & oAngle1, double & oAngle2, double & oAngle3);

   
   
   /**
   * Compute the transformation associated to the Euler angles given as input
   * in radian and under the provided convention iAxisOrder (0 for X, 1 for Y, 2 for Z)
   */
  static HRESULT ComputeMatrixFromEulerAngles(const CATLONG32 iAxisOrder[3], double iAngle1, double iAngle2, double iAngle3, 
                                               CATMathTransformation & oTransfo,
                                               CATMath3x3Matrix * DTD1 = NULL, CATMath3x3Matrix * DTD2 = NULL, CATMath3x3Matrix * DTD3 = NULL);
  static HRESULT EulerAnglesToTransformation(const CATLONG32 iAxisOrder[3], double iAngle1, double iAngle2, double iAngle3, 
                                      CATMathTransformation & oTransfo);
  static HRESULT EulerAnglesToMatrix(const CATLONG32 iAxisOrder[3], double iAngle1, double iAngle2, double iAngle3, 
                                      CATMath3x3Matrix & oRotMatrix);
  static HRESULT EulerAnglesToQuaternion(const CATLONG32 iAxisOrder[3], double iAngle1, double iAngle2, double iAngle3, 
                                      CATMathQuaternion & oRotQuaternion);

   /**
   * Constructs a transformation of axis systems.
   * This transformation transforms, in the global axis system CATMathOIJK, the coordinates of a point <tt>M</tt> into the coordinates of the point TM such that:
   *  ---> M and TM have the same coordinate values in the axis <tt>iFromAxis</tt> and <tt>iToAxis</tt>. 
   * WARNING : It is supposed that the used CATMathAxis are previously orthonormalized. No reorthonormalization is done !!!
   */
  static void ComputeTransfoWithoutOrthoNormalization(const CATMathAxis & iFromAxis, const CATMathAxis & iToAxis, CATMathTransformation & oTransfo);

private:
  CATMathTransfoTools();
  CATMathTransfoTools(const CATMathTransfoTools &);//Necessary to prevent unwanted automatic creation by compiler
  void operator = (const CATMathTransfoTools &);
  static HRESULT GetProperEulerAngles(const CATMathTransformation & iTransfo, const CATLONG32 iAxisOrder[3], const CATLONG32 iAxisOrientation, 
                                      double & oAngle1, double & oAngle2, double & oAngle3);
  static HRESULT GetTaitBryanAngles(const CATMathTransformation & iTransfo, const CATLONG32 iAxisOrder[3], const CATLONG32 iAxisOrientation, 
                                    double & oAngle1, double & oAngle2, double & oAngle3);

};

#endif
