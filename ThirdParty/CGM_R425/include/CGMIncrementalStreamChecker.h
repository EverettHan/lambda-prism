#ifndef CGMIncrementalStreamChecker_H
#define CGMIncrementalStreamChecker_H

//=================================================
//  CGMIncrementalStreamChecker 
//  IncrementalStream test on Feature level
//
//  Creation  YL3                   Aug 2015
//=================================================


#include "ExportedByCATCGMFusion.h"
#include "CATGeoFactory.h"

class ExportedByCATCGMFusion CGMIncrementalStreamChecker
{
public :
	CGMIncrementalStreamChecker();
	~CGMIncrementalStreamChecker();

	static void CheckIncrementalStreamFactory(CATICGMObject * iObject);
	static void FirstSaveBeforeUpdate(CATICGMContainer * iFactory);


private :
	static CATULONG32 _LastObjectCount;
	static int _StreamCheckIndex;
	static CATULONG32 _CheckTime;

};



#endif

