//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Class		:		CATTopImprintCellAttribute
//	Creation	:		11/12/2017
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

#ifndef CATTopImprintCellAttribute_H
#define CATTopImprintCellAttribute_H



#include "CATErrorDef.h"
#include "CATCGMStreamAttribute.h"
#include "CATCGMImprintAttribute.h"
#include "CATCGMStreamClonableAttribute.h"
#include "CATCollec.h"
#include "ExportedByCATTopologicalObjects.h"


class CATCGMContainer;
class CATCGMImprintAttribute;
class CATCGMObject;
class CATCell;
class CATCGMOutput;
class CATCGMStream;
class CATCloneManager;
class CATExtClonableManager;
class CATLISTP(CATCell); 



/** @nodoc @nocgmitf */
/**
* Implement class of Imprint Attribute for Cell. 
* An Imprint attribute is ..............................................
* ......................................................................
* ......................................................................
* ......................................................................
*/

class ExportedByCATTopologicalObjects CATTopImprintCellAttribute : public CATCGMImprintAttribute
{

   CATCGMDeclareAttribute (CATTopImprintCellAttribute, CATCGMImprintAttribute);

public:

   /** @nodoc @nocgmitf */
   static CATTopImprintCellAttribute * CreateCATTopImprintCellAttribute(CATCGMContainer *piCGMContainer);

   /** @nodoc @nocgmitf */
   //static CATCGMImprintAttribute *CreateCATTopImprintCellAttribute(CATLISTP(CATCell) &iListOfCell);


   /** @nodoc @nocgmitf */
   /**
   * reference the CGM container that will contain Imprinted edges.
   * @param piCellToImprint
   *    Cell to imprint.
   *
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   *
   */
   //HRESULT AddImprintCell(CATCell *piCellToImprint);

   /** @nodoc @nocgmitf */
   /**
   * Translates <tt>this</tt> CATCGMStreamAttribute into a byte sequence 
   * that can be later saved.
   * <br>Mandatory method.
   * @param ioStream
   * The stream.
   * Rmk : No data carried by <tt>this</tt> hence no data to stream
   */

   void Stream   (CATCGMStream& Str) const;

   /** @nodoc @nocgmitf */
   /**
   * Copies into <tt>this</tt> CATCGMStreamAttribute, the translation of a byte sequence 
   * that has been previoulsy streamed for an CATCGMStreamAttribute.
   * <br>Mandatory method.
   * @param ioStream
   * The stream.
   * Rmk : No data carried by <tt>this</tt> hence no data to unstream
   */

   void UnStream (CATCGMStream& Str);


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


   /** @nodoc @nocgmitf */
   void Dump( CATCGMOutput & os );
      
private:

   //==========================================================================================================================
   // DATA
   //==========================================================================================================================

   //CATCGMHashTable   *_pHashTabOfImprintCell;
   //CATCGMContainer  *_pCGMContainer;

   //==========================================================================================================================
   // Internal methods  
   //==========================================================================================================================
   /** @nodoc @nocgmitf */
   /**
   * reference the CGM container that will contain Imprinted edges.
   * @param piCGMContainer
   *    The container.
   *
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   *
   */
   //HRESULT SetContainer(CATCGMContainer *piCGMContainer);

   //==========================================================================================================================
   // Constructors  
   //==========================================================================================================================
   CATTopImprintCellAttribute();

   CATTopImprintCellAttribute(const CATTopImprintCellAttribute& iImprintAttribute);

   //==========================================================================================================================
   // Destructor  
   //==========================================================================================================================

   virtual ~CATTopImprintCellAttribute();

   //==========================================================================================================================
};



#endif

