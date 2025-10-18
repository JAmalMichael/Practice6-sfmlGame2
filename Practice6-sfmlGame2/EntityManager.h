#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Entity.h"

using namespace std;

class EntityManager
{
	vector<shared_ptr<Entity>> m_entity;
	unordered_map<string, vector<shared_ptr<Entity>>> m_entityMap;
	size_t m_nextID = 0;

public:
	shared_ptr<Entity> createEntity();
	void refresh();
	const vector<shared_ptr<Entity>> & getEntity() const;
	const vector<shared_ptr<Entity>>& getEntity(const string& tag);
};

#endif
