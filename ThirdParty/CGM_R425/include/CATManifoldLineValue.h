#ifndef CATManifoldLineValue_h
#define CATManifoldLineValue_h 1

// CATManifoldParameter
#include "CATManifoldParameter.h"
class CATBody;
#include "CATGMModelInterfaces.h"
#include "CATMathLine.h"

class ExportedByCATGMModelInterfaces CATManifoldLineValue : public CATManifoldParameter
{

public:
  CATManifoldLineValue(CATMathLine *iValue,
    CATDeclarativeManifold * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATManifoldLineValue(CATMathLine *iValue,
    CATCellManifoldGroup * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATBoolean CopyData(CATManifoldParameter &iParameter);

  CATMathLine GetValue () const;
  HRESULT SetValue (CATMathLine *value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

  CATMathLine GetInitialValue() const;
  CATMathLine GetFormerValue () const;

  void Dump(CATCGMOutput& os) const;

  CATManifoldLineValue* GetAsLineValue ();

  // for CGMReplay
  virtual void SpecificStream(CATCGMStream  & Str);

  static CATManifoldLineValue *  ReadValue(CATCGMStream              & Str, 
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

  virtual void Scale(const double iXScaleFactor);

private:

  virtual ~CATManifoldLineValue();

  CATManifoldLineValue(CATManifoldLineValue const& iOther); // forbidden

  CATManifoldLineValue(CATMathLine               & iInitialValue,
    CATMathLine               & iFormerValue,
    CATMathLine               & iCurrentValue,
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

  void SetFormerValue (CATMathLine *value);

private: //## implementation
  CATMathLine _Value;

  CATMathLine _FormerValue;

  CATMathLine _InitialValue;
};

#endif
