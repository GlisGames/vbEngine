#include "text_render.h"
//#include "scope_guard.h"
#include "math.h"
#include "rlgl.h"
#include <assert.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
//#define TEXT_USE_SHADER

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

//------------------------------------------------------------------------------

static const char* vertex_shader_string = R"(
#version 100

attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
attribute vec3 vertexNormal;
attribute vec4 vertexColor;

uniform mat4 mvp;

varying vec2 fragTexCoord;
varying vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    gl_Position = mvp*vec4(vertexPosition, 1.0);
}
)";

static const char* sdf_shader = R"(
#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// NOTE: Add here your custom variables
const float smoothing = 1.0/16.0;

void main()
{
    // Texel color fetching from texture sampler
    // NOTE: Calculate alpha using signed distance field (SDF)
    float distance = texture2D(texture0, fragTexCoord).a;
    float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
    
    // Calculate final fragment color
    //gl_FragColor = vec4(fragColor.rgb, fragColor.a*alpha);
    gl_FragColor = vec4(fragColor.rgb, texture2D(texture0, fragTexCoord).r*alpha);
}
)";

static const char* sdf_shader33 = R"(
#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    // Texel color fetching from texture sampler
    // NOTE: Calculate alpha using signed distance field (SDF)
    float distanceFromOutline = texture(texture0, fragTexCoord).a - 0.5;
    float distanceChangePerFragment = length(vec2(dFdx(distanceFromOutline), dFdy(distanceFromOutline)));
    float alpha = smoothstep(-distanceChangePerFragment, distanceChangePerFragment, distanceFromOutline);

    // Calculate final fragment color
    //finalColor = vec4(fragColor.rgb, fragColor.a*alpha);
    finalColor = vec4(fragColor.rgb, texture2D(texture0, fragTexCoord).r*alpha);
}
)";


static const char* fragment_shader_string = R"(
#version 100
precision mediump float;
// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 textColor;

void main()
{
    vec4 texelColor = vec4(1.0, 1.0, 1.0, texture2D(texture0, fragTexCoord).r);   
    gl_FragColor = texelColor*textColor;
}
)";

const int TextureAtlasWidth  = 1024;
const int TextureAtlasHeight = 1024;

//------------------------------------------------------------------------------

TextRender::TextRender()
: texReq_(0), texHit_(0), texEvict_(0), line_(Glyph{}), lastTexID_(0)
{
}

TextRender::~TextRender()
{

}

bool TextRender::Init(int numTextureAtlas)
{
    assert(numTextureAtlas > 0 && numTextureAtlas <= 16);

    std::string errorLog;
#if !defined(PLATFORM_WEB) && !defined(PLATFORM_RPI)
    mys = LoadShader("vertex_shader.txt", "fragment_shader.txt");//FromMemory(vertex_shader_string, fragment_shader_string);
    //sdfShader = LoadShader("vertex_shader.txt", "fragment_shader.txt");//FromMemory(vertex_shader_string, fragment_shader_string);
#else
    mys = LoadShaderFromMemory(vertex_shader_string, fragment_shader_string);
#endif
    mysLocation = GetShaderLocation(mys, "textColor");
    //for (int i = 0; i < numTextureAtlas; i++)
    //{
    //    std::unique_ptr<TextureAtlas> t(new TextureAtlas);
    //    if (!t->Init(TextureAtlasWidth, TextureAtlasHeight))
    //    {
    //        return false;
    //    }
    //    tex_.push_back(std::move(t));
    //    texGen_.push_back(0);
    //}

    line_.TexIdx = -1;
    return true;
}

