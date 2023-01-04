// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTextureVertexCoords2DLayer.h
//
//===================================================================
// September 2018  Creation: Q8M, NDO
//===================================================================

#ifndef _AIX_SOURCE

#include "PolyLayers.h"
#include "CATUnicodeString.h" 
#include "CATIPolyMesh.h"
#include "CATIPolyTextureVertexCoords2DLayer.h"
#include "CATIPolyMeshObserver.h"

#include <map>
#include <set>
#include <vector>

class CATPolyTextureVertexCoords2DLayerSpatialMeshObserver;
class CATPolyTextureVertexCoords2DLayerDisabler;

class ExportedByPolyLayers CATPolyTextureVertexCoords2DLayer : public CATIPolyTextureVertexCoords2DLayer
{
	friend class CATPolyTextureVertexCoords2DLayerSpatialMeshObserver;
	friend class CATPolyTextureVertexCoords2DLayerDisabler;

private:
	/**
	* Constructor
	*
	*/
	CATPolyTextureVertexCoords2DLayer(CATIPolyMesh *polyMesh3D, CATIPolyObject::PrecisionVertexPosition precision, int vDim /* not used for now */, const CATUnicodeString& texCoordSet);

public:
	/**
	* Creates a new layer and adds it to the given mesh
	*
	*/
	static CATPolyTextureVertexCoords2DLayer * AddNewLayer(CATIPolyMesh *polyMesh3D, CATIPolyObject::PrecisionVertexPosition precision, int vDim /* not used for now */, const CATUnicodeString& texCoordSet);

	/**
	* Destructor
	*/
	virtual ~CATPolyTextureVertexCoords2DLayer();

	/**
	* Returns an iterator through the texture-vertices of the triangle.
	* The texture-vertex values may differ from the surface-vertex values.
	*/
	virtual HRESULT GetIterator(CATIPolyMeshTriangleVertexIterator*& it) const;

	/**
	* Returns the three texture-vertices given a triangle index.
	*/
	virtual HRESULT GetTriangle(int t, int vt[3]) const;

	/**
	* Adds a texcoord
	*/
	virtual HRESULT Add(double a, double b, int& oTexCoordIdx);

	/**
	* Returns the double values associated to the texture-vertex.
	*/
	virtual HRESULT Get(int v, double& a, double& b) const;

	/**
	* Sets the double values associated to the texture-vertex.
	*/
	virtual HRESULT Set(int v, double a, double b) const;

	/**
	* Returns identifier of layer
	*/
	virtual const CATUnicodeString& GetIdentifier() const { return _TexCoordSet; }

	/**
	* Returns an instance of a CATIPolySurfaceDisabler.
	* A layer may not support all editing operations on a CATIPolySurface.
	* When a specific operation is not supported by the data layer, then a query
	* made to the disabler for this operation returns true.
	* The CATIPolySurface should not be edited otherwise the layer may become invalid.
	* @param oDisabler
	*   The output disabler. This instance must be deleted.
	*/
	virtual HRESULT GetDisabler(CATIPolySurfaceDisabler*& oDisabler);

	/**
	* Sets the three texture-vertices given a triangle index.
	*/
	HRESULT SetTriangle(int& ioTexCoordTriIdx, const int vt[3]);

	/**
	* Returns the texcoord triangle index of the given master triangle index
	*/
	HRESULT GetTexCoordTriangleIndex(int iMesh3DTriIdx, int& oTexCoordTriIdx) const;

	/**
	* Returns the master triangle index of the given texcoord triangle index
	*/
	HRESULT GetMesh3DTriangleIndex(int iTexCoordTriIdx, int& oMesh3DTriIdx) const;

	/**
	* Struct containing texcoord indices of a split bar in the texcoord mesh
	* After splitting a bar in the spatial mesh, the split texcoord (_VSplit) of the
	* corresponding texcoord bar (_V0 -- _V1) is undefined and must be set after
	* the SplitBar()-operation
	*/
	struct ExportedByPolyLayers SplitBarTriplet
	{
		SplitBarTriplet() : _V0(0), _V1(0), _VSplit(0) { }
		SplitBarTriplet(int v0, int v1, int vsplit) : _V0(v0), _V1(v1), _VSplit(vsplit) { }
		int _V0;
		int _V1;
		int _VSplit;
	};

	/**
	* Returns triplets of split texcoord bars
	*/
	HRESULT GetSplitBarTriplets(int& oNumTriplets, const SplitBarTriplet *& oTriplets) const;

protected:

	//! Called by the internal observer for the spatial mesh
	HRESULT ReactToAddVertex(int v);
	HRESULT ReactToSplitBar(int v0, int v1, int n);
	HRESULT PrepareToMergeVertices(int v0, int v1);
	HRESULT ReactToMergeVertices(int v0, int v1);
	HRESULT ReactToAddTriangle(int v0, int v1, int v2, int t);
	HRESULT PrepareToRemoveTriangle(int t);
	bool DisableFlipBar(int v0, int v1) const;
	HRESULT ReactToFlipBar(int v0, int v1);
	HRESULT ReactToSplitTriangle(int t, int t0, int t1);
	HRESULT ReactToUpdateTriangle(int t0, int t1, int v0, int v1);
	HRESULT ReactToCompact(const CATMapOfIntToInt& iVertexMap, const CATMapOfIntToInt& iTriangleMap);

	//! Called by the disabler to check whether the bar between t0 and t1 can be flipped in the texcoord layer
	HRESULT CheckFlipBar(int t0, int t1) const;

	//! "Master"-mesh for texcoord triangles. Number of triangles MUST be in sync
	CATIPolyMesh *_PolyMesh3D;

	//! Internal poly mesh used for texcoord triangles
	CATIPolyMesh *_TexCoordMesh;

	//! Identifier for the texoords
	CATUnicodeString _TexCoordSet;

	//! Disabler for checking FlipBar()-calls
	CATPolyTextureVertexCoords2DLayerDisabler *_PolyMeshDisabler;

	//! Mapping table for matching triangle indices between texcoord mesh and master mesh
	//! Instead a comination of RemoveTriangle()/AddTriangle() has to be used meaning that a new
	//! internal triangle index is returned for the changed texcoord triangle
	std::map<int, int> _TexCoordTriIdx2Mesh3DIdxMap;
	std::map<int, int> _Mesh3DIdx2TexCoordTriIdxMap;

	//! Dummy texcoords for invalid triangles
	int _InvalidTexCoordTri[3] = { 0, 0, 0 };

	//! List of SplitBarTriples in order to compute the final split texcoord position
	std::vector<SplitBarTriplet> _SplitBarTriples;

	//! Last vertex added to polymesh (used as cache)
	int _LastAddedVertex3D;

	//! Temporary list of pairs of triangles obtained during a SplitBar()-call (used as cache)
	typedef std::pair<int, int> SplitTrianglePair;
	std::vector<SplitTrianglePair> _SplitTrianglePairs;

	//! Vertices to merge (used as cache)
	typedef std::pair<int, int> MergeVerticesPair;
	MergeVerticesPair _VerticesToMerge;

	//! We may have several texcoords for each vertex (used as cache)
	std::set<MergeVerticesPair> _TexCoordsToMerge;

	//! Bar to flip as a pair of texcoords (used as cache)
	mutable std::pair<int, int> _BarToFlip;
};

#endif
