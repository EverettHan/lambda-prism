#ifndef CATTessTool_H
#define CATTessTool_H

// COPYRIGHT DASSAULT SYSTEMES  2001

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"
#include "ListPOfCATCell.h"
class CATBody;


typedef float cat_fpoint [3];
typedef int   cat_triple [3];


/**
 * Class defining a tessellation operator of a body.
 * This class is used by the @href CATTopSimulation class.
 * It is oriented real-time computation, the computation can be called several times
 * and do something only if object-state are modified.
 * In our case, if the body to tessellate is unchanged like the tessellation parameters
 * the computation must be very fast.
 * <br> This operator computes a discretized geometry on the skin of a body, as triangles and bars.
 * The extremities of the bars are called points. Three parameters tune the tessellation result:
 * <dl>
 * <ul>
 * <li> Create an operator instance,
 * <li> ComputeTessellation
 * <li> Recover the results by the means of the GetTessellation
 * <li> ComputeTessellation (again)
 * <li> Recover the results (again)
 * <li> ....
 * <li> Delete the operator instance. 
 * The deletion of the operator deletes the result arrays.
 * <br>
 * Warning : There is not implementation of this class at the Topological Level
 *           Implementation can be found at the Tesselation Level
 *           (See also CATTessXXX)

 * </ul>
 */
class ExportedByCATGMModelInterfaces CATTessTool
{

public:
  virtual ~CATTessTool();

