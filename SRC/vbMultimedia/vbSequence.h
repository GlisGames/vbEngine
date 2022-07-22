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
	void stepAnim(); // Legacy code
	void stepAnimByFrame(); // Frame based step

public:
	vbSequence();
	vbSequence(vbSpriteTexture2Dvector* slist, Vector2 pos, std::string name = "", WORD layer = 0);
	virtual void setup();
	virtual void update();
	virtual void draw();
	WORD actualIndex;
	BOOL enabled = FALSE;
	BOOL isTimeBased = TRUE;
	seqRepeatType repeat = seqRepeatType::REP_BEGINTOEND;
	vbSpriteTexture2Dvector* seqList;
	// This callback would be called once on every cycle
	// Can be used for synchronizing some external logics with this animation sequence
	std::function<void()> syncCallback = NULL;
	/// @param frameFrequency: Advance the animation every [frameFrequency] frames.
	void startAnimByFrame(WORD frameFrequency = 1, seqRepeatType rep = seqRepeatType::REP_BEGINTOEND);
	/// @param duration: Duration in milliseconds of the whole sequence
	void startAnimByTime(DWORD duration, seqRepeatType rep = seqRepeatType::REP_BEGINTOEND);
	void resetAnim();
	void stopAnim();
	bool isFinished();
	int getTotalFrames()
	{
		if (seqList) return seqList->size();
	}
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