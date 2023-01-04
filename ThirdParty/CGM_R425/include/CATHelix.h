#ifndef CATHelix_h
#define CATHelix_h

// COPYRIGHT DASSAULT SYSTEMES 2005
/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 
#include "CATBaseUnknown.h"
#include <stdio.h>
#include "CATCurve.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATIACGMLevel.h"
class CATLaw;
class CATMathFunctionX;
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATHelix ;
#else
extern "C" const IID IID_CATHelix ;
#endif
/**
* Interface describing a geometric helix.
* The CATHelix is created by the <tt>CreateHelix</tt>
* method of the <tt>CATGeoFactory</tt> interface and deleted 
* with the <tt>CATICGMContainer::Remove</tt> method. 
*/
class ExportedByCATGMGeometricInterfaces CATHelix : public CATCurve
{
	CATDeclareInterface;

public:
	/**
	* The type of helix.
	* @param ConstantPitch
	* Helix with a constant pitch.
	* @param VariablePitch
	* Helix with a variable pitch.
	*/
	enum HelixType { ConstantPitch = 0, VariablePitch = +1 };
	/**
	* Returns the axis of <tt>this</tt> CATSphere.
	* @param oAxis
	* The CATMathLine which defines the helix axis.
	*/
	virtual void GetAxis(CATMathLine &oAxis) const =0;
	/**
	* Returns the starting point of <tt>this</tt> CATSphere.
	* @param oPoint
	* The CATMathPoint which defines the starting point.
	*/
	virtual void GetStartingPoint(CATMathPoint &oPoint) const =0;
	/**
	* Returns the pitch of <tt>this</tt> CATSphere.
	* @return
	* The pitch value.
	*/
	virtual double GetPitch() const = 0 ;
	/**
	* Returns the coefficient of linear evolution of the radius 
	* (the radius increase for one turn).
	* @return
	* The value of the coefficient.
	*/
	virtual double GetRadiusEvolution() const = 0 ;
	/**
	* Returns the start angle of <tt>this</tt> CATSphere.
	* @return
	* The value of the angle in radians.
	*/
	virtual CATAngle GetStartAngle() const = 0 ;
	/**
	* Returns the end angle of <tt>this</tt> CATSphere.
	* @return
	* The value of the angle in radians.
	*/
	virtual CATAngle GetEndAngle() const = 0 ;
	/**
	* Returns the trigonometric orientation of <tt>this</tt> CATSphere.
	* @return
	* The value of the orientation: 1 (counterclockwise), -1 (clockwise).
	*/
	virtual CATLONG32 GetTrigonometricOrientation() const = 0;
	/**
	* Retrieves the law which defines how the radius evolves versus the helix length.
	* @param oRadiusLaw
	* The CATLaw to be retrieved.
	*/
	virtual void GetRadiusLaw(const CATLaw *&oRadiusLaw) const = 0;
	/**
	* Retrieves the law which defines how the z coordinates evolves versus the helix length.
	* @param oZLaw
	* The CATLaw to be retrieved.
	*/
	virtual void GetZLaw(const CATLaw *&oZLaw) const = 0;
	/**
	* Retrieves the law which defines the number of turns made by the helix versus its length.
	* @param oThetaLaw
	* The CATLaw to be retrieved.
	*/
	virtual void GetThetaLaw(const CATLaw *&oThetaLaw) const = 0;
	/**
	* Retrieves the angle(in radians) which defines position of the starting point with respect 
	* to the reference CATMathVector.
	* @return 
	* The angle(in radians) to be retrieved.
	*/
	virtual double GetTheta0() const = 0;
	
    /**
    * From V5R21 and V6R209. 
	* Retrieves the angle of a point defined by its CATCrvParam.
	* @param iParam
	* The CATCrvParam.
    * @param oAngle
	* The angle to be retrieved.
	*/
	virtual void GetAngleFromParameter(const CATCrvParam &iParam, CATAngle &oAngle) const = 0;

