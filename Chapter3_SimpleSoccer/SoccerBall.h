#pragma once
#ifndef SOCCERBALL_H
#define SOCCERBALL_H
#pragma warning (disable:4786)
//The SoccerBall as an object

#include <vector>

#include "MovingEntity.h"
#include "constants.h"


class Wall2D;
class PlayerBase;


class SoccerBall : public MovingEntity
{
private:

	//Mantiene el registro de la posicion del balon
	//hasta la ultima actualizacion
	Vector2D                  m_vOldPos;

	//Una referencia local a los muros para marcar
	//los limites del movimiento del balon
	const std::vector<Wall2D>& m_PitchBoundary;




public:
	//Prueba si el balon a colisionado con alguna pared.
	//si es asi refleja la trayectoria del balon, de 
	//acuerdo al angulo y la velocidad del objeto
	void testCollisionWithWalls(const std::vector<Wall2D>& walls);

	SoccerBall(Vector2D           pos,
		double               ballSize,
		double               mass,
		std::vector<Wall2D>& PitchBoundary) :

		//Inicializacion de la clase base
		MovingEntity(pos,
			ballSize,
			Vector2D(0, 0),
			-1.0,                //max speed - sin usar 
			Vector2D(0, 1),
			mass,
			Vector2D(1.0, 1.0),  //scale     - sin usar
			0,                   //turn rate - sin usar
			0),                  //max force - sin usar
		m_PitchBoundary(PitchBoundary)
	{}

	//Implementa la funcion update
	void      update();

	//Implementa la funcion render
	void      Render();

	//Es balon no necesita manejar mensajes
	bool      HandleMessage(const Telegram& msg) { return false; }

	//Este metodo aplica un vector dirrecional de fuerza del
	//balon (al "patearla")
	void      kick(Vector2D direction, double force);

	//Dada una fuerza de bombeo (nombre fancy de patear el balon)
	//y la distacia de viaje definida por una poscion inicial y una
	//final, este metod calcula cuanto tiempo tardara en cubrir
	//esa distancia
	double    timeToCoverDistance(Vector2D from,
		Vector2D to,
		double     force)const;

	//Este metodo calcula donde estara el balon en un tiempo
	//futuro (dado en segundos)
	Vector2D futurePosition(double time)const;

	//Se invoca cada vez que los jugadores y el guardameta 
	//tengan el balon en su control. Cuando un jugador la tiene
	//en su poder, la posicion y m_pOwner se adaptan
	void      trap() { m_vVelocity.zero(); }

	Vector2D  OldPos()const { return m_vOldPos; }

	//Esta funcion coloca el balon en una poscion deseada
	//y le asigna una nueva velocidad
	void      placeAtPosition(Vector2D newPos);
};



//Este metodo disminuye la precision al patear el balon
Vector2D addNoiseToKick(Vector2D ballPos, Vector2D ballTarget);



#endif