#ifndef CATEdgeCurveIterator_H
#define CATEdgeCurveIterator_H

// COPYRIGHT DASSAULT SYSTEMES  1998
/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 
#include "CATIAV5Level.h"
//#if defined ( CATIAV5R11 )
#include "CATCGMVirtual.h"
//#endif  

#include "YP00IMPL.h"    
class CATCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATPCurve;
class CATCGMOutput;
#include "CATGeometryType.h"
#include "CATDataType.h"

//#ifdef CATIAV5R11
// Optimization pointer data which can be used as a sub-letter mechanism to perform future implementation modification
// without modifying the header file
class	CATEdgeCurveIteratorOpt;
//#endif

/**
 * Class defining the iterator to scan the curves of a CATEdgeCurve.
 * <br>By default, a given curve is retrieved as many times as it appears in the
 * tree structure below the root CATEdgeCurve.
 * Stuttering shared curves can be turned off upon request by the @href CATEdgeCurveIterator#SetRepetitions method. 
 */
//#if defined ( CATIAV5R11 )
class ExportedByYP00IMPL CATEdgeCurveIterator : public CATCGMVirtual
/*
#else 
class ExportedByYP00IMPL CATEdgeCurveIterator
#endif  
*/
{
  public :
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Constructs a CATEdgeCurveIterator.
 * @param iEdgeCurve
 * The pointer to the CATEdgeCurve to be scanned.
 */
  CATEdgeCurveIterator(const CATEdgeCurve* iEdgeCurve);

/**
 * Assignment operator. An unfinished scan will not be memorized in the new iterator.
 */
  CATEdgeCurveIterator& operator=(const CATEdgeCurveIterator&);

/**
 * Copy constructor. An unfinished scan will not be memorized in the new iterator.
 */
  CATEdgeCurveIterator(const CATEdgeCurveIterator&);
  ~CATEdgeCurveIterator();

/**
 * Defines a new CATEdgeCurve to scan.
 * <br> Resets the iterator at the beginning.
 * @param iNewCurve
 * The pointer to the new curve to scan.
 */
  void Set(const CATEdgeCurve* iNewCurve) ;

/**
 * Returns the CATEdgeCurve that is scanned.
 * @return
 * The pointer to the curve to scan.
 */
  const CATEdgeCurve* GetElement() const ;

/**
 * Initializes the iterator to the beginning curve.
 * <br>This allows you to change the target type or any of the scanning specifications.
 */
  void Reset() ;

/**
 * Skips to the next curve of the CATEdgeCurve.
 * <br>If this mehod is called without
 * arguments the first time, it is forbidden to swap to the signature with
 * arguments within the same scanning sequence.
 * @param oOrientation
 * The orientation with respect to the root curve (curve that has been
 * provided to the constructor, or to the <tt>Set</tt> method). 
 * If <tt>NULL</tt>, this information is not retrieved.
 * @param oNbPCurves
 * The actual number of imbedded pcurves: 1 if the current
 * curve is a pcurve itself, and one for each of the imbedded pcurves,
 * whatever their number of occurences.
 * If <tt>NULL</tt>, this information is not retrieved.
 * @param oNbSurfaces
 * The number of underlying surfaces of the imbedded pcurves.
 * For example, the edge curve reprensenting the edge of the closure of a cylinder
 * yields to two pcurves and one surface. A 3d curve yields zero pcurve and zero surface.
 * If <tt>NULL</tt>, this information is not retrieved.
 * @return
 * The pointer to the next curve, <tt>NULL</tt> when the scan is over.
 */
  CATCurve * Next(short * oOrientation=0,
                  CATLONG32 * oNbPCurves=0, CATLONG32 * oNbSurfaces=0) ;

  //------------------------------------------------------------------
  // Scanning options can be specified by the following methods. Reset() is
  // required prior to changing any of the options, unless the iterator has
  // just been created and not yet used, or Set method has just been called.

  // Specific PCurves and / or surfaces can be specified. Setting mandatory
  // pcurves (resp. surfaces) and same number as maximum number of pcurves
  // (resp. surfaces) enables to filter out any curve that includes an
  // unwanted additional pcurve (resp. lies on an additional surface).
  // For instance CATEdgeCurve::NextOnSupport is equivalent to Next() after
  // setting one mandatory surface and setting target type to CATPCurveType.

  // Default specs are: scan only leaves, that is, force remaining depth to 0,
  // enable stuttering, and all other specs are unset. Use BackToDefault()
  // to cancel all specs, or use individual methods with "-1" to cancel a
  // given min or max, CATCurveType to cancel a target type, and omit pointers
  // in SetMandatory methods to cancel mandatory objects.

  // Some combinations of specs are obviously incompatible. In such cases,
  // Next() will return zero upon first call.

  // Hereafter is a list of incompatible specs :
  // * Targetting EdgeCurves or subtypes while scanning only leaves
  // * Setting minimum number of pcurves or surfaces > 0 and targetting 3dcurves
  // * Setting minimum number of pcurves or surfaces > 1 and targetting pcurves
  //   or 3dcurves
  // * Setting a min number of pcurves greater than the max number of surfaces
  // * Setting a max number of pcurves or surfaces strictly inferior to the
  //   actual number of mandatory objects for same type
  //------------------------------------------------------------------
 /**
  * Only scans a defined type of curves. 
  * @param iTarget
  * The geometry type that is scanned, like CATPCurveType, or CATIntCurveType.
  * For instance, use CATEdgeCurveType to skip the leaves in the tree.
  * Type <tt>0</tt> means no type filter at all.
  */
  void SetTargetType(CATGeometricType iTarget=0);
/** 
  * Only scans the leaf curves.
  * @param iOnlyLeaves
  * <tt>1</tt> to only scan the leaf curves, <tt>0</tt> otherwise. 
  * Note that the <tt>1</tt> value in this option is incompatible with the <tt>CATEdgeCurveType</tt>
  * value in the @href CATEdgeCurveIterator#SetTargetType method.
  */
  void SetLeafScan(short iOnlyLeaves = 1);
  /**
  * Defines whether a curve that appears several times in the root must be
  * output only one time.
  * @param iStutter
  * <tt>1</tt> if it is output as many times as it appears (default value), </tt>0</tt> otherwise.
  */
  void SetRepetitions(short iStutter = 1); 







  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/** @nodoc */
  void MakeSimplifiedPoec(CATPointOnEdgeCurve * iBigPoec,
                          CATPointOnEdgeCurve *& oSmallPoec,
                          CATEdgeCurve * iTargetCurve = 0) const;

/** @nodoc */
  void SetNbPCurves(CATLONG32 iMinNbPCurves=-1, CATLONG32 iMaxNbPCurves=-1);
  /** @nodoc */
  void SetNbSurfaces(CATLONG32 iMinNbSurf=-1, CATLONG32 iMaxNbSurf=-1);

  // the short value returned by append methods is zero if the object was
  // already in the mandatory list, otherwise it is internal number (>0) of
  // the mandatory object, this number can be input to NextPCurveOn.
  // Internal object numbering can be explored by methods GetSurface and
  // GetSurfaceNumber for surfaces, GetPCurve and GetPCurveNumber for PCurves

  // Remove methods return zero if the object was not in the list, otherwise 1.
  /** @nodoc */
  short AppendMandatoryPCurve(CATPCurve * iPCrv);
  /** @nodoc */
  short RemoveMandatoryPCurve(CATPCurve * iPCrv);
  /** @nodoc */
  void CancelAllMandatoryPCurves();
  /** @nodoc */
  short GetPCurveNumber(CATPCurve * iPCrv);
  /** @nodoc */
  CATPCurve * GetPCurve(short iNum);
/** @nodoc */
  short AppendMandatorySurface(CATSurface * iSurf);
  /** @nodoc */
  short RemoveMandatorySurface(CATSurface * iSurf);
  /** @nodoc */
  void CancelAllMandatorySurfaces();
  /** @nodoc */
  short GetSurfaceNumber(CATSurface * iSurf);
  /** @nodoc */
  CATSurface * GetSurface(short iNum);

  /** @nodoc */
  void BackToDefault();

  //------------------------------------------------------------------
  // If a mandatory surface has been set, the pcurves lying of this surface
  // and imbedded in the current curve can be retrieved by the following
  // "sub-scanning" method (returns zero when sub-scanning finished).
  // Surface number is the number returned by AppendMandatorySurface method.
  // Going back to the main scanning method (Next) cancels internal scanning
  // of pcurves if it had been started and left unfinished.
  // LocalReset() enables to re-scan the pcurves in the same current edge-crv

  // If additional information is required on closed surfaces (like position
  // and orientation versus closure for each pcurve), please use the
  // CATPositionVsSurfaceBorder::GetClosureNumber(..) method exported by
  // CATGeometricOperators framework. 
  //------------------------------------------------------------------
 /** @nodoc */
  CATPCurve * NextPCurveOn(short iSurfaceNumber, short * oOriVersusRoot=0);
  /** @nodoc */
  void LocalReset();

  //------------------------------------------------------------------
  /** @nodoc */
  struct CrvRep {
    const CATCurve *   _Crv;         // associated curve (edge-crv, pcrv,3dcrv)
    CATLONG32               _SubTreeSize; // number of crvs involved, including self
    CATLONG32               _FatherNodeNumber; // zero if root (number = index + 1)
    CATLONG32               _NbSons;      // number of curves one step beneath
    const CATSurface * _Surf;        // underlying surface, only if crv=pcurve
    CATLONG32               _NbOcc;       // total number of nodes sharing _Crv
    short              _GlobalOri;   // orientation versus root (=first) curve
    short              _ScanMet;     // _Crv already met within current scan
    short              _SubScanMet;  // pcrv already met within current subscan
  };

  /** @nodoc */
  enum {_StaticTreeSize = 12, _StaticStackSize = 6, _StaticMandatorySize = 4,
    _AllocationStep = 20};

  //------------------------------------------------------------------

  private :
    
    // shared code between copy-const and operator =
    void InitFrom(const CATEdgeCurveIterator & iToCopy);

    // deletes allocated data
    void FreeMemory();

    // builds the tree, if not yet done. Root curve is read in _Stack[0]
    void UpdateTree();

    // appends a CrvRep and returns its index within _Tree
    // relative orientation is 0 if it is unknown or if iCrv = root
    CATLONG32 AppendNode(const CATCurve * iCrv, short iOriVersusFather=0,
      CATLONG32 iFatherNodeNumber = 0);

    // expands the subtree from a given CrvRep, edge-curve may be given
    // if any, to save time
    void Expand(CATLONG32 iMasterNodeIndex, const CATEdgeCurve * iMasterECrv=0);

    // applies the filter to current node and optimizes next possible node
    short MatchNode(CATLONG32 & oNextNodeNumber);

    // updates _CurNodeNbPCurves and _CurNodeNbSurfaces
    void UpdateNbPCurvesForCurNode();
    void UpdateNbSurfacesForCurNode();

    // utility: handles a list of void* without repetitions
    void AppendToDummyPack(void * iObj, void **& ioPack,
                           CATLONG32 & ioSize, CATLONG32 & ioMaxSize);

//#ifdef CATIAV5R11
		// utility : appends a curve to the "already met" list, handled in basic mode
		void AddCurveToAlreadyMetList(CATCurve * iCrv);
//#endif

    // scanning main methods
    CATCurve * NextFromTree();
    CATCurve * NextFromStack();

    // dump (for debug only)
    void Dump(CATCGMOutput & s);
    void DumpTree(CATCGMOutput & s);
    void DumpStack(CATCGMOutput & s);
    void DumpNode(CATCGMOutput & s, CATLONG32 iNodeIndex);

    //------------------------------------------------------------------
    // Data
    //------------------------------------------------------------------

    // complete tree generated if needed : non basic scanning mode, or
    // additional info required by first Next() 
    // the tree is in "depth first" order

    // _Tree = _StaticTree, unless dynamic allocation has been done
    CrvRep *  _Tree;
    CrvRep    _StaticTree[_StaticTreeSize];
    CATLONG32      _TreeSize;
    CATLONG32      _TreeAllocatedSize;
    short     _DynamicTree;

    short     _TreeUpdated;

    // stack of last scanned curve, dynamically updated at each Next(),
    // processed in basic scanning mode only (see below), for time
    // saving reasons. Current depth (_CurDepth) is the index of last
    // curve returned by Next() within _Stack
    CATCurve  ** _Stack;
    CATCurve   * _StaticStack[_StaticStackSize];
    CATLONG32         _StackAllocatedSize;
    short        _DynamicStack;

    // ---------------------------------------------------
    // scanning mode (pairs of "CATLONG32" are [min, then max])

    // if _BasicScan = 1, scanning operates _Stack[], and _Tree
    // is not computed. Only leaf scan is allowed then
		// If Stuttering is disabled, a list of "already met" leaf-curves will be generated
    short            _BasicScan;

//#ifdef CATIAV5R11
		CATCurve      ** _AlreadyMetLeaves;
		CATLONG32             _AlreadyMetLeavesSize;
		CATLONG32             _AlreadyMetLeavesAllocatedSize;
//#endif

    CATGeometricType _TargetType; // 0 if unset (0 <=> CATCurveType)
    short            _Stutter;    // 0 if Next() never scans twice the same crv
    short            _LeafScan;
    CATLONG32             _TargetNbPCurves[2];
    CATLONG32             _TargetNbSurfaces[2];

    CATLONG32             _NbMandatoryPCurves;
    CATLONG32             _MandatoryPCrvAllocatedSize;
    CATPCurve *      _StaticMandatoryPCrv[_StaticMandatorySize];
    CATPCurve **     _MandatoryPCrv;

    CATLONG32             _NbMandatorySurfaces;
    CATLONG32             _MandatorySurfAllocatedSize;
    CATSurface *     _StaticMandatorySurf[_StaticMandatorySize];
    CATSurface **    _MandatorySurf;

    // ---------------------------------------------------
    // current scanning status

    // _Tree node number returned by last scanning and sub-scanning methods
    // called since construction or reset, otherwise 0 (number = 1 + index)
    CATLONG32      _CurNodeNumber;
    CATLONG32      _CurSubNodeNumber;

    // numbers of pcurves / surfaces in current node subtree, -1 if unknown
    CATLONG32      _CurNodeNbPCurves;
    CATLONG32      _CurNodeNbSurfaces;

    // current depth in _Stack, to be used in basic mode
    CATLONG32      _CurDepth;
//#ifdef CATIAV5R11
// Optimization pointer data which can be used as a sub-letter mechanism to perform future implementation modification
// without modifying the header file
		CATEdgeCurveIteratorOpt * _Opt;
//#endif
};

#endif
