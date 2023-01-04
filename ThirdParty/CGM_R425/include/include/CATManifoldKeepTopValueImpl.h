#ifndef CATManifoldKeepTopValueImpl_h
#define CATManifoldKeepTopValueImpl_h 1

#include "CATManifoldParameter.h"
#include "CATManifoldBaseParameter.h"
#include "CATManifoldKeepTopValue.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATEdge.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "PersistentCell.h"


class CATBody;
class CATlsoAdvancedStampData;
class CATDeclarativeManifold;
class CATCellManifoldGroup;

/**
 * @brief
 *  Parameter deriving from CATManifoldBooleanValue used for the POC of KeepTopAdvStamp project.
 *
 * [W16-Y2021] Creation after recognition of advanced stamp with edge list to keep.
 * Key 39 & 40
 *
 * @author
 *  YSY2
 */
class ExportedByPersistentCell CATManifoldKeepTopValueImpl : public CATManifoldKeepTopValue
{
public:

  //CATCGMDeclareAttribute(CATManifoldKeepTopValueImpl, CATManifoldKeepTopValue);

  // CONSTRUCTORS
  CATManifoldKeepTopValueImpl(CATBoolean                  iValue,
                          CATDeclarativeManifold * iDeclaration,
                          CATLONG32                   iKey,
                          CATManifoldParamDescription iDescription,
                          CATBoolean                  iEditable = TRUE,
                          CATBoolean                  iActive = TRUE);

  CATManifoldKeepTopValueImpl(CATBoolean                  iValue,
                          CATCellManifoldGroup * iDeclaration,
                          CATLONG32                   iKey,
                          CATManifoldParamDescription iDescription,
                          CATBoolean                  iEditable = TRUE,
                          CATBoolean                  iActive = TRUE);

  ~CATManifoldKeepTopValueImpl();

  /**
   * @brief
   *  Retrieve the edge list to keep
   * 
   * @param
   *  oEdgeList [out]
   *  Edge list to keep.
   */
  virtual void GetEdgeListToKeep(ListPOfCATEdge & oEdgeList);

  // for CGMReplay
  virtual void SpecificStream(CATCGMStream & Str);

  static CATManifoldKeepTopValue * ReadValue(CATCGMStream & Str,
                                             CATLONG32                   iKey,
                                             CATGeoFactory * iFactory,
                                             CATLiveBody * iLiveBody,
                                             CATDeclarativeManifold * iDeclaration,
                                             CATCellManifoldGroup * iDeclarationCMG,
                                             CATBoolean                  iEditable,
                                             CATBoolean                  iActive,
                                             CATManifoldParamDescription iDescription,
                                             CATLONG32                   iHasChanged);

  CATBoolean CopyData(CATManifoldParameter & iParameter);

  // Set methods
  void SetAdvancedStampData(CATlsoAdvancedStampData * iData);

protected:
  virtual CATlsoAdvancedStampData * GetAdvancedStampData() const;

private:

  //

  CATManifoldKeepTopValueImpl(CATManifoldKeepTopValueImpl const & iOther); // forbidden
  CATManifoldKeepTopValueImpl(CATBoolean iInitialValue,
                          CATBoolean                  iFormerValue,
                          CATBoolean                  iCurrentValue,
                          CATBody * iLocalisation,
                          CATDeclarativeManifold * iDeclaration,
                          CATCellManifoldGroup * iDeclarationCMG,
                          CATLONG32                   iKey,
                          CATBoolean                  iEditable,
                          CATBoolean                  iActive,
                          CATManifoldParamDescription iDescription,
                          CATLONG32                   iHasChanged);


private:

  // INTERNAL DATA
  /// Data structure containing Fillet, Draft DM and Edge List to Keep
  CATlsoAdvancedStampData * _AdvancedStampData;
};

#endif
