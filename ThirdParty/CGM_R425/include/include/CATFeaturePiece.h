#ifndef CATFeaturePiece_H
#define CATFeaturePiece_H

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"

#include "CATCGMReferenceClassImplHolder.h"
#include "CATBoolean.h"

class CATFeaturePieceInfo;
class CATFeaturePieceImpl;

/**
 * Class used as a smart pointer to feature piece objects derived from <tt>CATFeaturePieceInfo</tt>.
 *
 * <b>Role:</b>This class is designed with "reference-class" semantics; it is intended to 
 * be owned and passed by value, rather than being allocated on the heap.
 * To minimize memory consumption, use these objects as locally as possible.  
 **/
class ExportedByCATGMModelInterfaces CATFeaturePiece
{
public:
	/**
	* Default constructor.
	**/
	CATFeaturePiece();
	/**
	* Destructor.
	*/
	~CATFeaturePiece();
	/**
	* Copy constructor. 
	**/
	CATFeaturePiece(CATFeaturePiece const& iOther);
	/**
	* Assignment operator.
	**/
	CATFeaturePiece& operator=(CATFeaturePiece const& iOther); 

	/**
	* Returns a pointer to an object that encapsulates information about this feature piece.
	* <b>Role:</b> This pointer can be queried for type and cast to the appropriate concrete <tt>CATFeaturePieceInfo</tt> type.
	* Clients should not call <tt>delete</tt> on this pointer because it is owned by this object.
	* @return 
	* The <tt>CATFeaturePieceInfo</tt> pointer.
	**/
	CATFeaturePieceInfo const* GetFeaturePieceInfo() const;

	/**
	* @nodoc
	* For internal use only
	*/
	CATBoolean operator==(CATFeaturePiece const& iOther) const;
	/**
	* @nodoc
	* For internal use only
	*/
	CATBoolean operator!=(CATFeaturePiece const& iOther) const;
	/**
	* @nodoc
	* For internal use only
	*/
	CATFeaturePiece( CATFeaturePieceImpl* ipImpl );

protected:
private:
	CATCGMReferenceClassImplHolder _implHolder;
	DECLARE_USE_COUNTED_GET_IMPL_METHODS(CATFeaturePiece);
};
#endif
