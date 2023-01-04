#ifndef CATPolySurfParam_h
#define CATPolySurfParam_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATPolySurfParam:
//    Header file defining a parametric point on a CATGeoPolySurface (mesh-point)
//
//=============================================================================
// Usage notes:
//=============================================================================
// Jan.2017 Creation by DPS
//=============================================================================

#include "ExportedByCATCGMGeoMath.h"

#include "CATMathInline.h"
#include "CATSurParam.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"


class CATGeoPolySurface;
class CATIPolySurface;

/**
 * Class representing the parametric description of a point lying on a CATGeoPolySurface
 *<br> The parametric description of a mesh-point refers to a sub-element of the mesh and can lie
 * on a vertex (mesh-vertex), a bar (mesh-bar) or a triangle of the mesh. 
 *
 * More specifically, a PolySurfParam is defined by one, two or three mesh-vertices
 * associated to one, two or three barycentric coordinates, respectively.
 * <ul>
 *   <li> The mesh-point just refers to a mesh-vertex with the first barycentric coordinate
 *        set to one in the case of a mesh-point on a vertex.
 *   <li> The mesh-point refers to two mesh-vertices and two barycentric coordinates in the
 *        case of a mesh-point on a bar.
 *   <li> The mesh-point refers to three mesh-vertices and three barycentric coordinates in the
 *        case of a mesh-point on a triangle.
 * </ul>
 *
 * The sum of the barycentric coordinates is equal to 1.
 */
/** @nocgmitf (do not create any specific interface) */
class ExportedByCATCGMGeoMath CATPolySurfParam
{
 public:

   /**
   * Enumerator defining the type of a mesh point: vertex, bar or triangle.
   */
   enum PolySurfParamType
   {
     UndefinedType = 0,
     VertexType    = 1,
     BarType       = 2,
     TriangleType  = 3
   };  

   //=============================================================================
   //- CONSTRUCTORS
   //=============================================================================
   /**
   * Default constructor
   *<br> without any reference to CATGeoPolySurface, the object cannot be used if UpdateReference() isn't called before
   */
   CATPolySurfParam ();

   /**
   * Copy constructor.
   */
   CATPolySurfParam (const CATPolySurfParam & iParamToCopy);

   /**
   * Constructor with a CATGeoPolySurface
   */
   CATPolySurfParam (const CATGeoPolySurface &iPolySurfRef);

   /**
   * Constructor with a CATIPolySurface as reference
   */
   CATPolySurfParam (const CATIPolySurface &iPolySurfRef);


   //=============================================================================
   //- Destructor
   //=============================================================================
   ~CATPolySurfParam ();


   //=============================================================================
   // REFERENCE MANAGEMENT
   //=============================================================================

   /**
   * @nodoc
   * Updates the reference of a CATPolySurfParam.
   */
   void UpdateReference(const CATGeoPolySurface & iPolySurfRef);

   /**
   * @nodoc
   * Sets the CATIPolyMesh as reference for the CATPolySurfParam
   */
   INLINE void SetReference(const CATIPolySurface * iPolySurfRef);

   /**
   * @nodoc
   * Returns the identifier of the CATPolySurfParam reference.
   * @return
   * The value of the reference identifier. To be used to compare the polyhedral surfaces on which parameters are defined.
   */
   INLINE CATINTPTR GetReferenceID() const;


   //=============================================================================
   //- SETTING METHODS
   //=============================================================================

public:

  /**
   * Defines a mesh-point on a mesh-vertex.
   */
  INLINE void SetParamOnVertex (int iMeshVertexNum);

  /**
   * Defines a mesh-point on a mesh-bar.
   */
  INLINE void SetParamOnBar (int iBarStartVtxNum, int iBarEndVtxNum, double iStartCoord, double iEndCoord);

  /**
   * Defines a mesh-point on a triangle.
   */
  INLINE void SetParameters (int iVtx0, int iVtx1, int iVtx2, double iU, double iV, double iW);

  /**
  * Sets the triangle referred to by a mesh-point.
  */
  INLINE void SetTriangle (int iTriangleNum);

  /**
  * Sets all data to null value (idem constructor)
  */
  INLINE void Reset ();


//=============================================================================
//- READING METHODS
//=============================================================================
  /**
   * Returns the type of the mesh point.
   * @return
   * <ul>
   *   <li> PolySurfParamType::VertexType   for a mesh-point on a vertex.
   *   <li> PolySurfParamType::BarType      for a mesh-point on a bar.
   *   <li> PolySurfParamType::TriangleType for a mesh-point on a triangle.
   * </ul>
   */
  INLINE PolySurfParamType GetType () const;

  /**
   * Returns the three surface-vertices defining the mesh-point.
   * The second and third coordinates are equal to 0 for a mesh-point on a vertex.
   * The third coordinate is equal to 0 for a mesh-point on a bar.
   */
  INLINE void GetMeshVertices (int& oVtx0, int& oVtx1, int& oVtx2) const;

