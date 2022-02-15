#include <exec/types.h>
#include <intuition/intuition.h>
#include <intuition/screens.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <cybergraphx/cybergraphics.h>

#define WIDTH  640
#define HEIGHT 512
#define DEPTH  8

int mohawk()
{
	ULONG modeId = BestCModeIDTags(
		CYBRBIDTG_NominalWidth, WIDTH,
		CYBRBIDTG_NominalHeight, HEIGHT,
		CYBRBIDTG_Depth, DEPTH,
		TAG_DONE
	);

	if (modeId == INVALID_ID)
	{
		PutStr("Invalid Mode ID!");
		return 1;
	}

	struct Screen* screen = OpenScreenTags(NULL,
		SA_DisplayID, modeId,
		SA_Left, 0,
		SA_Top, 0,
		SA_Width, WIDTH,
		SA_Height, HEIGHT,
		SA_Depth, DEPTH,
		SA_Title, (unsigned int)"Mohawk",
		SA_Type, PUBLICSCREEN,
		SA_SysFont, 1,
		TAG_DONE
	);

	Delay(500);

	if (screen)
	{
		CloseScreen(screen);
		screen = NULL;
	}
}
