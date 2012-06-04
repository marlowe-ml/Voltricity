#include "Screen.h"
#include "ScreenManager.h"

using namespace game;

Screen::Screen() : _isTerminated(false), _isInitialized(false), _isInactive(false),
	_appTime(0), _appTimePrev(0), _activeScreenTime(0), _activeScreenTimePrev(0)
{}

Screen::~Screen() {
	if (!_isTerminated)
		Terminate();
}

int Screen::Run(unsigned long long newAppTime) {
	
	if (_isInactive) {
		// synch app time, since we have been inactive, this ensures gap-less screen time
		unsigned long long lastAppTimeDiff = _appTime - _appTimePrev;
		_appTime = newAppTime - lastAppTimeDiff;
 
		_isInactive = false;
	}

	_appTimePrev = _appTime;
	_appTime = newAppTime;

	if (_appTimePrev == 0)
		_appTimePrev = _appTime;

	_activeScreenTimePrev = _activeScreenTime;
	_activeScreenTime += _appTime - _appTimePrev;

	update();
	

	return EXIT_SUCCESS;
}

bool Screen::nextEvent(sf::Event& eventReceived) {
	if(_app->GetEvent(eventReceived)) {
		if (eventReceived.Type == sf::Event::Closed) {
			onCloseEvent();
			return false;
		}
		return true;
	} else {
		return false;
	}
}

void Screen::onCloseEvent() {
	Terminate();
	_app->Close();
}


void Screen::Render() {
	present();

	// todo: after render need to adjust last update time?
}

int Screen::Init(sf::RenderWindow& app) {
	_app = &app;
	if (onInit() == EXIT_SUCCESS) {
		_isInitialized = true;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

void Screen::SetInactive() {
	_isInactive = true;
}

void Screen::Terminate() {
	_isTerminated = true;
	onTerminate();
	ScreenManager::NotifyScreenTerminated(_screenId);
}

void Screen::onTerminate() {}

int Screen::onInit() {return EXIT_SUCCESS;}

void Screen::SetScreenId(const std::string& newScreenId) {
	_screenId = newScreenId;
}

const std::string& Screen::GetScreenId() const {
	return _screenId;
}
