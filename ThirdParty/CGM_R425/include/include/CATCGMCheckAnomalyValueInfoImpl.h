#ifndef CATCGMCheckAnomalyValueInfoImpl_H
#define CATCGMCheckAnomalyValueInfoImpl_H

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMModelInterfaces.h"
#include "CATCGMUseCounted.h"
#include "CATUnicodeString.h"
#include "CATListOfDouble.h"
#include "CATCGMCheckAnomalyValueInfo.h"
#include "CATListOfCATCGMCheckAnomalyValueInfo.h"

class ExportedByCATGMModelInterfaces CATCGMCheckAnomalyValueInfoImpl : public CATCGMUseCounted
{
public:
	CATCGMNewClassArrayDeclare;

private:
	// forbid copying
	CATCGMCheckAnomalyValueInfoImpl(CATCGMCheckAnomalyValueInfoImpl const& iOther);
	CATCGMCheckAnomalyValueInfoImpl& operator=(CATCGMCheckAnomalyValueInfoImpl const& iOther); 

public:
	CATCGMCheckAnomalyValueInfoImpl();
	CATCGMCheckAnomalyValueInfoImpl(CATUnicodeString const& iValueDescription, double iValue);
	CATCGMCheckAnomalyValueInfoImpl(CATUnicodeString const& iValueDescription, CATListOfDouble const& iValues);
	~CATCGMCheckAnomalyValueInfoImpl();

	void GetInfo(CATUnicodeString& oValueDescription, CATListOfDouble & oValues) const;
	void GetSubValueInfos(CATLISTV(CATCGMCheckAnomalyValueInfo) &oSubValueInfos) const;
	void AppendSubValueInfo(CATCGMCheckAnomalyValueInfo const& iSubValueInfo);

private:
	CATUnicodeString _description;
	CATListOfDouble  _values;
	CATLISTV(CATCGMCheckAnomalyValueInfo) _subInfos;
};
#endif
