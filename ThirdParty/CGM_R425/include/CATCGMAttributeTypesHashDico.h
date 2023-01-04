/* -*-c++-*- */
#ifndef CATCGMAttributeTypesHashDico_H
#define CATCGMAttributeTypesHashDico_H
// COPYRIGHT DASSAULT SYSTEMES  2011
//===================================================================
//  CGA geometry-topology internal stream behavior
//===================================================================
#include "ExportedByGeometricObjects.h"
#include "CATHashDico.h"
#include "CATMathInline.h"

class ExportedByGeometricObjects CATCGMAttributeTypesHashDico
{
public: 
 
  static INLINE CATHashDico * GetAttributeTypesHashDico() ;

  static INLINE void          SetAttributeTypesHashDico(CATHashDico *iDico) ;

private :

  static CATHashDico * _AttributeTypesHashDico ;

};



INLINE CATHashDico * CATCGMAttributeTypesHashDico::GetAttributeTypesHashDico()
{
  return _AttributeTypesHashDico;
}


INLINE void          CATCGMAttributeTypesHashDico::SetAttributeTypesHashDico(CATHashDico *iDico) 
{ 
  _AttributeTypesHashDico = iDico;
}


#endif // CATCGMAttributeTypesHashDico_H

