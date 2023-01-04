// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATIntersectionAutoSurImp.h
//  Class for self-intersection of a surface
//=============================================================================
// Usage Notes:
//
// 
//=============================================================================
// 26/03/14 Q48 Creation
// 27/05/13 Q48 Add result point storage
// 28/05/13 Q48 Add canonical check for early exit
// 25/06/14 Q48 Add SetSurface and Reset methods
// 26/06/14 Q48 Add methods boundary treatments / boxing
// 24/07/14 Q48 Add treatment of closed surface seam boundary
//              Add treatment of partial merge case for patch surfaces
//              Add check for duplicate points (UVRS)
// 28/07/14 Q48 Add filters for points (and debug check for pole)
//              Add filters for admissible and interior curves
//              Add tracking to swap "UV-1" : "UV-2" data for curve / surface merging
// 21/04/17 PKC compilation warning
//=============================================================================

#ifndef CATIntersectionAutoSurImp_h
#define CATIntersectionAutoSurImp_h

// Base class
#include "CATIntersectionAutoSur.h"

// C++11
#include "CATGeoOpVirtual.h"

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"

// Mathematics
class CATSoftwareConfiguration;
class CATTolerance;
#include "CATIsoParameter.h"
#include "CATMathSetOfLongs.h"
#include "CATMathBox.h"
#include "CATMathOBB.h"

// Advanced Mathematics
class CATMathSetOfPointsNDTwoTangents;

// Geometric Objects
class CATGeoFactory;
class CATSurface;
//class CATCurve;
//class CATPCurve;
class CATEdgeCurve;
class CATSurParam;
class CATSetOfSurParams;
class CATCartesianPoint;
#include "CATSurLimits.h"
#include "CATListOfCATEdgeCurves.h"

// Geometric Operators
class CATGeometryPack;
class CATGeoODTScaleManager; // Q48 (06/2014): X-scale
class CATIntersectionSurSur;
class CATIntersectionSurSurGen;
class CATSurSurResultCurve;
#include "CATIntersectionSign.h"
#include "CATIntersectionOrientation.h"

// Local classes
class CATAutoSurPatchInfo;
class CATAutoSurPatchInfoArray;
class CATAutoSurMergedPatchInfo;

class CATAutoSurCurveData;
class CATAutoSurPatchCurveData;
class CATAutoSurPatchSurfaceData;

class CATAutoSurResultPoint;
class CATAutoSurResultCurve;
class CATAutoSurResultSurface;

// Debug
#include "CATCGMOperatorDebug.h"
#include "CATGeoOpTimer.h"
#include "CATGeoOpDebug.h" // must be included to get #define GEOPDEBUG to be propagated here

#ifdef GEOPDEBUG
#include "CATUnicodeString.h"
#endif

class ExportedByY30C3XGG CATIntersectionAutoSurImp : public CATIntersectionAutoSur
{
public:

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  enum PatchSeamType { NoSeam, SeamOnMinEdge, SeamOnMaxEdge };

  //================================================
  //  Constructors / Destructors
  //================================================

protected:
  CATIntersectionAutoSurImp(); // Default constructor - do not use


public:
  // Constructors to be used
  CATIntersectionAutoSurImp(CATGeoFactory            * iFactory, 
                            CATSoftwareConfiguration * iConfig,
                            CATSurface               * iSurface);

  virtual ~CATIntersectionAutoSurImp();

  //================================================
  //  Set inputs
  //================================================

  virtual void SetSurface(      CATSurface * iSurface,
                          const CATBoolean   iForceReset = FALSE);

  virtual void SetSurLimits(const CATSurLimits & iSurLimit);
  
  //virtual void SetSeedParams(const CATSetOfSurParams & iUVParam);

  //================================================
  //  Get results
  //================================================

  //  Points
  //========

  virtual CATLONG32 GetNumberOfPoints() const;
  virtual void BeginningPoint();
  virtual CATBoolean NextPoint();

  virtual CATPointOnSurface* GetPointOnSurface(const CATLONG32 iPointIndex) const;

  virtual void GetSurParam(CATSurParam & oSurParam1, 
                           CATSurParam & oSurParam2) const;

