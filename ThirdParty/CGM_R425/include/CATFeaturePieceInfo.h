#ifndef CATFeaturePieceInfo_h
#define CATFeaturePieceInfo_h

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"

#include "CATCGMVirtual.h"

#include "ListPOfCATFace.h"

// Forward declare all the classes in the hierarchy
class CATFeaturePieceInfoCylinder;
class CATFeaturePieceInfoCone;
class CATFeaturePieceInfoPlane;
class CATFeaturePieceInfoTorus;

/**
 * Base class used to represent a feature piece.
 *
 * <b>Role:</b>Objects of this class are owned by <tt>CATFeaturePiece</tt> objects, 
 * which serve as smart pointers to these features. Clients can get pointers to 
 * these objects from the <tt>CATFeaturePiece</tt> objects. These pointers will be 
 * valid as long as their owning <tt>CATFeaturePiece</tt> objects are alive. Clients 
 * should not call delete on these pointers.
 **/
class ExportedByCATGMModelInterfaces CATFeaturePieceInfo : public CATCGMVirtual
{
public:
	CATCGMNewClassArrayDeclare;

   /**
    * Destructor
    */
	virtual ~CATFeaturePieceInfo();

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoCylinder</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoCylinder</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoCylinder* GetAsCATFeaturePieceInfoCylinder() const {return NULL;}

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoCone</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoCone</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoCone* GetAsCATFeaturePieceInfoCone() const {return NULL;}

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoPlane</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoPlane</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoPlane* GetAsCATFeaturePieceInfoPlane() const {return NULL;}

   /**
	 * Returns a pointer to an object of <tt>CATFeaturePieceInfoTorus</tt> type if this object can be cast to that type.
	 * @return 
	 * A pointer to the <tt>CATFeaturePieceInfoTorus</tt> object if the cast is valid; NULL if the cast is invalid.
    */
	virtual const CATFeaturePieceInfoTorus* GetAsCATFeaturePieceInfoTorus() const {return NULL;}

	/**
	* Returns the faces of this feature piece.
	* @param oFaces
	* The faces of the feature piece.
	**/
	virtual void GetFaces(CATLISTP(CATFace) & oFaces) const=0;

protected:
	// Only derived classes should use this constructor to create a 'concrete' CATFeaturePieceInfo object
	CATFeaturePieceInfo();

private:
	// forbid copying
	CATFeaturePieceInfo(CATFeaturePieceInfo const& other);
	CATFeaturePieceInfo& operator=(const CATFeaturePieceInfo &iOneOf);
};

#endif
