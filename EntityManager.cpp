#include "EntityManager.hpp"

EntityManager::EntityManager(SharedContext* l_context,
	unsigned int l_maxEntities) :m_context(l_context),
	m_maxEntities(l_maxEntities), m_idCounter(0)
{
	LoadEnemyTypes("EnemyList.list");
	RegisterEntity<Player>(EntityType::Player);
	RegisterEntity<Enemy>(EntityType::Enemy);
}

EntityManager::~EntityManager() { Purge(); }

int EntityManager::Add(const EntityType& l_type,
	const std::string& l_name)
{
	auto itr = m_entityFactory.find(l_type);
	if (itr == m_entityFactory.end()) { return -1; }
	EntityBase* entity = itr->second();
	entity->m_id = m_idCounter;
	if (l_name != "") { entity->m_name = l_name; }
	m_entities.emplace(m_idCounter, entity);
	if (l_type == EntityType::Enemy) {
		auto itr = m_enemyTypes.find(l_name);
		if (itr != m_enemyTypes.end()) {
			Enemy* enemy = (Enemy*)entity;
			enemy->Load(itr->second);
		}
	}
	++m_idCounter;
	return m_idCounter - 1;
}