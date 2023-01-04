#ifndef CATGeoMeshFactory_H
#define CATGeoMeshFactory_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//
//  3D Factory, tactical modularisation for Meshes domains
//
/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 
#include "CATIACGMLevel.h"
#include "ExportedByCATGMGeometricInterfaces.h"
 
#include "CATMathDef.h"  // deplacement en tete pour logique + compatibilité CATCGMSpecialHandler. NLD210220
#include "CATBaseUnknown.h"
#include "CATICGMContainer.h"
#include "CATGeometryType.h"
#include "CATListOfCATMathSetOfPointsND.h"

 
class CATGeometry;
class CATICGMObject;
class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathDirection;
class CATMathPlane;
class CATMathLine;
class CATMathLine2D;
class CATMathAxis;
class CATMathAxis2D;
class CATMathBox2D;
class CATMathFunctionX;
class CATMathNonLinearTransformation;
class CATMathTransformation;
class CATCrvParam;
class CATCrvLimits;
class CATSurParam;
class CATSurLimits;
class CATMathSetOfPoints;
class CATMathGridOfPoints;
 
class CATCloudOfPoints;

class CATCldGenEntity;
class CATCldBody;
class CATCldCloud;
class CATCldScan;
class CATCldGrid;
class CATCldPolygon;
class CATCldSubPolygon;
class CATCldVectors;
class CATCldSetOfScans;
class CATCldSetOfGrids;
class CATCldScanOnPolygon;
class CATCldSetOfPoints;
class CATCldSetOfPointsF;
class CATCldSetOfPointsD;

class CATClay;
class CATTessClay;
class CATCloud;
class CATTessCloud;
class CATScan;
class CATTessScan;
 
class CATSobMesh;
class CATSubdivMesh;
 
class CATSubdivCellSurface;
class CATSubdivGridSurface;
class CATSobFace;
class CATSubdivMeshGeo;

class CATGeoPolyPoint;
class CATIPolyPoint;
class CATGeoPolyCurve;
class CATIPolyCurve;
class CATGeoPolySurface;
class CATIPolySurface;
class CATGeoPolyBody;
class CATPolyBody;

class CATCldSubPolygon;

 
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoMeshFactory ;
#else
extern "C" const IID IID_CATGeoMeshFactory ;
#endif

//CAA_Exposed CATIGemFactory
/**
* Interface representing the factory of all geometric elements.
*<br><b>Role</b>: The CATGeoMeshFactory creates the geometric elements. It manages the AddRef mechanism.
* To suppress a geometric element, you must use <tt>CATICGMContainer::Remove</tt> method, 
* that also takes in charge the AddRef mechanism.
*<br> The creation of a container implies the creation of two factories,
* an explicit one and an implicit one.
* All the methods described here
* work on both, except the <tt>Next</tt> method, that only works on
* the explicit factory. 
*<br>At the container creation, 7 implicit objects (called Datums)
* are created and represent the canonical geometric objects: the space
* origin <tt>CATGeoMeshFactory::O</tt>, the infinite lines in the three directions,
* <tt>CATGeoMeshFactory::OI</tt>, <tt>CATGeoMeshFactory::OJ</tt>, <tt>CATGeoMeshFactory::OK</tt>, and the three
* infinite planes passing through these lines 
* <tt>CATGeoMeshFactory::OIJ</tt>, <tt>CATGeoMeshFactory::OJK</tt>, <tt>CATGeoMeshFactory::OKI</tt>.
*<br>The description and the use of the entities created by the factory 
* are described in each entity class.
* <br><b>Lifecyle rules</b>: a CATGeoMeshFactory is created by using the  <tt>CATCreateCGMContainer</tt> 
* global function or
* loaded from a stream with the  <tt>CATLoadCGMContainer</tt> global function. 
* It can be saved on a given stream (<tt>CATLoadCGMContainer</tt>).When you do not need 
* it anymore, you must close it
* <tt>CATCloseCGMContainer</tt>. All these global functions can be found in the <tt>CATCGMContainerMngt.h</tt>
* file.
*/
class ExportedByCATGMGeometricInterfaces CATGeoMeshFactory : public CATBaseUnknown
{
   CATDeclareInterface;

public:
 
  

   //-------------------------------------------------------------------------
   // - CloudOfPoints creation
   //-------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a permanent list of sets of 3D mathematical points.
   *<br>The list of CATMathSetOfPointsNDs will be referred to and appropriated by the new
   * CATCloudOfPoints. It will be deleted as soon as the CATCloudOfPoints
   * is deleted.
   * @param iListOfPoints
   * The list of set of points.
   * @param iOperatingDistance
   * The distance defining how two points need to be close in order  
   * to be topologically related.
   * @return
   * The pointer to the created cloud of points.
   */
   virtual CATCloudOfPoints * CreateCloudOfPoints(CATLISTP(CATMathSetOfPointsND) & iListOfPoints,
                                                  const double iOperatingDistance) = 0 ; 



 

