#include "EntityBase.hpp"

EntityBase::EntityBase(EntityManager* l_entityMgr)
	:m_entityManager(l_entityMgr), m_name("BaseEntity"),
	m_type(EntityType::Base), m_referenceTile(nullptr),
	m_state(EntityState::Idle), m_id(0),
	m_collidingOnX(false), m_collidingOnY(false) {
}

void EntityBase::SetPosition(const float& l_x, const float& l_y) {
	m_position = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}
void EntityBase::SetPosition(const sf::Vector2f& l_pos) {
	m_position = l_pos;
	UpdateAABB();
}
void EntityBase::SetSize(const float& l_x, const float& l_y) {
	m_size = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}
void EntityBase::SetState(const EntityState& l_state) {
	if (m_state == EntityState::Dying) { return; }
	m_state = l_state;
}

void EntityBase::Move(float l_x, float l_y) {
	m_positionOld = m_position;
	m_position += sf::Vector2f(l_x, l_y);
	sf::Vector2u mapSize = m_entityManager->
		GetContext()->m_gameMap->GetMapSize();
	if (m_position.x < 0) {
		m_position.x = 0;
	}
	else if (m_position.x > (mapSize.x + 1) * Sheet::Tile_Size) {
		m_position.x = (mapSize.x + 1) * Sheet::Tile_Size;
	}
	if (m_position.y < 0) {
		m_position.y = 0;
	}
	else if (m_position.y > (mapSize.y + 1) * Sheet::Tile_Size) {
		m_position.y = (mapSize.y + 1) * Sheet::Tile_Size;
		SetState(EntityState::Dying);
	}
	UpdateAABB();
}

void EntityBase::AddVelocity(float l_x, float l_y) {
	m_velocity += sf::Vector2f(l_x, l_y);
	if (abs(m_velocity.x) > m_maxVelocity.x) {
		if (m_velocity.x < 0) { m_velocity.x = -m_maxVelocity.x; }
		else { m_velocity.x = m_maxVelocity.x; }
	}
	if (abs(m_velocity.y) > m_maxVelocity.y) {
		if (m_velocity.y < 0) { m_velocity.y = -m_maxVelocity.y; }
		else { m_velocity.y = m_maxVelocity.y; }
	}
}

void EntityBase::Accelerate(float l_x, float l_y) {
	m_acceleration += sf::Vector2f(l_x, l_y);
}

void EntityBase::ApplyFriction(float l_x, float l_y) {
	if (m_velocity.x != 0) {
		if (abs(m_velocity.x) - abs(l_x) < 0) { m_velocity.x = 0; }
		else {
			if (m_velocity.x < 0) { m_velocity.x += l_x; }
			else { m_velocity.x -= l_x; }
		}
	}
	if (m_velocity.y != 0) {
		if (abs(m_velocity.y) - abs(l_y) < 0) { m_velocity.y = 0; }
		else {
			if (m_velocity.y < 0) { m_velocity.y += l_y; }
			else { m_velocity.y -= l_y; }
		}
	}
}

void EntityBase::Update(float l_dT) {
	Map* map = m_entityManager->GetContext()->m_gameMap;
	float gravity = map->GetGravity();
	Accelerate(0, gravity);
	AddVelocity(m_acceleration.x * l_dT, m_acceleration.y * l_dT);
	SetAcceleration(0.0f, 0.0f);
	sf::Vector2f frictionValue;
	if (m_referenceTile) {
		frictionValue = m_referenceTile->m_friction;
		if (m_referenceTile->m_deadly) { SetState(EntityState::Dying); }
	}
	else if (map->GetDefaultTile()) {
		frictionValue = map->GetDefaultTile()->m_friction;
	}
	else {
		frictionValue = m_friction;
	}
	float friction_x = (m_speed.x * frictionValue.x) * l_dT;
	float friction_y = (m_speed.y * frictionValue.y) * l_dT;
	ApplyFriction(friction_x, friction_y);
	sf::Vector2f deltaPos = m_velocity * l_dT;
	Move(deltaPos.x, deltaPos.y);
	m_collidingOnX = false;
	m_collidingOnY = false;
	CheckCollisions();
	ResolveCollisions();
}