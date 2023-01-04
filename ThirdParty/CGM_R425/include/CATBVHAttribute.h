// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHAttribute
//
//===================================================================
// 2015-04-29   WMN   Adding CATBodyBVHAttribute
// 2009-01-06   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//===================================================================
#ifndef CATBVHAttribute_H
#define CATBVHAttribute_H
#include "BVHObjects.h"

// System
#include "CATBoolean.h"


class CATGeomBVHAttribute; // Casting to a privileged attribute (Any geometric model).
class CATPolyBVHAttribute; // Casting to a privileged attribute (polyhedral model).
class CATBVHVisuAttribute; // Casting to a privileged attribute (visualization model).
class CATTessBVHAttribute; // Casting to a privileged attribute (PGMTessBody model).
class CATBodyBVHAttribute; // Casting to a privileged attribute (CATBody model).
class CATBVHPointCloudVisuAttribute; // Casting to a priviledged attribute (OOCPointCloud in visu model).

/**
 * Base class from which all attributes to a CATBVHNode derive.
 * There will be a set of privileged attributes supported through a set of CastAs methods.
 * (Should we support visitors to visit concrete attribute types? No, not really needed.)
 */
class ExportedByBVHObjects CATBVHAttribute
{

public:

  CATBVHAttribute () {_iFlags=0;}
  virtual ~CATBVHAttribute () {}

public:

  // Casting methods for privileged attributes.

  virtual CATGeomBVHAttribute* CastAsGeomAttribute ();
  virtual const CATGeomBVHAttribute* CastAsGeomAttribute () const;

  virtual CATPolyBVHAttribute* CastAsPolyAttribute ();
  virtual const CATPolyBVHAttribute* CastAsPolyAttribute () const;

  virtual CATBVHVisuAttribute* CastAsVisuAttribute ();
  virtual const CATBVHVisuAttribute* CastAsVisuAttribute () const;

  virtual CATTessBVHAttribute* CastAsTessAttribute ();
  virtual const CATTessBVHAttribute* CastAsTessAttribute () const;

  virtual CATBodyBVHAttribute* CastAsBodyAttribute ();
  virtual const CATBodyBVHAttribute* CastAsBodyAttribute () const;

  virtual CATBVHPointCloudVisuAttribute* CastAsPointCloudVisuAttribute ();
  virtual const CATBVHPointCloudVisuAttribute* CastAsPointCloudVisuAttribute () const;

  /**
   * Possible values for flags.
   * There are 32 "booleans" that can be defined.
   */
  enum FlagType
  {
    CLOSED_STATUS_COMPUTED = 1<<0,
    POLYBODY_CLOSED = 1<<1,
    CELLLAYERS_COMPUTED = 1<<2,
    USE_CANONICAL_INFORMATION = 1<<3,
    ACTIVATION_COMPUTED = 1<<4,
    IS_ACTIVATED = 1<<5,
    POLYBODY_NOCELLS = 1<<6
  };

  /**
   * Test one flag.
   * @return TRUE if the flag is on, false otherwise.
   */
  CATBoolean TestFlag(FlagType flagId) const;

  /**
   * Set one of the flags to TRUE.
   * By default the flags are all set to FALSE.
   */
  void EnableFlag(FlagType flagId);

  /**
   * Set one of the flags to FALSE.
   * By default the flags are all set to FALSE.
   */
  void DisableFlag(FlagType flagId);


  /**
   * Don't use.
   */
  virtual void FlushComputedData();

private:
  int _iFlags; // To store informations on the attribute.
};

#endif
