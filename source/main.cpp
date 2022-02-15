#include <proto/exec.h>
#include <proto/dos.h>

void mohawk();

struct Library* CyberGfxBase = NULL;

static void libs_init()
{
	CyberGfxBase = OpenLibrary("cybergraphics.library", 41);
	if (!CyberGfxBase) {
		PutStr("ERROR: can`t open cybergraphics.library V41.\n");
	}
}


static void libs_cleanup()
{
	if (CyberGfxBase) {
		CloseLibrary(CyberGfxBase);
	}
}


int main(int argc, char** argv)
{
	libs_init();
	mohawk();
	libs_cleanup();
}
