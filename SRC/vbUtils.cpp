#include "vbEngine.h"

std::string getParentFolder(string path)
{
	string folder = path;
	BOOL startAdd = FALSE;
	WORD intexBegin = 0;
	WORD intexEnd = 0;

	for (int i = folder.length()-1; i >= 0; i--)
	{
		if (folder[i] == '/' || folder[i] == '\\')
		{
			if (!startAdd)
			{
				intexBegin = i;
				startAdd = TRUE;
			}
			else
			{
				intexEnd = i + 1;
				break; //found a second parent folder, stop.
			}
		}
	}
	try
	{
		return folder.substr(intexEnd, (intexBegin - intexEnd));
	}
	catch (std::exception e)
	{
		return "";
	}
}

const char* formatMoney(DWORD value)
{
	//if currency = Euro
	//return TextFormat(u8"€%.2f", (float)value / 100.0f);
	return TextFormat("€%.2f", (float)value / 100.0f);
}
