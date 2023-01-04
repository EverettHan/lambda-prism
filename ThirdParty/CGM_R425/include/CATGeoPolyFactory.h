#ifndef CATGeoPolyFactory_H
#define CATGeoPolyFactory_H

//=============================================================================
// COPYRIGHT Dassault Systemes 2014
//=============================================================================
//
// CATGeoPolyFactory.h
//
//  3D Factory, tactical modularisation for polyhedral objects management in the CGMContainer
//
//
//=============================================================================
// Usage Notes:
//
//    Please, note that the default behavior of the CATGeoPolyFactory consists in instanciating all the polyhedral objects in the "Implicit" mode, 
//    excepted for the CATBody or CATGeoPolyBody instances if the root GeoFactory is itself Explicit and only in this case.
//    -> Explanation here :
//    1. Create CATBody/CATGeoPolyBody objects in the "Explicit" mode means that 
//       the caller is in charge of its Life Cycle and has to call explicitely the "Remove()" method in order to delete it.
//    2. Instanciate all the other types in the "Implicit" mode means that the caller has to choose between :
//          attaching the object to another one in order to create direct or indirect dependency with at least one body,
//       or changing the mode from Implicit to Explicit thanks to the method "SetMode(CATCGMExplicit)"
//       -> in the first case, Remove bodies (and only bodies) with all dependancies leads to delete all the implicit objects in the Factory
//       -> in the second case, the caller has to use explicitely the Remove() method on all explicit objects
//
//=============================================================================
// Creation:      DPS, December. 2014
// Modifications: DPS, May. 2015
//                Change of signatures for the geometric objects creation methods, in order to instanciate :
//                GeoPolyPoint in 3D only or Lying on a curve or a surface, 
//                GeoPolyCurve in 3D only or lying on a surface ...
//                ... waiting for the final dedicated interfaces
//                DPS, September. 2015, Add the GeoPolyCouplingCurve instanciation
//                DPS, January 2019, Add the CATGeoPolyCurveOnPlane instanciation
//                DPS, January 2021, Add continuous CATCurve as optional reference in CreateGeoPolyCurve
//                DPS, April   2021, Add CATGeoPolyBody with matrix position
//=============================================================================

#include "CATIACGMLevel.h"
#include "YP00IMPL.h" 
#include "CATBaseUnknown.h"
#include "CATICGMContainer.h"

#include "CATListValCATCrvParam.h"
#include "CATListValCATSurParam.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"

#ifndef NULL
#define NULL 0
#endif

class CATGeoFactory;
class CATGeoFactoryProtected;
class CATCGMContainer;

class CATBody;  
class CATVolume;  
class CATFace;  
class CATEdge;  
class CATVertex;  
class CATLump;  
class CATShell;  
class CATLoop;  
class CATWire;  
class CATVertexInFace;  
class CATVertexInVolume;  

class CATSurface;
class CATCurve;
class CATSurParam;
class CATCrvParam;

class CATGeoPolyBody;
class CATGeoPolyPoint;
class CATGeoPolyPointOnCurve;
class CATGeoPolyPointOnSurface;
class CATGeoPolyCurve;
class CATGeoPolyCurveOnCurve;
class CATGeoPolyCurveOnSurface;
class CATGeoPolyCurveOnPlane;
class CATGeoPolyCouplingCurve;
class CATGeoPolySurface;

class CATPolyBody;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;

class CATMathVector;
class CATMathTransformation;


class ExportedByYP00IMPL CATGeoPolyFactory : public CATBaseUnknown
{
	//CATDeclareInterface;

public:

  // No constructor, 
  // use the static method GetPolyFactory() to retrieve or create the instance of CATGeoPolyFactory attached to a specific CATGeoFactory

  //---------------------------------------------------------------------------
  // GetPolyFactory
  //---------------------------------------------------------------------------

  // No creation here
  // Just a way to retrieve a CATGeoPolyFactory attached to the Factory of the CGMContainer
  // If not, retrieve the CATGeoPolyFactory attached to the implicit Factory of the CGMContainer 
  // (only if different from the first one)
  // The optional argument oImplicitFactory allows the caller to know the nature 
  // of the referencial GeoFactory from which the returned GeoPolyFactory has been retrieved
  static CATGeoPolyFactory * RetrieveGeoPolyFactoryFromContainer(CATICGMContainer * iCGMContainer, CATBoolean * oImplicitFactory=NULL);

  
  // ************************************************************************************************
  // *** Retrieve or Create an instance of CATGeoPolyFactory attached to a specific CATGeoFactory ***
  // ************************************************************************************************
  static CATGeoPolyFactory * GetPolyFactory(CATGeoFactory * iFactory, CATBoolean iCreationMode=TRUE);

