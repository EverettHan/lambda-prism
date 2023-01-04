#ifndef CATTopOperItf_h
#define CATTopOperItf_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATThrowForNullPointer.h"
#include "CATBoolean.h"

#ifndef NULL
#define NULL 0
#endif

class CATTopSplitShellByWires;
class CATGeoFactory;
class CATTopData;
class CATListPtrCATBody;
class CATBody;
class CATCell;
class CATSoftwareConfiguration;
class CATCXBodyDatumiserBridge;
class CATExplicitCheckOperatorTopOpBridge;
class CATTopMaxIsoMoveCalculator;
class CATListPtrCATFace;
class CATMathDirection;

class ExportedByCATTopologicalObjects CATTopOperItf
{
private:
  CATTopOperItf(const CATTopOperItf &);

protected:
  CATTopOperItf()
  {}

  virtual ~CATTopOperItf()
  {}

public:

  /** @nodoc @nocgmitf */
  static CATTopOperItf * DynamicGetInstance(const char * iGetterFunctionLibrary, const char * iGetterFunctionName);

  /** @nodoc @nocgmitf
  * Throws an error if the entry point cannot be loaded.
  */
  static CATTopOperItf & DynamicGetInstanceRef(const char * iGetterFunctionLibrary, const char * iGetterFunctionName);

  /** @nodoc @nocgmitf */
  virtual CATTopSplitShellByWires * CreateSplitShellByWiresBasicExtrapol(
    CATGeoFactory     * iFactory,
    CATTopData        * iTopData,
    CATListPtrCATBody * iSplittingBodies,
    CATBody           * iSkinBody)
  {CATThrowForNullPointerReturnValue(NULL);}

  /** @nodoc @nocgmitf */
  virtual CATBoolean IsAThinFace(
    CATCell * ipFace,
    CATGeoFactory * ipFactory,
    CATSoftwareConfiguration * ipConfig,
    double iTolerance)
  {CATThrowForNullPointerReturnValue(FALSE);}

  /** @nodoc @nocgmitf */
  virtual CATBoolean AreFacesCoincident(
    CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATCell * iCell1,
    CATCell * iCell2,
    double iTolerance)
  {CATThrowForNullPointerReturnValue(FALSE);}

  /** @nodoc @nocgmitf */
  virtual CATCXBodyDatumiserBridge * GetCXBodyDatumiserBridge()
    {CATThrowForNullPointerReturnValue(NULL);}

  /** @nodoc @nocgmitf */
  virtual CATExplicitCheckOperatorTopOpBridge * GetExplicitCheckOperatorTopOpBridge()
    {CATThrowForNullPointerReturnValue(NULL);}

  /** @nodoc @nocgmitf */
  virtual CATTopMaxIsoMoveCalculator * MakeOperatorIsoMoveSimulator(
              CATGeoFactory           * ipFactory,          CATTopData  * iTopData,
              const CATListPtrCATFace  &iListOfMobileFaces, CATBody     * ipInputBody,
              const CATMathDirection   &iDisplacementAxis)
    {CATThrowForNullPointerReturnValue(NULL);}

  /** @nodoc @nocgmitf */
  virtual CATBody * RelimitBody(
    CATGeoFactory     * iFactory,
    CATTopData        * iTopData,
    CATBody           * iTrimmingBody,
    CATBody           * iRelimitedBody,
    int                 iSideToKeep,
    CATBoolean          iNoSimplif)
  {CATThrowForNullPointerReturnValue(NULL);}
  
  /** @nodoc @nocgmitf */
  virtual CATBody * RunCloseWithContextBody(
    CATGeoFactory * ipFactory,
    CATSoftwareConfiguration * ipConfig,
    CATBody * ipBodyToClose,
    CATBody * ipContextBody)
  {CATThrowForNullPointerReturnValue(NULL);}



};

#endif
