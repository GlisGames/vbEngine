#ifndef vbSequence_H
#define vbSequence_H

#include "basetypes.h"

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
	WORD frameCounter = 0;
public:
	virtual void vbSequence::setup();
	virtual void vbSequence::update();
	virtual void vbSequence::draw();
	WORD actualIndex;
	BOOL enabled = TRUE;
	seqRepeatType repeat = seqRepeatType::REP_BEGINTOEND;
	Texture2Dvector *seqList;
	vbSequence();
	vbSequence(Texture2Dvector *slist, Vector2 pos, WORD frameFrequency = 1, std::string name = "", WORD layer = 0);
	void startAnim(seqRepeatType rep = seqRepeatType::REP_BEGINTOEND, WORD frameFrequency = 1);
	void resetAnim();
	void stopAnim();
	void stepAnim();
	bool isFinshed();
};

// vbSequenceMap
class vbSequenceMap : public std::map<std::string, Texture2Dvector*>
{
public:
	Texture2Dvector* operator [](std::string str);
};
#endif