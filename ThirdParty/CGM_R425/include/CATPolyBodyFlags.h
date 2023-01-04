// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyFlags.h
//
//===================================================================
// September 2010  Creation: NDO
// July      2014  Modification JXO: Geometric validity flags
// November  2018  Modification JXO: IntersectionsFlag and checker version
// December  2020  Modification JXO: HasCellErrors flag
//===================================================================
#ifndef CATPolyBodyFlags_H
#define CATPolyBodyFlags_H

#include "PolySupports.h"
#include "CATBoolean.h"


class ExportedByPolySupports CATPolyBodyFlags
{

public:

  CATPolyBodyFlags () : _Flags (0) {}
  ~CATPolyBodyFlags () {}

public:

  /**
   * Various flags.
   */
  enum Flag
  {
    /** Fatal flag. */                                                                eFatal = -2,
    /** Unset flag. */                                                                eUnset = -1,
    /** Set to <tt>TRUE</tt>. */                                                      eFalse = 0,
    /** Set to <tt>FALSE</tt>. */                                                     eTrue = 1
  };

public:

  void SetValidityFlag (Flag iValue);
  void SetGeoValidityFlag (Flag iValue);
  void SetTopologyWatertightness (Flag iValue);
  void SetGeometryWatertightness (Flag iValue);
  void SetSelfIntersectionsFlag(Flag iValue);
  /**
   * Sets the version number of the checker used to set all the validity flags.
   * This version number should be 0 < n < 128
   */
  void SetCheckerVersion(int iValue);

public:

  Flag GetValidityFlag () const;
  Flag GetGeoValidityFlag () const;
  Flag GetTopologyWatertightness () const;
  Flag GetGeometryWatertightness () const;
  Flag GetSelfIntersectionsFlag() const;
  /**
   * Gets the version number of the checker used to set all the validity flags.
   */
  int GetCheckerVersion();

public:

  /**
   * Clears the flag for the domains of all dimensions (0, 1, 2 or 3).
   */
  void UnsetDomainDimensions ();

  /**
   * Sets the flag for the domains of dimension 0, 1, 2 or 3.
   */
  void SetDomainDimension (unsigned int dim, Flag iValue);

  /**
   * Gets the flag for the domains of dimension 0, 1, 2 or 3.
   */
  Flag GetDomainDimension (unsigned int dim) const;

public:

  /** 
   * Sets the reserved bit A.  By default the bit is cleared.
   * @param iValue
   *   Sets the bit if <tt>TRUE</tt> and clears it if <tt>FALSE</tt>.
   */
  inline void SetReservedBitA (CATBoolean iValue);

  /** 
   * Gets the reserved bit A.
   * @return
   *   <ul>
   *     <li> <tt>TRUE</tt> if the bit is set.
   *     <li> <tt>FALSE</tt> if the bit is cleared.
   *   </ul>
   */
  inline CATBoolean GetReservedBitA () const;

  /**
   * Sets the reserved bit B.  By default the bit is cleared.
   * @param iValue
   *   Sets the bit if <tt>TRUE</tt> and clears it if <tt>FALSE</tt>.
   */
  inline void SetReservedBitB(CATBoolean iValue);

  /**
   * Gets the reserved bit B.
   * @return
   *   <ul>
   *     <li> <tt>TRUE</tt> if the bit is set.
   *     <li> <tt>FALSE</tt> if the bit is cleared.
   *   </ul>
   */
  inline CATBoolean GetReservedBitB() const;

  /**
   * Set wether the diagnosis has cell errors or not.
   */
  void SetHasCellErrors(CATBoolean iValue);

  /**
   * Gets wether the diagnosis has cell errors or not.
   */
  CATBoolean GetHasCellErrors() const;

public:

  /**
   * Reserved for  CATPolyBody streamer.
   */
  void SetFlags (unsigned int flags) {_Flags = flags;}

  /**
   * Reserved for  CATPolyBody streamer.
   */
  unsigned int GetFlags () const {return _Flags;}

protected:

#ifndef _SUNOS_SOURCE
  mutable unsigned int _Flags;  // Flags for various purposes.
#else
  unsigned int _Flags;  // Flags for various purposes.  (Dumb compiler.)
#endif

protected:

  /**
   * Masks for various flags.
   * Do not change the definition of the various bits without also editing
   * CATPolyBodyDefaultStreamer.
   */
  enum Masks
  {
    /** Bits 0 & 1 reserved for validity. */                  MaskValidity        = 0x00000003,
    /** Bits 2, 3 & 4 reserved for watertightness. */         MaskWatertight      = 0x0000001C,
    /** Bits 5 & 6 reserved for geometric validity. */        MaskGeoValidity     = 0x00000060,
    /** Does body have cell errors? */                        MaskHasCellErrors   = 0x00000080,
    /** Bits 8, 9, 10 & 11 reserved for domains. */           MaskDomains         = 0x00000F00,
    /** Bit 8 reserved for domains of Dimension 0. */         MaskDomain0         = 0x00000100,
    /** Bit 9 reserved for domains of Dimension 1. */         MaskDomain1         = 0x00000200,
    /** Bit 10 reserved for domains of Dimension 2. */        MaskDomain2         = 0x00000400,
    /** Bit 11 reserved for domains of Dimension 3. */        MaskDomain3         = 0x00000800,
    /** Bit 12 & 13 for self intersections. */                MaskIntersections   = 0x00003000,
    /** Bit 16: Reserved Bit A. */                            MaskBitA            = 0x00010000,
    /** Bit 17: Reserved Bit B. */                            MaskBitB            = 0x00020000,
    /** Bit 18, 19, 20, 21, 22, 23, 24 for checker version */ CheckerVersion      = 0x01FC0000
  };

  /**
   * Offset to first bit.
   */
  enum Offset
  {
    /** Bit 0. */    OffsetValidity       = 0,
    /** Bit 2. */    OffsetWatertight     = 2,
    /** Bit 5. */    OffsetGeoValidity    = 5,
    /** Bit 8. */    OffsetDomains        = 8,
    /** Bit 12. */   OffsetIntersections  = 12,
    /** Bit 18. */   OffsetCheckerVersion = 18,
    /** USE NEXT. */ FreeBits             = 25
  };

};


inline void CATPolyBodyFlags::SetReservedBitA (CATBoolean iValue)
{
  if (iValue)
    _Flags |= MaskBitA;
  else
    _Flags &= ~MaskBitA;
}


inline CATBoolean CATPolyBodyFlags::GetReservedBitA () const
{
  return (_Flags & MaskBitA)?TRUE:FALSE;
}


inline void CATPolyBodyFlags::SetReservedBitB (CATBoolean iValue)
{
  if (iValue)
    _Flags |= MaskBitB;
  else
    _Flags &= ~MaskBitB;
}


inline CATBoolean CATPolyBodyFlags::GetReservedBitB () const
{
  return (_Flags & MaskBitB)?TRUE:FALSE;
}


#endif // !CATPolyBodyFlags_H
