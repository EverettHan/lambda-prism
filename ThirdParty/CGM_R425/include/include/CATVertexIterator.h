#ifndef CATVertexIterator_H
#define CATVertexIterator_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"
#include "CATCell.h"    
#include "CATCGMVirtual.h"

class CATDomain;
class CATBody;
class CATVertex;
class CATEdge;
class CATFace;

/**
* Class defining an iterator that recursively scans (inside the context 
* of a specified body) the cells that bound a vertex.
*  <br>  The input vertex must belong to the specified Body. 
*    The returned bounded cells belong to the specified body.
*<br>
* This means that this class performs a radial iteration around the vertex,
*    each call to the <tt>Next</tt> method returning a new cell 
*   (whatever its dimension) that can be :
* <ul>
*     <li> an edge (bounded by the vertex)
*     <li> a face (bounded by a domain VertexInFace)
*     <li> a face (bounded by an edge that is itself bounded by the vertex)
* </ul>
* For instance: the iterator on the 
*    corner of a cube returns by iteration six cells (of the same shell):
*         Edge1, Face1, Edge2, Face2, Edge3, Face3.
*
*/
class ExportedByCATGMModelInterfaces CATVertexIterator: public CATCGMVirtual
{
  public :
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Defines <tt>this</tt> vertex iterator.
 * @param iVertex
 * The pointer to the vertex around which the iteration is done. <tt>iVertex</tt>
 * must belong to <tt>iBody</tt>.
 * @param iBody
 * The pointer to the body inside which the iteration is done. As cells can be shared
 * by several bodies, this argument precises the context of the iteration.
 */
  virtual void  SetVertex(CATVertex *iVertex, CATBody *iBody) = 0;


/**
 * Initializes the iterator.
 * <br> Allows you to run again the iterations.
 */
  virtual void Reset()=0;
  
	/**
	 * Skips to the next cell of <tt>this</tt> iterator.
	 * @param ioSide
	 * The side attribute of </tt>this</tt> with regards to the returned cell.
	 * If <tt>NULL</tt>, this attribute is not returned.
	 * @param ioDomain
	 * The pointer to the domain to which the returned cell belongs to.
	 * If <tt>NULL</tt>, this argument is not output.
	 * @return
	 * The pointer to the next cell of the iterator. <tt>NULL</tt> after the last cell.
	 * <br>Sample:
	 *<pre>CATVertexIterator iter;
	 * iter.SetVertex(AVertex, InsideThisBody);
	 * iter.Reset();
	 * // to only retrieve the next cell
	 * CATCell * nextcell=iter.Next(NULL,NULL);
	 * // to retrieve the cell and more information
	 * CATSide side;
	 * CATDomain * domain;
	 * nextcell=iter.Next(&side,&domain);
	 * </pre>
	 */
  virtual CATCell* Next(CATSide * ioSide=NULL, CATDomain ** ioDomain=NULL )=0;

   virtual ~CATVertexIterator();

	 /**
	  * Duplicates <tt>this</tt> CATVertexIterator.
		* @return
		* A pointer to the duplicated iterator.
		*/

  virtual CATVertexIterator* Duplicate() const = 0;
  
	/**
	 * Default constructor.
   * @param iTopData
   * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
   */
    CATVertexIterator(const CATTopData * iData = 0);

		/**
		* Assignment operator.
		*/
    CATVertexIterator& operator=(const CATVertexIterator& iToCopy);

		/**
		 * Copy constructor.
		 */
    CATVertexIterator(const CATVertexIterator& iToCopy);

  /**
	 * Returns a pointer to the body inside which <tt>this</tt> iterator iterates.
	 * @return
	 * The pointer to the body.
	 */
  virtual CATBody*    GetBody() const = 0;

	/**
	 * Returns a pointer to the vertex around which <tt>this</tt> iterator iterates.
	 * @return
	 * The pointer to the vertex.
	 */
  virtual CATVertex*  GetVertex() const = 0;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Defines the initial cell of the iteration.the Iteration will start with firstEdge, 
 * second times, the iteration will gives back startFace,
 * third times, the other Edge bounded by Vertex and bounding of startFace 
 */
  virtual void Init(CATEdge *iFirstEdge, CATFace *iStartFace) = 0;

};
#endif 
