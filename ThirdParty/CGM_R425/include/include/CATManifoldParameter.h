#ifndef CATManifoldParameter_h
#define CATManifoldParameter_h 1

#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"
#include "CATDeclarativeManifold.h"
#include "CATCellManifoldGroup.h"
#include "CATManifoldBaseParameter.h"
#include "CATGMLiveShapeDef.h"

class CATCGMStream;

#ifndef NULL
#define NULL 0
#endif

class CATDeclarativeManifoldCGM;
class CATCellManifoldGroupCGM;
class CATManifoldValue;
class CATManifoldHValue;
class CATManifoldAxis;
class CATManifoldIntValue;
class CATManifoldVector;
class CATManifoldMathPoint;
class CATManifoldLineValue;
class CATManifoldPatternActivationInstanceValue;
class CATLiveBody;
class CATManifoldBooleanValue;
class CATManifoldPatternSecondaryTransfoValue;
class CATManifoldPatternLiveBodyValue;
class CATGeoFactory;
class CATManifold;
class CATManifoldParamId;
class CATManifoldTransfoValue;
class CATManifoldKeepTopValue;

//-----------------------------------------------------------------------------
// Stream/Unstream version
//-----------------------------------------------------------------------------
#define MANIFOLDPARAMETER_CURRENTVERSION 2

class ExportedByCATGMModelInterfaces CATManifoldParameter : public CATManifoldBaseParameter
{
  friend class CATGMLiveSpecChgUtils;  
  friend class CATlsoManifoldEditorUtilities; 
public:

  enum MPSource
  {
    CGM=0, // default
    Kwe_Publish=1,
    Kwe_UnPublish=2
  };

  CATManifoldParameter(CATDeclarativeManifold   * iDeclaration,
                      CATLONG32                   iKey,
                      CATManifoldParamDescription iDescription,
                      CATBoolean                  iEditable,
                      CATBoolean                  iActive);

  CATManifoldParameter(CATCellManifoldGroup     * iDeclaration,
                      CATLONG32                   iKey,
                      CATManifoldParamDescription iDescription,
                      CATBoolean                  iEditable,
                      CATBoolean                  iActive);
  /* Contructor to use one day*/
  CATManifoldParameter(CATManifold              * ipManifold,
                       CATManifoldParamId       & ipManifoldParamId,
                       CATBoolean                 iEditable,
                       CATBoolean                 iActive);

    
  // From mother class
  // --------------------------------------------------------
  virtual int GetKey() const;      
  virtual CATManifoldParamDescription GetDescription() const;
  virtual CATBoolean GetActive () const;

  CATBoolean GetHasChanged() const;
  CATBoolean GetHasChangedSystem() const;
  CATBoolean GetHasChangedUser() const;
  CATBoolean GetHasChangedSimilar() const;
  CATBoolean GetPropagated () const;
  void SetActive (CATBoolean iActive, CATLONG32 iValueType=MANIFOLDPARAMETER_HASCHANGED_USER);

  CATBoolean GetEditable() const;

  virtual CATBoolean CopyData(CATManifoldParameter &iParameter);

  virtual CATManifoldParameter * GetAsManifoldParameter() const;
  virtual CATManifoldValue     * GetAsValue ();
  virtual CATManifoldHValue    * GetAsHValue ();
  virtual CATManifoldAxis      * GetAsAxis ();
  virtual CATManifoldIntValue  * GetAsIntValue ();
  virtual CATManifoldLineValue * GetAsLineValue ();
  virtual CATManifoldVector    * GetAsVector ();
  virtual CATManifoldMathPoint * GetAsMathPoint ();
  virtual CATManifoldTransfoValue * GetAsTransfoValue() const;
  virtual CATManifoldPatternActivationInstanceValue * GetAsActivationInstanceValue ();
  virtual CATManifoldBooleanValue                   * GetAsBooleanValue ();
  virtual CATManifoldPatternSecondaryTransfoValue   * GetAsMathTransfo(); // To remove
  virtual CATManifoldPatternLiveBodyValue           * GetAsLiveBody();

  virtual CATManifoldKeepTopValue                   * GetAsKeepTopValue();

  CATDeclarativeManifold* GetDeclaration () const;
  CATCellManifoldGroup * GetDeclarationCMG () const; // ajout zus
  void SetDeclaration (CATDeclarativeManifold * value);
  void SetDeclarationCMG (CATCellManifoldGroup * value); // ajout ZUS

  virtual void Dump(CATCGMOutput& os) const;

  static CATString GetFunction(const CATLONG32 iKey);
  // ----------------------------------------------------------------------------------------------------------






  // ----------------------------------------------------------------------------------------------------------
  // Do not use: private section
  // ----------------------------------------------------------------------------------------------------------
  void HasChanged(CATLONG32 iHasChangedValue=MANIFOLDPARAMETER_HASCHANGED_USER);
  void HasNotChanged();
  
  const CATManifoldParameter::MPSource & GetSourceOrigin() const;

  //VB7 for CGMReplay
  HRESULT UpdateParameter (CATManifoldParameter*& ioParameter);

  void WriteParameter(CATCGMStream  & Str);

  static CATManifoldParameter * ReadParameter(CATCGMStream  & Str, CATGeoFactory* iFactory, CATLiveBody* iLiveBody);

  virtual CATManifoldParamId * CreateManifoldParamId() const /*= 0*/;

  virtual int operator==(/*const*/ CATManifoldParameter &iOther) const = 0; 

  virtual void Scale(const double iXScaleFactor);

protected : 

  virtual ~CATManifoldParameter();

  CATManifoldParameter(CATManifoldParameter const& iOther);  // Forbidden
  CATManifoldParameter &operator=(const CATManifoldParameter &iParameter); // Forbidden

  // Stream
  void GeneralStream(CATCGMStream  & Str);
  virtual void SpecificStream(CATCGMStream  & Str);
 
  CATManifoldParameter(CATDeclarativeManifold *    iDeclaration,
                       CATCellManifoldGroup   *    iDeclarationCMG,
                       CATLONG32                   iKey,
                       CATBoolean                  iEditable,
                       CATBoolean                  iActive,
                       CATManifoldParamDescription iDescription,
                       CATLONG32                   iHasChanged);

	CATGeoFactory * GetFactory() const;

  void SetEditable(CATBoolean IsEditable);
  void SetHasChanged(CATLONG32 value=MANIFOLDPARAMETER_HASCHANGED_USER);
  void SetSourceOrigin(CATManifoldParameter::MPSource iSource);
  void SetPropagated(CATBoolean iPropagated);

  friend class CATOneDRepModification;
  friend class CATManifoldUpdaterImpl;

private:

  void SetKey (CATLONG32 value);

  void SetDescription (CATManifoldParamDescription value);

  void CertifyPropagated ();

  virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter)=0; //presume that this and ioParameter have same key/same DM/CMG & same Id

  // SpecChg Management
  HRESULT PutSpecChg();
  HRESULT UpdateSpecChg();
  HRESULT ReleaseSpecChg();

  // Data Members 
  CATDeclarativeManifold * _Declaration;
  CATCellManifoldGroup   * _DeclarationCMG; 
  CATLONG32                   _Key;
  CATBoolean                  _Editable;
  CATManifoldParamDescription _Description;
  CATBoolean                  _HasChanged;
  CATBoolean                  _Active;
  CATBoolean                  _Propagated;

  MPSource   _SrcOrigin; // pas streamé !
};

#endif
