// COPYRIGHT DASSAULT SYSTEMES 2004-2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyFileOBJ.h
//
//===================================================================
// Sep 2004 Creation: svx, ndo
// Fev 2016 : KTU Correction  test HasUniqueTextureCoord
//===================================================================
#ifndef CATPolyFileOBJ_h
#define CATPolyFileOBJ_h

#include "PolyMeshTools.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyFileOBJ.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATMathPointf.h"

class CATIPolyMesh;
class CATPolyBody;
class CATPolySurfaceVertexNNormalsLayer;
class CATUnicodeString;

struct ObjMaterial;
struct ObjTriangle;
struct ObjGroup;


/**
* Service to stream a CATIPolyMesh into an OBJ file or to unstream a CATIPolyMesh from an OBJ file.
*/
class ExportedByPolyMeshTools CATPolyFileOBJ
{

public:

  CATPolyFileOBJ ();
  ~CATPolyFileOBJ ();

public:

  /**
   * Reads and parses an OBJ file.
   */
  HRESULT Read (const CATUnicodeString & iFileName);

  /**
   * Fills in a CATIPolyMesh from the data in the OBJ file.
   * @param iPolyMesh
   *   The input CATIPolyMesh for adding vertices and triangles.
   * @param iNormalLayer
   *   An optional (deprecated) normal layer for the vertices of the mesh.
   *   This class is deprecated. Do not use.
   */
  HRESULT Get (CATIPolyMesh* iPolyMesh, 
               CATPolySurfaceVertexNNormalsLayer* iNormalLayer = 0) const;

public:

  /**
   * Writes the data into an OBJ file.
   */
  HRESULT Write (const CATUnicodeString & iFileName);
  
  /**
   * Streams the data from a CATIPolyMesh to the OBJ file.
   * @param iPolyMesh
   *   The input CATIPolyMesh.
   */
  HRESULT Put (const CATIPolyMesh& iPolyMesh) const;

  /**
   * Streams the data from a CATIPolyMesh to the OBJ file.
   * @param iPolyMesh
   *   The input CATIPolyMesh.
   * @param iNormalLayer
   *   An optional (deprecated) normal layer for the vertices of the mesh.
   *   This class is deprecated. Do not use.
   * @param iNoGroup
   *   Without or with groups.
   */
  HRESULT Put (const CATIPolyMesh* iPolyMesh, 
               const CATPolySurfaceVertexNNormalsLayer* iNormalLayer, 
               int iNoGroup, CATListOfCATUnicodeString* iGroups,const char * imtlFileName = 0) const;

  HRESULT Put (const CATIPolyMesh* iPolyMesh, 
               const CATPolySurfaceVertexNNormalsLayer* iNormalLayer = 0, 
               int iNoGroup = 0, const char * imtlFileName = 0) const {return Put (iPolyMesh, iNormalLayer, iNoGroup, 0, imtlFileName);}
			   
  HRESULT Put (const CATIPolyMesh* iPolyMesh, const CATLISTV(CATMathPointf) &iVertexColors,
			   const CATPolySurfaceVertexNNormalsLayer* iNormalLayer = NULL,
			   int iNoGroup = 0,
			   CATListOfCATUnicodeString* iGroups = NULL, const char * imtlFileName = 0) const;

  /**
   * Streams the data from a CATPolyBody to the OBJ file.
   * @param iPolyBody
   *   The input CATPolyBody.
   */
  HRESULT Put (const CATPolyBody& iPolyBody) const;

  /**
   * @deprecated
   */
  HRESULT Put (const CATPolyBody* iPolyBody, 
               const CATPolySurfaceVertexNNormalsLayer*, int) const;

public:

  /**
   * Iterator through the groups of the OBJ file.
   */
  class ExportedByPolyMeshTools GroupIterator 
  {
  public:
    GroupIterator (const CATPolyFileOBJ& iOBJFile) : _Group (iOBJFile._Groups) {}
    ~GroupIterator () {_Group = NULL;}
  public:
    CATBoolean End () const {return _Group == NULL;}
    GroupIterator& operator++ ();
  public:
    /**
     * Returns the number of triangles from the group.
     */
    int GetNbTriangles () const;
    /**
     * Returns the group.
     */
    ObjGroup* Get () const {return _Group;}
  private:
    ObjGroup* _Group;
  };

public:

  /**
   * Returns <tt>TRUE</tt> if the OBJ file has normals.
   */
  inline CATBoolean HasNormals () const;

  /**
   * Returns <tt>TRUE</tt> if the OBJ file has the same number of normals than the number of vertices.
   * can be used after Read
   */
  inline CATBoolean HasUniqueNormals () const;

  /**
   * Returns <tt>TRUE</tt> if the OBJ file has the same number of textures coordinates than the number of vertices.
   * can be used after Read
   */
  inline CATBoolean HasUniqueTextureCoord () const;

  /**
   * Fills in a mesh with the data from an OBJ group.
   */
  HRESULT FillMesh (const ObjGroup* iGroup, CATIPolyMesh& iMesh, const bool iDuplicateVeticesIfSeveralTextureOrNormalCoordinate = false);
  /**
   * Fills in a mesh with the data from default group.
   */
  HRESULT FillMeshFromDefaultGroup (CATIPolyMesh& iMesh, const bool iDuplicateVeticesIfSeveralTextureOrNormalCoordinate = false);

private:

  void Deallocate (void);

  CATBoolean FirstPass (void* iFile);
  CATBoolean SecondPass (void* iFile);
  ObjGroup* FindGroup (char* iName) const;
  ObjGroup* AddGroup (char* iName);
  CATBoolean ReadMaterial (char* iFilename);
  int FindMaterial (char* iMtlName);
  HRESULT BuildFaceIndexes() const;

  CATUnicodeString* _PathName;
  CATUnicodeString* _MaterialLibraryName;

  int             _NumVertices;
  float*          _Vertices;
                
  int             _NumNormals;
  float*          _Normals;
                
  int             _NumTextureCoords;
  float*          _TextureCoords;
                
  int             _NumFacetNormals;
  float*          _FacetNormals;
                
  int             _NumTriangles;
  ObjTriangle*    _Triangles;

  int             _NumMaterials;
  ObjMaterial*    _Materials;

  int             _NumGroups;
  ObjGroup*       _Groups;
#ifndef CHU_11dec2006
  int             _SmoothGroups;
#endif

  float           _Position[3];

  friend class GroupIterator;

};

inline CATBoolean CATPolyFileOBJ::HasNormals () const
{
  return _NumNormals > 0;
}

inline CATBoolean CATPolyFileOBJ::HasUniqueNormals () const
{
  return (_NumNormals == _NumVertices);
}

  
inline CATBoolean CATPolyFileOBJ::HasUniqueTextureCoord () const
{
  return (_NumVertices == _NumTextureCoords);
}

#endif
