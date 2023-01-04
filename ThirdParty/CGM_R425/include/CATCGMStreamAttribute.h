#ifndef CATCGMStreamAttribute_H
#define CATCGMStreamAttribute_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U2
 */ 


class CATCGMAttrId;
class CATCGMAttributeDef;
class CATCGMStream;
class CATICGMObject;
class CATCGMStreamAttrData;

#include "YP0LOGRP.h"
#include "CATCGMAttribute.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMStreamVersion.h"


/**
 * Class representing the persistent attribute that can be pointed to by one or several CATICGMObject.
 * <b>Role</b>: This class allows you to stream the attribute with the objects that are pointed them.
 * If you want to create your own class, you overload the methods that are written as mandatory.
 * If you want that your attribute points objects, use @href CATCGMAttribute#AddLink . These objects
 * will be automatically streamed. To put an attribute on a object, use @href CATICGMObject#PutAttribute .
 * <b>Rule</b>When implementing by overloading this class, expected mandatory material in software delivery 
 *   is the logical domain declaration <tt>MyDomainId</tt> adhesion, such as :
 *<pre>
 * #include "TIE_CATICGMDomainBinder.h"
 * AppDef(MyDomainId);
 *</pre>
 *Do not forget to update of your associated ObjectModeler dictionnary.
 */
class ExportedByYP0LOGRP CATCGMStreamAttribute :public CATCGMAttribute 
{
  CATCGMDeclareAttribute (CATCGMStreamAttribute, CATCGMAttribute);
public :
  
/**
 * Translates <tt>this</tt> CATCGMStreamAttribute into a byte sequence 
 * that can be later saved.
 * <br>Mandatory method.
 * @param ioStream
 * The stream.
 */
  virtual void Stream(CATCGMStream & ioStream) const=0;

/**
 * Copies into <tt>this</tt> CATCGMStreamAttribute, the translation of a byte sequence 
 * that has been previoulsy streamed for an CATCGMStreamAttribute.
 * <br>Mandatory method.
 * @param ioStream
 * The stream.
 */
  virtual void   UnStream( CATCGMStream& ioStr ) = 0 ;

/**
 * Attaches CATICGMObjects to <tt>this</tt> CATCGMStreamAttribute.
 * @param iObject
 * A pointer to the CATICGMObject that will be pointed to.
 */ 
  void AddLink    (CATICGMObject*                 iObject);

 /**
 * Removes the link from <tt>this</tt> CATCGMStreamAttribute to a CATICGMObjects.
  * @param iObject
 * A pointer to the CATICGMObject that will be not pointed to anymore.
 */
  void RemoveLink (CATICGMObject*                 iObject);

/** 
*  Replaces all the links from <tt>this</tt> CATCGMStreamAttribute to a CATICGMObjects.
 * @param iObjects
 * A list of pointers to the CATICGMObjects that will be pointed to. The already existing
 * links are removed.
 */
  void SetLinks   (const CATLISTP(CATICGMObject)& iObjects);

/** 
*  Retrieves all the links from <tt>this</tt> CATCGMStreamAttribute to a CATICGMObjects.
* @param ioLinkedObjects
* A list of pointers to the linked CATICGMObjects.
*/
  void GetLinks   (CATLISTP(CATICGMObject)&       ioLinkedObjects);

/** @nodoc */
    virtual short IsDirty(); // For Debug Purpose

 /** @nodoc */
 virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

/**
 * Default constructor.
 */
  CATCGMStreamAttribute();
  virtual ~CATCGMStreamAttribute();

 /** @nodoc */
 void SetMustStreamForStreamCompact(int iMustStreamForStreamCompact = 1);

 /** @nodoc */
 int MustStreamForStreamCompact() const;

private:
  CATCGMStreamAttrData* _Data;
};

/**
 * Casts a CATCGMattribute into a CATCGMStreamAttribute.
 * @param iAttr
 * The attribute to cast.
 * @param ioStrAttr
 * The streamed attribute if possible.
 */
extern ExportedByYP0LOGRP void CastTo(CATCGMAttribute * iAttr, CATCGMStreamAttribute *& ioStrAttr);

#endif
