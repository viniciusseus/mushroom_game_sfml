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

EntityBase* EntityManager::Find(const std::string& l_name) {
	for (auto& itr : m_entities) {
		if (itr.second->GetName() == l_name) {
			return itr.second;
		}
	}
	return nullptr;
}

EntityBase* EntityManager::Find(unsigned int l_id) {
	auto itr = m_entities.find(l_id);
	if (itr == m_entities.end()) { return nullptr; }
	return itr->second;
}

void EntityManager::Remove(unsigned int l_id) {
	m_entitiesToRemove.emplace_back(l_id);
}

void EntityManager::Update(float l_dT) {
	for (auto& itr : m_entities) {
		itr.second->Update(l_dT);
	}
	EntityCollisionCheck();
	ProcessRemovals();
}

void EntityManager::Draw() {
	sf::RenderWindow* wnd = m_context->m_wind->GetRenderWindow();
	sf::FloatRect viewSpace = m_context->m_wind->GetViewSpace();
	for (auto& itr : m_entities) {
		if (!viewSpace.intersects(itr.second->m_AABB)) { continue; }
		itr.second->Draw(wnd);
	}
}

void EntityManager::Purge() {
	for (auto& itr : m_entities) {
		delete itr.second;
	}
	m_entities.clear();
	m_idCounter = 0;
}

void EntityManager::ProcessRemovals() {
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end()) {
		unsigned int id = m_entitiesToRemove.back();
		auto itr = m_entities.find(id);
		if (itr != m_entities.end()) {
			std::cout << "Discarding entity: "
				<< itr->second->GetId() << std::endl;
			delete itr->second;
			m_entities.erase(itr);
		}
		m_entitiesToRemove.pop_back();
	}
}