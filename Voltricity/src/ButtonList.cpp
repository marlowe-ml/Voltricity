#include "ButtonList.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "Layout.h"

using namespace volt;

ButtonList::ButtonList() : _height(0), _width(0), _buttonMargin(10) {}

void ButtonList::addButton(const std::string label, const int index) {
	LabelList::iterator itExisting = iteratorToButton(_selectedButtonIndex);
	if (itExisting != _buttons.end())
		return;	// index must be unique

	MenuButton button(label, index);
	button.SetFont(game::ResourceManager::GetFont());
	button.SetColor(sf::Color(255,255,255));

	float currentHeight = 0;

	// insert before first button with higher index
	LabelList::iterator it = _buttons.begin();
	for (; it != _buttons.end(); it++)
	{
		if ((*it).Index > index)
			break;
	}

	if (it == _buttons.end())
		_buttons.push_back(button);		
	else
		_buttons.insert(it, button);

	align();
}

void ButtonList::showButton(int index, bool show) {
	LabelList::iterator it = iteratorToButton(index);
	if (it == _buttons.end())
		return;

	(*it).Visible = show;

	if ((*it).Index == index && !show)
		selectFirstButton();

	align();
}

void ButtonList::selectFirstButton() {
	for (LabelList::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
		if ((*it).Visible) {
			_selectedButtonIndex = (*it).Index;
			onSelectionChanged();
			break;
		}
	}	
}

void ButtonList::selectPreviousButton() {
	LabelList::iterator it = iteratorToButton(_selectedButtonIndex);
	if (it == _buttons.end())
		return;

	while (it != _buttons.begin()) {
		--it;
		if ((*it).Visible) {
			_selectedButtonIndex = (*(it)).Index;
			onSelectionChanged();
			break;
		}
	}
}

void ButtonList::selectNextButton() {
	LabelList::iterator it = iteratorToButton(_selectedButtonIndex);
	if (it == _buttons.end())
		return;

	while (++it != _buttons.end()) {
		if ((*it).Visible) {
			_selectedButtonIndex = (*it).Index;
			onSelectionChanged();
			break;
		}
	}
}

LabelList::iterator ButtonList::iteratorToButton(int index) {
	LabelList::iterator it = _buttons.begin(); 
	while (it != _buttons.end()) {
		if ((*it).Index == index) {
			break;
		}
		it++;
	}

	return it;
}

void ButtonList::onSelectionChanged() {
	for (LabelList::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
		if ((*it).Index == _selectedButtonIndex)
			(*it).SetColor(sf::Color(255,0,0));
		else
			(*it).SetColor(sf::Color(255,255,255));
	}	
}

int ButtonList::getSelectedButton() const {
	return _selectedButtonIndex;
}

sf::FloatRect ButtonList::GetRect() const {
	return sf::FloatRect(0, 0, _width, _height);
}

void ButtonList::align() {
	float currentHeight = 0;
	float currentWidth = 0;

	for (LabelList::iterator it = _buttons.begin(); it != _buttons.end(); it++)
	{
		if (!(*it).Visible)
			continue;

		(*it).SetY(currentHeight);
		currentHeight += (*it).GetRect().GetHeight() + _buttonMargin;

		float buttonWidth = (*it).GetRect().GetWidth();
		if (buttonWidth > currentWidth)
			currentWidth = buttonWidth;
	}

	_height = currentHeight;
	_width = currentWidth;
	centerButtonsHorizontally();

	const game::Layout & layout = game::ScreenManager::GetLayout();
	layout.AlignDrawable(*this, sf::Vector2f(_width,_height), game::Direction::center);
}


void ButtonList::centerButtonsHorizontally() {
	for (LabelList::iterator it = _buttons.begin(); it!=_buttons.end(); it++) {
		float buttonWidth = (*it).GetRect().GetWidth();
		float offsetDistance = (_width - buttonWidth)/2.f;

		(*it).SetX(offsetDistance);
	}
}

void ButtonList::Render(sf::RenderTarget& target) const {
	for (LabelList::const_iterator it = _buttons.begin(); it!=_buttons.end(); it++) {
		if ((*it).Visible)
			target.Draw(*it);
	}
}