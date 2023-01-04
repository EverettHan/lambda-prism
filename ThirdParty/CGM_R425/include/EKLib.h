//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/01/19
//===================================================================

#ifndef EKLib_H
#define EKLib_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"
#include <ctime>
#include <stdint.h>
#include <string>

namespace EK
{
class Binary;

ExportedByKernel void getCurrentTime(unsigned int& seconds, unsigned int& microseconds);
ExportedByKernel double getCurrentTime(); // in seconds
ExportedByKernel void getSystemTimes(uint64_t& idleMilliseconds, uint64_t& totalMilliseconds);
ExportedByKernel std::tm localtime(std::time_t timer);
ExportedByKernel void sleep(int milliseconds);

ExportedByKernel bool dirExist(const char* dirname);
ExportedByKernel bool fileExist(const char* filename);

ExportedByKernel bool writeFile   (const char* filename, const CATUnicodeString& content);
ExportedByKernel bool appendToFile(const char* filename, const CATUnicodeString& content);
ExportedByKernel bool readFile    (const char* filename,       CATUnicodeString& content);
ExportedByKernel bool readFile    (const char* filename, char*& data, size_t& size);

ExportedByKernel bool writeFile   (const char* filename, const Binary& binary);
ExportedByKernel bool appendToFile(const char* filename, const Binary& binary);
ExportedByKernel bool readFile    (const char* filename,       Binary& binary);

ExportedByKernel CATUnicodeString getEnv(const char* name);
ExportedByKernel std::string getEnvAsString(const char* name);
ExportedByKernel bool isEnvSet(const char* name);
ExportedByKernel void replaceAllEnvironmentVariables(std::string& str);

ExportedByKernel std::string getPrivateIP();
ExportedByKernel std::string getHostname(bool fullyQualified = false);
ExportedByKernel std::string getSysname();
ExportedByKernel std::string getUsername();
ExportedByKernel int getPid();

// thread-safe version of the rand() function
ExportedByKernel unsigned int generateSeed(const void* p = nullptr);
ExportedByKernel int safeRand(unsigned int& seed);

// case insensitive pattern matching
ExportedByKernel bool match(const char* pattern, const char* string);
}

#endif /*EKLib_H*/
