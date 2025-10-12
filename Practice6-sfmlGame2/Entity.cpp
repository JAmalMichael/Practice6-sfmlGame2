#include "Entity.h"

Entity::Entity(size_t id) : m_id(id) {};

size_t Entity::get_id() const { return m_id; };
bool Entity::isActive() const { return m_active; };
void Entity::destroy() { m_active = false; };
