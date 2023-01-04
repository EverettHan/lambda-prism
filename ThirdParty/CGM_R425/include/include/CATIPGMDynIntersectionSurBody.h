#ifndef CATIPGMDynIntersectionSurBody_h_
#define CATIPGMDynIntersectionSurBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"

class CATBody;
class CATPCurve;
class CATSurface;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynIntersectionSurBody;

/**
 * Do not use.
 * Interface representing a topological operation of intersection of a CATSurface
 * with a CATBody.
 * As all the topological operators, the input body and geometry are not modified. 
 * The resulting body is
 * a new one, that you can get by using the <tt>CATIPGMDynOperator::GetResult</tt> method.<br>
 * The resulting body contains edges, and methods are given to directly scan
 * the geometry attached to these edges.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionSurBody: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynIntersectionSurBody();

  /**
 * Initializes the iterator of the geometrical curves,
 * corresponding to edges of the resulting 
 * body from a CATIPGMDynIntersectionSurBody operator.
 *<br>By default, the initialization is performed once the operator has been
 * calculated, and is therefore only used to read the solutions again.
 */
  virtual void BeginningPCurve() = 0;

  /**
 * Points to the next CATPCurve, corresponding to an edge of the resulting 
 * body from a CATIPGMDynIntersectionSurBody operator.
 *<br>Called just after the <tt>Beginning</tt> method, it points to the first curve.
 * @return
 *<dl><dt><tt>1</tt> <dd>if there is still a curve that is solution.
 *    <dt><tt>0</tt> <dd>otherwise.</dl>
 */
  virtual CATBoolean NextPCurve() = 0;

  /**
 * Retrieves the next geometrical CATPCurve corresponding to an
 * edge, solution of a CATIntersectionSurBody operator.
  *<br>Creates the object if necessary.
 */
  virtual CATPCurve *GetPCurve() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynIntersectionSurBody(); // -> delete can't be called
};

// Creation EntryPoints
/**
 * Creates a CATIPGMDynIntersectionSurBody operator.
 * @param iForResultingBody
 * Where to create the resulting CATBody. 
 * @param iPart
 * The CATBody to intersect.
 * @param iSurface
 * The CATSurface intersecting <tt>iBody</tt>.  
 * @param journal
 * A pointer to the topological journal. If NULL, no line will be writen.
 * @return [out, IUnknown#Release]
 */
//cbk-ri0296310A-debut
ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionSurBody *CATPGMCreateDynIntersectionSurBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATSurface *iSurface,
  CATBody *iPart);

////////////////cbk-ri0296310A-fin
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionSurBody *CATPGMDynCreateIntersectionSurBody(
  CATGeoFactory *iFactory,
  CATSurface *iSurface,
  CATBody *iPart,
  CATCGMJournalList *iJournal = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynIntersectionSurBody *CATPGMDynCreateIntersectionSurBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATSurface *iSurface,
  CATBody *iPart);

#endif /* CATIPGMDynIntersectionSurBody_h_ */
