#include "ResourceManager.h"

using namespace game;

sf::Font ResourceManager::_font;
sf::RenderWindow* ResourceManager::_app;
ImageLookup ResourceManager::_imageLookup;

// todo: consider a generic resource lookup which can return any resource by name, e.g. one lookup per resource type

void ResourceManager::Init(sf::RenderWindow& app) {
	ResourceManager::_font.LoadFromFile("Arial.ttf");
	_app = &app;
}

void ResourceManager::Cleanup() {
	for (ImageLookup::iterator it = _imageLookup.begin(); it != _imageLookup.end(); it++) {
		// could use ptr_map but deciding to rather avoid dependency
		delete it->second;
		it->second = NULL;
	}
	_imageLookup.clear();
}

const sf::Font& ResourceManager::SetFont(const std::string& fontName, unsigned int charSize /*= 30*/) {
	_font.LoadFromFile(fontName, charSize);
	return _font;
}

const sf::Font& ResourceManager::GetFont() {
	return _font;
}

sf::RenderWindow* ResourceManager::GetApp() {
	return _app;
}

const sf::Image& ResourceManager::GetImage(const std::string& fileName) {
	ImageLookup::iterator it = _imageLookup.find(fileName);

	if (it != _imageLookup.end()) {
		return *(it->second);
	} else {
		sf::Image* img = new sf::Image();
		img->LoadFromFile(fileName);
		_imageLookup[fileName] = img;
		return *img;
	}
}
