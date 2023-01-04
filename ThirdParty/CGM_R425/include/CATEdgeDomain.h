#ifndef CATEdgeDomain_H
#define CATEdgeDomain_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATDomain.h"    
class CATEdge;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATEdgeDomain ;
#else
extern "C" const IID IID_CATEdgeDomain ;
#endif

/**
* Base interface representing a set of connected edges.
* Derived interfaces are supplied, such as:
* <dl><dt><tt>CATWire</tt></dt><dd> A set of connected edges
* of a body or a volume.
* <dt><tt>CATLoop</tt></dt><dd> A set of connected
* edges of a face.</dl>
*/

class ExportedByCATGMModelInterfaces CATEdgeDomain : public CATDomain
{
  CATDeclareInterface;
  
public :
  
  /**
    * Adds an edge in <tt>this</tt> CATEdgeDomain at a specified position.
		* <br>The edges of the CATEdgeDomain must be given contiguously. If you want
		* to append an edge at the end of the CATEdgeDomain, you can use the @href CATDomain#AddCell method.
		* @param iEdge
		* The pointer to the edge to insert.
		* @param iPosition
		* The rank (beginning at 1) of the edge to insert inside <tt>this</tt> CATEdgeDomain.
		* @param iOrientation
		* The relative orientation of <tt>iEdge</tt>with regards to <tt>this</tt> CATEdgeDomain.
    */
   virtual void InsertEdge(CATEdge* iEdge, CATULONG32  iPosition, CATOrientation iOrientation=CATOrientationPositive ) = 0;
 
};

CATDeclareHandler(CATEdgeDomain,CATDomain);

#endif // CATEdgeDomain_H
