// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// Jun. 09  Creation                                                    ASE
//=============================================================================

#include "ExportedByGeometricObjects.h"

#ifndef CATCGMSafeHashTable_H
#define CATCGMSafeHashTable_H

#include "IUnknown.h"
#include "CATGeoFactory.h"
#include "CATCGMHashTable.h"

#include "CATICGMObject.h"
#include "CATCGMStream.h"


/*
*	Class used with the CGM MPROCTools for the optimization of the stream and unstream between the processes
*	This class is virtual and grants access to cgm optimized partial stream functions in the form of the two functions below.
*
*	an implementation of this class must be used with an implementation of the CATMProcAppliManagerCGM for the stream capabilities to function correctly
*/

class CATMProcAppliTask;
class CATMProcAppliDataCGM;


class ExportedByGeometricObjects CATCGMSafeHashTable
{
public:

	CATCGMSafeHashTable();

	virtual ~CATCGMSafeHashTable();

  // Free and remove all elements from hash table
  HRESULT  RemoveAll();

  // Insert element into hash table (and increase its UseCount)
  int Insert (CATICGMUnknown *iCGMElem);

  // Insert element into hash table (and increase its UseCount)
  int Locate(CATICGMUnknown *iCGMElem);

public:

	CATCGMHashTable _CGMHashTable;

};
#endif

