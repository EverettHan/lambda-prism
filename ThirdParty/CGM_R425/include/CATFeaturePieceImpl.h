//COPYRIGHT DASSAULT SYSTEMES 2015
#ifndef CATFeaturePieceImpl_h
#define CATFeaturePieceImpl_h

#include "CATGMModelInterfaces.h"

#include "CATCGMUseCounted.h"

class CATFeaturePieceInfo;

class ExportedByCATGMModelInterfaces CATFeaturePieceImpl : public CATCGMUseCounted
{
public:
	CATCGMNewClassArrayDeclare;

private:
	// forbid copying
	CATFeaturePieceImpl(CATFeaturePieceImpl const& other);
	CATFeaturePieceImpl& operator=(const CATFeaturePieceImpl &iOneOf);

	const CATFeaturePieceInfo* _pFeaturePieceInfo;
    
public:
	// Constructor
	CATFeaturePieceImpl();
	CATFeaturePieceImpl(CATFeaturePieceInfo const* ipFeaturePieceInfo);

	virtual ~CATFeaturePieceImpl();

	CATFeaturePieceInfo const* GetFeaturePieceInfo() const;
	
};

#endif
