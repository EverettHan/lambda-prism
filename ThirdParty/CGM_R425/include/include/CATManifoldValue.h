#ifndef CATManifoldValue_h
#define CATManifoldValue_h 1

// CATManifoldParameter
#include "CATManifoldParameter.h"
class CATBody;
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATManifoldValue : public CATManifoldParameter
{

  public:
      CATManifoldValue(double iValue,
                      CATDeclarativeManifold * iDeclaration,
                      CATLONG32 iKey,
                      CATManifoldParamDescription iDescription,
                      CATBoolean iEditable=TRUE,
                      CATBoolean iActive=TRUE);

      CATManifoldValue(double iValue,
        CATCellManifoldGroup * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATBoolean CopyData(CATManifoldParameter &iParameter);

      double GetValue () const;
      HRESULT SetValue (double value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

      double GetInitialValue() const;
      double GetFormerValue () const;

      void Dump(CATCGMOutput& os) const;

      CATManifoldValue* GetAsValue ();

      virtual void SpecificStream(CATCGMStream  & Str);
      
      static CATManifoldValue * ReadValue(CATCGMStream              & Str, 
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

      virtual CATManifoldParamId * CreateManifoldParamId() const;

protected :

      virtual ~CATManifoldValue();

  private:

    CATManifoldValue(CATManifoldValue const& iOther); // forbidden

       CATManifoldValue(double                      iInitialValue,
                        double                      iFormerValue,
                        double                      iCurrentValue,
                        CATBody                   * iLocalisation,
                        CATDeclarativeManifold    * iDeclaration,
                        CATCellManifoldGroup      * iDeclarationCMG,
                        CATLONG32                   iKey,
                        CATBoolean                  iEditable,
                        CATBoolean                  iActive,
                        CATManifoldParamDescription iDescription,
                        CATBoolean                  iHasChanged);

      virtual HRESULT Check () const;

      //VB7 for CGMReplay
      //presume that this and ioParameter have same key
      virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);

      void SetFormerValue (double value);

  private: //## implementation
      double _Value;

      double _FormerValue;

      double _InitialValue;
};


#endif
