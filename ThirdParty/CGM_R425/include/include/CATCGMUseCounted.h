#ifndef CATCGMUseCounted_H
#define CATCGMUseCounted_H

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"

// Please note: Classes derived from CATCGMUseCounted must include
//
// code/macros in the .h file:
// #include "CATCGMNewArray.h"
// public:
//	CATCGMNewClassArrayDeclare;
//
// and code/macros in the .cpp file:
// #include "CATCGMNewClassArray.h"
// CATCGMNewClassArray(<DERIVEDCLASSNAME>,3,catcgmPoolTEMP)

class ExportedByCATMathematics CATCGMUseCounted : public CATCGMVirtual
{
public:
	CATCGMNewClassArrayDeclare;

	// Constructor
	CATCGMUseCounted();

	// Use counting methods
	void AddRef();
	void Release();

	int GetCount() const;
	CATCGMUseCounted* Clone() const;

protected:	
	// virtual destructor required, so that Release can call "delete this" 
	// make destructor protected so that clients must go through use-counting
	// sub-classes should also make their destructors private or protected
	virtual ~CATCGMUseCounted();

private:
	int _useCount;
	virtual CATCGMUseCounted* CloneImpl() const;
};

#endif

