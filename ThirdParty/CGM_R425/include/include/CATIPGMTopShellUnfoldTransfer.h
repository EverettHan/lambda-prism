#ifndef CATIPGMTopShellUnfoldTransfer_h_
#define CATIPGMTopShellUnfoldTransfer_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopShellUnfoldTransfer;

// exported by
class ExportedByCATGMOperatorsInterfaces CATIPGMTopShellUnfoldTransfer: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopShellUnfoldTransfer();

  virtual void SetTransfertTolerance(double iTol) = 0;

  //Cleaning of transferred wire is on by default
  virtual void SetClean(CATBoolean iClean) = 0;

  //virtual void SetMaxDeviationForClean(double iMaxCleanDeviation) = 0; //BUGBUG shall go
  virtual void SetAssemblyTolerance(double iAsslyTol) = 0;

  virtual int RunTransfer(
    const CATLISTP(CATBody) &iBodiesToTransfer,
    CATLISTP(CATBody) &ioBodiesTransferred,
    CATCGMJournalList *iReport,
    CATBoolean iReverse = FALSE) = 0;

  virtual int RunTransfer(
    CATBody *iBody,
    CATBody *&oBody,
    CATCGMJournalList *iReport,
    CATBoolean iReverse = FALSE) = 0;

  // SZR3: Start: 28 May 2020
  /**
   * Checks if the input flattened shell is the result of unfolding
   * the input body. 
   *
   * @return
   * <ul>
   *   <li> <tt>-1</tt> if the relationship is unknown
   *   <li> <tt>0</tt> if they are not related
   *   <li> <tt>1</tt> if they are related
   * </ul>
   */
  virtual int IsInputShellFlattenedInputBody() const = 0;
  // SZR3: End: 28 May 2020

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopShellUnfoldTransfer(); // -> delete can't be called
};

//Note that this API is only to support curve transfer between provided bodies.
//Hence, the only methods supported by the returned interface are the two overloads of
//RunTransfer. Calling other methods can generate an error
//
//Either or both iListOfInputFaces and iListOfFlattenedFaces can be empty. They are then filled up
// from all the faces from iBody and iFlattenedBody respectively. After this, if iListOfInputFaces
// and iListOfFlattenedFaces have different sizes, the API will fail. 
// Hence, it shall be always ensured that:
// - If iListOfInputFaces and iListOfFlattenedFaces both are not empty, their sizes should be the same.
// - If either or both iListOfInputFaces and iListOfFlattenedFaces are empty, the sizes computed inside 
//   the API should be the same.
//extern "C" 
/**
 * @return [out, IUnknown#Release]
 *   The operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopShellUnfoldTransfer *CATPGMCreateTopShellUnfoldTransfer(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATBody *iFlattenedBody,
  const CATLISTP(CATFace) &iListOfInputFaces,
  const CATLISTP(CATFace) &iListOfFlattenedFaces);

#endif /* CATIPGMTopShellUnfoldTransfer_h_ */
