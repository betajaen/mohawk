#ifndef GAME_H
#define GAME_H

#include <exec/types.h>
#include <proto/intuition.h>
#include <proto/graphics.h>

namespace Mohawk
{
	class Game
	{
	public:

		Game();
		~Game();

		bool Setup();
		void Run();

	private:

		struct Screen* mScreen;
		struct Window* mWindow;
		struct ScreenBuffer* mScreenBuffer;
		struct RastPort mRastPort;

	};
}

#endif
