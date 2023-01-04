//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//==============================================================================================================
// CATCldPointAttributes.h
//==============================================================================================================
// 17-Sep-2014 - JLH - Correction des bugs IR-306340 et IR-306429 :
//                     Prise en compte des attributs applicatifs persistants dans la méthode DuplicateInside
//                     D'où la nécessité de deux nouvelles méthodes CreateOfSameType et CopyAttribute
// 25-apr-2014 - JLH - Creation
//==============================================================================================================

#ifndef CATCldPointAttributes_H
#define CATCldPointAttributes_H

#include "CATCGMStreamAttribute.h"

#include "YP00IMPL.h"

class ExportedByYP00IMPL CATCldPointAttributes : public CATCGMStreamAttribute
{
  CATCGMDeclareAttribute (CATCldPointAttributes, CATCGMStreamAttribute) ;

public:

  CATCldPointAttributes() ;
  virtual ~CATCldPointAttributes() ;

  virtual CATCldPointAttributes * CreateOfSameType() ;

  // Clone management from CATCGMAttribute
  virtual int IsClonableAttribute() ;
  virtual CATCGMAttribute * ReportClonableAttributes (CATExtClonableManager * iClonableManager,
                                                      CATICGMObject         * iOrigin,
                                                      CATICGMObject         * iDestination) ;

  // Stream/unstream management from CATCGMStreamAttribute
  virtual void Stream   (CATCGMStream &ioStream) const ;
  virtual void UnStream (CATCGMStream &ioStream) ;

  // Callbacks for CATCldUniCell
  virtual boolean AddAttribute() ;
  virtual boolean RemoveAttribute (const int iNoAttr) ;
  virtual boolean MoveAttribute   (const int iFrom, const int iTo) ;
  virtual boolean SwapAttributes  (const int iNoAttr, const int iMoAttr) ;
  virtual boolean SetNbAttributes (const int iNbAttributes) ;
  virtual boolean CopyAttribute   (const CATCldPointAttributes * iOther, const int iFrom, const int iTo) ;

} ;

#endif
