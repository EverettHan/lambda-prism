#ifndef CATBodyMotion_H
#define CATBodyMotion_H

// COPYRIGHT DASSAULT SYSTEMES 2014


#include "CATGMModelInterfaces.h"

#include "CATMathAxis.h"
#include "CATMath3x3Matrix.h"
#include "CATLISTV_CATMathAxis.h"
#include "CATLISTV_CATMathVector.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATLISTV_CATMathTransformation.h"
#include "CATListOfDouble.h"

#include "CATCGMValueClassImplHolder.h"


class CATGeoFactory;
class CATBody;
class CATBodyMotionImpl;
class CATMathInterval;
class CATCGMStream;
class CATSoftwareConfiguration;

/**
* @nodoc
* Class used to represent a body motion to be used with the <tt>CATICGMTopSweepVolume</tt> operator.
* 
* This class is designed with "value-class" semantics; it is intended to be owned and passed by value, rather than being allocated on the heap.
* To minimize memory consumption, you are advised to use <tt>CATBodyMotion</tt> objects as locally as possible.  
**/
class ExportedByCATGMModelInterfaces CATBodyMotion 
{
public:

	/**
	* Default constructor.
	* <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
	**/
	CATBodyMotion();

	/**
	* Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iAxisList
    * A list of axis that define the motion.
	**/
	CATBodyMotion( CATLISTV(CATMathAxis) const& iAxisList, CATGeoFactory* ipFactory, CATSoftwareConfiguration* ipConfig);

	/**
	* Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iAxisList
    * A list of axis that define the motion.
    * @param iOriginFirstDerivatives
    * A list of first translation derivatives with respect to the parameter of motion.
    * @param iOriginSecondDerivatives
    * A list of second translation derivatives with respect to the parameter of motion.
    * @param iParameters
    * A list of doubles that define the parameter of motion.
	**/
	CATBodyMotion(	CATLISTV(CATMathAxis) const& iAxisList, 
                    CATLISTV(CATMathVector) const& iOriginFirstDerivatives,
					CATLISTV(CATMathVector) const& iOriginSecondDerivatives,
					CATListOfDouble const& iParameters,
					CATGeoFactory* ipFactory,
					CATSoftwareConfiguration* ipConfig);

	/**
	* Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iAxisList
    * A list of axis that define the motion.
    * @param iFirstDerivatives
    * A list of first translation (vector) and rotation (3x3matrix) derivatives
    * with respect to the parameter of motion.
    * @param iOriginSecondDerivatives
    * A list of second translation derivatives with respect to the parameter of motion.
    * @param iParameters
    * A list of doubles that define the time parameter of motion.
	**/
	CATBodyMotion( CATLISTV(CATMathAxis) const& iAxisList,
                   CATLISTV(CATMathTransformation) const& iFirstDerivatives,
				   CATLISTV(CATMathVector) const& iOriginSecondDerivatives,
				   CATListOfDouble const& iParameters,
				   CATGeoFactory* ipFactory,
				   CATSoftwareConfiguration* ipConfig);

	/**
	* Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iAxisList
    * A list of axis that define the motion.
    * @param iXFirstDerivatives
    * A list of first rotation derivatives in x direction with respect to the parameter of motion.
    * @param iYFirstDerivatives
    * A list of first rotation derivatives in y direction with respect to the parameter of motion.
    * @param iZFirstDerivatives
    * A list of first rotation derivatives in z direction with respect to the parameter of motion.
    * @param iOriginFirstDerivatives
    * A list of first translation derivatives with respect to the parameter of motion.
    * @param iOriginSecondDerivatives
    * A list of second translation derivatives with respect to the parameter of motion.
    * @param iParameters
    * A list of doubles that define the parameter of motion.
	**/
	CATBodyMotion(  CATLISTV(CATMathAxis) const& iAxisList, 
                    CATLISTV(CATMathVector) const& iXFirstDerivatives,
                    CATLISTV(CATMathVector) const& iYFirstDerivatives,
                    CATLISTV(CATMathVector) const& iZFirstDerivatives,
					CATLISTV(CATMathVector) const& iOriginFirstDerivatives,
					CATLISTV(CATMathVector) const& iOriginSecondDerivatives,
					CATListOfDouble const& iParameters,
					CATGeoFactory* ipFactory,
					CATSoftwareConfiguration* ipConfig);

    // An enum to control the degree of interpolation the given data.

    enum InterpolationDegree
    {
        InterpLinear = 1,
        InterpCubic = 3,
        InterpQuintic = 5
    };

