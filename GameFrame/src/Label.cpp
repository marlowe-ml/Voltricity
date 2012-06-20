#include "Label.h"

using namespace game;

Label::Label() {}

Label::Label(const std::string& text) {
	_text.SetText(text);
}

void Label::Render(sf::RenderTarget& target) const {
	target.Draw(_text);
}

