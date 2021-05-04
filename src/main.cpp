#include <psp2/kernel/processmgr.h>
#include "screen.h"
#include "game.h"
int main()
{
	Screen screen;
	screen.StartScreen();

	Game gm;
	gm.StartGame();

	sceKernelExitProcess(0);
	return 0;
}
