#ifndef CATTransfoManager_H
#define CATTransfoManager_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

//Windows compatibility
#include "YP00IMPL.h"

//GeometricObjects libraries
#include "CATCloneManager.h"
#include "CATCGMNewArray.h"

//Mathematics libraries
#include "CATMathDef.h"

class CATGeometry;
class CATICGMObject;
class CATSurface;
class CATCurve;
class CATGeoFactory;
class CATTransfoUnknown;
class CATMathTransformation1D;
class CATMathTransformation2D;
class CATMathTransformation;
class CATMathNonLinearTransformation;
class CATCrvLimits;
class CATSurLimits;
class CATMapGeoToAssoc;

/**
 * Class representing the process of geometric transformation of a CATGeometry.<br>
 * <ul>
 * <li>The transformation process takes the forward links  into account
 * <li>A CATTransfoManager can process several CATGeometry at the same time.
 * <li>If the transformation is linear, a CATTransfoManager has two modes of transformation:
 *<dl><dt>CATTransfoManager::Duplicate</dt><dd>Duplicates and transforms the objects
 * that are <tt>Add</tt>ed to the CATTransfoManager 
 *    <dt>CATTransfoManager::Replace</dt><dd>Only transforms the objects
 * that are <tt>Add</tt>ed to the CATTransfoManager.
 *</dl>
 * <li>A CATTransfoManager does not duplicate or replace a forward linked object 
 * if it is geometrically invariant by the transformation, 
 * except if this forward linked object
 * is specifically <tt>Add</tt>ed to the CATTransfoManager. Invariant means that
 * it is invariant within its maximum limits. A line is invariant
 * by a transformation along its direction, a circle is invariant by a rotation
 * of center the center of the circle, as examples.
 * A CATTransfoManager duplicates or replaces a forward linked object 
 * if it is not geometrically invariant by the transformation
 * <li>A CATTransfoManager offers two types of methods:
 *<ul>
 * <li>"user methods" that are called by the application programmer 
 * to transform CATGeometry: <tt>Add</tt>, <tt>Run</tt>
 * <li>"object methods" that are called by the CATGeometry to
 * ask for the transformation of their forward linked objects. 
 * These methods must not be normally called,
 * except in the <tt>CATGeometry::Move3D</tt> and 
 * <tt>CATGeometry::CloneAndMove3D</tt> methods, 
 * if you intend to create your own CATGeometry class.
 *</ul>
 * <li>The objects of this class are temporary and cannot be streamed
 * </ul>
 */
class ExportedByYP00IMPL CATTransfoManager: public CATCloneManager
{
public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Defines the mode of the transformation process.
 * @param CATTransfoManager::Duplicate
 * Duplicates and transforms the objects
 * that are <tt>Add</tt>ed to the CATTransfoManager.
 * <br>Does not duplicate a forward linked object 
 * if it is geometrically invariant by the transformation, 
 * except if this forward linked object
 * is specifically <tt>Add</tt>ed to the CATTransfoManager.
 * Duplicates a forward linked object 
 * if it is not geometrically invariant by the transformation.
 * @param CATTransfoManager::FullDuplicate
 * Duplicates and transforms the objects
 * that are <tt>Add</tt>ed to the CATTransfoManager.
 * <br>Duplicates a forward linked object 
 * even if it is geometrically invariant by the transformation, 
 * @param CATTransfoManager::Replace
 * Only transforms the objects
 * that are <tt>Add</tt>ed to the CATTransfoManager.
 * <br>Does not replace a forward linked object 
 * if it is geometrically invariant by the transformation, 
 * except if this forward linked object
 * is specifically <tt>Add</tt>ed to the CATTransfoManager. 
 * Replaces a forward linked object 
 * if it is not geometrically invariant by the transformation.
 * <br>Invariant means that it is invariant within its maximum limits. An line is invariant
 * by a transformation along its direction, a circle is invariant by a rotation
 * of center the center of the circle, as examples.
 */
  enum CATTransfoManagerType {Duplicate = +10, FullDuplicate = +90, Replace = +50 };

