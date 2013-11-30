#ifndef Highscore_h__
#define Highscore_h__

#include <string>

class Highscore {
	public:

		Highscore(long points, std::string name) : Points(points), Name(name) {}

		long Points;
		std::string Name;
};


#endif	// Highscore_h__
