#include "vbEngine.h"

void PANIC(const char* message)
{
	while (true)
	{
		pGAME->errorState = FALSE;
		WaitTime(100);
		BeginDrawing();
		ClearBackground(RED);
		DrawRectangle(0, 0, pGAME->gameResolution.x, pGAME->gameResolution.y, RED);
		DrawText(TextFormat("ERROR, please refresh (F5) the page."), 50, 0, 30, BLACK);
		DrawText(message, 50, 60, 40, BLACK);
		EndDrawing();
		//exit(1);
	}
}