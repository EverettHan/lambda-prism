// COPYRIGHT DASSAULT SYSTEMES 2014

#ifndef CATBodyMotionImpl_H
#define CATBodyMotionImpl_H

#include "CATBoolean.h"
#include "CATCGMNewArray.h"

#include "CATMathTransformation.h"
#include "CATMath3x3Matrix.h"
#include "CATMathVector.h"
#include "CATMathPoint.h"
#include "CATMathInterval.h"

#include "CATBodyMotion.h"
#include "CATBodyMotionImplType.h"
#include "CATCGMUseCounted.h"

#include "CGMVswpRotation.h"
#include "CGMVswpKeyframeDef.h"
#include "CGMVswpKeyframesCache.h"
#include "CATListOfDouble.h"
#include "CATTolerance.h"
#include "ListPOfCATBodyMotion.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMStream;
class CATCGMOutput;
class CATMathPlane;
class CATUnicodeString;
class CATListValCATMathTransformation;
class CATLISTP(CATICGMObject);

//Temporary (to be able to compile)
class VswpQuadraturePoints;
class VswpKeyframeDef;
//End temporary

// For now, a C2 interpolation of translation and C0 interpolation of the 
// rotation component of the motion of the wheel from the keyframes.

class ExportedByCATGMModelInterfaces CATBodyMotionImpl : public CATCGMUseCounted
{

public:
    CATCGMNewClassArrayDeclare;
    // Default constructor - is used with the derived class constructors
	CATBodyMotionImpl(CATSoftwareConfiguration* ipConfig);

    CATBodyMotionImpl(CATGeoFactory* ipFactory,CATSoftwareConfiguration* ipConfig);

	// Copy constructor
	// Please note: only the external data that was used to create the iOther object
	// is copied. The state of the iOther object is not copied.
    CATBodyMotionImpl(CATBodyMotionImpl const& iOther);

    enum MotionType
    {
	    UniformTranslation,
	    UniformRotation,
	    UniformHelical,
		NonUniformCoPlanar,
	    NonUniform,
		Undefined
    };

    // Whether this is a pure translational or rotational motion.

	CATBoolean IsUniformMotion() const;

	CATBoolean IsUniformTranslation() const;

	CATBoolean IsUniformTranslation( 
		CATMathVector & oLinearVelocity
		) const;

	CATBoolean IsUniformRotation( 
		CATMathPoint & oRoot, 
		CATMathVector & oAngularVelocity
		) const;

	// Whether a non-uniform motion where the points stay in a plane
	// over time.

	CATBoolean IsNonUniformCoPlanar() const;

    // The parameter limits of the motion definition.

    double GetStartParameter() const;
    double GetEndParameter() const;
    CATMathInterval GetParameterLimits() const;

    //Set Flag for A/B Euler Angles Version
    void SetEulerABAnglesMode(CATBoolean iUsingABAngles);
    CATBoolean IsEulerABAnglesMode() const;

      // Evaluator main interface
    void Evaluate(double iParameter, int iNDeriv, CATBoolean EvalBelow,
            CATMathAxis & oAxis, CATLISTV(CATMathTransformation)& olDerivatives) const;

    // Evaluate helper methods
    // Obtains the axis at parameter iTime
    void Evaluate(double iParameter, CATBoolean EvalBelow, CATMathAxis & oAxis) const;

    // Obtains the origin at parameter iTime
    void EvaluatePosition(double iParameter, CATBoolean EvalBelow,
        CATMathPoint & oOrigin) const;

    // Obtains the orientation at parameter iTime
    void EvaluateOrientation(double iParameter, CATBoolean EvalBelow,
        CATMath3x3Matrix & oOrientation) const;

    // The linear velocity component of the velocity field at the
    // given time instant.
    void EvaluateLinearVelocity( double t, CATBoolean EvalBelow,
        CATMathVector & oLinearVelocity ) const;

    // The angular velocity component of the velocity field. 
    // Override this in a derived class if there is a more performant calculation.
    virtual void EvaluateAngularVelocity( double t, CATBoolean EvalBelow,
        CATMathVector & oAngularVelocity ) const;

