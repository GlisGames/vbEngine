#include "vbEngine.h"
#include "rlgl.h"
#include <assert.h>
#include <alfons/path/lineSampler.h>
#include <algorithm>
#include <vector>
#include <limits>
//#define TEXT_USE_SHADER
#ifdef USE_SDF
#define SDF_IMPLEMENTATION
#include "sdf.h"
#endif

GlyphTextureAtlas::GlyphTextureAtlas()
{
    resetAtlas();
    //atlasImage = GenImageColor
}

void GlyphTextureAtlas::resetAtlas()
{
    texData.clear();
    width = 0;
    height = 0;
    dirty = true;
    for (int index = 0; index < 4; ++index) {
        dirtyRect[index] = 0;
    }
}

QuadBatch::QuadBatch()
{
    resetVertexData();
}

void QuadBatch::resetVertexData() 
{ 
    rectDest.clear();
    rectSource.clear();
    atlasTarget.clear();
    boundingX1 = 0;
    boundingY1 = 0;
    boundingX2 = 0;
    boundingY2 = 0;
    boundingY2 = 0;
}

int QuadBatch::size() const
{
    return rectDest.size();
}

void QuadBatch::add(const alfons::Rect& _rect, const alfons::Glyph& _glyph, const alfons::AtlasID _atlasID)
{
    if (rectDest.empty()) {
        boundingX1 = _rect.x1;
        boundingY1 = _rect.y1;
        boundingX2 = _rect.x2;
        boundingY2 = _rect.y2;
    }
    Rectangle dest = { (float)_rect.x1, (float)_rect.y1, (float)_rect.x2 - (float)_rect.x1, (float)_rect.y2 - (float)_rect.y1 };
    rectDest.push_back(dest);
    if (_rect.x1 < boundingX1) {
        boundingX1 = _rect.x1;
    }
    if (_rect.y1 < boundingY1) {
        boundingY1 = _rect.y1;
    }
    if (_rect.x2 > boundingX2) {
        boundingX2 = _rect.x2;
    }
    if (_rect.y2 > boundingY2) {
        boundingY2 = _rect.y2;
    }
    Rectangle src = { (float)_glyph.u1, (float)_glyph.v1, (float)_glyph.u2 - (float)_glyph.u1, (float)_glyph.v2 - (float)_glyph.v1 };
    rectSource.push_back(src);
    atlasTarget.push_back(_atlasID);
}

vbAlfonsFontManager& vbAlfonsFontManager::getAlfonsFontManager()
{
    static vbAlfonsFontManager g_vbAlfonsFontManager;
    return g_vbAlfonsFontManager;
}

vbAlfonsFontManager::vbAlfonsFontManager() :
    atlas(*this, 1024, 2)
{
#ifndef TEXT_USE_SHADER
    //this->loadTextureAtlas();
#endif
}

FontPtr vbAlfonsFontManager::addFont(const char* fontname, const char* fontFile, float fontSize)
{
    font = fontMan.addFont(fontname, alfons::Font::Properties(fontSize), alfons::InputSource(fontFile));
    addFontFace("notosans.otf", fontSize);
    return font;
    //return (font == nullptr);
}

bool vbAlfonsFontManager::addFontFace(const char* fontFile, float fontSize)
{
    if (font != nullptr) {
        return font->addFace(fontMan.addFontFace(alfons::InputSource(fontFile), fontSize));
    }
    else {
        return false;
    }
}

alfons::LineLayout vbAlfonsFontManager::shapeText(vbString txt, FontPtr fnt)
{
    return shaper.shape(fnt, txt);
}

