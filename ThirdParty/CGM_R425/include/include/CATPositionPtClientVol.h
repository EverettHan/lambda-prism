/* -*-c++-*- */
#ifndef CATPositionPtClientVol_H
#define CATPositionPtClientVol_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
// CATPositionPtClientVol :

// Set membership algorithm tailored for foreign implementations of volumes
// Ray tracing analysis on foreign volumes

//=============================================================================
// Usage Notes:

// Use ForceComputationOnBorders() if points located on the boundary within
// a given tolerance must be found, even if it is costly. Otherwise, they will
// be found only if their distance to the boundary <projected onto one of the
// rays>  is smaller than the tolerance

//=============================================================================
// Nov. 1999.                                                   C.Hurch
//=============================================================================
#include "YI00IMPL.h"
#include "CATTopDefine.h"
#include "CATMathBox.h"      // agregated classes
#include "CATMathVector.h"
#include "CATSurParam.h"
#include "CATMathInline.h"
#include "CATCurve.h"
#include "CATListOfCATCurves.h"

class CATMathPoint;
class CATMathVector;
class CATVolume;
class CATSurface;
class CATFace;
class CATLine;
class CATSurLimits;
class CATCrvParam;
class CATGeoFactory;
class CATIntersectionCrvSur;
class CATPositionPtFaceOperator;
class CATCGMOutput;
class CATSoftwareConfiguration;

class ExportedByYI00IMPL CATPositionPtClientVol
{
  public :

    //------------------------------------------------------------------
    // Declaration of inner classes used as interfaces between the algorithm
    // and the client model. The user only needs to choose CATClientVolume1 or
    // CATClientVolume2, then construct one object, that is, provide all its
    // call-back methods. The difference between the two classes is spotted on
    // the way faces can be visited by an iterator : ClientVolume1 is a simple
    // volume model and gives back a number of faces and allows working on its
    // n-th face, whereas ClientVolume2 must encapsulate the iteration context
    // itself and provide a NextFace method to work on the "current face",
    // therefore enabling optimization if jumping to a next face is less time
    // -consuming than counting faces in order to work on the n-th one. Besides,
    // the second client class is designed to process several points together
    // in the point/face set membership call-back, also for optimization purposes

    // The second model provides three constructors, only the third one is
    // designed for client data and must be used by the application. The first
    // two constructors are used internally to plug CATVolumes or first kind of
    // client volumes onto this class.
    //------------------------------------------------------------------

    struct ExportedByYI00IMPL CATClientVolume1 {

      // iClientData points to the application data that represents a volume, the
      // same pointer will be given as input to all call-backs
      // The meaning of the call-backs arguments is listed below in the "Data" section
      CATClientVolume1(void * iClientData, 
                       void (*iGet3DBox)(void*,CATMathBox&),
                       void (*iGetUVBox) (void*, CATLONG32, const CATSurLimits*&),
                       CATLONG32 (*iGetNumberOfFaces)(void*),
                       CATSurface* (*iGetSurface)(CATLONG32,void*,short&),
                       CATLocation (*iIsPointInsideFace)
                                   (CATSurParam&,CATLONG32,double,void*));
      ~CATClientVolume1();
      void DumpObj(CATCGMOutput& s) const;
      
      // Data
      void            * _ClientData;
      void           (* _Get3DBox) (void * iClientData, CATMathBox& oBox);
      void           (* _GetUVBox) (void * iClientData, CATLONG32 iFaceIndex, const CATSurLimits *& oUVBox);
      CATLONG32           (* _GetNumberOfFaces) (void * iClientData);
      CATSurface *   (* _GetSurface)(CATLONG32 iFaceIndex, void * iClientData, short & oOriVsFac);
      //              Following method must return -1 if the point is inside the
      //              face, 1 if it is outside, and 2 if it is on the border,
      //              within iTol tolerance in xyz.
      CATLocation    (* _IsPointInsideFace)(CATSurParam & iParm, CATLONG32 iFaceIndex, 
                                            double iTol, void * iClientData);
    };


    struct ExportedByYI00IMPL CATClientVolume2 {

