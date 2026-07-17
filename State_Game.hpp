#include "BaseState.hpp"
#include "EntityBase.hpp"
#include "EventManager.hpp"
#include <functional>

class State_Game : public BaseState {
public:
	State_Game(StateManager* l_stateManager);
	void OnCreate();
	void OnDestroy();
	void Activate();
	void Deactivate();
	void Update(const sf::Time& l_time);
	void Draw();
	void MainMenu(EventDetails* l_details);
	void Pause(EventDetails* l_details);
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_increment;
	Map* m_gameMap;
};