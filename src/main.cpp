#include <psp2/kernel/processmgr.h>
#include "game.h"
#include "screen.h"
int main()
{
	Screen screen;
	screen.StartScreen();

	Game gm;
	gm.StartGame();

	sceKernelExitProcess(0);
	return 0;
}