      // Three constructors are provided, one for native CATVolumes, one for the
      // first client class (CATClientVol1) and one for this kind of client volumes.
      // The first two constructor are used internally to plug the algorithm
      // onto CATVolumes or CATClientVolume1, and must not be used by the application
      // Only the last constructor must be used externally, it is designed for
      // client volumes that encapsulate a face-iteration context, and it  must be
      // given the following arguments :

      // iClientData points to any kind of "volume" model that enables the five
      // call-backs described herefater :
      // 3 methods are designed to iterate on faces :
      // - iStartIterator initializes the iterator (possibly enclosing allocated data)
      // - iEndIterator cleans up the iterator, so that it can be run again without 
      //   leaving data leaks (iEndIterator can deallocate data if needed)
      // - iNextFace jumps to the next face, which becomes the "current face", it
      //   returns 1 if there is one, zero if all faces have been visited. iNextFace
      //   will be called once after iStartIterator to get to the first face
      // 3 methods inquire on the current face :
      // - iGetSurface gives the CATSurface that holds the current face
      // - iArePointsInsideCurrentFace runs a test membership algorithm in the point
      //   / face context, and computes a table of CATLocation corresponding to the 
      //   table of input CATSurParams: Each result is CATLocationOuter if the given
      //   CATSurParam lies outside the current face, CATLocationInner if it lies
      //   inside, and CATLocationFull if it is located on the boundary, within
      //   iTolXYZ tolerance. The output table must not be allocated in the call-back,
      //   it is already allocated when entering the method
      // - iGetVolSideVsFace is optional. If returns the CATSide of the volume with
      //   respect to the current face. If not provided, intersection signatures will
      //   never be processed, hence "Signature Sensitive mode" will not be operational
      // Consequently, iClientData should retain the volume plus a current face.
      // The meaning of the call-backs arguments can be read in the "Data" section

      CATClientVolume2(CATVolume * iVolume);
      CATClientVolume2(CATClientVolume1 * iCVol1);
      CATClientVolume2(void * iClientData,
                       void (*iGet3DBox)(void*,CATMathBox&),
                       void (*iGetUVBox) (void*,const CATSurLimits*&),
                       void (*iStartIterator)(void*),
                       void (*iEndIterator)(void*), short (*iNextFace)(void*),
                       CATSurface* (*iGetSurface)(void*, short&),
                       void (*iArePointsInsideCurrentFace)(CATSurParam*, CATLONG32,
                                                           double, void*,
                                                           CATLocation*&),
                       CATSide (*iGetVolSideVsFace)(void*) = 0);
      ~CATClientVolume2();
      void CleanAllocatedData(); // resets the ClientVolume 
      void DumpObj(CATCGMOutput& s) const;
      void InternalInit();

      // Data
      void             * _ClientData; // one and only one of the three pointers
      CATClientVolume1 * _CVol1;      // _ClientData, _CVol1 or _Volume will not
      CATVolume        * _Volume;     // be null (hidden to the application)

      //               call-backs used to handle client data
      void            (* _Get3DBox)         (void * iClientData, CATMathBox& oBox);
      void            (* _GetUVBox)         (void * iClientData, const CATSurLimits *& oUVBox);
      void            (* _StartIterator)    (void * iClientData);
      void            (* _EndIterator)      (void * iClientData);
      short           (* _NextFace)         (void * iClientData);
      CATSurface *    (* _GetSurface)       (void * iClientData, short & oOriVsFac);
      void            (* _ArePointsInsideCurrentFace)(CATSurParam *  iParms,
                                                      CATLONG32      iNbPoints,
                                                      double         iTolXYZ,
                                                      void        *  iClientData,
                                                      CATLocation *& oPositions);
      CATSide         (* _GetVolSideVsFace) (void * iClientData);

      //                    internal data used to plug CATClientVolume1
      CATLONG32                  _CVol1_NbFaces;
      CATLONG32                  _CVol1_CurFaceIndex;

      //                    internal data used to plug CATVolumes
      CATLONG32                  _Volume_CurDomainIndex;
      CATLONG32                  _Volume_CurCellIndexWithinDomain;
      CATFace             * _Volume_CurFace;
      CATPositionPtFaceOperator * _CurPFO;

      //                    allocated list used to plug CATVolumes or ClientVolume1
      CATLocation         * _CurPosList;
    };

