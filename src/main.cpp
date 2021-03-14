#include <psp2/kernel/processmgr.h>
#include "game.h"

int main()
{
	Game gm;
	gm.StartGame();

	sceKernelExitProcess(0);
	return 0;
}
