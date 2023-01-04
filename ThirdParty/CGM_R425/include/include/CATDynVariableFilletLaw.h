/* -*-C++-*- */

#ifndef CATDynVariableFilletLaw_H
#define CATDynVariableFilletLaw_H

// COPYRIGHT DASSAULT SYSTEMES 2003

//------------------------------------------------------------------------------
//
// CATDynVariableFilletLaw: Compute mapping and radius law for variable fillet
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Usage notes:
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Oct. 2003    Creation                                   F. Dujardin
//------------------------------------------------------------------------------
#include "CATGMOperatorsInterfaces.h"
#include "CATDynFilletRadius.h"
#include "CATTopDefine.h"

class CATTopData;
class CATCGMJournalList;
class CATGeoFactory;

class CATBody;
class CATCompositeLaw;

class ExportedByCATGMOperatorsInterfaces CATDynVariableFilletLaw
{
 public :

  // Constructor :
  // iSpine = Mono wire body, containing only one edge, or two for closed spine  
  //          (the two edges using the same geometry)
  // iRadiusLawMode = 0 : old radius law computation
  //                  1 : improved radius law computation
  CATDynVariableFilletLaw(CATGeoFactory *                iFactory, 
                          CATTopData *                   iData,
                          CATBody *                      iSpine,
                          CATLISTP(CATDynFilletRadius) * iRadiusList,
                          int                            iRadiusLawMode=0);


  virtual ~CATDynVariableFilletLaw();

  // Get radius law (and also mapping, as computed internally)
  CATCompositeLaw * GetRadiusLaw(CATCompositeLaw *& oMappingLaw) const;
  // Get radius law
  CATCompositeLaw * GetMappingLaw() const;

  // data
  CATCompositeLaw * _MappingLaw;
  CATCompositeLaw * _RadiusLaw;


  // Utilities
  //==========
  // Extend a law according to cursor
  CATCompositeLaw * ExtendVariableFilletLaw(CATGeoFactory * iFactory, CATCompositeLaw * iLaw, 
                                            double iStart, double iEnd);

};
#endif
