#ifndef CATPGMTrdReportBody_h_
#define CATPGMTrdReportBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATTrdReport.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATCell.h"
#include "ListPOfListPOfCATCell.h"

class CATBody;
class CATGeoFactory;
class CATPGMTrdReportBody;
class CATSoftwareConfiguration;

class ExportedByCATGMOperatorsInterfaces CATPGMTrdReportBody: public CATTrdReport
{
public:
  /**
   * Constructor
   */
  CATPGMTrdReportBody();

  /**
   * Destructor
   */
  virtual ~CATPGMTrdReportBody();

  /**
  * @nodoc
  * Get Rep fully mapped from Body1 and Body2
  * iMappedRep1 and iMappedRep2 are synchronized by Index (iMappedRep1[x] is mapped to iMappedRep2[x])
  * The caller is responsible for cleaning iMappedRep1 and iMappedRep2
  */
  virtual HRESULT GetFullyMappedRep(ListPOfListPOfCATCell &iMappedRep1, ListPOfListPOfCATCell &iMappedRep2) = 0;

  /**
  * @nodoc
  * Get Rep partially mapped from Body1 and Body2
  * iMappedRep1 and iMappedRep2 are synchronized by Index (iMappedRep1[x] is mapped to iMappedRep2[x])
  * The caller is responsible for cleaning iMappedRep1 and iMappedRep2
  */
  virtual HRESULT GetPartiallyMappedRep(ListPOfListPOfCATCell &iMappedRep1, ListPOfListPOfCATCell &iMappedRep2) = 0;

  /**
  * @nodoc
  * Get Rep not mapped from Body1 and Body2
  */
  virtual HRESULT GetNotMappedRep(ListPOfCATCell &iNotMappedCells1, ListPOfCATCell &iNotMappedCells2) = 0;

  /**
  * @nodoc
  * iFactory[2] are the factories to create Bodies into.
  * If succeeded,
  * oBodies[2] are the 2 lists of 3 Bodies each.
  * The first body contains fully similar faces, the second one contains partially similar faces, and the third one contains dissimilar faces.
  * Whenever there is no face matching the criteria, the corresponding body is null.
  * The BodyAnalyzer who filled this report must be still alive.
	*/
  virtual HRESULT CreateSimilarBodies(
    CATSoftwareConfiguration* iConfig, 
    CATGeoFactory* iFactory[2], 
    ListPOfCATBody oBodies[2]) = 0;


  /**
  * @nodoc
  * DEPRECATED, use previous method.
	* If succeeded, oBodySimilar1 (resp oBodySimilar2) contains Body1 (resp Body2) faces similar to Body2 (resp Body1) faces
  * and oBodyDissimilar1 (resp oBodyDissimilar2) the rest of faces.
  * oBodyDissimilar1 (resp oBodyDissimilar2) is null whenever no face is dissimilar.
  * oBodySimilar1 (resp oBodySimilar2) and oBodyDissimilar1 (resp oBodyDissimilar2) are created into iFactory1 (resp iFactory2).
  * The BodyAnalyzer who filled this report must be still alive.
	*/
  virtual HRESULT CreateSimilarBodies(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory *iFactory1,
    CATBody *&oBodySimilar1,
    CATBody *&oBodyDissimilar1,
    CATGeoFactory *iFactory2,
    CATBody *&oBodySimilar2,
    CATBody *&oBodyDissimilar2) = 0;

  /**
  * @nodoc
  * DEPRECATED, use first method.
	* If succeeded, oBody1 & oBody2 similar faces get green colored, other ones get red colored,
  * oBody1 is a copy of iBody1, oBody2 is a moved copy so that similar faces are at the same location as oBody1.
  * The BodyAnalyzer who filled this report must be still alive.
	*/
  virtual HRESULT CreateSimilarBodies(
    CATGeoFactory *iFactory,
    CATBody *&oBody1,
    CATBody *&oBody2) = 0;

};

/**
  * @nodoc
  */
ExportedByCATGMOperatorsInterfaces CATPGMTrdReportBody *CATPGMCreateTrdReportBody();

#endif /* CATPGMTrdReportBody_h_ */
