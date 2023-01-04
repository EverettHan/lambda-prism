#ifndef CATGEOMETRYPACK_H
#define CATGEOMETRYPACK_H

// 
//--------------------------------------------------
//- Copyright DASSAULT SYSTEMES 
//
//
//- 05/xx/2001 Alexandre Heimburger
//  27/01/2004 EAB Versionning de l'opérateur
//- xx/06/2014 Q48 Add scale manager for X-scale
//               - see tag "Q48 (06/2014): X-scale"
//- xx/08/2014 Q48 Xscale: memory management + improved flags
//  05/03/2016 JSX Compare add TabTol to allow different tolerances
//  21/04/2017 PKC compilation warning
//--------------------------------------------------
//

//--------------------------------------------------
//--------------------------------------------------
#include "Y3DYNOPE.h"
#include "CATCGMOperator.h"
#include "CATCGMVirtual.h"

class CATCGMStream;
class CATCGMOutput;
class CATPoint;
class CATCurve;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATICGMObject;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATGeoODTScaleManager;

class ExportedByY3DYNOPE CATGeometryPack : public CATCGMVirtual
{
public:
  //
   CATGeometryPack(CATSoftwareConfiguration * iConfig, CATGeoFactory *iFactory = NULL);
  ~CATGeometryPack();
  
  // surcharge new/delete
  CATCGMNewClassArrayDeclare;
  
  // *****************************************************
  // These five methods add different types of geometry
  // inside the pack.
  // *****************************************************
  void AddPoint  (CATPoint   *Pt);
  void AddCurve  (CATCurve   *Crv, const CATCrvLimits &limits);
  void AddSurface(CATSurface *Sur, const CATSurLimits &limits);
  void AddCurve  (CATCurve   *Crv);
  void AddSurface(CATSurface *Sur);
  
  // *****************************************************
  // This method streams the pack inside a CATCGMStream
  // A CATICGMObject array is created with _PointTab,
  // _SurfaceTab, _CurveTab.
  // Order of stream: numbers of each geometry,
  // the geometries, the crvlimits and
  // the surlimits.
  // *****************************************************
  void Stream(CATCGMStream &);
  
  
  // *****************************************************
  // Check if the CATGeometryPack has already been 
  // unstreamed
  // *****************************************************
  CATBoolean   IsUnStreamed();
  
  // *****************************************************
  // Unstreams the pack in the same order than 
  // the method stream.
  // <=>first inside, first outside
  // *****************************************************
  void         UnStream( CATCGMStream & ioStream, const CATBoolean iApplyXScale = FALSE);

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  // XScaleLevel replaces XscaleLevel (which is also defined as an internal class in CATGeoOpDebug: XRef search will be easier)
  enum XScaleLevel { Attempt_None = 0, Attempt_Unknown, Attempt_Expect };

  void         UnStream( CATCGMStream & ioStream, const XScaleLevel iApplyXScale);
  
  // *****************************************************
  // Returns the number of geometries
  // inside the pack.
  // *****************************************************
  CATLONG32    GetNumberOfGeometry();
  CATLONG32    GetNumberOfPoints  ();
  CATLONG32    GetNumberOfCurves  ();
  CATLONG32    GetNumberOfSurfaces();
  
  // *****************************************************
  // Gets current geometry and its limits.
  // *****************************************************
  CATCurve   * GetCurve           (CATCrvLimits &);
  CATCurve   * GetCurve           ();
  CATSurface * GetSurface         (CATSurLimits &);
  CATSurface * GetSurface         ();
  CATPoint   * GetPoint           ();
  
  // ******************************************************************************
  // Resets the iterators to read the Points/Curves/Surfaces again.
  // ******************************************************************************
  void         Beginning ();

  // *****************************************************
  // Gets the factory.
  // *****************************************************
  CATGeoFactory * GetFactory();
  
  // *****************************************************
  // Tests the validity of each geometry 
  // (Curves and Surfaces).
  // *****************************************************
  CATCGMOperator::CATCheckDiagnostic CheckValidity(CATCGMOutput &ios, CATBoolean AdvMode = TRUE);
  
  // *****************************************************
  // Compares 2 CATGeometryPack.
  // *****************************************************
  CATCGMOperator::CATCheckDiagnostic Compare(CATGeometryPack * iPack               ,
                                             CATCGMOutput    * os                  = NULL,
                                             double            ErrTol              = 0.  ,
                                             double            WarningTol          = 0.  ,
                                             CATListOfDouble * TabTol              = NULL,
                                             CATBoolean        CurveTypeComparison = FALSE);
  
