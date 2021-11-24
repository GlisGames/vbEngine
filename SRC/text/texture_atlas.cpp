#include "texture_atlas.h"
#include "rlgl.h"
//#include "external/glad.h"
#include <cassert>
#include <cstdlib>
#include "raylib.h"

TextureAtlas::TextureAtlas()
: width_(0), height_(0),/* data_(nullptr),*/ texture_()
{
}

TextureAtlas::~TextureAtlas()
{
    //free(data_);
    UnloadTexture(texture_);
    //glDeleteTextures(1, &texture_);
}

bool TextureAtlas::Init(uint16_t width, uint16_t height)
{
    //mys = LoadShaderFromMemory(vertex_shader_string, fragment_shader_string);
    assert(width > 0);
    assert(height > 0);

    width_ = width;
    height_ = height;
    
    binPacker_.Init(width, height);
    //Image im = GenImageColor(width, height, { 255,255,255,0 });
    Image im = GenImageColor(width, height, CLITERAL(Color){ 255, 0, 0, 255 });
    im.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
    //ImageColorGrayscale(&im);
    texture_ = LoadTextureFromImage(im);
    // generate texture
    
    //texture_.width = width;
    //texture_.height = height;
    //texture_.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;

    //texture_.id = rlLoadFontAtlas(width, height);
    //texture_.id = rlLoadTexture(im.data, im.width, im.height, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, 0);
    
    //glGenTextures(1, &texture_.id);
    //glBindTexture(GL_TEXTURE_2D, texture_.id);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glTexImage2D(
    //    GL_TEXTURE_2D,
    //    0,
    //    GL_RED,
    //    width_,
    //    height_,
    //    0,
    //    GL_RED,
    //    GL_UNSIGNED_BYTE,
    //    nullptr
    //);
    //// set texture options
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glBindTexture(GL_TEXTURE_2D, 0);
    

    return true;
}

bool TextureAtlas::AddRegion(uint16_t width, uint16_t height, const uint8_t *data, uint16_t &x, uint16_t &y)
{
    assert(width > 0);
    assert(height > 0);
    assert(data != nullptr);

    assert(width_ > 0);
    assert(height_ > 0);
    //assert(data_ != nullptr);

    //binRect r = binPacker_.Insert(width+1, height+1);
    binRect r = binPacker_.Insert(width+4, height+4);
    if (r.height <= 0)
    {
        return false;
    }

    //Copy the image in the CPU memory atlas (not the GPU one)
    //for (uint16_t i = 0; i < height; i++)
    //{
    //    memcpy(data_ + ((r.y + i) * width_ + r.x), data + i * width, width);
    //}
    // TODO Optimization of text rendering
    //RenderTexture2D target = LoadRenderTexture(width, height);
    //BeginDrawing();
    //BeginTextureMode(target);
    //BeginShaderMode(mys);
    //Color color = WHITE;
    //float tocolor[4] = { (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f, };
    //SetShaderValue(mys, GetShaderLocation(mys, "textColor"), tocolor, SHADER_UNIFORM_VEC4);

    //glBindTexture(GL_TEXTURE_2D, texture_.id);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, r.x, r.y, width, height, GL_RED, GL_UNSIGNED_BYTE, data);
    //glBindTexture(GL_TEXTURE_2D, 0);
    rlUpdateTexture(texture_.id, r.x+2, r.y+2, width, height, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, data);  
    x = r.x+2;
    y = r.y+2;
    
    return true;
}

void TextureAtlas::Clear()
{
    assert(width_ > 0);
    assert(height_ > 0);
    //assert(data_ != nullptr);
    //assert(texture_ != 0);

    binPacker_.Init(width_, height_);

    //memset(data_, 0, width_ * height_ * 1 * sizeof(uint8_t));

    //glBindTexture(GL_TEXTURE_2D, texture_);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RED, GL_UNSIGNED_BYTE, data_);
    //glBindTexture(GL_TEXTURE_2D, 0);
}
