/* -*-c++-*- */
#ifndef CATRadialSortOperator_H
#define CATRadialSortOperator_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
// CATRadialSortOperator :
//
// This operator orders (clockwise or counter clockwise) a set of CATEdges or
// CATCurves lying on a given surface and all incident to one point (or vertex),
// hereafter called "center". Constructor and destructor must be called (no
// Create and Remove methods are provided now)

// The CW or CCW orientation is relative to the normal to the surface

//=============================================================================
// Usage Notes:

// Incident CATEdges must be associated with their CATSide with respect to the 
// "center" vertex (left if it is the starting vertex, right if it is the end),
// this enables handling cyclic edges bordered by a single vertex.

// Incident CATCurves must be associated with a poec or crv-param corresponding
// to the center, plus an orientation (+1 or -1) giving the direction of the
// half-curve to be processed (if both directions must be processed, input the
// curve twice)

// Sorted edges can be retrieved either by a Next method that gives the edge
// following a given edge, or all together by a GetList method.
// Edges (or half-curves) are identified throughout the operator by an integer
// "id" which is, by default, the input range starting from zero (the first edge
// that is input is given id = 0, the second one is given id = 1, and so on)

//=============================================================================
// Nov. 1999.                                                   C.Hurch
// Feb. 2006.  traitement cas speciaux de courbes tangentes
//             pour l'operateur parallele                       AOV
//=============================================================================
#include "YI00IMPL.h"
#include "CATTopDef.h"
#include "CATCrvParam.h"      // agregated classes
#include "CATMathVector2D.h"
#include "CATMathInline.h"

class CATEdge;
class CATCurve;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATCrvParam;
class CATSurface;
class CATMathPlane;
class CATCGMOutput;
class CATSoftwareConfiguration;

#if defined(_AIX_SOURCE) && (__xlC__ >= 0x0500)
int CATCGMRadSortComparator( const void* iEl1, const void* iEl2);
#elif defined(_LINUX_SOURCE)
int CATCGMRadSortComparator( const void* iEl1, const void* iEl2);
#endif


class ExportedByYI00IMPL CATRadialSortOperator
{
  public :

    //------------------------------------------------------------------
    // Construction and destruction
    // If no surface is provided upon construction, please use the SetSurface
    // method before running the operator
    //------------------------------------------------------------------
    CATRadialSortOperator(CATSoftwareConfiguration * iConfig, CATSurface * iSurf=0);
    virtual ~CATRadialSortOperator();
  
    //-----------------------------------------------------------------------------
    // Adds a new edge or curve to be sorted by the operator :

    // The int value returned is the "id" of the edge (equal to *iId if an id was
    // already set as input, otherwise it is the sequential order of input edges,
    // starting from zero up to NbEdges-1). This enables a naming convention for
    // the application. If one edge is explicitly named, then all have to be
    // named by the user, mixing implicit and explicit ids is not allowed.

    // If a CATEdge is input, the side must be either left or right, Full and
    // Unknown sides cannot be accepted (input twice the same edge if a vertex 
    // is full).

    // If a CATCurve is input, the caller must either provide a poec that owns a
    // spec on the gien curve, or a crvparam relative to this curve.
    // The orientation (+1 or -1) of the half-curve to be processed is mandatory
    //------------------------------------------------------------------------------
    int AppendEdge(CATEdge * iEdge, CATSide iVtxEdgeSide, int * iId=0);
    int AppendEdge(CATCurve * iCurve, short iOrientation,
                   CATPointOnEdgeCurve * iPoec, int * iId=0);
    int AppendEdge(CATCurve * iCurve, short iOrientation,
                   CATCrvParam & iParm, int * iId=0);

    //------------------------------------------------------------------
    // Setting the surface and the orientation with respect to its normal
    // The surface is mandatory if it was not provided to the constructor,
    // it must be set only once (cannot be changed after appending edges)
    // Use SetCCW(-1) to set clockwise orientation
    //------------------------------------------------------------------
    void SetSurface(CATSurface * iSurface);
    void SetCCW(short iCCW = 1);

    //------------------------------------------------------------------
    // Runs the operator (no "basic" mode with implicit run is available,
    // since edges are input one after the other)
    // Returned value is 1 if everything is ok, 0 if at least two edges
    // could not be separated (Next and GetList methods are still available
    // in this case)
    //------------------------------------------------------------------
    int Run();

    //------------------------------------------------------------------
    // Retrieving sorted edges :

    // Either use Next to find which edge is "after" a given one, according to
    // the CW or CCW orientation (CCW by default), or use GetList to obtain the
    // whole sorted list (starting with the firt one input), that will not be
    // allocated in the method (must have been allocated before) and will have
    // to be deallocated by the user

    // Optional argument oIsSeparableFromPrevious, if not null, will point 
    // to zero if "next" edge could not be separated from previous one
    //------------------------------------------------------------------
    int Next(int iPreviousId, int * oIsSeparableFromPrevious = NULL);
    INLINE int GetNumberOfEdges();
    void GetList(int *& oList);

    //------------------------------------------------------------------
    // Reading input data (edges are retrieved by their CATCurve, even if
    // they were input as CATEdges; orientation and crvparam are optional)
    // GetCCW() returns +1 if current mode is CCW, -1 otherwise (CW)
    //------------------------------------------------------------------
    void GetEdge(int iId, CATCurve *& oCurve, short * oOrientation = 0,
      CATCrvParam * oParam = 0);
    CATSurface * GetSurface();
    INLINE short GetCCW();