  // *****************************************************
  // Moves all the geometries into the factory ifacto and
  // returns a new CATGeometryPack.
  // *****************************************************
  CATGeometryPack      * TransfertIntoOtherFactory(CATGeoFactory *iFactoru);
  
  CATGeoODTScaleManager* GetScaleManager(const CATBoolean iPermanent = TRUE);

private:

  //
  HRESULT RemoveGeometry();

  // *****************************************************
  // Scales the geometry currently in the pack
  // and replaces the factory with the scaled one
  // *****************************************************
  void ApplyScaleToGeometry(const XScaleLevel); // Q48 (06/2014): X-scale


  //******************************************************
  // CheckCrv : 
  // initializes _CurveTab/_SurfaceTab/_PointTab if 
  // _InitCrv/_InitSurface/_InitPoint is FALSE;
  // increases the size of array if the number of 
  // geometries is equal to the max size of the array.
  // *****************************************************
  void CheckCrv();
  void CheckSur();
  void CheckPoint();
  
  //******************************************************
  // DispatchGeometry:
  // puts the geometries inside arrays after the unstream method.
  // *****************************************************
  void DispatchGeometry(const CATICGMObject **, const XScaleLevel);
  
  // *****************************************************
  // These methods are able to compare 2 geometries with the same type.
  // *****************************************************
  CATCGMOperator::CATCheckDiagnostic ComparePoints        (CATPoint    *,                 CATGeometryPack *,double ErrTol, double WarningTol,                                   CATCGMOutput * os = NULL);
  CATCGMOperator::CATCheckDiagnostic CompareCurves        (CATCurve    *, CATCrvLimits &, CATGeometryPack *,double ErrTol, double WarningTol, CATBoolean CurveTypeComparison,   CATCGMOutput * os = NULL);
  CATCGMOperator::CATCheckDiagnostic CompareSurfaces      (CATSurface  *, CATSurLimits &, CATGeometryPack *,double ErrTol, double WarningTol,                                   CATCGMOutput * os = NULL);
  CATCGMOperator::CATCheckDiagnostic CompareArcsNumber    (CATCurve    *, CATCrvLimits &, CATCurve   *, CATCrvLimits &,  CATCGMOutput * os = NULL);
  CATCGMOperator::CATCheckDiagnostic ComparePatchNumber   (CATSurface  *, CATSurLimits &, CATSurface *, CATSurLimits &, CATCGMOutput * os = NULL );
  CATCGMOperator::CATCheckDiagnostic CompareSurfParameter (CATSurface  *, CATSurLimits &, CATSurface *, CATSurLimits &, CATCGMOutput * os = NULL );
  CATCGMOperator::CATCheckDiagnostic CurveDerivativesCheck(CATCurve    *, CATCrvLimits &, CATCurve   *, CATCrvLimits &,  CATCGMOutput * os = NULL);
  CATCGMOperator::CATCheckDiagnostic CurveMaxGap          (CATCurve    *, CATCurve *,    CATCGMOutput * os = NULL);
  CATCGMOperator::CATCheckDiagnostic CurveMapping         (CATCurve    *, CATCurve *,    CATCGMOutput * os = NULL);

//==================================================================================
//
// DATA
//
//==================================================================================

private:
  CATGeoFactory            * _Factory;
  CATSoftwareConfiguration * _Config;
  CATLONG32                  _NbPoints, _NbCrv, _NbSur;
  CATLONG32                  _MaxPoint ,_MaxCrv,_MaxSur;
  CATPoint                ** _PointTab;
  CATCurve                ** _CurveTab;
  CATSurface              ** _SurfaceTab;
  CATCrvLimits             * _CrvLimitsTab;
  CATSurLimits             * _SurLimitsTab;

  int                        _DepileCurve,_DepileSurface,_DepilePoint; // For Get methods
  CATBoolean                 _InitCrv,_InitPoint,_InitSur;
  CATBoolean                 _IsUnStreamed, _Lock;

  CATBoolean                 _ScaleManagerOwned;
  CATGeoODTScaleManager    * _ScaleManager; // Q48 (06/2014): X-scale


};

#endif