  // ---------------------------------------------------
  // No destructor, use Release() instead


  // ========================================================================
  //   Object management SERVICE
  // ========================================================================

  virtual CATBoolean IsNativeOfGeoPolyFactory(const CATICGMObject * ipICGMObject)=0;


public:

  // ========================================================================
  //   TOPOLOGY
  // ========================================================================

  //-------------------------------------------------------------------------
  // - Polyhedral Body creation
  //-------------------------------------------------------------------------
  /**
  * Creates an empty polyhedral body.
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @return
  *   The pointer to the created body.
  * This object will be created in an implicit mode, excepted if the Root GeoFactory is itself Explicit.
  * Explicit instanciation means that the caller has to explicitely call the Remove() method on the returned object in order to delete it
  */
  virtual CATBody * CreateBody() = 0 ;


  //----------------------------------------------------------------------
  // Cells creation in the polyhedral factory
  //----------------------------------------------------------------------

  /**
  * Creates a volume.
  * @return
  * The pointer to the created volume (cell of dimension 3)
  */
  virtual CATVolume * CreateVolume() = 0 ;

  /**
  * Creates a face.
  * @return
  * The pointer to the created face (cell of dimension 2)
  */
  virtual CATFace * CreateFace() = 0 ;

  /**
  * Creates an edge.
  * @return
  * The pointer to the created edge (cell of dimension 1)
  */
  virtual CATEdge * CreateEdge() = 0 ;

  /**
  * Creates a vertex.
  * @return
  * The pointer to the created vertex (cell of dimension 0)
  */
  virtual CATVertex * CreateVertex() = 0 ;


  //----------------------------------------------------------------------
  // Domains creation in the polyhedral factory
  //----------------------------------------------------------------------

  /**
  * Creates a topological domain (called lump) which contained cells are CATVolumes.
  * <br>It corresponds to <tt>iContainedCellsDimension = 3,
  * iContainingCellDimension = 3</tt>.
  * @return
  * The pointer to the created lump.
  */
  virtual CATLump * CreateLump() = 0 ;


  /**
  * Creates a topological domain (called shell) which contained connected cells are CATFaces.
  * <br>It corresponds to <tt>iContainedCellsDimension = 2,
  * iContainingCellDimension = 3</tt>.
  * @return
  * The pointer to the created shell.
  */
  virtual CATShell * CreateShell() = 0 ;

  /**
  * Creates a topological domain (called loop) representing a set of connected egdes bounding
  * a face .
  * <br>It corresponds to <tt>iContainedCellsDimension = 1,
  * iContainingCellDimension = 2</tt>. The loop may be closed or not.
  * @param iLocation
  * The location of the contained cells relative to the containing cell.
  * @return
  * The pointer to the created loop.
  */
  virtual CATLoop * CreateLoop() = 0 ;

  /**
  * Creates a topological domain representing a set of connected edges (called wire) of a
  * body or a volume.
  * <br>It corresponds to <tt>iContainedCellsDimension = 1,
  * iContainingCellDimension = 3</tt>.
  * @return
  * The pointer to the created wire.
  */
  virtual CATWire * CreateWire() = 0 ;

  /**
  * Creates a topological domain representing a vertex immersed inside a face.
  * <br>It corresponds to <tt>iContainedCellsDimension = 0,
  * iContainingCellDimension = 2</tt>.
  * @return
  * The pointer to the created VertexInFace domain.
  */
  virtual CATVertexInFace * CreateVertexInFace() = 0 ;

  /**
  * Creates a topological domain representing a vertex immersed inside a volume.
  * <br>It corresponds to <tt>iContainedCellsDimension = 0,
  * iContainingCellDimension = 3</tt>.
  * @return
  * The pointer to the created VertexInVolume domain.
  */
  virtual CATVertexInVolume * CreateVertexInVolume() = 0 ;

    
  
  // ========================================================================
  //   GEOMETRY
  // ========================================================================