  virtual CATCartesianPoint * GetCartesianPoint() const;

  //  Curves
  //========

  virtual CATLONG32 GetNumberOfCurves() const;
  virtual void BeginningCurve();
  virtual CATBoolean NextCurve();

  virtual CATEdgeCurve* GetEdgeCurve();
  virtual CATIntersectionSign GetSignatureOn(const short iSignatureIndex); 
  virtual CATIntersectionCrossing GetCrossingOn(const short iCrossingIndex);
  virtual void GetStartingPointsIndex(CATLONG32 & oBegin, CATLONG32 & oEnd);

  // Surfaces
  //=========

  virtual CATLONG32 GetNumberOfSurfaces() const;
  virtual void BeginningSurface();
  virtual CATBoolean NextSurface();

  virtual CATLISTP(CATEdgeCurve) GetSurfaceBoundaries(CATIntersectionOrientation *& oListOfPCurvesOrientation,
                                                      CATIntersectionOrientation  & oContourOrientation1,
                                                      CATIntersectionOrientation  & oContourOrientation2,
                                                      CATLONG32                  *& oStartIndices,
                                                      CATLONG32                  *& oEndIndices);

  // Utility
  // =======

  static void MergePatchCurves(      CATAutoSurPatchCurveData **  iPatchCurves, 
                               const CATLONG32                    iNumPatchCurves,
                               const CATTolerance               & iTolObject,
                                     CATAutoSurResultCurve    **& oMergeCurves,
                                     CATLONG32                  & oNumMergeCurves);


  //================================================
  //  Run
  //================================================

  virtual int RunOperator();

  //
  //=============================================================================
  // Internal data class (must be public)
  //=============================================================================
  //
public:
  
    
  class CurveMergeElement
  {
  public:
    CurveMergeElement();
    CurveMergeElement(const CATLONG32, const CATBoolean);
    CurveMergeElement(const CATLONG32, const CATBoolean, const CATBoolean);
    CurveMergeElement(const CurveMergeElement&);
    ~CurveMergeElement();

    void SetDataFromListFormat(const CATLONG32);

    static CATLONG32 GetIndexFromListFormat(const CATLONG32);
    static CATLONG32 ConvertToListIndex(const CATLONG32);

    CATLONG32 ConvertToListFormat() const;
    CATLONG32 GetIndex() const;
    CATBoolean GetOrientation() const;
    CATBoolean GetSwapUVRS() const;

    GEOPDEBUG_CMD(CATUnicodeString Debug_StringOfElement() const);

  private:
    CATLONG32 _Index;
    CATBoolean _Orientation;
    CATBoolean _SwapUVRS;
  };

  class CurveMergeArray
  {
  public:
    CurveMergeArray();
    ~CurveMergeArray();

    void AppendMerge(const CurveMergeElement & iElem);
    void AppendMerge(const CurveMergeElement * iElem);
    void PrependMerge(const CurveMergeElement & iElem);
    void PrependMerge(const CurveMergeElement * iElem);

    CATLONG32 GetNumMerges() const;

    const CurveMergeElement* GetMergeElement(const CATLONG32 iIndex) const;

    CATBoolean ContainsMergeWithIndex(const CATLONG32 iIndex) const;

    GEOPDEBUG_CMD(CATUnicodeString Debug_StringOfElements() const);

  private:
    void IncreaseStorage();

    CATLONG32 _NumElements;
    CATLONG32 _NumElementsAlloc;

    const CurveMergeElement ** _Array;
  };

  class SurfaceMergeElement
  {
  private:
    SurfaceMergeElement();
  public:
    SurfaceMergeElement(const CATLONG32);
    ~SurfaceMergeElement();

    const CATLONG32 GetInitSurfaceIndex() const;

    const CATLONG32  GetNumMerges() const;

    const CATBoolean GetMerge(const CATLONG32            iIndex, 
                                    CATLONG32          & oSurfIndex1, 
                              const CurveMergeElement *& oCurveBoundaryElement1, 
                                    CATLONG32          & oSurfIndex2, 
                              const CurveMergeElement *& oCurveBoundaryElement2) const;

