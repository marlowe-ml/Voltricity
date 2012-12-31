#ifndef ResourceManager_h__
#define ResourceManager_h__

#include <SFML/Graphics.hpp>

namespace game {

	typedef std::map<std::string, sf::Image*> ImageLookup;

	class ResourceManager {

	public:
		static void Init(sf::RenderWindow& app);
		static void Cleanup();
		static const sf::Font& GetFont();
		static const sf::Image& GetImage(const std::string& fileName);
		static sf::RenderWindow* GetApp();
		
		static const sf::Font& SetFont(const std::string& fontName, unsigned int charSize = 30);

	private:
		static sf::Font _font;
		static sf::RenderWindow* _app;
		static ImageLookup _imageLookup;

	};


	/*
	template <class T>
	class ResourceInitParameters {
	public: 
		ResourceInitParameters() {}
	};


	template <>
	class ResourceInitParameters < sf::Font > {
	public:
		unsigned int FontSize;
	};

	
	template <class T>
	class ResourceLookup {

	public:
		T& Get(const std::string& resourceName, ResourceInitParameters<T>* initParams = NULL) {
		}

	private:
		std::map<std::string, T*> _lookup;

	};
	*/
	
}



#endif // ResourceManager_h__
