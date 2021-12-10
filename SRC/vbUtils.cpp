#include "vbEngine.h"

const char* formatMoney(DWORD value)
{
	//if currency = Euro
	return TextFormat(u8"€%.2f", (float)value / 100.0f);
}