	// Gets the transformation between position and orientation at time t and the global axis system (for now)
	void EvaluateTransformationFromOIJK(double iParameter, CATBoolean EvalBelow,
        CATMathTransformation & oTransformation) const;

    // Get the discontinuities of the specified order. The caller owns the
    // output array.

    virtual CATLONG32 GetDiscontinuities( short const Order, double *& Discs ) const;

	virtual  CATLONG32 
	SplitAtDiscontinuity( short const Order, 
						  CATLISTP(CATBodyMotion)&oMotions ) const = 0;

private:

	// Kludge: add these so we can handle relative body motion for now
	// Limit who can change the offsets so we don't get strange side effects
	// due to caching, etc.

	friend ExportedByCATGMModelInterfaces CATBodyMotion 
    VolumetricSweepGetTransformedBodyMotion(
                                    CATMathPoint const& iBodyAxisOrigin, 
                                    CATMathVector const& iBodyAxisDirection, 
                                    CATBodyMotion const& iBodyMotion
                                    );
    friend ExportedByCATGMModelInterfaces CATBodyMotion  
    VolumetricSweepGetTransformedBodyMotion(
                                    CATMathPlane const& iBodyRefPlane,
                                    CATMathPlane const& iBodyTargetPlane,
                                    CATBodyMotion const& iBodyMotion
                                    );
	void SetOriginOffset( CATMathVector const & iOriginOffset );
	void SetOrientationChange( CATMath3x3Matrix const & iOrientationChange );

public:

	CATMathVector GetOriginOffset() const;
	CATMath3x3Matrix GetOrientationChange() const;

	// Methods for replay
	
    enum BodyMotionVersion
    {
        BodyMotion_Initial = 1,
        BodyMotion_Version_And_Delta_Pos_And_Interp_Degree = 2,
        BodyMotion_Version_And_Delta_Pos_And_Interp_Degree_And_ABEuler = 3,
        BodyMotion_Version_And_Delta_Pos_And_Interp_Degree_And_ABEuler_And_Corner = 4,
		BodyMotion_Version_And_Delta_Pos_And_Interp_Degree_And_ABEuler_And_Corner_And_DP_In_Length = 5
    };

	// Some implementations of BodyMotion e.g.: CATBodyMotionFixedOrientation
	// may contain a CATICGMObject object(s) (e.g. CATBody). The management of streaming 
    // unstreaming these objects is deligated to the client operator
	// because this::Stream is called after such objects are streamed by the client,
	// GetInputObj should be called prior to Stream and passed to the obj manager. 
	void GetInputObj(CATLISTP(CATICGMObject) &iListOfInputObj) const;
	void Stream(CATCGMStream &iOStream, short BodyMotionVersion) const;

	// Same story as above, we need to use the SetInputObj method
	// Before the Unstream is called 
	void SetInputObj(CATLISTP(CATICGMObject) &iListOfInputObj);
	void Unstream(CATCGMStream &iIStream, short BodyMotionVersion);

	void Dump(CATCGMOutput& ioOs) const;

	static CATBodyMotionImpl * CreateConcreteCATBodyMotionImpl(
                                                    CATCGMStream &iIStream,
													CATGeoFactory * ipFactory,
													CATSoftwareConfiguration* ipConfig,
													CATLISTP(CATICGMObject) &iListOfInputObj,
											        short iBodyMotionVersion
                                                    );
	virtual CATBoolean IsATypeOf(CATBodyMotionImplType iType) const = 0;
    virtual CATUnicodeString GetName() const = 0;

    // virtual base class destructor to allow deletion of derived instances 
    // through a base class pointer. The base class destructror is implemented
    // and will be called by the derived class destructor.
    virtual ~CATBodyMotionImpl();

    VswpQuadraturePoints const * SetTimeSpan( 
                                    CATMathInterval const& Dm,
									CATBoolean Fwd,
                                    int const NumStages,
                                    double const * Pts,
                                    int nDeriv
                                    ) const;

	double* CreateKnotVector(int& oNumKnots ) const;


	// Cleanup the data the Initilize method has generated 
	// make sure that this object is in uninitialized state
	void CleanupInitialize() const;

