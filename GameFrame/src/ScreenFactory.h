#ifndef ScreenFactory_h__
#define ScreenFactory_h__

#include "Screen.h"

namespace game {

class ScreenFactory {

protected:
	virtual Screen* DoCreate(const std::string& screenId) = 0;

public:
	Screen* CreateScreen(const std::string& screenId) {
		game::Screen* newScreen = 0;
		
		newScreen = DoCreate(screenId);

		if (newScreen != 0) {
			newScreen->SetScreenId(screenId);
		}

		return newScreen;
	}

};


}

#endif // ScreenFactory_h__
