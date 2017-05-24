#pragma once
#ifndef MOVING_ENTITY
#define MOVING_ENTITY
//The first inheritor of the BaseGameEntity class

#include <cassert>

#include "Vector2D.h"
#include "BaseGameEntity.h"



class MovingEntity : public BaseGameEntity
{
protected:

	Vector2D    m_vVelocity;

	//El vector normalizado, que apunta en direccion del movimiento
	//de la entidad.
	Vector2D    m_vHeading;

	//Un vector perpendicular al vector de movimiento de la entidad.
	Vector2D    m_vSide;

	double      m_dMass;

	//La velocidad maxima a la que esta permitido moverse la entidad
	double      m_dMaxSpeed;
	
	//La fuerza maxima que la entidad puede producir para propulsarse
	//(como si fuera un bote con su motor)
	double      m_dMaxForce;

	//El radio maximo (radianes / segundo) en que este vehiculo puede rotar
	double      m_dMaxTurnRate;

public:


	MovingEntity(Vector2D position, double   radius, 
		Vector2D velocity, double   max_speed, Vector2D heading,
		double   mass, Vector2D scale, double   turn_rate,
		double   max_force)
			:BaseGameEntity(BaseGameEntity::GetNextValidID()),
			m_vHeading(heading),
			m_vVelocity(velocity),
			m_dMass(mass),
			m_vSide(m_vHeading.perp()),
			m_dMaxSpeed(max_speed),
			m_dMaxTurnRate(turn_rate),
			m_dMaxForce(max_force)
	{
		m_vPosition = position;
		m_dBoundingRadius = radius;
		m_vScale = scale;
	}


	virtual ~MovingEntity() {}

	//getters y setters
	Vector2D  getVelocity()const { return m_vVelocity; }
	void      setVelocity(const Vector2D& NewVel) { m_vVelocity = NewVel; }

	double    getMass()const { return m_dMass; }

	Vector2D  getSide()const { return m_vSide; }

	double    getMaxSpeed()const { return m_dMaxSpeed; }
	void      setMaxSpeed(double new_speed) { m_dMaxSpeed = new_speed; }

	double    getMaxForce()const { return m_dMaxForce; }
	void      setMaxForce(double mf) { m_dMaxForce = mf; }

	bool      isSpeedMaxedOut()const { return m_dMaxSpeed * m_dMaxSpeed >= m_vVelocity.lengthSq(); }
	double    getSpeed()const { return m_vVelocity.length(); }
	double    getSpeedSq()const { return m_vVelocity.lengthSq(); }

	Vector2D  getHeading()const { return m_vHeading; }
	void      setHeading(Vector2D new_heading);
	bool      rotateHeadingToFacePosition(Vector2D target);

	double    getMaxTurnRate()const { return m_dMaxTurnRate; }
	void      setMaxTurnRate(double val) { m_dMaxTurnRate = val; }

};



//-----------------> Gira hasta apuntar al blanco <----------------//

//Dada la posicion de un objetivo, este metodo gira los vectores de
//direccion y lateral sin sobrepasar el valor de m_dMaxTurnRate, hasta
//apuntar al objetivo

//Regresa verdadero una vez que apunte al blanco
inline bool MovingEntity::rotateHeadingToFacePosition(Vector2D target)
{
	Vector2D toTarget = vec2DNormalize(target - m_vPosition);

	double dot = m_vHeading.dot(toTarget);

	//Algunos compiladores son imprecisos, asi que el valor se sujeta
	//dentro de los limetes del acos
	clamp(dot, -1, 1);

	//Primero determina el angulo entre el vector de trayectoria
	//de la entidad y el del objetivo
	double angle = acos(dot);

	//Regresa verdadero si la entidad apunta al objetivo
	if (angle < 0.00001) 
		return true;

	//Fuerza a que el valor no sea mayor al radio de giro
	if (angle > m_dMaxTurnRate) 
		angle = m_dMaxTurnRate;

	//Las siguientes lineas usan una matriz de rotacion para girar el
	//vector de trayectoria de la entidad de acuerdo a la cantidad de giro
	C2DMatrix RotationMatrix;

	//Aqui podemos observar como el sentido de rotacion determina como
	//vamos a crear la matriz de rotacion
	RotationMatrix.rotate(angle * m_vHeading.sign(toTarget));
	RotationMatrix.transformVector2Ds(m_vHeading);
	RotationMatrix.transformVector2Ds(m_vVelocity);

	//Finalmente obtemos el vector penpendicular m_vSide
	m_vSide = m_vHeading.perp();

	return false;
}



//-----------------> Fijar la trayectoria <----------------//

//Primero determina si el nuevo vector de trayectoria no es nulo. Si
//el nuevo vector es valido, este vector ajusta los vectores de 
//trayectoria y lateral de la entidad
inline void MovingEntity::setHeading(Vector2D new_heading)
{
	assert((new_heading.lengthSq() - 1.0) < 0.00001);

	m_vHeading = new_heading;

	//El vector lateral debe ser perpendicular al de trayectoria
	m_vSide = m_vHeading.perp();
}




#endif