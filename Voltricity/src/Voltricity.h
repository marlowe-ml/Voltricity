#ifndef Voltricity_h__
#define Voltricity_h__

#include <SFML/Graphics.hpp>
#include "Clock.h"

namespace volt {

class Voltricity {
	
public:
	Voltricity();
	virtual ~Voltricity();

	void Run();

private:
	sf::RenderWindow* _app;
	game::Clock _clock;

};

}


#endif // Voltricity_h__
