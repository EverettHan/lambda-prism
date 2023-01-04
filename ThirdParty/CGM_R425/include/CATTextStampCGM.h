/* -*-C++-*- */
#ifndef CATTextStampCGM_H
#define CATTextStampCGM_H
// COPYRIGHT DASSAULT SYSTEMES 2011

//===================================================================
//===================================================================
//
// CATTextStampCGM: Label attached to objects, dedicated to debug with dump
//
//===================================================================
//===================================================================
// June 2011    Creation                         R. Rorato
//===================================================================

#include "CATCGMStreamAttribute.h"
#include "CATCGMNewArray.h"
#include "CATUnicodeString.h"
#include "PersistentCell.h"

class CATICGMObject;

class ExportedByPersistentCell CATTextStampCGM : private CATCGMStreamAttribute
{
public:
  CATCGMDeclareAttribute(CATTextStampCGM,CATCGMStreamAttribute);

  CATTextStampCGM();

  CATTextStampCGM(CATUnicodeString iString); 

  virtual ~CATTextStampCGM();

  CATCGMNewClassArrayDeclare;      // Pool allocation

  void PutOn(CATICGMObject* iSupport); 

  static void Dump(CATICGMObject* iSupport, CATUnicodeString& oText);

  void Dump(CATCGMOutput& os); 

  void Stream(CATCGMStream & ioStream) const;

  void UnStream(CATCGMStream& ioStr);

private:
  CATUnicodeString _String;

};

#endif
