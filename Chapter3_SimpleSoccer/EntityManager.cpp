#include "EntityManager.h"
#include "BaseGameEntity.h"

//The definition of the member methods inside EM class


//-----------------> Area de un circulo <----------------////

//Esta clase es un singleton
EntityManager* EntityManager::instance()
{
	static EntityManager instance;

	return &instance;
}

//-----------------> Obtener una entidad <----------------//
//-----------------> por medio de su ID <----------------//

BaseGameEntity* EntityManager::getEntityFromID(int id)const
{
	//Encuentra la entidad
	EntityMap::const_iterator ent = m_EntityMap.find(id);

	//Arrojamos un error si la entidad no es valida
	assert((ent != m_EntityMap.end()) && "<EntityManager::getEntityFromID>: invalid ID");

	return ent->second;
}


//-----------------> Remueve una entidad <----------------//

void EntityManager::removeEntity(BaseGameEntity* pEntity)
{
	m_EntityMap.erase(m_EntityMap.find(pEntity->getID()));
}

//-----------------> Registra una entidad <----------------//

void EntityManager::registerEntity(BaseGameEntity* NewEntity)
{
	m_EntityMap.insert(std::make_pair(NewEntity->getID(), NewEntity));
}