  //***************************************************************************
  //****** USER METHODS
  //***************************************************************************

/**
 * Constructs a CATTransfoManager for linear transformation.
 * @param iMathTransfo
 * The transformation to apply.
 * @param iFactory
 * A pointer to the factory of the resulting objects
 * @param iType
 * The mode of the transformation process.
 * @param  iConfig
 * The pointer to the configuration.Should not be <tt>NULL</tt> in case of topological objects.
 */
  CATTransfoManager(const CATMathTransformation  &iMathTransfo     ,
		               CATGeoFactory                 *iFactory         ,
		               CATTransfoManagerType          iMode   = Duplicate,
                   CATSoftwareConfiguration      *iConfig = NULL);

 /**
   * Adds a CATGeometry to transform with <tt>this</tt> CATTransfoManager.
   *<br>All the added objects must belong
   * to the same factory.
   * @param iObjectToTransform
   * A pointer to the CATGeometry to add to the CATTransfoManager.
   * @param iTransformedObject
   * If not NULL, it forces the transformation of <tt>iObjectToTransform</tt> to be
   * the object <tt>iTransformedObject</tt>. This must be compatible with the
   * given transformation of the CATTransfoManager.
   */
  void Add(CATICGMObject * iObjectToTransform    ,
           CATICGMObject * iTransformedObject = 0);

  /**
   * Runs the CATTransfoManager process.
   * This method should be called only once.
   */
  int Run();

 /**
  * Retrieves the CATMathTransformation associated with <tt>this</tt>
  * CATTransfoManager.
	* @param oMathTransfo
  * The associated transformation. This is part of the class and must not be deleted.
  */
  void GetMathTransformation(CATMathTransformation * &oMathTransfo) const;
                                 
  








  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /** @nodoc */
  CATCGMNewClassArrayDeclare;
  

/**
 * @nodoc
 * Constructs a CATTransfoManager for non-linear transformation.
 * <br>Internal use.
 * @param iMathTransfo
 * The non-linear transformation to apply. 
 * @param iFactory
 * A pointer to the factory of the resulting objects
 */
  CATTransfoManager(const CATMathNonLinearTransformation  &iMathTransfo,
		                CATGeoFactory                         * iFactory,
                    CATSoftwareConfiguration              * iConfig = NULL );


 /**
  * @nodoc
  * Retrieves the CATMathNonLinearTransformation associated with <tt>this</tt>
  * CATTransfoManager.
	* <br>Internal use.
	* @param oMathTransfo
  * The associated transformation. This is part of the class and must not be deleted.
  */
  void GetMathNonLinearTransformation(CATMathNonLinearTransformation * &oMathTransfo) const;

/**
 * @nodoc
 * Retrieves the 1D-transformation to apply to a CATGeometry 
 * which forward linked object is a CATCurve.
 * Let us take the following example:
 * <pre>CATPointOnCurve -> CATCurve</pre>
 * If CATCurve is invariant by the CATTransfoManager process, it is sufficient
 * to use a 1D transformation in the space of the CATCurve to transform the
 * CATPointOnCurve that points it.
 * A non-invariant object may also return a 1D-transformation.
 * @param iCurve
 * The curve that is invariant by the CATTransfoManager process.
 * @param Transfo1D
 * The transformation to apply for processing a CATGeometry that points <tt>iCurve</tt> .
 * This object is part of the class and must not be deleted.
 */
  CATLONG32 RetrieveTransfoW(CATCurve                *  iCurve    ,
		        CATMathTransformation1D * &oTransfo1D);

