#ifndef CATFeaturePieceInfoPlane_h
#define CATFeaturePieceInfoPlane_h

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"

#include "CATFeaturePieceInfo.h"

#include "ListPOfCATFace.h"

class CATMathVector;
class CATMathPoint;
/**
 * Class used to represent a feature piece that describes a plane.
 *
 * <b>Role:</b>Objects of this class are owned by <tt>CATFeaturePiece</tt> objects, 
 * which serve as smart pointers to these features. Clients can get pointers to 
 * these objects from the <tt>CATFeaturePiece</tt> objects. These pointers will be 
 * valid as long as their owning <tt>CATFeaturePiece</tt> objects are alive. Clients 
 * should not call delete on these pointers.
 **/
class ExportedByCATGMModelInterfaces CATFeaturePieceInfoPlane : public CATFeaturePieceInfo
{
public:
	CATCGMNewClassArrayDeclare;

   /**
    * Destructor
    */
	virtual ~CATFeaturePieceInfoPlane();

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoPlane</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoPlane</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoPlane* GetAsCATFeaturePieceInfoPlane() const {return this;}

	/**
	* Returns the parameters of this planar feature piece.
	* @param oOrigin
	* A point on the plane.
	* @param oNormal
	* The normal direction of the plane.
	**/
	virtual void GetPlaneParameters(CATMathPoint & oOrigin, CATMathVector & oNormal) const=0;

protected:
	CATFeaturePieceInfoPlane();
private:
	// forbid copying
	CATFeaturePieceInfoPlane(CATFeaturePieceInfoPlane const& other);
	CATFeaturePieceInfoPlane& operator=(const CATFeaturePieceInfoPlane &iOneOf);

};

#endif
