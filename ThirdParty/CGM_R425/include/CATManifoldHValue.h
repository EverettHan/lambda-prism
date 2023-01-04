#ifndef CATManifoldHValue_h
#define CATManifoldHValue_h 

#include "CATManifoldParameter.h"
class CATBody;
class CATHVertex;
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATManifoldHValue : public CATManifoldParameter
{

public:
  double  GetValue() const;
  double* GetFirstDeriv() const;

  HRESULT SetValue(double iValue, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);
  HRESULT SetFirstDeriv(double* iFirstDeriv);

  // --------------------------------------------------------------------------
  // CGM internal use only
  // --------------------------------------------------------------------------
  CATManifoldHValue(double iValue, double* iFirstDeriv, double* iSecondDeriv, CATDeclarativeManifold* iDeclaration, CATLONG32 iKey, CATHVertex* iHVertex, CATManifoldParamDescription iDescription, CATBoolean iEditable=TRUE, CATBoolean iActive=TRUE);

  CATBoolean CopyData(CATManifoldParameter &iParameter);

  /*
  double* GetSecondDeriv() const;
  HRESULT SetSecondDeriv(double* value);

  double GetInitialValue() const;
  double* GetInitialFirstDeriv() const;
  double* GetInitialSecondDeriv() const;

  double GetFormerValue() const;
  double* GetFormerFirstDeriv() const;
  double* GetFormerSecondDeriv() const;
  */
  void Dump(CATCGMOutput& os) const;

  CATHVertex* GetHVertex(); // Read only. Cannot be changed.

  virtual void SpecificStream(CATCGMStream  & Str);

  static CATManifoldHValue * ReadValue(CATCGMStream              & Str, 
                                       CATLONG32                   iKey, 
                                       CATGeoFactory             * iFactory, 
                                       CATLiveBody               * iLiveBody,
                                       CATDeclarativeManifold    * iDeclaration,
                                       CATCellManifoldGroup      * iDeclarationCMG,
                                       CATBoolean                  iEditable,
                                       CATBoolean                  iActive,
                                       CATManifoldParamDescription iDescription,
                                       CATLONG32                   iHasChanged);

  virtual int operator == (/*const*/ CATManifoldParameter &iOther) const;

  virtual void Scale(const double iXScaleFactor);

  // --------------------------------------------------------------------------
  // Private Section
  // --------------------------------------------------------------------------
private:
  
  virtual ~CATManifoldHValue();

  CATManifoldHValue(CATManifoldHValue const& iOther); // forbidden

  CATManifoldHValue* GetAsHValue();

  virtual HRESULT Check() const;

  static void Dump(CATCGMOutput& os, const double iValue, const double* iFirstDeriv, const double* iSecondDeriv);

  //VB7 for CGMReplay
  //presume that this and ioParameter have same key
  virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);

  // --------------------------------------------------------------------------
  // Data Section
  // --------------------------------------------------------------------------
private: 
    double  _Value;
    double* _FirstDeriv;
    double* _SecondDeriv;

    double  _FormerValue;
    double* _FormerFirstDeriv;
    double* _FormerSecondDeriv;

    double  _InitialValue;
    double* _InitialFirstDeriv;
    double* _InitialSecondDeriv;

    CATHVertex* _HVertex;
};


#endif
