#include <exec/types.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <proto/datatypes.h>

#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <cybergraphx/cybergraphics.h>

#include <datatypes/datatypes.h>
#include <datatypes/datatypesclass.h>
#include <datatypes/pictureclass.h>
#include <graphics/gfx.h>
#include <graphics/scale.h>
#include <graphics/displayinfo.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>

#include <string.h>

#include "game.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 512
#define SCREEN_DEPTH  24

#define GAME_WIDTH 544
#define GAME_HEIGHT 333

STATIC const ULONG COPY_CHAR = 0x16c04e75; /* move.b d0,(a3)+ ; rts */

namespace Mohawk
{
	Game::Game()
		: mScreen(NULL),
		  mWindow(NULL),
		  mIsRunning(true)
	{
	}

	Game::~Game()
	{
		if (mScreenBuffer && mScreen)
		{
			FreeScreenBuffer(mScreen, mScreenBuffer);
			mScreenBuffer = NULL;
		}

		if (mWindow)
		{
			CloseWindow(mWindow);
			mWindow = NULL;
		}

		if (mScreen)
		{
			CloseScreen(mScreen);
			mScreen = NULL;
		}

		PrintF("Game Stopped.\n");
	}

	bool Game::Setup()
	{
		mOutput = Output();

		ULONG modeId = BestCModeIDTags(
			CYBRBIDTG_NominalWidth, SCREEN_WIDTH,
			CYBRBIDTG_NominalHeight, SCREEN_HEIGHT,
			CYBRBIDTG_Depth, SCREEN_DEPTH,
			TAG_DONE
		);

		if (modeId == INVALID_ID)
		{
			PutStr("Invalid Mode ID!");
			return 1;
		}

		mScreen = OpenScreenTags(NULL,
			SA_DisplayID, modeId,
			SA_Left, 0,
			SA_Top, 0,
			SA_Width, SCREEN_WIDTH,
			SA_Height, SCREEN_HEIGHT,
			SA_Depth, SCREEN_DEPTH,
			SA_Title, (ULONG) "Mohawk",
			SA_Type, CUSTOMSCREEN,
			SA_SysFont, 1,
			TAG_DONE
		);

		if (mScreen == NULL)
		{
			return false;
		}
		
		PrintF("Screen Opened Size = %ldx%ld, Depth = %ld, ModeID = %lx\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, modeId);

		mScreenBuffer = AllocScreenBuffer(
			mScreen,
			NULL,
			SB_SCREEN_BITMAP
		);

		if (mScreenBuffer == NULL)
		{
			return false;
		}

		InitRastPort(&mRastPort);
		mRastPort.BitMap = mScreenBuffer->sb_BitMap;

		mWindow = OpenWindowTags(NULL,
			WA_Left, 0,
			WA_Top, 0,
			WA_Width, SCREEN_WIDTH,
			WA_Height, SCREEN_HEIGHT,
			WA_CustomScreen, (ULONG)mScreen,
			WA_Backdrop, TRUE,
			WA_Borderless, TRUE,
			WA_DragBar, FALSE,
			WA_Activate, TRUE,
			WA_SimpleRefresh, TRUE,
			WA_CloseGadget, FALSE,
			WA_DepthGadget, FALSE,
			WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY |IDCMP_IDCMPUPDATE,
			TAG_END
		);

		if (mWindow == NULL)
		{
			return false;
		}

		return true;
	}

	void Game::Run()
	{

		PasteImageFromFile("myst/4137.PICT");

		InputLoop();
	}

	void Game::InputLoop()
	{
		int timer = 0;

		while (mIsRunning)
		{
			ULONG signal = Wait((1 << mWindow->UserPort->mp_SigBit) | SIGBREAKF_CTRL_C);

			if (signal & SIGBREAKF_CTRL_C)
			{
				mIsRunning = false;
			}

			struct IntuiMessage* msg;

			while (true)
			{
				msg = (struct IntuiMessage*)GetMsg(mWindow->UserPort);

				if (msg == NULL)
					break;

				struct TagItem* tstate, * tag, * tags;
				ULONG tiData;

				switch (msg->Class)
				{
				case IDCMP_CLOSEWINDOW:
					mIsRunning = false;
					break;
				case IDCMP_VANILLAKEY:

					if (msg->Code == 27)
						mIsRunning = false;
					break;
				}

				ReplyMsg((struct Message*)msg);

				// General activity line
				SetAPen(&mRastPort, 1);
				Move(&mRastPort, 10, 10);

				int x = timer & 0xFF;
				timer += 892332;
				int y = timer & 0xFF;
				timer += 23881;
				Draw(&mRastPort, x, y);
			}

		}
	}

	void Game::PrintF(const char* fmt, ...)
	{
		return;

		unsigned char buf[256];
		STRPTR* arg = (STRPTR*)(&fmt + 1);
		RawDoFmt((STRPTR)fmt, arg, (void (*)()) &COPY_CHAR, buf);
		Write(mOutput, buf, strlen((char*)buf));
	}

	void Game::PasteImageFromFile(const char* path)
	{
		Object* dtObj = NewDTObject(
			(APTR) path,
			DTA_SourceType, DTST_FILE,
			DTA_GroupID, GID_PICTURE,
			TAG_DONE
			);

		if (dtObj == NULL)
		{
			PrintF("Could not open image %s!\n", path);
			return;
		}

		struct BitMapHeader* bmhd;
		UWORD width, height;
		UBYTE depth;

		if (GetDTAttrs(dtObj,
			PDTA_BitMapHeader, (ULONG) & bmhd,
			TAG_END))
		{
			width = bmhd->bmh_Width;
			height = bmhd->bmh_Height;
		}

		PrintF("Load DataType %s as %lx, Size = %ld x %ld, Depth = %ld\n", path, dtObj, (ULONG) width, (ULONG) height, (ULONG) depth);

		struct BitMap* dtBitmap;

		GetDTAttrs(dtObj,
			PDTA_DestBitMap, (ULONG) &dtBitmap,
			TAG_END);

		PrintF("Got Bitmap $%lx\n", dtBitmap);

		BltBitMapRastPort(dtBitmap, 0, 0,
			&mRastPort, SCREEN_WIDTH / 2 - width / 2, SCREEN_HEIGHT / 2 - height / 2,
			width, height, 0xFF);

		DisposeDTObject(dtObj);
	}

}