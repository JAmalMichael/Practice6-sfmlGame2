#include <iostream>
#include "EntityManager.h"
using namespace std;


shared_ptr<Entity> EntityManager::createEntity()
{
	auto entity = make_shared<Entity>(m_nextID);
	m_entity.push_back(entity);
	return entity;
}

void EntityManager::refresh()
{
	m_entity.erase(
		remove_if(
			m_entity.begin(), m_entity.end(),
			[](const shared_ptr<Entity>& e) {return !e->isActive(); }
		),
			m_entity.end()
		);
}

const vector<shared_ptr<Entity>>& EntityManager::getEntity() const
{
	return m_entity;
}