    void AddMerge(const CATLONG32                     iSurfIndex1, 
                  const CurveMergeElement           & iCurveBoundaryElement1, 
                  const CATLONG32                     iSurfIndex2, 
                  const CurveMergeElement           & iCurveBoundaryElement2,
                        CATAutoSurPatchSurfaceData ** iPatchSurfaces = NULL);

    void AddSet(const SurfaceMergeElement         & iSetToAdd,
                      CATAutoSurPatchSurfaceData ** iPatchSurfaces = NULL);

    CATBoolean Contains(const CATLONG32 iSurfIndex1,
                        const CATLONG32 iCurveBoundaryIndex1) const;

  private:
    void IncreaseStorage();

    CATLONG32 _InitSurfaceIndex;

    CATLONG32 _NbMerge;

    CATLONG32 _ArraySize;

    CATLONG32* _SurfaceIndex1ToMerge;
    CATLONG32* _SurfaceIndex2ToMerge;
    CurveMergeArray _CurveIndexSurface1ToMerge;
    CurveMergeArray _CurveIndexSurface2ToMerge;
  };

  //
  //=============================================================================
  // Protected methods
  //=============================================================================
  //
protected:

  // Admin
  // =====

  static const CATString * GetDefaultOperatorId() { return & _OperatorId; };

  void ResetData();

  void InitialiseForConstructor();
  void InitialiseData();

  void LockSurface();
  void UnlockSurface();

  // Algorithmic
  // ===========

  CATSurLimits GetReducedSurfaceLimits() const;
  CATSurParam GetReducedStartParam() const;
  CATSurParam GetReducedEndParam() const;

  // Subdivision
  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  enum BoundaryInfo { BoundaryNone = 0, BoundaryMin, BoundaryMax, BoundariesBoth };
  BoundaryInfo IsOnBoundary(const CATLONG32, const CATLONG32, const CATLONG32) const;
  CATBoolean IsOnMinBoundary(const BoundaryInfo) const;
  CATBoolean IsOnMaxBoundary(const BoundaryInfo) const;

  CATBoolean* FillBoundaryInfo(const CATIsoParameter) const;
  
  CATBoolean  FillSeamInfo(const CATIsoParameter, CATMathSetOfPointsND & oSeamList) const;
  CATBoolean  FillSeamInfo_GenericFillet(CATMathSetOfPointsND & oSeamList) const;

  PatchSeamType IsPatchOnSeam(const CATIsoParameter, const CATSurLimits &, CATMathSetOfPointsND &) const;

  CATBoolean InitialisePatchInfo();
  void ConstructPatchData();
  void MergePatchData();
  CATLONG32 DoMergePatchData(const CATAngle iMergeThresholdAngle);

  // Canonical
  CATBoolean IsPossibleIntersection() const;

  // Special surface types
  CATBoolean TreatSpecialSurfaces();
  CATBoolean TreatTabulatedCylinderSurface();

  // Intersection
  void IntersectAllPatches();

  void IntersectOnePatch(const CATAutoSurPatchInfo * iPatchInfo);

  void IntersectPatchPair(const CATAutoSurPatchInfo * iPatchInfo1, 
                          const CATAutoSurPatchInfo * iPatchInfo2);

  // Process output
  // ==============

  // Points
  CATLONG32 FilterPoints(const CATAutoSurPatchInfo      * iPatch1,
                         const CATAutoSurPatchInfo      * iPatch2,
                               CATIntersectionSurSurGen * iInter);

  GEOPDEBUG_CMD(CATBoolean Debug_IsAPolePoint(const CATAutoSurPatchInfo* iPatch1, const CATAutoSurPatchInfo* iPatch2, const CATSurParam iPar[]) const); // to be fully implemented when needed

  CATBoolean IsMidPointDistinct(const double iPt[]) const;
  CATBoolean IsMidPointDistinct(const CATSurParam iPar[]) const;

  CATBoolean IsDuplicatePoint(const CATSurParam   iPar[],
                                    CATLONG32   & oDuplicateIndex) const;


  // Curves
  CATLONG32 FilterPatchCurves(const CATAutoSurPatchInfo      * iPatch1,
                              const CATAutoSurPatchInfo      * iPatch2,
                                    CATIntersectionSurSurGen * iInter);

