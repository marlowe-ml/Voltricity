#ifndef VoltricityScreenFactory_h__
#define VoltricityScreenFactory_h__

#include "Screen.h"
#include "ScreenFactory.h"
#include "GameScreen.h"
#include "AboutScreen.h"
#include "HighscoreScreen.h"

namespace volt {

	class VoltricityScreenFactory : public game::ScreenFactory {

	protected:
		game::Screen* DoCreate(const std::string& screenId) {

			if (screenId == "Game")
				return new GameScreen();

			if (screenId == "About")
				return new AboutScreen();

			if (screenId == "Highscore")
				return new HighscoreScreen();



			return NULL;
		}


	};

}

#endif // VoltricityScreenFactory_h__
