// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
// ----------------------------------------------------------------------------//
//==========================================================
// !!!!!!!!!!!!!!!!!!!!!!DO NOT USE!!!!!!!!!!!!!!!!!!!!!!!!!
//==========================================================
// WORK IN PROGRESS VB7 W05 2018


#ifndef CATGMDRepLabelServices_H
#define CATGMDRepLabelServices_H

#include "ListPOfCATDRepLabel.h"
#include "PersistentCell.h"
#include "CATTopOperator.h"

class CATDRepLabel;
class CATCGMJournalList;
class CATGMDRepLabelServicesImpl;
class CATDRepLabelAssoc;

class ExportedByPersistentCell CATGMDRepLabelServices : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATGMDRepLabelServices);
public:

  //Constructor
  CATGMDRepLabelServices(CATGeoFactory              *iFactory,
                         CATTopData                 *iTopData,
                         CATGMDRepLabelServicesImpl *iImpl);
  //Destructor
  virtual ~CATGMDRepLabelServices();


  HRESULT GetDRepLabelImages(CATDRepLabel * iDRepLabel, CATDRepLabelAssoc *& oDRepLabelAssoc);

  virtual int RunOperator();

  // ------------------
  // CGMReplay Methodes
  // ------------------
  /** @nodoc @nocgmitf */
  static const CATString *GetDefaultOperatorId();
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  void WriteInput(CATCGMStream  & Str);
  /** @nodoc @nocgmitf */
  void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  void DumpOutput(CATCGMOutput& os);
  /** @nodoc @nocgmitf */
  void RequireDefinitionOfInputAndOutputObjects();
  /** @nodoc @nocgmitf */
  void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  void DumpOutput(CATCGMStream & Str, CATCGMOutput & os , int VersionNumber=1);
  /** @nodoc @nocgmitf */
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  CATBoolean ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  /** @nodoc @nocgmitf */
  CATBoolean ValidateOutput(CATCGMStream & Str, CATCGMOutput & os, int VersionNumber=1);
  /** @nodoc @nocgmitf */
  CATBoolean ReadReferenceOutput(CATCGMStream &Str);

protected:
  CATGMDRepLabelServicesImpl * GetGMDRepLabelServicesImpl();

};

ExportedByPersistentCell CATGMDRepLabelServices * CATCreateGMDRepLabelServices(CATGeoFactory     * iFactory,
                                                                               CATTopData        * iTopData,
                                                                               ListPOfCATBody    & iInputBodyList, 
                                                                               ListPOfCATBody    & iOutputBodyList,
                                                                               CATCGMJournalList * iCMJournal); 

#endif
