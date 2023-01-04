#ifndef CATICGMTopBodyExtremum_h_
#define CATICGMTopBodyExtremum_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATMinMax.h"

class CATBody;
class CATCGMJournalList;
class CATMathPoint;
class CATMathVector;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopBodyExtremum;

//-----------------------------------------------------------------------------
/**
* Class defining the operator that computes the point the furthest away from a given point
* in a given direction.
*<br>
* The CATICGMTopBodyExtremum operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the input body is not modified. The result is a body
* containing vertices (for isolated solutions), wires or skins.
*<ul>
* <li>A CATICGMTopBodyExtremum operator is created with the <tt>CATCGMCreateDirBodyExtremum</tt> 
* global method. It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>The computation is done with the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopBodyExtremum: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopBodyExtremum();

  /**
      * Runs <tt>this</tt> operator.
      */
  virtual int Run() = 0;

  /**
      * Returns the distance between the origin and the extremum projection
      * along the specified direction.
      * @return
      * The value.
      */
  virtual double GetExtremum() = 0;

  /**
      * Returns the created body.
      * @return
      * The pointer to the created body containing the vertices, wires or surfaces representing
      * the body extremum.
      */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopBodyExtremum(); // -> delete can't be called
};

/**
* @nodoc
* @deprecated V5R22 CATCreateDirNewBodyExtremum
* Creates the operator that computes the point(s) the furthest away from a given point
* in a given direction.
* @param iFactory
* The pointer to the geometry factory.
* @param iBody
* The pointer to the body.
* @param iTypeOfExtremum
* The type of extremum: minimum or maximum.
* @param iDirection
* The direction.
* @param iPtOrig
* The origin from which the distance returned by GetExtremum is computed.
* By default, the CATMathPoint is (0,0,0).
* @param iJournal
* The pointer to the journal. If <tt>NULL</tt>, the journal is not filled in.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopBodyExtremum *CATCGMCreateDirBodyExtremum(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATMinMax iTypeOfExtremum,
  const CATMathVector &iDirection,
  const CATMathPoint &iPtOrig);

/**
* Creates the operator that computes the point(s) the furthest away from a given point
* in a given direction.
* @param iFactory
* The pointer to the geometry factory.
* @param iBody
* The pointer to the body.
* @param iTypeOfExtremum
* The type of extremum: minimum or maximum.
* @param iDirection
* The direction.
* @param iPtOrig
* The origin from which the distance returned by GetExtremum is computed.
* By default, the CATMathPoint is (0,0,0).
* @param iJournal
* The pointer to the journal. If <tt>NULL</tt>, the journal is not filled in.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopBodyExtremum *CATCGMCreateDirNewBodyExtremum(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATMinMax iTypeOfExtremum,
  const CATMathVector &iDirection,
  const CATMathPoint &iPtOrig);

#endif /* CATICGMTopBodyExtremum_h_ */