  CATBoolean ArePatchBordersSeparated(const CATSurSurResultCurve * iCurve,
                                      const CATAutoSurPatchInfo  * iPatchInfo1,
                                      const CATAutoSurPatchInfo  * iPatchInfo2) const;

  CATBoolean AreCurveExtremitiesSeparated(const CATSurSurResultCurve * iCurve) const;
  
  CATBoolean IsCurveExtremitySeparated(const CATSurSurResultCurve * iCurve, 
                                       const CATBoolean             iStart) const;

  // Surfaces
  CATLONG32 StorePatchSurfaces(const CATAutoSurPatchInfo      * iPatch1,
                               const CATAutoSurPatchInfo      * iPatch2,
                                     CATIntersectionSurSurGen * iInter);


  // Curve output
  void MergePatchCurves();

  static CATAutoSurResultCurve* CreateResultCurve(      CATAutoSurPatchCurveData ** iPatchCurves,
                                                  const CurveMergeArray           & iMergeList,
                                                  const CATTolerance              & iTolObject);
                                                        
  static CATAutoSurResultCurve* CreateResultCurve(      CATAutoSurPatchCurveData ** iPatchCurves,
                                                  const CATLONG32                   iPatchCurveIndex,
                                                  const CATTolerance              & iTolObject);

  static CATBoolean MergeSingleCurveData(const CATBoolean                  iSearchForwards,
                                               CATAutoSurPatchCurveData ** iPatchCurves, 
                                         const CATLONG32                   iNumPatchCurves,
                                         const CATTolerance              & iTolObject,
                                               CurveMergeArray           & ioCurveIndices);
  // Surface output
  void MergePatchSurfaces();
  CATBoolean MergePatchSurface(const CATLONG32             iPatchSurfaceIndex,
                                     SurfaceMergeElement & ioMergeData, 
                                     SurfaceMergeElement * ioPartialMergeData = NULL);

  CATBoolean MergeSingleSurfaceBoundaryData(const CATLONG32             iPatchSurfaceIndex, 
                                            const CATLONG32             iPatchCurveBoundaryIndex, 
                                                  SurfaceMergeElement & ioMergeData, 
                                                  SurfaceMergeElement * ioPartialMergeData = NULL);

  // Other
  void CleanAdmissibleCurves();

  // Data handling
  // =============

  static void AddElementToList(const CurveMergeElement & iElem,
                               const CATBoolean          iAddToEnd,
                                     CurveMergeArray   & ioMergedList);

  void IncreasePatchCurveStorage();
  void IncreasePatchSurfaceStorage();

  void StorePatchCurveResult(const CATAutoSurPatchInfo  * iPatch1,
                             const CATAutoSurPatchInfo  * iPatch2,
                                   CATSurSurResultCurve * iResultCurve);

  void StorePatchSurfaceResult(const CATAutoSurPatchInfo         * iPatch1,
                               const CATAutoSurPatchInfo         * iPatch2,
                               const CATLONG32                     iNumCurves,
                                     CATIntersectionOrientation  * iPCurveOrientation[],
                               const CATIntersectionOrientation  & iLoopOrientation1,
                               const CATIntersectionOrientation  & iLoopOrientation2,
                                     CATSurSurResultCurve       ** iResultCurves);

  void CheckPointIndex() const;
  void IncreasePointStorage();
  void StorePointResult(CATAutoSurResultPoint*);

  void CheckCurveIndex() const;
  void IncreaseCurveStorage();
  void StoreCurveResult(CATAutoSurResultCurve*);

  void CheckSurfaceIndex() const;
  void IncreaseSurfaceStorage();
  void StoreSurfaceResult(CATAutoSurResultSurface*);

  //
  //=============================================================================
  // Protected data
  //=============================================================================
  //
protected:

  // Input data
  // ==========

  CATSoftwareConfiguration * _Config;

  CATSurface * _Surf;
  CATSurface * _SurfRep;

  CATSurLimits _SurLimits;

  // Internal options
  // ================

  // These data are constant for the life of the operator. They are
  // cached to allow them to be stored in the replay mechanism

