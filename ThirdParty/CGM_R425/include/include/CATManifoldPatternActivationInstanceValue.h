#ifndef CATManifoldPatternActivationInstanceValue_h
#define CATManifoldPatternActivationInstanceValue_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
#include "CATPatternActivationInstanceStructure.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldPatternActivationInstanceValue : public CATManifoldParameter
{

  public:
    //## Constructors (generated)
      CATManifoldPatternActivationInstanceValue(CATPatternActivationInstanceStructure *iValue,
        CATDeclarativeManifold * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      //## Constructors 
      CATManifoldPatternActivationInstanceValue(CATPatternActivationInstanceStructure *iValue,
        CATCellManifoldGroup * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATBoolean CopyData(CATManifoldParameter &iParameter);

    // Additional Public Declarations
      CATPatternActivationInstanceStructure GetValue () const;
      HRESULT SetValue (CATPatternActivationInstanceStructure *value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

      CATPatternActivationInstanceStructure GetInitialValue() const;
      CATPatternActivationInstanceStructure GetFormerValue () const;

      void Dump(CATCGMOutput& os) const;

      CATManifoldPatternActivationInstanceValue* GetAsActivationInstanceValue ();

     // for CGMReplay
      virtual void SpecificStream(CATCGMStream  & Str);

      static CATManifoldPatternActivationInstanceValue * ReadValue(CATCGMStream              & Str, 
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

  private:
    
    //## Destructor (generated)
    virtual ~CATManifoldPatternActivationInstanceValue();

    CATManifoldPatternActivationInstanceValue(CATManifoldPatternActivationInstanceValue const& iOther); // forbidden

    CATManifoldPatternActivationInstanceValue(CATPatternActivationInstanceStructure     & iInitialValue,
                                              CATPatternActivationInstanceStructure     & iFormerValue,
                                              CATPatternActivationInstanceStructure     & iCurrentValue,
                                              CATBody                   * iLocalisation,
                                              CATDeclarativeManifold    * iDeclaration,
                                              CATCellManifoldGroup      * iDeclarationCMG,
                                              CATLONG32                   iKey,
                                              CATBoolean                  iEditable,
                                              CATBoolean                  iActive,
                                              CATManifoldParamDescription iDescription,
                                              CATLONG32                   iHasChanged);

      virtual HRESULT Check () const;

      void SetFormerValue (CATPatternActivationInstanceStructure *value);

      //VB7 for CGMReplay
      //presume that this and ioParameter have same key
      virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);

  private: //## implementation
      CATPatternActivationInstanceStructure _Value;

      CATPatternActivationInstanceStructure _FormerValue;

      CATPatternActivationInstanceStructure _InitialValue;
};

#endif
