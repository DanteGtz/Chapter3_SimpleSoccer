#pragma once
#ifndef BASE_GAME_ENTITY_H
#define BASE_GAME_ENTITY_H
#pragma warning (disable:4786)
//The base class for all agents and objects
#include <vector>
#include <string>
#include <iosfwd>

#include "Geometry.h"
#include "utils.h"
#include "Vector2D.h"



struct Telegram;


class BaseGameEntity
{
public:

	enum { DEFAULT_ENTITY_TYPE = -1 };

private:

	//Cada una de las entidades tiene un identificador
	int         m_ID;

	//Cada entidad tiene un tipo asociado en el
	//(Ya sea health, troll, ammo, etc.)
	int         m_iType;

	//Una bandera bit 
	bool        m_bTag;

	//El siguiente identificador valido. Cada vez que BaseGameEntity
	//es instanciada este valor se actualiza
	static int  m_iNextValidID;

	//this must be called within each constructor to make sure the ID is set
	//correctly. It verifies that the value passed to the method is greater
	//or equal to the next valid ID, before setting the ID and incrementing
	//the next valid ID
	void setID(int val);


protected:

	//Su posicion en el espacio
	Vector2D m_vPosition;

	Vector2D m_vScale;

	//
	//la magnitud de su 'bounding radius', variable utilizada en la
	//parte grafica del objeto
	double    m_dBoundingRadius;


	BaseGameEntity(int ID);

public:

	virtual ~BaseGameEntity() {}

	virtual void Update() {};

	virtual void Render() = 0;

	virtual bool HandleMessage(const Telegram& msg) { return false; }
	
	//Las entidades deben ser capaces de leer/escribir su informacion
	//dentro de un stream
	virtual void write(std::ostream&  os)const {}
	virtual void read(std::ifstream& is) {}

	//Se ultiliza para asignar el siguiente identificador valido
	static int   GetNextValidID() { return m_iNextValidID; }

	//Funcion utiliza para reiniciar el valor ID
	static void  ResetNextValidID() { m_iNextValidID = 0; }



	Vector2D     getPos() const { return m_vPosition; }
	void         setPos ( Vector2D new_pos ) { m_vPosition = new_pos; }

	double       getBRadius () const { return m_dBoundingRadius; }
	void         setBRadius ( double r ) { m_dBoundingRadius = r; }
	int          getID () const { return m_ID; }

	bool         isTagged ()const { return m_bTag; }
	void         tagIt () { m_bTag = true; }
	void         unTag () { m_bTag = false; }

	Vector2D     getScale () const { return m_vScale; }
	void         setScale ( Vector2D val) 
	{ 
		m_dBoundingRadius *= maxOf(val.x, val.y) / 
		maxOf(m_vScale.x, m_vScale.y);
		m_vScale = val; 
	}
	void         setScale ( double val ) 
	{
		m_dBoundingRadius *= (val / maxOf(m_vScale.x, m_vScale.y)); 
		m_vScale = Vector2D(val, val);
	}

	int          getEntityType()const { return m_iType; }
	void         setEntityType(int new_type) { m_iType = new_type; }

};




#endif




