#ifndef vbSequence_H
#define vbSequence_H

#include "basetypes.h"
#include "vbTexture.h"

enum class seqRepeatType
{
	REP_BEGINTOEND = 0,
	REP_YOYO = 1,
	REP_ONETIME = 2
};

class vbSequence : public vbImage
{
private:
	SWORD yoyoDirection = 0;
	WORD frameFreq = 1;
	QWORD frameCounter = 0;
public:
	virtual void setup();
	virtual void update();
	virtual void draw();
	WORD actualIndex;
	BOOL enabled = FALSE;
	BOOL isTimeBased = TRUE;
	seqRepeatType repeat = seqRepeatType::REP_BEGINTOEND;
	vbSpriteTexture2Dvector* seqList;
	vbSequence();
	vbSequence(vbSpriteTexture2Dvector*slist, Vector2 pos, WORD frameFrequency = 1, std::string name = "", WORD layer = 0);
	void startAnimByFrame(seqRepeatType rep = seqRepeatType::REP_BEGINTOEND, WORD frameFrequency = 1);
	void startAnimByTime(DWORD FPS = 60, seqRepeatType rep = seqRepeatType::REP_BEGINTOEND);
	void resetAnim();
	void stopAnim();
	void stepAnim();
	bool isFinshed();
};

// vbSequenceMap
//class vbSequenceMap : public std::map<std::string, Texture2Dvector*>
//{
//public:
//	Texture2Dvector* operator [](std::string str);
//};

class vbSequenceMap : public std::map<std::string, vbSpriteTexture2Dvector*>
{
public:
	vbSpriteTexture2Dvector* operator [](std::string str);
};
#endif