   //-----------------------------------------------------------------------------
   //- CloudEditor objects creation
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   */
   virtual CATCldBody* CreateCldBody (const CATCldSetOfPoints* iSetOfPoints = NULL) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldBody* CreateCldBody (const CATCldGenEntity* iEntity) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldCloud* CreateCldCloud (const CATCldGenEntity* iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldScan* CreateCldScan (const CATCldGenEntity* iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldGrid* CreateCldGrid (const CATCldGenEntity* iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldPolygon* CreateCldPolygon (const CATCldGenEntity* iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldVectors* CreateCldVectors (const CATCldGenEntity* iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldSetOfScans* CreateCldSetOfScans (const CATCldGenEntity* iEntity) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldSetOfGrids* CreateCldSetOfGrids (const CATCldGenEntity* iEntity) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldScanOnPolygon* CreateCldScanOnPolygon (const CATCldPolygon* iPolygon) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldSetOfPointsF* CreateCldSetOfPointsF () = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldSetOfPointsD* CreateCldSetOfPointsD () = 0 ; 
   /**
   * @nodoc
   */
  virtual CATCldSubPolygon* CreateCldSubPolygon(const CATCldPolygon* iPolygon) = 0;
  virtual CATCldSubPolygon* CreateCldSubPolygonBasic (const CATCldPolygon* iPolygon) = 0;
 

   //-------------------------------------------------------------------------
   // Cloud creation
   // iNormals may be a NULL pointer.
   // If iPointsActivity is NULL, then all points are considered to be active.
   // CharacteristicDistance is the max of the min distance for all points, so
   // it should be strictly greater than 0. Default value will force the computation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATCloud  * CreateCloud (CATLONG32 iNbPoints, const float * iPoints,
                                    const float * iNormals, const CATULONG32  * iPointsActivity,
                                    double CharacteristicDistance = 0) = 0;

   //-------------------------------------------------------------------------
   // Scan creation
   // iNormals may be a NULL pointer.
   // If iPointsActivity is NULL, then all points are considered to be active.
   // CharacteristicDistance is the max of the min distance for all points, so
   // it should be strictly greater than 0. Default value will force the computation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATScan  * CreateScan (CATLONG32 iNbPoints, const float * iPoints,
                                  const float * iNormals, const CATULONG32  * iPointsActivity,
                                  CATLONG32 NumberOfScan, CATLONG32 * NumberOfPointsPerScan,
                                  double CharacteristicDistance = 0) = 0;

   //-------------------------------------------------------------------------
   // TessCloud creation
   // If iPrimitivesActivity is ULL, then all primitives are considered to be active.
   // iPrimitives is an array of indexes on the three vertices of the triangle.
   // iNeighbours is an array of indexes on the three neighbours triangles. If there is 
   // neighbour on a side of the triangle, index=-2.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATTessCloud  * CreateTessCloud (      CATCloud    * iCloud, 
                                                  CATLONG32     iNbPrimitives, 
                                            const CATLONG32   * iPrimitives,
                                            const CATLONG32   * iNeighbours,
                                            const CATULONG32  * iPrimitivesActivity) = 0;

   //-------------------------------------------------------------------------
   // TessScan creation
   // If iPrimitivesActivity is ULL, then all primitives are considered to be active.
   // iPrimitives is an array of indexes on the three vertices of the triangle.
   // iNeighbours is an array of indexes on the three neighbours triangles. If there is 
   // neighbour on a side of the triangle, index=-2.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATTessScan  * CreateTessScan (      CATScan     * iScan,
                                                CATLONG32     iNbPrimitives,
                                          const CATLONG32   * iPrimitives,
                                          const CATLONG32   * iNeighbours,
                                          const CATULONG32  * iPrimitivesActivity) = 0;


 
   //-------------------------------------------------------------------------
   //Subdivision Mesh creation
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATSubdivMesh* CreateSubdivMesh() = 0;

   /** @nodoc */
   virtual CATSubdivMesh* CreateSubdivMesh(CATSobMesh* iMesh) = 0;
 
  virtual CATSubdivMesh* CreateSubdivMesh(CATSubdivMeshGeo* iSubdivMeshGeo) = 0;

  //-----------------------------------------------------------------------------
  // CATSubdivCellSurface creation from a CATSubdivMeshGeo object, a CATSobFace and a Daughter-Face Index
  //-----------------------------------------------------------------------------
  virtual CATSubdivCellSurface* CreateSubdivCellSurface()  = 0;
  virtual CATSubdivCellSurface* CreateSubdivCellSurface(CATSubdivMesh* iSubdivMesh,
                                                        CATSobFace * iFace,
                                                        int iDaughterIndex)  = 0;
  virtual CATSubdivCellSurface* CreateSubdivCellSurfaceBasic(CATSubdivMesh* iSubdivMesh,
                                                             CATSobFace * iFace,
                                                             int iDaughterIndex) = 0;

  //--------------------------------------------------------------------------------------------------
  // CATSubdivCellSurface creation from a CATSubdivMesh object, and Grid of NU*NV CATSobFace(s) 
  // Such as iTabFaces[iu + iv*NU] 0<=iu<NU 0<=iv<NV 
  //--------------------------------------------------------------------------------------------------
  virtual CATSubdivGridSurface * CreateSubdivGridSurface     (CATSubdivMesh* iSubdivMesh, const int NU, const int NV, CATSobFace * const * iTabFaces) = 0;
  virtual CATSubdivGridSurface * CreateSubdivGridSurfaceBasic(CATSubdivMesh* iSubdivMesh, const int NU, const int NV, CATSobFace * const * iTabFaces) = 0;

  //Create a Surface with the imposed Steps in the Uniforms KnotVectors
  virtual CATSubdivGridSurface * CreateSubdivGridSurface     (CATSubdivMesh* iSubdivMesh, const int NU, const int NV, CATSobFace * const * iTabFaces,
                                                              double StepU, double StepV)  = 0;
  virtual CATSubdivGridSurface * CreateSubdivGridSurfaceBasic(CATSubdivMesh* iSubdivMesh, const int NU, const int NV, CATSobFace * const * iTabFaces,
                                                              double StepU, double StepV)  = 0;
  
  //---------------------------------------------------------------------------
  // Polyhedral objects
  //---------------------------------------------------------------------------
    
  /*
  Deprecated instantiation of CATGeoPolyPoint, CATGeoPolyCurve, CATGeoPolySurface, CATGeoPolyBody
  See CATGeoPolyFactory to switch to new implementations, wrapping native CATIPolyObjects
  
  virtual CATGeoPolyPoint   *CreateGeoPolyPoint  (CATIPolyPoint *iPolyPoint) = 0;
  virtual CATGeoPolyCurve   *CreateGeoPolyCurve  (CATIPolyCurve *iPolyCurve) = 0;
  virtual CATGeoPolySurface *CreateGeoPolySurface(CATIPolySurface *iPolySurface) = 0;

  virtual CATGeoPolyBody *CreateGeoPolyBody(CATPolyBody *iPolyBody) = 0;
  */
  
  //---------------------------------------------------------------------------
  // Added 
  //---------------------------------------------------------------------------


    
  virtual CATCloudOfPoints* CreateCloudOfPointsBasic(CATLISTP(CATMathSetOfPointsND)& iListOfPoints,
                                                     const CATPositiveLength         iOperatingDistance) = 0;

  //-------------------------------------------------------------------------
  // Scan creation
  //-------------------------------------------------------------------------
  virtual CATScan  * CreateScanBasic (      CATLONG32 iNbPoints, const float * iPoints,
                                      const float * iNormals, const CATULONG32  * iPointsActivity,
                                            CATLONG32 NumberOfScan, CATLONG32 * NumberOfPointsPerScan,
                                            CATPositiveLength CharacteristicDistance = 0)= 0;
  
  //-------------------------------------------------------------------------
  // TessCloud creation
  //-------------------------------------------------------------------------
  virtual CATTessCloud  * CreateTessCloudBasic (      CATCloud   * iCloud, 
                                                      CATLONG32    iNbPrimitives,
                                                const CATLONG32  * iPrimitives,
                                                const CATLONG32  * iNeighbours,
                                                const CATULONG32 * iPrimitivesActivity)= 0;

   //-------------------------------------------------------------------------
  // TessScan creation
  //-------------------------------------------------------------------------
  virtual CATTessScan  * CreateTessScanBasic (      CATScan     * iScan,
                                                    CATLONG32     iNbPrimitives,
                                              const CATLONG32   * iPrimitives,
                                              const CATLONG32   * iNeighbours,
                                              const CATULONG32  * iPrimitivesActivity)= 0;

  
  virtual CATCloud* CreateCloudBasic(CATLONG32         iNbPoints,
                                     const float*      iPoints,
                                     const float*      iNormals,
                                     const CATULONG32* iPointsActivity,
                                     CATPositiveLength CharacteristicDistance = 0)= 0;


  virtual  CATCldCloud*        CreateCldCloudBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldScan*          CreateCldScanBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldGrid*          CreateCldGridBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldPolygon*       CreateCldPolygonBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldVectors*       CreateCldVectorsBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldSetOfScans*    CreateCldSetOfScansBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldSetOfGrids*    CreateCldSetOfGridsBasic(const CATCldGenEntity* iEntity)= 0;

  virtual CATCldScanOnPolygon* CreateCldScanOnPolygonBasic(const CATCldPolygon* iPolygon)= 0;

  virtual CATCldSetOfPointsF*  CreateCldSetOfPointsFBasic()= 0;

  virtual CATCldSetOfPointsD*  CreateCldSetOfPointsDBasic()= 0;


  virtual CATSubdivMesh*       CreateSubdivMeshBasic(CATSobMesh* iMesh)= 0;

  virtual CATSubdivMesh*       CreateSubdivMeshBasic(CATSubdivMeshGeo* iSubdivMeshGeo) = 0;

  virtual CATSubdivMeshGeo*    CreateSubdivMeshGeoBasic(CATSobMesh* iMesh, const CATBoolean iBuildInsideFactory = TRUE)= 0;

};

CATDeclareHandler(CATGeoMeshFactory,CATBaseUnknown);

#endif

