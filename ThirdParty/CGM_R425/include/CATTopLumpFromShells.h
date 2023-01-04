#ifndef CATTopLumpFromShells_H
#define CATTopLumpFromShells_H

//=============================================================================
// June 2009   Creation                                  LD2
//=============================================================================

/** 
 * Class representing the operator that takes the closed shells of the input body
 * and creates corresponding volumes in the output body.
 * <br>To use the CATTopLumpFromShells:
 * <ul><li>Create it the <tt>CATCreateTopLumpFromShells</tt> global function. 
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the created body with the <tt>GetResult</tt> method. 
 * <li>Delete with the usual C++ <tt>delete</tt> operator after use.</ul>
 */

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

class CATGeoFactory;
class CATBody;
class CATTopData;
class CATTopLumpFromShellsExt;

class ExportedByCATTopologicalObjects CATTopLumpFromShells : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopLumpFromShells);

protected:
  
  CATTopLumpFromShells(CATGeoFactory * iFactory, CATTopData * iTopData, CATTopLumpFromShellsExt * iExtensible);

public:

  virtual ~CATTopLumpFromShells();

  virtual CATBody * GetResult() = 0;

};

ExportedByCATTopologicalObjects CATTopLumpFromShells * CATCreateTopLumpFromShells(CATGeoFactory * iFactory,
                                                                                  CATTopData * iTopData,
                                                                                  CATBody * iBody);

#endif

