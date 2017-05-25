#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#pragma warning (disable:4786)
//Keeps control of Every entity that exists in the game
#include <map>
#include <cassert>


class BaseGameEntity;

//provee de un macro de facil acceso
#define EntityMgr EntityManager::instance()



class EntityManager
{
private:

	typedef std::map<int, BaseGameEntity*> EntityMap;

private:

	//Para facilitar de un revision rapida de las identidades, estas
	//son almacenadas en un std::map, en el cual los apuntadores de las
	//entidades estan referenciados por su numero de identificacion
	EntityMap m_EntityMap;

	EntityManager() {}

	//Los ctores copia y asignacion deben ser privados
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);

public:

	static EntityManager* instance();

	//Este metodo almacena un apuntador a la entidad, en un 
	//std::vector m_Entities con el indice indicando el ID
	//de la entidad (para un acceso mas rapido)
	void            registerEntity(BaseGameEntity* NewEntity);

	//Regresa un apuntador a la entidad, localizada
	//por medio de su ID como parametro
	BaseGameEntity* getEntityFromID(int id)const;

	//Este metodo remueve una entidad de la lista
	void            removeEntity(BaseGameEntity* pEntity);

	//Limpia todas las entidades del mapa
	void            reset() { m_EntityMap.clear(); }
};







#endif