// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyCopier.h
//
//===================================================================
// September 2011  Creation: ZFI
// November 2011   Revisited: NDO
// October 2014   JXO: transformation
//===================================================================
#ifndef CATPolyBodyCopier_H
#define CATPolyBodyCopier_H

#include "PolyBodyTools.h"
#include "CATPolyMeshTypeVisitor.h"
#include "CATIPolyObject.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATIAV5Level.h"

class CATPolyBody;
class CATPolyBodyUnaryObserver;
class CATIPolyBodyFrameLayers;
class CATIPolyMesh;
class CATIPolySurfaceVertexLine;
class CATMapOfPtrToPtr;
class CATMathTransformation;
class CATPolyCell;
class CATPolyBodyCopierObserver;
class CATechExt;

#include "CATUnicodeString.h"


/**
* Operator that makes a copy of a CATPolyBody.
* The new CATPolyBody has the same topology as the input CATPolyBody.
* The copy is editable; the mesh data are copied in classes from PolyhedralObjects.
*/
class ExportedByPolyBodyTools CATPolyBodyCopier
{

public:

  /**
   * Choice of the mesh implementation.
   */
  enum MeshImplementation
  {
    /** CATPolyCompactMeshConst (non-editable mesh, data stored in compact arrays) */ ePolyCompactMeshConst = CATPolyMeshTypeVisitor::ePolyCompactMeshConst,  // TO DO.
    /** CATPolyCompactMesh (editable layers, data stored in compact arrays) */        ePolyCompactMesh = CATPolyMeshTypeVisitor::ePolyCompactMesh,
    /** CATPolyMeshImpl (fully editable) */                                           ePolyMeshImpl = CATPolyMeshTypeVisitor::ePolyMeshImpl
  };

public:

  /**
  * Construction of CATPolyBodyCopier with the choice of a CATPolyMeshImpl as the default mesh implementation.
  */
  CATPolyBodyCopier (const MeshImplementation iMeshImplementation = ePolyMeshImpl);

  ~CATPolyBodyCopier ();

public:

  /**
   *	@brief Filter unwanted cells
   */
  class Filter
  {
  public:
      virtual CATBoolean SkipCell (const CATPolyCell& iCell) const = 0;
  };

