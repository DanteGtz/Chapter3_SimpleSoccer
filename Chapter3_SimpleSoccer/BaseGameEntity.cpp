//The declaration of some member methods within BGE
#include <cassert>
#include "BaseGameEntity.h"


int BaseGameEntity::m_iNextValidID = 0;

//-----------------> Constructor <----------------//

BaseGameEntity::BaseGameEntity(int ID) :m_dBoundingRadius(0.0),
m_vScale(Vector2D(1.0, 1.0)), m_iType(DEFAULT_ENTITY_TYPE), m_bTag(false)
{
	setID(ID);
}



//-----------------> set identificador <----------------//

//Este debe ser llamado dentro de cada constructor para asegurarnos
//que el ID se ha asignado correctamente. Nos aseguramos que el
//valor pasado sea igual o mayor al siguiente indentificador
//valido, antes asignarselo al ID e incrementar el proximo
//identificador valido
void BaseGameEntity::setID(int val)
{
	//Nos aseguramos que el valor es igual o mayor que el siguient
	//identificador disponible
	assert((val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

	m_ID = val;

	m_iNextValidID = m_ID + 1;
}
