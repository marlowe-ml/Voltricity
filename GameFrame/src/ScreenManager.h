#ifndef ScreenManager_h__
#define ScreenManager_h__

#include "Screen.h"
#include "Layout.h"
#include "ScreenFactory.h"
#include <SFML/Graphics.hpp>
#include <map>

namespace game {

	typedef std::map<std::string, Screen* > ScreenMap;

	class ScreenManager  {
	public:
		static void Init(sf::RenderWindow& app, ScreenFactory& factory);
		static bool ActivateScreen(const std::string& screenId);
		static bool RunActiveScreen(unsigned long long appTime);
		static bool RenderActiveScreen();
		static void NotifyScreenTerminated(const std::string& screenId);
		static void Cleanup();
		static unsigned int GetScreenCount();
		static const Layout& GetLayout();

	private:
		static sf::RenderWindow* _app;
		static ScreenFactory* _screenFactory;
		static Layout _screenLayout;

		static ScreenMap _screens;
		static Screen* _activeScreen;
		static bool _cleanupTerminatedScreens;

		static Screen* createScreen(const std::string& screenId);
		static void ScreenManager::cleanupTerminatedScreens();

		

	};
}

#endif // ScreenManager_h__