#include "BaseState.hpp"
#include "EventManager.hpp"
#include <functional>

class State_Paused : public BaseState {
public:
	void OnCreate();
	void OnDestroy();
	void Activate();
	void Deactivate();
	void Update(const sf::Time& l_time);
	void Draw();
	void Unpause(EventDetails* l_details);
private:
	sf::Text m_text;
	sf::RectangleShape m_rect;
	sf::Font m_font;
};