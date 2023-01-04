//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Class		:		CATPrototypeExtrusion
//	Creation	:		15/06/2015
//
//
//	Synopsis	:		
//					
//	
//
//
//	Authors		:  I49
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CATPrototypeExtrusion_H
#define CATPrototypeExtrusion_H


#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMVirtual.h"

#include "CATGMLiveExtrusionPrimitive.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATListOfInt.h"
#include "ListPOfCATCellManifold.h"
#include "CATFeaturePiece.h"
#include "ListVOfCATFeaturePiece.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCellManifoldGroupOperator;
class CATLiveBody;
class CATBody;
class CATCGMStream;
class CATCloneManager;
class CATCGMJournalList;

class ExportedByCATTopologicalObjects CATPrototypeExtrusion : public CATCGMVirtual
{

public:
	CATCGMNewClassArrayDeclare;

	typedef enum 
	{
		CATPrototypeExtrusionType = 0
	}
	ClassType;
public:
	CATPrototypeExtrusion();
private:
	CATPrototypeExtrusion(const CATPrototypeExtrusion& iCATPrototypeExtrusion); //forbid copying
public:
	virtual ~CATPrototypeExtrusion();

public:
	void Stream(CATCGMStream& ioStream) const;
	void UnStream(CATCGMStream& ioStream);
	static CATPrototypeExtrusion* CreateAndUnstream(CATCGMStream& ioStream);

	virtual void GetExtrusionManifolds(ListPOfCATCellManifold &oManifolds) const;
	virtual void SetExtrusionManifolds(ListPOfCATCellManifold const &iManifolds);
	virtual void GetTransitionManifolds1(ListPOfCATCellManifold &oManifolds) const;
	virtual void SetTransitionManifolds1(ListPOfCATCellManifold const &iManifolds);
	virtual void GetTransitionManifolds2(ListPOfCATCellManifold &oManifolds) const;
	virtual void SetTransitionManifolds2(ListPOfCATCellManifold const &iManifolds);

	CATLISTV(CATFeaturePiece) GetFeaturePiece(CATLiveBody const & iLiveBody, CATSoftwareConfiguration const & iConfig) const;

	static void ComputeImage(CATCloneManager& iCloner, const CATPrototypeExtrusion& iPrototype, CATPrototypeExtrusion& oPrototype);
	static CATPrototypeExtrusion* ComputeImage(CATCGMJournalList &iLiveJournal, const CATPrototypeExtrusion& iPrototype);

protected:
	virtual void UnStreamImpl(CATCGMStream& ioStream);

private:

	//==========================================================================================================================
	// DATA
	//==========================================================================================================================
private:
	ClassType _type;
	ListPOfCATCellManifold   _ExtrudeManifolds;  
	ListPOfCATCellManifold   _TransitionManifolds1;  
	ListPOfCATCellManifold   _TransitionManifolds2;

	//==========================================================================================================================
};
#endif
