#ifndef CATDistanceTool_H
#define CATDistanceTool_H

// COPYRIGHT DASSAULT SYSTEMES 2000

/**
 * @level Protected
 * @usage U1
 */ 
#include "Connect.h"
#include "CATDataType.h"

#include "CATIAV5Level.h"
//#if defined ( CATIAV5R11 )
#include "CATCGMVirtual.h"
//#endif  

#include "CATBoolean.h"
#include "CATDistanceToolDef.h"

class CATGeoFactory;
class CATCompositeLaw;
class CATParallelComputer;

class CATMathSetOfPointsND;
class CATMathFunctionX;
class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATLaw;
class CATParallelConnectTool;
class CATCGMOperator;
class CATTopData;
class CATGeometry;

/**
 * Class defining the type of parallel computation and is to be used when you want to 
 * create a parallel curve onto a support. This class does not create directly a curve onto 
 * a support. To do this, you must:
 * <ol>
 * <li>Specify the parameters of the offset distance by using CATDistanceTool: 
 * <ul>
 * <li> the parallelism mode: euclidian or geodesic 
 * <li> the side on which the wire is offset, it is computed from the support normal and the wire tangent: Side = Normal^Tangent 
 * <li> the law which defines the distance evolution along the wire.
 * </ul>
 * <li>Specify the type of relimitation: sharp or round and the support on which the wire is offset.
 * This is done by creating the CATExtrapolParallelTool object. 
 * <li>Create and run the CATTopParallel operator.
 * </ol>
 * The CATDistanceTool class is created by :
 * <ul> 
 * <li> either @href CATCreateTopEuclidianDistanceTool that computes the parallel
 * with an euclidian distance
 * <li> or @href CATCGMCreateTopGeodesicDistanceTool that computes the parallel
 * with a geodesic distance.
 * </ul>
 * This class is the base class for some supplied classes, but you must not derive it yourself.
 */
//#if defined ( CATIAV5R11 )
class ExportedByConnect CATDistanceTool : public CATCGMVirtual
/*
#else 
class ExportedByConnect CATDistanceTool
#endif  
*/
{
  CATCGMVirtualDeclareClass(CATDistanceTool);
 public:

  virtual ~CATDistanceTool();

/**
 * Returns the type of parallelism.
 * @return
 * <ul>
 * <li>1 = GeodesicDistanceToolType_Euclidian
 * <li>or 2 = GeodesicDistanceToolType_Geodesic.
 * </ul>
 */
  virtual short GetType() const=0;

/**
  * Returns the law used to compute the distance.
  * <br>Note that this operator converts the law provided to CATCreateTopEuclidianDistanceTool
  * and CATCGMCreateTopGeodesicDistanceTool into a CATCompositeLaw (if it is not already one).
  * @return
  * The pointer to the law.
  */
  CATCompositeLaw * GetCompositeLaw();

/** 
 * @deprecated V5R11 GetCompositeLaw.
 */
  CATCompositeLaw * GetLaw();

/**
  * Returns the side on which the parallel is computed.
  * @return
  * The side value defined when standing along the face direction and watching in the wire direction.
  * <ul>
  * <li><tt>1</tt> for the left side
  * <li><tt>-1</tt> for the right side.
  * </ul>
  */
  short GetSide();

  /** 
  * @nodoc
  * Specifies the side on which the parallel is computed.
  * @param iSide
  * The side value defined when standing along the face direction and watching in the wire direction.
  * <ul>
  * <li><tt>1</tt> for the left side
  * <li><tt>-1</tt> for the right side.
  * </ul>
  */
	void SetSide(short iSide);

/** @nodoc
 * @nocgmitf
 */
  virtual CATParallelComputer *GetParallelComputer(CATCurve * iCurve,
				                   CATCrvLimits & iCurveLimit,
				                   CATLONG32 iOrientationEdge,
				                   CATBoolean iExtrapolEdge,
				                   CATSurface * iSupport,
				                   CATSurLimits & iSupportLimit,
				                   CATLONG32 iOrientationSupport,
				                   CATBoolean iExtrapolSupport,
                                                   CATParallelConnectTool *iConnectTool,
				                   CATMathSetOfPointsND * iInitPoints,
	                                           CATBoolean iLoopSearch );

/** @nodoc
 * @nocgmitf
 */
	virtual CATCGMOperator * GetProjectOpe(CATGeoFactory * iFacto, CATTopData * iData, CATGeometry * iToProject, CATGeometry * iSupport) =0;
/** @nodoc
 * @nocgmitf
 */
	virtual CATCGMOperator * GetDistOpe(CATGeoFactory * iFacto, CATTopData * iData, CATGeometry * iToProject, CATGeometry * iSupport) =0;

 protected:

/** @nodoc */
  CATDistanceTool( CATGeoFactory * iGeoFactory, CATLaw *iDistance );
  /** @nodoc */
  CATDistanceTool( CATGeoFactory * iGeoFactory, CATCompositeLaw *iDistance );
/** @nodoc */
  CATGeoFactory *_Factory;
/** @nodoc */
  CATCompositeLaw *_Law;
	CATLONG32 _iNewLaw;
/** @nodoc */
  short _Side;

};

#endif
