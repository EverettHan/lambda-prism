// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathPNTriangleData.h
// Header definition of CATPolyMathPNTriangleData
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathPNTriangleData_H
#define CATPolyMathPNTriangleData_H

#include "PolyMathSurfaces.h"

class CATMathPoint;
class CATMathVector;

class CATCGMOutput;


/**
 * Describe your class here.
 * Structure to hold the data required for the construction of a PNT Triangle.
 * This structure is filled in and then used to construct a PNT triangle.
 */
class ExportedByPolyMathSurfaces CATPolyMathPNTriangleData 
{

public:

  CATPolyMathPNTriangleData ();

  // Set the vertex positions and normals.
  // @param iVertex
  //   The vertex index: 0, 1 or 2.
  void SetVertexPosition (const int iVertex, const CATMathPoint& P);
  void SetVertexNormal (const int iVertex, const CATMathVector& N);

  // CONTROL POINTS

  void SetControlPoint (const int iControlPointIndex, const CATMathPoint& P);
  void GetControlPoint (const int iControlPointIndex, CATMathPoint& P) const;

  void SetControlPoint (const int iControlPointIndex, const float x, const float y, const float z);
  void GetControlPoint (const int iControlPointIndex, float& x, float& y, float& z) const;

  void SetControlPoint (const int iControlPointIndex, const double xyz[]);
  void GetControlPoint (const int iControlPointIndex, double xyz[]) const;

  // CONTROL NORMALS

  void SetControlNormal (const int iControlNormalIndex, const CATMathVector& N);
  void GetControlNormal (const int iControlNormalIndex, CATMathVector& N) const;

  void SetControlNormal (const int iControlNormalIndex, const float x, const float y, const float z);
  void GetControlNormal (const int iControlNormalIndex, float& x, float& y, float& z) const;

  void SetControlNormal (const int iControlNormalIndex, const double xyz[]);
  void GetControlNormal (const int iControlNormalIndex, double xyz[]) const;

  // TANGENTS

  void SetTangent (const int iTangentIndex, const CATMathVector& T);
  void GetTangent (const int iTangentIndex, CATMathVector& T) const;

  void SetTangent (const int iTangentIndex, const float x, const float y, const float z);
  void GetTangent (const int iTangentIndex, float& x, float& y, float& z) const;

  void SetTangent (const int iTangentIndex, const double xyz[]);
  void GetTangent (const int iTangentIndex, double xyz[]) const;

public:

  void Print (CATCGMOutput& stream) const;

public:

  int IsControlPointSet (const int iControlPointIndex) const;
  int IsControlNormalSet (const int iControlNormalIndex) const;
  int IsTangentSet (const int iTangentIndex) const;

private:

  double _ControlPoints[10][3];  // Control points.
  double _ControlNormals[6][3];  // Control normals.
  double _Tangents[6][3];        // Tangents.

  // Flags (10 for control points, 6 for control normals and 6 for tangents) indicating 
  // whether the corresponding triangle data have been set or not.
  int _Flags;  

};

#endif
