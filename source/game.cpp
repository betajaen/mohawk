#include <exec/types.h>
#include <intuition/intuition.h>
#include <intuition/screens.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <cybergraphx/cybergraphics.h>

#include "game.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 512
#define SCREEN_DEPTH  24

#define GAME_WIDTH 544
#define GAME_HEIGHT 333

namespace Mohawk
{
	Game::Game()
		: mScreen(NULL),
		  mWindow(NULL)
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
	}

	bool Game::Setup()
	{

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
			WA_Borderless, FALSE,
			WA_DragBar, FALSE,
			WA_Activate, TRUE,
			WA_SimpleRefresh, TRUE,
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
		SetAPen(&mRastPort, 1);
		Move(&mRastPort, 100, 100);
		Draw(&mRastPort, 200, 150);

		Delay(500);
	}

}