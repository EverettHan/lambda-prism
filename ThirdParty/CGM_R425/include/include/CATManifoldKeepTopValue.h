#ifndef CATManifoldKeepTopValue_h
#define CATManifoldKeepTopValue_h 1

#include "CATManifoldParameter.h"
#include "CATManifoldBooleanValue.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATEdge.h"


class CATBody;
class CATlsoAdvancedStampData;

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
class ExportedByCATGMModelInterfaces CATManifoldKeepTopValue : public CATManifoldBooleanValue
{
  friend class CATSingleManifoldEditorImpl;

public:
  // CONSTRUCTORS
  CATManifoldKeepTopValue(CATBoolean                  iValue,
                          CATDeclarativeManifold    * iDeclaration,
                          CATLONG32                   iKey,
                          CATManifoldParamDescription iDescription,
                          CATBoolean                  iEditable=TRUE,
                          CATBoolean                  iActive=TRUE);

  CATManifoldKeepTopValue(CATBoolean                  iValue,
                          CATCellManifoldGroup      * iDeclaration,
                          CATLONG32                   iKey,
                          CATManifoldParamDescription iDescription,
                          CATBoolean                  iEditable=TRUE,
                          CATBoolean                  iActive=TRUE);

  /**
   * @brief
   *  Retrieve the edge list to keep. 
   * TODO
   * @param 
   *  oEdgeList [out]
   *  Edge list to keep.
   */
  virtual void GetEdgeListToKeep(ListPOfCATEdge &oEdgeList) = 0;



  void Dump(CATCGMOutput & os) const;

  CATManifoldKeepTopValue * GetAsKeepTopValue();


  virtual int operator == (/*const*/ CATManifoldParameter & iOther) const;

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATManifoldKeepTopValue();

protected:

  virtual CATlsoAdvancedStampData * GetAdvancedStampData() const = 0;

  CATManifoldKeepTopValue(CATBoolean iInitialValue,
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

  void InitMembers();
  void ResetMembers();

  

  CATManifoldKeepTopValue(CATManifoldKeepTopValue const & iOther); // forbidden


  ////VB7 for CGMReplay
  ////presume that this and ioParameter have same key
  //virtual HRESULT UpdateSpecificParameter(CATManifoldParameter *& ioParameter);

  //void SetFormerValue(CATBoolean value);

private:
};

#endif
