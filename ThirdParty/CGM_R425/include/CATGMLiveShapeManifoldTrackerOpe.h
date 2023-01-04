// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : L. Marini 
//
// DESCRIPTION  : Create a journal of CATManifold from PerviousBodyList to CurrentBodyList 
//
//=============================================================================
// Creation LAP July 2014
//
//=============================================================================
#ifndef CATGMLiveShapeManifoldTrackerOpe_H
#define CATGMLiveShapeManifoldTrackerOpe_H

#include "PersistentCell.h"
#include "CATTopOperator.h"
#include "ListPOfCATBody.h"
#include "CATCGMJournalList.h"
#include "ListPOfCATManifold.h"
#include "IUnknown.h" // For HRESULT
#include "CATListOfULONG32.h"

class CATGMLiveShapeManifoldTrackerImpl;
class CATSoftwareConfiguration;

/**
* This class is used to select faces with.<br>
**/
class ExportedByPersistentCell CATGMLiveShapeManifoldTrackerOpe : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATGMLiveShapeManifoldTrackerOpe);

public:

  //==============================================================================
  // constructor: do not use, use CATCreateLiveShapeManifoldTrackerOpe
  //==============================================================================
  // @nocgmitf
  CATGMLiveShapeManifoldTrackerOpe(CATGeoFactory                      * iFactory,
                                   CATTopData                         * iTopData,
                                   CATGMLiveShapeManifoldTrackerImpl  * iImp);

  //==============================================================================
  // destructor 
  //==============================================================================
  /**
  * Standard destructor.<br>
  **/
  // @nocgmitf
  virtual ~CATGMLiveShapeManifoldTrackerOpe();

  //==============================================================================
  //
  // CGMREPLAY METHODES
  //
  //==============================================================================
  /** @nodoc @nocgmitf declaration integre au CGMReplay */
  void RequireDefinitionOfInputAndOutputObjects();
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  static const CATString * GetDefaultOperatorId();
  /** @nodoc @nocgmitf */
  void DumpOutput(CATCGMOutput &os);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void ReadInput(CATCGMStream  & ioStream,int VersionOfStream, short iNumReplayVersion=1);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  /** @nodoc @nocgmitf */
  CATBoolean ReadReferenceOutput(CATCGMStream &Str);
  /** @nodoc @nocgmitf */
  void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  CATBoolean ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  // @nocgmitf
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  // @nocgmitf
  CATBoolean ValidateOutput(CATCGMStream & Str, CATCGMOutput & os, int VersionNumber=1);

protected:
  CATGMLiveShapeManifoldTrackerImpl *GetCATGMLiveShapeManifoldTrackerImpl() const;

private :

  //==============================================================================
  // copy constructor
  //==============================================================================
  /**
  * Copy constructor: Not implemented. <br>
  **/
  CATGMLiveShapeManifoldTrackerOpe (CATGMLiveShapeManifoldTrackerOpe &);


  //==============================================================================
  // Equal operator
  //==============================================================================
  /**
  * Equal operator : Not implemented. <br>
  **/
  CATGMLiveShapeManifoldTrackerOpe& operator=(CATGMLiveShapeManifoldTrackerOpe&);


  //==============================================================================
  // Data
  //==============================================================================

};

//==============================================================================
// CATGMLiveShapeManifoldTracker - 1
//==============================================================================
/**
* static methode to get the Journal of CATManifold<br>
**/   

ExportedByPersistentCell HRESULT CATGMLiveShapeManifoldTracker(
                             const ListPOfCATBody      & iPreviousBodyList,
                             const ListPOfCATBody      & iCurrentBodyList,
                             const CATCGMJournalList   & iCMJournal,
                             const ListPOfCATManifold  & iPreviousManifoldList,
                             CATSoftwareConfiguration  & iConfig,
                             CATCGMJournalList         & oManifoldJournal);


//==============================================================================
// CATGMLiveShapeManifoldTracker - 2
//==============================================================================
/**
* static methode to get the Journal of CATManifold<br>
**/   

ExportedByPersistentCell HRESULT CATGMLiveShapeManifoldTracker(
                             const ListPOfCATBody      & iPreviousBodyList,
                             const ListPOfCATBody      & iCurrentBodyList,
                             const CATCGMJournalList   & iCMJournal,
                             const CATListOfULONG32    & iGeometryTypeList,
                             CATSoftwareConfiguration  & iConfig,
                             CATCGMJournalList         & oManifoldJournal);






// @nocgmitf
ExportedByPersistentCell CATGMLiveShapeManifoldTrackerOpe * CATCreateLiveShapeManifoldTrackerOpe(
                             CATTopData                * iTopData,
                             const ListPOfCATBody      & iPreviousBodyList,
                             const ListPOfCATBody      & iCurrentBodyList,
                             const CATCGMJournalList   & iCMJournal,
                             const ListPOfCATManifold  & iPreviousManifoldList);

// @nocgmitf
ExportedByPersistentCell CATGMLiveShapeManifoldTrackerOpe * CATCreateLiveShapeManifoldTrackerOpe(
                             CATTopData                * iTopData,
                             const ListPOfCATBody      & iPreviousBodyList,
                             const ListPOfCATBody      & iCurrentBodyList,
                             const CATCGMJournalList   & iCMJournal,
                             const CATListOfULONG32    & iGeometryTypeList);

#endif