Texture2D vbAlfonsFontManager::loadTexture(GlyphTextureAtlas& atlas)
{
    Texture2D rlTexture = { 0 };
#ifdef TEXT_USE_SHADER
    if (atlas.texData.size() > 0) {
        Image img = LoadImageRawFromBuffer(&atlas.texData[0], atlas.texData.size(),
            atlas.width, atlas.height, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, 0 /*header size*/);
        rlTexture = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    else {
        TRACELOG(LOG_ERROR, "No texture for Alfons text rendering!");
    }
#else
	Image img = GenImageColor(atlas.width, atlas.height, BLANK);
    rlTexture = LoadTextureFromImage(img);
    UnloadImage(img);
#endif
    return rlTexture;
}

void vbAlfonsFontManager::loadTextureAtlas()
{
    if (glyphTextureAtlas.dirty) {
        //if(atlasTexture.width == 0)
        //    atlasTexture = loadTexture(glyphTextureAtlas);
#ifdef TEXT_USE_SHADER
        else
            UpdateTexture(atlasTexture, &glyphTextureAtlas.texData[0]);
#endif // TEXT_USE_SHADER
        glyphTextureAtlas.dirty = false;
    }
    // Debug: test the atlas
    //DrawRectangle(0, 0, pGAME->gameResolution.x, pGAME->gameResolution.y, BLACK);
    //DrawTexture(atlasTexture, 0, 0, WHITE/*CLITERAL(Color){ 200, 200, 200, 255 }*/);
}

void vbAlfonsFontManager::addTexture(alfons::AtlasID id, uint16_t textureWidth, uint16_t textureHeight)
{
    //Image plain = GenImageColor(textureWidth, textureHeight, BLANK);
    //ImageFormat(&plain, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE);
    //this->atlasTexture = LoadTextureFromImage(plain); //TEST

    glyphTextureAtlas.resetAtlas();
    if (id > 0) {
        TRACELOG(LOG_INFO, "Unexpected Alfons Atlas Id.");
    }
    glyphTextureAtlas.width = textureWidth;
    glyphTextureAtlas.height = textureHeight;
#ifdef TEXT_USE_SHADER
    glyphTextureAtlas.texData.resize(textureWidth * textureHeight);
#else
    atlasTexture.push_back(loadTexture(glyphTextureAtlas));
#endif
}

void vbAlfonsFontManager::addGlyph(alfons::AtlasID id, uint16_t gx, uint16_t gy, uint16_t gw, uint16_t gh, const unsigned char* src, uint16_t padding)
{
//    printf("addGlyph");
    auto& texData = glyphTextureAtlas.texData;
    auto& dirtyRect = glyphTextureAtlas.dirtyRect;
    auto width = glyphTextureAtlas.width;
    unsigned int stride = width;
    //PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
#ifndef TEXT_USE_SHADER
    Image img = LoadImageRawFromBuffer((unsigned char*)src, gw * gh, gw, gh, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, 0);
    Image target = GenImageColor(gw, gh, BLANK);
    //ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    //ImageColorInvert(&img);
    //ImageColorReplace(&img, BLACK, BLANK);
    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            Color p = GetImageColor(img, x, y);
            if (p.r != 255 && p.r != 0)
                BREAKPOINT;
            if (p.r)
            {
                Color c = WHITE;
                c.a = p.r; //give alpha channel equal to the grayscale
                ImageDrawPixel(&target, x, y, c);
            }
        }
    }    
    Rectangle upd;
    upd.x = gx + padding;
    upd.y = gy + padding;
    upd.width = gw;
    upd.height = gh;
    UpdateTextureRec(this->atlasTexture[id], upd, target.data);
    UnloadImage(img);
    UnloadImage(target);
#else
    unsigned char* dst = &texData[(gx + padding) + (gy + padding) * stride];
    //unsigned char* pp = (unsigned char*)img.data;
    unsigned int pos = 0;
    for (unsigned int y = 0; y < gh; y++) {
        for (unsigned int x = 0; x < gw; x++) {
            dst[x + (y * stride)] = src[pos++];
        }
    }
    dst = &texData[gx + gy * width];
    gw += padding * 2;
    gh += padding * 2;


