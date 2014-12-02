#include <3ds.h>
#include "gfx.h"
#include "Block.h"

Block block[16];

int main()
{
	// Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	for (int i=0;i < 15;i++){
		block[i].setID(i);
	}
	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		gspWaitForEvent(GSPEVENT_VBlank0, false);
	}

	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
