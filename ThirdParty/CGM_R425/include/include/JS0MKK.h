#ifndef JS0MKK_h
#define JS0MKK_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef CPK_TOOL
#define IMPEXP
#else
#if defined(__JS0MKK)
#define IMPEXP DSYExport
#else
#define IMPEXP DSYImport
#endif
#include "DSYExport.h"
#endif

#define CPKDecoder "CPKDecoder"
#define DLKBuilder "DLKBuilder"
#define ICSigner "ICSigner"


#define EncodeAlphabet js0mkk01
#define DecodeAlphabet js0mkk02
#define EncodeLibrary js0mkk03
#define ICSign js0mkk04
#define CheckDecodingAuthorization js0mkk05
#define DecodeCryptedObject js0mkk06
#define CheckExtendedAuthorization js0mkk07
#define GetServerUrlPart js0mkk08
#define EncodeCPK js0mkk09
#define CheckEnv js0mkk10


extern "C" int IMPEXP EncodeAlphabet(const char* alphabet, const unsigned char* input, size_t inputLength, char* output, size_t outputLength);
extern "C" int IMPEXP DecodeAlphabet(const char* alphabet, const char* input, size_t inputLength, unsigned char* output, size_t outputLength, size_t& decodedLength);
extern "C" int IMPEXP EncodeLibrary(const char* library, const char* release, int debug);
extern "C" int IMPEXP ICSign(const char* inputIC, const char* outputIC, const char* release, int debug);
extern "C" int IMPEXP CheckDecodingAuthorization(const char* encodingKey, const char* release, int debug);
extern "C" int IMPEXP DecodeCryptedObject(const char* encodingKey, const char* release, const unsigned char* inBuffer, size_t inLength, unsigned char*& outBuffer, size_t& outLength, int debug);
extern "C" int IMPEXP CheckExtendedAuthorization(const char* encodingKey, const char* release, int debug);
extern "C" int IMPEXP GetServerUrlPart(char*& serverUrlPart, int debug);
extern "C" int IMPEXP EncodeCPK(const char* encodingKey, const char* release, const unsigned char* inBuffer, size_t inLength, unsigned char*& outBuffer, size_t& outLength, int debug);
extern "C" int IMPEXP CheckEnv(const char* component, const char* release, int debug);


#define ERROR_DECRYPTDLL_MEMORY 1
#define ERROR_DECRYPTDLL_PUBLICKEY 2
#define ERROR_DECRYPTDLL_OPENINPUTFILE 3
#define ERROR_DECRYPTDLL_STATINPUTFILE 4
#define ERROR_DECRYPTDLL_READINPUTFILE 5
#define ERROR_DECRYPTDLL_CHUNKDECRYPT 6
#define ERROR_DECRYPTDLL_INVALIDHEADER 7
#define ERROR_DECRYPTDLL_STREAMERROR 68
#define ERROR_CRYPTDLL_MEMORY 8
#define ERROR_CRYPTDLL_PRIVATEKEYSTEP1 9
#define ERROR_CRYPTDLL_PRIVATEKEYSTEP2 10
#define ERROR_CRYPTDLL_CHUNKCRYPT 11
#define ERROR_CRYPTDLL_WRITEFILE 12
#define ERROR_CRYPTDLL_INVALIDARGS 13
#define ERROR_CRYPTDLL_OPENINPUTFILE 14
#define ERROR_CRYPTDLL_STATINPUTFILE 15
#define ERROR_CRYPTDLL_READINPUTFILE 16
#define ERROR_CRYPTDLL_OPENOUTPUTFILE 17
#define ERROR_CRYPTDLL_CLOSEOUTPUTFILE 18
#define ERROR_CRYPTDLL_INVALIDDLLFORMAT 19
#define ERROR_CRYPTDLL_ZIP 20
#define ERROR_CRYPTDLL_VERIFYDATA 21
#define ERROR_GETKEYS_INVALIDARGS 22
#define ERROR_GETKEYS_MISSING_MKMKPKTOKEN 23
#define ERROR_GETKEYS_INVALID_MKMKPKTOKEN 24
#define ERROR_GETKEYS_RETRIEVE_LOGINNAME 25
#define ERROR_GETKEYS_HTTP_INVALID_ARGS 26
#define ERROR_GETKEYS_HTTP_CONNECT_ERROR 27
#define ERROR_GETKEYS_HTTP_UNKNOWN_HOST 28
#define ERROR_GETKEYS_HTTP_INTERNAL_ERROR 29
#define ERROR_GETKEYS_HTTP_CONNECTION_LOST 30
#define ERROR_GETKEYS_HTTP_NO_CONNECTION 31
#define ERROR_GETKEYS_HTTP_BADFORMATED_RESPONSE 32
#define ERROR_GETKEYS_HTTP_NODATA 33
#define ERROR_GETKEYS_HTTP_NO_MEMORY 34
#define ERROR_GETKEYS_HTTP_SIZE_OVERFLOW 35
#define ERROR_GETKEYS_HTTP_OTHERS 36
#define ERROR_GETKEYS_HTTP_NOT200 37
#define ERROR_GETKEYS_NOLOCAL_USER 38
#define ERROR_GETKEYS_UNAUTHORIZED_USER 39
#define ERROR_GETKEYS_UNAUTHORIZED_MACHINE 40
#define ERROR_GETKEYS_UNREGISTERED_RELEASE 41
#define ERROR_GETKEYS_UNREGISTERED_COMPONENT 42
#define ERROR_GETKEYS_UNEXPECTED_SERVERCODE 43
#define ERROR_GETKEYS_NO_PUBLICKEY_RETURNED 44
#define ERROR_GETKEYS_NO_PRIVATEKEY_RETURNED 45
#define ERROR_GETKEYS_MEMORY 46
#define ERROR_SIGN_MEMORY 47
#define ERROR_SIGN_PRIVATEKEYSTEP1 48
#define ERROR_SIGN_PRIVATEKEYSTEP2 49
#define ERROR_SIGN_INIT 50
#define ERROR_SIGN_UPDATE 51
#define ERROR_SIGN_FINAL 52
#define ERROR_VERIFYSIGN_MEMORY 53
#define ERROR_VERIFYSIGN_PUBLICKEY 54
#define ERROR_VERIFYSIGN_BASE64 55
#define ERROR_VERIFYSIGN_INIT 56
#define ERROR_VERIFYSIGN_UPDATE 57
#define ERROR_VERIFYSIGN_FINAL 58
#define ERROR_SIGN_INVALIDARGS 59
#define ERROR_SIGN_STATINPUTFILE 60
#define ERROR_SIGN_OPENINPUTFILE 61
#define ERROR_SIGN_READINPUTFILE 62
#define ERROR_SIGN_NOEOF 63
#define ERROR_SIGN_OPENOUTPUTFILE 64
#define ERROR_SIGN_WRITEOUTPUTFILE 65
#define ERROR_SIGN_CLOSEOUTPUTFILE 66
#define ERROR_SIGN_FORK_ENCODER 67

#endif
