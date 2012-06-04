#include "ScreenManager.h"

using namespace game;

sf::RenderWindow* ScreenManager::_app = 0;
ScreenMap ScreenManager::_screens;
Screen* ScreenManager::_activeScreen = 0;
Layout ScreenManager::_screenLayout;
bool ScreenManager::_cleanupTerminatedScreens = false;
ScreenFactory* ScreenManager::_screenFactory = 0;

void ScreenManager::Init(sf::RenderWindow& app, ScreenFactory& factory)  
{
	ScreenManager::_app = &app;
	ScreenManager::_screenFactory = &factory;
	ScreenManager::_screenLayout = Layout(sf::FloatRect(0,0,(float)app.GetWidth(),(float)app.GetHeight()));
}

const Layout& ScreenManager::GetLayout() {return _screenLayout;}

bool ScreenManager::ActivateScreen(const std::string& screenId) {
	ScreenMap::iterator it = _screens.find(screenId);

	Screen* screen = 0;

	if (it == _screens.end()) {
		screen = createScreen(screenId);
		_screens.insert(std::pair<std::string, Screen*>(screenId, screen));
	} else {
		screen = it->second;		
	}

	if (screen != 0)
	{
		if (screen!=_activeScreen && _activeScreen != NULL)
			_activeScreen->SetInactive();

		if (!screen->IsInitialized())
			screen->Init(*_app);

		_activeScreen = screen;
		return true;
	}

	return false;
}

bool ScreenManager::RunActiveScreen(unsigned long long appTime) {
	if (_cleanupTerminatedScreens)
		cleanupTerminatedScreens();

	if (_activeScreen == NULL || _activeScreen->IsTerminated())
		return false;

	_activeScreen->Run(appTime);
	return true;
}

bool ScreenManager::RenderActiveScreen() {
	if (_activeScreen == NULL || _activeScreen->IsTerminated())
		return false;

	_activeScreen->Render();
	return true;
}


Screen* ScreenManager::createScreen(const std::string& screenId) {
	return _screenFactory->CreateScreen(screenId);	
}


void ScreenManager::NotifyScreenTerminated(const std::string& screenId) {
	_cleanupTerminatedScreens = true;

	ScreenMap::iterator it = _screens.find(screenId);
	if (it!=_screens.end()) {
		if (_activeScreen != NULL && _activeScreen->GetScreenId() == screenId)
			_activeScreen = NULL;			
	}

}


void ScreenManager::Cleanup() {
	for (ScreenMap::iterator it = _screens.begin(); it!=_screens.end(); it++) {
		if (it->second != NULL && it->second->IsTerminated() == false)
			it->second->Terminate();

		delete it->second;
	}

	_screens.clear();
}

unsigned int ScreenManager::GetScreenCount() {
	return _screens.size();

}

void ScreenManager::cleanupTerminatedScreens() {

	ScreenMap::iterator it = _screens.begin();

	while (it!=_screens.end()) {
		if (it->second->IsTerminated()) {
			delete it->second;
			_screens.erase(it++);
		} else {
			it++;	
		}
	}

	_cleanupTerminatedScreens = false;
}
