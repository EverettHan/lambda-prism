// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHTreeStream.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2009 Creation: JXO
//===================================================================
#ifndef CATPolyBVHTreeStream_h
#define CATPolyBVHTreeStream_h

// ExportedBy
#include "PolyBodyBVH.h"

// SpecialAPI
#include "CATDataType.h"
#include "CATBoolean.h"

// BVH
class CATBVHTree;
class CATBVHNodeConst;
class CATPolyBoundingVolume;

// Math
class CATMathStream;


class ExportedByPolyBodyBVH CATPolyBVHTreeStream
{
public:

  /**
  * Descent mode during stream.
  * Full  : All nodes are traversed and expanded. If tree contains smart nodes, they will be expanded, and their expansion streamed.
  *         Not implemented yet.
  * AsIs  : All nodes are traversed and streamed as is. If tree contains smart nodes, their potential (prior to stream) children will
  *         be streamed, but no more.
  *         Not implemented yet.
  * Smart : Try to stream smart nodes whenever possible, with a smaller stream size. Do not descent into smart nodes, even if they have children.
  *         Note that traversal will probably take longer after unstream.
  *         Only mode currently implemented.
  */
  enum DescentMode
  {
    Full = 0,
    AsIs,
    Smart
  };

  /**
   * Constructor and destructor.
   */
  CATPolyBVHTreeStream(CATMathStream & oStream);
  ~CATPolyBVHTreeStream();

  /**
   * Stream a BVH Tree.
   * @return
   *    0: Everything went OK.
   *    Other value: Something went wrong.
   */
  virtual int Stream(CATBVHTree & Tree);


protected:
  /**
   * Derive this method if you want to add any applicative attribute to the node into the stream.
   * Unstream will work only if such attributes are unstreamed as well.
   * @param ocontinuedescent
   *    If FALSE, children are not streamed.
   * @return
   *    0: Everything went OK.
   *    Other: Something went wrong.
   */
  virtual int StreamAttribute(CATBVHNodeConst & iNode, CATMathStream & oStream, CATBoolean & ocontinuedescent)
  {
    return 0;
  }

  /**
   * You can overide version before streaming
   */
  void SetVersion(int version);
  /**
   * You can overide mode before streaming
   */
  void SetMode(DescentMode mode);

private:
  int StreamNode(CATBVHNodeConst & iNode, CATMathStream & oStream, CATBoolean & ocontinuedescent);
  int Descent(CATBVHNodeConst & iNode, CATMathStream & oStream);
  int StreamBoundingVolume(const CATPolyBoundingVolume & BV, CATMathStream & oStream);
  void ManageNodeExpansionBasedOnMode();

private:
  CATMathStream & _Stream;
  CATLONG32       _version;
  DescentMode     _mode;

  // For managing the expansion of smart nodes
  CATBoolean      _smartNodeExpandStatus, 
                  _smartRepNodeExpandStatus;
};

#endif // CATPolyBVHTreeStream_H

