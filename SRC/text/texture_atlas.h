#ifndef __TEXTURE_ATLAS_H__
#define __TEXTURE_ATLAS_H__

#include "skyline_binpack.h"
#include <cstdint>
#include "raylib.h"

class TextureAtlas
{
public:
    TextureAtlas();
    ~TextureAtlas();
    bool Init(uint16_t width, uint16_t height);
    
    bool AddRegion(uint16_t width, uint16_t height, const uint8_t *data, uint16_t &x, uint16_t &y);

    void Clear();

    uint16_t Width() const { return width_; }
    uint16_t Height() const { return height_; }
    unsigned int TextureID() const { return texture_.id; }

    float Occupancy() { return binPacker_.Occupancy(); }
    
    Texture2D texture_;
    Image image_;
    //Shader mys;
private:
    uint16_t width_;
    uint16_t height_;
    SkylineBinPack binPacker_;
    //uint8_t *data_;
    //unsigned int texture_;
};

#endif // !__TEXTURE_ATLAS_H__