#ifdef USE_SDF
    size_t bytes = gw * gh * sizeof(float) * 3;
    if (tmp_buffer.size() < bytes) {
        printf("realloc: %d", (int)bytes);
        tmp_buffer.resize(bytes);
    }

    sdfBuildDistanceFieldNoAlloc(dst, width, 3,
        dst,
        gw, gh, width,
        &tmp_buffer[0]);
#endif

    dirtyRect[0] = std::min(dirtyRect[0], gx);
    dirtyRect[1] = std::min(dirtyRect[1], gy);
    dirtyRect[2] = std::max(dirtyRect[2], uint16_t(gx + gw));
    dirtyRect[3] = std::max(dirtyRect[3], uint16_t(gy + gh));
#endif
    glyphTextureAtlas.dirty = true;

}

void vbAlfonsFontManager::freeTextureData()
{
    //FIXME finish the unloading logic
    // remove logically the elements
    glyphTextureAtlas.texData.clear();
    // release the memory
    glyphTextureAtlas.texData.shrink_to_fit();
    //UnloadTexture(this->atlasTexture);
}


vbTextbox::vbTextbox():
    batchTextRenderer(vbAlfonsFontManager::getAlfonsFontManager().getAtlas(), *this)
{
}

vbTextbox::vbTextbox(const vbString& seltext, Vector2 pos, Color colour, BOOL isDictionary, vbString fontName, WORD layer, std::string name):
    batchTextRenderer(vbAlfonsFontManager::getAlfonsFontManager().getAtlas(), *this)
{
    this->init(seltext, pos.x, pos.y, colour, isDictionary, fontName, layer, name);
}

vbTextbox::vbTextbox(const vbString& seltext, FLOAT posx, FLOAT posy, Color colour, BOOL isDictionary, vbString fontName, WORD layer, std::string name):
    batchTextRenderer(vbAlfonsFontManager::getAlfonsFontManager().getAtlas(), *this)
{
    this->init(seltext, posx, posy, colour, isDictionary, fontName, layer, name);
}

void vbTextbox::init(const vbString& seltext, FLOAT posx, FLOAT posy, Color colour, BOOL isDictionary, vbString fontName, WORD layer, std::string name)
{
    this->type = TYPE_TEXT;
    this->setLayer(layer);
    Vector2 pos = { (float)posx, (float)posy };
    this->setFont(fontName);
    this->position = pos;
    this->colour = colour;
    this->isDictionaryText = isDictionary;
    this->fitMode = fitToBoundingBox::SHRINK_TO_FIT;
    this->verticalAlignment = verticalAlignmentText::ALIGN_CENTER;
    this->horizontalAlignment = horizontalAlignmentText::ALIGN_CENTER;
    this->regPointRule = transformRegRule::REG_TOP_LEFT; //FIXME (list 3)
    this->setText(seltext);
    this->dirty_ = TRUE;
}

void vbTextbox::setFont(vbString fontname)
{
    if (pGAME->language->getFont(fontname.c_str()) == NULL)
        fontname = "default";
    this->fontUse = fontname;
    this->dirty_ = TRUE;
}

void vbTextbox::setBoundingBox(float _width, float _height)
{
    if (_width < 0) {
        _width = 0;
    }
    if (_height < 0) {
        _height = 0;
    }
    if ((_width >= 0) && (_height >= 0) && ((this->boundingBox.x != _width) || (this->boundingBox.y != _height))) {
        this->boundingBox = { _width, _height };
        this->width = _width;
        this->height = _height;
        setDirty();
    }
}

Vector2 vbTextbox::getBoundingBox()
{
    return this->boundingBox;
}

vbString vbTextbox::getDictionaryText(vbString dictionaryText)
{
    vbString txtnew = "";

    if (pGAME->language != NULL)
    {
        this->lastLang = pGAME->language;
        this->dictionaryText = dictionaryText;
        vbString found = this->lastLang->get(dictionaryText);
        if (found == "")
            txtnew = "#" + dictionaryText + "#";
        else
            txtnew = found;
    }
    else
        txtnew = "#" + dictionaryText + "#";
    return txtnew;
}

