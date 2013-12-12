#include "Highscore.h"
#include <vector>

using namespace volt;


std::ostream& Highscore::Serialize(std::ostream &out) const {
    out << Points;
    out << ','; //number seperator
    out << Name.size(); //serialize size of string
    out << ','; //number seperator
    out << Name; //serialize characters of string
    return out;
}


std::istream& Highscore::Deserialize(std::istream &in) {
    if (in) {
        int len=0;
        char comma;
        in >> Points;
        in >> comma; //read in the seperator
        in >> len;  //deserialize size of string
        in >> comma; //read in the seperator
        if (in && len > 0) {
            std::vector<char> tmp(len);
            in.read(&tmp[0] , len); //deserialize characters of string
            Name.assign(&tmp[0], len);
        }
    }
    return in;
}

