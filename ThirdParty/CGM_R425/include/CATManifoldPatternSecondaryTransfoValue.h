#ifndef CATManifoldPatternSecondaryTransfoValue_h
#define CATManifoldPatternSecondaryTransfoValue_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
#include "CATMathTransformation.h"
#include "CATMathVector.h"
#include "CATPatternSecondaryTransfoStructure.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldPatternSecondaryTransfoValue : public CATManifoldParameter
{

  public:
      CATManifoldPatternSecondaryTransfoValue(CATPatternSecondaryTransfoStructure *iValue,
        CATDeclarativeManifold * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATManifoldPatternSecondaryTransfoValue(CATPatternSecondaryTransfoStructure *iValue,
        CATCellManifoldGroup * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATBoolean CopyData(CATManifoldParameter &iParameter);
  
      // Additional Public Declarations
      CATPatternSecondaryTransfoStructure GetValue () const;
      HRESULT SetValue (CATPatternSecondaryTransfoStructure *value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

      CATPatternSecondaryTransfoStructure GetInitialValue() const;
      CATPatternSecondaryTransfoStructure GetFormerValue () const;

      void Dump(CATCGMOutput& os) const;

      CATManifoldPatternSecondaryTransfoValue* GetAsMathTransfo ();

      // for CGMReplay
      virtual void SpecificStream(CATCGMStream  & Str);

      static CATManifoldPatternSecondaryTransfoValue * ReadValue(CATCGMStream              & Str, 
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

    virtual ~CATManifoldPatternSecondaryTransfoValue();
    
    CATManifoldPatternSecondaryTransfoValue(CATManifoldPatternSecondaryTransfoValue const& iOther);

    CATManifoldPatternSecondaryTransfoValue(CATPatternSecondaryTransfoStructure  & iInitialValue,
                                            CATPatternSecondaryTransfoStructure  & iFormerValue,
                                            CATPatternSecondaryTransfoStructure  & iCurrentValue,
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

      void SetFormerValue (CATPatternSecondaryTransfoStructure *value);

  private: //## implementation

      CATPatternSecondaryTransfoStructure _Value;

      CATPatternSecondaryTransfoStructure _FormerValue;

      CATPatternSecondaryTransfoStructure _InitialValue;

private: //utilities
  CATBoolean AreSameTransfo( CATMathTransformation & iMathTransformation1, CATMathTransformation & iMathTransformation2);
  CATBoolean AreSameVector(const CATMathVector & iVector1, const CATMathVector & iVector2);

};

#endif
