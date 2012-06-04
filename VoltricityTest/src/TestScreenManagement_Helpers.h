#ifndef TestScreenManagement_Helpers_h__
#define TestScreenManagement_Helpers_h__

#include "ScreenManager.h"
#include "VoltricityScreenFactory.h"
#include "SFML/Graphics.hpp"

namespace testScreen {


	class TestScreen : public game::Screen {

	protected:

		virtual void handleEvent(const sf::Event& e) {}
		virtual void update() {}
		virtual void present() {}

		virtual int onInit() {
			return EXIT_SUCCESS;
		}

	};


	class TestScreenFactory : public game::ScreenFactory {

	protected:
		game::Screen* DoCreate(const std::string& screenId) {
			game::Screen* newScreen = 0;

			if (screenId == "Test")
				newScreen = new TestScreen();

			return newScreen;
		}


	};

}
#endif // TestScreenManagement_Helpers_h__
