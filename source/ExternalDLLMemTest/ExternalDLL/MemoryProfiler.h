#pragma once

#include "windows.h"
#include "psapi.h"
#include "stdio.h"

#define MEMORY_USAGE_PROFILER_FILE_OUT "MemoryConsumption.log"

#define TRACE_MEMORY_USAGE { \
	PROCESS_MEMORY_COUNTERS_EX __pmc; \
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&__pmc, sizeof(__pmc)); \
	SIZE_T __virtualMemUsedByMe = __pmc.PrivateUsage; \
	FILE* f; \
	fopen_s(&f, MEMORY_USAGE_PROFILER_FILE_OUT, "a"); \
	printf("%d\n", __virtualMemUsedByMe); \
	fprintf(f, "%d\n", __virtualMemUsedByMe); \
	fflush(f); \
	fclose(f); \
}