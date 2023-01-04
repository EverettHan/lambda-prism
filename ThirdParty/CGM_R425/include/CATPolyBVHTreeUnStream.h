// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHTreeUnStream.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2009 Creation: JXO
//===================================================================
#ifndef CATPolyBVHTreeUnStream_h
#define CATPolyBVHTreeUnStream_h

#include "PolyBodyBVH.h"
#include "CATBoolean.h"
#include "CATDataType.h"

#include "CATPolyBVHTreeStreamVersion.h"

// BVH
class CATPolyBoundingVolume;
// New BVH
class CATBVHTree;
class CATBVHNode;

// Math
class CATMathStream;


/**
 * Derive this class to unstream your own tree
 */
class ExportedByPolyBodyBVH CATPolyBVHTreeUnStream
{
public:

  /**
   * Constructor and destructor.
   */
  CATPolyBVHTreeUnStream(CATMathStream & iStream);
  ~CATPolyBVHTreeUnStream();

public:
  CATBVHTree * UnStream();

protected:
  /**
   * Derive this method to unstream your own attribute.
   * If return code is different of 0, children of node won't be unstreamed.
   * (Usefull in case of lazy stream)
   * Type of node
   * 0 is for default   node (CATBVHNode)
   * 1 is for smart     node (CATBVHSmartNode)
   * 2 is for i-smart   node (CATBVHIntermediateSmartNode)
   * 3 is for smart rep node (CATBVHSmartRepNode)
   * @return
   *         0: everything is fine
   *         1: unknown attribute
   *        -1: Big problem in unstream, will stop all other operations
   */
  virtual int UnStreamAttribute(CATBVHNode & iNode, CATMathStream & iStream, int nodetype)
  {
    return 0;
  }
  /**
   * Derive to stop unstream whenever version does not fit your unstream operator.
   */
  virtual CATBoolean CheckVersion(int version){return (version <= CURRENT_BVHTREE_STREAM_VERSION);}
  /**
   * Derive to be warned of what mode is used.
   */
  virtual void SetMode(int mode){}
  /**
   * Derive to create your own nodes.
   */
  virtual CATBVHNode * GetNewCATBVHNode(int nodetype, int nbchildren);

private:
  CATPolyBoundingVolume * UnStreamBoundingVolume(CATMathStream & iStream);
  CATBVHNode * UnStreamBVHNode(CATMathStream & iStream);

private:

  CATMathStream & _Stream;
  CATBVHTree    * _BVHTree;
  CATLONG32       _version;
};

#endif // CATPolyBVHTreeUnStream_H

