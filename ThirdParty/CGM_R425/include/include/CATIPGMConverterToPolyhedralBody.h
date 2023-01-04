#ifndef CATIPGMConverterToPolyhedralBody_h_
#define CATIPGMConverterToPolyhedralBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPolyTopOperator.h"
#include "CATCGMJournal.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMConverterToPolyhedralBody;

class ExportedByCATGMOperatorsInterfaces CATIPGMConverterToPolyhedralBody: public CATIPGMPolyTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConverterToPolyhedralBody();

  //=============================================================================
  // Optional Settings
  //=============================================================================
  /**
  * Sets the sag as the maximum deviation between the generated triangles (resp. bars) and the original surfaces (resp. curves)
  * The input value must include the scale factor.
  * If not set, the default value will be the Tolerant Resolution (0.1 mm at NormalScale)
  */
  virtual void SetSag(double iSag) = 0;

  /**
  * Sets the maximum step size. 
  * The input value must include the scale factor.
  * If not set, the default value will be 1.e12 mm (at NormalScale)
  */
  virtual void SetMaxStep(double iMaxStep) = 0;

  /**
  * Sets the maximum radian angle not to be exceeded.  
  * If not set, the default value will be (CATPI * 0.25)
  */
  virtual void SetMaxAngle(double iMaxAngle) = 0;

  /** 
  * Sets the type of journal items 
  * (CATCGMJournal::Creation or CATCGMJournal::Modification)
  * default is Creation
  */
  virtual void SetJournalType(CATCGMJournal::Type iJournalType) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConverterToPolyhedralBody(); // -> delete can't be called
};

/**
 * Creates a CATIPGMConverterToPolyhedralBody operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBody
 * The pointer to the exact body to convert
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be deleted with the usual C++ delete operator after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMConverterToPolyhedralBody *CATPGMCreateConverterToPolyhedralBody(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATIPGMConverterToPolyhedralBody_h_ */