  /**
   * Makes a copy of a CATPolyBody instance.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param iPos
   *   The optional position of the CATPolyBody instance.
   * @param oPolyBody
   *   The output CATPolyBody.  
   *   If any, the optional position transformation will be applied to the output CATPolyBody.
   *   The triangles will be flipped for transformation matrices with negative determinants.
   * @param iObserver
   *   The unary observer to obtain:
   *     - The mappings of the resulting cells to the input operand cells.
   *     - The mapping of the curve and mesh vertices made during the copy.
   * @param ipFilter
   *   Skip defined poly cells during copy
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> upon successful copy.
   *   <li> <tt>S_FALSE</tt> if some cells were skipped because of invalidity reasons.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  inline HRESULT Copy (const CATPolyBody& iPolyBody, const CATMathTransformation* iPos, 
                       CATPolyBody*& oPolyBody, CATPolyBodyUnaryObserver* iObserver = 0, CATPolyBodyCopier::Filter* ipFilter = 0) const;

  /**
   * Copies the CATPolyBody.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param oPolyBody
   *   The output CATPolyBody.
   *   It must be released upon successful copy of the input CATPolyBody.
   * @param ioInputToOutputCell
   *   A optional argument that maps the cells of the input CATPolyBody to
   *   the cells of the output CATPolyBody.
   * @param iPos
   *   A optional position that will be applied to the resulting copied poly body.
   *   If determinant of this matrix is negative, then the triangles will be flipped.
   * @param ipFilter
   *   Skip defined poly cells during copy
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> upon successful copy.
   *   <li> <tt>S_FALSE</tt> if some cells were skipped because of invalidity reasons.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  inline HRESULT Copy (const CATPolyBody& iPolyBody,
    CATPolyBody*& oPolyBody,
    CATMapOfPtrToPtr* ioInputToOutputCells = 0,
    const CATMathTransformation* iPos = 0, CATPolyBodyCopier::Filter* ipFilter = 0) const;

  /**
   * Copies the CATPolyBody with the data from the ith frame of the frame layers.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param iFrameLayers
   *   The input layers.
   * @param iFrame
   *   The index of the frame to copy (range from 1 to GetNbFrames () included.)
   * @param oPolyBody
   *   The output CATPolyBody.
   *   It must be released upon successful copy of the input CATPolyBody.
   * @param ioInputToOutputCell
   *   A optional argument that maps the cells of the input CATPolyBody to
   *   the cells of the output CATPolyBody.
   * @param iPos
   *   A optional position that will be applied to the resulting copied poly body.
   *   If determinant of this matrix is negative, then the triangles will be flipped.
   * @param ipFilter
   *   Skip defined poly cells during copy
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> upon successful copy.
   *   <li> <tt>S_FALSE</tt> if some cells were skipped because of invalidity reasons.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  inline HRESULT Copy (const CATPolyBody& iPolyBody, const CATIPolyBodyFrameLayers& iFrameLayers, const unsigned int iFrame,
    CATPolyBody*& oPolyBody,
    CATMapOfPtrToPtr* ioInputToOutputCells = 0,
    const CATMathTransformation* iPos = 0, CATPolyBodyCopier::Filter* ipFilter = 0) const;

public:

  // For internal use
  inline void SetObserver (CATPolyBodyCopierObserver* iObserver);
  inline CATPolyBodyCopierObserver* GetObserver () const;

protected:

  CATPolyBodyCopierObserver* _Observer;
  CATechExt* _PhoenixExtension;

private:

  MeshImplementation _Implementation;

private:

  HRESULT DoCopy (const CATPolyBody& iPolyBody, const CATMathTransformation* iPos,
    const CATIPolyBodyFrameLayers* iFrameLayers, const unsigned int iFrame,
    CATPolyBody*& oPolyBody, CATPolyBodyUnaryObserver* iUnaryObserver,
    CATMapOfPtrToPtr* ioInputToOutputCells, CATPolyBodyCopier::Filter* ipFilter) const;  // Redundant with unary observer.

  HRESULT CopyTopologyAndLayers (const CATPolyBody& iPolyBody,
    const CATIPolyBodyFrameLayers* iFrameLayers, const unsigned int iFrame,
    CATPolyBody& oPolyBody,
    CATMapOfPtrToPtr& ioCellToVertexMap,
    CATMapOfPtrToPtr& ioInputToOutputCell,
    CATPolyBodyUnaryObserver* iUnaryObserver, CATPolyBodyCopier::Filter* ipFilter, const CATMathTransformation* iPos) const;

  CATIPolyMesh* NewMesh (PolyPrecision Precision, const int nbVertices, const int nbTriangles,
    const CATBoolean iWithNormals) const;

  CATIPolySurfaceVertexLine* NewSurfaceVertexLine (CATIPolyMesh& iMesh, const int nbVertices) const;

};


inline HRESULT CATPolyBodyCopier::Copy (const CATPolyBody& iPolyBody, const CATMathTransformation* iPos, 
                                        CATPolyBody*& oPolyBody, CATPolyBodyUnaryObserver* iObserver, CATPolyBodyCopier::Filter* ipFilter ) const
{
  return DoCopy (iPolyBody, iPos, 0, 0, oPolyBody, iObserver, 0, ipFilter );
}

inline HRESULT CATPolyBodyCopier::Copy (const CATPolyBody& iPolyBody,
                                        CATPolyBody*& oPolyBody,
                                        CATMapOfPtrToPtr* ioInputToOutputCells,
                                        const CATMathTransformation* iPos, CATPolyBodyCopier::Filter* ipFilter ) const
{
  return DoCopy (iPolyBody, iPos, 0, 0, oPolyBody, 0, ioInputToOutputCells, ipFilter );
}

inline HRESULT CATPolyBodyCopier::Copy (const CATPolyBody& iPolyBody, const CATIPolyBodyFrameLayers& iFrameLayers, const unsigned int iFrame,
                                        CATPolyBody*& oPolyBody,
                                        CATMapOfPtrToPtr* ioInputToOutputCells,
                                        const CATMathTransformation* iPos, CATPolyBodyCopier::Filter* ipFilter ) const
{
  return DoCopy (iPolyBody, iPos, &iFrameLayers, iFrame, oPolyBody, 0, ioInputToOutputCells, ipFilter );
}

inline void CATPolyBodyCopier::SetObserver (CATPolyBodyCopierObserver* iObserver)
{
  _Observer = iObserver;
}

inline CATPolyBodyCopierObserver* CATPolyBodyCopier::GetObserver () const
{
  return _Observer;
}

#endif // !CATPolyBodyCopier_H