	/**
	* Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iRefAxis
    * A reference axis for the translation and rotation parameters.
    * @param iOriginList
    * A list of translations with respect to the parameter of motion.
    * @param iOriginFirstDerivatives
    * A list of first translation derivatives with respect to the parameter of motion.
    * @param iOriginSecondDerivatives
    * A list of second translation derivatives with respect to the parameter of motion.
    * @param iXAnglesAndDerivs
    * A list of rotations ( in radians ) and derivatives about x direction with respect to the parameter of motion.
    * @param iYAnglesAndDerivs
    * A list of rotations ( in radians ) and derivatives about y direction with respect to the parameter of motion.
    * @param iZAnglesAndDerivs
    * A list of rotations ( in radians ) and derivatives about z direction with respect to the parameter of motion.
    * @param iXYZOrder
    * The forward or reversed order in which the X-Y-Z rotations should be applied.
    * @param iParameters
    * A list of doubles that define the parameter of motion.
	**/
    CATBodyMotion( CATMathAxis const& iRefAxis,
                   CATLISTV(CATMathPoint) const& iOriginList,
                   CATLISTV(CATMathVector) const& iOriginFirstDerivatives,
				   CATLISTV(CATMathVector) const& iOriginSecondDerivatives,
                   CATListOfDouble const& iXAnglesAndDerivs,
                   CATListOfDouble const& iYAnglesAndDerivs,
                   CATListOfDouble const& iZAnglesAndDerivs,
                   CATBoolean iXYZOrder,
                   CATListOfDouble const& iParameters,
                   CATGeoFactory* ipFactory,
                   InterpolationDegree iInterpDegree,
				   CATSoftwareConfiguration* ipConfig);

	/**
	* Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iRefAxis
    * A reference axis for the translation and rotation parameters.
    * @param iOriginList
    * A list of translations with respect to the parameter of motion.
    * @param iXAngles
    * A list of rotations ( in radians ) about x direction with respect to the parameter of motion.
    * @param iYAngles
    * A list of rotations ( in radians ) about y direction with respect to the parameter of motion.
    * @param iZAngles
    * A list of rotations ( in radians ) about z direction with respect to the parameter of motion.
    * @param iXYZOrder
    * The forward or reversed order in which the X-Y-Z rotations should be applied.
	**/
    CATBodyMotion( CATMathAxis const& iRefAxis,
                   CATLISTV(CATMathPoint) const& iOriginList,
                   CATListOfDouble const& iXAngles,
                   CATListOfDouble const& iYAngles,
                   CATListOfDouble const& iZAngles,
                   CATBoolean iXYZOrder,                   
                   CATGeoFactory* ipFactory,
                   InterpolationDegree iInterpDegree,
				   CATSoftwareConfiguration* ipConfig);
    /**
    * Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iRefAxis
    * A reference axis for the translation and rotation parameters.
    * @param iOriginList
    * A list of translations with respect to the parameter of motion.
    * @param iAAngles
    * A list of rotations ( in radians ) about x direction with respect to the parameter of motion.
    * @param iBAngles
    * A list of rotations ( in radians ) about y direction with respect to the parameter of motion.
    **/
        CATBodyMotion( CATMathAxis const& iRefAxis,
                   CATLISTV(CATMathPoint) const& iOriginList,
                   CATListOfDouble const& iAAngles,
                   CATListOfDouble const& iBAngles,                 
                   CATGeoFactory* ipFactory,
                   InterpolationDegree iInterpDegree,
				   CATSoftwareConfiguration* ipConfig);
     /**
    * Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iRefAxis
    * A reference axis for the translation and rotation parameters.
    * @param iOriginList
    * A list of translations with respect to the parameter of motion.
    * @param iAAngles
    * A list of rotations ( in radians ) about x direction with respect to the parameter of motion.
    * @param iBAngles
    * A list of rotations ( in radians ) about y direction with respect to the parameter of motion.
    * @param iDP1List
    * A list of double parameters for the computation of Corners (ratio).
    * @param iDP2List
    * A list of double parameters for the computation of Corners (ratio).
    * @param iATension1List
    * A list of double parameters for the computation of Corners.
    * @param iATension2List
    * A list of double parameters for the computation of Corners.
    * @param iBTension1List
    * A list of double parameters for the computation of Corners.
    * @param iBTension2List
    * A list of double parameters for the computation of Corners.
    * @param iXTension1List
    * A list of double parameters for the computation of Corners.
    * @param iXTension2List
    * A list of double parameters for the computation of Corners.
    * @param iYTension1List
    * A list of double parameters for the computation of Corners.
    * @param iYTension2List
    * A list of double parameters for the computation of Corners.
    * @param iZTension1List
    * A list of double parameters for the computation of Corners.
    * @param iZTension2List
    * A list of double parameters for the computation of Corners.
    **/
        CATBodyMotion( CATMathAxis const& iRefAxis,
                   CATLISTV(CATMathPoint) const& iOriginList,
                   CATListOfDouble const& iAAngles,
                   CATListOfDouble const& iBAngles, 
                   CATListOfDouble const& iDP1List,
                   CATListOfDouble const& iDP2List,
                   CATListOfDouble const& iATension1List,
                   CATListOfDouble const& iATension2List,
                   CATListOfDouble const& iBTension1List,
                   CATListOfDouble const& iBTension2List,
                   CATListOfDouble const& iXTension1List,
                   CATListOfDouble const& iXTension2List,
                   CATListOfDouble const& iYTension1List,
                   CATListOfDouble const& iYTension2List,
                   CATListOfDouble const& iZTension1List,
                   CATListOfDouble const& iZTension2List,
                   CATGeoFactory* ipFactory,
                   InterpolationDegree iInterpDegree,
				   CATSoftwareConfiguration* ipConfig );

