#include "Label.h"

using namespace game;

Label::Label() {}

Label::Label(const sf::String& text)  {
	_text = text;
	sf::FloatRect rect = _text.GetRect();
	_width = rect.Right - rect.Left;
	_height = rect.Bottom - rect.Top;
}

void Label::SetText(const std::string& text) {
	_text.SetText(text);
}

void Label::Render(sf::RenderTarget& target) const {
	target.Draw(_text);
}

const sf::Vector2f Label::GetSize() const {
	return sf::Vector2f(_width, _height);
}