void TextRender::DrawTextureFonthere(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint)
{
    // Check if texture is valid
    if (texture.id > 0)
    {
        float width = (float)texture.width;
        float height = (float)texture.height;

        bool flipX = false;

        if (source.width < 0) { flipX = true; source.width *= -1; }
        if (source.height < 0) source.y -= source.height;

        Vector2 topLeft = { 0 };
        Vector2 topRight = { 0 };
        Vector2 bottomLeft = { 0 };
        Vector2 bottomRight = { 0 };

        // Only calculate rotation if needed
        if (rotation == 0.0f)
        {
            float x = dest.x - origin.x;
            float y = dest.y - origin.y;
            topLeft = { x, y };
            topRight = { x + dest.width, y };
            bottomLeft = { x, y + dest.height };
            bottomRight = { x + dest.width, y + dest.height };
        }
        else
        {
            float sinRotation = sinf(rotation * DEG2RAD);
            float cosRotation = cosf(rotation * DEG2RAD);
            float x = dest.x;
            float y = dest.y;
            float dx = -origin.x;
            float dy = -origin.y;

            topLeft.x = x + dx * cosRotation - dy * sinRotation;
            topLeft.y = y + dx * sinRotation + dy * cosRotation;

            topRight.x = x + (dx + dest.width) * cosRotation - dy * sinRotation;
            topRight.y = y + (dx + dest.width) * sinRotation + dy * cosRotation;

            bottomLeft.x = x + dx * cosRotation - (dy + dest.height) * sinRotation;
            bottomLeft.y = y + dx * sinRotation + (dy + dest.height) * cosRotation;

            bottomRight.x = x + (dx + dest.width) * cosRotation - (dy + dest.height) * sinRotation;
            bottomRight.y = y + (dx + dest.width) * sinRotation + (dy + dest.height) * cosRotation;
        }

        rlCheckRenderBatchLimit(4);     // Make sure there is enough free space on the batch buffer
        rlBegin(RL_QUADS);
        rlSetTexture(texture.id);

        rlColor4ub(tint.r, tint.g, tint.b, tint.a);
        rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer

        // Top-left corner for texture and quad
        rlTexCoord2f(source.x, source.y);
        rlVertex2f(topLeft.x, topLeft.y);

        // Bottom-left corner for texture and quad
        rlTexCoord2f(source.x, (source.y + source.height));
        rlVertex2f(bottomLeft.x, bottomLeft.y);

        // Bottom-right corner for texture and quad
        rlTexCoord2f((source.x + source.width), (source.y + source.height));
        rlVertex2f(bottomRight.x, bottomRight.y);

        // Top-right corner for texture and quad
        rlTexCoord2f((source.x + source.width), source.y);
        rlVertex2f(topRight.x, topRight.y);

        rlEnd();
        rlSetTexture(0);
    }
}
#define MEMCMP(a, b) memcmp((a), (b), (sizeof(a) < sizeof(b)) ? sizeof(a) : sizeof(b))

void TextRender::DrawTextBoundingAlfons(vbTextbox* text,
    float initialx,
    float initialy,
    Color color, float zoom, float rotation)
{
#ifdef TEXT_USE_SHADER
    BeginShaderMode(mys);
    if (MEMCMP(&color, &currentColor_) != 0)
    {
        currentColor_ = color;
        float tocolor[4] = { (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f, };
        SetShaderValue(mys, this->mysLocation, tocolor, SHADER_UNIFORM_VEC4);
    }
#endif
    text->draw(initialx, initialy);

#ifdef TEXT_USE_SHADER
    EndShaderMode();
#endif
    
    if (text->debugBox) //debug bounding box
        DrawRectangleLinesEx({ initialx, initialy, text->getBoundingBox().x ,text->getBoundingBox().y }, 1, RED);
    //DrawLine(initialx, initialy, 1000, initialy, VIOLET); //Debug baseline

}



/*
void TextRender::CacheText(vbTextbox* text)
{
    // Iterate over each glyph.
    size_t glyph_count = text->GetGlyphCount();
    float x = 0;
    float y = 0;
    float zoom = 1;
    float maxs = text->getMaxHeight();
    Vector2 box = text->getPrintSize();
    UnloadTexture(text->cachetxt);
    //-------------------------------------
    RenderTexture2D target = LoadRenderTexture(box.x, box.y);
    BeginTextureModePro(target);
    this->DrawText(text, 0, 0, text->colour, text->zoom, text->rotation);
    //text->cachetxt = target.texture;
    Image toflip = GetTextureData(target.texture);
    ImageFlipVertical(&toflip);
    text->cachetxt = LoadTextureFromImage(toflip);
    //void *data = rlReadScreenPixels(target.)
    EndTextureMode();
    UnloadRenderTexture(target);
    //rlUnloadFramebuffer(target.id);
    return;

    /*
    //Image im = GenImageColor(box.x, box.y, CLITERAL(Color){ 255, 0, 0, 255 });
    //im.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;

    text->cachetxt = LoadTextureFromImage(GenImageColor(box.x, box.y, BLANK));
    //UpdateTexture
    for (size_t i = 0; i < glyph_count; i++)
    {
        GlyphInfo info;
        text->GetGlyph(i, info);

        Glyph g;
        if (!getGlyph(text->GetFont(), info.glyphid, g))
        {
            // TODO: error log
            break;
        }

        if (g.Size.x > 0 && g.Size.y > 0)
        {
            TextureAtlas* t = tex_[g.TexIdx].get();
            float glyph_x = (x + g.Bearing.x * zoom + info.x_offset * zoom);

            float glyph_y = y - (g.descent * zoom + g.Bearing.y * zoom) - info.y_offset * zoom; //OK NO FLIP
            glyph_y += (g.ff->bbox.yMax / 64.0f) * zoom;
            glyph_y += maxs;

            float glyph_w = (float)g.Size.x;
            float glyph_h = (float)g.Size.y;

            float tex_x = g.TexOffset.x;
            float tex_y = g.TexOffset.y;
            float tex_w = glyph_w * zoom;
            float tex_h = glyph_h * zoom;

            Rectangle source = { tex_x, tex_y, tex_w, tex_h };
            Rectangle dest = { glyph_x, glyph_y, glyph_w * zoom, glyph_h * zoom };
            UpdateTextureRec(text->cachetxt, dest, rlReadTexturePixelsRect(t->texture_, source));
            //text->cachetxt.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
            //UpdateTextureRec(text->cachetxt, dest, g.ff->glyph->bitmap.buffer);

        }
        // advance cursors for next glyph
        x += info.x_advance * zoom;
        y += info.y_advance * zoom;
    }
}
*/
void TextRender::PrintStats()
{
    fprintf(stdout, "\n");
    fprintf(stdout, "----glyph texture cache stats----\n");
    fprintf(stdout, "texture atlas size: %d %d\n", TextureAtlasWidth, TextureAtlasHeight);
    fprintf(stdout, "texture atlas count: %d\n", (int)tex_.size());
    fprintf(stdout, "texture atlas occupancy:");
    for (size_t i = 0; i < tex_.size(); i++)
    {
        float rate = tex_[i].get()->Occupancy() * 100.f;
        fprintf(stdout, " %.1f%%", rate);
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "texture atlas evict: %llu\n", texEvict_);
    fprintf(stdout, "request: %llu\n", texReq_);
    fprintf(stdout, "hit    : %llu (%.2f%%)\n", texHit_, (double)texHit_ / texReq_ * 100);
    fprintf(stdout, "\n");
}

bool TextRender::getGlyph(vbFont *font, unsigned int glyph_index, Glyph& x)
{
    GlyphKey key = GlyphKey{ font->getID(), glyph_index };
    GlyphCache::iterator iter = glyphs_.find(key);
    if (iter != glyphs_.end())
    {
        x = iter->second;
        if (x.TexIdx < 0)
        {
            return true;
        }
        else if (x.TexGen == texGen_[x.TexIdx])  // check texture atlas generation
        {
            texReq_++;
            texHit_++;
            return true;
        }
    }

    // load glyph
    FT_Face face = font->getFTFont();
    if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT)) //FT_LOAD_DEFAULT
    {
        return false;
    }
    if (font->synthesisItalic())
    {
        // horizontal shear
        FT_Matrix matrix;
        matrix.xx = 0x10000L;
        matrix.xy = (FT_Fixed)(0.3 * 0x10000L);
        matrix.yx = 0;
        matrix.yy = 0x10000L;
        FT_Outline_Transform(&face->glyph->outline, &matrix);
    }
    if (font->synthesisBold())
    {
        FT_Outline_Embolden(&face->glyph->outline, (FT_Pos)(font->getSize() * 0.04 * 64));
    }
    if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
    {
        return false;
    }
   
    int texIdx = -1;
    unsigned int texGen = 0;
    uint16_t texOffsetX = 0, texOffsetY = 0;
    if (face->glyph->bitmap.width > 0 && face->glyph->bitmap.rows > 0)
    {
        if (!addToTextureAtlas(face->glyph->bitmap.width, 
                               face->glyph->bitmap.rows, 
                               face->glyph->bitmap.buffer, 
                               texIdx,
                               texGen,
                               texOffsetX, 
                               texOffsetY))
        {
            return false;
        }

        texReq_++;
    }
    // now store Glyph for later use
    x = Glyph{
        {(float)face->glyph->bitmap.width,(float)face->glyph->bitmap.rows},
        {(float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top},
        {(float)texOffsetX, (float)texOffsetY},
        texIdx,
        texGen,
        (float)face->ascender/64.0f,
        (float)face->bbox.yMax/ 64.0f,
        (float)face->size->metrics.height / 64.0f, face
    };
    glyphs_[key] = x;

    return true;
}