  /**
  * Creates a geometry of polyhedral point in 3D
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyPoint : the polyhedral object to wrap in the CATGeometry
  * @return
  *   The pointer to the created CATGeoPolyPoint.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyPoint * CreateGeoPolyPoint(const CATIPolyPoint &iPolyPoint) = 0;

  /**
  * Creates a geometry of polyhedral point lying on a PolyCurve
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyPoint : the polyhedral object to wrap in the CATGeometry (CATPolyCurveVertex, ...)
  *                     this object is supposed to contain the full information relative to the PolyCurve support 
  * @param iGeoPolyCurveSupport : the CATGeometry curve support
  * @param iParamOnCurve : equivalent parameter of the point on the curve support
  * @return
  *   The pointer to the created CATGeoPolyPoint.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyPointOnCurve * CreateGeoPolyPointOnCurve(const CATIPolyPoint &iPolyPoint, const CATGeoPolyCurve & iGeoPolyCurveSupport, const CATCrvParam & iParamOnCurve) = 0;

  /**
  * Creates a geometry of polyhedral point lying on a PolySurface
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyPoint : the polyhedral object to wrap in the CATGeometry (CATPolySurfaceVertex, CATPolyMeshPoint, ...)
  *                     this object is supposed to contain the full information relative to the PolySurface support 
  * @param iGeoPolySurfaceSupport : the CATGeometry surface support
  * @return
  *   The pointer to the created CATGeoPolyPoint.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyPointOnSurface * CreateGeoPolyPointOnSurface(const CATIPolyPoint &iPolyPoint, const CATGeoPolySurface & iGeoPolySurfaceSupport) = 0;


  /**
  * Creates a geometry of polyhedral curve in 3D with associated tangents to the 2 extremities
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyCurve3D : the 3D PolyLine object to wrap in the CATGeometry
  * @param iStartTangent : vectorial Tangent associated to the Start extremity, consistent with the orientation of the curve support
  * @param iEndTangent : vectorial Tangent associated to the End extremity, consistent with the orientation of the curve support
  * @param iContinuousCurve : the optional original exact curve support
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCurve * CreateGeoPolyCurve3D(const CATIPolyCurve &i3DPolyCurve, const CATMathVector &iStartTangent, const CATMathVector &iEndTangent, CATCurve * iContinuousCurve=NULL) = 0;

  /**
  * Creates a geometry of polyhedral curve in 3D
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyCurve : the polyhedral object to wrap in the CATGeometry
  * @param iContinuousCurve : the optional original exact curve support
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCurve * CreateGeoPolyCurve(const CATIPolyCurve &iPolyCurve, CATCurve * iContinuousCurve=NULL) = 0;

  /**
  * Creates a geometry of polyhedral curve fully coincident with a part of another PolyCurve
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyCurve : the polyhedral object to wrap in the CATGeometry
  * @param iGeoPolyCurveSupport : the CATGeometry curve support
  * @param iSameOrientation : TRUE if the CATIPolyCurve is oriented like the curve support parametrization
  * @param iStartParamOnSupport : equivalent parameter of the start extremity on the curve support
  * @param iEndParamOnSupport : equivalent parameter of the end extremity on the curve support
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCurveOnCurve * CreateGeoPolyCurveOnCurve(const CATIPolyCurve &iPolyCurve, const CATGeoPolyCurve &iGeoPolyCurveSupport, CATBoolean iSameOrientation,
    const CATCrvParam & iStartParamOnSupport, const CATCrvParam & iEndParamOnSupport) = 0;

  /**
  * Creates a geometry of polyhedral curve lying on (bounding or crossing) a PolySurface
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyCurve : the polyhedral object to wrap in the CATGeometry (CATPolySurfaceVertexLine, CATPolyMeshCurve, ...)
  *                     this object is supposed to contain the full information relative to the PolySurface support 
  * @param iGeoPolySurfaceSupport : the CATGeometry surface support (wrapping the CATIPolySurface support of iPolyCurve)
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCurveOnSurface * CreateGeoPolyCurveOnSurface(const CATIPolyCurve &iPolyCurve, const CATGeoPolySurface &iGeoPolySurfaceSupport) = 0;

  /**
  * Creates a geometry of polyhedral curve lying on (bounding or crossing) a PolySurface 
  * with 2 specific normal vectors associated to the curve extremities, useful information for cone apex for example 
  * (meshes have only one normal vector per point, not enough in degenerated surfacic configurations)
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolyCurve : the polyhedral object to wrap in the CATGeometry (CATPolySurfaceVertexLine, CATPolyMeshCurve, ...)
  *                     this object is supposed to contain the full information relative to the PolySurface support 
  * @param iGeoPolySurfaceSupport : the CATGeometry surface support (wrapping the CATIPolySurface support of iPolyCurve)
  * @param iStartNormal : vectorial Normal associated to the Start extremity, consistent with the orientation of the surface support
  * @param iEndNormal   : vectorial Normal associated to the End extremity, consistent with the orientation of the surface support
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCurveOnSurface * CreateGeoPolyCurveOnSurfWithNormals(const CATIPolyCurve &iPolyCurve, const CATGeoPolySurface &iGeoPolySurfaceSupport, const CATMathVector &iStartNormal, const CATMathVector &iEndNormal) = 0;

  /**
  * Creates a geometry managing a synchronized mapping between a 3D polycurve and a planar 2D polycurve
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iRefCurve : the 3D CATGeoPolyCurve as reference
  *                    this object is not supposed to have any link with the planar surface
  * @param iPlanarSurface : the CATSurface whose the geometric representation is planar (Mandatory)
  * @param iPlanarSurParams : ordered list of (at least 2) surface parameters associated to the curve discretization points,
  *                           this list defines the bijective mapping between the 3DCurve and the planar polycurve
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCurveOnPlane * CreateGeoPolyCurveOnPlane(const CATGeoPolyCurve &iRefCurve, const CATSurface &iPlanarSurface, CATLISTV(CATSurParam) &iPlanarSurParams) = 0;

  /**
  * Creates a geometry managing a mapping between 2 CATGeoPolyCurves, 
  * the first one considered as the reference curve for the coupling (asymmetric object)
  * in order to support tolerant configurations of a geometry lying on another one (specific curve).
  * Please note that the RefCurve is fully lying on the SpecCurve which can be longer
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iRefCurve : the 1D-CATGeometry as reference
  * @param iTwinSpecCurve : the specific 1D-CATGeometry to link with the reference
  * @param iSameOrientation : TRUE if the 2 ascending parameterizations have the same orientation, else FALSE
  * @param iRefCrvParams : list of (at least 2) ascending ordered CrvParams defining the mapping from the reference, 
  *     >> Mandatory <<    the Start and End parameters of the RefCurve,
  *     << Optional  >>    the intermediate points defining the discretization of the RefCurve
  * @param iEquivalentCrvParamsOnTwin : list (same size) of equivalent parameters on the twin specific curve
  * @return
  *   The pointer to the created CATGeoPolyCurve.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolyCouplingCurve * CreateGeoPolyCouplingCurve(const CATGeoPolyCurve &iRefCurve, const CATGeoPolyCurve &iTwinSpecCurve, CATBoolean iSameOrientation, 
    CATLISTV(CATCrvParam) & iRefCrvParams, CATLISTV(CATCrvParam) & iEquivalentCrvParamsOnTwin) = 0;


  /**
  * Creates a geometry of polyhedral surface
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iPolySurface : the polyhedral object to wrap in the CATGeometry
  * @param iExactSurface : the optional original exact surface support
  * @param iRelativeOrientation : the optional knowledge of the relative orientation (+1 or -1) between the CATIPolySurface and the CATSurface
  * @return
  *   The pointer to the created CATGeoPolySurface.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoPolySurface * CreateGeoPolySurface(const CATIPolySurface &iPolySurface, CATSurface * iExactSurface=NULL, short iRelativeOrientation=0) = 0;

    
  // ========================================================================
  //   CATGeoPolyBody
  // ========================================================================

  /**
  * Creates a geometry wrapping a native instance of CATPolyBody
  *<br> This object is mainly used by the GMPolyObjects framework.
  * @param iRefNativePolyBody : the referential CATPolyBody object to wrap in the CATGeometry
  * If the PolyBody is not declared as native, no CATGeoPolyBody will be created
  * @param iInstanceMatrixPosition : optional transformation to complete the instance definition from the referencial CATPolyBody
  * iInstanceMatrixPosition will not be referenced by the new object, but cloned into a private data member.
  * @return
  *   The pointer to the created CATGeoPolyBody.
  */
  virtual CATGeoPolyBody * CreateGeoPolyBody(CATPolyBody & iRefNativePolyBody, const CATMathTransformation * iInstanceMatrixPosition = NULL) = 0;


