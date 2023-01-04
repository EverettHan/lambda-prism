#ifndef CATPGMCreateTopNonLinearTransformation_h_
#define CATPGMCreateTopNonLinearTransformation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATMathNonLinearTransformation;
class CATTopData;
class CATIPGMTopNonLinearTransformation;

/**
 * Deprecated.
 * Constructs a CATTopNonLinearTransformation for non-linear transformation.
 * @param iMathTransfo
 * The non-linear transformation to apply. 
 * @param iFactory
 * A pointer to the factory of the resulting objects
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBodyToTransform
 * The pointer to the body to transform. This body will not be modified. A new resulting
 * body is created, that can be retrieved by the <tt>GetResult</tt> method.
 * @param iReport
 * The pointer to the journal. If <tt>NULL</tt>, the journal is not written.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopNonLinearTransformation *CATPGMCreateTopNonLinearTransformation(
  const CATMathNonLinearTransformation &iMathTransfo,
  CATGeoFactory *iFactory,
  CATBody *iBodytoTransform,
  CATCGMJournalList *iReport = NULL);

/**
 * Constructs a CATTopNonLinearTransformation for non-linear transformation.
 * @param iMathTransfo
 * The non-linear transformation to apply. 
 * @param iFactory
 * A pointer to the factory of the resulting objects
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBodyToTransform
 * The pointer to the body to transform. This body will not be modified. A new resulting
 * body is created, that can be retrieved by the <tt>GetResult</tt> method.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopNonLinearTransformation *CATPGMCreateTopNonLinearTransformation(
  const CATMathNonLinearTransformation &iMathTransfo,
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodytoTransform);

#endif /* CATPGMCreateTopNonLinearTransformation_h_ */
