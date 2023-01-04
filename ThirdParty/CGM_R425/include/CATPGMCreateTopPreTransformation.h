#ifndef CATPGMCreateTopPreTransformation_h_
#define CATPGMCreateTopPreTransformation_h_

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
class CATIPGMTopPreTransformation;
class CATLISTP(CATFace);



/**
 * Deprecated.
 * Constructs a CATTopPreTransformation.
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
 * @param iFacestoTransform
 * The pointer to list of faces to transform.
 * @param iReport
 * The pointer to the journal. If <tt>NULL</tt>, the journal is not written.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopPreTransformation *CATPGMCreateTopPreTransformation(
  const CATMathNonLinearTransformation &iMathTransfo,
  CATGeoFactory *iFactory,
  CATBody *iBodytoTransform,
  CATLISTP(CATFace) *iFacestoTransform,
  CATCGMJournalList *iReport = NULL);

/**
 * Constructs a CATTopPreTransformation.
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
 * @param iFacestoTransform
 * The pointer to list of faces to transform.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopPreTransformation *CATPGMCreateTopPreTransformation(
  const CATMathNonLinearTransformation &iMathTransfo,
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodytoTransform,
  CATLISTP(CATFace) *iFacestoTransform);

#endif /* CATPGMCreateTopPreTransformation_h_ */
