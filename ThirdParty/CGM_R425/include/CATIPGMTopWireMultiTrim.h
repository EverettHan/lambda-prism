#ifndef CATIPGMTopWireMultiTrim_h_
#define CATIPGMTopWireMultiTrim_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCell;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopWireMultiTrim;

class ExportedByCATGMModelInterfaces CATIPGMTopWireMultiTrim: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopWireMultiTrim();

  //========================================================
  // Methodes de parametrisation de l'operateur (INTERFACES)
  //========================================================
  virtual void SetKeepOrderOn(int iPortionNumber, CATBody *iRefBody) = 0;

  //========================================================
  // Methodes d'execution et de resultats (INTERFACES)
  //========================================================
  virtual int Run() = 0;

  virtual CATBody *GetResult() = 0;

  virtual CATBody *GetIntermediateResult() = 0;

  virtual int GetNumberOfIntersections(CATBody *iRefBody, CATBody *iVersusBody) = 0;

  virtual int GetPortionNumber(CATCell *iRefCell, CATBody *iRefBody) = 0;

  virtual void GetResultBodies(
    CATBody *iRefBody,
    CATLISTP(CATBody) &ioResultBodies) = 0;

  virtual void GetJournalForOneBody(
    CATBody *iBodyInput,
    CATBody *iBodyMosaicResult,
    CATCGMJournalList &ioJournal) = 0;

  virtual void SetCuttingBodiesOthers(CATLISTP(CATBody) *iCuttingBodiesOthers) = 0;

  // vertices et shells decoupant les wires
  virtual int GetNbVerticesOnWireTable(int iIndexWireInitial) = 0;

  virtual void SetVerticesOnWireTable(
    int iIndexWireInitial,
    CATListOfInt *iIndexVertexInitialList,
    CATLISTP(CATBody) *iNewVertexBodyList) = 0;

  virtual void GetVerticesOnWireTable(
    int iIndexWireInitial,
    CATListOfInt *ioIndexVertexInitialList,
    CATLISTP(CATBody) *ioNewVertexBodyList) = 0;

  virtual CATBoolean ResultIsConnex() = 0;

  virtual CATBoolean ResultIsManifold() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopWireMultiTrim(); // -> delete can't be called
};

#endif /* CATIPGMTopWireMultiTrim_h_ */
