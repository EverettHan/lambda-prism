//* -*-c++-*- */
//===========================================================================
// Class CATDebugBodyNameAttr
//---------------------------------------------------------------------------
// Classe qui sert à attribuer un nom a un body.
//
//---------------------------------------------------------------------------
// Sep. 99  Creation.                                                L. Alt
//
//===========================================================================
#ifndef CATDebugBodyNameAttr_H
#define CATDebugBodyNameAttr_H

#include "CATCGMStreamAttribute.h"
#include "CATUnicodeString.h"
#include "CATCGMStreamClonableAttribute.h"
#include "ExportedByGeometricObjects.h"
 
class CATCloneManager;
class CATExtClonableManager;

class ExportedByGeometricObjects CATDebugBodyNameAttr : public CATCGMStreamClonableAttribute
{

  CATCGMDeclareAttribute( CATDebugBodyNameAttr, CATCGMStreamAttribute );

 public :

  CATDebugBodyNameAttr();
  CATDebugBodyNameAttr( const CATUnicodeString & iName );
  ~CATDebugBodyNameAttr();


  virtual void Stream(CATCGMStream &) const;
  virtual void UnStream( CATCGMStream& Str );
  virtual CATBoolean  IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  void GetName( CATUnicodeString & oName );

  virtual void Dump( CATCGMOutput & os ); // For Debug Purpose

  

  /**
  * Tests whether <tt>this</tt> CATCGMAttribute is manageable by Clone managements.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the attribute can be managed (i.e. implements ReportClonableAttributes), <tt>0</tt> otherwise.
  */
  virtual int IsClonableAttribute();


   //===================================== 
   //  Manage Report of attributes
   //    Sample of management
   //===================================== 
   /**
   * Manage Report of attributes.
   * @param iCloneManager
   *    context of operator.
   * @param Origin
   *    Original Holder of attribute.
   * @param Destination
   *    Destination Holder of attribute.
   */
   virtual CATCGMAttribute *  ReportClonableAttributes(CATExtClonableManager* iClonableManager,
                                         CATICGMObject  * iOrigin,
                                         CATICGMObject  * iDestination)  ;
 private : 

  CATUnicodeString _Name;

};


#endif
