#ifndef GAME_H
#define GAME_H

#include <exec/types.h>

struct Screen;

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

	};
}

#endif
