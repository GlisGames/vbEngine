#ifndef VBUTILS_H
#define VBUTILS_H
#include "basetypes.h"
#include <locale>
#include <codecvt>
#include <string>
namespace Frames
{
	static BOOL afterAndEvery(QWORD currentFrame, QWORD after, QWORD every)
	{
		return (currentFrame > after && !((currentFrame + after) % every));
	}
}

std::string getParentFolder(string path);
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

static Color ColorTurnOffPercent(Color c, float percent = 100.0f)
{
	Color ret = c;
	percent /= 100;
	ret.r *= percent;
	ret.g *= percent;
	ret.b *= percent;
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

static bool IsKeyPressedAny()
{
	return (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_B) ||
		IsKeyPressed(KEY_C) || IsKeyPressed(KEY_D) ||
		IsKeyPressed(KEY_E) || IsKeyPressed(KEY_F) ||
		IsKeyPressed(KEY_G) || IsKeyPressed(KEY_H) ||
		IsKeyPressed(KEY_I) || IsKeyPressed(KEY_J) ||
		IsKeyPressed(KEY_K) || IsKeyPressed(KEY_L) ||
		IsKeyPressed(KEY_M) || IsKeyPressed(KEY_N) ||
		IsKeyPressed(KEY_O) || IsKeyPressed(KEY_P) ||
		IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_R) ||
		IsKeyPressed(KEY_S) || IsKeyPressed(KEY_T) ||
		IsKeyPressed(KEY_U) || IsKeyPressed(KEY_V) ||
		IsKeyPressed(KEY_W) || IsKeyPressed(KEY_X) ||
		IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_Z) ||
		IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) ||
		IsKeyPressed(KEY_BACKSPACE));
}


#endif