void vbTextbox::setText(vbString toset, vbString _appendText)
{
    vbString txtnew = "";
    if (this->isDictionaryText)
    {
        txtnew = getDictionaryText(toset);
    }
    else
        txtnew = toset;

    this->appendText = _appendText;
    if (_appendText != "") {
        txtnew += _appendText;
    }
    
    if (!TextIsEqual(txtnew.c_str(), this->text.c_str()))
    {
        this->text = txtnew;
        this->setDirty();
        if (this->useCache)
            this->doLayout();
    }
}

vbString vbTextbox::getText()
{
    if (this->lastLang == NULL)
        this->lastLang = pGAME->language;

    if (this->isDictionaryText)
    {
        if (this->lastLang != pGAME->language)
        {
            this->lastLang = pGAME->language;
            this->setText(this->dictionaryText, this->appendText);
        }
    }
    return this->text;
}

void vbTextbox::setDirty()
{
    dirty_ = true;
}

void vbTextbox::doLayout()
{
    if (!dirty_ || (width <= 0) || (height <= 0))
        return;
    dirty_ = false;
    lineLayout = vbAlfonsFontManager::getAlfonsFontManager().shapeText(this->text, pGAME->language->getFont(this->fontUse.c_str()));

    glm::vec2 offset(0, 0);
    float renderWidth = width;
    if (!wrapText) {
        renderWidth = std::numeric_limits<float>::infinity();
    }
    textHeight = 0;
    if (fitMode == fitToBoundingBox::NONE) {
        lineLayout.setScale(1);
    }
    else {
        lineLayout.setScale(0.5);
    }
    textLines.clear();
    textHeight = batchTextRenderer.draw(lineLayout, offset, renderWidth).y - minY;
    if (fitMode != fitToBoundingBox::NONE) {
        float lastGoodScale = 0;
        float firstBadScale = -1;
        const int iterationCount = 10;
        //printf("start\r\n");
        for (int iteration = 0; (iteration < iterationCount) && (fabsf(lastGoodScale - firstBadScale) > fillPrecision); ++iteration)
        {
            if (textHeight < height) {
                lastGoodScale = lineLayout.scale();
                if (firstBadScale < 0) {
                    float newScale = lineLayout.scale() * 2;
                    if ((fitMode == fitToBoundingBox::SHRINK_TO_FIT) && (newScale > 1)) {
                        newScale = 1;
                    }
                    lineLayout.setScale(newScale);
                }
                else {
                    lineLayout.setScale((lastGoodScale + firstBadScale) / 2);
                }
            }
            else {
                firstBadScale = lineLayout.scale();
                lineLayout.setScale((lastGoodScale + firstBadScale) / 2);
            }
            //printf("lG: %4.2f fB: %4.2f tH: %4.2f h: %4.2d\r\n", lastGoodScale, firstBadScale, textHeight, height);
            textLines.clear();
            textHeight = batchTextRenderer.draw(lineLayout, offset, renderWidth).y - minY;
        }
        if (lineLayout.scale() != lastGoodScale) {
            lineLayout.setScale(lastGoodScale);
            textLines.clear();
            textHeight = batchTextRenderer.draw(lineLayout, offset, renderWidth).y - minY;
        }
    }

    if (this->useCache == TRUE)
        this->CacheText();
}

void vbTextbox::CacheText()
{
    // not yet implemented
}


