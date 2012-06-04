#ifndef VoltricityScreenFactory_h__
#define VoltricityScreenFactory_h__

#include "Screen.h"
#include "ScreenFactory.h"
#include "GameScreen.h"

namespace volt {

	class VoltricityScreenFactory : public game::ScreenFactory {

	protected:
		game::Screen* DoCreate(const std::string& screenId) {
			game::Screen* newScreen = 0;

			if (screenId == "Game")
				newScreen = new GameScreen();

			return newScreen;
		}


	};

}

#endif // VoltricityScreenFactory_h__
