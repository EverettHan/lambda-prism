#ifndef CATManifoldIntValue_h
#define CATManifoldIntValue_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldIntValue : public CATManifoldParameter
{

public:
  CATManifoldIntValue(CATLONG32 iValue,
    CATDeclarativeManifold * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATManifoldIntValue(CATLONG32 iValue,
    CATCellManifoldGroup * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATBoolean CopyData(CATManifoldParameter &iParameter);

  CATLONG32 GetValue () const;
  HRESULT SetValue (CATLONG32 value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

  CATLONG32 GetInitialValue() const;
  CATLONG32 GetFormerValue () const;

  void Dump(CATCGMOutput& os) const;

  CATManifoldIntValue* GetAsIntValue ();

  // for CGMReplay
  virtual void SpecificStream(CATCGMStream  & Str);

  static CATManifoldIntValue *  ReadValue(CATCGMStream              & Str, 
                                          CATLONG32                   iKey, 
                                          CATGeoFactory             * iFactory, 
                                          CATLiveBody               * iLiveBody,
                                          CATDeclarativeManifold *    iDeclaration,
                                          CATCellManifoldGroup   *    iDeclarationCMG,
                                          CATBoolean                  iEditable,
                                          CATBoolean                  iActive,
                                          CATManifoldParamDescription iDescription,
                                          CATLONG32                   iHasChanged);

  virtual int operator == (CATManifoldParameter &iOther) const;

  virtual CATManifoldParamId * CreateManifoldParamId() const;

private:
    
  virtual ~CATManifoldIntValue();
  
  CATManifoldIntValue(CATManifoldIntValue const& iOther); // forbidden

  CATManifoldIntValue(CATLONG32                   iInitialValue,
    CATLONG32                   iFormerValue,
    CATLONG32                   iCurrentValue,
    CATBody                   * iLocalisation,
    CATDeclarativeManifold    * iDeclaration,
    CATCellManifoldGroup      * iDeclarationCMG,
    CATLONG32                   iKey,
    CATBoolean                  iEditable,
    CATBoolean                  iActive,
    CATManifoldParamDescription iDescription,
    CATLONG32                   iHasChanged);

  virtual HRESULT Check () const;

  //VB7 for CGMReplay
  //presume that this and ioParameter have same key
  virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);

  void SetFormerValue (CATLONG32 value);

private: //## implementation

  CATLONG32 _Value;

  CATLONG32 _FormerValue;

  CATLONG32 _InitialValue;
};

#endif
