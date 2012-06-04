#include "Voltricity.h"
#include "ScreenFactory.h"
#include "ScreenManager.h"
#include "Clock.h"
#include "VoltricityScreenFactory.h"
#include "boost/scoped_ptr.hpp"

using namespace volt;
using namespace game;

Voltricity::Voltricity()
	:	_app(sf::RenderWindow(sf::VideoMode(800,600,32), "Voltricity"))
{

}

Voltricity::~Voltricity() {
}


void Voltricity::Run() {

	const int UPDATES_PER_SECOND = 25;
	const int TICKS_BETWEEN_UPDATES = 1000 / UPDATES_PER_SECOND;
	const int MAX_FRAME_RENDER_SKIP = 5;

	VoltricityScreenFactory screenFactory;
	ScreenManager::Init(_app, screenFactory);
	ScreenManager::ActivateScreen("Game");


	_clock.Restart();

	unsigned long long appTime = 0;
	unsigned long long nextUpdateTick = _clock.GetElapsedMicroSeconds();
	int loops;
	float interpolation;

	while (_app.IsOpened()) {

		loops = 0;
		// check if updates should be run, allow to skip rendering for defined number of frames if updates are running behind
		while ((appTime = _clock.GetElapsedMicroSeconds()) > nextUpdateTick && loops < MAX_FRAME_RENDER_SKIP) {			
			ScreenManager::RunActiveScreen(appTime);
			nextUpdateTick += TICKS_BETWEEN_UPDATES;
			loops++;
		}

		interpolation = (float)(_clock.GetElapsedMicroSeconds() + TICKS_BETWEEN_UPDATES - nextUpdateTick) / (float)TICKS_BETWEEN_UPDATES;

		_app.Clear();
		
		ScreenManager::RenderActiveScreen();
		if (_app.IsOpened())
			_app.Display();

		// todo: sleep longer depending on frame rate
		Sleep(1);

	}

	ScreenManager::Cleanup();

}