#ifndef CATIPGMTopBodyHealerOperator_h_
#define CATIPGMTopBodyHealerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATLISTP(CATFace);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopBodyHealerOperator;

class ExportedByCATGMModelInterfaces CATIPGMTopBodyHealerOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopBodyHealerOperator();

  virtual int Run() = 0;

  virtual CATBoolean GetComputeInteriorHealing() = 0;

  virtual void SetComputeInteriorHealing(CATBoolean iCompute) = 0;

  virtual void SetFacesToHeal(CATLISTP(CATFace) *iFacesToHeal) = 0;

  virtual void SetHealDomains(CATBoolean iHealDomains) = 0;

  // Cette option n'est valide que pour les bodys composes uniquement de wires. 
  virtual void SetHealBody(CATBoolean iHealBody) = 0;

  // N'est implemente que pour un body constitue que de wires
  virtual void SetRegularizatorMode(CATBoolean iRegulMode) = 0;

  virtual void SetStabilizeConfusion(CATBoolean iStabilize) = 0;

  virtual void EliminateInitialFatGeometry(CATBoolean iEliminate) = 0;

  virtual void DetectDeadEnd(CATBoolean iDeadEnd) = 0;

  // by default using factory resolution
  // valid value for custom resolution are : resolution of a higher scale factory  ex: input body tol = NS ; custom tol = LS
  // or a resolution value between inputbody resolution and higher scale factory ( only work for edge )
  virtual void SetResolution(double iResolution) = 0;

  // apply healer only on small edge
  virtual void RegularizeSmallEdgeOnly(CATBoolean iSmallEdge) = 0;

  virtual CATLISTP(CATBody) *GetResultBodies() = 0;

  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopBodyHealerOperator(); // -> delete can't be called
};

#endif /* CATIPGMTopBodyHealerOperator_h_ */
