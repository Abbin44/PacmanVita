#include <psp2/kernel/processmgr.h>
#include "screen.h"
#include "game.h"
int main()
{
	Screen screen;
	screen.StartScreen();

	while(true)
	{
			Game gm;
			gm.StartGame();
			screen.EndScreen(gm.score);
	}

	sceKernelExitProcess(0);
	return 0;
}
