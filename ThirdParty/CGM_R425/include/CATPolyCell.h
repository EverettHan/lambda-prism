// COPYRIGHT DASSAULT SYSTEMES 2003, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyCell
//
//=============================================================================
// 2014-11-19   NDO: Replaced CATIPolySurface by CATPolyFaceSurface in constructor.
// 2009-11-03   NDO: Revisited implementation, Optimizations (size of CATPolyCell objects.)
// 2006-08-27   BPG: Raise
// 2003-03-20   FDS: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyDart.h"
#include "CATPolyDartLink.h"
#include "CATPolyMacroTopologyFwd.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Poly 
{
  ExportedByPolyMODEL CATPolyBody* NewEditableBody (const CATPolyBody& iPolyBody);
}
#endif


/*
 * Base class for these classes: CATPolyVertex, CATPolyEdge, CATPolyFace and CATPolyVolume.
 * This class is not virtual.  Do not make it virtual.
 */
class ExportedByPolyMODEL CATPolyCell
{

public:

  ~CATPolyCell ();  // DO NOT MAKE THIS CLASS VIRTUAL!

public:

  /** 
   * @return
   *   Returns the dimension of this CATPolyCell:
   *   <dl>
   *     <dt> 0 </dt><dd> for a CATPolyVertex.</dd>
   *     <dt> 1 </dt><dd> for a CATPolyEdge.</dd>
   *     <dt> 2 </dt><dd> for a CATPolyFace.</dd>
   *     <dt> 3 </dt><dd> for a CATPolyVolume.</dd>
   *   </dl>
   */
  int GetDimension () const;

  /**
   * @return
   *   Returns the tag identifying this cell.
   */
  unsigned int GetCellTag () const;

public:

/** @name Reserved (Manual Edition)
    @{ */

  /**
   * Returns the state of the observer.
   */
  inline bool IsObserverSuspended () const;

  /**
   * Suspends the observer that propagates editing events
   * to adjacent and incident cells. The edition of the 
   * adjacent cells must be done manually including 
   * updates of the surface-cell layers from the CATPolyFace.
   */
  inline void SuspendObserver ();

  /**
   * Resumes the observer that propagates editing events
   * to adjacent and incident cells. 
   */
  inline void ResumeObserver ();

/* @} */

protected:

  // The placement variables come first in the definition of the CATPolyCell.  
  // It's reserved memory space for objects (observers.)
  // The overal size of the placement space must be at least equal to the largest size of the 
  // following objects:
  //   o CATPolyVertexPoint (a CATIPolyPointObserver.)
  //   o CATPolyEdgeCurve (a CATIPolyCurveObserver.)
  //   o CATPolyFaceSurface* (a pointer to a CATIPolySurfaceObserver.)
  // *** Do not change order of member variables! ***
  // *** Do not make CATPolyCell virtual! ***
  void* _PlacementPointer;   // Space reserved for a pointer.
  int   _PlacementInteger;   // Space reserved for an integer.

  // Bitfields: see below.
  unsigned int _BitFields;

private:

  // A tag used to identify the cell. It is zero by default and should be set
  // by the body the cell is attached to.
  unsigned int _CellTag;

  // Most CATPolyCell refers to one dart.  If a CATPolyCell refers to more than one dart, then
  // the darts are stored in a link list and the flag for multiple darts is set.
  // The darts from the link list below can be interpreted as:
  //   o CATPolyPseudoManifoldVertex;
  //   o CATPolyManifoldEdge; or,
  //   o Seed darts for face loops.
  union
  {
    CATPolyDart2* _Dart2;
    CATPolyDart3* _Dart3;
    CATPolyDartLink<CATPolyDart2>* _Dart2Link;
    CATPolyDartLink<CATPolyDart3>* _Dart3Link;
    CATPolyBody* _PolyBody;
  } _Darts;

  friend class CATPolyBody;
  friend class CATPolyBodyHelpers;
  friend class CATPolyDartHelpers;
  friend class CATPolyCellOrbit;
  friend class CATPolyCellOrbitIterator;
  friend class CATPolyCellOrbitComputer;
  friend class CATPolyBodyTopologyUnstreamer;
  friend CATPolyBody* Poly::NewEditableBody (const CATPolyBody& iPolyBody);

protected:

  /**
   * Bitfields.
   * The first three bits are reserved for the cell type:
   *   * Vertex:                                                       0 0 1   = 0x01
   *   * Edge:                                                         0 1 0   = 0x02
   *   * Face with positive orientation w.r.t. CATPolyBody:            1 0 0   = 0x04
   *   * Face with no orientation w.r.t. CATPolyBody:                  1 0 1   = 0x05
   *   * Face with negative orientation w.r.t. CATPolyBody:            1 1 0   = 0x06
   *   * Volume:                                                       1 1 1   = 0x07
   *
   * The cell dirty-bit is set when the cell refers to multiple darts from the same orbit.
   * 
   * Relative orientation:
   *   Four bits are reserved to specify the orientation of a cell C of dimension N w.r.t.
   *   the cells of dimension N+1 if there are at most two, let say A1 and A2.
   *   These bits enable the definition of the relative orientation of the two pairs: (C, A1) and (C, A2).
   *   (Relative orientation of C w.r.t. A1 and relative orientation of C w.r.t. A2.)
   *   The two pairs are distinguished by the values of the cell tags for A1 and A2;
   *   Let A1 be the N+1 cell with the smallest cell tag.
   *   The first two-bits are reserved to define the relative orientation of the (C, A1) pair.
   *   The second two-bits are reserved to define the relative orientation of the (C, A2) pair.
   *   Given the two-bits, the relative orientation is defined as follows:
   *     * 00: (C, Ai) has unset relative orientation
   *     * 01: (C, Ai) has positive relative orientation
   *     * 10: (C, Ai) has negative relative orientation
   *     * 11: (C, Ai) has null relative orientation
   *   Any change of the incidence of the cells require an update of the relative orientation bits.
   * 
   *   The relative orientation of an edge with at most two incident faces can be defined in this manner.
   *   And similarly, for the relative orientation of a face with at most two incident volumes.
   */
  enum BitFields
  {
    /* Cell type */              Bit0                 = 0x0001,  // Bit 0
    /* Cell type */              Bit1                 = 0x0002,  // Bit 1
    /* Cell type */              Bit2                 = 0x0004,  // Bit 2
    /* Mask for cell type */     MaskCells            = 0x0007,  // Bits 0, 1 & 2
    /* Map to Dart2 */           BitDart2             = 0x0008,  // Bit 3
    /* Map to Dart3 */           BitDart3             = 0x0010,  // Bit 4
    /* Map to Dart2Link */       BitDart2Link         = 0x0020,  // Bit 5
    /* Map to Dart3Link */       BitDart3Link         = 0x0040,  // Bit 6
    /* Map to Body */            BitBody              = 0x0080,  // Bit 7
    /* Mask for darts & body */  MaskDarts            = 0x00F8,  // Bits 3, 4, 5, 6 & 7
    /* Observer suspended */     BitObserverSuspended = 0x0100,  // Bit 8
    /* Cell dirty */             BitCellDirty         = 0x0200,  // Bit 9
    /* Relative orientation. */  BitOrientation00     = 0x0400,  // Bit 10
    /* Relative orientation. */  BitOrientation01     = 0x0800,  // Bit 11
    /* Relative orientation. */  BitOrientation10     = 0x1000,  // Bit 12
    /* Relative orientation.*/   BitOrientation11     = 0x2000,  // Bit 13
    /* Outer orbit first. */     BitOuterOrbitFirst   = 0x4000   // Bit 14
  };

  enum CellType
  {
    /* Vertex */               Vertex = Bit0,
    /* Edge */                 Edge   = Bit1,
    /* Face */                 Face   = Bit2,  // Face without relative orientation w.r.t. CATPolyBody by default.
    /* Volume */               Volume = Bit0 | Bit1 | Bit2
  };

  /**
    * Relative orientation of a cell w.r.t. incident cell of dimension K+1.
    * By default, the relative orientation is unset.
    */
  enum RelativeCellOrientation
  {
    /* Positive orientation */   PositiveRelativeOrientation0  = BitOrientation00,
    /* Negative orientation */   NegativeRelativeOrientation0  = BitOrientation01,
    /* Null orientation */       NullRelativeOrientation0      = BitOrientation00 | BitOrientation01,
    /* Positive orientation */   PositiveRelativeOrientation1  = BitOrientation10,
    /* Negative orientation */   NegativeRelativeOrientation1  = BitOrientation11,
    /* Null orientation */       NullRelativeOrientation1      = BitOrientation10 | BitOrientation11,
  };

