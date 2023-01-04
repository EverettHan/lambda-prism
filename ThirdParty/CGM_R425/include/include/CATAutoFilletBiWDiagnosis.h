// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : RR
//
// DESCRIPTION  : Diagnosis for CATAutoFilletBiW.
// This class is dedicated to provide the application with the necessary information to be returned to the user and or to be used to control the application workflow.
// Only data common to all Diagnosis types should be stored in this class.
// If data specific to some Diagnosis type has to be added, then the class should be derived and packaged inside the modeler.
//
//=============================================================================
// Creation RR April 2017
//=============================================================================
#ifndef CATAutoFilletBiWDiagnosis_H
#define CATAutoFilletBiWDiagnosis_H

#include "CATCGMVirtual.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATCGMNewArray.h"
class CATCGMOutput;
class CATCGMStream;

class ExportedByCATGMOperatorsInterfaces CATAutoFilletBiWDiagnosis: public CATCGMVirtual 
{
public:
  enum DiagnosisType {UnspecifiedError=0, NonConnexSpecification, UnknownEdgesConvexity, IncompatibleRadius, ErrorInEdgePropagation, LastOnLastAmbiguousPropagation, TooManyEdgesConnected, SpecificationIsMissing};

  virtual ~CATAutoFilletBiWDiagnosis();

  virtual int GetSpecIndex() const = 0;

  virtual DiagnosisType GetType() const = 0;

  virtual void Dump(CATCGMOutput& oStream) const = 0;

  //----------------------------------------------------------------------------
  // Protected section (not exported)
  //----------------------------------------------------------------------------
  virtual void Stream(CATCGMStream& oStr, const short iVersion) = 0; // For CGMReplay

  static int Compare(CATAutoFilletBiWDiagnosis* iDiag1, CATAutoFilletBiWDiagnosis* iDiag2);

  CATCGMNewClassArrayDeclare; // Pool allocation  

};

//----------------------------------------------------------------------------

#endif
