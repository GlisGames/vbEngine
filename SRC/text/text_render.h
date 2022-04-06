#ifndef __TEXT_RENDER_H__
#define __TEXT_RENDER_H__

//#include "shader.h"
#include "vbFont.h"
#include "texture_atlas.h"
#include "vbTextBox.h"
//#include "vbTextBoxAlfons.h"

#include <string>
#include <map>
#include <vector>
#include <memory>
typedef std::pair<unsigned int, unsigned int> GlyphKey;

struct Glyph {
    Vector2 Size;       // Size of glyph
    Vector2 Bearing;    // Offset from horizontal layout origin to left/top of glyph
    Vector2 TexOffset;  // Offset of glyph in texture atlas
    int TexIdx;            // Texture atlas index
    unsigned int TexGen;   // Texture atlas generation
    float ascent;
    float descent;
    float height;
    FT_Face ff;
};

class TextRender
{
    typedef std::map<GlyphKey, Glyph> GlyphCache;

    //typedef std::vector<std::unique_ptr<TextureAtlas>> TexVector;
    typedef std::vector<TextureAtlas*> TexVector;
    typedef std::vector<unsigned int> TexGenVector;
    void DrawTextureFonthere(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
    TexVector tex_;
    TexGenVector texGen_;
    uint64_t texReq_;
    uint64_t texHit_;
    uint64_t texEvict_;
    GlyphCache glyphs_;
    Glyph line_;
    Shader mys;
    int mysLocation = -1;
    Shader sdfShader;
    unsigned int lastTexID_;
    Color currentColor_ = BLANK;
public:
    TextRender();
    ~TextRender();

    bool Init(int numTextureAltas);

    void DrawText(vbTextbox* text,
        float x,
        float y,
        Color color, float zoom = 1.0f, float rotation = 0);
    void DrawTextBounding(vbTextbox* text,
        float x,
        float y,
        Color color, float zoom = 1.0f, float rotation = 0);
    void DrawTextBoundingAlfons(vbTextbox* text,
        float x,
        float y,
        Color color, float zoom = 1.0f, float rotation = 0);
    //void CacheText(vbTextbox* text);
    void PrintStats();

    bool getGlyph(vbFont* font, unsigned int glyph_index, Glyph& x);
private:
    bool setupLineGlyph();
    bool addToTextureAtlas(uint16_t width, uint16_t height, const uint8_t *data, 
                           int &tex_idx, unsigned int &tex_gen, uint16_t &tex_x, uint16_t &tex_y);
    void setTexID(unsigned int texID);
    void commitDraw();
};

#endif // !__TEXT_RENDER_H__