	const CATTolerance & GetTolerance() const;

protected:

	CATMathVector _deltaPosition;
	CATMath3x3Matrix _deltaOrientation;
  CATBoolean _IsEulerABAnglesMode;
  

	void CheckInitialized() const;

    void SetMotionType(MotionType iMotionType) const;
    MotionType GetMotionType() const;
	virtual void SaveMotionType() const;  // Calculate the motion type (called lazily) - by default motion is always non-uniform

    double const GetEpsilon() const;
    CATGeoFactory* GetFactory() const;
	void SetFactory(CATGeoFactory* ipFactory);
	// Because Initializaiton is called lazily (from Evaluator methods)
	// we need to "preserve" constness, while in reality the sole purpose
	// of this method is to initialize member data objects!
	virtual void InitializeVF() const = 0;

	// Cleaner for the derived classes
	virtual void CleanupInitializeVF() const = 0;

    // Concrete evaluate method called by Evaluate
    virtual void EvaluateVF(double iParameter, int iNDeriv, CATBoolean EvalBelow, CATMathAxis & oAxis, CATLISTV(CATMathTransformation)& oDerivatives) const = 0;

    virtual double* CreateKnotVectorVF( int &NumKnots ) const = 0;

	virtual void CalculateParameterLimits() const = 0;  // Initialize the parameter limits cache (called lazily)
	void SetParameterLimits( CATMathInterval const & iLimits ) const;

    // A simpler representation for uniform motion.
	// TODO
	// For now keep this in the baseclass
	// to be blended with caching infrastructure.
	mutable CATMathPoint _Root;
	mutable CATMathVector _LinV, _AngV;

	// Keyframes cache access
	virtual VswpKeyframeDef* CreateKeyframes( CATGeoFactory* ipExternalFactory,  CATGeoFactory *& opInternalFactory ) const = 0;  
                                                                                               // Set up the keyframes in the cache (called lazily)
                                                                                               // If an internal factory was created during keyframes
                                                                                               // initialization, return the internal factory. The 
                                                                                               // ownership of the internal factory will be passed to 
                                                                                               // the VswpKeyframesCache _Frames object.
	VswpKeyframesCache const & GetKeyframesCache() const;
	mutable VswpKeyframesCacheIter _KeyframesIterator;	// keep protected since we want to take advantage
													// of starting a search from the last span stored

	// External factory
	CATGeoFactory* _pFactory;
	CATBoolean _externalFactoryIsNULL;
	mutable CATBoolean _IsInitialized;
	CATSoftwareConfiguration* _pConfig;

private:

	virtual void GetInputObjImpl(CATLISTP(CATICGMObject) &oListOfInputObj) const=0;
	virtual void StreamImpl(CATCGMStream &iOStream, short BodyMotionVersion) const=0;
	virtual void SetInputObjImpl(CATLISTP(CATICGMObject) &iListOfInputObj)=0;
	virtual void UnstreamImpl(CATCGMStream &iIStream, short BodyMotionVersion)=0;
	virtual void DumpImpl(CATCGMOutput& ioOs) const=0;

    // The specific type of motion.
    mutable MotionType _MotionType;

	// Parameter limits cache
	mutable CATMathInterval _R;

	// Keyframes cache
	mutable VswpKeyframesCache _Frames;
};

// Return a shifted with respect to iBodyAxisOrigin 
// and rotated with respect to iBodyAxisDirection 
// body motion object. 

ExportedByCATGMModelInterfaces CATBodyMotion 
VolumetricSweepGetTransformedBodyMotion(
                        CATMathPlane const& iBodyRefPlane,
                        CATMathPlane const& iBodyTargetPlane,
                        CATBodyMotion const& iBodyMotion
                        );

// The deprecated interface.

ExportedByCATGMModelInterfaces CATBodyMotion 
VolumetricSweepGetTransformedBodyMotion(
                        CATMathPoint const& iBodyAxisOrigin, 
                        CATMathVector const& iBodyAxisDirection, 
                        CATBodyMotion const& iBodyMotion
                        );

#endif 