  //***************************************************************************
  //****** OBJECTS METHODS
  //***************************************************************************

/**
 * @nodoc
 * Retrieves the inverse transformation associated with <tt>this</tt>
 * CATTransfoManager.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>.
 */
  void GetMathTransformationInverse(CATMathTransformation * &oMathTransfoInverse);

/**
 * @nodoc
 * Tests whether the associated transformation is the identity.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <tt>1</tt> if the associated transformation is the identity , <tt>0</tt> otherwise.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>.
 */
  CATBoolean IsIdentity() const;

/**
 * @nodoc
 * Tests whether the associated transformation is a similitude.
 * @param ioRatio
 * The value of the scaling, if the associated transformation is a similitude.
 * If <tt>NULL</tt>, this argument is not output.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <tt>1</tt> if the associated transformation is a similitude, <tt>0</tt> otherwise.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>.
 */
  CATBoolean IsSimilitude(CATPositiveLength * ioRatio = NULL) const;

/**
 * @nodoc
 * Retrieves the orientation change of the associated transformation.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>.
 * @param ioOrientationChange
 * If the associated transformation is linear:
 * <tt>-1</tt> for a indirect transformation and <tt>1</tt> for a direct
 * transformation.
 */
  void GetOrientationChange(CATLONG32 & ioOrientationChange) const;
  
/**
 * @nodoc
 * Processes the transformation of a CATGeometry (except CATCurve and
 * CATSurface).
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>
 * to ask for the transformation of a forward linked object.
 */
  void Compute(CATGeometry *  iObjectToTransform,
	       CATGeometry * &oTransformedObject);

 /**
 * @nodoc
 * Processes the transformation of a CATSurface.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>
 * to ask for the transformation of a forward linked object that is a surface.
 * @param iSurfaceToTransform
 * A pointer to the surface to transform.
 * @param oTransformedSurface
 * A pointer to the resulting surface.
 * @param oTransfo2D
 * The 2D-transformation to apply to an object that points the surface, if
 * this surface is invariant. This object is part of the class and must not be deleted.
  */
  void ComputeUV(CATSurface*               iSurfaceToTransform,
		 CATSurface*              &oTransformedSurface,
		 CATMathTransformation2D* &oTransfo2D         );

 /**
 * @nodoc
 * Processes the transformation of a CATCurve.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>
 * to ask for the transformation of a forward linked object that is a curve.
 *@param iCurveToTransform
 * A pointer to the curve to transform.
 * @param oTransformedCurve
 * A pointer to the resulting curve
 * @param oTransfo1D
 * The 1D-transformation to apply to an object that points the curve, if
 * this curve is invariant. This object is part of the class and must not be deleted.
  */
  void ComputeW(CATCurve*                 iCurveToTransform,
		CATCurve*                &oTransformedCurve,
		CATMathTransformation1D* &oTransfo1D       );

/**
 * @nodoc
 * Tests whether the CATGeometry has been detected as invariant by
 * <tt>this</tt> CATTransfoManager.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <tt>1</tt> if the CATGeometry has been detected as invariant by
 * <tt>this</tt> CATTransfoManager, <tt>0</tt> otherwise.
 *<br> "Object method": to be only called by the methods
 * <tt>CATGeometry::CloneAndMove3D</tt> and <tt>CATGeometry::Move3D</tt>.
 */
  CATBoolean IsInvariant(CATGeometry* iIn);

/**
 * @nodoc
 * Processes the transformation of a CATGeometry. 
 *<br> "Object method": to be only called by the <tt>CATGeometry::CloneAndMove3D</tt> method.
 * @param iIn
 * The object to transform. 
 * @return
 * A pointer to the transformed object.
  */
  CATICGMObject* ComputeImage(CATICGMObject * iIn);

/** 
 * Associates a CATMathTransformation1D to a curve to apply it on CATGeometry
 * that points to it. 
 * This is especially usefull together with the <tt>Add</tt> method to replace a transformed curve by another curve
 * confused with it.
 * If it is not the case , the generated model will not be valid.
 * @param iIn
 * A pointer to the input curve.
 * @param iTransfo1D
 * The 1D transformation on the curve corresponding to the 3D transformation defined by <tt>this</tt>. 
 */
  void SetTransfoW(CATCurve                * iIn       ,
		   CATMathTransformation1D  &iTransfo1D);

/**
 * Associates a CATMathTransformation2D to a Surface to apply it on CATGeometry
 * that points to it.
 * This is especially usefull together with the <tt>Add</tt> method to replace a transformed surface by another 
 * surface confused with it.
 * If it is not the case , the generated model will not be valid.
 * @param iIn
 * A pointer to the input surface.
 * @param iTransfo2D
 * The 2D transformation on the surface corresponding to the 3D transformation defined by <tt>this</tt>. 
 */
  void SetTransfoUV(CATSurface              * iIn       ,
		    CATMathTransformation2D  &iTransfo2D);

/**
 * @nodoc
 * Associates a CATCrvLimits to a curve. If a limit has already been associated to this curve,
 * the current limit will inflate the previous one.
 * @param iIn
 * A pointer to the input curve.
 * @param iBox
 * The limits to assiocate to the curve. 
 */
  void AddToBoxW(CATCurve    * iIn ,
		 CATCrvLimits &iBox);
 

/**
 * @nodoc
 * Associates a CATSurLimits to a surface. If a limit has already been associated to this curve,
 * the current limit will inflate the previous one.
 * @param iIn
 * A pointer to the input surface.
 * @param iBox
 * The limits to assiocate to the surface. 
 */
  void AddToBoxUV(CATSurface    * iIn ,
		  CATSurLimits   &iBox);

/**
  * @nodoc
  * Associates a new CATMathTransformation  with <tt>this</tt>
  * CATTransfoManager. To use only with CATTransfoManager::Duplicate.
  * @param iMathTransfo
  * The new transformation.
  */
  void SetTransformation(const CATMathTransformation & iMathTransfo);

/**
  * @nodoc
  * Allow to replace a surface by another which is not confused with it
  */
  void SetNoCheckInAdd();

/**
  * @nodoc
  * Enables or Disables invariance computation
  */
  void SetCheckInvariance(CATBoolean iMode);