    //------------------------------------------------------------------
    // Construction, destruction and Set methods
    // On of the three SetVolume methods must be called before running the operator
    // The tolerance, by default, will be set to the CGM model resolution, for
    // the container in which CATSurfaces will be returned for each client face
    //------------------------------------------------------------------
    CATPositionPtClientVol(CATSoftwareConfiguration * iConfig, CATMathPoint * iPoint = 0);
    virtual ~CATPositionPtClientVol();

    void SetPoint(CATMathPoint * iPoint);
    void SetVolume(CATVolume * iVol);
    void SetVolume(CATClientVolume1 * iCVol1);
    void SetVolume(CATClientVolume2 * iCVol2);

    void SetXYZTolerance(double iTolXYZ);

    //------------------------------------------------------------------
    // Setting the investigation mode for points close to the boundary
    // If this mode is set, the poerator turns out to be musch more cpu-costly
    // Use iForce = 0 to unset this mode, and iForce = 1 (or no arguments) to
    // set it on again. This mode is unset by default
    //------------------------------------------------------------------
    void ForceComputationOnBorders(short iForce = 1);

    //------------------------------------------------------------------
    // The following method tunes the algorithm to take line / face intersection
    // signatures into account in the set-membership computation (each ray is
    // analyzed as going in or out of volume matter at each intersection, and the
    // consistency of all collected data is checked). However, this requires an
    // access to the face / volume CATSides, so this mode is not allowed (and it is
    // not the default mode) when sides are not available (if a ClientVolume1 has
    // been provided, or a ClientVolume2 without the "iGetVolSideVsFace" argument
    // input to the ClientVolume2 constructor)
    //------------------------------------------------------------------
    void SetSignatureSensitiveMode(short iForce = 1);

    //------------------------------------------------------------------
    // If the set-membership result must not be "on the boundary", it is possible
    // to force the algorithm to come to another conclusion, no tolerance will then
    // be applied when positioning an intersection on each ray
    //------------------------------------------------------------------
    void ForceInsideOrOutside(short iForce = 1);

    //------------------------------------------------------------------
    // Runs the set-membership operator
    //------------------------------------------------------------------
    void Run();

    //------------------------------------------------------------------
    // Reading result

    // returned CATLocation is
    // CATLocationOuter if the point is outside the volume
    // CATLocationInner if the point is inside the volume
    // CATLocationFull if the point is on the boundary of the volume

    // If the point is on the boundary, GetBoundaryInformation(..) can be used
    // to get the involved CATFace (if a CATVolume was provided, otherwise a face
    // index starting from zero will be returned), the involved CATSurface and the
    // CATSurParam that corresponds to the closest point on the boundary.
    //------------------------------------------------------------------
    CATLocation GetPosition();
    void GetBoundaryInformation(CATLONG32 & oFaceIndex, CATFace ** oFace = 0,
                                CATSurface ** oSurf = 0, CATSurParam * oParm = 0);

    //------------------------------------------------------------------
    // Reading input data (introspection methods)
    // GetClientVolumeX() methods return Null pointer if no corresponding client volume
    // of the specified type was provided by a Set method.
    // GetVolume() returns a CATVolume only if one has been provided by SetVolume
    // The factory returned is the one that contains all CATSurfaces given by call-backs
    // The tolerance returned is infered from the factory if it is not set by the user
    // GetComputationOnBordersMode returns 1 if border computation is on, 0 if it is off
    //------------------------------------------------------------------
    CATMathPoint * GetMathPoint();
    CATClientVolume1 * GetClientVolume1();
    CATClientVolume2 * GetClientVolume2();
    CATVolume * GetVolume();
    double GetXYZTolerance();
    CATGeoFactory * GetFactory();
    short GetComputationOnBordersMode();

    //------------------------------------------------------------------
    // Second function for this operator :

    // It is also possible to check the interferences of a single ray with
    // a given set of faces (CATClientVolume1 or 2), thru the following methods
    // (the ray is a half-line starting from the point given by SetPoint method
    // and running in the direction given by the following SetVector method)
    // If the ray is found lying on one face, no further computation is done
    // and the run method returns 1 (failure)
    //------------------------------------------------------------------
    void SetVectorForSingleRayAnalysis(const CATMathVector& iDirection);

