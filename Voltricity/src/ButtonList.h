#ifndef ButtonList_h__
#define ButtonList_h__

#include <SFML/Graphics.hpp>
#include <list>

namespace volt {

class MenuButton : public sf::String {
public:
	MenuButton() : Index(0), Visible(true)
	{}

	MenuButton(const std::string& label, const int index) : sf::String(label), Index(index) 
	{}

	operator int() const {
		return Index;
	}

	int Index;
	bool Visible;
};

typedef std::list<MenuButton> LabelList;

class ButtonList : public sf::Drawable {

public:
	ButtonList();
	void addButton(const std::string label, int index);
	void showButton(int index, bool show);
	void selectFirstButton();
	int getSelectedButton() const;
	void selectPreviousButton();
	void selectNextButton();

	virtual void Render(sf::RenderTarget& target) const;
	sf::FloatRect GetRect() const;

private:
	LabelList _buttons;
	int _selectedButtonIndex;

	float _height;
	float _width;
	float _buttonMargin;

	void align();
	void centerButtonsHorizontally();
	void onSelectionChanged();
	LabelList::iterator ButtonList::iteratorToButton(int index);

};

}

#endif // ButtonList_h__
