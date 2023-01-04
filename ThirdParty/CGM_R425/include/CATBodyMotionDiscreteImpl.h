// COPYRIGHT DASSAULT SYSTEMES 2014

#ifndef CATBodyMotionDiscreteImpl_H
#define CATBodyMotionDiscreteImpl_H

#include "CATGMModelInterfaces.h"
#include "CATCGMNewArray.h"

#include "CATMathTransformation.h"

#include "CGMVswpMoveDesignDef.h"
#include "CGMVswpRotation.h"

#include "CATBodyMotionImpl.h"

#include "CATLISTV_CATMathAxis.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATLISTV_CATMathVector.h"

class CATCurve;
class VswpQuaternionCurve;
class VswpSlerpCurve;
class VswpQuadraturePoints;
class CATCGMStream;
class CATUnicodeString;

//#define BodyMotion_ConvertDPFromRatioToLength

// A C3 interpolation of translation and rotation component of the motion 
// of the wheel from the keyframes.

class ExportedByCATGMModelInterfaces CATBodyMotionDiscreteImpl : public CATBodyMotionImpl
{
	typedef VswpInterpPathDef::WheelPosDef WheelPosDef;

public:
  
    CATCGMNewClassArrayDeclare;

    // Default constructor - should only be used with unstream.

    CATBodyMotionDiscreteImpl(CATSoftwareConfiguration* ipConfig);

    CATBodyMotionDiscreteImpl( 
		        CATGeoFactory * ipFactory,
				CATSoftwareConfiguration* ipConfig,
                VswpInterpPathDef const& PDef
                );

    // Create an interpolation from an ordered sequence of axes.

    CATBodyMotionDiscreteImpl( 
		        CATGeoFactory * ipFactory,
				CATSoftwareConfiguration* ipConfig,
                CATLISTV(CATMathAxis) const& iAxes, 
                CATLISTV(CATMathVector) const& iXFirstDerivatives,
                CATLISTV(CATMathVector) const& iYFirstDerivatives,
                CATLISTV(CATMathVector) const& iZFirstDerivatives,
                CATLISTV(CATMathVector) const& iOrigFirstDerivList,
				CATLISTV(CATMathVector) const& iOrigSecondDerivList,
				CATListOfDouble const& iTimes
                );

    // Create an interpolation from an ordered sequence of axes, with
    // orientations given by euler angles.

    CATBodyMotionDiscreteImpl( 
		        CATGeoFactory * ipFactory,
				CATSoftwareConfiguration* ipConfig,
                CATMathAxis const& iRefAxis, 
                CATLISTV(CATMathPoint) const& iOriginList,
                CATLISTV(CATMathVector) const& iOrigFirstDerivList,
				CATLISTV(CATMathVector) const& iOrigSecondDerivList,
                CATListOfDouble const& iXAnglesAndDerivs,
                CATListOfDouble const& iYAnglesAndDerivs,
                CATListOfDouble const& iZAnglesAndDerivs,
                CATBoolean iXYZOrder,
				CATListOfDouble const& iTimes
                );

    // Create an interpolation from an ordered sequence of axes, with
    // orientations given by euler angles.

    CATBodyMotionDiscreteImpl( 
		        CATGeoFactory * ipFactory,
				CATSoftwareConfiguration* ipConfig,
                CATMathAxis const& iRefAxis, 
                CATLISTV(CATMathPoint) const& iOriginList,
                CATListOfDouble const& iXAngles,
                CATListOfDouble const& iYAngles,
                CATListOfDouble const& iZAngles,
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
                CATBoolean iXYZOrder,
                CATBodyMotion::InterpolationDegree iInterpDegree,
				CATBoolean IsDPParamInRatio
                );

