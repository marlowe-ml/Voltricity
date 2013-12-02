#ifndef InputField_h__
#define InputField_h__

#include "Label.h"

namespace game {

class InputField : public Label {
public:
	InputField(int maxLength);
	std::string GetText();
	void HandleEvent(const sf::Event& e);
private:
	int _maxLength;
};

}

#endif //InputField_h__