  //---------------------------------------------------------------------------
  // remove object from the container
  //---------------------------------------------------------------------------
  virtual void Remove(CATICGMObject*                                  iObjectToRemove, 
                      const CATICGMContainer::CATRemovingDependancies iHow = CATICGMContainer::RemoveDependancies) = 0;


  //---------------------------------------------------------------------------
  // Access to the root CATGeoFactory
  //---------------------------------------------------------------------------
  virtual CATGeoFactory * GetRootFactory() const = 0;

  //---------------------------------------------------------------------------
  // Retrieve the CATTolerance attached to the Root GeoFactory
  //---------------------------------------------------------------------------
  virtual const CATTolerance & GetTolerance() const = 0;

};


// *******************************************************
// *** DO NOT USE, UNDER INVESTIGATION, FOR DEBUG ONLY ***
// *******************************************************
// Global Create method dedicated to the CATGeoFactoryCGM class.
// Please, consider this as a private service reserved for friend classes.
ExportedByYP00IMPL CATGeoPolyFactory * CATCreateGeoPolyFactory(CATGeoFactoryProtected & iGeoFactoryProtected, 
                                                               CATCGMContainer        & iCGMContainer);

// CATDeclareHandler(CATGeoPolyFactory,CATBaseUnknown);

#endif

