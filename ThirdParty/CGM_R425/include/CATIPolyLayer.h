// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyLayer.h
//
//===================================================================
// January 2013  Creation: NDO
//===================================================================
#ifndef CATIPolyLayer_H
#define CATIPolyLayer_H

#include "PolyhedralAttributes.h"

#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATIPolyDoublesLayer;
class CATIPolyFloatsLayer;
class CATIPolySurfaceVertexDataLayer;  // To get rid of.
class CATIPolySupport;
class CATIPolySurfaceDisabler;


/**
 * A layer of data associated to integer indices.
 */
class ExportedByPolyhedralAttributes CATIPolyLayer : public CATPolyRefCounted
{

protected:

  virtual ~CATIPolyLayer () {}

public:

  /**
   * Returns 0 if the two class ID are the same.
   */
  static int CompareClassID (const CLSID& id1, const CLSID& id2);

  /**
   * Returns the class ID identifying the layer.
   */
  virtual const CLSID& GetClassID () const = 0;

public:

  /**
   * Casts as a double data layer.
   */
  virtual CATIPolyDoublesLayer* CastAsDoublesLayer () { return 0; }

  /**
   * Casts as a float data layer.
   */
  virtual CATIPolyFloatsLayer* CastAsFloatsLayer () { return 0; }

  /**
   * Casts as a CATIPolySupport.
   */
  virtual CATIPolySupport* CastAsPolySupport () { return 0; }

  /**
   * To get rid of.
   */
  virtual CATIPolySurfaceVertexDataLayer* CastAsSurfaceVertexDataLayer () { return 0; }

public:

  /**
   * Returns an instance of a CATIPolySurfaceDisabler.
   * A layer may not support all editing operations on a CATIPolySurface.
   * When a specific operation is not supported by the data layer, then a query 
   * made to the disabler for this operation returns true.  
   * The CATIPolySurface should not be edited otherwise the layer may become invalid.
   * @param oDisabler
   *   The output disabler. This instance must be deleted.
   */
  virtual HRESULT GetDisabler (CATIPolySurfaceDisabler*& oDisabler);

};

#endif // !CATIPolyLayer_H
