#ifndef Screen_h__
#define Screen_h__

#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
#include <iostream>

namespace game {

	class Screen {
	public:
		Screen();
		virtual ~Screen();

		int Init(sf::RenderWindow& app);
		int Run(unsigned long long appTime);
		void Render();
		void Terminate();
		void SetScreenId(const std::string& newScreenId);
		const std::string& GetScreenId() const;
		inline bool IsTerminated() const {return _isTerminated;}
		inline bool IsInitialized() const {return _isInitialized;}
		void SetInactive();


	protected:
		sf::RenderWindow* _app;
		bool _isTerminated;
		bool _isInitialized;
		bool _isInactive;
		std::string _screenId;

		unsigned long long _activeScreenTime;
		unsigned long long _activeScreenTimePrev;
		unsigned long long _appTime;
		unsigned long long _appTimePrev;

		virtual void handleEvent(const sf::Event& e) = 0;
		virtual void update() = 0;
		virtual void present() = 0;
		virtual void onTerminate();
		virtual int onInit();		

		bool nextEvent(sf::Event& eventReceived);
		void onCloseEvent();
	};

}

#endif // Screen_h__