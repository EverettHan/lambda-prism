//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//==============================================================================================================
// CATPolyImportTypedef : declaration of typedef used for handling pointers to functions in cgr import
//==============================================================================================================
// Creation : CHU , 07 / 08 / 2003
//==============================================================================================================

#ifndef CATPolyImportTypedef_H
#define CATPolyImportTypedef_H

class CAT3DRep;

// Iterators on vertices and triangles of a face, ioIterData must be null at first call
// iterations must be processed until null is returned (then ioIterData is also reset to null)
// FaceVertexIterator returns a triple {x,y,z} whereas FaceTriangleIterator returns 9 values
// {x1,y1,z1,x2,y2,z2,x3,y3,z3}
// iFaceObject is a pointer to an object that defines the face, it is signed void* to match all types.
// oTrName and oVtxName give a char* representing the name that may differ from a chronological number (nb of
// iterations), but corresponds to whatever semantics iFaceObject is assumed to stick to.
// *oNbNormals is the number of normal vectors if oNbNormals is not a null pointer in input
// The number of normals returned will be null if precise normals are not available
// If they are available, they can be retrieved in oNormals[] array (size = 3 * (*oNbNormals))
typedef float * (*FaceTriangleIterator)(void * iFaceObject, void *& ioIterData, char *& oTrName, int & oOrientation);
typedef float * (*FaceVertexIterator)(void * iFaceObject, void *& ioIterData, char *& oVtxName, int * oNbNormals, float *& oNormals);

// Iterating on bounding bars gives 6 float: BdVertex1(x,y,z), BdVertex2(x,y,z)
// If oAuxPt is not null, the triangle (BdVertex1,BdVertex1,oAuxPt) is interior with
// respect to the face (for arrow and numbers positionning purposes)
typedef float * (*FaceBoundingBarIterator)(void * iFaceObject, void *& ioIterData, char *& oBdBarName,
                                           float *& oAuxPt, char *& oBdVtx1Name, char *& oBdVtx2Name);

// Give a name on a face
typedef char * (*GetFaceName)(void * iFaceObject, float * oAnchorPt);

// Deallocate methods should be used whenever an iteration is interrupted, to clean
// data held by "ioIterData"
typedef void (*DeallocateFaceTriangleIterData)(void *& ioIterData);
typedef void (*DeallocateFaceVertexIterData)(void *& ioIterData);
typedef void (*DeallocateFaceBoundingBarIterData)(void *& ioIterData);

// typedef for method used to build a dress up rep on a given face for debug
// 2nd and 3rd arguments are iterators of above defined types
typedef CAT3DRep *(*DressUpFaceMethod)(void* iFace,
                                       float*(*iTrIt)(void*iFace,void*&ioIter,char*&oName, int & oOrientation),
                                       float*(*iVtIt)(void*iFace,void*&ioIter,char*&oName,int*oNbNormals,float*&oNormals),
                                       float*(*iBdBarIt)(void*iFace,void*&ioIter,char*&oName,float*&oAuxPt,char*&oBdVtx1Name,char*&oBdVtx2Name),
                                       char*(*iGetFaceName)(void*iFace,float*oAnchorPt),
                                       int iShowVtxNames,
                                       int iShowTriangleNames,
                                       int iShowTrianglesArrows,
                                       int iShowBdBars,
                                       int iShowBars,
                                       int iDisplayFaceName,
                                       int iDisplayVerticesNormals);

#endif
