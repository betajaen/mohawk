#include <proto/exec.h>
#include <proto/dos.h>

#include "game.h"
#include "crt.h"

struct Library* CyberGfxBase = NULL;

static bool libs_init()
{
	CyberGfxBase = OpenLibrary("cybergraphics.library", 41);
	if (!CyberGfxBase) {
		PutStr("ERROR: can`t open cybergraphics.library V41.\n");
		return false;
	}

	return true;
}


static void libs_cleanup()
{
	if (CyberGfxBase) {
		CloseLibrary(CyberGfxBase);
	}
}


int main(int argc, char** argv)
{
	using namespace Mohawk;

	if (libs_init())
	{
		AllocateSharedStringMemory();
		
		Game game;

		if (game.Setup())
		{
			game.Run();
		}

		ReleaseSharedStringMemory();
	}

	libs_cleanup();
}
