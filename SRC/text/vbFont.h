#ifndef __FONT_H__
#define __FONT_H__

#include <ft2build.h>
#include FT_FREETYPE_H
#include <hb.h>
#include <hb-ft.h>

//------------------------------------------------------------------------------

class vbFont
{
    unsigned int ID_;
    
    float fontSize_;
    float contentScale_;
    bool bold_;
    bool italic_;
    float underlinePos_;
    float underlineThickness_;
    bool initOK_;

public:
    vbFont() {};
    vbFont(FT_Library *ftLib, const char* fontFile, float fontSize, float contentScale = 1.0f, bool bold = false, bool italic = false);
    ~vbFont();
    
    bool Ok() { return this->initOK_; }
    FT_Face ftFont_;
    hb_font_t* hbFont_;
    unsigned int getID() { return this->ID_; }
    FT_Face getFTFont() { return this->ftFont_; }
    hb_font_t* getHBFont() { return this->hbFont_; }
    float getSize() { return this->fontSize_; }
    float getContentScale() { return this->contentScale_; }
    bool getBold() { return this->bold_; }
    bool getItalic() { return this->italic_; }
    bool synthesisBold() 
    { 
        return (bold_ && !(ftFont_->style_flags & FT_STYLE_FLAG_BOLD));
    }
    bool synthesisItalic() 
    {
        return (italic_ && !(ftFont_->style_flags & FT_STYLE_FLAG_ITALIC));
    }
    float getUnderlinePos() 
    {
        return underlinePos_;
    }
    float getUnderlineThickness() 
    {
        return underlineThickness_;
    }
    
private:
    void init(FT_Library ftLib, const char* fontFile, float fontSize, float contentScale, bool bold, bool italic);
    unsigned int genID();
};

//------------------------------------------------------------------------------

#endif // !__FONT_H__
