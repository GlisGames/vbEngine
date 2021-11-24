#include "vbEngine.h"

void PANIC(const char* message)
{
	TraceLog(LOG_ERROR, "\n PANIC: %s", message);
	exit(1);
}