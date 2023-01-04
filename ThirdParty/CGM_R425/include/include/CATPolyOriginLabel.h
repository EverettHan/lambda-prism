// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabel.h
//
//===================================================================
// November 2018  Creation: JXO
// April    2019  Modification JXO: added eVRep
//===================================================================
#ifndef CATPolyOriginLabel_H
#define CATPolyOriginLabel_H


namespace Poly
{
 /** @name List different certification levels for the validity of a CATPolyBody
  *
  * CATPolyOriginLabel.h
  * @{ */
  enum OriginLabel
  {
    /** Unset origin. */                                                   eUnset                           = 0x00000000,
    /** Checked by our checker. */                                         eChecker                         = 0x00000001,
    /** Boolean operation. */                                              eBoolean                         = 0x00000010,
    /** Dual contouring (VRep). Needs to be checked. */                    eUnsafeDual                      = 0x00000100,
    /** Dual contouring (VRep). */                                         eDual                            = 0x00000200,
    /** Lattice operator. */                                               eLattice                         = 0x00000400,
    /** Decimation. */                                                     eDecimation                      = 0x00000800,
    /** Remove intersecting slivers */                                     eRISCleaner                      = 0x00001000,
    /** Healing With Overlay */                                            eHWOCleaner                      = 0x00002000,
    /** Import from the outside. */                                        eImport                          = 0x00004000,
    /** V6 tessellation */                                                 eTessellation                    = 0x00008000,
    /** Ribbon from road design */                                         eRibbon                          = 0x00010000,
    /** Fill from road design */                                           eFill                            = 0x00020000
  };
  enum OriginLabelMask
  {
    /** Checked by our checker. */                                         eCheckerMask                     = 0x0000000F,
    /** Boolean operations. */                                             eBooleanMask                     = 0x000000F0,
    /** Others. */                                                         eOthersMask                      = 0xFFFFFF00
  };

};

/** @} */

#endif // !CATPolyOriginLabel_H
