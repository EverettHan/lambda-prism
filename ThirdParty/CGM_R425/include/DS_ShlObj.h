#ifndef _DS_ShlObj
#define _DS_ShlObj
// Seules les definitions manquantes de l'include ShlObj.h ont ete prises.
// Ce fichier sera a effacer quand ls niveau de SDK sera bon sur les machines de build a DS


#define CSIDL_FLAG_CREATE               0x8000        // combine with CSIDL_ value to force folder creation in SHGetFolderPath()
#define CSIDL_COMMON_APPDATA            0x0023        // All Users\Application Data
#define CSIDL_LOCAL_APPDATA             0x001c        // <user name>\Local Settings\Applicaiton Data (non roaming)

// shell32 APIs that are also exported from shfolder
//#ifndef SHFOLDERAPI
#if defined(_SHFOLDER_) || defined(_SHELL32_)
#define SHFOLDERAPI           STDAPI
#else
#define SHFOLDERAPI           EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#endif
//#endif

SHFOLDERAPI SHGetFolderPathA(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPSTR pszPath);
SHFOLDERAPI SHGetFolderPathW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath);
#ifdef UNICODE
#define SHGetFolderPath  SHGetFolderPathW
#else
#define SHGetFolderPath  SHGetFolderPathA
#endif // !UNICODE

#endif
