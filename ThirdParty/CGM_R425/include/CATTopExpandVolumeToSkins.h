// COPYRIGHT DASSAULT SYSTEMES 2019
//================================================================================
// Creation DLR6  01/04/2019
//
// Operator that expands one (or several) volume(s)
// so that they fill a bigger space.
//
//================================================================================


#ifndef CATTopExpandVolumeToSkins_H
#define CATTopExpandVolumeToSkins_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

/**
 * Interface representing the operator to expand a volume to fill a bigger space.
 * The inputs should be :
 * a "solid body" containing only volumes (no surfacic shells or wires)
 * a surfacic body containing only surfacic skins
 * All volumes of the solid body that are touched by at least one shell of the surfacic body
 * will be expanded to fill the biggest possible closed space defined by shells of the surfacic body.
 * For the operation to work, at least one combination of shells of the surfacic body
 * should form a set of faces that is closed by a combination of input volumes
 * To use this operator:
 *<ul>
 * <li>Create it with the <tt>CATCreateExpandVolumeToSkins</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResult method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul> 
 */

class CATExtTopExpandVolumeToSkins;
class CATCGMJournalList;
class CATBody;

class ExportedByCATTopologicalObjects CATTopExpandVolumeToSkins: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopExpandVolumeToSkins);

protected:

  CATTopExpandVolumeToSkins(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopExpandVolumeToSkins * iExtensible);

  virtual int RunOperator()           = 0;


public:

  virtual ~CATTopExpandVolumeToSkins();

  /**
    * Returns the pointer to the resulting body.
    * The pointer to the journal of the operation.
    * @param iJournal
    * The pointer to the journal to fill.
    * @return
    * The pointer to the resulting body. If you do not want to keep it,
    * use the @href CATICGMContainer#Remove method to remove it from the
    * geometric factory.
    */
  CATBody *             GetResult(CATCGMJournalList * ioJournal);
  CATBody *             GetResult();

  virtual void        SetCheckJournal(CATBoolean iCheckMode)      = 0;


private:

  int                     _NbGetResult; // Number of times GetResult() was called


  friend class CATExtTopExpandVolumeToSkins;
};

#endif
