#ifndef CATIPGMDynIntersectionCrvBody_h_
#define CATIPGMDynIntersectionCrvBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"

class CATBody;
class CATCrvParam;
class CATCurve;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynIntersectionCrvBody;

/**
 * Do not use.
 * Interface representing a topological operation of intersection of a CATCurve
 * with a CATBody.
 * As all the topological operators, the input body and geometry are not modified.
 * Notice that this operator does not create a new resulting CATBody.
 * It only creates geometrial points, that can be scans with an iterator.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionCrvBody: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynIntersectionCrvBody();

  /**
 * Initializes the iterator of the geometrical points,
 * resulting from a CATIPGMDynIntersectionCrvBody operator.
 *<br>By default, the initialization is performed once the operator has been
 * calculated, and is therefore only used to read the solutions again.
 */
  virtual void Beginning() = 0;

  /**
 * Points to the next point, resulting from a CATIPGMDynIntersectionCrvBody operator.
 *<br>Called just after the <tt>Beginning</tt> method, it points to the first point.
 * @return
 *<dl><dt><tt>1</tt> <dd>if there is still a point that is solution.
 *    <dt><tt>0</tt> <dd>otherwise.</dl>
 */
  virtual CATBoolean NextSolution() = 0;

  /**
 * Retrieves, as a CATCrvParam, the next geometrical point
 * solution of a CATIntersectionCrvBody operator.
 *<br>Creates the object if necessary.
 */
  virtual void GetSolution(CATCrvParam &oSolution) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynIntersectionCrvBody(); // -> delete can't be called
};

// Creation EntryPoints
/**
 * Creates a CATIPGMDynIntersectionCrvBody operator.
 * @param iForResultingBody
 * Where to create the resulting CATBody. For the moment, this body
 * is not created. Only geometrical points are created.
 * @param iPart
 * The CATBody to intersect.
 * @param iCurve
 * The CATCurve intersecting <tt>iBody</tt>.  
 * @param journal
 * A pointer to the topological journal. If NULL, no line will be writen.
 * @return [out, IUnknown#Release]
 */
//cbk-ri0296310A-debut
ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionCrvBody *CATPGMCreateDynIntersectionCrvBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATCurve *iCurve,
  CATBody *iPart);

////////////////cbk-ri0296310A-fin
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionCrvBody *CATPGMDynCreateIntersectionCrvBody(
  CATGeoFactory *iFactory,
  CATCurve *iCurve,
  CATBody *iPart,
  CATCGMJournalList *iJournal = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionCrvBody *CATPGMDynCreateIntersectionCrvBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATCurve *iCurve,
  CATBody *iPart);

#endif /* CATIPGMDynIntersectionCrvBody_h_ */
