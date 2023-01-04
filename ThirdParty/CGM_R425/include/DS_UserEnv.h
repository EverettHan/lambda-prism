#ifndef _DS_USERENV
#define _DS_USERENV

// Seules les definitions manquantes de l'include UserEnv.h ont ete prises.
// Ce fichier sera a effacer quand ls niveau de SDK sera bon sur les machines de build a DS

//
// Define API decoration for direct importing of DLL references.
//

#if !defined(_USERENV_)
#define USERENVAPI DECLSPEC_IMPORT
#else
#define USERENVAPI
#endif


#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
//
// LoadUserProfile
//
// Loads the specified user's profile.
//
// Most applications should not need to use this function.  It's used
// when a user has logged onto the system or a service starts in a named
// user account.
//
// hToken        - Token for the user, returned from LogonUser()
// lpProfileInfo - Address of a PROFILEINFO structure
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:  The caller of this function must have admin privileges on the machine.
//
//        Upon successful return, the hProfile member of the PROFILEINFO
//        structure is a registry key handle opened to the root
//        of the user's hive.  It has been opened with full access. If
//        you need to read or write to the user's registry file, use
//        this key instead of HKEY_CURRENT_USER.  Do not close this
//        handle.  Instead pass it to UnloadUserProfile to close
//        the handle.
//
//=============================================================================

//
// Flags that can be set in the dwFlags field
//

#define PI_NOUI         0x00000001      // Prevents displaying of messages
#define PI_APPLYPOLICY  0x00000002      // Apply NT4 style policy

typedef struct _PROFILEINFOA {
    DWORD       dwSize;                 // Set to sizeof(PROFILEINFO) before calling
    DWORD       dwFlags;                // See flags above
    LPSTR       lpUserName;             // User name (required)
    LPSTR       lpProfilePath;          // Roaming profile path (optional, can be NULL)
    LPSTR       lpDefaultPath;          // Default user profile path (optional, can be NULL)
    LPSTR       lpServerName;           // Validating domain controller name in netbios format (optional, can be NULL but group NT4 style policy won't be applied)
    LPSTR       lpPolicyPath;           // Path to the NT4 style policy file (optional, can be NULL)
    HANDLE      hProfile;               // Filled in by the function.  Registry key handle open to the root.
} PROFILEINFOA, FAR * LPPROFILEINFOA;
typedef struct _PROFILEINFOW {
    DWORD       dwSize;                 // Set to sizeof(PROFILEINFO) before calling
    DWORD       dwFlags;                // See flags above
    LPWSTR      lpUserName;             // User name (required)
    LPWSTR      lpProfilePath;          // Roaming profile path (optional, can be NULL)
    LPWSTR      lpDefaultPath;          // Default user profile path (optional, can be NULL)
    LPWSTR      lpServerName;           // Validating domain controller name in netbios format (optional, can be NULL but group NT4 style policy won't be applied)
    LPWSTR      lpPolicyPath;           // Path to the NT4 style policy file (optional, can be NULL)
    HANDLE      hProfile;               // Filled in by the function.  Registry key handle open to the root.
} PROFILEINFOW, FAR * LPPROFILEINFOW;
#ifdef UNICODE
typedef PROFILEINFOW PROFILEINFO;
typedef LPPROFILEINFOW LPPROFILEINFO;
#else
typedef PROFILEINFOA PROFILEINFO;
typedef LPPROFILEINFOA LPPROFILEINFO;
#endif // UNICODE



USERENVAPI
BOOL
WINAPI
LoadUserProfileA(
    IN HANDLE hToken,
    IN OUT LPPROFILEINFOA lpProfileInfo);
USERENVAPI
BOOL
WINAPI
LoadUserProfileW(
    IN HANDLE hToken,
    IN OUT LPPROFILEINFOW lpProfileInfo);
#ifdef UNICODE
#define LoadUserProfile  LoadUserProfileW
#else
#define LoadUserProfile  LoadUserProfileA
#endif // !UNICODE


//=============================================================================
//
// UnloadUserProfile
//
// Unloads a user's profile that was loaded by LoadUserProfile()
//
// hToken        -  Token for the user, returned from LogonUser()
// hProfile      -  hProfile member of the PROFILEINFO structure
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     The caller of this function must have admin privileges on the machine.
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
UnloadUserProfile(
    IN HANDLE hToken,
    IN HANDLE hProfile);

//=============================================================================
//
// GetUserProfileDirectory
//
// Returns the path to the root of the requested user's profile
//
// hToken         -  User's token returned from LogonUser()
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Documents and Settings\Joe
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
GetUserProfileDirectoryA(
    IN HANDLE  hToken,
    OUT LPSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
USERENVAPI
BOOL
WINAPI
GetUserProfileDirectoryW(
    IN HANDLE  hToken,
    OUT LPWSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
#ifdef UNICODE
#define GetUserProfileDirectory  GetUserProfileDirectoryW
#else
#define GetUserProfileDirectory  GetUserProfileDirectoryA
#endif // !UNICODE


USERENVAPI
BOOL
WINAPI
CreateEnvironmentBlock(
  OUT LPVOID *lpEnvironment,  // environment block
  IN HANDLE hToken,          // user token
  IN BOOL bInherit           // inheritance
);

USERENVAPI
BOOL
WINAPI
DestroyEnvironmentBlock(
  LPVOID lpEnvironment  // environment block
);


#ifdef __cplusplus
}
#endif

#endif 