    // Following Run method returns 1 if the interferences have not been computed,
    // and zero if it is ok
    short RunSingleRayAnalysis();

    // The number of interferences includes the origin point if it does lie on some faces
    // in the set (whether it does or not can be checked by oNbTimesOriginOnTheSetOfFaces)
    CATLONG32 GetNbInterferences(CATLONG32 * oNbTimesOriginOnTheSetOfFaces = 0);

    // Each interference can be investigated by the following method (*oIsTheOrigin = 1
    // if the current interference is coincident with the origin point)
    void GetClashInformation(CATLONG32 iClashIndex, CATLONG32 & oFaceIndex, short * oOnFaceBoundary = 0,
      short * oFaceSignat = 0, CATSurface ** oSurf = 0, CATSurParam * oParm = 0,
      double * oRayParam = 0, short * oIsTheOrigin = 0);

    //------------------------------------------------------------------
    // Copy construction and operator= are declared but not defined. Copying
    // this kind of objects does not seem necessary. This omission is intended
    // to issue a build-error if one of the methods happens to be called
    //------------------------------------------------------------------
    CATPositionPtClientVol& operator=(const CATPositionPtClientVol&);
    CATPositionPtClientVol(const CATPositionPtClientVol&);

    //------------------------------------------------------------------
    // Internal structure used to handle the intersections of the volume with one ray
    //------------------------------------------------------------------
    struct RayClash {
      CATLONG32         _FaceIndex;
      CATSurface * _Surf;
      CATSurParam  _Surp;
      double       _LnParm;
      short        _FaceSignat; // scalar product <tgt ray, norm. to face>
      CATSide      _VolSideIfAvailable;
      CATLocation  _Loc;      // inner(-1) = inside face, outer(+1) = outside, full(+2) = on face border
      short        _OnOrigin; // -1 = unknown, 0 = no, 1 <=> _SqDistToOrigin<_TolXYZ**2
      double       _SqDistToOrigin;

      RayClash();
      ~RayClash();
      void Initialize(CATLONG32 iFaceIndex, CATSurface * iSurf, CATSide iVolSide, 
        CATSurParam & iSurp, double iLnParm, short iFaceSignature,
        short iOnOrigin=-1, double iSqDistToOrigin=0.);
      void DumpObj(CATCGMOutput& s, CATLONG32 iIndex = -1) const;
    };

    struct OneRay {
      CATPositionPtClientVol * _Father;
      CATLine                * _HalfLine;

      CATIntersectionCrvSur  * _CurXLnSur;
      CATSurface             * _CurSurf;
      CATLONG32                     _NbPtsOnCurSurf;
      CATLONG32                     _CurSolutionNumberOnCenter; // 0 if center not on _Surf
      
      RayClash               * _ClashList;

      CATLONG32                     _NbPoints;    // Size of _ClashList
      CATLONG32                     _MaxNbPoints; // Allocated size of _ClashList

      // _Nbonfirmed = number of clashes inside face or on its boundary
      CATLONG32                     _NbConfirmed;

      // In case a face is tangent to the half-line, its index is stored
      CATLONG32                     _IndexOfFaceInConfusionIfAny;

      // _OriginFoundOnBorder = 0 if the origin is not on the set of faces,
      // = 1 otherwise
      CATLONG32                     _OriginFoundOnBorder;

      OneRay();
      ~OneRay();
      void CleanGeometry();
      void SetRay(CATPositionPtClientVol * iFather, CATMathPoint * iEndOfRay);
      void SetCurSurface(CATSurface * iCurSurf, const CATSurLimits * iCurUVBox);
      void AllocateUpTo(CATLONG32 iNeededSize);
      // Following method returns the number of intersections with the surface
      CATLONG32 ComputeIntersections(CATLONG32 iIndFac, short iSurfVsFac,
                                     CATSoftwareConfiguration* iConfig);
      void TrimByCurrentFace();
      short GetDiagnosticForThisRay(); // gives 1=inside, -1=outside, 0=boundary

      // Compute positions from first and last clash (returns -2 if unknown)
      // iRelativeToleranceMode to make comparaison with relative tolerance
      void ComputePositionFromFirstAndLastClash(short                   & oPosFromFirstClash,
                                                short                   & oPosFromLastClash, 
                                                short                     iRelativeToleranceMode,
                                                CATSoftwareConfiguration* iConfig);
      
