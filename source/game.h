#ifndef GAME_H
#define GAME_H

#include <exec/types.h>
#include <proto/intuition.h>
#include <proto/graphics.h>
#include <proto/datatypes.h>

namespace Mohawk
{
	class Game
	{
	public:

		Game();
		~Game();

		bool Setup();
		void Run();

		void PrintF(const char* fmt, ...);
		void PasteImageFromFile(const char* path);

	private:

		void InputLoop();

		bool mIsRunning;
		BPTR  mOutput;
		struct Screen* mScreen;
		struct Window* mWindow;
		struct ScreenBuffer* mScreenBuffer;
		struct RastPort mRastPort;

	};
}

#endif
