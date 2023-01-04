#ifndef CATIPGMChecker_h_
#define CATIPGMChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDataType.h"

class CATCheckDiagnosisList;
class CATCheckDiagnosis;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMChecker;

class ExportedByCATGMModelInterfaces CATIPGMChecker: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMChecker();

  //======================================
  // Methodes specifiques a CATIPGMTopOperator
  //======================================
  virtual int Run() = 0;

  virtual CATBody *GetResult() = 0;

  //====================================
  // Acces aux parametres de l'operateur
  //====================================
  virtual CATBody *GetBodyToCheck() const = 0;

  virtual CATBoolean GetFullCheckMode() const = 0;

  virtual CATBoolean GetDiagnosisMode() const = 0;

  virtual double GetTolerance() const = 0;

  //===========================================
  // Methodes de parametrisation de l'operateur
  //===========================================
  virtual void SetFullCheckMode(CATBoolean iFullCheckMode) = 0;

  virtual void SetDiagnosisMode(CATBoolean iDiagnosisMode) = 0;

  virtual void SetStabilizeConfusion(CATBoolean iStabilize) = 0;

  //==============================================
  // Methodes d'acces aux resultats de l'operateur
  //==============================================
  virtual CATBoolean GetLogicalResult() const = 0;

  virtual CATLONG32 GetNbDiagnoses() const = 0;

  virtual const CATCheckDiagnosis *GetDiagnosis(CATLONG32 iDiagnosisIndex) const = 0;

  virtual CATCheckDiagnosisList *GetCheckDiagnosisList() const = 0;

  virtual void Dump(ostream &iOutput) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMChecker(); // -> delete can't be called
};

#endif /* CATIPGMChecker_h_ */
