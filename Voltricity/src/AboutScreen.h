#ifndef AboutScreen_h__
#define AboutScreen_h__

#include "Screen.h"
#include "Label.h"
#include <SFML/Graphics.hpp>

namespace volt {
	class AboutScreen : public game::Screen {

	protected:
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	private:
		game::Label _labelAbout;

	};

}


#endif // AboutScreen_h__
