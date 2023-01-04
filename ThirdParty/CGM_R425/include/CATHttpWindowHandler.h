#ifndef CATHTTPWINDOWHANDLER_H
#define CATHTTPWINDOWHANDLER_H
#include "JS0HTTP.h"
#include "CATHttpTools.h"

#ifdef _WINDOWS_SOURCE
#include <WinDef.h>
#endif

class ExportedByJS0HTTP CATHttpWindowHandler 
{
private:
	HWND	_hWnd;
	CATHttpWindowHandler();
	~CATHttpWindowHandler();

public:
	static CATHttpWindowHandler*	getInstance();
	void SetWindowHandler(HWND ihWnd);
	HWND getWindowHandler();


	//Do not use: only used at exit
	static void                 releaseInstance();
};


#endif
