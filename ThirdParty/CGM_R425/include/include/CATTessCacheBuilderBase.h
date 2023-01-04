//=============================================================================
// COPYRIGHT Dassault Systemes 2010
//=============================================================================
//
// CATTessCacheBuilderBase
//
//=============================================================================
// 2010-08-11 MPX: New
//=============================================================================
#ifndef CATTessCacheBuilderBase_H
#define CATTessCacheBuilderBase_H

#include "TessCacheObjects.h"
#include "CATMathInline.h"
#include "CATErrorDef.h"
#include "ListVOfCATTessParamToken.h"
#include "CATTessParamToken.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "ListPOfCATCell.h"
#include "CATListOfCATCGMAttribute.h"

class CATBody;
class CATFace;
class CATEdge;
class CATTessDataCache;

class ExportedByTessCacheObjects CATTessCacheBuilderBase
{

public:

  HRESULT Run();

public:

  CATTessCacheBuilderBase(
              CATBody& iBody, 
              const CATTessParamToken& iToken, 
              ListVOfCATTessParamToken* iRefTokens,
              CATBoolean iExcludeEdges,
              CATBoolean iExcludeFaces);

  CATTessCacheBuilderBase(
              CATFace& iFace, 
              const CATTessParamToken& iToken);

  CATTessCacheBuilderBase(
              CATEdge& iEdge, 
              const CATTessParamToken& iToken);

  virtual ~CATTessCacheBuilderBase();

  INLINE CATBoolean ExcludeEdges();
  INLINE CATTessParamToken& Token();

  HRESULT GetRefMesh(CATCell& iCell, CATTessDataCache*& oMesh);
  HRESULT GetFinalMesh(CATCell& iCell, CATTessDataCache*& oMesh);
  HRESULT SetRefAsFinal(CATCell& iCell);
  HRESULT IsRefSetAsFinal(CATCell& iCell, CATBoolean& oIsRefSetAsFinal);

protected:

  // Prepare for Tessellation:
  // Identify which cells need new tessellation and which do not. 
  // For those that do not need new tessellation, identify the reference tessellation data
  // Setup worker attributes on all cells with this information.

  HRESULT Prep();

  // Perform Tessellation:
  // Pure virtual method to tessellate. This is supposed to tessellate only the cells that need
  // tessellation. To achieve water-tightness it allowed to compute new tessellation for some cells
  // that already have reference tessellation data
  // This method will keep the new tessellation data into worker attributes

  virtual HRESULT Tessellate() = 0;

  // Create Tessellation Cache:
  // This just transfers the data from worker attributes into tessellation cache attributes

  HRESULT CreateCache();

protected:
  
  HRESULT InitCells();
  HRESULT InitEdge(CATEdge& iEdge);
  HRESULT InitFace(CATFace& iFace);

  HRESULT SelectOneRefMeshPerFace();
  HRESULT SelectOneRefMeshPerEdge();
  HRESULT ResolveWaterTightness();

  HRESULT DoesCellHaveMultipleOptions(CATCell& iCell, CATBoolean& oHasMultipleOptions);
  HRESULT DoesCellHaveUniqueRef(CATCell& iCell, CATBoolean& oHasUniqueRef);
  HRESULT DoesCellHaveNoRef(CATCell& iCell, CATBoolean& oHasNoRef);
  HRESULT GetAdjacentFaces(CATEdge& iEdge, ListPOfCATCell& oAdjacentFaces);
  HRESULT GetAdjacentFaces(CATFace& iFace, ListPOfCATCell& oAdjacentFaces);
  HRESULT GetAdjacentFaces(ListPOfCATCell& iGivenFaces, ListPOfCATCell& oAdjacentFaces);
  HRESULT IsLoneEdge(CATEdge& iEdge, CATBoolean& oIsLoneEdge);

  HRESULT ChooseBestMatchingRefMesh(CATFace& iFace, ListPOfCATCell& iBorderFaces);
  HRESULT ChooseLightestRefMesh(CATCell& iCell);
  HRESULT GetNumberOfPointsInRefMesh(CATFace& iFace, CATLONG32 &oNbPts);
  HRESULT GetTokensOfRefMesh(CATCell& iCell, ListVOfCATTessParamToken& ioTokens);
  HRESULT RemoveRefMesh(CATCell& iCell);
  HRESULT SelectRefMeshForEdge(CATEdge& iEdge, const CATTessParamToken& iToken);

protected:

  CATBody* _Body;
  ListPOfCATCell _Faces;
  ListPOfCATCell _Edges;

  ListPOfCATCell _NewFaces;
  ListPOfCATCell _AdjacentFaces;
  ListPOfCATCell _LoneEdges;
  ListPOfCATCell _NewLoneEdges;

  CATTessParamToken _Token;
  ListVOfCATTessParamToken _RefTokens;
  CATBoolean _ExcludeEdges;
  CATBoolean _ExcludeFaces;

  CATLISTP(CATCGMAttribute) _WorkerAttributes;
};

INLINE CATTessParamToken& 
CATTessCacheBuilderBase::Token()
{
  return _Token;
}

INLINE CATBoolean 
CATTessCacheBuilderBase::ExcludeEdges()
{
  return _ExcludeEdges;
}


#endif // !CATTessCacheBuilderBase_H

