#ifndef CATIPGMDynShellBody_h_
#define CATIPGMDynShellBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATCollec.h"

class CATBody;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynShellBody;

/**
 * Interface representing the topological creation of a shell domain.
 * This operator takes a list of faces in input, builds the shell domain and put the
 * result in a new body.
 * As all the topological operators, the input objects are not modified. The resulting body is
 * a new one, that you can get by using the <tt>CATIPGMDynOperator::GetResult</tt> method.<br>
 * The faces must have the same orientation and define an open shell, but these properties
 * are not tested.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDynShellBody: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynShellBody();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynShellBody(); // -> delete can't be called
};

// Creation EntryPoints
/**
 * Creates a CATIPGMDynShellBody operator.
 * @param iForResultingBody
 * Where to create the resulting CATBody. 
 * @param iFaces
 * The list of faces used to create the shell domain. The faces must have the
 * same orientation, and define an open shell.
 * @param iJournal
 * A pointer to the topological journal. If NULL, no line will be writen.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynShellBody *CATPGMDynCreateShellBody(
  CATGeoFactory *iForResultingBody,
  const CATLISTP(CATFace) &iFaces,
  CATCGMJournalList *iJournal = NULL);

#endif /* CATIPGMDynShellBody_h_ */