    // Create an interpolation from an ordered sequence of axes, with
    // orientations given by euler angles and corner parameters.
    CATBodyMotionDiscreteImpl( 
      CATGeoFactory * ipFactory,
	  CATSoftwareConfiguration* ipConfig,
      CATMathAxis const& iRefAxis, 
      CATLISTV(CATMathPoint) const& iOriginList,
      CATListOfDouble const& iXAngles,
      CATListOfDouble const& iYAngles,
      CATListOfDouble const& iZAngles,
      CATBoolean iXYZOrder,
      CATBodyMotion::InterpolationDegree iInterpDegree
      );

	// Copy constructor. The state of the iOther object is not copied.

    CATBodyMotionDiscreteImpl( 
                CATBodyMotionDiscreteImpl const& iOther
                );

    ~CATBodyMotionDiscreteImpl();

    // The keyframe definitions that were interpolated.

    VswpInterpPathDef const& PathDef() const { return _PathDef; }	

    // Optimized implementation to calculate the angular velocity.

    //virtual void EvaluateAngularVelocity( 
    //                                double t, 
    //                                CATBoolean EvalBelow,
    //                                CATMathVector & oAngularVelocity 
    //                                ) const;

    // Get the discontinuities of the specified order. The caller owns the
    // output array.

    virtual CATLONG32 GetDiscontinuities( short const Order, double *& Discs ) const;

	virtual CATLONG32 				 
	SplitAtDiscontinuity( short const Order, 
						  CATLISTP(CATBodyMotion)&oMotions ) const;
    // Methods for Replay

	static CATUnicodeString GetNameStatic();
    virtual CATBoolean IsATypeOf(CATBodyMotionImplType iType) const;
    virtual CATUnicodeString GetName() const;

    void SetRefAxis( const CATMathAxis& RefAxis);

protected:

	// Because Initializaiton is called lazily (from Evaluator methods)
	// we need to "preserve" constness, while in reality member data 
	// objects are modified.

	virtual void InitializeVF() const;

	// In case the Initialization fails cleanup the objects that
	// InitilizeVF method has touched, and return the object
	// into the uninitialized state

	virtual void CleanupInitializeVF() const;

    // Concrete evaluate method called by Evaluate.

    virtual void EvaluateVF(
                        double iParameter, 
                        int iNDeriv, 
                        CATBoolean EvalBelow,
                        CATMathAxis & oAxis, 
                        CATLISTV(CATMathTransformation)& olDerivatives
                        ) const;

    virtual double * CreateKnotVectorVF( int &NumKnots ) const;

	virtual void CalculateParameterLimits() const;

	virtual VswpKeyframeDef * CreateKeyframes( 
                                    CATGeoFactory*  ipExternalFactory, 
                                    CATGeoFactory*& opInternalFactory 
                                    ) const;

    // Cache the type of motion, useful when the motion is uniform (linear or
    // angular).

    virtual void SaveMotionType() const;

private:

     // Frame translation evaluator.

    CATMathPoint EvaluateTranslation( 
                                double t,                                 
                                int nDeriv,
                                CATBoolean EvalBelow,
                                CATMathVector const ** dT 
                                ) const;

    // Frame rotation evaluator.

	void EvaluateOrientation( 
                        double t,
                        CATBoolean EvalBelow,
                        VswpRotationMatrix & R,                        
                        int nDeriv,
                        VswpRotationMatrix const ** dR 
                        ) const;

	// Stream/Unstream methods for CGMReplay

	virtual void GetInputObjImpl(CATLISTP(CATICGMObject) &oListOfInputObj) const;
    virtual void StreamImpl( CATCGMStream &oStream, short BodyMotionVersion ) const;
  //  virtual void StreamImpl( CATCGMStream &oStream, short BodyMotionVersion, short iVersion ) const;
    virtual void SetInputObjImpl(CATLISTP(CATICGMObject) &iListOfInputObj);
	virtual void UnstreamImpl( CATCGMStream &ioStream, short BodyMotionVersion );
	//virtual void UnstreamOldImpl( CATCGMStream &ioStream, short BodyMotionVersion);
  virtual void DumpImpl(CATCGMOutput& ioOs) const;

    // Helper methods to fill the oPathDef object

