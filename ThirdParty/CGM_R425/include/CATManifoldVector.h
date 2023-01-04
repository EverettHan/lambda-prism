#ifndef CATManifoldVector_h
#define CATManifoldVector_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
#include "CATMathVector.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldVector : public CATManifoldParameter
{

  public:
      CATManifoldVector(CATMathVector *iValue,
        CATDeclarativeManifold * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATManifoldVector(CATMathVector *iValue,
        CATCellManifoldGroup * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATBoolean CopyData(CATManifoldParameter &iParameter);

      CATMathVector GetValue () const;
      HRESULT SetValue (const CATMathVector * iValue, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

      CATMathVector GetInitialValue() const;
      CATMathVector GetFormerValue () const;

      CATManifoldVector* GetAsVector ();

      void Dump(CATCGMOutput& os) const;

      // for CGMReplay
      virtual void SpecificStream(CATCGMStream  & Str);

      static CATManifoldVector *  ReadValue(CATCGMStream              & Str, 
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

      virtual void Scale(const double iXScaleFactor);

  private:
      
    virtual ~CATManifoldVector();

    CATManifoldVector(CATManifoldVector const& iOther); // forbidden

    CATManifoldVector(CATMathVector             & iInitialValue,
                      CATMathVector             & iFormerValue,
                      CATMathVector             & iCurrentValue,
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

      void SetFormerValue (CATMathVector *value);

  private: //## implementation
      CATMathVector _Value;

      CATMathVector _FormerValue;

      CATMathVector _InitialValue;
};


#endif
