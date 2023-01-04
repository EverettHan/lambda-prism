#ifndef CATICGMDeltaPersistence_h
#define CATICGMDeltaPersistence_h 


#include "ExportedByGeometricObjects.h"
#include "CATListOfCATICGMObjects.h"
#include "CATBoolean.h"

class CATCGMStream;
class CATGeoFactory;


class ExportedByGeometricObjects CATICGMDeltaSave
{
public : 
  // constructor & deconstructor
	CATICGMDeltaSave(CATCGMStream & ioStreamArea);
  ~CATICGMDeltaSave();

  // set objects to saves
	void SetObjectsToSave(const CATLISTP(CATICGMObject) & iFederatorObjects);

  // set context objects( delta objects)
	void SetContext(const CATLISTP(CATICGMObject) & iFederatorContextObjects);

	// set a flag if Linked objects need to be found
	void SetFindLinkedObjects(CATBoolean iVal);

  // Run operator
	void Run();

private :
  CATCGMStream *                _StreamArea;
  const CATLISTP(CATICGMObject)  *    _FederatorObjects;
  const CATLISTP(CATICGMObject)  *    _FederatorContextObjects;
  CATBoolean _FindLinkedObjects;
};

class ExportedByGeometricObjects CATICGMDeltaLoad
{
public :
   // constructor & deconstructor
	CATICGMDeltaLoad(CATCGMStream & ioStreamArea);
  ~CATICGMDeltaLoad();

	//The tags of the objects must be the same as they were in CATICGMDeltaSave::SetContext
	//The factory must not contain objects with same tags as the objects contained in ioStreamArea (that have been streamed with CATICGMDeltaSave::SetObjectsToSave)
	void SetContext(CATGeoFactory * ioCATGeoFactory);

  // Run operator
	void Run();

  // Retrieve the result objects list
	void GetObjects( CATLISTP(CATICGMObject) & oFederatorObjects);

private :
  CATCGMStream *                _StreamArea;
  CATGeoFactory *               _Factory;
  CATLISTP(CATICGMObject) *     _ResultFederatorObjects;
};

#endif