      void DumpObj(CATCGMOutput& s) const;
    };

    // constants : maximum number of rays used, and allocation step
    enum { _TotalNbRays = 5, _MajAllocStep = 10 };

    //------------------------------------------------------------------
    // Utility method used to hide the kind of client data used
    // oPositions will be allocated inside the following method
    //------------------------------------------------------------------
    void ArePointsInsideCurrentFace(CATSurParam * iParm,
                                    CATLONG32 iNbPoints,
                                    double iTol,
                                    CATLocation *& oPositions);

    // Initializing _FoundBorderParm
    void SetBorderParm(CATSurParam & iParm);

    // Reading internal data
    short IsSingleRayModeActive();
    CATSide GetVolumeSide(); // CATSideUnknown si non disponible
    INLINE short GetForceInsideOrOutside() const;

    //------------------------------------------------------------------
    // Dump methods
    //------------------------------------------------------------------
    void DumpObj(CATCGMOutput& s) const;
    friend ExportedByYI00IMPL CATCGMOutput& operator<< (CATCGMOutput& s,
                                     const CATPositionPtClientVol& iObj);

    CATSoftwareConfiguration * _Config;

  private:

    // Cleaning allocated data upon destruction or exception raised
    void Clean();
    void CleanWorkVol();

    // Positioning algorithm with rays, computes a list of 1 (inside), -1 (outside),
    // 0 (on the boundary) according to the <odd or even> number of intersections
    void ComputePositionsFromRays(CATMathVector * iRayVectors, CATLONG32 iNbRays,
                                  double iRayLength, short *& oPositions,
                                  short **& oPosFromFirstAndLastClash, CATLISTP(CATCurve) iCrvList);

    // Internal utility methods that hide the kind of construction used
    // (note : GetCurrentFace() returns null if no CATVolume was input)
    void Compute3DBox();
    void StartIterator();
    void EndIterator();
    short NextFace();
    CATFace * GetCurrentFace();
    CATSurface * GetCurrentSurface(short * oOriVsFac = 0);
    void GetUVBox(const CATSurLimits *& oUVBox);

    // Building several "OneRay" structures at a time
    void GenerateRays(CATMathVector * iRayVectors, CATLONG32 iNbRays,
                      double iRayLength);

    // Checking precisely if the center is on the border
    short CheckOnBorder();

    // Utility (includes center point in a box)
    void IncludeCenterPoint(double & ioXMin, double & ioXMax,
      double & ioYMin, double & ioYMax, double & ioZMin, double & ioZMax);

    // Are face / volume sides available
    short AreSidesAvailable();

    //------------------------------------------------------------------
    // Internal data

    CATMathPoint     * _Point;
    CATClientVolume1 * _CVol1;
    CATClientVolume2 * _CVol2;

    double             _TolXYZ;
    short              _IsTolXYZSet;
    CATGeoFactory    * _Factory;

    // Data for single ray mode
    short              _SingleRayMode; // 0 or 1
    CATMathVector      _SingleRayVector; 

    // Border computation mode
    short              _ForceComputationOnBorder;

    // Origin point forced not to be on the boundary
    short              _ForceInsideOrOutside;

    // Signature sensitive mode
    short              _SignatureSensitiveMode;

    // a ClientVolume2 is used, whatever the kind of client volume formerly set
    CATClientVolume2 * _WorkCVol;
    CATMathBox         _3DBox;
    short              _Is3DBoxSet;

    // List of structures used to handle the intersection generated by one ray 
    // (one half-line)
    OneRay           * _Rays;
    CATLONG32               _NbRays;

    // Final result (for set-membership)
    CATLocation        _Position;

    // Boundary information, in case the point is on the border
    CATLONG32               _FoundBorderFaceIndex;
    CATFace          * _FoundBorderFace;
    CATSurface       * _FoundBorderSurf;
    CATSurParam        _FoundBorderParm;

    // Results for single ray mode
    CATLONG32               _NbInterferences;


};
INLINE short CATPositionPtClientVol::GetForceInsideOrOutside() const {
  return _ForceInsideOrOutside; }


#endif 
