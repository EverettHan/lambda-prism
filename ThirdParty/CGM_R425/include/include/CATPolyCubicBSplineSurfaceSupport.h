// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCubicBSplineSurfaceSupport.h
//
//===================================================================
//
// March 2009  Creation: TPG
//===================================================================
#ifndef CATPolyCubicBSplineSurfaceSupport_H
#define CATPolyCubicBSplineSurfaceSupport_H

#include "PolySupports.h"
#include "CATIPolySurfaceSupport.h"
#include "CATPolyFace.h"
#include "CATIPolySurface.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

class CATFace;
class CATIPolyMesh;
class CATIPolySurfaceVertexLine;
class CATPolyMathCubicBSplineSurface;
class CATPolyMathCurve;
class CATMathStream;


class ExportedByPolySupports CATPolyCubicBSplineSurfaceSupport : public CATIPolySurfaceSupport
{

public:

  CATPolyCubicBSplineSurfaceSupport ();
  CATPolyCubicBSplineSurfaceSupport (int iNbU, int iNbV, const double * iKnotU, const double * iKnotV, const double * iGrid);
  CATPolyCubicBSplineSurfaceSupport (const CATPolyMathCubicBSplineSurface& iSurface);
  virtual ~CATPolyCubicBSplineSurfaceSupport ();

public:

  static const CATPolyCubicBSplineSurfaceSupport* Cast (const CATIPolyLayer*);
  static CATPolyCubicBSplineSurfaceSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  inline const void GetData (int & oNbU, int & oNbV, const double *& oKnotU, const double *& oKnotV, const double *& oGrid) const;
  const int FillCubicBSplinePolyMesh (CATIPolyMesh & iQuadMesh, int iNormalOrientationInFace = 1);
  inline const int GetNbVertexOnGridSide(int iSide) const;
  const int GetGridSideIndexInMesh(int iSide, int iIndexOnSide, int iDir = 1) const;
  //const int GetGridSideBarOfParam(int iSide, double iParam, double * oUV, int & oIndexV1,  int & oIndexV2) const;
  const int GetUVOfGridPoint(int iIndexInMesh, double oUV[2]) const;
  const int RefineGridUniformelyWithoutEdges(CATPolyFace * iPolyFace, CATIPolyMesh *& oRefinedPolyMesh, int iRefinementLevel) const;
  const int RefineGridUniformelyWithEdges(CATPolyFace * iPolyFace, CATIPolyMesh *& oRefinedPolyMesh, double iSag, int iRefinementLevel, int iRefinementMode) const;
  const int ComputeMaxRefinementLevel(double iSag, int iRefinementLevel,  int & oRefinementLevelU, int & oRefinementLevelV) const;
  const int Stream(CATMathStream& iStream) const;
  const int Unstream(CATMathStream& iStream) ;

public:

  Type GetType () const;

  const CATPolyCubicBSplineSurfaceSupport* CastAsCubicBSplineSurface () const;

  /*
   * Return a CATPolyMathSurface.  The object returned is not supposed to be deleted.
   * Its life cycle is managed by this class.
   */
  HRESULT GetMathSurface (const CATPolyMathSurface*& oSurface) const;
  HRESULT GetMathSurface (CATPolyMathSurface*& oSurface);
  HRESULT GetNewMathSurface (CATPolyMathSurface*& oSurface) const;
   
public:

  // Make a copy of itself.  Instance is to be deleted.
  CATIPolySupport* Clone () const;

public:

  const CATPolyMathCubicBSplineSurface * GetMathCubicBSplineSurface()const{return _CubicBSplineSurface;}

private:

	//void GetCubicBSplineSurfaceInterpolationGrid(CATPolyMathCubicBSplineSurface * pCubicBSplineSurface,double * iGrid);
  const int VertexLineRefinement (CATIPolySurfaceVertexLine * iVertexLine, int iBSplineVertexLineType, CATIPolyMesh * iRefinedPolyMesh, int iNormalOrientationInFace, double iSag, int iRefinementLevel, int iRefinementMode, 
                                  int & oNbVerticesOfRefinedVertexLine, double *& oTabUVOfRefinedVertexLine, int *& oTabIndexInMeshOfRefinedVertexLine) const;
  const int TriangulateBorder (CATIPolyMesh * iRefinedPolyMesh, int iNormalOrientationInFace,
                               int iNbVerticesOfRefinedVertexLine, double * iTabUVOfRefinedVertexLine, int * iTabIndexOfRefinedVertexLine,
                               int iNbVerticesOfRefinedBorderNeighbor, double * iTabRefinedBorderNeighborUV, int * iTabRefinedBorderNeighborIdxInMesh) const;
  const int GetUVOfVertexLinePoint(CATIPolySurfaceVertexLine * iVertexLine, int iSubSegmentStartIdx, int iSubSegmentEndIdx, double * iTabUVOfvertexLine) const;
  unsigned int ComputeLevelOfRefinement (const CATPolyMathCurve& iCurve, double itStart, double itEnd, const double iSag, const unsigned int iMaxLevelOfRefinement, double * iTabCoefSag) const;
  double ComputeUpperBoundOfDeviation (const CATPolyMathCurve& iCurve, const double tS, const CATMathPoint& S, const double tE, const CATMathPoint& E) const;

private:

  int _NbU;
  int _NbV;
  double * _KnotU;
  double * _KnotV;
  double * _Grid;
  CATPolyMathCubicBSplineSurface * _CubicBSplineSurface;
};

inline const void CATPolyCubicBSplineSurfaceSupport::GetData (int & oNbU, int & oNbV, const double *& oKnotU, const double *& oKnotV, const double *& oGrid) const
{
  oNbU = _NbU;
  oNbV = _NbV;
  oKnotU = _KnotU;
  oKnotV = _KnotV;
  oGrid = _Grid;
}

inline const int CATPolyCubicBSplineSurfaceSupport::GetNbVertexOnGridSide(int iSide) const
{
  if (iSide==1 || iSide == 3) // Iso V
    return _NbU;
  else if (iSide==2 || iSide == 4) // Iso U
    return _NbV;
  return 0;
}

#endif // !CATPolyCubicBSplineSurfaceSupport_H
