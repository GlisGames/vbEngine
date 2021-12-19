#include "vbEngine.h"

void PANIC(const char* message)
{
#ifdef PLATFORM_RASPBERRY
	while (true)
	{
		WaitTime(100);
		BeginDrawing();
		ClearBackground(RED);
		DrawText(TextFormat("ERROR"), 50, 0, 40, BLACK);
		DrawText(message, 50, 50, 40, BLACK);
		//DrawText(TextFormat("READ: % d", digitalRead(7)), 0, 50, 40, BLACK);
		//vbRender_printWorld(&GAME.mainGame);
		EndDrawing();
	}
#else
	TraceLog(LOG_ERROR, "\n PANIC: %s", message);
	exit(1);
#endif // PLATFORM_RASPBERRY
}