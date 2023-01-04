#ifndef EKStorageUsage_H
#define EKStorageUsage_H

#include "EKExportedByKernel.h"
#include <stdint.h>

namespace EK
{
ExportedByKernel bool getStorageSpace(uint64_t& availableStorageSpace, uint64_t& totalStorageSpace);
ExportedByKernel bool getStorageSpace(const char* path, uint64_t& availableStorageSpace, uint64_t& totalStorageSpace);
}

#endif /*EKStorageUsage_H*/
