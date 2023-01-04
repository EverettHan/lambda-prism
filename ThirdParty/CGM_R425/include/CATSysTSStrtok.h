#ifndef CATSysTSStrtok_h
#define CATSysTSStrtok_h

/**
 * COPYRIGHT DASSAULT SYSTEMES 2004
 */
 
#include "JS0MT.h"

/**
 * Equivalent of strtok_r useable on all operating systems
 */
ExportedByJS0MT char * CATSysTSStrtok(char * orig, const char * sep, char ** ptr);

#endif // CATSysTSStrtok_h
