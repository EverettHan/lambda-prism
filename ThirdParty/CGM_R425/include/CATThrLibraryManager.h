#ifndef CATThrLibraryManager_h
#define CATThrLibraryManager_h

#ifdef _WINDOWS_SOURCE
#include <wtypes.h>
#endif

#include "JS0MT.h"
#include "CATDataType.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CATBoolean.h"

#include "CATSmartMutex.h"

#if defined(_IRIX_SOURCE) || defined(_SUNOS_SOURCE) || defined(_AIX) || defined(_LINUX_SOURCE) || defined(_DARWIN_SOURCE) || defined(_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)
#include <dlfcn.h>
#endif
#ifdef _HPUX_SOURCE
#include <dl.h>
#endif

#ifdef _HPUX_SOURCE
typedef shl_t CATThrLibraryType;
#endif
#if defined(_IRIX_SOURCE) || defined(_SUNOS_SOURCE) || defined(_AIX) || defined(_LINUX_SOURCE) || defined(_DARWIN_SOURCE) || defined(_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)
typedef void* CATThrLibraryType;
#endif
#ifdef _WINDOWS_SOURCE
typedef HINSTANCE CATThrLibraryType;
#endif

struct CATThrLoadedLib;
struct CATThrFoundSymbol;

struct CATThrLibraryHandler
{
   void *EntryPoint;
#if defined(_IRIX_SOURCE) || defined(_SUNOS_SOURCE) || defined(_AIX) || defined(_LINUX_SOURCE) || defined(_DARWIN_SOURCE) || defined(_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)
   void *Handler;
#endif
#ifdef _HPUX_SOURCE
   shl_t Handler;
#endif
#if defined (_WINDOWS_SOURCE)
   HINSTANCE Handler;
#endif
};

class ExportedByJS0MT CATThrLibraryManager {
	
	public :

		/**
		 * iLibraryName = nom de la librairie contenant le point d'entree
		 * EntryName   = nom du point d'entree
		 */
		static CATThrLibraryHandler GetFunctionAddress(
						const char *iLibraryName,
						const char *iEntryName);

		static CATThrLibraryType LoadLibrary(const char *iLibraryName);

	private :
	
		static void * _FindSymbolInLibrary(const char * name, CATThrLibraryType thelib);
		
		static int _CompareLib(const void *pt1, const void *pt2);
		
		// Retourne l'indice dans le tableau _loadedLibraries si name est present, -1 sinon
		// oThrLoadedLib a utiliser avec precaution, hors de la methode le pointeur n'est plus protege de la destruction depuis d'autres threads
		static CATBoolean _QueryLoadedLib(const char *iName, CATThrLibraryType &oTyp, CATThrLoadedLib ** oThrLoadedLib = NULL);

		static void _AddLoadedLib(const char *name, CATThrLibraryType lib);

		static int _CompareSymbols(const void *pt1, const void *pt2);
		
		// + JBX 11.7.8 : le retour de la methode est maintenant un void * 
		static void * _QueryFoundSymbol(const char *iLibraryName, const char *iEntryName);
		
		static void _AddFoundSymbol(const char *iLibraryName, const char *iEntryName, void * iSymbol);
	
		static void _Cleanup();
		
		/* librairies deja chargees */
		static CATThrLoadedLib * _loadedLibraries;
		static int _nbLibs;
		static CATThrFoundSymbol * _foundSymbols;
		static int _nbSymbols;

		//static CATMutex * _pMutex;
		static CATSmartMutex _MutexThrLib;		
};

#endif // CATThrLibraryManager_h
