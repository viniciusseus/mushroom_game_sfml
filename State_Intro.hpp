#include "BaseState.hpp"
#include "EventManager.hpp"
#include <functional>

class State_Intro : public BaseState {

public:
	void Continue(EventDetails* l_details);
	void OnCreate();
	void OnDestroy();
	void Activate();
	void Deactivate();
	void Update(const sf::Time& l_time);
	void Draw();

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Text m_text;
	sf::Font m_font;
	float m_timePassed;
};