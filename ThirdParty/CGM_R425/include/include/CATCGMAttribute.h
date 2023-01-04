#ifndef CATCGMAttribute_H
#define CATCGMAttribute_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U2
*/ 

class CATCGMAttributeDef;
class CATCGMStream;
class CATCGMStreamCGMImpl;
class CATICGMObject;
class CATCGMContainer;
class CATCGMOutput;
class CATExtClonableManager;
 
#include "YP0LOGRP.h"
#include "CATListOfCATCGMAttribute.h"
#include "CATCGMAttrId.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATIACGMLevel.h"

#if defined(_MOBILE_SOURCE) || defined(_DARWIN_SOURCE) || defined(_LINUX_SOURCE) || defined(_AIX_SOURCE) && (__xlC__ >= 0x0500)
/** @nodoc */
extern ExportedByYP0LOGRP CATCGMAttribute * CATCGMAttribute_CreateAttribute () ;
#endif

class CATGeometry;



//-----------------------------------------------------------------------------
/**
* Class representing the attribute that can be pointed to by one or several CATICGMObject.
* <br>The attribute are characterized by 
* <ul> <li> A class name
*       <li> An application name: the logical name of the physical load module containing the
* class
*       <li>A version number
* </ul>
* The identifier is defined by the use of the macro <tt>UIDName(MyAttributeClassName)</tt>.
*<br>For streamable attribute, use @href CATCGMStreamAttribute.
*<br>For declaration and implementation of your own attributes,
* use macros @href CATCGMDeclareAttribute and @href CATCGMImplAttribute.
*/
class ExportedByYP0LOGRP CATCGMAttribute  : public CATCGMVirtual
{
public :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  virtual                       ~CATCGMAttribute ();
  /**
  * Creates an attribute of a given identifier.
  * @param iId
  * The attribute identifier
  * @return
  * The created attribute
  */
  static       CATCGMAttribute * CreateAttribute (const CATCGMAttrId * iId);
  
  /**
  * Tests whether <tt>this</tt> CATCGMAttribute is persistent.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the attribute can be streamed (i.e. persistent), <tt>0</tt> otherwise.
  */
  virtual       int              IsPersistent    ();
  
 /**
 * Returns the identifier of <tt>this</tt> CATCGMAttribute.
 * @return
 * The identifier.
 *<br>Do not overload this method.
 * Use macros <tt>CATCGMDeclareAttribute</tt> and <tt>CATCGMImplAttribute</tt>.
  */
  virtual const CATCGMAttrId   * GetCGMAttrId    () const =0; 
  
  /**
  * Tests whether <tt>this</tt> CATCGMAttribute is of a given type (or a derived type).
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the attribute identifier is <tt>iId</tt>, <tt>0</tt> otherwise.
  */
                int              IsATypeOf       (const CATCGMAttrId * iId); 
  
  /**
  * Adds <tt>1</tt> to the count of CATICGMObjects pointing to <tt>this</tt> CATCGMAttribute.
  * @return
  * The number of CATICGMObjects pointing to <tt>this</tt> CATCGMAttribute.
  */
                CATULONG32       AddAttrRef      ();
 
  /**
  * Removes <tt>1</tt> to the count of CATICGMObjects pointing to <tt>this</tt> CATCGMAttribute.
  * @return
  * The number of CATICGMObjects still pointing to <tt>this</tt> CATCGMAttribute.
  */
                CATULONG32       ReleaseAttrRef  ();

  /**
  * Returns the number of CATICGMObjects pointing to <tt>this</tt> CATCGMAttribute.
  * @return
  * The number of CATICGMObjects.
  */
  INLINE        CATULONG32       GetNbAttrRef    () const;

  
  /**
  * Equality operator.
  * @return
  * The result of the test.
  * <tt>1</tt> if true, <tt>0</tt> otherwise.
  */
                CATLONG32        operator ==     (const CATCGMAttribute &iToCompare);
  
  /**
  * Inequality operator.
  * @return
  * <tt>1</tt> if they are different, <tt>0</tt> otherwise.
  */
                CATLONG32        operator !=     (const CATCGMAttribute &iToCompare);


  protected :