  /**
   * Returns a surface-vertex given its index: 0, 1, or 2.
   */
  INLINE int GetMeshVertex (unsigned int iIdx012) const;

  /**
   * Returns the barycentric coordinates associated to the vertices.
   */
  INLINE void GetParameters (double& oU, double& oV, double& oW) const;

  /**
   * Returns a barycentric coordinate given its index: 0, 1, or 2.
   */
  INLINE double GetParameter (unsigned int iIdx012) const;

  /** @nodoc */
  INLINE int GetTriangle () const;


//=============================================================================  
// OVERLOADED OPERATORS
//=============================================================================

  /**
  * @nodoc
  * Assignment operator.
  */
  CATPolySurfParam& operator = (const CATPolySurfParam &iPolySurfRef);

  /**
  * @nodoc
  * Equality operator.
  */
  CATLONG32 operator == (const CATPolySurfParam &iOtherParam) const;

  /**
  * @nodoc
  * Inequality operator.
  */
  CATLONG32 operator != (const CATPolySurfParam &iOtherParam) const;

  /**
  * @nodoc
  * forbidden operators without any implementation : Subtraction, Addition, Addition assignment
  */
  CATPolySurfParam operator - (const CATPolySurfParam & iOtherParam) const;
  CATPolySurfParam operator + (const CATPolySurfParam & iOtherParam) const;
  void operator += (const CATPolySurfParam & iOtherParam);


  //=============================================================================  
  // OTHER SERVICES
  //=============================================================================

  /**
  * @nodoc
  * returns the validity status 
  * valid only if the reference is known, if the type is defined and if the sum of barycentric coordinates is equal to 1.
  */
  CATBoolean IsValid() const;


private:

//=============================================================================
// INTERNAL DATAS
//=============================================================================

  int _V[3];        // MeshVertexNum
  int _T;           // Triangle index. (Optional.)

  double _UVW[3];   // Barycentric Coordinates.  The sum of the three coordinates is equal to 1.

// Pointer on the CATIPolyMesh
  /** @nodoc */
  const CATIPolySurface * _Reference;
};


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================

INLINE void CATPolySurfParam::SetParamOnVertex (int iMeshVertexNum) {
  _V[0] = iMeshVertexNum;
  _V[1] = _V[2] = 0;
  _UVW[0] = 1.;
  _UVW[1] = _UVW[2] = 0.; }

INLINE void CATPolySurfParam::SetParamOnBar (int iBarStartVtxNum, int iBarEndVtxNum, double iStartCoord, double iEndCoord) {
  if (iBarStartVtxNum < iBarEndVtxNum)
  {
    _V[0] = iBarStartVtxNum;
    _V[1] = iBarEndVtxNum;
    _UVW[0] = iStartCoord;
    _UVW[1] = iEndCoord;
  }
  else
  {
    _V[0] = iBarEndVtxNum;
    _V[1] = iBarStartVtxNum;
    _UVW[0] = iEndCoord;
    _UVW[1] = iStartCoord;
  }
  _V[2] = 0;
  _UVW[2] = 0.; }

INLINE void CATPolySurfParam::SetParameters (int iVtx0, int iVtx1, int iVtx2, double iU, double iV, double iW) {
  _V[0] = iVtx0;
  _V[1] = iVtx1;
  _V[2] = iVtx2;
  _UVW[0] = iU;
  _UVW[1] = iV;
  _UVW[2] = iW;
}

INLINE void CATPolySurfParam::SetTriangle (int iTriangleNum) {
  _T = iTriangleNum; }

INLINE void CATPolySurfParam::Reset () {
  _Reference = NULL;
  _V[0] = _V[1] = _V[2] = _T = 0;
  _UVW[0] = _UVW[1] = _UVW[2] = 0.;  
}

INLINE void CATPolySurfParam::SetReference(const CATIPolySurface * iPolySurfRef) {
  _Reference = iPolySurfRef; }

INLINE CATINTPTR CATPolySurfParam::GetReferenceID() const {
  return (CATINTPTR) _Reference; }

INLINE CATPolySurfParam::PolySurfParamType CATPolySurfParam::GetType () const {
  if (_V[2] != 0)
    return TriangleType;
  else if (_V[1] != 0)
    return BarType;
  else if (_V[0] != 0)
    return VertexType;
  else
    return UndefinedType; }

INLINE void CATPolySurfParam::GetMeshVertices (int& oVtx0, int& oVtx1, int& oVtx2) const {
  oVtx0 = _V[0];
  oVtx1 = _V[1];
  oVtx2 = _V[2]; }

INLINE int CATPolySurfParam::GetMeshVertex (unsigned int iIdx012) const {
  return _V[iIdx012]; }

INLINE void CATPolySurfParam::GetParameters (double& oU, double& oV, double& oW) const {
  oU = _UVW[0];
  oV = _UVW[1];
  oW = _UVW[2]; }

INLINE double CATPolySurfParam::GetParameter (unsigned int iIdx012) const {
  return _UVW[iIdx012]; }

INLINE int CATPolySurfParam::GetTriangle () const {
  return _T; }

#endif
