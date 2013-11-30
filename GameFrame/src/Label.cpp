#include "Label.h"

using namespace game;

Label::Label() {}

Label::Label(const sf::String& text) 
	: _bgColor(sf::Color(0,0,0,0)), _borderColor(sf::Color(0,0,0,0)), _borderSize(0)
{
	_text = text;
	fitText();
}

void Label::SetText(const std::string& text) {
	_text.SetText(text);
	fitText();
}

void Label::SetTextWithoutFit(const std::string& text) {
	_text.SetText(text);
}

void Label::fitText() {
	sf::FloatRect rect = _text.GetRect();
	_width = rect.Right - rect.Left;
	_height = rect.Bottom - rect.Top;
}

void Label::Render(sf::RenderTarget& target) const {
	if (_bgColor.a != 0 || _borderSize > 0)
	{
		sf::Vector2f pos = GetPosition();
		target.Draw(sf::Shape::Rectangle(
			sf::Vector2f(-10,-10), 
			sf::Vector2f(_width + 20, _height + 20),
			_bgColor, _borderSize, _borderColor));
	}

	target.Draw(_text);
}

const sf::Vector2f Label::GetSize() const {
	return sf::Vector2f(_width, _height);
}

void Label::SetBackground(sf::Color backgraoundColor) {
	_bgColor = backgraoundColor;
}

void Label::SetBorder(float size, sf::Color color) {
	_borderSize = size;
	_borderColor = color;
}

