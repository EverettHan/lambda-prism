#ifndef CATPGMDRepBehavior_h_
#define CATPGMDRepBehavior_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMModelInterfaces.h"
#include "CATCGMUnknown.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATDeclarativeContext.h"

class CATGeoFactory;
class CATDRepBehavior;
class CATBody;
class CATCGMODTScaleManager;
class CATLiveBody;

class ExportedByCATGMModelInterfaces CATPGMDRepBehavior: public CATCGMUnknown
{
public:
  
  // Lifecycle management
  // -----------------------
  virtual CATLONG32 __stdcall AddRef(void *iReferencing = NULL) = 0;

  virtual CATLONG32 __stdcall Release(void *iReferencing = NULL) = 0;

  //  ** Getters **
  // ----------------------
  virtual CATDeclarativeContext     * GetDeclarativeContext()       const = 0;
  virtual CATDeclarativeApplication   GetDeclarativeApplication()   const = 0;
  virtual CATDeclarativeOriginModeler GetDeclarativeOriginModeler() const = 0;

  virtual double GetFilletRoundingTolerance() const = 0;

  // ** Setters **
  // ----------------------
  virtual void SetDeclarativeContext(CATDeclarativeContext *iDeclarativeContext) = 0;

  // << Stream / Unstream >>
  // ==========================================
  virtual void Stream(CATCGMStream &Str) = 0;

  virtual void UnStream(CATCGMStream &Str, CATSoftwareConfiguration * ipConfig=NULL, CATCGMODTScaleManager *iODTScaleManager=NULL) = 0;

  virtual void Dump(CATCGMOutput &os) = 0;

  // For Internal use
  virtual CATDRepBehavior *CastToDRepBehaviorImpl() const = 0;

protected :
 /**
   * Constructor
   */
  /** @nodoc */
  CATPGMDRepBehavior();
    /**
   * Destructor
   */
  virtual ~CATPGMDRepBehavior();

  /** @nodoc */
  CATPGMDRepBehavior(const CATPGMDRepBehavior &iCopy);
  /** @nodoc */
  CATPGMDRepBehavior& operator=(const CATPGMDRepBehavior &iCopy);
};

ExportedByCATGMModelInterfaces CATPGMDRepBehavior *CATPGMCreateDRepBehavior(
  CATDeclarativeContext *iDeclarativeContext,
  CATDeclarativeApplication iDeclarativeApplication);

ExportedByCATGMModelInterfaces CATPGMDRepBehavior *CATPGMCreateDRepBehavior(
  CATDeclarativeContext *iDeclarativeContext,
  CATDeclarativeApplication iDeclarativeApplication,
  CATDeclarativeOriginModeler iDeclarativeOriginModeler);

// ================================================================================================
// Copy-Paste Methods 
// ================================================================================================
//
// CATCreateDeclarativeContextForPaste
// Create DeclarativeContext from a LiveBody. For NaturalShape, PasteMode.
// ------------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATDeclarativeContext *CATPGMCreateDeclarativeContextForPaste(
  const CATLiveBody *iLiveBody,
  CATSoftwareConfiguration *iConfig);

/**
 * ~ Verify if the input body is allowed to be pasted
 *   in the iFactory comparing factories scales and bodies industries
 * @param iFactory
 * The factory where iBodyToPaste is supposed to be pasted
 * @param iBodyToPaste
 * The inputBody to be pasted
 * @param iContextToCompare
 * The declarative context related to iFactory
 * @param iConfig
 * The SoftwareConfiguration
 *
 * SPEC
 *  -1 If there is a change of scale, always allow the paste.
 *  -2 If the 2 Industries are compatible, allow the paste 
 *  -3 Otherwise the paste is not allowed
*/
ExportedByCATGMModelInterfaces CATBoolean CATPGMIsAllowedForPaste (
  CATGeoFactory *iFactory, 
  CATBody *iBodyToPaste, 
  CATDeclarativeContext *iContextToCompare, 
  CATSoftwareConfiguration * iConfig);


// Description : Attach iContext to iCopyBody
ExportedByCATGMModelInterfaces HRESULT CATPGMAttachContextForCopy(
  CATBody *iCopyBody,
  CATDeclarativeContext *iContextToAttach,
  CATSoftwareConfiguration *iConfig);

// @ Internal Use only
// Descritpion : Compare context from iCopyBody to iContext
// CATDeclarativeContextCompatibility is define in CATDeclarativeContext.h
ExportedByCATGMModelInterfaces CATDeclarativeContextCompatibility CATPGMCompareContextBeforePaste(
  CATBody *iCopyBody,
  CATDeclarativeContext *iContextToCompare,
  CATSoftwareConfiguration *iConfig);

#endif /* CATPGMDRepBehavior_h_ */
