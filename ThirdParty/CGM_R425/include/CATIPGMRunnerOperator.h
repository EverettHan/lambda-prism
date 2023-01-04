#ifndef CATIPGMRunnerOperator_h_
#define CATIPGMRunnerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATCollec.h"
#include "IUnknown.h"

class CATBody;
class CATCGMJournalList;
class CATLISTP(CATBody);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMRunnerOperator;

/**
 * Class for operator runner.
   */

#ifndef CAT_GENERATE_TIE

class ExportedByCATGMModelInterfaces CATIPGMRunnerOperator: public CATIPGMVirtual
{
public:
  /**  
   * Constructor
   */
  CATIPGMRunnerOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMRunnerOperator(); // -> delete can't be called

public:

#else

class ExportedByCATGMModelInterfaces CATIPGMRunnerOperator: public IUnknown
{
public:

#endif


  /**
   *  Returns the pointer to the topological journal associated with <tt>this</tt> operator.
   */
  virtual CATCGMJournalList *GetJournal() const = 0;

  /**
   * Returns the list of input bodies.
   * @param oListOfCopyInputBodies
   * @param oListOfNoCopyInputBodies
   */
  virtual void ReadInputBodies(
    CATLISTP(CATBody) &oListOfCopyInputBodies,
    CATLISTP(CATBody) &oListOfNoCopyInputBodies) = 0;

  /**
   *  Performs the operation.
   * <br>This method does not throw exceptions.
   *
   * @return An HRESULT value. 
   *   <br><b>Legal values</b>:
   *   <dl>
   *     <dt>S_OK</dt>
   *     <dd>The operation was successfully performed.</dd>
   *     <dt>E_FAIL </dt>
   *     <dd>An unexpected error was occured during the operation.</dd>
   *   </dl>
   */
  virtual HRESULT Run() = 0;

  /** 
   *  Returns the main result of this topological operator.
   */
  virtual CATBody *GetLiveResult() const = 0;

  /**
   * @nodoc
   * Returns the meta class associated with the interface.<br>
   * Note that it's handled by the implementation in order not to expose more internal data.
   */
  virtual const CATCGMItfMetaClass &GetItfMetaClass() const = 0;

protected:
  /**
   * @nodoc
   * Returns the internal data.
   */
  virtual CATCGMItfInternalData &GetInternalData() = 0;
};

#endif /* CATIPGMRunnerOperator_h_ */
