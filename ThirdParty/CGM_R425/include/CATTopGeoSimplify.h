#ifndef CATTopGeoSimplify_h
#define CATTopGeoSimplify_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
* Class representing the operator that geometrically simplify a body.
*
* This operator try to minimize the number of confused surfaces within a body or a faces selection.
*
* This operator follows the usual way of topological operation ( CATCreate + Run() + GetResult() + delete )
*
* If no simplification has occured , the result body is identical to the input body
*
* Performance : It is strongly recommanded to limit the geometrical simplification to a restricted area ( "SetCellsToSimplify" ).
*
* Restriction : it is not possible to simplify confused closed surfaces in all topological situation.
*
*/

class CATBody;
class CATGeoFactory;
class CATTopData;

#include "CATTopOperator.h"
#include "CATListOfCATCells.h"
#include "BOOPER.h"

class ExportedByBOOPER CATTopGeoSimplify : public CATTopOperator
{

  CATCGMVirtualDeclareClass(CATTopGeoSimplify);

public:

   //  Destructor
  virtual ~CATTopGeoSimplify();

  /**
  * Defines the cells to simplify.
  * @param iCellsToSimplify
  * The list of cells to simplify. This restricts the simplification to these cells only.
  * This method is only currently available for faces.
  * If not called , the simplification will occurs on the whole body.
  */
  virtual void SetCellsToSimplify ( CATLISTP(CATCell)& iCellsToSimplify ) = 0;
  
  /**
  * Activate parameter for canonic, fillet & tabulated cylinder surfaces simplification only
  */
  virtual void DisableAllButCanonic() = 0;

protected:

  /** @nodoc */
  CATTopGeoSimplify ( CATGeoFactory * iFactory        ,
	                  CATTopData *    iTopData        ,
	                  CATBody *       iBodyToSimplify );

};

/**
 * Creates a CATTopGeoSimplify operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToSimplify
 * The pointer to the body to geometrically simplify.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */

ExportedByBOOPER CATTopGeoSimplify * CATCreateTopGeoSimplify ( CATGeoFactory * iFactory        ,
														       CATTopData    * iData           ,
                                                               CATBody       * iBodyToSimplify );

#endif
