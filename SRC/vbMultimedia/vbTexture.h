#ifndef vbTexture_H
#define vbTexture_H

#include "basetypes.h"

class vbSpriteTexture
{
public:
    WORD spriteID = 0;
    string name = "";
    Rectangle spriteFrame = { 0,0,0,0 };
    Rectangle originalcut = { 0,0,0,0 };
    Vector2 originalSize = { 0,0 };
    DWORD width = 0;
    DWORD height = 0;

    vbSpriteTexture() {};
    vbSpriteTexture(WORD _spriteID, string _name, Rectangle _frame, Rectangle _cut, Vector2 _originalSize)
    {
        spriteID = _spriteID;
        name = _name;
        spriteFrame = _frame;
        originalcut = _cut;
        originalSize = _originalSize;
        width = originalSize.x;
        height = originalSize.y;
    }

    struct seqAlphabeticalOrder
    {
        inline bool operator() (const vbSpriteTexture* s1, const vbSpriteTexture* s2)
        {
            return ((s1->name) < s2->name);
        }
    };
};

typedef std::vector<vbSpriteTexture*> vbSpriteTexture2Dvector;
#endif