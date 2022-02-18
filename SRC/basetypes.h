#ifndef BASETYPES_H
#define BASETYPES_H

#include "raylib.h"

#include <locale>
#include <codecvt>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <algorithm>
#include <list> 
using namespace std;
#define TRUE 1
#define FALSE 0
#define VBMIN(a,b) (((a)<(b))?(a):(b))
#define VBMAX(a,b) (((a)>(b))?(a):(b))
#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

//PHYSICS
#define PPM 100

#define lvoid [=]()
typedef void(*fvoid)();

#define BREAKPOINT char _breakhere_ = 0
typedef unsigned char BOOL;				// 8 bit unsigned

typedef unsigned char BYTE;				// 8 bit unsigned
typedef unsigned int WORD;				//16 bit unsigned
typedef unsigned long int DWORD;		//32 bit unsigned
typedef unsigned  long long int QWORD;	//64 bit unsigned

typedef unsigned int SWORD;				//16 bit signed
typedef unsigned long int SDWORD;		//32 bit signed
typedef unsigned  long long int SQWORD;	//64 bit signed
typedef float FLOAT;

typedef std::vector<Texture2D*> Texture2Dvector;
typedef std::vector<Sound*> Soundvector;
typedef std::vector<std::vector<BYTE>> t_grid;

typedef std::string vbString;

//class vbString : public std::wstring
//{
//private:
//    std::wstring fromString(string s)
//    {
//        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//        return converter.from_bytes(s);
//    }
//public:
//    vbString() :wstring() {};
//    vbString(wstring& s) :wstring(s) {};
//    vbString(const wchar_t* s) :wstring(s) {};
//    vbString(string &s) :wstring(this->fromString(s)) {};
//    vbString(const char* s) :wstring(this->fromString(s)) {};
//
//    std::string toStdString()
//    {
//        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//        return converter.to_bytes(*this);
//    }
//    std::string toChar()
//    {
//        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//        return converter.to_bytes(*this).c_str();
//    }
//
//};

enum class hwButton
{
    BUTTON_NONE = 0,
    BUTTON_TOUCH = 0,
    BUTTON_START = (1u << 0),
    BUTTON_CHANGEBET = (1u << 1),
    BUTTON_TICKETOUT = (1u << 2),
    BUTTON_HELP = (1u << 3),
    BUTTON_AUTOPLAY = (1u << 4),
    BUTTON_MINBET = (1u << 5),
    BUTTON_MAXBET = (1u << 6),
    BUTTON_LINESUP = (1u << 7),
    BUTTON_LINESDOWN = (1u << 8),
    BUTTON_BETUP = (1u << 9),
    BUTTON_BETDOWN = (1u << 10),
    BUTTON_GAME1 = (1u << 11),
    BUTTON_GAME2 = (1u << 12),
    BUTTON_GAME3 = (1u << 13),
    BUTTON_GAME4 = (1u << 14)
};

#define myfor(var, cond, comp) for(decltype(comp) var = 0; var cond comp; var++)
#define myforfor(var1, var2, cond, comp1, comp2) myfor(var1, cond, comp1) myfor(var2, cond, comp2)
/*
template<typename T>
class matrix {
    std::vector<std::vector<T>> content;
    size_t width;
    size_t height;

public:
    matrix(size_t width_, size_t height_) : width{ width_ }, height{ height_ }
    {
        content.resize(height);

        for (size_t i = 0; i < height; ++i)
        {
            content[i].resize(width);
        }
    }

    const std::vector<T>& operator[](size_t row_index) const {
        return content[row_index];
    }

    std::vector<T>& operator[](size_t row_index) {
        return content[row_index];
    }

    size_t get_width()  const { return width; }
    size_t get_height() const { return height; }
};

template<typename T1, typename T2>
auto operator*(const matrix<T1>& a, const matrix<T2>& b)->matrix<decltype(T1{} *T2{}) >
{
    if (a.get_height() != b.get_width())
    {
        std::stringstream ss;
        ss << "Matrix dimenstion mismatch: ";
        ss << a.get_height();
        ss << " x ";
        ss << a.get_width();
        ss << " times ";
        ss << b.get_height();
        ss << " x ";
        ss << b.get_width();
        ss << ".";
        throw std::runtime_error(ss.str());
    }

    using value_type = decltype(T1{} + T2{});
    matrix<decltype(T1{} *T2{}) > result(a.get_height(), b.get_width());

    for (size_t rowa = 0; rowa != a.get_height(); ++rowa)
    {
        for (size_t colb = 0; colb != b.get_width(); ++colb)
        {
            value_type sum = 0;

            for (size_t i = 0; i != a.get_width(); ++i)
            {
                sum += a[rowa][i] * b[i][colb];
            }

            result[rowa][colb] = sum;
        }
    }

    return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, matrix<T> m)
{
    size_t maximum_entry_length = 0;

    for (size_t row = 0; row < m.get_height(); ++row)
    {
        for (size_t col = 0; col < m.get_width(); ++col)
        {
            std::stringstream ss;
            ss << m[row][col];
            std::string entry_text;
            ss >> entry_text;
            maximum_entry_length = std::max(maximum_entry_length,
                entry_text.length());
        }
    }

    for (size_t row = 0; row < m.get_height(); ++row)
    {
        for (size_t col = 0; col < m.get_width(); ++col)
        {
            os << std::setw((int)maximum_entry_length) << m[row][col];

            if (col < m.get_width() - 1)
            {
                os << ' ';
            }
        }

        if (row < m.get_height() - 1)
        {
            os << '\n';
        }
    }

    return os;
}
*/
#endif // !INCLUDES_H