    void FillPathDef( 
                double iEps, 
                CATLISTV(CATMathAxis) const& iAxes, 
                CATLISTV(CATMathVector) const& iXFirstDerivatives,
                CATLISTV(CATMathVector) const& iYFirstDerivatives,
                CATLISTV(CATMathVector) const& iZFirstDerivatives,
                CATLISTV(CATMathVector) const& iFirstDerivList,
                CATLISTV(CATMathVector) const& iSecondDerivList,
                CATListOfDouble const& ioTimes,
                int iNbPoints,
				VswpInterpPathDef & oPathDef
                ) const;

    // This version is for euler angles based input.

    void FillPathDef(
		        double iEps, 
                CATMathAxis const& iRefAxis, 
                CATLISTV(CATMathPoint) const& iOriginList,
                CATLISTV(CATMathVector) const& iOrigFirstDerivList,
			    CATLISTV(CATMathVector) const& iOrigSecondDerivList,
                CATListOfDouble const& iXAnglesAndDerivs,
                CATListOfDouble const& iYAnglesAndDerivs,
                CATListOfDouble const& iZAnglesAndDerivs,
                CATBoolean iXYZOrder,
			    CATListOfDouble const& iTimes,
                VswpInterpPathDef & oPathDef,
                CATListOfInt*  CornerList=NULL
                ) const;

    void FillPathDef(
      double iEps, 
      CATMathAxis const& iRefAxis, 
      CATLISTV(CATMathPoint) const& iOriginList,
      CATLISTV(CATMathVector) const& iOrigFirstDerivList,
      CATLISTV(CATMathVector) const& iOrigSecondDerivList,
      CATListOfDouble const& iXAnglesAndDerivs,
      CATListOfDouble const& iYAnglesAndDerivs,
      CATListOfDouble const& iZAnglesAndDerivs,
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
      CATBoolean iXYZOrder,
      CATListOfDouble const& iTimes,
      VswpInterpPathDef & oPathDef
      ) const;

    // Read the iPathDef into lists of axes and times

    void ReadPathDef(
				VswpInterpPathDef const & iPathDef,
                CATLISTV(CATMathAxis) & oAxes,
                CATLISTV(CATMathVector) & oXFirstDerivatives,
                CATLISTV(CATMathVector) & oYFirstDerivatives,
                CATLISTV(CATMathVector) & oZFirstDerivatives,
                CATLISTV(CATMathVector) & oFirstDerivList,
                CATLISTV(CATMathVector) & oSecondDerivList,
                CATListOfDouble & oTimes,
                CATLONG32 & oNbPoints
                ) const;

    // This version is for euler angles based input.

    void ReadPathDef(
		        VswpInterpPathDef const& iPathDef, 
                CATMathAxis & oRefAxis, 
                CATLISTV(CATMathPoint) & oOriginList,
                CATLISTV(CATMathVector) & oOrigFirstDerivList,
			    CATLISTV(CATMathVector) & oOrigSecondDerivList,
                CATListOfDouble & oXAnglesAndDerivs,
                CATListOfDouble & oYAnglesAndDerivs,
                CATListOfDouble & oZAnglesAndDerivs,
                CATBoolean & oXYZOrder,
			    CATListOfDouble & oTimes
                ) const;

