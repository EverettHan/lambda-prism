#ifndef CATIPGMPolygon2Surface_h_
#define CATIPGMPolygon2Surface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATPolygonToSurfMeshFunction.h"


class CATCGMProgressBar;
class CATCldPolygon;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATIPolyMesh;
class CATMathPoint;
class CATMathVector;
class CATPolygon2SurfaceImp;
class CATPowerCldPolygon;
class CATSurface;
class CATTopData;
class CATLISTV(CATMathPoint);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolygon2Surface;

class ExportedByCATGMOperatorsInterfaces CATIPGMPolygon2Surface: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPolygon2Surface();

  /**
	* Run.
	*
	* <br><b>Role</b>:Run
	*
	*
	* @return
	*    0 for success, other for failure.
	*
	*/
  //virtual int Run() = 0;
  /**
   * To set the decimated mesh 
   *
   * <br><b>Role</b>: Define the decimate mesh for parameterization. Use it if the number of original mesh is greater than 45 000 triangles.
   *
   * @param ipDecimatedPolygon [in]
   *  Decimated mesh as CATCldPolygon object. Use this if p2s was instanciated with CATCldPolygon object
   *
   * @return
   *   0 for success, other for failure.
	*    
	*/
  virtual int SetDecimatedPolygon(CATCldPolygon *ipDecimatedPolygon) = 0;

  /**
   * To set the decimated mesh 
   *
   * <br><b>Role</b>: Define the decimate mesh for parameterization. Use it if the number of original mesh is greater than 45 000 triangles.
   *
   * @param ipPolyMesh [in]
   *  Decimated mesh as CATIPolyMesh object. Use this if p2s was instanciated with CATIPolyMesh object
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual int SetDecimatedPolygon(CATIPolyMesh *ipPolyMesh) = 0;

  virtual int SetMaxDeviationG0Allowed(const double Tol) = 0;

  virtual void SetRatioOfReachPoints(const double iRatio = 0.95) = 0;

  // --------------------------------------------------------------------------
  /** @name DEPRECATED SetTolerance . DON'T USE ANYMORE
      @{ */
  /** 
   * SetTolerance.
   *
   * <br><b>Role</b>: Define the accuracy of process.
   *
   * @param iG0 [in]
   *   Maximum deviation allowed. It must be greater or equal to the resolution of factory.
   * @param iSatisfiedRatio [in]
   *   Minimum rate of points to hold. By default it is 95%<->0.95 but use 0.99(99%) if you are not sure.
   * @param iG1 [in]
   *   G1 accuracy. It is not important because p2s doesn't support kind of caonstrants now.
   * @param iG2 [in]
   *   G2 accuracy. It is not important because p2s doesn't support kind of caonstrants now.
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual int SetTolerance(
    double iG0,
    double iSatisfiedRatio = 0.95,
    double iG1 = 0.5,
    double iG2 = 0.001) = 0;

  /** @} */
  // --------------------------------------------------------------------------
  /**
   * To set Degree of Nurbs
   *
   * <br><b>Role</b>: Define degree of nurbs. The degree is the same in both direction.
   *
   * @param iDeg [in]
   *   Degree values
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual int SetDegree(short iDeg) = 0;

  /**
   * To set the maximum number of spans for Nurbs
   *
   * <br><b>Role</b>: Define the "maximum" spans (Nbspans) of the result. NbSpan=NbSpan(in U dir )x NbSpan(in V dir ).
   *
   * @param iNbSpan [in]
   *   Maximum number of spans of the result nurbs
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual int SetNbSpan(int iNbSpan) = 0;

  /**
   * SetNormalizationCoefficient
   *
   * <br><b>Role</b>: Define the internal parametric domain UV for computation. For exemple if it is 5, this means the calculation wil be done in domain [0,lu]x[0,lv]
   * with l(u/v)<=5. This will not be the parametric domain of the result. Generally, we use it in multi energies cases to balance the influence of one order of energies on the others.
   * Don't use if you are not sure!
   *
   * @param iCoeff [in]
   *   Coefficient value
   *
   * @return
   *   0 for success, other for failure.
   *
    */
  virtual int SetNormalizationCoefficient(double iCoeff) = 0;

  /** 
   * Energies to minimize.
   *
   * <br><b>Role</b>: Define which kind of energies to minimize and  its influence. The system minimizes Sum( alpha_i*Energy_i ) i from 0 to 9
   * Energy_i = Intragal of square of the  ith derivate of Surface on it s domain. Don't use if you are not sure!
   *
   * @param iEE[10] [in]
   *   Array of  10 double.  iEE[i] = alpha_i with alpha_i>=0.
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual int SetEnergy(const double iEE [10]) = 0;

  virtual void SetCallback(CATCGMProgressBar *ipProgressBar) = 0;

  /**
   * Activate or desactivate the internal 3d filter..
   *
   * <br><b>Role</b>: This method filters the potential wrong 3d points.
   *
   * @param iNoFilter [in]
   *   TRUE to desactivate, FALSE to activate.
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual int NoFilter(CATBoolean iNoFilter = FALSE) = 0;

  /** 
   * Extrapolation rate of parametrique domain of the result
   *
   * <br><b>Role</b>: Set the rate of inflating of 2d domaine i.e if the computed domaine is [umin,umax]x[vmin,vmax],
   * it wil be [umin-du,umax+du]x[vmin-dv,vmax+dv] with du=iCoef*(umax-umin) and dv=iCoef*(vmax-vmin). Use it if you know what you do.
   *
   * @param iCoef [in]
   *  the rate value
   *
   * @return
   *   0 for success, other for failure.
   *
   */
  virtual void SetMarginCoef(const double iCoef) = 0;

  /** 
	* To active or not the smoothing of intput mesh.
	*
	* <br><b>Role</b>: if it is actived, the mesh  will be smoothed before computation.
	*
	* @param iSmoothInput [in]
	*   TRUE to activate, FALSE to smooth.
	*
	* @return
	*   Explain return values
	*
	*/
  virtual int SetSmoothInput(const CATBoolean iSmoothInput) = 0;

  /**
	* To authorize the input with wholes
	*
	* <br><b>Role</b>: To authorize the input with wholes. by default it is denied.
	*
	* @param iWithHoles [in]
	*   TRUE to authorize, FALSE to denied.
	*
	*/
  virtual void SetWithHoles(CATBoolean iWithHoles) = 0;

  /**
	*UseMeshUVLayerAsFitUV
	* <br><b>In CATIPolyMesh context, this method authorizes the operator to use the UV layer of the mesh, if there is, as the fitting uv. 
	*    Be aware that the validity of the UVs is under your responsibility </b>: 
	* 
	*/
  virtual void UseMeshUVLayerAsFitUV() = 0;

  /** 
   * To retrieve the result as face. 
   * <br><b>Role</b>: To retrieve directly the face. This doesn' exempt the call of GetResult().
   * @return
   *   Result as face.
   */
  virtual CATFace *GetFace() const = 0;

  /**
   * Deviation max of the result.
   * <br><b>Role</b>: Return maximum deviation of the result.
   * @return
   *   Deviation max of the result.
    */
  virtual double GetErrorG0Max() const = 0;

  /** 
   * G1 Error max of the result.
   * <br><b>Role</b>: Return maximum G1 error of the result.
   * @return
   *   G1 Error max of the result.
   */
  virtual double GetErrorG1Max() const = 0;

  /** 
   * G2 Error max of the result.
   * <br><b>Role</b>: Return maximum G2 error of the result.
   * @return
   *   G2 Error max of the result.
   */
  virtual double GetErrorG2Max() const = 0;

  /** 
   * the rate of holded points .
   * <br><b>Role</b>: Return the rate of holded points.
   * @return
   *    the rate of holded points .
   */
  virtual double GetRatioOkMax() const = 0;

  /** 
	* To retrieve the points which are out of tolerance.
	* <br><b>Role</b>: Fill the list with the points which are out of tolerance.
	* @param olPointsKO [out]
	*   List to fill
	* @return
	*    0 for success, other for failure.
	*/
  virtual int GetListOfPointsOutTolerance(
    CATLISTV(CATMathPoint) &olPointsKO) const = 0;

  /**
	* Special mode of P2S. that permits to avoid  topolocal construction of the result
	* That meaans the Body result will not be constructed. so If it sets to true,
	* GetResult an GetFace will return ni pointer. Call GetSurface() rather.
	* <br><b>Role</b>: Set if the result is the body  surface.
	* @param iSurfaceOnly [in]
	*   FALSE body is create, TRUE no.
	*/
  virtual void SurfaceOnly(const CATBoolean iSurfaceOnly = FALSE) = 0;

  virtual CATSurface *GetSurface() = 0;

  /** 
   * UNDER DEVELOPMENT FOR UNFOLD, DON'T USE WITHOUT RAQ's ADVICE
   * Enable automatic filtering of highly distorted points.
   */
  virtual void SetEnableAutomaticFiltering() = 0;

  /** 
   * nodoc
   *
   */
  virtual int SetBoundMaxDeviationG0Allowed(const double iTolG0) = 0;

  //virtual int SetBoundMaxDeviationG1Allowed( const double iTolG1 )=0;// a virer
  virtual double GetBoundMaxDeviationG0() const = 0;

  virtual double GetBoundMaxDeviationG1() const = 0;

  virtual double GetInnerMaxDeviation() const = 0;

  virtual int SetG1Constraints(
    const int iNbG1Csts,
    const int *ipG1VtxIdx,
    const CATMathVector *ipNormals,
    const double iTolG1,
    const CATBoolean iOnlyForChecking) = 0;

  /** 
   * nodoc
   *
   */
  virtual int Add(CATEdge *iEdge) = 0;

  virtual void SetReferenceFace(CATFace *iRefFace) = 0;

  virtual int Set2DFiltering(const CATBoolean iFiltered2D) = 0;

  virtual int ForceParamLimits(CATBoolean iForce) = 0;

  virtual void SetUVLimits(const double iUVLimits[4]) = 0;

  virtual void GetUVLimits(double iUVLimits[4]) const = 0;

  virtual CATBoolean IsConsistentUV(double iU, double iV) const = 0;

  virtual CATPowerCldPolygon *GetPowerCldPolygon() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolygon2Surface(); // -> delete can't be called
};

