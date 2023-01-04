// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshChecker.h
// Header definition of CATPolyMeshChecker
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// September 2005  Creation: NDO
//===================================================================
#ifndef CATPolyMeshChecker_H
#define CATPolyMeshChecker_H

#include "PolyBodyTools.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATErrorDef.h"

class CATIPolyMesh;
class CATPolyBars;
class CATPolyExactArithmetic;
class CATPolyGriddedPositionsConst;
class CATIPolySurfaceVertexPositionConstLayer;
class CATMathPoint;
class CATPolyMeshCheckerObserver;


/**
 * This operator checks a mesh for:
 *   a) Unreferenced vertices.
 *   b) Hole vertices.
 *   c) Non-manifold vertices.
 *   d) Hole bars.
 *   e) Non-manifold bars.
 *   f) Degenerate bars.
 *   g) Bad triangles.
 *   h) Degenerate triangles.
 *   i) Duplicate triangles.
 */
class ExportedByPolyBodyTools CATPolyMeshChecker
{

public :

  /**
   * Constructor. An instance of CATPolyExactArithmetic is required to find degenerate triangles.
   * If the instance is set to 0, the checker will not try to find degenerate triangles.
   */
  CATPolyMeshChecker (const CATPolyExactArithmetic& iExactArithmetic);
  CATPolyMeshChecker (const CATPolyExactArithmetic* iExactArithmetic);

  /**
   * Destructor
   */
  virtual ~CATPolyMeshChecker ();

  // Turns on or off the check for unreferenced vertices. (Default is off.)
  // An unreferenced vertex is a vertex not referenced by any triangle.
  inline void SetCheckUnreferencedVertices (const CATBoolean iCheck);

  // Turns on or off the check for hole vertices. (Default is off.)
  inline void SetCheckHoleVertices (const CATBoolean iCheck);

  // Turns on or off the check for non-manifold vertices. (Default is off.)
  inline void SetCheckNonManifoldVertices (const CATBoolean iCheck);

  // Turns on or off the check for hole bars. (Default is off.)
  inline void SetCheckHoleBars (const CATBoolean iCheck);

  // Turns on or off the check for non-manifold bars. (Default is off.)
  inline void SetCheckNonManifoldBars (const CATBoolean iCheck);

  // Turns on or off the check for degenerate bars. (Default is off.)
  inline void SetCheckDegenerateBars (const CATBoolean iCheck);

  // Turns on or off the check for bad triangles. (Default is off.)
  // Bad triangles are triangles with two or three identical vertices.  They are also degenerate triangles.
  inline void SetCheckBadTriangles (const CATBoolean iCheck);

  // Turns on or off the check for degenerate triangles. (Default is off.)
  inline void SetCheckDegenerateTriangles (const CATBoolean iCheck);

  // Turns on or off the check for duplicate triangles. (Default is off.)
  // Duplicate triangles are triangles having three identical vertices regardless of their orientation.
  inline void SetCheckDuplicateTriangles (const CATBoolean iCheck);

public:

  /**
   * Runs the operator.
   */
  HRESULT Run (const CATIPolyMesh& iMesh);

  /**
   * Runs the operator using a gridded vertex position layer.
   */
  HRESULT Run (const CATIPolyMesh& iMesh, const CATPolyGriddedPositionsConst& iGriddedVertexPositions);

public:

  // Returns the number of unreferenced vertices.
  int GetNbUnreferencedVertices () const;

  // Returns the number of hole vertices.
  int GetNbHoleVertices () const;

  // Returns the number of non-manifold vertices.
  int GetNbNonManifoldVertices () const;

  // Returns the number of hole bars.
  int GetNbHoleBars () const;

  // Returns the number of non-manifold bars.
  int GetNbNonManifoldBars () const;

  // Returns the number of degenerate bars.
  int GetNbDegenerateBars () const;

  // Returns the number of bad triangles.
  int GetNbBadTriangles () const;