      // This version is for euler angles based input with corner parameters
    void ReadPathDef(
		                    VswpInterpPathDef const& iPathDef, 
                        CATMathAxis & oRefAxis, 
                        CATLISTV(CATMathPoint) & oOriginList,
                        CATLISTV(CATMathVector) & oOrigFirstDerivList,
			                  CATLISTV(CATMathVector) & oOrigSecondDerivList,
                        CATListOfDouble & oXAnglesAndDerivs,
                        CATListOfDouble & oYAnglesAndDerivs,
                        CATListOfDouble & oZAnglesAndDerivs,
                        CATBoolean & oXYZOrder,
			                  CATListOfDouble & oTimes,
                        CATListOfDouble & oDP1List,
                        CATListOfDouble & oDP2List,
                        CATListOfDouble & oATension1List,
                        CATListOfDouble & oATension2List,
                        CATListOfDouble & oBTension1List,
                        CATListOfDouble & oBTension2List,
                        CATListOfDouble & oXTension1List,
                        CATListOfDouble & oXTension2List,
                       CATListOfDouble & oYTension1List,
                       CATListOfDouble & oYTension2List,
                       CATListOfDouble & oZTension1List,
                       CATListOfDouble & oZTension2List
                        ) const;
	//Convert DP Params from length into ratio params
	void ConvertDPParam(const CATMathAxis& RefAxis,
						const CATMathPoint& Translation0,
						const CATMathPoint& Translation1,
						CATListOfDouble& iEulerAngles0,
						CATListOfDouble& iEulerAngles1,
						CATBoolean iXYZOrder,
						CATBoolean IsCornerAt0,
						double iDP,
						double& oDP) const;
#ifdef BodyMotion_ConvertDPFromRatioToLength
	//Convert DP Params from ratio into length params
	void ConvertOldDPToNewParam( const CATMathAxis& RefAxis,
								const CATMathPoint& Translation0,
								const CATMathPoint& Translation1,
								CATListOfDouble& iEulerAngles0,
								CATListOfDouble& iEulerAngles1,
								CATBoolean iXYZOrder,
								CATBoolean IsCornerAt0,
								double iDP,
								double& oDP) const;
#endif
	// Clean up curves

	void Cleanup();

    // Setup any missing translation and orientation derivatives at the
    // keyframes.

    void SetupKeyframeDerivs( VswpKeyframeDef * Frames ) const;

    // Create a cubic curve to interpolate the translation or euler angle
    // component of the moving frame.

    CATCurve * CreateCubicInterpolant(
                                    VswpKeyframeDef const * Frames,
                                    CATBoolean ForTranslation
                                    ) const;

    // Create a quintic curve to interpolate the translation or euler angle
    // component of the moving frame.

    CATCurve * CreateQuinticInterpolant(
                                    VswpKeyframeDef const * Frames,
                                    CATBoolean ForTranslation
                                    ) const;

    // Setup any missing orientation derivatives at the keyframes.

    void SetupKeyframeOrientationDerivs( 
                                    VswpKeyframeDef * Frames 
                                    ) const;

    // Create a C0 curve interpolating the keyframe orientations.

    VswpQuaternionCurve * CreateC0RotationInterpolant(
                                            VswpKeyframeDef const * Frames 
                                            ) const;

    // Create a piecewise C3 hermite interpolant from the keyframes. 

    VswpQuaternionCurve * CreatePiecewiseInterpolant( 
                                            VswpKeyframeDef * Frames 
                                            ) const;

    // The keyframe definitions that were interpolated. The definition
    // might not specify all the derivatives, we interpolate in such
    // cases. The path definition shouldn't be modified, any missing
    // information should be added to the keyframe object.

    mutable VswpInterpPathDef _PathDef;

	// Data from user input to be populated only by stream or constructors. 
    // It should not be used in any context other than 
    // initialize/unstream/dump.

	VswpInterpPathDef _PathDefFromUserInput;

    // The interpolated translation and rotation components of the
    // sweep euclidean motion.

    CATBodyMotion::InterpolationDegree _InterpDegree;
    mutable VswpQuaternionCurve * _pQCurve;

   CATMathAxis _RefAxis;

   //The corners parameters
   mutable CATListOfDouble 
     _DP1List, 
     _DP2List,
     _ATension1List,
     _ATension2List,
     _BTension1List,
     _BTension2List,
     _XTension1List,
     _XTension2List,
     _YTension1List,
     _YTension2List,
     _ZTension1List,
     _ZTension2List;
   CATBoolean _IsInputDPParamInRatio;
   CATBoolean _IsCornerDef;
   mutable CATBoolean _UseGlobalCurve; //temporary
};


#endif 

