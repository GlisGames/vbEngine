#ifndef TEXTBOXALFONS_H
#define TEXTBOXALFONS_H
#include "basetypes.h"
#include "vbGraphicObject.h"
#include <alfons/lineLayout.h>
#include <alfons/alfons.h>
#include <alfons/atlas.h>
#include <alfons/textBatch.h>
#include <alfons/font.h>
#include <alfons/fontManager.h>
#include <alfons/inputSource.h>
#include <alfons/textShaper.h>
//#define USE_SDF

class vbLanguage; //forward declaration
class vbTextbox; //forward declaration

typedef std::shared_ptr<alfons::Font> FontPtr;

enum class fontSize
{
	VERYSMALL = 6,
	SMALL = 10,
	MEDIUMSMALL = 15,
	MEDIUM = 20,
	MEDIUMLARGE = 30,
	LARGE = 40,
	VERYLARGE = 80,
};

enum class horizontalAlignmentText
{
	ALIGN_LEFT = 0,
	ALIGN_CENTER = 1,
	ALIGN_RIGHT = 2
};

enum class verticalAlignmentText
{
	ALIGN_TOP = 0,
	ALIGN_CENTER = 1,
	ALIGN_BOTTOM = 2
};

enum class fitToBoundingBox
{
	NONE = 0, //no scaling
	SHRINK_TO_FIT = 1, //only scale down if the the text goes out from the bounding box
	BEST_FIT = 2 //always scale to fit exactly the bounding box
};

struct GlyphTextureAtlas {

	std::vector<unsigned char> texData;
	Image atlasImage;
	uint16_t width = 0;
	uint16_t height = 0;
	uint16_t dirtyRect[4] = { 0 };
	bool dirty = true;

	GlyphTextureAtlas();
	void resetAtlas();
};

struct QuadBatch {

	std::vector<unsigned char> texData;
	uint16_t width = 0;
	uint16_t height = 0;
	uint16_t dirtyRect[4] = { 0 };
	bool dirty = true;

	std::vector<Rectangle> rectDest;
	std::vector<Rectangle> rectSource;
	std::vector<alfons::AtlasID> atlasTarget;
	float boundingX1 = 0;
	float boundingY1 = 0;
	float boundingX2 = 0;
	float boundingY2 = 0;

	QuadBatch();
	void resetVertexData();
	// return number of quads
	int size() const;
	void add(const alfons::Rect& _rect, const alfons::Glyph& _glyph, const alfons::AtlasID _atlasID);
};

class vbAlfonsFontManager: public alfons::TextureCallback
{
public:
	static vbAlfonsFontManager& getAlfonsFontManager();

	FontPtr addFont(const char* fontname, const char* fontFile, float fontSize);
	bool addFontFace(const char* fontFile, float fontSize);
	alfons::GlyphAtlas& getAtlas() { return atlas; };
	alfons::LineLayout shapeText(vbString txt, FontPtr fnt);
	void loadTextureAtlas();
	const std::vector<Texture2D> getAtlasTexture() { return atlasTexture; };
	void freeTextureData();// Texts can not be changed after this!
	// Alfons callbacks
	virtual void addTexture(alfons::AtlasID id, uint16_t textureWidth, uint16_t textureHeight);
	virtual void addGlyph(alfons::AtlasID id, uint16_t gx, uint16_t gy, uint16_t gw, uint16_t gh,
		const unsigned char* src, uint16_t padding);
private:
	vbAlfonsFontManager();
	Texture2D loadTexture(GlyphTextureAtlas& batch);

	FontPtr font;

	// Singleton. Access using getAlfonsFontManager
	alfons::FontManager fontMan;
	// Global atlas with glyph data
	alfons::GlyphAtlas atlas;
	alfons::TextShaper shaper;
	GlyphTextureAtlas glyphTextureAtlas;
	std::vector<Texture2D> atlasTexture;

};

class vbTextbox : public vbGraphicObject, public alfons::MeshCallback
{
private:
	void CacheText();
	void setDirty();
	void drawVertices(std::vector<Texture2D> texture, QuadBatch& quads, float initialx, float initialy);

	Texture2D cachetxt = { 0 };
	bool dirty_ = true;
	vbString text;
	vbLanguage* lastLang = NULL;
	vbString dictionaryText = "";
	vbString appendText = "";
	bool useCache = FALSE;
	Vector2 boundingBox = { 0,0 };
	alfons::LineLayout lineLayout;

	alfons::TextBatch batchTextRenderer;

	std::vector<QuadBatch> textLines;
	// smallest generated Y coordinate in Alfons layout - used for vertical alignment
	float minY = 0;
	float textHeight = 0;
	vbString fontUse;

#ifdef USE_SDF
	std::vector<unsigned char> tmp_buffer;
#endif

protected:
public:
	vbTextbox();
	vbTextbox(const vbString& seltext, Vector2 pos, Color colour, BOOL isDictionary = FALSE, vbString fontName = "default", WORD layer = 0, std::string name = "");
	vbTextbox(const vbString& seltext, FLOAT posx, FLOAT posy, Color colour, BOOL isDictionary = FALSE, vbString fontName="default", WORD layer = 0, std::string name = "");
	void init(const vbString& seltext, FLOAT posx, FLOAT posy, Color colour, BOOL isDictionary = FALSE, vbString fontName="default", WORD layer = 0, std::string name = "");
	Texture2D getCacheTexture();
	void setCacheFlag(BOOL cacheON);
	BOOL getCacheFlag();
	//bool addFont(const char* fontname, const char* fontFile = "arial.ttf", float fontSize = 20);
	//bool addFontFace(const char* fontFile, float fontSize);
	// 
	//vector<float> centerCoords;
	//float getBoundingScale();
	//vector<WORD> getLineBreaks();
	//Vector2 getGlyphPrintSize(WORD i, float scale = 1.0f);
	void setFont(vbString fontName);
	void setBoundingBox(float width, float height);
	Vector2 getBoundingBox();
	BOOL useBoundingBox = FALSE;
	//float getMaxHeight();
	//Vector2 getPrintSize(BOOL multiline = FALSE);
	BOOL isDictionaryText = FALSE;
	//BYTE fontIndex = 0;
	horizontalAlignmentText horizontalAlignment = horizontalAlignmentText::ALIGN_CENTER;
	verticalAlignmentText verticalAlignment = verticalAlignmentText::ALIGN_CENTER;
	fitToBoundingBox fitMode = fitToBoundingBox::NONE;
	// A value of 0.2f gives already a good precision with fewer iterations, 
	// a value of 0.01 gives very good precistion with more iterations.
	float fillPrecision = 0.2f;
	bool wrapText = true;
	void setText(vbString toset, vbString appendText = "");
	vbString getDictionaryText(vbString dictionaryText);
	vbString getText();
	//vbFont* GetFont();
	//size_t GetGlyphCount();
	//void GetGlyph(size_t index, GlyphInfo& info);

	// Alfons callback interface
	virtual void drawGlyph(const alfons::Quad& quad, const alfons::AtlasGlyph& glyph, bool newLine);
	virtual void drawGlyph(const alfons::Rect& rect, const alfons::AtlasGlyph& glyph, bool newLine);

	void doLayout();
	void draw(float initialx, float initialy);

};

#endif