  // For derived classes.
  CATPolyCell (CellType iCellType, unsigned int iTag = 0);

  template<class DART>
  CATPolyCell (CellType iCellType, unsigned int iTag, DART* iFirstDart);

  inline bool IsVertex () const;
  inline bool IsEdge () const;
  inline bool IsFace () const;
  inline bool IsVolume () const;

public:

/** @name Internal usage only
    @{ */

  /**
   * Adds a new orbit to the cell.
   * @param prepend
   * By default the new orbit is prepended to the list of orbits.
   * If set to false, the orbit is appended to the list of orbits.
   */
  template<class DART>
  HRESULT AddOrbit (DART& iDart, bool prepend = true);

  // Removes an orbit from the cell.
  template<class DART>
  HRESULT RemoveOrbit (DART& iDart);

  /**
   * Returns true if the cell refers to at least one or several orbits.
   * It must refer to at least to one dart of the specified type.
   */
  template<class DART>
  inline bool HasOrbits () const;

  template<class DART>
  inline bool HasMultipleOrbits () const;

  /**
   * Returns the number of orbits:
   *   * Pseudo-manifold vertices
   *   * Manifold edges
   *   * Face loops
   *   * Volume shells
   */
  template<class DART>
  inline unsigned int GetNbOrbits () const;

  inline unsigned int GetDimensionOfDarts () const;

  /**
   * Sets the cell dirty meaning that there may be multiple dart references to the cell orbits.
   */
  inline void SetDirty ();

  /**
   * Clears the dirty flag of the cell.
   */
  inline void UnsetDirty ();

  /**
   * Returns true if the cell refers to a CATPolyBody instead of darts.
   * Returns true also if the set of darts referred by the cell is not the minimal set.
   * (A non-minimal set may refer to too many darts or equivalent darts.)
   */
  inline bool IsDirty () const;

  /**
   * Clears a dirty cell by removing all its darts or reference to a CATPolyBody.
   */
  template<class DART>
  void Clear ();

  // Returns the parent CATPolyBody, if this link is available (instead of darts.)
  inline CATPolyBody* GetPolyBody ();
  inline void SetPolyBody (CATPolyBody* iPolyBody);

  /**
   * Returns true if the cell has a reference to the CATPolyBody instead of darts.
   */
  inline bool HasBody () const;

  enum RelativeOrientation
  {
    /* Unset */      UnsetOrientation    = 2,
    /* Positive */   PositiveOrientation = 1,
    /* Negative */   NegativeOrientation = -1,
    /* Null */       NullOrientation     = 0,
  };

/** @} */

public:

/** @name Casting methods
    @{ */

  // Use CATPolyVertex::Cast ().
  CATPolyVertex* CastToVertex ();
  const CATPolyVertex* CastToVertex () const;

  // Use CATPolyEdge::Cast ().
  CATPolyEdge* CastToEdge ();
  const CATPolyEdge* CastToEdge () const;

  // Use CATPolyFace::Cast ().
  CATPolyFace* CastToFace ();
  const CATPolyFace* CastToFace () const;

  // Use CATPolyVolume::Cast ().
  CATPolyVolume* CastToVolume ();
  const CATPolyVolume* CastToVolume () const;

/* @} */

protected:

  // Return the very first dart stored in the cell.
  template<class DART>
  inline DART* GetVeryFirstDart () const;

  /**
   * Sets the relative orientation (positive, negative or null) of this cell w.r.t. the cell of dimension K+1.
   * The method can distinguish up to two cells depending on the value of their tags.
   */
  inline void SetRelativeOrientation (RelativeOrientation iOrientation, bool iCellWithSmallestTag = true);

  /**
   * Gets the relative orientation (positive, negative or null) of this cell w.r.t. the cell of dimension K+1.
   */
  inline RelativeOrientation GetRelativeOrientation (bool iCellWithSmallestTag = true) const;

private:

  inline void SetCellTag (unsigned int tag);  // Reserved for CATPolyBodyTopologyUnstreamer.

  // Set the very first dart stored in the cell.
  template<class DART>
  inline void SetVeryFirstDart (DART* iDart);

  template<class DART>
  inline bool HasDart () const;

  template<class DART>
  inline void SetDart (DART* d);

  template<class DART>
  inline void SetDartLink (CATPolyDartLink<DART>* dl);

  template<class DART>
  inline DART* GetDart () const;

