#pragma once
#include <vector>

#include "Vector2D.h"
#include "C2DMatrix.h"

//-----------------> Transformacion global <----------------//

//Dada un std:::vector de vectores dos dimencionales, una posicion,
//una orientacion y una escala esta funcion transforma los vectores
//en 2D en objetos globales
inline std::vector<Vector2D> worldTransform
	(std::vector<Vector2D> &points, const Vector2D &pos, const Vector2D &forward,
		const Vector2D &side, const Vector2D &scale)
{
	//Copia los vertices originales en un 'buffer' que esta por ser
	//transformado
	std::vector<Vector2D> transVector2Ds = points;

	//Crea una matriz de transformacion
	C2DMatrix matTransform;

	//Escala
	if ((scale.x != 1.0) || (scale.y != 1.0))
	{
		matTransform.scale(scale.x, scale.y);
	}

	//Rotar
	matTransform.rotate(forward, side);

	//Y por ultimo transladar
	matTransform.translate(pos.x, pos.y);

	//Ahora transforma los vertices del objeto
	matTransform.transformVector2Ds(transVector2Ds);

	return transVector2Ds;
}




//-----------------> Transformacion global <----------------//

//Esta funcion sobrecarga a la anterior, si decidimos no
///pasarle un factor de escala
inline std::vector<Vector2D> worldTransform
(std::vector<Vector2D> &points, const Vector2D &pos, const Vector2D &forward,
	const Vector2D &side)
{
	std::vector<Vector2D> transVector2Ds = points;

	C2DMatrix matTransform;

	matTransform.rotate(forward, side);

	matTransform.translate(pos.x, pos.y);

	matTransform.transformVector2Ds(transVector2Ds);

	return transVector2Ds;
}



//-----------------> Punto sobre coordenadas globales <----------------//

//Transforma un punto dado en coordenadas locales del agente
//a coordenadas globales
inline Vector2D pointToWoldSpace
	(const Vector2D &point, const Vector2D &agentHeading,
		const Vector2D &agentSide, const Vector2D &agentPosition)
{
	//Hace una copia del punto
	Vector2D tempPoint = point;

	//Crea una matriz de transformacion
	C2DMatrix matTransform;

	//Rotar
	matTransform.rotate(agentHeading, agentSide);

	//Y translada
	matTransform.translate(agentPosition.x, agentPosition.y);

	matTransform.transformVector2Ds(tempPoint);

	return tempPoint;
}



//-----------------> Punto Global a Local <----------------//
inline Vector2D pointToLocalSpace(const Vector2D &point, Vector2D agentHeading,
	Vector2D &agentSide, Vector2D &agentPosition)
{

	//make a copy of the point
	Vector2D transPoint = point;

	//create a transformation matrix
	C2DMatrix matTransform;

	double tX = -agentPosition.dot(agentHeading);
	double tY = -agentPosition.dot(agentSide);

	//create the transformation matrix
	matTransform._11(agentHeading.x); matTransform._12(agentSide.x);
	matTransform._21(agentHeading.y); matTransform._22(agentSide.y);
	matTransform._31(tX);           matTransform._32(tY);

	//now transform the vertices
	matTransform.transformVector2Ds(transPoint);

	return transPoint;
}




//-----------------> Vector local sobre coordenadas globales <----------------//

//Aplica una transformacion desde las coordenadas locales del
//agente a las coordenadas del sistema
inline Vector2D vectorToWorldSpace
(const Vector2D &vec, const Vector2D &agentHeading,
	const Vector2D &agentSide)
{
	//Crea una copia del vector
	Vector2D tempVec = vec;

	//Crea una matriz de transformacion
	C2DMatrix matTransform;

	//Rotar
	matTransform.rotate(agentHeading, agentSide);

	//Ahora transforma el vector
	matTransform.transformVector2Ds(tempVec);

	return tempVec;
}




//-----------------> Vector de coordenadas globales o locales <----------------//

//Esta funcion transforma las coordenadas de un vector global,
//para que el agente pueda operar sobre el.
inline Vector2D vectorToLocalSpace
(const Vector2D &point, Vector2D &agentHeading, 
	 Vector2D &agentSide, Vector2D &agentPosition)
{
	//Crea una copia del vector
	Vector2D tempVec = point;

	//Crea una matriz de transformaciones
	C2DMatrix matTransform;

	double tX = -agentPosition.dot(agentHeading);
	double tY = -agentPosition.dot(agentSide);

	//Asigna los parametros en cada uno de los 
	//elementos de la matriz de transformacion
	matTransform;
}