#include "vbEngine.h"
#include "rlgl.h"
#include <vector>
#include <queue>

//#define DEBUG_BOX_ALL
BOOL clickDone = FALSE;
double previousFrameMillis = 0;

void _recursiveUpdate(vbContainer* c, BOOL visible, uint64_t timeSinceLastFrame = 0)
{

}

void _recursiveRender(vbContainer* c)
{

}
uint64_t prevtime = 0;
void vbRender_updateWorld(vbContainer* worldcanvas)
{

}

void vbRender_renderWorld(vbContainer* worldcanvas)
{
	_recursiveRender(worldcanvas);
}

void vbRender_init()
{

}
