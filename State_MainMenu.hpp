#include "BaseState.hpp"
#include "EventManager.hpp"
#include <functional>

class State_MainMenu : public BaseState {
	public:
		State_MainMenu(StateManager* l_stateManager);
		void MouseClick(EventDetails* l_details);
		void Continue(EventDetails* l_details);
		void OnCreate();
		void OnDestroy();
		void Activate();
		void Deactivate();
		void Update(const sf::Time& l_time);
		void Draw();
	private:
		sf::Text m_text;
		sf::Vector2f m_buttonSize;
		sf::Vector2f m_buttonPos;
		unsigned int m_buttonPadding;
		sf::RectangleShape m_rects[3];
		sf::Text m_labels[3];
		sf::Font m_font;
};