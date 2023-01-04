#ifndef CATIPGMOperator_h_
#define CATIPGMOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGeometricObjects.h"
#include "CATIPGMVirtual.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCGMWarning.h"
#include "CATCGMInterruptDef.h"
#include "CATIACGMLevel.h"

class CATBaseUnknown;
class CATCGMOutput;
class CATCGMStream;
class CATCloneManager;
class CATError;
class CATExtCGMReplay;
class CATExtGeoOperator;
class CATGeoFactory;
class CATICGMObject;
class CATSoftwareConfiguration;
class CATString;
class CATTolerance;
class CATTopCheckJournal; // Not interfaced here
class CATIPGMTopOperator;
class CATechAttribute;
class CATechSet;
class CATICGMOperator;

extern ExportedByCATGeometricObjects IID IID_CATIPGMOperator;

//=======================================================================================================================
/**
 * Base class for all the CGM operators.
 * <br>To use a CGM operator:
 * <ul><li>Create it with the corresponding <tt>CreateXxx</tt> global method
 * <li>Tune some parameters if needed
 * <li>Run it
 * <li>Read the results
 * <li>Release the operator with the <tt>Release</tt> method.
 *</ul>
 */
class ExportedByCATGeometricObjects CATIPGMOperator: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMOperator();

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
 * Returns the factory of <tt>this</tt> operator. 
 * @return
 * The pointer to the geometric factory that creates the output objects.
 */
  virtual CATGeoFactory *GetFactory() const = 0;

  /**
 * Retrieves the name of <tt>this</tt> operator.
 * @return
 * The name. This output string is part of the class and will be deleted at its deletion.
 */
  virtual const CATString *GetOperatorId() = 0;

  /** 
 * Defines the name of <tt>this</tt> operator.
 * @param iOperatorName
 * The name of the operator.
 */
  virtual void SetOperatorId(const CATString iOperatorName) = 0;


  /**
  * @nodoc
  * Associates an interruption function with this operator.
  * @param ipInterruptFunction
  * The interruption function to be written by the application calling this operator.
  * Must return TRUE if the operator is to be interrupted.
  */
  virtual void EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction) = 0;

  /** 
   * @nodoc
   * Returns the Software configuration to be taken 
   * into acccount by <tt>this</tt> operator.
   * @return
   * The Software configuration.
   */
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  /** @nodoc */
  virtual CATIPGMTopOperator *IsTopological() = 0;

  /** @nodoc  */
  virtual void DefineFactory(CATGeoFactory *Factory) = 0;

  /** @nodoc  */
  virtual CATULONG32 GetSessionIdentifier() = 0;

  /** @nodoc */
  virtual void SetWarningMode(CATCGMWarning iMode = Warning_On) = 0;

  /** @nodoc */
  virtual CATCGMWarning GetWarningMode() const = 0;

  /** @nodoc  Default is Valid and Modifiable (exeption CATCloneManager and CATIPGMTopOperator) */
  virtual void GetResultStatus(short &ioValidation, short &ioModifiable) const = 0;

  /** @nodoc  */
  virtual void SetResultStatus(const short iValidation, const short iModifiable) = 0;

  /** @nodoc */
  virtual short GetNumberOfReplay() = 0;

  /** @nodoc  */
  virtual CATExtGeoOperator *GetExtensible(CATBoolean iRequired = TRUE) const = 0;

  /**
  * @nodoc CGMTkJournaling
  */
  virtual HRESULT DumpObjects(
    const unsigned int iOptions,
    CATechAttribute *iOutput,
    CATechSet *iJournaling) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMOperator(); // -> delete can't be called
};

#endif /* CATIPGMOperator_h_ */
