#ifndef CATManifoldMathPoint_h
#define CATManifoldMathPoint_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
#include "CATMathPoint.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldMathPoint : public CATManifoldParameter
{
public:
  CATManifoldMathPoint(CATMathPoint *iValue,
    CATDeclarativeManifold * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATManifoldMathPoint(CATMathPoint *iValue,
    CATCellManifoldGroup * iDeclaration,
    CATLONG32 iKey,
    CATManifoldParamDescription iDescription,
    CATBoolean iEditable=TRUE,
    CATBoolean iActive=TRUE);

  CATBoolean CopyData(CATManifoldParameter &iParameter);

  // Additional Public Declarations
  CATMathPoint GetValue () const;
  HRESULT SetValue (CATMathPoint *value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

  // !! Should be used only in unstream !!
  void SetInitialValue(CATMathPoint *value);
  CATMathPoint GetInitialValue() const;

  void SetFormerValue (CATMathPoint *value);
  CATMathPoint GetFormerValue () const;

  CATManifoldMathPoint* GetAsMathPoint ();

  void Dump(CATCGMOutput& os) const;

  // for CGMReplay
  virtual void SpecificStream(CATCGMStream  & Str);

  static CATManifoldMathPoint * ReadValue(CATCGMStream              & Str, 
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
  
  virtual ~CATManifoldMathPoint();

  CATManifoldMathPoint(CATManifoldMathPoint const& iOther); // forbidden

  CATManifoldMathPoint(CATMathPoint              & iInitialValue,
    CATMathPoint              & iFormerValue,
    CATMathPoint              & iCurrentValue,
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

private: //## implementation
  CATMathPoint _Value;

  CATMathPoint _FormerValue;

  CATMathPoint _InitialValue;
};

#endif