	/**
	* Perform (or retrieves) a tesselation.
	 *  @param iBody
	 *  The pointer to the body to tessellate.
	 *  @param iCells
	 *  The list of cells to tessellate.
	 *  @param iSag 
	 *  The maximum distance between a bar and the object to tessellate.
	 *  @param iStep 
	 *  The maximum length of a bar.
	 *
	 */
	virtual CATLONG32 ComputeTessellation(CATBody* iBody, CATLISTP(CATCell) * iCells, 
																	 const double iStep, const double iSag)=0;

/**
   * Retrieves the results associated with a topological face of the input body.
   * <br> All the outputs are allocated by the <tt>this</tt> CATTopSimulation,
   * and are deleted when the operator is deleted or when <tt>this</tt> is modified.
   * @param iFaceNumber
   *    The index to a deformed face.
   * @param oVertices
   *    The array <tt>[<tt>oVerticesArraySize</tt>]</tt> containing the coordinates of the face vertices: XYZXYZXYZ...
   * @param oVerticesArraySize
   *    The size, in float, of the <tt>oVertices</tt> array. Equal to three times the
   *    vertices number.
   *    If information on vertices is shared with another element,
   *    returned size for this parameter is equal to 0.
   * @param oNormals
   *    The array containing the normal coordinates. It is organized as <tt>oVertices</tt> : one vertex has exactly
   *    one normal at the same field entry.
   * @param oNormalsArraySize
   *    The size, in float, of the <tt>oNormal</tt> array. Equal to three times the number
   *    of normals.
   *    If information on normals is shared with another element,
   *    returned size for this parameter is equal to 0.
   * @param oTriangleIndices
   *    The array containing the vertices of the single triangles. Each of its field represents
   *    a vertex index, in the <tt>oVertices</tt> array.
   *    As the <tt>*oVertices</tt> array contains the XYZ coordinates for each
   *    vertex, the indices used to point the vertices are multiples of three.
   *    So, the first three indices of the <tt>oTriangleIndices</tt> array represent the indices of three vertices 
   *    of the the first single triangle.
   *    <pre>
   *
   *                 -----------------       
   *                |*oTriangleIndices[iface] |
   *                 -----------------
   *                |       i00       |   }
   *                |       i01       |   } triangle 0 defined by index i00, i01 and i02
   *                |       i02       |   }
   *                |        .        |
   *                |        .        |
   *                |       ij0       |   }
   *                |       ij1       |   } triangle j defined by index ij0, ij1 and ij2. 
   *                |       ij2       |   }
   *                |        .        |
   *                |        .        |
   *                 -----------------
   *
   *   </pre>
   *    For example, index <tt>ij0</tt> enables access to the face <tt>j</tt>-th single triangle first vertex,
   *    which coordinates are <tt>X = *oVertices[ij0]</tt>, <tt>Y = *oVertices[ij0+1]</tt> 
   *    and <tt>Z = *oVertices[ij0+2]</tt>, and
   *    which normal has coordinates <tt>Nx = *oNormals[ij0]</tt>, <tt>Ny = *oNormals[ij0+1]</tt> 
   *    and <tt>Nz = *oNormals[ij0+2]</tt>.
   * @param oNbTriangle
   *    The number of single triangles in the face. 
   * @param oTriangleStripIndices
   *    The array used to store the vertices of the triangle strips. Each field contains a
   *    vertex index, belonging to one of the strips, in the <tt>oVertices</tt> array.  As the
   *    <tt>oVertices</tt> array contains the XYZ coordinates for each
   *    vertex, the indices used to designate the vertices are multiples of three.
   *    <pre>
   *
   *
   *                   ----------------------
   *                  | oTriangleStripIndices[iface] |
   *                   ----------------------
   *                  |          i00         |   }
   *                  |          i01         |   } first triangle strip defined
   *                  |           .          |   } by the first n1 indices
   *                  |           .          |   }
   *                  |          i0n1        |   }
   *                  |           .          |
   *                  |           .          |
   *                  |           .          |   
   *                  |          ij0         |   }
   *                  |          ij1         |   }
   *                  |           .          |   } triangle strip j
   *                  |           .          |   } with nj vertices
   *                  |          ijnj        |   }
   *                   ----------------------
   *
   *
   *    </pre> 
   *    For example, index <tt>ij0</tt> allows you to access to the the first vertex of <tt>j</tt>-th strip of the face, 
   *    which coordinates are <tt>X = *oVertices[ij0]</tt>, <tt>Y = *oVertices[ij0 + 1]</tt> 
   *    and <tt>Z = *oVertices[ij0 + 2]</tt>, and
   *    which normal coordinates are <tt>Nx = *oNormals[ij0]</tt>, <tt>Ny = *oNormals[ij0 + 1]</tt> 
   *    and <tt>Nz = *oNormals[ij0 + 2]</tt>.
   * @param oNbTriangleStrip
   *    The number of triangle strips in the face.
   * @param oNbVertexPerTriangleStrip
   *    The array containing the number of vertices for each triangles strip of the face.
   *    The size of this array is equal to <tt>*oNbTriangleStrip</tt>. For example, the first strip
   *    has <tt>*oNbVertexPerTriangleStrip[0]</tt> vertices.
   *    <pre>
   *                --------------------------
   *               |*oNbVertexPerTriangleStrip[iface]|
   *                --------------------------
   *               |             n1           |
   *               |             .            |
   *               |             .            |   m = Number of triangle strips(*oNbTriangleStrip)
   *               |             nm           |   nm = number of vertices of the m-th strip. (*oNbVertexPerTriangleStrip[m]
   *                --------------------------    
   *
   *   </pre>
   * @param oTriangleFanIndices
   *    The array containing the vertices of triangle fans for the face. Each field contains a
   *    vertex index, belonging to one of the fans, in the <tt>oVertices</tt> array.  As the
   *    <tt>oVertices</tt> array contains the XYZ coordinates for each
   *    vertex, the indices used to designate the vertices are multiples of three.
   *    <pre>
   *
   *
   *                   ----------------------
   *                  | *oTriangleFanIndices[iface]  |
   *                   ----------------------
   *                  |          i00         |   }
   *                  |          i01         |   } first triangle fan defined
   *                  |           .          |   } by the first n1 indices
   *                  |           .          |   }
   *                  |          i0n1        |   }
   *                  |           .          |
   *                  |           .          |
   *                  |           .          |   
   *                  |          ij0         |   }
   *                  |          ij1         |   }
   *                  |           .          |   } triangle fan j
   *                  |           .          |   } with nj vertices
   *                  |          ijnj        |   }
   *                   ----------------------
   *
   *
   *    </pre> 
   *    For example, index <tt>ij0</tt> allows you to access to the first vertex of <tt>j<tt>-th fan of the face,
   *    which coordinates are <tt>X = *oVertices[ij0]</tt>, <tt>Y = *oVertices[ij0 + 1]</tt> and <tt>Z = *oVertices[ij0 + 2]</tt>, and
   *    which normal coordinates are <tt>Nx = *oNormals[ij0]</tt>, <tt>Ny = *oNormals[ij0 + 1]</tt> and <tt>Nz = *oNormals[ij0 + 2]</tt>.
   *    Each <tt>ij0</tt>, <tt>j</tt> in <tt>[0, jn]</tt>, represents the <tt>j</tt>-th fan center.
   * @param oNbTriangleFan
   *    Retrieves the number of face triangles fans.
   * @param oNbVertexPerTriangleFan
   *    Retrieves the array containing the number of vertices for each triangle fan of the face.
   *    The size of this array is equal to <tt>*oNbTriangleFan</tt>. For example, the first fan
   *    has <tt>*oNbVertexPerTriangleStrip[0]</tt> vertices.
   *    <pre>
   *                --------------------------
   *               | *oNbVertexPerTriangleFan |
   *                --------------------------
   *               |             n1           |
   *               |             .            |
   *               |             .            |   m = Number of triangle fans(*oNbTriangleFan)
   *               |             nm           |   nm = number of vertices of the m-th fan. (*oNbVertexPerTriangleFan[m]
   *                --------------------------    
   *
   *   </pre>
   */
	virtual void GetTessellation(int&            oNumberOfFaces,
															 cat_fpoint**&   oVertices,
															 cat_fpoint**&   oNormals,
															 cat_triple**&   oTriangleIndices,
															 int   **&    oTriangleStripIndices,
															 int   **&    oNbVertexPerTriangleStrip,
															 int   **&    oTriangleFanIndice,
															 int   **&    oNbVertexPerTriangleFan,
															 int   *&     oNumberOfVerticies, 
															 int   *&     oNbTriangle, 
															 int   *&     oNbTriangleStrip,
															 int   *&     oNbTriangleFan) const=0;

protected:
    CATTessTool();

private:
    CATTessTool(const CATTessTool & iToCopy);
    void operator = (const CATTessTool & iToCopy);


};
#endif

