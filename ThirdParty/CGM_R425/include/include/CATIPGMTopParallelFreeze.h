#ifndef CATIPGMTopParallelFreeze_h_
#define CATIPGMTopParallelFreeze_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopParallel.h"

class CATBody;
class CATIPGMDistanceTool;
class CATICGMExtrapolParallelTool;
class CATLaw;
class CATSimplifyParallelTool;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopParallelFreeze;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopParallelFreeze: public CATIPGMTopParallel
{
public:
  /**
   * Constructor
   */
  CATIPGMTopParallelFreeze();

  // valeur 1 pas de trim realise. Le body resultant est invalide et doit etre detruit
  // utiliser cette valeur uniquement pour de la visu et optimiser ces perfos
  // valeur 0 traitement normal
  virtual void SetNoTrim(CATLONG32 notrim) = 0;

  // valeur 1 traitement des twists
  // valeur 0 traitement normal
  virtual void TwistedAuthorized(CATLONG32 twisted) = 0;

  // Allow the use of G0Law - 1 on / 0 off
  virtual void UseG0LawAuthorized(CATLONG32 AllowG0Law) = 0;

  virtual CATLONG32 GetUseG0LawAuthorized() = 0;

  virtual CATLONG32 SetSimplifyTool(CATSimplifyParallelTool *CurSimplif) = 0;

  // 1 = simplification des PLines
  // 0 = pas de simplification des PLines
  virtual void SetPLineSimplif(CATLONG32 simplif) = 0;

  virtual void GetPLineSimplif(CATLONG32 &simplif) = 0;

  virtual void Freeze(int iFreeze) = 0;

  // utilitaire : recuperation de lois de mapping sur un wire
  static void GetMappings(
    CATGeoFactory *Facto,
    CATTopData *iData,
    CATBody *iWire,
    CATLONG32 &nblaws,
    CATLaw **&MapLaws);

  virtual void SetLayDownTolerance(double Tolerance) = 0;

  virtual void GetLayDownTolerance(double &Tolerance) = 0;

  // Start : SUH : 2003:5:21
  virtual void SetSimplifOn(int ) = 0;

  virtual void CompleteSolutionForPlanarSupport() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopParallelFreeze(); // -> delete can't be called
};

// End : SUH : 2003:5:22
/** @nodoc */
ExportedByCATGMOperatorsInterfaces CATIPGMTopParallelFreeze *CATPGMCreateNONL1Parallel(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

/** @nodoc */
ExportedByCATGMOperatorsInterfaces CATIPGMTopParallelFreeze *CATPGMCreateNONL1ParallelLight(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

ExportedByCATGMOperatorsInterfaces CATIPGMTopParallelFreeze *CATPGMCreateNONL1Parallel(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

/** @nodoc */
ExportedByCATGMOperatorsInterfaces CATIPGMTopParallelFreeze *CATPGMCreateNONL1ParallelLight(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

#endif /* CATIPGMTopParallelFreeze_h_ */
