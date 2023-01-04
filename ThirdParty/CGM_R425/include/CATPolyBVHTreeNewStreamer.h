// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//=================================================================================================
//
// CATPolyBVHTreeNewStreamer.h
//
//=================================================================================================
//
// Usage notes: Base class for streaming a BVH Tree, provides minimal
// functionality. Users should derive it and implement the methods
// according to their needs
//=================================================================================================
// June 2013 Creation: AV7
//=================================================================================================
#ifndef CATPolyBVHTreeNewStreamer_h
#define CATPolyBVHTreeNewStreamer_h

// ExportedBy
#include "PolyBodyBVH.h"

// PolyhedralObjects
#include "CATPolyBVStreamer.h"

// PolyhedralMathematics
class CATBVHTree;
class CATBVHAttribute;
class CATBVHNodeConst;

// CATMathStream
class CATMathStream;

class ExportedByPolyBodyBVH CATPolyBVHTreeNewStreamer
{
public:

  /**
  * Descent mode during stream.
  * Full  : All nodes are traversed and expanded. If tree contains smart nodes, 
  *         they will be expanded, and their expansion streamed.
  * AsIs  : All nodes are traversed and streamed as is. If tree contains smart nodes, 
  *         their potential (prior to stream) children will be streamed, but no more.
  * Smart : Try to stream smart nodes whenever possible, with a smaller stream size. 
  *         Do not descent into smart nodes, even if they have children.
  *         NOTE: Traversal will probably take longer after unstream.
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
  CATPolyBVHTreeNewStreamer(CATMathStream & oStream);
  
  virtual ~CATPolyBVHTreeNewStreamer();

  /**
   * Stream a BVH Tree.
   * @return
   *    S_OK    : Everything went OK.
   *    E_FAIL  : Something went wrong.
   */
  virtual HRESULT Stream(CATBVHTree & Tree);


protected:
  
  //-----------------------------------------------------------------------------------------------
  // METHODS
  //-----------------------------------------------------------------------------------------------

  /**
   * Stream the data associated with a node.
   * NOTE : Default implementation considering basic CATBVHNode is provided
   * @return
   *    S_OK    : Everything went OK.
   */
  virtual HRESULT StreamNode(CATBVHNodeConst  & iNode,
                             CATBoolean       & oContinueDescent) = 0;

  /**
   * Stream the data of an attribute associated with a node
   * @return
   *    S_OK    : Everything went OK.
   */
  virtual HRESULT StreamAttribute(CATBVHAttribute * ipAttribute) = 0;

  /**
   * Implement this method for performing any operation before beginning
   * tree traversal
   */
  virtual HRESULT PreProcessingForTreeTraversal() = 0;

  /**
   * Implement this method for performing any operation after completing
   * tree traversal(like resetting values set using PreProcessingForTreeTraversal()
   */
  virtual HRESULT PostProcessingForTreeTraversal() = 0;

  /**
   * You can overide version before streaming
   */
  void SetVersion(int version);
  
  /**
   * You can overide mode before streaming
   */
  void SetMode(DescentMode mode);

  //-----------------------------------------------------------------------------------------------
  // DATA MEMBERS
  //-----------------------------------------------------------------------------------------------
  
  CATMathStream   & _stream;
  int               _version;
  DescentMode       _mode;

private:

  CATPolyBVHTreeNewStreamer(const CATPolyBVHTreeNewStreamer & iToCopy);
  CATPolyBVHTreeNewStreamer & operator = (const CATPolyBVHTreeNewStreamer & iToAssign);

  HRESULT Descent(CATBVHNodeConst & iNode);

  HRESULT StreamBoundingVolume(CATBVHNodeConst & iNode);

  CATPolyBVStreamer   _bvStreamer;
};

#endif // CATPolyBVHTreeNewStreamer_H

