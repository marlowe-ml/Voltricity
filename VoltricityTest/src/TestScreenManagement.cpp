#include <UnitTest++.h>
#include "TestScreenManagement_Helpers.h"
#include "VoltricityScreenFactory.h"

using namespace testScreen;

class ScreenFixture {
public:
	ScreenFixture() : App(sf::RenderWindow(sf::VideoMode(800,600,32), "TestWindow")) {		
		ScreenFactoryImpl = new TestScreenFactory();
		game::ScreenManager::Init(App, *ScreenFactoryImpl);
	}
	
	~ScreenFixture() {
		game::ScreenManager::Cleanup();
		delete ScreenFactoryImpl;
	}

	TestScreenFactory* ScreenFactoryImpl;
	sf::RenderWindow App;
};



TEST_FIXTURE(ScreenFixture, ScreenActivates) {
	CHECK(game::ScreenManager::ActivateScreen("Test"));
}

TEST_FIXTURE(ScreenFixture, CannotRunWithNoScreen) {
	game::ScreenManager::Cleanup();
	CHECK( ! game::ScreenManager::RunActiveScreen(0));
}

TEST_FIXTURE(ScreenFixture, ActiveScreenCanRun) {
	game::ScreenManager::Cleanup();
	game::ScreenManager::ActivateScreen("Test");
	CHECK(game::ScreenManager::RunActiveScreen(0));
}

TEST_FIXTURE(ScreenFixture, NoScreensLeftAfterCleanup) {
	game::ScreenManager::Cleanup();
	CHECK(game::ScreenManager::GetScreenCount() == 0);
	game::ScreenManager::ActivateScreen("Test");
	game::ScreenManager::RunActiveScreen(0);
	CHECK(game::ScreenManager::GetScreenCount() == 1);
	game::ScreenManager::Cleanup();
	CHECK(game::ScreenManager::GetScreenCount() == 0);
}
