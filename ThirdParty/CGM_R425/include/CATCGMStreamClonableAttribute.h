#ifndef CATCGMStreamClonableAttribute_h_
#define CATCGMStreamClonableAttribute_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//  TODO 
//     Integration in GeometricObjects\PublicInterfaces\CATCGMAttribute.h
//  WITH IMPACT ON 
//     NewTopologicalObjects\CATCGMStreamTopoImpl.m\src\CATGeoToTopo_ReportClonableAttributes.cpp
//
//=============================================================================
#include "CATCGMStreamAttribute.h"
#include "YP0LOGRP.h"

#include "CATExtClonableManager.h"
#include "CATMathInline.h"

class CATICGMObject;

class ExportedByYP0LOGRP CATCGMStreamClonableAttribute : public CATCGMStreamAttribute
{
public :
  CATCGMStreamClonableAttribute();

  ~CATCGMStreamClonableAttribute();

  /**
  * Tests whether <tt>this</tt> CATCGMAttribute is manageable by Clone managements.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the attribute can be managed (i.e. implements ReportClonableAttributes), <tt>0</tt> otherwise.
  */
  virtual int IsClonableAttribute();


private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMStreamClonableAttribute(const CATCGMStreamClonableAttribute &iCopy);
  CATCGMStreamClonableAttribute& operator=(const CATCGMStreamClonableAttribute &iCopy);

};



#endif
