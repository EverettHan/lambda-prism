#ifndef CATGeoToTopOperatorExt_H
#define CATGeoToTopOperatorExt_H

//=============================================================================
// CATGeoToTopOperatorExt
//-----------------------------------------------------------------------------
// 2011 WEEK 03    Creation                                                   LD2
// 12/08/2015      Create CGMReplay infrsstructure because it's needed for 
//                 FaceOperator, which inherits from this class.              G5S
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATExtTopOperator.h"
#include "CATMathInline.h"
#include "CATCGMJournal.h"

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATCGMJournalList;
class CATCGMJournalInfo;
class CATTopologicalOperator;
class CATCGMOperator;

class ExportedByCATTopologicalObjects CATGeoToTopOperatorExt: public CATExtTopOperator
{

public:

  CATCGMNewClassArrayDeclare;

  /** @nodoc */
  static void AssociateOperatorAndExtensible(CATExtGeoOperator *& OldExtensible, CATExtGeoOperator * NewExtensible, CATCGMOperator * Operator);

  /**  @nodoc */
  CATGeoToTopOperatorExt(CATGeoFactory      *iFactory, 
    CATTopData * iData);

  /**  @nodoc */
  CATGeoToTopOperatorExt(CATGeoFactory      *iFactory,
    CATTopData * iData,
    CATBody            *iBodyForCellCreation);

  /**  @nodoc */
  CATGeoToTopOperatorExt(CATGeoFactory      *iFactory, 
    CATBody            *iBodyForCellCreation,
    CATBodyFreezeMode   iBodyFreezeMode=CATBodyFreezeOn,
    CATCGMJournalList  *iReport=NULL);

  /**  @nodoc */
  void FillResultBody();

  /** @nodoc */
  void SetLog(CATLONG32 );

  /** @nodoc */
  virtual ~CATGeoToTopOperatorExt();

  /** @nodoc */
  void SetTolerance(double iTol);

  /** @nodoc */
  double GetTolerance()const;

  /** @nodoc */
  void SetUseGeometriesInJournalItems(int iUseGeometriesInJournalItems);

  /** @nodoc */
  int GetUseGeometriesInJournalItems();

  /** @nodoc */
  void Report(CATCGMJournal::Type   iType,
    const CATGeometry    *iBeforeObjects,
    const CATGeometry    *iAfterObjects,
    CATCGMJournalInfo    *iOptionalInfo=NULL);

  /** @nodoc */
  CATCGMJournalList* GetReport();

  /** @nodoc */
  CATBody * GetTheResultBody();

  // RequireDefinitionOfInputAndOutputObjects for CGMReplay.
  void   RDOIAOO(CATTopOperator & iOperator);

protected:
  // Methods for CGMReplay recording. 
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutputExt(CATCGMOutput & os);

  virtual void DumpExt(CATCGMOutput& os);

  /**  @nodoc */
  CATCGMJournalList*   _OldJournal;
  /**  @nodoc */
  double	                 _tolerance;
  /**  @nodoc */
  CATBody                * _Draft;
  /**  @nodoc */
  CATDomain              * _manifold;
  /**  @nodoc */
  CATTopologicalOperator * _cleaner;

private:

  int                      _UseGeometriesInJournalItems;
};

#endif