void vbTextbox::drawVertices(std::vector<Texture2D> texture, QuadBatch& quads, float initialx, float initialy)
{
    for (uint32_t idx = 0; idx < quads.rectDest.size(); ++idx)  {
        Rectangle dest = quads.rectDest[idx];
        dest.x += initialx;
        dest.y += initialy;
        DrawTexturePro(texture[quads.atlasTarget[idx]], quads.rectSource[idx], dest, { 0, 0 }, 0, this->colour);
        // Debug - draw the boxes for the fonts
        //DrawRectangleLinesEx({ dest.x, dest.y, dest.width, dest.height}, 1, RED);
    }
}

void vbTextbox::draw(float initialx, float initialy)
{
    doLayout();
    if ((width <= 0) || (height <= 0))
        return;

    vbAlfonsFontManager& fontMan = vbAlfonsFontManager::getAlfonsFontManager();
#ifdef TEXT_USE_SHADER
    fontMan.loadTextureAtlas();
#endif // !

    float verticalAlignmentOffset = 0;
    switch (verticalAlignment) {
    case verticalAlignmentText::ALIGN_TOP:
        verticalAlignmentOffset = lineLayout.height();
        break;
    case verticalAlignmentText::ALIGN_CENTER:
        verticalAlignmentOffset = (height - textHeight) / 2 + lineLayout.ascent();
        break;
    case verticalAlignmentText::ALIGN_BOTTOM:
        verticalAlignmentOffset = height - textHeight + lineLayout.ascent();
    default:
        break;
    }
 
    //BeginScissorMode(initialx, initialy, width, height); //FIXME bounding box scissoring with cache
    for (int lineIndex = 0; lineIndex < textLines.size(); ++lineIndex) {
        float lineWidth = textLines[lineIndex].boundingX2 - textLines[lineIndex].boundingX1;
        float horizontalAlignmentOffset = 0;
        switch (horizontalAlignment) {
        case horizontalAlignmentText::ALIGN_RIGHT:
            horizontalAlignmentOffset = width - lineWidth;
            break;
        case horizontalAlignmentText::ALIGN_CENTER:
            horizontalAlignmentOffset = (width - lineWidth) / 2;
            break;
        case horizontalAlignmentText::ALIGN_LEFT:
        default:
            break;
        }
        drawVertices(fontMan.getAtlasTexture(), textLines[lineIndex], initialx + horizontalAlignmentOffset,
            initialy + verticalAlignmentOffset);
        // Debug
        //DrawRectangleLines(textLines[lineIndex].boundingX1 + initialx + horizontalAlignmentOffset, 
        //    textLines[lineIndex].boundingY1 + initialy + verticalAlignmentOffset,
        //    textLines[lineIndex].boundingX2 - textLines[lineIndex].boundingX1,
        //    textLines[lineIndex].boundingY2 - textLines[lineIndex].boundingY1,RED);
    }
    //EndScissorMode();
}

void vbTextbox::drawGlyph(const alfons::Quad& quad, const alfons::AtlasGlyph& glyph, bool newLine)
{
    printf("SHOULD NOT BE HERE, QUAD CALL!\r\n");
    for (;;);
}

void vbTextbox::drawGlyph(const alfons::Rect& rect, const alfons::AtlasGlyph& glyph, bool newLine)
{
//    printf("drawGlyph");
    if (newLine) {
        textLines.push_back(QuadBatch());
    }
    bool bad = false;
    if (!textLines.empty()) {
        textLines.back().add(rect, *glyph.glyph, glyph.atlas);
    }
    //DrawRectangleLinesEx({ rect.x1, rect.y1, rect.x2 - rect.x1, rect.y2 - rect.y1 }, 1, GREEN);
}

void vbTextbox::setCacheFlag(BOOL cacheON)
{
    if (cacheON == TRUE && this->useCache == false)
        this->CacheText();
    else if (cacheON == FALSE)
    {
        UnloadTexture(this->cachetxt);
        this->cachetxt.id = 0;
    }

    this->useCache = cacheON;
}

BOOL vbTextbox::getCacheFlag()
{
    return this->useCache;
}

Texture2D vbTextbox::getCacheTexture()
{
    return this->cachetxt;
}