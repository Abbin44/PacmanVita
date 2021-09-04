#include <psp2/kernel/processmgr.h>
#include "screen.h"
#include "game.h"
int main()
{
	int score;
	Screen screen;
	screen.StartScreen();

	while(true)
	{
			Game gm;
			score = gm.StartGame();
			screen.EndScreen(score);
	}

	sceKernelExitProcess(0);
	return 0;
}
