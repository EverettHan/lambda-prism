#ifndef CATManifoldPatternLiveBodyValue_h
#define CATManifoldPatternLiveBodyValue_h 1

#include "CATManifoldParameter.h"
#include "CATGMModelInterfaces.h"
#include "CATLiveBody.h"
class CATBody;

class ExportedByCATGMModelInterfaces CATManifoldPatternLiveBodyValue : public CATManifoldParameter
{

  public:
      CATManifoldPatternLiveBodyValue(CATLiveBody *iValue,
        CATDeclarativeManifold * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATManifoldPatternLiveBodyValue(CATLiveBody *iValue,
        CATCellManifoldGroup * iDeclaration,
        CATLONG32 iKey,
        CATManifoldParamDescription iDescription,
        CATBoolean iEditable=TRUE,
        CATBoolean iActive=TRUE);

      CATBoolean CopyData(CATManifoldParameter &iParameter);

      CATLiveBody *GetValue () const;
      HRESULT SetValue (CATLiveBody *value, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

      CATLiveBody *GetInitialValue() const;
      CATLiveBody *GetFormerValue () const;

      void Dump(CATCGMOutput& os) const;

      CATManifoldPatternLiveBodyValue* GetAsLiveBody ();

      // for CGMReplay
      virtual void WriteParameter(CATCGMStream  & Str);
      static CATManifoldPatternLiveBodyValue * ReadValue(CATCGMStream & Str, CATLONG32 iKey, CATGeoFactory* iFactory, CATLiveBody* iLiveBody);

      virtual int operator == (/*const*/ CATManifoldParameter &iOther) const;

  private:
 
    virtual ~CATManifoldPatternLiveBodyValue();

    CATManifoldPatternLiveBodyValue(CATManifoldPatternLiveBodyValue const& iOther);

    //## Other Operations (specified)
    virtual HRESULT Check () const;

    //VB7 for CGMReplay
    //presume that this and ioParameter have same key
    virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);

    //## Get and Set Operations for Class Attributes (generated)

      void SetFormerValue (CATLiveBody *value);

    // Additional Private Declarations

  private: //## implementation
    // Data Members for Class Attributes

      CATLiveBody *_Value;

      CATLiveBody *_FormerValue;

      CATLiveBody *_InitialValue;

    // Additional Implementation Declarations

};

// Class CATManifoldPatternLiveBodyValue 



#endif
