#include "vbEngine.h"
#include "rlgl.h"
#include <vector>
#include <queue>

//#define DEBUG_BOX_ALL
BOOL clickDone = FALSE;
void _recursiveUpdate(vbContainer* c, BOOL visible)
{
	gObjectList* objList = NULL;
	objList = &c->gObjects;

	for (auto it = objList->rbegin(); it != objList->rend(); it++)
	{
		(*it)->setClick(FALSE);
		if ((*it)->type == TYPE_CONTAINER)
		{
			_recursiveUpdate((vbContainer*)(*it), ((*it)->visible && visible));
		}
		//else if ((*it)->type == TYPE_TEXT)
		//{
		//	vbTextbox* t = (vbTextbox*)(*it);
		//	if (t->getCacheFlag() && t->getCacheTexture().id == 0) //cache to be done
		//	{
		//		RenderTexture targetTxtCache = LoadRenderTexture(t->getBoundingBox().x, t->getBoundingBox().y); //create render target
		//		BeginTextureMode(targetTxtCache);
		//		ClearBackground(BLANK);  // Clear texture background
		//		t->draw(0,0);
		//		t->getCacheTexture
		//	}
		//}
		if (clickDone == FALSE && (*it)->visible && visible && (*it)->isClickable && IsMouseButtonPressed(0) && (*it)->isMouseOver())
		{
			(*it)->setClick(TRUE);
			clickDone = TRUE;
		}
		//Living object logic update
		if ((*it)->isAlive == TRUE && (*it)->enabled == TRUE)
			(*it)->update();

		if ((*it)->lupdate != NULL && (*it)->enabled == TRUE)
			(*it)->lupdate();

		//Tween logic update
		(*it)->tweens.stepAll();
		//Sequence logic update
		if ((*it)->type == TYPE_SEQUENCE) //if it's a sequence then step it
		{
			vbSequence* s = (vbSequence*)(*it);
			s->stepAnim();
		}
	}
}