    //------------------------------------------------------------------
    // Copy construction and operator= are declared but not defined. Copying
    // this kind of objects does not seem necessary. This omission is intended
    // to issue a build-error if one of the methods happens to be called
    //------------------------------------------------------------------
    CATRadialSortOperator& operator=(const CATRadialSortOperator&);
    CATRadialSortOperator(const CATRadialSortOperator&);

    //------------------------------------------------------------------
    // Dump methods
    //------------------------------------------------------------------
    void DumpObj(CATCGMOutput& s) const;
    friend ExportedByYI00IMPL CATCGMOutput& operator<< (CATCGMOutput& s,
                                     const CATRadialSortOperator& iObj);

    //--------------------------------------------------------------------------
    //Set pour le parallele:correction du tri pour les cas de courbes tangentes
    //--------------------------------------------------------------------------
    void SetCheckTangency();

  private:

    // Half-edge structure designed to model one incident edge and computed
    // data used for radial sort
    struct HEdg {
      CATRadialSortOperator * _father;
      int                     _id;

      CATEdge               * _edge;

      CATCurve              * _crv;
      CATPCurve             * _pcrv; // =_crv if lying on _Surf, otherwise null
      short                   _ori;  // -1 if increasing _crv param = outside hedg
      CATPointOnEdgeCurve   * _poec; // enables late report to pcrv if _crv is ecrv
      CATCrvParam             _parm;

      CATMathVector2D         _d1;  // first non degenerate derivative -> tangent
      double                  _ang; // angle with respect to first edge tangent
                                    // always measured counter-clockwise

      CATMathVector2D         _d2;    // derivative of d1
      short                   _okd2;  // 1 if _d2 could be computed (deriv.order<4)
      double                  _curva; // algebraic curvature = det(d1,d2)/|d1|**3

      // _abs is the id of the "absorbing" edge chosen to stand for an
      // equivalence class of non separable edges, equal to _id if none
      int                     _abs;

      // Initialization, either iPoec or iParm is not null
      // If iCrv is an edge-curve and encloses a pcurve on _Surf, and if a poec
      // is provided, the initialization method eventually stores a parm on pcurve
      void Initialize(CATEdge  *iEdge, CATRadialSortOperator * iFather, int iId, CATCurve * iCrv,
                      short iOri, CATPointOnEdgeCurve * iPoec, CATCrvParam * iParm,
                      CATSurface * iRefSurf);

      short TryToConvertToPCurveOn(CATSurface * iRefSurf); // returns 1 if ok

      // Tangent computations, return 1 ik ok
      short ComputeUVTangent();
      short ComputeXYZTangent(CATMathPlane * iProjectPlane);

      void DumpObj(CATCGMOutput& s) const;
    };

    // Step for dynamic allocation
    enum { _AllocStep = 10 };

    // friend global function used by quick sort to compare two HEdges
    friend int CATCGMRadSortComparator(const void* iEl1, const void* iEl2);

	// friend global function used by quick sort to compare two HEdges
	// duplique pour les besoins d'une correction versionnee aov wk26 2006
    friend int CATCGMRadSortComparator2(const void* iEl1, const void* iEl2);

    //ST5 Wk17-2012: New harmonization for Small angles and curvatures
    friend int CATCGMRadSortComparator3(const void* iEl1, const void* iEl2);

    // Cleaning allocated data upon destruction or exception raised
    void Clean();

    // Find an edge from its id
    int GetEdgIndex(int iId, short iThrowIfNotFound = 0);

    // Adds an HEdg at the end of the list, returns its id
    int AddHEdg(CATEdge  *iEdge, CATCurve * iCrv, short iOri, CATPointOnEdgeCurve * iPoec,
                CATCrvParam * iParm, int * iId);

    // Computes tangents to all edges, towards the inside of the edge
    // If UV tangents are unavailable, due to lack of pcurves, XYZ tangents
    // are projected onto a tangent plane, that must be computed
    // ALl these methods return 1 if everything is ok, zero otherwise
    short ComputeUVTangents();
    short ComputeTangentPlane();
    short ComputeXYZTangents();

    // Computes all angles with respect to first edge tangent
    void ComputeAngles();

    // Merge equivalence classes of tangent edges
    void MergeClasses(int iEater, int iEated);

    // Handle flag saying there are at least two non-separable edges
    void SetNonSeparableEdgesExistenceFlag(short iFlag);

    // Compute algebraic cuvatures on non separable edges
    void ComputeCurvatures();

    //------------------------------------------------------------------
    // Internal data
    CATSoftwareConfiguration * _Config;
    CATSurface * _Surf;
    int          _NbEdges;
    int          _NbAllocatedEdges;
    short        _CCW;
    HEdg       * _Edg;
    short        _AlreadySorted;
    short        _AllIdsAreImplicit;

    CATMathPlane * _TgtPlane; // computed only if UV tangent unavailable
    short          _NonSeparableEdgesExist;
    short          _CheckTangency;
};

//------------------------------------------------------------------
//                       INLINE
//------------------------------------------------------------------
INLINE int CATRadialSortOperator::GetNumberOfEdges()
{
  return _NbEdges;
}
//
INLINE short CATRadialSortOperator::GetCCW()
{
  return _CCW;
}
  
#endif 
