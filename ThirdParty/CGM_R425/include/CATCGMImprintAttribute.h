//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Class		:		CATCGMImprintAttribute
//	Creation	:		10/01/2012
//
//
//	Synopsis	:		
//					
//	
//
//
//	Authors		:  KY1
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CATCGMImprintAttribute_H
#define CATCGMImprintAttribute_H


class CATCGMObject;
class CATCGMOutput;
class CATCGMStream;
class CATCloneManager;
class CATExtClonableManager;
 

//Pour l'export
//#include "CATGMModelInterfaces.h"
#include "ExportedByGeometricObjects.h"
#include "CATErrorDef.h"
#include "CATCGMStreamAttribute.h"
#include "CATCGMStreamClonableAttribute.h"

 
/** @nodoc @nocgmitf */
/**
 * Interface class for Imprint Attribute (refers to CATGNImprintAttribute) 
 * An Imprint attribute is ..............................................
 * ......................................................................
 * ......................................................................
 * ......................................................................
 */

class ExportedByGeometricObjects CATCGMImprintAttribute : public CATCGMStreamClonableAttribute
{

  CATCGMDeclareAttribute (CATCGMImprintAttribute, CATCGMStreamClonableAttribute);

public:

   CATCGMImprintAttribute();

   ~CATCGMImprintAttribute();
  

/** @nodoc @nocgmitf */
/**
 * Translates <tt>this</tt> CATCGMStreamAttribute into a byte sequence 
 * that can be later saved.
 * <br>Mandatory method.
 * @param ioStream
 * The stream.
 * Rmk : No data carried by <tt>this</tt> hence no data to stream
 */

void Stream   (CATCGMStream& Str) const = 0;

/** @nodoc @nocgmitf */
/**
 * Copies into <tt>this</tt> CATCGMStreamAttribute, the translation of a byte sequence 
 * that has been previoulsy streamed for an CATCGMStreamAttribute.
 * <br>Mandatory method.
 * @param ioStream
 * The stream.
 * Rmk : No data carried by <tt>this</tt> hence no data to unstream
 */

void UnStream (CATCGMStream& Str) = 0 ;


/** @nodoc @nocgmitf */
/**
* Manage Report of attributes.
* @param iClonableManager
*    may be context of operator.
* @param Origin
*    Original Holder of attribute.
* @param Destination
*    Destination Holder of attribute.
*/
CATCGMAttribute * ReportClonableAttributes(CATExtClonableManager* iClonableManager, CATICGMObject  * iOrigin, CATICGMObject  * iDestination);


//==========================================================================================================================
// DATA
//==========================================================================================================================
private:

   // No Data

   //==========================================================================================================================
   // Constructors  
   //==========================================================================================================================
   CATCGMImprintAttribute(const CATCGMImprintAttribute& iSeamAttribute);

   

//==========================================================================================================================
};
#endif
