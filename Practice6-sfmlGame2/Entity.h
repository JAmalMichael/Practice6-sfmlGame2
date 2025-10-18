#ifndef ENTITY_H
#define ENTITY_H

#include<unordered_map>
#include<memory>
#include <typeindex>
#include "Component.h"

using namespace std;

class Entity 
{
	size_t m_id; 
	bool m_active = true;  
	unordered_map<type_index, shared_ptr<Component>> m_components; 

public:
	//explicity called constructor
	explicit Entity(size_t id); 
	bool isActive() const; 
	size_t get_id() const;
	void destroy();

	//followed function accepts template arguments and a number of arguments
	template<typename T, typename... Args>
	void addComponent(Args&&... args) 
	{
		m_components[typeid(T)] = make_shared<T>(forward<Args>(args)...);
	}

	//has component function for m_components array
	template<typename T>
	bool hasComponent() const
	{
		return m_components.find(typeid(T)) != m_components.end();
	}

	//a getter function referencing the m_component array
	template<typename T>
	T& getComponent()
	{
		return *static_pointer_cast<T>(m_components.at(typeid(T)));
	}


};

#endif