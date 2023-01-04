#ifndef CATIPGMBodyFromLengthOnShell_h_
#define CATIPGMBodyFromLengthOnShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"
#include "CATLengthType.h"
#include "CATSkillValue.h"

class CATBody;
class CATCGMJournalList;
class CATFace;
class CATGeoFactory;
class CATPoint;
class CATShell;
class CATTopData;
class CATVertex;
class CATMathDirection;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMBodyFromLengthOnShell;

class ExportedByCATGMModelInterfaces CATIPGMBodyFromLengthOnShell: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBodyFromLengthOnShell();

  //- ----------------------------------------
  //- General method to compute the necessary data.
  //- If Run() was already used, all previous results will be lost
  //- ----------------------------------------
  virtual int Run() = 0;

/* Not implemented
  //- ----------------------------------------
  //- Since there is only one possible result for a wire,
  //- those methods are useless.
  virtual void Begin() = 0;

  virtual void Next() = 0;
*/

  //- ----------------------------------------
  //- ----------------------------------------
  // Returns the vertex computed by the run.
  //- If the ouput ( i.e. the CATBody or the CATVertex ) is 
  //- NULL, then the run has not been done.
  //- ----------------------------------------
  virtual CATBody *GetResult() = 0;

  //- ----------------------------------------
  //- To use these, CATSkillValue must be declared 
  //- as ADVANCED when the operator is created.
  //- ----------------------------------------
  virtual void SetFactory(CATGeoFactory *iFactory) = 0;

  virtual void SetShell(const CATBody *iNewShell) = 0;

  virtual void SetVertex(const CATBody *iNewVertex) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBodyFromLengthOnShell(); // -> delete can't be called
};

//- ----------------------------------------
// Constructor:  if type is RELATIVE, the ABSOLUTE value will be calculated.
//- ----------------------------------------
/**
* Creates a CATIPGMBodyFromLengthOnShell operator.
* @param iFactory
* The factory of the geometry. 
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iShellBody
* The pointer to the target surfacic body on which the offset is expected. 
* @param iVertexBody
* The body containing the point to offset. 
* @param iDirection
* The offset direction.
* @param iDistance
* The offset value.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMBodyFromLengthOnShell *CATPGMCreateBodyFromLengthOnShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATBody *iShell,
  const CATBody *iVertex,
  const CATMathDirection &iDirection,
  const CATLength iDistance,
  const CATLengthType itype = CATLengthType_ABSOLUTE_L,
  const CATSkillValue imodev = BASIC);

/**
 * @nodoc
 * Deprecated
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMBodyFromLengthOnShell *CATPGMCreateBodyFromLengthOnShell(
  CATGeoFactory *iFactory,
  const CATBody *iShell,
  const CATBody *iVertex,
  const CATMathDirection &iDirection,
  const CATLength iDistance,
  const CATLengthType itype = CATLengthType_ABSOLUTE_L,
  const CATSkillValue imodev = BASIC,
  CATCGMJournalList *Journal = NULL);

#endif /* CATIPGMBodyFromLengthOnShell_h_ */
