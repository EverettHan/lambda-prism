#ifndef CATIPGMLiveVectorialRunnerOperator_h_
#define CATIPGMLiveVectorialRunnerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMModelInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATBoolean.h"

class CATCGMJournalList;
class CATListPtrCATBody;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMLiveVectorialRunnerOperator;

/**
 * Class for live operator runner.
 */


#ifndef CAT_GENERATE_TIE

class ExportedByCATGMModelInterfaces CATIPGMLiveVectorialRunnerOperator: public CATIPGMVirtual
{
public:
  /**  
   * Constructor
   */
  CATIPGMLiveVectorialRunnerOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLiveVectorialRunnerOperator(); // -> delete can't be called

public:

#else

class ExportedByCATGMModelInterfaces CATIPGMLiveVectorialRunnerOperator: public IUnknown
{
public:

#endif

  virtual CATBoolean IsInMultiBodiesContext() const = 0;

  virtual void SetBodiesInSession(const CATListPtrCATBody &iBodyInSessionList) = 0;

  virtual void GetBodyResults(CATListPtrCATBody &oOutputBodyList) = 0;

  virtual void GetBodyInputs(CATListPtrCATBody &oInputBodyList) = 0;

  virtual CATCGMJournalList *GetBodyJournal() = 0;

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

#endif /* CATIPGMLiveVectorialRunnerOperator_h_ */