bool TextRender::setupLineGlyph()
{
    if (line_.TexIdx >= 0 && line_.TexGen == texGen_[line_.TexIdx])
    {
        return true;
    }

    static uint8_t data[4*4] = {
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
    };
    uint16_t tex_x, tex_y;
    if (addToTextureAtlas(4, 4, data, line_.TexIdx, line_.TexGen, tex_x, tex_y))
    {
        line_.Size.x = 4;
        line_.Size.y = 4;
        line_.TexOffset.x = tex_x;
        line_.TexOffset.y = tex_y;
        return true;
    }

    return false;
}

bool TextRender::addToTextureAtlas(uint16_t width, uint16_t height, const uint8_t *data, 
                                   int &tex_idx, unsigned int &tex_gen, uint16_t &tex_x, uint16_t &tex_y)
{
    for (size_t i = 0; i < tex_.size(); i++)
    {
        TextureAtlas *t = tex_[i].get();
        if (t->AddRegion(width, height, data, tex_x, tex_y))
        {
            tex_idx = (unsigned int)i;
            tex_gen = texGen_[i];
            return true;
        }
    }

    // evict a random choosed one
    size_t index = (size_t)rand() % tex_.size();
    TextureAtlas *tex = tex_[index].get();
    // clear contents
    tex->Clear();
    // increment generation
    texGen_[index]++;
    texEvict_++;

    // retry
    if (tex->AddRegion(width, height, data, tex_x, tex_y))
    {
        tex_idx = index;
        tex_gen = texGen_[index];
        return true;
    }

    return false;
}

void TextRender::setTexID(unsigned int texID)
{

}

void TextRender::commitDraw()
{

}
