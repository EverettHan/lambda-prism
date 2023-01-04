//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Object class implementation for the ContextAttibute for DRep layer
//
//=============================================================================
// 15/01/13  QF2  Creation
//=============================================================================

#ifndef CATDRepBehavior_H
#define CATDRepBehavior_H

#include "PersistentCell.h"
#include "CATDeclarativeContext.h"
#include "CATDeclarativeApplication.h"
#include "CATPGMDRepBehavior.h"
#include "CATDeclarativeOriginModeler.h"

class CATLiveBody;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMODTScaleManager;

class ExportedByPersistentCell CATDRepBehavior : public CATPGMDRepBehavior
{
protected :
   
  //Default contructor
  CATDRepBehavior();
   /**
   * Destructor
   */ 
  ~CATDRepBehavior();

  CATDRepBehavior(const CATDRepBehavior &iCopy);
  CATDRepBehavior& operator=(const CATDRepBehavior &iCopy);

public:
   /**
   * Constructor
   */
  // @nocgmitf 
  CATDRepBehavior(CATDeclarativeContext * iDeclarativeContext, CATDeclarativeApplication iDeclarativeApplication);
  // @nocgmitf
  CATDRepBehavior(CATDeclarativeContext * iDeclarativeContext, 
                  CATDeclarativeApplication iDeclarativeApplication, 
                  CATDeclarativeOriginModeler iDeclarativeOriginModeler
                  );


  virtual CATDRepBehavior * CastToDRepBehaviorImpl() const;

  // Lifecycle management
  // -----------------------
  virtual CATLONG32  __stdcall AddRef (void*  iReferencing=NULL);
  virtual CATLONG32   __stdcall Release(void*  iReferencing=NULL);

  //  ** Getters **
  // ----------------------
  virtual CATDeclarativeContext     * GetDeclarativeContext()       const;
  virtual CATDeclarativeApplication   GetDeclarativeApplication()   const;
  virtual CATDeclarativeOriginModeler GetDeclarativeOriginModeler() const;

  virtual double GetFilletRoundingTolerance() const ;
  

  // @nocgmitf 
  CATDeclarativeContextIndustry GetIndustry() const ;


  // @nocgmitf
  static HRESULT RoundRadius(CATSoftwareConfiguration* iConfig, CATLiveBody* iLiveBody, double ioRadius[], const int iRadiusCount=1); 

  // ** Setters **
  // ----------------------
  void SetDeclarativeContext (CATDeclarativeContext *iDeclarativeContext);
  // @nocgmitf 
  void SetDeclarativeApplication (CATDeclarativeApplication iDeclarativeApplication);
  // @nocgmitf 
  void SetDeclarativeOriginModeler (CATDeclarativeOriginModeler iDeclarativeOriginModeler);

  // << Stream / Unstream >>
  // ==========================================
  void Stream(CATCGMStream& Str);
  void UnStream(CATCGMStream& Str, CATSoftwareConfiguration * ipConfig, CATCGMODTScaleManager *iODTScaleManager=NULL);
  void Dump(CATCGMOutput& os);


  // @nocgmitf
  static void Dump(CATCGMOutput & os, CATPGMDRepBehavior * iDRepBehavior);

  // @nocgmitf 
  static void Stream(CATPGMDRepBehavior * iDRepBehavior, CATCGMStream& Str);

  // The Param oDRepBehavior must be set NULL
  // @nocgmitf 
  static void UnStream(CATCGMStream& Str, CATPGMDRepBehavior *& oDRepBehavior, CATSoftwareConfiguration * ipConfig, CATCGMODTScaleManager *iODTScaleManager=NULL);

  // @nocgmitf 
  static const char * GetApplicationName(CATDeclarativeApplication iDeclarativeApplication);
  // @nocgmitf 
  static const char * GetOriginModelerName(CATDeclarativeOriginModeler iDeclarativeOriginModeler);

private :

  CATDeclarativeContext       *_DeclarativeContext;
  CATDeclarativeApplication    _DeclarativeApplication;
  CATDeclarativeOriginModeler  _DeclarativeOriginModeler;

};

// CATCreate Object : Official contructor
// ----------------------------------------
ExportedByPersistentCell CATDRepBehavior * CATCreateDRepBehavior (CATDeclarativeContext     * iDeclarativeContext, 
                                                                  CATDeclarativeApplication   iDeclarativeApplication);

ExportedByPersistentCell CATDRepBehavior * CATCreateDRepBehavior (CATDeclarativeContext     * iDeclarativeContext, 
                                                                  CATDeclarativeApplication   iDeclarativeApplication,
                                                                  CATDeclarativeOriginModeler iDeclarativeOriginModeler);

// ================================================================================================
// Copy-Paste Methods 
// ================================================================================================
//
// CATCreateDeclarativeContextForPaste
// Create DeclarativeContext from a LiveBody. For NaturalShape, PasteMode.
// ------------------------------------------------------------------------------------------------
ExportedByPersistentCell CATDeclarativeContext * CATCreateDeclarativeContextForPaste(const CATLiveBody *iLiveBody, CATSoftwareConfiguration *iConfig);


// Description : Attach iContext to iCopyBody
ExportedByPersistentCell HRESULT AttachContextForCopy (CATBody *iCopyBody, CATDeclarativeContext *iContextToAttach, CATSoftwareConfiguration * iConfig);

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
ExportedByPersistentCell CATBoolean IsAllowedForPaste (CATGeoFactory *iFactory, CATBody *iBodyToPaste, CATDeclarativeContext *iContextToCompare, CATSoftwareConfiguration * iConfig);


// @ Internal Use only
// Descritpion : Compare context from iCopyBody to iContext
// CATDeclarativeContextCompatibility is define in CATDeclarativeContext.h
ExportedByPersistentCell CATDeclarativeContextCompatibility CompareContextBeforePaste (CATBody *iCopyBody, CATDeclarativeContext *iContextToCompare, CATSoftwareConfiguration * iConfig);

// @nocgmitf 
ExportedByPersistentCell CATBoolean HasCopyPasteAttribut (CATBody *iBodyToTest);



#endif
