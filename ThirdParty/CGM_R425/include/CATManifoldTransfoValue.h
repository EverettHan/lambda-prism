#ifndef CATManifoldTransfoValue_H
#define CATManifoldTransfoValue_H
//
#include "CATGMModelInterfaces.h"
#include "CATManifoldParameter.h"
#include "CATMathTransformation.h"
#ifdef CATIAR213
#include "CATSysBoolean.h"
#else
#include "CATBoolean.h"
#endif

class CATBody;
class CATDeclarativeManifold;
class CATCellManifoldGroup;
class CATLiveBody;
class CATGeoFactory;
class CATCGMStream;

class ExportedByCATGMModelInterfaces CATManifoldTransfoValue : public CATManifoldParameter
{

public:

  CATManifoldTransfoValue(const CATMathTransformation &iValue,
                            CATDeclarativeManifold    * iDeclaration,
                            CATLONG32                   iKey,
                            CATManifoldParamDescription iDescription,
                            CATBoolean                  iEditable=TRUE,
                            CATBoolean                  iActive=TRUE);

  CATManifoldTransfoValue(const CATMathTransformation &iValue,
                            CATCellManifoldGroup       * iDeclaration,
                            CATLONG32                    iKey,
                            CATManifoldParamDescription  iDescription,
                            CATBoolean                   iEditable=TRUE,
                            CATBoolean                   iActive=TRUE);

  virtual CATBoolean CopyData(CATManifoldParameter &iParameter); // ???

  // Additional Public Declarations
  const CATMathTransformation & GetValue () const;  
  const CATMathTransformation & GetInitialValue() const;
  const CATMathTransformation & GetFormerValue () const;

  HRESULT SetValue (const CATMathTransformation &iValue, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

  virtual void Dump(CATCGMOutput& os) const;
  
  CATManifoldTransfoValue * GetAsTransfoValue() const;

  // for CGMReplay
  virtual void SpecificStream(CATCGMStream  & Str);

  static CATManifoldTransfoValue * ReadValue(CATCGMStream              & Str, 
                                                CATLONG32                   iKey, 
                                                CATGeoFactory             * iFactory, 
                                                CATLiveBody               * iLiveBody,
                                                CATDeclarativeManifold *    iDeclaration,
                                                CATCellManifoldGroup   *    iDeclarationCMG,
                                                CATBoolean                  iEditable,
                                                CATBoolean                  iActive,
                                                CATManifoldParamDescription iDescription,
                                                CATLONG32                   iHasChanged);

  virtual int operator == (/*const*/ CATManifoldParameter &iOther) const; // Mais quelle horreur...

  virtual void Scale(const double iXScaleFactor);

private:

  virtual ~CATManifoldTransfoValue();

  // Copy - constructor 
  CATManifoldTransfoValue(const CATManifoldTransfoValue & iOther);

  // Private constructor
  CATManifoldTransfoValue(const CATMathTransformation  & iInitialValue,
                            const CATMathTransformation  & iFormerValue,
                            const CATMathTransformation  & iCurrentValue,
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
  virtual HRESULT UpdateSpecificParameter (CATManifoldParameter *& ioParameter);

  void SetFormerValue (const CATMathTransformation &iValue);


  // -----------------------------------------------------
  // Internal Data 
  // -----------------------------------------------------

  CATMathTransformation _Value;
  CATMathTransformation _FormerValue;
  CATMathTransformation _InitialValue;

};

#endif