    /**
    * Checks whether two attributes of the same identifier are equal.
    * <br>Called in the == and =! operators.
    * @return
    * <tt>1</tt> if they are, <tt>0</tt> otherwise.
    */
  virtual       CATLONG32        Compare         (const CATCGMAttribute & iToCompare);

  public :



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //  Attribute's reporting : Limited availability    
  //     restricted to entities'holder : Body/Face/Edge/Vertex holder
  //     but genuine to Clone/TransfoManager (and partially to SmartDuplicator) services
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /**
  * Tests whether <tt>this</tt> CATCGMAttribute is manageable by Clone managements.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the attribute can be managed (i.e. implements ReportClonableAttributes), <tt>0</tt> otherwise.
  */
  virtual       int              IsClonableAttribute();
  
   /**
   * @nodoc limited availability low-level attributes reporting  
   * Manage Report of attributes.
   * @param iClonableManager
   *    may be context of operator.
   * @param Origin
   *    Original Holder of attribute.
   * @param Destination
   *    Destination Holder of attribute.
   */
   virtual      CATCGMAttribute * ReportClonableAttributes(CATExtClonableManager* iClonableManager,
                                                           CATICGMObject        * iOrigin         ,
                                                           CATICGMObject        * iDestination    )  ;
   /**
   * @nodoc limited availability low-level attributes reporting  
   * Set ReportedClonable Attributes.
   */
   INLINE       void              SetReportedClonableAttributes() ;

   /**
   * @nodoc limited availability low-level attributes reporting  
   * Set ReportedClonable Attributes.
   */
   INLINE       CATBoolean        IsReportedAsClonableAttributes() const;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /** @nodoc @nocgmitf */
  virtual       void              Dump           (CATCGMOutput & os ); // For Debug Purpose
  
  /** @nodoc */
  virtual       short             IsDirty        ();                   // For Debug Purpose
  
  /** @nodoc */
                CATCGMConstrAttr  GetAttrFunc    () const;             // get the construction function


  /** @nodoc */
  virtual const CATCGMAttributeDef * GetAttributeDef() const =0 ;     // get the definition of attribute
  

  /** @nodoc */
  virtual       int               AddRef         ();
  

  /** @nodoc */
  virtual       int               Release        ();
  
  /**
  * @nodoc 
  * Allows the programmer to code a user link from <tt>this</tt> attribute to the CATICGMObject.
  * <br>By default, this method does nothing.
  */
  virtual       void              PutObject      (CATICGMObject * iToPoint);
  
    
#ifdef CATIACGMR214CAA
  /** @nodoc or UV project with optional Attributes on Topology and FreeStyle direct geometrical Edition  */
  virtual       void              InvalidateExtendedCachesOnTopology(CATGeometry* iFromTopology) ;  
#endif


  /** @nodoc */
  static        CATCGMAttrId _UAID;
  
  /** @nodoc */
  static        void              InitStaticCATCGMAttributeDef();
  
  
  protected :

    /** @nodoc */
                                  CATCGMAttribute(); 
        
    /** @nodoc */
  static        short             CATCGMAttrIdSecureInit();
        
  private :
    
   friend class CATCGMStream;
   friend class CATCGMStreamCGMImpl;
    
   friend       CATCGMAttribute * CATCGMAttribute_CreateAttribute ();
    
    /** @nodoc */
    struct  CATCGMAttributeData
    {
      CATULONG32    RefCounter;
      signed int    IsStreaming : 30;
      unsigned int  _IsReportedAsClonableAttributes : 1;
    } 
    _CGM;
};



/** @nodoc */
INLINE CATULONG32  CATCGMAttribute::GetNbAttrRef() const
{
  return _CGM.RefCounter; 
}


/**
* @nodoc limited availability low-level attributes reporting  
* Set ReportedClonable Attributes.
*/
INLINE CATBoolean CATCGMAttribute::IsReportedAsClonableAttributes() const 
{
  return _CGM._IsReportedAsClonableAttributes ? TRUE : FALSE; 
}

/**
* @nodoc limited availability low-level attributes reporting  
* Set ReportedClonable Attributes.
*/
INLINE void CATCGMAttribute::SetReportedClonableAttributes()   
{
  _CGM._IsReportedAsClonableAttributes = 1; 
}



#endif
