#include "EntityManager.hpp"
#include "Character.hpp"

class Player : public Character {
public:
	Player(EntityManager* l_entityMgr);
	~Player();
	void OnEntityCollision(EntityBase* l_collider, bool l_attack);
	void React(EventDetails* l_details);
};