/**
* Creation of p2s with CATIPolyMesh objet
*
* <br><b>Role</b>: Creation of p2s with CATIPolyMesh objet
*
* @param iFactory [in]
*   CATGeoFactory object
* @param iData [in]
*   CATTopData object
* @param ipPolyMesh [in]
*   The mesh to fit as CATIPolyMesh object
*
* @return [out, IUnknown#Release]
*   The pointer to the p2s operator in case of success and NULL in case of failure.
*
*/
ExportedByCATGMOperatorsInterfaces CATIPGMPolygon2Surface *CATPGMCreatePolygon2Surface(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATIPolyMesh *ipPolyMesh);

/** 
* Creation of p2s in context of mesh  CATCldPolygon objet
*
* <br><b>Role</b>: Creation of p2s in context of mesh  CATCldPolygon objet
*
* @param iFactory [in]
*   CATGeoFactory object
* @param iData [in]
*   CATTopData object.
* @param iCldPolygon [in]
*   The mesh to fit as CATCldPolygon object
* @param iLevel [in]
*   The level of operator. It is will be absolete. So put it to 9.
*
* @return [out, IUnknown#Release]
*   The pointer to the p2s operator in case of success and NULL in case of failure.
*
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolygon2Surface *CATPGMCreatePolygon2Surface(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATCldPolygon *iCldPolygon,
  const short iLevel = 0);

/**
* Creation of p2s in context of cloud of points
*
* <br><b>Role</b>: Creation of p2s in context of cloud of points
*
* @param iFactory [in]
*   CATGeoFactory object
* @param iData [in]
*    CATTopData object.
* @param iCldPolygon [in]
*   Points to fit as CATPowerCldPolygon object
* @param iLevel [in]
*    The level of operator. It is will be absolete. So put it to 9.
*
* @return [out, IUnknown#Release]
*   The pointer to the p2s operator in case of success and NULL in case of failure.
*
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolygon2Surface *CATPGMCreatePolygon2Surface(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPowerCldPolygon *iCldPolygon,
  const short iLevel = 0);

#endif /* CATIPGMPolygon2Surface_h_ */
