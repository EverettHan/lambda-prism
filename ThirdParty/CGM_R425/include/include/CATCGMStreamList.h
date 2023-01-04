/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//-----------------------------------------------------------------------------
// Usage :Simulate rough overweigth disk size for PCS criteria
// November 2009 : temporary  [ CatCGMStream_2009Fall ; CatCGMStream_2012Spring [
//   no more needed in August 2012 
//       with CATRootSharedDataCGM@_PersistencySelection_Initial
//=================================================================================
#ifndef CATCGMStreamList_H
#define CATCGMStreamList_H
#include "CATCGMStreamAttribute.h"                                 
#include "CATDataType.h"

class CATGeoFactory;

class ExportedByYP0LOGRP CATCGMStreamList : public CATCGMStreamAttribute
{
public :
  // Definition of the attribute (constructor, destructor, stream etc...)
  CATCGMStreamList();
  ~CATCGMStreamList();

  CATCGMStreamList(const CATLISTP(CATICGMObject)& iObjects);
  void  GetObjects(CATGeoFactory* iTheCATGeoFactory, CATLISTP(CATICGMObject)& ioObjects);

   /** @nodoc */
   virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  CATCGMDeclareAttribute (CATCGMStreamList,CATCGMStreamAttribute);

  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);
 
private :
  CATCGMStreamList(const CATCGMStreamList&);
  CATCGMStreamList& operator = (const CATCGMStreamList&);

  CATLONG32       _NumberOfTag;
  CATULONG32    * _Tags;
};

#endif
