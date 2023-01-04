//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttp                                                                  *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation novembre 2019                                       sip         *
//* Class to manage a requete but only used for close connection              *
//*===========================================================================*

#ifndef CATHTTPREQUEST_H
#define CATHTTPREQUEST_H
#include "CATHttp.h" 
#include "DSYSysRefCounter.h"
#include <atomic>

#pragma warning( push )
#pragma warning( disable : 4275 )
class ExportedByJS0HTTP  CATHttpRequest : public DSYSysRefCounter
{
public:
	CATHttpRequest();
	~CATHttpRequest();

	std::atomic_bool		_IsConnectionClose;
	std::atomic_ullong		_TotalRcv;
	std::atomic_ullong		_TotalRcvHeader;
	std::atomic_ullong		_TotalRcvBody;
};
#pragma warning( pop )


#endif
