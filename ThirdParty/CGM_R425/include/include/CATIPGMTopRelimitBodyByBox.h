#ifndef CATIPGMTopRelimitBodyByBox_h_
#define CATIPGMTopRelimitBodyByBox_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATGeoFactory;
class CATMathAdvancedBox;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopRelimitBodyByBox;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopRelimitBodyByBox: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopRelimitBodyByBox();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopRelimitBodyByBox(); // -> delete can't be called
};

///**
// * Creates a CATIPGMTopRelimitBodyByBox operator.
// * @param iFactory
// * The factory of the geometry. 
// * @param iTopData
// * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
// * is <tt>NULL</tt>, it is not filled. 
// * @param iBodyToSplit
// * The pointer to the target body which might be modified by either removing matter.
// * @param iAdvBox
// * Advanced Box that will relimit the iBodyToRelimit
// * @return [out, IUnknown#Release]
// * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
// */
ExportedByCATGMOperatorsInterfaces CATIPGMTopRelimitBodyByBox *CATPGMCreateTopRelimitBodyByBox(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToRelimit,
  const CATMathAdvancedBox &iAdvBox);

#endif /* CATIPGMTopRelimitBodyByBox_h_ */
