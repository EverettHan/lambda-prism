// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHTreeNewUnstreamer.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2013 Creation: AV7
//===================================================================
#ifndef CATPolyBVHTreeNewUnstreamer_h
#define CATPolyBVHTreeNewUnstreamer_h

// ExportedBy
#include "PolyBodyBVH.h"

// PolyhedralMathematics
class CATBVHNode;
class CATBVHTree;
class CATBVHAttribute;

// CATMathStream
class CATMathStream;

/**
 * Derive this class to unstream your own tree
 */
class ExportedByPolyBodyBVH CATPolyBVHTreeNewUnstreamer
{
public:

  /**
   * Constructor and destructor.
   */
  CATPolyBVHTreeNewUnstreamer(CATMathStream & iStream);
  ~CATPolyBVHTreeNewUnstreamer();

  CATBVHTree * UnStream();

protected:
  
  // Implement method to stream nodes of a particular type
  virtual CATBVHNode * UnStreamBVHNode() = 0;

  // Implement method to stream attributes of a particular type
  virtual CATBVHAttribute * UnstreamAttribute() = 0;
  
  /**
   * Derive to stop unstream whenever version does not fit your unstream operator.
   */
  virtual CATBoolean IsCurVersionValid() const;

  CATMathStream   & _stream;
  CATLONG32         _version;
  CATLONG32         _streamMode;
};

#endif // CATPolyBVHTreeNewUnstreamer_H

