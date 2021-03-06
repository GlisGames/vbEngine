#include "vbFont.h"
#include "vbErrors.h"
//#include "scope_guard.h"

vbFont::vbFont(FT_Library *ftLib, const char* fontFile, float fontSize, float contentScale, bool bold, bool italic)
: ftFont_(NULL), hbFont_(NULL), 
  fontSize_(0), contentScale_(0), bold_(false), italic_(false), underlinePos_(0), underlineThickness_(0), 
  initOK_(false)
{
    init(*ftLib, fontFile, fontSize, contentScale, bold, italic);
}

vbFont::~vbFont()
{
    if (hbFont_)
    {
        hb_font_destroy(hbFont_);
        hbFont_ = NULL;
    }
    if (ftFont_)
    {
        FT_Done_Face(ftFont_);
        ftFont_ = NULL;
    }
}

void vbFont::init(FT_Library ftLib, const char* fontFile, float fontSize, float contentScale, bool bold, bool italic)
{
    if (ftLib == NULL)
        PANIC("ftlib not initialized...");
    if (FT_New_Face(ftLib, fontFile, 0, &ftFont_))
    {
        return;
    }
    //auto ftFont_guard = scopeGuard([this]{ FT_Done_Face(ftFont_); ftFont_ = NULL; });

#if defined(_WIN32)
    const int logic_dpi_x = 96;
    const int logic_dpi_y = 96;
#elif defined(__APPLE__)
    const int logic_dpi_x = 72;
    const int logic_dpi_y = 72;
#else
    const int logic_dpi_x = 96;
    const int logic_dpi_y = 96;
    //#error "not implemented"
#endif
    FT_Set_Char_Size(
        ftFont_, 
        0,                                       // same as character height
        (FT_F26Dot6)(fontSize*contentScale*64),  // char_height in 1/64th of points
        logic_dpi_x,                             // horizontal device resolution
        logic_dpi_y                              // vertical device resolution
    );

    underlinePos_ = 
        ftFont_->underline_position / (float)ftFont_->units_per_EM * ftFont_->size->metrics.y_ppem;
    underlineThickness_ = 
        ftFont_->underline_thickness / (float)ftFont_->units_per_EM * ftFont_->size->metrics.y_ppem;

    hbFont_ = hb_ft_font_create_referenced(ftFont_);

    //ftFont_guard.dismiss();
    ID_ = genID();
    fontSize_ = fontSize;
    contentScale_ = contentScale;
    bold_ = bold;
    italic_ = italic;
    if (synthesisBold())
    {
        underlineThickness_ *= 1.5f;
    }
    initOK_ = true;
    return;
}

unsigned int vbFont::genID()
{
    static unsigned int s_ID = 0;
    return (++s_ID);
}
