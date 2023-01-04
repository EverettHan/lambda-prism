#ifndef CATIPGMExtrapolOpWireOnShell_h_
#define CATIPGMExtrapolOpWireOnShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATExtrapolWireOnShellAtVtxOpr;
class CATExtrapolWireOnShellContext;
class CATMathVector;
class CATMathVector2D;
class CATWireOnShellExtrSpecAttr;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapolOpWireOnShell;

/**
 * Do not use.
 * Interface representing a topological operation of extrapolation of a wire 
 * CATBody 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolOpWireOnShell: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolOpWireOnShell();

  // Ajout d'une spec d'extrapolation sur un vertex
  virtual void Append(CATVertex *iVertex, double iLengthToAchieve = -1.) = 0;

  // Execution of the operator
  virtual int Run() = 0;

  // Get the resulting Body
  virtual CATBody *GetResult() = 0;

  /**
   * Returns the mode in which the resulting body is created.
   * @return
   * The smart mode.
   */
  virtual CATBodyFreezeMode GetFreezeMode() const = 0;

  /**
   * Defines the state of the resulting body.
   * @param iOnOrOff
   * The state of the resulting body. 
   */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

  // force le logging dans le journal par des :
  //  Creation (Edge Extrapolee) a partir de (Face support, Edge a Extrapoler)
  virtual void SetJournalFromEdges() = 0;

  // Force l'operateur a ne pas verifier les auto-intersections. A utiliser
  // quand on sait ce qu'on fait.
  virtual void SetNoSelfIntersectionCheck() = 0;

  // Force l'operateur a reutiliser la geometrie existante quand c'est
  // possible (1 pour oui, 0 pour non).
  virtual void SetUseExistingGeometry(short iOnOff) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolOpWireOnShell(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolOpWireOnShell *CATPGMCreateExtrapolOpWireOnShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *BodyWire,
  CATBody *BodyShell);

#endif /* CATIPGMExtrapolOpWireOnShell_h_ */