     /**
    * Constructor. 
    * <br><b>Role:</b>Creates a discrete body motion object.
    * @param iRefAxis
    * A reference axis for the translation and rotation parameters.
    * @param iOriginList
    * A list of translations with respect to the parameter of motion.
    * @param iAAngles
    * A list of rotations ( in radians ) about x direction with respect to the parameter of motion.
    * @param iBAngles
    * A list of rotations ( in radians ) about y direction with respect to the parameter of motion.
    * @param iDP1List
    * A list of double parameters for the computation of Corners.
    * @param iDP2List
    * A list of double parameters for the computation of Corners.
    * @param iATension1List
    * A list of double parameters for the computation of Corners.
    * @param iATension2List
    * A list of double parameters for the computation of Corners.
    * @param iBTension1List
    * A list of double parameters for the computation of Corners.
    * @param iBTension2List
    * A list of double parameters for the computation of Corners.
    * @param iXTension1List
    * A list of double parameters for the computation of Corners.
    * @param iXTension2List
    * A list of double parameters for the computation of Corners.
    * @param iYTension1List
    * A list of double parameters for the computation of Corners.
    * @param iYTension2List
    * A list of double parameters for the computation of Corners.
    * @param iZTension1List
    * A list of double parameters for the computation of Corners.
    * @param iZTension2List
    * A list of double parameters for the computation of Corners.
    **/
		CATBodyMotion(  CATGeoFactory* ipFactory,
						CATSoftwareConfiguration* ipConfig,
						CATMathAxis const& iRefAxis,
						CATLISTV(CATMathPoint) const& iOriginList,
						CATListOfDouble const& iAAngles,
						CATListOfDouble const& iBAngles, 
						CATListOfDouble const& iDP1List,
						CATListOfDouble const& iDP2List,
						CATListOfDouble const& iATension1List,
						CATListOfDouble const& iATension2List,
						CATListOfDouble const& iBTension1List,
						CATListOfDouble const& iBTension2List,
						CATListOfDouble const& iXTension1List,
						CATListOfDouble const& iXTension2List,
						CATListOfDouble const& iYTension1List,
						CATListOfDouble const& iYTension2List,
						CATListOfDouble const& iZTension1List,
						CATListOfDouble const& iZTension2List);
	/**
	* @nodoc 
	**/
	CATBodyMotion( CATBody* ipWireBody, CATGeoFactory* ipFactory,CATSoftwareConfiguration* ipConfig );

	/**
	* Copy constructor. 
	**/
	CATBodyMotion(CATBodyMotion const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATBodyMotion& operator=(CATBodyMotion const& iOther); 

	/**
	* Destructor.
	**/
	virtual ~CATBodyMotion();
	
	/**
	* Gets the start parameter.
	* @return 
	* The start parameter value.
	**/
	double GetStartParameter() const;

	/**
	* Gets the end parameter.
	* @return 
	* The end parameter value.
	**/
	double GetEndParameter() const;

	/**
	* Gets the interval from the start parameter to the end parameter.
	* @return 
	* The <tt>CATMathInterval</tt> for the limits.
	**/
	CATMathInterval GetParameterLimits() const;

	/**
	* Evaluate the body motion at the specified parameter value.
	* @param iParameter
	* The value at which to evaluate.
	* @param iNbDerivatives
	* The number of derivatives to calculate.
	* @param oAxis
	* The calculated position and orientation.
	* @param oDerivatives
	* A list of transformations representing the calculated derivatives.
	**/
    void Evaluate( 
		double iParameter,
		int iNbDerivatives,        
		CATMathAxis & oAxis,
		CATLISTV(CATMathTransformation)& oDerivatives,
        CATBoolean EvalBelow = TRUE ) const;

	/**
	* Evaluate the position of the origin at the specified parameter value.
	* @param iParameter
	* The value at which to evaluate.
	* @param oPosition
	* The calculated position.
	**/
	void EvaluatePosition( 
		double iParameter,
		CATMathPoint & oPosition,
        CATBoolean EvalBelow = TRUE ) const;

	/**
	* Evaluate the orientation at the specified parameter value.
	* @param iParameter
	* The value at which to evaluate.
	* @param oOrientation
	* The calculated orientation.
	**/
	void EvaluateOrientation( 
		double iParameter,
		CATMath3x3Matrix & oOrientation,
        CATBoolean EvalBelow = TRUE ) const;

	/**
	* @nodoc
	* For internal use only.
	**/
	CATBodyMotionImpl const* GetImpl() const;

	/**
	* @nodoc
	* For internal use only.
	**/
	CATBodyMotionImpl const& GetImplRef() const;

	/**
	* @nodoc
	* For internal use Only. Temporary
	**/
	CATBodyMotion( CATBodyMotionImpl* ipImpl );

protected:
	CATCGMValueClassImplHolder _implHolder;
	//CATBodyMotionImpl( CATBodyMotionImpl* ipImpl );
	//CATBodyMotion();

};

#endif 

