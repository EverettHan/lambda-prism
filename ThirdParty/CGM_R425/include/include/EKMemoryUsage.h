#ifndef EKMemoryUsage_H
#define EKMemoryUsage_H

#include "EKExportedByKernel.h"
#include <stdint.h>

namespace EK
{
ExportedByKernel bool getPhysicalMemory(uint64_t& availablePhysicalMemory, uint64_t& totalPhysicalMemory);
ExportedByKernel double getPhysicalMemoryLoadInPercent();

ExportedByKernel bool getProcessMemory(uint64_t& mem);
ExportedByKernel bool getProcessMemory(uint64_t& mem, int pid);

ExportedByKernel bool getPhysicalMemoryInMB(int& availablePhysicalMemory, int& totalPhysicalMemory);
ExportedByKernel bool getProcessMemoryInMB(int& mem);
ExportedByKernel bool getProcessMemoryInMB(int& mem, int pid);
}

#endif /*EKMemoryUsage_H*/
