#ifndef Highscore_h__
#define Highscore_h__

#include <string>
#include <iostream>
#include <fstream>


namespace volt {

class Highscore {
	public:

		Highscore(long points, std::string name) : Points(points), Name(name) {}

		long Points;
		std::string Name;

		
		std::ostream& Highscore::Serialize(std::ostream &out) const;
		std::istream& Highscore::Deserialize(std::istream &in);


	friend std::ostream &operator<<(std::ostream& out, const volt::Highscore &obj)
	{obj.Serialize(out); return out;}

	friend std::istream &operator>>(std::istream& in, volt::Highscore &obj)
	{obj.Deserialize(in); return in;}


};

}



#endif	// Highscore_h__
