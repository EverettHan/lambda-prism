#ifndef CATFeaturePieceInfoCone_h
#define CATFeaturePieceInfoCone_h

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"

#include "CATFeaturePieceInfo.h"

#include "ListPOfCATFace.h"
#include "CATMathConstant.h"

class CATMathLine;
class CATMathPoint;
/**
 * Class used to represent a feature piece that describes a cone.
 *
 * <b>Role:</b>Objects of this class are owned by <tt>CATFeaturePiece</tt> objects, 
 * which serve as smart pointers to these features. Clients can get pointers to 
 * these objects from the <tt>CATFeaturePiece</tt> objects. These pointers will be 
 * valid as long as their owning <tt>CATFeaturePiece</tt> objects are alive. Clients 
 * should not call delete on these pointers.
 **/
class ExportedByCATGMModelInterfaces CATFeaturePieceInfoCone : public CATFeaturePieceInfo
{
public:
	CATCGMNewClassArrayDeclare;

   /**
    * Destructor
    */
	virtual ~CATFeaturePieceInfoCone();

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoCone</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoCone</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoCone* GetAsCATFeaturePieceInfoCone() const {return this;}

	/**
	* Returns the parameters of this conical feature piece.
	* @param oBaseCenter
	* The center of the base of the conical section.
	* @param oTopCenter
	* The center of the top of the conical section.
	* @param oBottomRadius
	* The radius of the base of the conical section.
	* @param oTopRadius
	* The radius of the top of the conical section.
	**/
	virtual void GetConeParameters(CATMathPoint & oBaseCenter, CATMathPoint & oTopCenter,
									double & oBottomRadius, double & oTopRadius) const=0;

protected:
	CATFeaturePieceInfoCone();
private:
	// forbid copying
	CATFeaturePieceInfoCone(CATFeaturePieceInfoCone const& other);
	CATFeaturePieceInfoCone& operator=(const CATFeaturePieceInfoCone &iOneOf);

};

#endif
