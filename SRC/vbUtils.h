#ifndef VBUTILS_H
#define VBUTILS_H
#include "basetypes.h"
#include <locale>
#include <codecvt>
#include <string>
namespace Frames
{
	static BOOL afterAndEvery(DWORD currentFrame, DWORD after, DWORD every)
	{
		return (currentFrame > after && !((currentFrame + after) % every));
	}
}

const char* formatMoney(DWORD value);

/// <summary>
/// Takes out 50% of the brightness of the given color
/// </summary>
/// <param name="c">the color you want to make darker</param>
/// <returns></returns>
static Color ColorTurnOff(Color c)
{
	Color ret = c;
	ret.r /= 2;
	ret.g /= 2;
	ret.b /= 2;
	return ret;
}

static Color colorApplyFilter(Color color, Color filter)
{
	Color ret = color;
	float cR = (float)filter.r / 255;
	float cG = (float)filter.g / 255;
	float cB = (float)filter.b / 255;
	float cA = (float)filter.a / 255;
	ret.r = (unsigned char)(((float)color.r / 255 * cR) * 255.0f);
	ret.g = (unsigned char)(((float)color.g / 255 * cG) * 255.0f);
	ret.b = (unsigned char)(((float)color.b / 255 * cB) * 255.0f);
	ret.a = (unsigned char)(((float)color.a / 255 * cA) * 255.0f);
	return ret;
}

namespace utils
{
	static std::string wstringToBytes(std::wstring s)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(s);
	}
}
#endif
