#include "hzpch.h"
#include "Entity.h"

namespace SandTable {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}