  template<class DART>
  inline CATPolyDartLink<DART>* GetDartLink () const;

  template<class DART>
  unsigned int GetNbDartLinks () const;

  /**
   * Records the outer status of the first orbit of a cell.
   * If the first orbit is declared as outer, then all others are inner orbits.
   */
  void SetOuterOrbitFirst (bool b);

  /**
   * Returns true if the first orbit from a cell is declared as the outer orbit.
   * It returns false if it is unknown.
   */
  bool IsOuterOrbitFirst () const;

  static bool WithVolumes (const CATPolyBody* B);
};

inline bool CATPolyCell::IsVertex () const
{
  return (MaskCells & _BitFields) == 0x01;
}

inline bool CATPolyCell::IsEdge () const
{
  return (MaskCells & _BitFields) == 0x02;
}

inline bool CATPolyCell::IsFace () const
{
  return (MaskCells & _BitFields) >= 0x04;
}

inline bool CATPolyCell::IsVolume () const
{
  return (MaskCells & _BitFields) == 0x07;
}

template<>
inline bool CATPolyCell::HasDart<CATPolyDart2> () const
{
  return BitDart2 & _BitFields ? true : false;
}

template<>
inline bool CATPolyCell::HasDart<CATPolyDart3> () const
{
  return BitDart3 & _BitFields ? true : false;
}

template<>
inline bool CATPolyCell::HasMultipleOrbits<CATPolyDart2> () const
{
  return BitDart2Link & _BitFields ? true : false;
}

template<>
inline bool CATPolyCell::HasMultipleOrbits<CATPolyDart3> () const
{
  return BitDart3Link & _BitFields ? true : false;
}

inline bool CATPolyCell::IsDirty () const
{
  return BitCellDirty & _BitFields ? true : false;
}

inline void CATPolyCell::SetDirty ()
{
  _BitFields |= BitCellDirty;
}

inline void CATPolyCell::UnsetDirty ()
{
  _BitFields &= ~BitCellDirty;
}

inline bool CATPolyCell::IsObserverSuspended () const
{
  return BitObserverSuspended & _BitFields ? true : false;
}

inline void CATPolyCell::SuspendObserver ()
{
  _BitFields |= BitObserverSuspended;
}

inline void CATPolyCell::ResumeObserver ()
{
  _BitFields &= ~BitObserverSuspended;
}

inline void CATPolyCell::SetCellTag (unsigned int tag)
{
  _CellTag = tag;
}

template<>
inline void CATPolyCell::SetDart<CATPolyDart2> (CATPolyDart2* d)
{
  _Darts._Dart2 = d;
  _BitFields &= ~MaskDarts;
  if (d)
    _BitFields |= BitDart2;
}

template<>
inline void CATPolyCell::SetDart<CATPolyDart3> (CATPolyDart3* d)
{
  _Darts._Dart3 = d;
  _BitFields &= ~MaskDarts;
  if (d)
    _BitFields |= BitDart3;
}

template<>
inline void CATPolyCell::SetDartLink<CATPolyDart2> (CATPolyDartLink<CATPolyDart2>* dl)
{
  _Darts._Dart2Link = dl;
  _BitFields &= ~MaskDarts;
  if (dl)
    _BitFields |= BitDart2Link;
}

template<>
inline void CATPolyCell::SetDartLink<CATPolyDart3> (CATPolyDartLink<CATPolyDart3>* dl)
{
  _Darts._Dart3Link = dl;
  _BitFields &= ~MaskDarts;
  if (dl)
    _BitFields |= BitDart3Link;
}

template<>
inline CATPolyDart2* CATPolyCell::GetDart<CATPolyDart2> () const
{
  return BitDart2 & _BitFields ? _Darts._Dart2 : 0;
}

template<>
inline CATPolyDart3* CATPolyCell::GetDart<CATPolyDart3> () const
{
  return BitDart3 & _BitFields ? _Darts._Dart3 : 0;
}

template<>
inline CATPolyDartLink<CATPolyDart2>* CATPolyCell::GetDartLink<CATPolyDart2> () const
{
  return BitDart2Link & _BitFields ? _Darts._Dart2Link : 0;
}

template<>
inline CATPolyDartLink<CATPolyDart3>* CATPolyCell::GetDartLink<CATPolyDart3> () const
{
  return BitDart3Link & _BitFields ? _Darts._Dart3Link : 0;
}

