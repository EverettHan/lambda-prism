#ifndef CATIPGMFaceOperator_h_
#define CATIPGMFaceOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMGeoToTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATLoop;
class CATMathBox;
class CATMathLine;
class CATPCurve;
class CATPlane;
class CATSurface;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFaceOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMFaceOperator: public CATIPGMGeoToTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFaceOperator();

  // Adds An internal loop 
  virtual void AddInternalLoop(int nbpcurves, CATPCurve **pcurves) = 0;

  virtual int Run() = 0;

  //  void CheckCrossing() const;
  virtual CATFace *GetFace() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFaceOperator(); // -> delete can't be called
};

//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFaceOperator *CATPGMCreateFaceOperator(
  CATGeoFactory *factory,
  CATTopData *iData,
  int nbpcurves,
  CATPCurve **pcurves);

// Creates a body with one face bounded by pcurves
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFaceOperator *CATPGMCreateFaceOperator(
  CATGeoFactory *factory,
  int nbpcurves,
  CATPCurve **pcurves,
  CATBody *targetBody = NULL,
  CATBodyFreezeMode bodyfreezemode = CATBodyFreezeOn,
  CATCGMJournalList *report = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFaceOperator *CATPGMCreateFaceOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATSurface *iSurface);

// Creates a body with one face bounded by Surface Boundaries
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFaceOperator *CATPGMCreateFaceOperator(
  CATGeoFactory *factory,
  CATSurface *surface,
  CATBody *targetBody = NULL,
  CATBodyFreezeMode bodyfreezemode = CATBodyFreezeOn,
  CATCGMJournalList *report = NULL);

#endif /* CATIPGMFaceOperator_h_ */