  // Returns the number of degenerate triangles.
  int GetNbDegenerateTriangles () const;

  // Returns the number of duplicate triangles.
  int GetNbDuplicateTriangles () const;

  const CATListOfInt& GetUnreferencedVertices () const;
  const CATListOfInt& GetHoleVertices () const;
  const CATListOfInt& GetNonManifoldVertices () const;

  const CATPolyBars* GetHoleBars () const;
  const CATPolyBars* GetNonManifoldBars () const;
  const CATPolyBars* GetDegenerateBars () const;

  const CATListOfInt& GetBadTriangles () const;
  const CATListOfInt& GetDegenerateTriangles () const;
  const CATListOfInt& GetDuplicateTriangles () const;

  void RegisterObserver(CATPolyMeshCheckerObserver * obs);

public:

  // DO NOT USE.  DEPRECATED.
  HRESULT Run ();
  void SetMesh(const CATIPolyMesh* iMesh){_polyMesh = iMesh;}

private :

  void Clear ();

  const CATPolyExactArithmetic* _ExactArithmetic;
  const CATPolyGriddedPositionsConst* _GriddedPositions;
  CATIPolySurfaceVertexPositionConstLayer* _SurfaceVertexPositions;

  CATBoolean _CheckUnreferencedVertices;
  CATBoolean _CheckHoleVertices;
  CATBoolean _CheckNonManifoldVertices;
  CATBoolean _CheckHoleBars;
  CATBoolean _CheckNonManifoldBars;
  CATBoolean _CheckDegenerateBars;
  CATBoolean _CheckBadTriangles;
  CATBoolean _CheckDegenerateTriangles;
  CATBoolean _CheckDuplicateTriangles;

  CATListOfInt _UnreferencedVertices;
  CATListOfInt _HoleVertices;
  CATListOfInt _NonManifoldVertices;

  CATPolyBars* _HoleBars;
  CATPolyBars* _NonManifoldBars;
  CATPolyBars* _DegenerateBars;

  CATListOfInt _BadTriangles;
  CATListOfInt _DegenerateTriangles;
  CATListOfInt _DuplicateTriangles;

  const CATIPolyMesh* _polyMesh;
  CATPolyMeshCheckerObserver * m_obs;

private:

  void GetVertexPositions (const int vertices[], 
                           CATMathPoint& A, CATMathPoint& B, CATMathPoint& C) const;

  HRESULT RunPrivate (const CATIPolyMesh& iMesh);

};


inline void CATPolyMeshChecker::SetCheckUnreferencedVertices (const CATBoolean iCheck)
{
  _CheckUnreferencedVertices = iCheck;
}


inline void CATPolyMeshChecker::SetCheckHoleVertices (const CATBoolean iCheck)
{
  _CheckHoleVertices = iCheck;
}


inline void CATPolyMeshChecker::SetCheckNonManifoldVertices (const CATBoolean iCheck)
{
  _CheckNonManifoldVertices = iCheck;
}


inline void CATPolyMeshChecker::SetCheckHoleBars (const CATBoolean iCheck)
{
  _CheckHoleBars = iCheck;
}


inline void CATPolyMeshChecker::SetCheckNonManifoldBars (const CATBoolean iCheck)
{
  _CheckNonManifoldBars = iCheck;
}


inline void CATPolyMeshChecker::SetCheckDegenerateBars (const CATBoolean iCheck)
{
  _CheckDegenerateBars = iCheck;
}


inline void CATPolyMeshChecker::SetCheckBadTriangles (const CATBoolean iCheck)
{
  _CheckBadTriangles = iCheck;
}


inline void CATPolyMeshChecker::SetCheckDegenerateTriangles (const CATBoolean iCheck)
{
  _CheckDegenerateTriangles = iCheck;
}


inline void CATPolyMeshChecker::SetCheckDuplicateTriangles (const CATBoolean iCheck)
{
  _CheckDuplicateTriangles = iCheck;
}

#endif