  virtual ~CATTransfoManager();

protected:
  /**/
  //---------------------------------------------------------------------------
  //- Data
  //---------------------------------------------------------------------------
  //Main data
	/** @nodoc */
  CATMathTransformation          * _MathTransfo, * _MathTransfoInverse;
	/** @nodoc */
  CATMathNonLinearTransformation * _MathNonLinearTransfo;
	/** @nodoc */
  CATLONG32                             _TransfoType;

  //Information concerning the MathTransformation
	/** @nodoc */
  CATPositiveLength _Ratio; 

  //Other data
	/** @nodoc */
  CATTransfoUnknown   * _TransfoUnknown;
	/** @nodoc */
  CATMapGeoToAssoc    * _MapCurveToAssoc;

	/** @nodoc */
  CATLONG32              _OrientationChange;

	/** @nodoc */
  CATBoolean        _IsIdentity, _IsSimilitude;

	/** @nodoc */
  CATLONG32                  _NewTransfo, 
                        _Status,       // =0 by default, =1 si RunDuplicate 
                                       // =2 si runDulpicate + Add 
                        _NoCheckInAdd; // =1 if no search for transfo1D/2D in 
                                       // Add methode
  //---------------------------------------------------------------------------
  //- Internal only
  //---------------------------------------------------------------------------
  /** @nodoc */
  static CATString _OperatorId;
  /** @nodoc */
	const CATString * GetOperatorId();
  /** @nodoc */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc */
  void WriteInput(CATCGMStream  & ioStream);
  /** @nodoc */
  void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc */
	CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc */
  void Dump( CATCGMOutput& os ) ;
  /** @nodoc */
  int RunOperator();

/** @nodoc */
  virtual void CreateTransformation();

private:
  void AddInternal(CATICGMObject * iObjectToTransform    ,
                   CATICGMObject * iTransformedObject = 0);
  void Clear();
  void Reset(CATLONG32 & oNoFindLinks);
  void CreateMathTransformation(const CATMathTransformation & iMathTransfo);

friend class CATTransfoUnknown;
friend class CATTransfoSimplify;

};
#endif
