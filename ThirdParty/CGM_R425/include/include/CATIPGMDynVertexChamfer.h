#ifndef CATIPGMDynVertexChamfer_h_
#define CATIPGMDynVertexChamfer_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATCollec.h"
#include "CATListOfDouble.h"
#include "ListPOfCATEdge.h"

class CATBody;
class CATGeoFactory;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynVertexChamfer;

class ExportedByCATGMOperatorsInterfaces CATIPGMDynVertexChamfer: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynVertexChamfer();

  // CPT: impact on SWx!!!
  virtual void SetVertex(CATVertex *iVertex) = 0;

  virtual void SetEdges(CATLISTP(CATEdge) &iEdges) = 0;

  virtual void SetSetbacks(double *iSetbacks) = 0;

  virtual void Append(
    CATVertex *iVertex,
    const CATLISTP(CATEdge) &iEdges,
    const CATListOfDouble &iSetbacks) = 0;

  virtual void SetPrevisualizationOnly() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynVertexChamfer(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynVertexChamfer *CATPGMCreateDynVertexChamfer(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynVertexChamfer *CATPGMCreateDynVertexChamfer(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart,
	CATVertex* iVertex,
  const CATLISTP(CATEdge) &iEdges,
	const CATListOfDouble& iSetbacks);

#endif /* CATIPGMDynVertexChamfer_h_ */
