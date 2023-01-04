/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATCGMTransfo2DDefine :
//=============================================================================
//=============================================================================
// Nov 03  Creation                          OAU
//=============================================================================

#ifndef CATCGMTransfo2DDefine_H
#define CATCGMTransfo2DDefine_H

class CATCGMTransfo2D;

#include "YN000FUN.h"

class ExportedByYN000FUN CATCGMTransfo2DDefine
{
public:
	virtual ~CATCGMTransfo2DDefine();
	
	virtual int Run()=0;
	virtual CATCGMTransfo2D * GetResult() =0;
	
	
protected:
	CATCGMTransfo2DDefine();
	
private:
	CATCGMTransfo2DDefine(const CATCGMTransfo2DDefine &);
	void operator = (const CATCGMTransfo2DDefine &);
	
};

#endif