	/**
	* Retrieves the CATCrvParam of a point defined by its angle.
	* @param iAngle
	* The angle in radians.
    * @param oParam
	* The CATCrvParam to be retrieved.
	*/
	virtual void GetParameterFromAngle(CATAngle iAngle, CATCrvParam &oParam) const = 0;
	/**
	* Retrieves the CATCrvParam of a point defined by its Z coordinate.
	* @param iZ
	* The coordinate of the point along Oz.
    * @param oParam
	* The CATCrvParam to be retrieved.
	*/
	virtual void GetParameterFromZ(double iZ, CATCrvParam &oParam) const = 0;
	
    /**
    * From V5R21 and V6R209. 
	* Retrieves the Z coordinate of a point defined by its CATCrvParam.	
    * @param iParam
	* The input CATCrvParam.
	* @param oZ
	* The coordinate(along Z)to be retrieved.
	*/
	virtual void GetZFromParameter(const CATCrvParam &iParam, double &oZ) const = 0;
	/**
	* Modifies all the characteristics of <tt>this</tt> CATHelix.
	* @param iAxis
	* The new axis.
	* @param iStartingPoint
	* The new starting point.
	* @param iStartAngle
	* The new start angle.
	* @param iEndAngle
	* The new end angle.
	* @param iPitch
	* The new pitch.
	* @param iTrigonometricOrientation
	* The new trigonometric orientation.
	* @param iRadiusEvolution
	* The new radius evolution.
	*/
	virtual void Set(const CATMathLine   &iAxis,
		const CATMathPoint  &iStartingPoint,
		CATAngle            iStartAngle,
		CATAngle            iEndAngle,
		double              iPitch,
		CATLONG32                iTrigonometricOrientation,
		double              iRadiusEvolution = 0.) = 0;
	/**
	* @nodoc
	* Modifies all the characteristics of <tt>this</tt> CATHelix to create an helix
	* with a radius law, a variable pitch.
	* @param iCenter
	* The helix center. This point together with iUnitZ 
	* defines the helix axis.
    * @param iUnitZ
	* The vector which defines the direction of the helix axis. The helix axis passes through iCenter.
	* @param iUnitU
	* Defines a reference for the new helix starting point.
    * @param iRatioU
	* Applies a ratio to the coordinate along the reference vector.
	* @param iRatioV
	* Applies a ration to the coordinate along V.
	* @param iRatioZ
	* Applies a ratio to the Z coordinate.
    * @param iRadiusLaw
	* Defines the radius law, i.e. how the radius evolves versus the helix length.
    * @param iZLaw
	* Defines how the z coordinates evolves versus the helix length.
	* To create a variable pitch helix, you must specify a composite law.
    * @param iThetaLaw
	* Defines the angular law, i.e the number of turns made by the helix versus its length.
	* @param iTheta0
	* Defines a starting point for the new helix. The value must be specified in radians.
	* If 0 is specified, the starting point is located along iUnitU. Otherwise, it is shifted according 
	* to the iTheta0 value.
	* @param iTrigonometricOrientation 
	* The orientation of the rotation about the axis.
	*/
	virtual void Set(CATMathPoint    &iCenter,
		CATMathVector   &iUnitZ,
		CATMathVector   &iUnitU,
		double           iRatioU,
		double           iRatioV,
		double           iRatioZ,
		CATLaw          *iRadiusLaw,
		CATLaw          *iZLaw,
		CATLaw          *iThetaLaw,
		double           iTheta0,
		CATLONG32        iTrigonometricOrientation) = 0;
	/**
	* Modifies the orientation of <tt>this</tt> CATHelix.
	* @param iTrigonometricOrientation
	* The orientation of the rotation about the axis: 1 to turn counterclockwise,
	* -1 to turn clockwise.
	*/
	virtual void SetTrigonometricOrientation(CATLONG32 iTrigonometricOrientation) =0;
	/**
	* Modifies the helix starting with respect to the iUnitU reference vector.
    * @param iTheta0
	* Defines a starting point for the new helix. The value must be specified in radians.
	* If 0 is specified, the starting point is located along iUnitU. Otherwise, it is shifted according 
	* to the iTheta0 value.
	*/
	virtual void SetTheta0(double iTheta0) =0;

};
CATDeclareHandler(CATHelix,CATCurve);

#endif