  short      _MergeNumMaxIterations;
  double     _MergeMaxAngleThreshold;

  CATBoolean _ApplyPointFilters;
  CATBoolean _ApplyPatchCurveFilters;

  // Derived data cache
  // ==================

  const CATTolerance & _TolObject;
  const double _Tolerance;

  CATGeoFactory * _ImplicitFactory;

  // Computed data cache
  // ===================

  CATAutoSurPatchInfoArray* _PatchInfo;

  CATBoolean _IsLock;


  //------------------------
  // Iterators parameters
  //------------------------
  //

  // For point solutions 
  // -------------------

  CATLONG32 _NbPoints, _NbAllocPoints, _IndexPoint;
  CATAutoSurResultPoint ** _PointSol;
  
  // For curve solutions
  // -------------------

  CATLONG32 _NbCurves, _NbAllocCurves, _IndexCurve;
  CATAutoSurResultCurve** _CurveSol;
  
  CATLONG32 _NbPatchCurves, _NbAllocPatchCurves;
  CATAutoSurPatchCurveData** _PatchCurves;

  // For confused face solutions
  // ---------------------------

  CATLONG32 _NbSurfaces, _NbAllocSurfaces, _IndexSurface;
  CATAutoSurResultSurface** _SurfaceSol;
  
  CATLONG32 _NbPatchSurfaces, _NbAllocPatchSurfaces;
  CATAutoSurPatchSurfaceData** _PatchSurfaces;

  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:

  virtual const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  virtual CATExtCGMReplay* IsRecordable(short & LevelOfRuntime, short & VersionOfStream);

  static CATGeoODTScaleManager*  ReadInput_Constructor(CATCGMStream              & iStr,
                                                       int                         iVersionOfStream,
                                                       CATGeoFactory            *& oFactory,
                                                       CATSurface               *& oSurf,
                                                       CATSoftwareConfiguration *& oConfig);


  virtual void ReadInput(CATCGMStream          & iStr,
                         int                     iVersionOfStream,
                         CATGeoODTScaleManager * iScaleManager);

  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);

  virtual void WriteCurvesToPack(CATGeometryPack*);

  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  virtual CATBoolean                         ValidateOutput(CATCGMStream & ioStream, 
                                                            CATCGMOutput & os,
                                                            int            VersionNumber = 1);

  virtual void Dump(CATCGMOutput & os);

  virtual void DumpOutput(CATCGMStream & ioStream, 
                          CATCGMOutput & os, 
                          int            VersionNumber = 1);

  virtual void DumpOutput(CATCGMOutput & os);

protected:
  void SetSoftwareConfiguration(CATSoftwareConfiguration* iSoftwareConfiguration);
  
  //========================================================================
  // Debug
  //========================================================================
protected:
  GEOPDEBUG_CMD(CATLONG32 _NumIntersections);

  GEOPDEBUG_CMD(void Debug_ExitOnResult() const);
  GEOPDEBUG_CMD(void Debug_CheckMergedCurvePoints(CATAutoSurResultCurve*) const);

  GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromResults(const CATIntersectionSurSurGen*) const);
  GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromResults(const CATLONG32, const CATLONG32, const CATLONG32) const);

  GEOPDEBUG_CMD(void Debug_PrintPatchResults() const);
  GEOPDEBUG_CMD(void Debug_PrintPatchPointResults() const);
  GEOPDEBUG_CMD(void Debug_PrintPatchCurveResults() const);
  GEOPDEBUG_CMD(void Debug_PrintPatchSurfaceResults() const);

  GEOPDEBUG_CMD(void Debug_DrawInterSurSurResults(CATIntersectionSurSurGen*) const);
  GEOPDEBUG_CMD(void Debug_DrawInterSurSurResults_Points(CATIntersectionSurSurGen*) const);
  GEOPDEBUG_CMD(void Debug_DrawInterSurSurResults_Curves(CATIntersectionSurSurGen*) const);
  GEOPDEBUG_CMD(void Debug_DrawInterSurSurResults_Surfaces(CATIntersectionSurSurGen*) const);

  GEOPDEBUG_CMD(void Debug_DrawPatchBoundaries(const int * iRGB = NULL) const);
};
#endif
