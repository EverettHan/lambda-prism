// COPYRIGHT DASSAULT SYSTEMES 2014CATBodyMotionFixedOrientationImpl

#ifndef CATBodyMotionFixedOrientationImpl_H
#define CATBodyMotionFixedOrientationImpl_H

#include "CATGMModelInterfaces.h"
#include "CATMathTransformation.h"
#include "CATBodyMotionImpl.h"
#include "CATListOfDouble.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATEdge.h"

class CATBody;
class CATEdge;
class CATCGMStream;
class CATUnicodeString;
class CATSoftwareConfiguration;
// Motion along a path defined by the input wireBody
// the orientation of the body remains fixed.

class ExportedByCATGMModelInterfaces CATBodyMotionFixedOrientationImpl : public CATBodyMotionImpl
{

public:
    CATCGMNewClassArrayDeclare;

// Default constructor - should only be used with unstream
    CATBodyMotionFixedOrientationImpl(CATSoftwareConfiguration* ipConfig);

    CATBodyMotionFixedOrientationImpl( 
		        CATGeoFactory* ipFactory,
				CATSoftwareConfiguration* ipConfig,
                CATBody* pWireBody
                );

    // Copy Constructor
    // Please note: only data that is essential is deep copied.
    // The cached data from the iOther object is NOT copied.
    CATBodyMotionFixedOrientationImpl( 
                CATBodyMotionFixedOrientationImpl const& iOther
                );

	~CATBodyMotionFixedOrientationImpl();

    // Optimized implementation to calculate the angular velocity
    virtual void EvaluateAngularVelocity( double t, CATBoolean EvalBelow,
        CATMathVector & oAngularVelocity ) const;

    // Methods for Replay
	static CATUnicodeString GetNameStatic();
    virtual CATBoolean IsATypeOf(CATBodyMotionImplType iType) const;
    virtual CATUnicodeString GetName() const;

	virtual CATLONG32 
	SplitAtDiscontinuity( short const Order, 
						  CATLISTP(CATBodyMotion)&oMotions ) const;
	virtual CATLONG32 GetDiscontinuities(short const Order,
										 double *& Discs) const;
protected:

	// Because Initializaiton is called lazily (from Evaluator methods)
	// we need to "preserve" constness, while in reality member data 
	// objects are modified.
	virtual void InitializeVF() const;

	// In case the Initialization fails cleanup the objects that
	// InitilizeVF method has touched, and return the object
	// into the uninitialized state
	virtual void CleanupInitializeVF() const;

    // Concrete evaluate method called by Evaluate
    virtual void EvaluateVF(double iParameter, int iNDeriv, CATBoolean EvalBelow,
        CATMathAxis & oAxis, CATLISTV(CATMathTransformation)& olDerivatives) const;

    virtual double * CreateKnotVectorVF( int &NumKnots ) const;

	virtual void CalculateParameterLimits() const;

	virtual VswpKeyframeDef* CreateKeyframes( CATGeoFactory*   ipExternalFactory, 
											  CATGeoFactory *& opInternalFactory ) const;

	virtual void SaveMotionType() const;

private:

	// Stream/Unstream methods for CGMReplay
	virtual void GetInputObjImpl(CATLISTP(CATICGMObject) &oListOfInputObj) const;
    virtual void StreamImpl(CATCGMStream &oStream, short BodyMotionVersion) const;
    virtual void SetInputObjImpl(CATLISTP(CATICGMObject) &iListOfInputObj);
	virtual void UnstreamImpl(CATCGMStream &ioStream, short BodyMotionVersion);
	virtual void DumpImpl(CATCGMOutput& ioOs) const;

	void Cleanup();

	CATBody* _pWireBody;  // TODO: do we need a smart pointer here?
	mutable CATEdge* _pSweepEdge;
  mutable CATLISTP(CATEdge) _pSweepEdgeList;
  
  //versionned fixes
  CATBoolean _ParamCrvFix; 
};


#endif 

