#ifndef CATManifoldBooleanValue_h
#define CATManifoldBooleanValue_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldBooleanValue : public CATManifoldParameter
{
public:
  CATManifoldBooleanValue(CATBoolean iValue,
    CATDeclarativeManifold * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATManifoldBooleanValue(CATBoolean iValue,
    CATCellManifoldGroup * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATBoolean CopyData(CATManifoldParameter &iParameter);

  CATBoolean GetValue () const;
  HRESULT SetValue (CATBoolean value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

  CATBoolean GetInitialValue() const;
  CATBoolean GetFormerValue () const;

  void Dump(CATCGMOutput& os) const;

  CATManifoldBooleanValue* GetAsBooleanValue ();

  // for CGMReplay
  virtual void SpecificStream(CATCGMStream  & Str);

  static CATManifoldBooleanValue * ReadValue( CATCGMStream              & Str, 
                                              CATLONG32                   iKey, 
                                              CATGeoFactory             * iFactory, 
                                              CATLiveBody               * iLiveBody,
                                              CATDeclarativeManifold *    iDeclaration,
                                              CATCellManifoldGroup   *    iDeclarationCMG,
                                              CATBoolean                  iEditable,
                                              CATBoolean                  iActive,
                                              CATManifoldParamDescription iDescription,
                                              CATLONG32                   iHasChanged);

  virtual int operator == (/*const*/ CATManifoldParameter &iOther) const;

protected:

  virtual ~CATManifoldBooleanValue();
  void SetFormerValue(CATBoolean value);

  CATManifoldBooleanValue(CATBoolean iInitialValue,
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

  static HRESULT SpecificUnstream(CATCGMStream & Str, CATBoolean & oInitialValue, CATBoolean & oFormerValue, CATBoolean & oCurVal);
private:
    
  
  CATManifoldBooleanValue(CATManifoldBooleanValue const& iOther); // forbidden


  virtual HRESULT Check () const;

  //VB7 for CGMReplay
  //presume that this and ioParameter have same key
  virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);


private: 

  CATBoolean _Value;

  CATBoolean _FormerValue;

  CATBoolean _InitialValue;
};

#endif
