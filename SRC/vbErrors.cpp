#include "vbEngine.h"

void PANIC(const char* message)
{
	while (true)
	{
		WaitTime(100);
		BeginDrawing();
		ClearBackground(RED);
		DrawText(TextFormat("ERROR, please refresh (F5) the page."), 50, 0, 40, BLACK);
		DrawText(message, 50, 50, 40, BLACK);
		EndDrawing();
	}
}