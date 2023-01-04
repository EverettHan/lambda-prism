#ifndef CATFeaturePieceInfoCylinder_h
#define CATFeaturePieceInfoCylinder_h

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"

#include "CATFeaturePieceInfo.h"

#include "ListPOfCATFace.h"

class CATMathLine;
/**
 * Class used to represent a feature piece that describes a cylinder.
 *
 * <b>Role:</b>Objects of this class are owned by <tt>CATFeaturePiece</tt> objects, 
 * which serve as smart pointers to these features. Clients can get pointers to 
 * these objects from the <tt>CATFeaturePiece</tt> objects. These pointers will be 
 * valid as long as their owning <tt>CATFeaturePiece</tt> objects are alive. Clients 
 * should not call delete on these pointers.
 **/
class ExportedByCATGMModelInterfaces CATFeaturePieceInfoCylinder : public CATFeaturePieceInfo
{
public:
	CATCGMNewClassArrayDeclare;

   /**
    * Destructor
    */
	virtual ~CATFeaturePieceInfoCylinder();

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoCylinder</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoCylinder</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoCylinder* GetAsCATFeaturePieceInfoCylinder() const {return this;}

	/**
	* Returns the parameters of this cylindrical feature piece.
	* @param oAxis
	* The axis of the cylinder.
	* @param oRadius
	* The radius of the cylinder.
	**/
	virtual void GetCylinderParameters(CATMathLine & oAxis, double & oRadius) const=0;

protected:
	CATFeaturePieceInfoCylinder();
private:
	// forbid copying
	CATFeaturePieceInfoCylinder(CATFeaturePieceInfoCylinder const& other);
	CATFeaturePieceInfoCylinder& operator=(const CATFeaturePieceInfoCylinder &iOneOf);

};

#endif
