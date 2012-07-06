#include "Utils.h"
#include <iostream>
#include <sstream>

using namespace game;

std::string Utils::IntToStr(int val) {
	std::stringstream ss;
	std::string s;
	ss << val;
	return ss.str();
}