template<>
inline bool CATPolyCell::HasOrbits<CATPolyDart2> () const
{
  return ((BitDart2 | BitDart2Link) & _BitFields) && _Darts._Dart2;
}

template<>
inline bool CATPolyCell::HasOrbits<CATPolyDart3> () const
{
  return ((BitDart3 | BitDart3Link) & _BitFields) && _Darts._Dart3;
}

inline unsigned int CATPolyCell::GetDimensionOfDarts () const
{
  if (HasOrbits<CATPolyDart2> ())
    return 2;
  else if (HasOrbits<CATPolyDart3> ())
    return 3;
  else if (HasBody ())
    return WithVolumes (_Darts._PolyBody) ? 3 : 2;
  else
    return 0;
}

template<>
inline void CATPolyCell::SetVeryFirstDart<CATPolyDart2> (CATPolyDart2* d)
{
  if (HasMultipleOrbits<CATPolyDart2> ())
    _Darts._Dart2Link->SetDart (d);
  else
    SetDart<CATPolyDart2> (d);
}

template<>
inline void CATPolyCell::SetVeryFirstDart<CATPolyDart3> (CATPolyDart3* d)
{
  if (HasMultipleOrbits<CATPolyDart3> ())
    _Darts._Dart3Link->SetDart (d);
  else
    SetDart<CATPolyDart3> (d);
}

template<>
inline CATPolyDart2* CATPolyCell::GetVeryFirstDart<CATPolyDart2> () const
{
  return HasDart<CATPolyDart2> () ? _Darts._Dart2 : HasMultipleOrbits<CATPolyDart2> () ? _Darts._Dart2Link->GetDart () : 0;
}

template<>
inline CATPolyDart3* CATPolyCell::GetVeryFirstDart<CATPolyDart3> () const
{
  return HasDart<CATPolyDart3> () ? _Darts._Dart3 : HasMultipleOrbits<CATPolyDart3> () ? _Darts._Dart3Link->GetDart () : 0;
}

template<class DART>
inline unsigned int CATPolyCell::GetNbOrbits () const
{
  return HasOrbits<DART> () ? (!HasMultipleOrbits<DART> () ? 1 : GetNbDartLinks<DART> ()) : 0;
}

inline bool CATPolyCell::HasBody () const
{
  return BitBody & _BitFields ? true : false;
}

inline CATPolyBody* CATPolyCell::GetPolyBody ()
{
  return HasBody () ? _Darts._PolyBody : 0;
}

inline void CATPolyCell::SetPolyBody (CATPolyBody* iPolyBody)
{
  if (_Darts._PolyBody == 0)  // No dart or body should be associated to the cell.
  {
    _Darts._PolyBody = iPolyBody;
    _BitFields &= ~MaskDarts;
    if (iPolyBody)
      _BitFields |= (BitBody + BitCellDirty);  // Cell refers to a CATPolyBody; it is a dirty cell (no links to darts.)
  }
}

inline void CATPolyCell::SetRelativeOrientation (RelativeOrientation iOrientation, bool iCellWithSmallestTag)
{
  _BitFields &= iCellWithSmallestTag ? ~NullRelativeOrientation0 : ~NullRelativeOrientation1;  // Clear the two bits.
  switch (iOrientation)
  {
  case PositiveOrientation:
    _BitFields |= iCellWithSmallestTag ? PositiveRelativeOrientation0 : PositiveRelativeOrientation1;
    return;
  case NegativeOrientation:
    _BitFields |= iCellWithSmallestTag ? NegativeRelativeOrientation0 : NegativeRelativeOrientation1;
    return;
  case NullOrientation:
    _BitFields |= iCellWithSmallestTag ? NullRelativeOrientation0 : NullRelativeOrientation1;
    return;
  }
}

inline CATPolyCell::RelativeOrientation CATPolyCell::GetRelativeOrientation (bool iCellWithSmallestTag) const
{
  unsigned int mask = iCellWithSmallestTag ? NullRelativeOrientation0 : NullRelativeOrientation1;
  switch (mask & _BitFields)
  {
  case PositiveRelativeOrientation0:
  case PositiveRelativeOrientation1:
    return PositiveOrientation;
  case NegativeRelativeOrientation0:
  case NegativeRelativeOrientation1:
    return NegativeOrientation;
  case NullRelativeOrientation0:
  case NullRelativeOrientation1:
  default:
    return NullOrientation;
  };
}
