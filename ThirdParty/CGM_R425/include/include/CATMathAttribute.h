#ifndef CATMATHATTRIBUTE_H
#define CATMATHATTRIBUTE_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
//     Advanced mathematics operators attributes for specific parameterizations
//
//=============================================================================
// ??/??/?? ??? Creation
// 27/07/09 NLD Stream des attributs
//              - ajout IsStreamable()
//              - ajout Stream() et StreamRun(), ajout UnStream(), GetStreamType()
//              Ajout Dump()
//              et protection contre definition nefaste de _PU
//=============================================================================

#define CATMathAttributeStreamInfrastructure

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATCGMVirtual.h"


// NLD280709 l'inclusion de CATCGMOutput ramene un #define _PU ultranuisible
// petit effet de bord dans GeometricOperators\Connect.m
// ou _PU est defini en donnee membre de certaines classes
// et ou l'on peut trouver, ex: GeometricOperators/ConnectInt.m/LocalInterfaces/CATChordalFilletInitSystem.h
// mais pas partout (defini de multiples fois en LocalInterfaces)
// la protection suivante:
// /** @c++ansi fbq 2004-08-06.14:54:19 [_PU already #defined xlocinfo.h:#define _PU _PUNCT] **/
// #ifdef _CAT_ANSI_STREAMS
// #undef _PU
// #endif
#ifndef _PU
#define MustUndefPU
#endif
#include "CATCGMOutput.h"
#ifdef MustUndefPU
 #ifdef _PU
  #undef _PU
 #endif
#endif
//
#include "CATCGMStreamVersion.h"
#include "CATMathStream.h"

class ExportedByYN000FUN CATMathAttribute : public CATCGMVirtual
{
 public:
  virtual CATMathAttrId GetType() const = 0;
  virtual ~CATMathAttribute();
  virtual CATBoolean IsExclusive() const; 
  virtual void Dump(CATCGMOutput &os) const;

  #ifdef CATMathAttributeStreamInfrastructure
  // ---------------------------------------------------------
  // to be defined in derived classes
  // ---------------------------------------------------------
  // making an attribute streamable means:
  // - coding in derived class IsStreamable(), StreamRun()
  // - coding a constructor with a CATMathStream input
  //   for instance
  //   CATMathAttributeXXX(CATMathAttrId id, CATLONG32 Exclusive, CATMathStream& Str, const char iLabelReserved[] = "")
  // - calling this constructor in generic static CATMattAttribute::UnStream() method
  // - define stream type constant in CATMathAttributeStrType.h
  //   for instance #define CATMathStrAttributeTypeXXX   101
  // - coding GetStreamType() 
  // 
  // indicates whether derived class is streamable
  //                                            (const CATCGMStreamVersion iTargetVersion /*, NLD/TCX: inutile CATBoolean& ioReversible*/)
  virtual CATBoolean IsStreamable(const CATCGMStreamVersion iTargetVersion)const;
  // (internal: no direct use by application) stream specific data from derived class
  virtual void StreamRun( CATMathStream& Str, const char iLabelReserved[] = "") const;
  virtual short GetStreamType() const;

  // generic Stream infrastructure to be called by application
  // ---------------------------------------------------------
  void Stream( CATMathStream& Str, const char iLabelReserved[] = "") const;
  // create attribute from stream
  // oAttribute should be null in input, and is set by method if UnStream is possible 
  static void UnStream(CATMathStream&Str, CATMathAttribute*& oAttribute, const char iLabelReserved[] = "");
  #endif
};
#endif
