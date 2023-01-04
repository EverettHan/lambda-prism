#ifndef CATFeaturePieceInfoTorus_h
#define CATFeaturePieceInfoTorus_h

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"

#include "CATFeaturePieceInfo.h"

#include "ListPOfCATFace.h"
#include "CATMathConstant.h"

class CATMathVector;
class CATMathPoint;
/**
 * Class used to represent a feature piece that describes a torus.
 *
 * <b>Role:</b>Objects of this class are owned by <tt>CATFeaturePiece</tt> objects, 
 * which serve as smart pointers to these features. Clients can get pointers to 
 * these objects from the <tt>CATFeaturePiece</tt> objects. These pointers will be 
 * valid as long as their owning <tt>CATFeaturePiece</tt> objects are alive. Clients 
 * should not call delete on these pointers.
 **/
class ExportedByCATGMModelInterfaces CATFeaturePieceInfoTorus : public CATFeaturePieceInfo
{
public:
	CATCGMNewClassArrayDeclare;

   /**
    * Destructor
    */
	virtual ~CATFeaturePieceInfoTorus();

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoTorus</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoTorus</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoTorus* GetAsCATFeaturePieceInfoTorus() const {return this;}

	/**
	* Returns the parameters of this toric feature piece.
	* @param oCenter
	* The center of the torus.
	* @param oNormal
	* The normal direction of the torus.
	* @param oMajorRadius
	* The major radius of the torus.
	* @param oMinusRadius
	* The minor radius of the torus.
	**/
	virtual void GetTorusParameters(CATMathPoint & oCenter, CATMathVector & oNormal,
									double & oMajorRadius, double & oMinusRadius) const=0;

protected:
	CATFeaturePieceInfoTorus();
private:
	// forbid copying
	CATFeaturePieceInfoTorus(CATFeaturePieceInfoTorus const& other);
	CATFeaturePieceInfoTorus& operator=(const CATFeaturePieceInfoTorus &iOneOf);

};

#endif
