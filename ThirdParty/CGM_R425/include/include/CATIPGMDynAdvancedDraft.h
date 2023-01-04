#ifndef CATIPGMDynAdvancedDraft_h_
#define CATIPGMDynAdvancedDraft_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynDraft.h"
#include "CATFreeFormDef.h"
#include "CATMathDef.h"

class CATAutomaticDraftContext;
class CATBody;
class CATDynSolidDraftCGM;
class CATGeoFactory;
class CATPlane;
class CATPoint;
class CATTopData;
class CATDynDraftReorderZone; // Not interfaced for the moment
class CATDynDraftReorderZoneParams; // Not interfaced for the moment

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynAdvancedDraft;

class ExportedByCATGMOperatorsInterfaces CATIPGMDynAdvancedDraft: public CATIPGMDynDraft
{
public:
  /**
   * Constructor
   */
  CATIPGMDynAdvancedDraft();

  /**
   * @nodoc
   */
  virtual void SetContinuityLevel(
    const CATFrFContinuity iContinuityLevel,
    const CATPositiveLength iTolerance = 0.) = 0;

  /**
   * @nodoc
   */
  virtual void GetRecommendedLimitingElements(
    CATLISTP(CATBody) &oListLimitingBody,
    CATListOfInt &oListLimitingOrientations) = 0;

  //to be used after Run()
  //Get the number of twist zones that caused the failure of draft operation
  /** @nodoc */
  virtual int GetNumberOfTwistZones() = 0;

  //to be used after Run()
  //Get the reorder zone corresponding to a given twist zone index and given CATDynDraftReorderZoneParams 
  //you need to delete the memory allocated by the operator to oReorderZone
  //returns TRUE on success. else FALSE
  /** @nodoc */
  virtual CATBoolean GetReorderZone(
    const int &iReorderZoneIndex,
    CATDynDraftReorderZone *&oReorderZone,
    CATDynDraftReorderZoneParams *iReorderParams = 0) = 0;

  //to be used before Run()
  //This will fail if used together with SetUntwistDraftFillFunction
  //The SetAutomaticUntwistMode method will also fail under this condition!
  //The iReorderZone may not get used for untwisting if it is invalid
  //returns TRUE on success. else FALSE
  /** @nodoc */
  virtual CATBoolean SetReorderZone(CATDynDraftReorderZone *iReorderZone) = 0;

  //to be used before Run()
  //This will set the option to keep features during the draft both sides
  /** @nodoc */
  virtual void SetKeepFeature( CATBoolean iKeepFeature ) = 0;

  /**
   * Defines how twisted topology is handled.
   * <br>By default, the automatic untwisting of topology is turned off.  When activated, the twisting is repaired.
   * @param iAutoUntwistMode
   * If <tt>iAutoUntwistMode</tt> is TRUE, untwisting is activated.
   */
  virtual void SetAutomaticUntwistMode(CATBoolean iAutoUntwistMode) = 0;

  //iAutoUntwistOffset = the offset used to modify the limits of default twist zones  on neutral wire (mm). 1mm is the default offset
  /** @nodoc */
  virtual void SetAutomaticUntwistOffset(double iAutoUntwistOffset) = 0;

  // For DraftBothSides fitted Draft, to be used before Run() and with SetAutomaticUntwistMode on
  //By default automatic gapfill mode is off
  //one can activate it by using iAutoGapFillMode=TRUE
  /** @nodoc */
  virtual void SetAutomaticGapFillMode(CATBoolean iAutoGapFillMode) = 0;

  // For DraftBothSides Reflect-Reflect Draft, to be used after Run()
  /** @nodoc */
  virtual int GetNumberOfLimitingElements() = 0;

  /** @nodoc */
  virtual void GetLimitingElement(
    int iNumber,
    double iShift,
    CATBody *&oLimitingElement,
    CATOrientation &oOrientation) = 0;

  /**
   * @nodoc
   */
  virtual void SetAutomaticDraftContext(CATAutomaticDraftContext *iContext) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynAdvancedDraft(); // -> delete can't be called
};

/**
 * Creates a CATIPGMDynDraft operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iPart
 * The pointer to the body to draft.
 * @param iType
 * The type of the draft operation.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynAdvancedDraft *CATPGMCreateDynAdvancedDraft(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart,
  const CATDynDraftType iType);

#endif /* CATIPGMDynAdvancedDraft_h_ */