void _recursiveRender(vbContainer* c)
{
	BOOL canvasToCache = FALSE;
	BOOL parentCache = FALSE;
	RenderTexture2D targetCache = { 0 };
	if (c->name == "cnvHbox")
		BREAKPOINT;
	c->gObjects.sortMe();
	//c->tweens.stepAll();
	Color finalColor = WHITE;
	WORD finalRotation = c->rotation;
	FLOAT finalZoom = c->zoom;
	Vector2 cacheBox = {0,0};
	Rectangle finalScissor = { c->getAbsolutePosition().x, c->getAbsolutePosition().y, (FLOAT)c->width, (FLOAT)c->height };
	if (c->width > 0 && c->height > 0)
	{
		vbContainer* pc = c->parentCanvas;
		while (pc != NULL)
		{
			//inherit transformation
			finalZoom *= pc->zoom;
			finalRotation += pc->rotation;
			if (pc->colour.a != 255 || pc->colour.r != 255 || pc->colour.g != 255 || pc->colour.b != 255)
				finalColor = colorApplyFilter(finalColor, pc->colour);
				//finalColor = ColorAlphaBlend(WHITE, finalColor, pc->colour);
			pc = pc->parentCanvas; //MAYBE TOFIX
		}
		// Scissoring
		Rectangle dest;
		if (c->regPointRule == transformRegRule::REG_CENTER)
			dest = { finalScissor.x + ((finalScissor.width * 0.5f) * (1.0f - finalZoom)), finalScissor.y + ((finalScissor.height * 0.5f) * (1.0f - finalZoom)), finalScissor.width * finalZoom, finalScissor.height * finalZoom };
		else
			dest = { finalScissor.x, finalScissor.y, finalScissor.width * finalZoom, finalScissor.height * finalZoom };
		finalScissor = dest;

		pc = c->parentCanvas;
		while (pc != NULL)
		{
			if (pc->getCacheFlag() == TRUE/* && pc->getCacheTexture().id != 0*/)
			{
				parentCache = TRUE;
				cacheBox = pc->getAbsolutePosition();
			}
			//inherit scissoring
			if (pc->scissor)// && pc->zoom == 1.0)
			{
				if (pc->scissorBox.x > finalScissor.x)
				{
					finalScissor.width -= (pc->scissorBox.x - finalScissor.x);
					finalScissor.x = pc->scissorBox.x;
				}
				if (pc->scissorBox.y > finalScissor.y)
				{
					finalScissor.height -= pc->scissorBox.y - finalScissor.y;
					finalScissor.y = pc->scissorBox.y;
				}

				if (pc->scissorBox.x + pc->scissorBox.width < finalScissor.x + finalScissor.width)
					finalScissor.width = (pc->scissorBox.x + pc->scissorBox.width) - finalScissor.x;
				if (pc->scissorBox.y + pc->scissorBox.height < finalScissor.y + finalScissor.height)
					finalScissor.height = (pc->scissorBox.y + pc->scissorBox.height) - finalScissor.y;
			}
			pc = pc->parentCanvas; //MAYBE TOFIX
		}
		//CHECK cache
		if (c->getCacheFlag() == TRUE && parentCache == FALSE) //if to be cached and not inside an already cached canvas
		{
			if (c->getCacheTexture().id == NULL) //new cache to do
			{
				targetCache = LoadRenderTexture(c->width, c->height); //create render target
				BeginTextureMode(targetCache);
				ClearBackground(BLANK);  // Clear texture background
				cacheBox = c->getAbsolutePosition();
				canvasToCache = TRUE;
			}
		}

		if ((c->width > 0 && c->height > 0) && (finalScissor.width <= 0 || finalScissor.height <= 0))
			return; //we're out of the box, stop to render this whole canvas

		if (c->scissor)// && (finalScissor.width != c->width || finalScissor.height != c->height || finalScissor.x != c->position.x || finalScissor.y != c->position.y))
		{
			//scale scissor
			c->scissorBox = finalScissor;

			BeginScissorMode(finalScissor.x, finalScissor.y, finalScissor.width, finalScissor.height); //it evetually overwrite precendent scissors areas
			//DrawRectangleLinesEx({ finalScissor.x, finalScissor.y, finalScissor.width, finalScissor.height }, 4, RED);
		}
		//if (c->scissor) //debug lines
		//{
		//	DrawRectangleLinesEx({ c->position.x, c->position.y, (float)c->width, (float)c->height }, 5, WHITE);
		//	DrawRectangleLinesEx({ finalScissor.x, finalScissor.y, finalScissor.width, finalScissor.height }, 2, RED);
		//}
		//else
		//	if (c->scissor)
		//	{
		//		DrawRectangleLinesEx({ c->position.x, c->position.y, (float)c->width, (float)c->height }, 5, BLACK);
		//		BeginScissorMode(c->position.x, c->position.y, (FLOAT)c->width, (FLOAT)c->height);
		//	}
	}
	else
	{
		return;
	}

	gObjectList cclist;
	gObjectList* objList = NULL;
	vbImage cachedanvas;

	// Check if object has Cache
	if (c->getCacheFlag() == TRUE && canvasToCache == FALSE)
	{
		cachedanvas = vbImage(&c->canvasCache, c->getAbsolutePosition());
		(vbGraphicObject)cachedanvas = (vbGraphicObject)(*c);
		cclist.push_back(&cachedanvas);
		objList = &cclist;
	}
	else
		objList = &c->gObjects;

	for (gObjectIndex it = objList->begin(); it != objList->end(); it++)
	{
		//Render
		if ((*it)->visible /*&& parentCache == FALSE*/) //if it's visible and not inside a cached canvas
		{
			vbGraphicObject* t = (vbGraphicObject*)(*it);
			Vector2 pos = t->getAbsolutePosition();
			pos.x -= cacheBox.x;
			pos.y -= cacheBox.y;
			//Living object render update (if any...)
			if (t->lrender != NULL)
			if (t->lrender != NULL && t->enabled)
				t->lrender();
			if (t->isAlive && t->enabled)
				t->render();
			Color destColor = t->colour;
			if (finalColor.a != 255 || finalColor.r != 255 || finalColor.g != 255 || finalColor.b != 255)
				destColor = colorApplyFilter(t->colour, finalColor);
				//destColor = ColorAlphaBlend(WHITE, t->colour, finalColor);
			switch ((*it)->type)
			{
			case TYPE_TEXT:
			{
				if (t->visible == TRUE)
				{
					vbTextbox* txt = (vbTextbox*)(*it);
					if (txt->getText().length() > 0 && txt->getText() != "")
					{
						// scale
						
						pGAME->textEngine.render.DrawTextBoundingAlfons(txt, pos.x, pos.y, destColor, txt->zoom* finalZoom, txt->rotation + finalRotation);
					}
				}
			}
			case TYPE_TEXTURE:
			case TYPE_SEQUENCE:
			//case TYPE_TEXT:
			{
				//TEXTURE RENDER
				if (t->visible == TRUE)
				{
					BOOL isCachedText = FALSE;
					vbImage cachedText;
					Texture2D tempTex;
					if ((*it)->type == TYPE_TEXT)
					{
						vbTextbox* txt = (vbTextbox*)(*it);
						if (txt->getCacheFlag() == TRUE)
						{
							isCachedText = TRUE;
							tempTex = txt->getCacheTexture(); //per emscripten
							cachedText = vbImage(&tempTex);
							(vbGraphicObject)cachedText = (vbGraphicObject)(*txt);
						}
					}

					if ((*it)->type == TYPE_TEXTURE || (*it)->type == TYPE_SEQUENCE || isCachedText == TRUE)
					{
						vbImage* tx;
						if (isCachedText)
							tx = &cachedText;
						else
							tx = (vbImage*)(*it);

						if (tx->getTexture() != NULL)
						{
							//DrawTextureEx(*tx->getTexture(), pos, (float)t->rotation, tozoom, t->colour);
							Vector2 origin;
							if (t->rotation != 0)
							{
								origin = { ((float)tx->width / 2.0f) * finalZoom, ((float)tx->height / 2.0f) * finalZoom };
								pos.x += (float)tx->width / 2.0f;
								pos.y += (float)tx->height / 2.0f;
							}
							else
								origin = { 0,0 };

							Rectangle source = { 0.0f, 0.0f, (float)tx->width, (float)tx->height };
							Rectangle dest;
							FLOAT imgZoom = t->zoom * finalZoom;
							if (t->regPointRule == transformRegRule::REG_CENTER)
								dest = { pos.x + (((float)tx->width * 0.5f) * (1.0f - imgZoom)), pos.y + (((float)tx->height * 0.5f) * (1.0f - imgZoom)), (float)tx->width * imgZoom, (float)tx->height * imgZoom };
							else
								dest = { pos.x, pos.y, (float)tx->width * imgZoom, (float)tx->height * imgZoom };
							if (t->name == "sym1_r0")
							{
								//printf("%.2f\n", dest.y);
 								BREAKPOINT;
							}
							if (isCachedText || c->getCacheFlag() == TRUE)
								source.height *= -1;
							//DrawTexturePro(*tx->getTexture(), source, dest, origin, t->rotation + finalRotation, t->colour);
							//scale
							DrawTexturePro(*tx->getTexture(), source, dest, origin, t->rotation + finalRotation, destColor);
#ifndef DEBUG_BOX_ALL
							if (t->debugBox == TRUE)
#endif // !DEBUG_BOX_ALL
								DrawRectangleLinesEx(dest, 1, RED);
						}
					}
				}
				break;
			}
			case TYPE_CONTAINER:
			{
				if (c->scissor)
					EndScissorMode();
				_recursiveRender((vbContainer*)(*it));

				if (c->scissor)
					//scale scissor
					BeginScissorMode(finalScissor.x, finalScissor.y, finalScissor.width, finalScissor.height);
				break;
			}
			}

		}
	}
	if (c->scissor)
		EndScissorMode();
#ifndef DEBUG_BOX_ALL
	if (c->width > 1 && c->height > 1 && c->debugBox)
#else
	if (c->width > 1 && c->height)
#endif
		DrawRectangleLinesEx({ finalScissor.x, finalScissor.y, finalScissor.width, finalScissor.height }, 2, RED);
	if (canvasToCache == TRUE)
	{
		if (c->getCacheTexture().id == NULL)
		{
			c->canvasCache = targetCache.texture;
			EndTextureMode();
		
			//UnloadRenderTexture(targetCache); //unload the rest
			//UnloadTexture(targetCache.depth);
			rlUnloadFramebuffer(targetCache.id);
			_recursiveRender(c); //call again to print the cached texture (we were inside texture mode)
		}
	}
}

void vbRender_printWorld(vbContainer* worldcanvas)
{
	_recursiveUpdate(worldcanvas, worldcanvas->visible);
	_recursiveRender(worldcanvas);
	clickDone = FALSE;
}

void vbRender_init()
{

}
