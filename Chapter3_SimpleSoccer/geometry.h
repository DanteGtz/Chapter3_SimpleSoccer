#pragma once
#include <math.h>
#include <vector>

#include "C2DMatrix.h"
#include "Transformations.h"
#include "utils.h"
#include "Vector2D.h"

//-----------------> Area de un circulo <----------------//
inline double circleArea(double radius)
{
	return pi * radius * radius;
}

//-----------------> Distancia al segmento de linea <----------------//

//Dado un segmanto de linea AB y el punto P, esta funcion
//calcula la distancia perpendicular entre ellos
inline double distToLineSegment(Vector2D A,
	Vector2D B, Vector2D P)
{
	//Si el angulo entre PA y AB es obtuso, entonces el vertice mas
	//cercano es  por ende A
	double dotA = (P.x - A.x) * (B.x - A.x) + (P.y - A.y) * (B.y - A.y);

	if (dotA <= 0) return vector2DDistance(A, P);

	//Si el angulo entre PB y AB es obtuso, entonces el vertice mas
	//cercano es por ende A
	double dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

	if (dotB <= 0) return vector2DDistance(B, P);

	//Calcula el punto de AB mas cercano a P
	Vector2D Point = A + ((B - A) * dotA) / (dotA + dotB);

	//calcula la distancia entre P y el punto del segmento de linea
	return vector2DDistance(P, Point);
}




//-----------------> Distancia cuadrada al segmento de linea <----------------//

//Dado un segmanto de linea AB y el punto P, esta funcion
//calcula la distancia perpendicular entre ellos. Omite el paso
//de sacar raiz cuadrada
inline double distToLineSegment(Vector2D A,
	Vector2D B, Vector2D P)
{
	//Si el angulo entre PA y AB es obtuso, entonces el vertice mas
	//cercano es  por ende A
	double dotA = (P.x - A.x) * (B.x - A.x) + (P.y - A.y) * (B.y - A.y);

	if (dotA <= 0) return vector2DDistanceSq(A, P);

	//Si el angulo entre PB y AB es obtuso, entonces el vertice mas
	//cercano es por ende A
	double dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

	if (dotB <= 0) return vector2DDistanceSq(B, P);

	//Calcula el punto de AB mas cercano a P
	Vector2D Point = A + ((B - A) * dotA) / (dotA + dotB);

	//calcula la distancia entre P y el punto del segmento de linea
	return vector2DDistanceSq(P, Point);
}



//-----------------> Distancia de un segmento a un plano <----------------//

//Dado un plano y un segmento de linea (presentado por un vector)
//esta funcion determina en que punto del segmento ocurre una 
//interseccion. Regresa negativo si el arreglo es paralelo
inline double distanceToRayPlaneIntersection(Vector2D rayOrigin,
	Vector2D rayHeading,
	Vector2D planePoint,  //any point on the plane
	Vector2D planeNormal)
{

	double d = -planeNormal.dot(planePoint);
	double numer = planeNormal.dot(rayOrigin) + d;
	double denom = planeNormal.dot(rayHeading);

	// Aqui nos aseguramos que el segmento no sea perpendicular
	if ((denom < 0.000001) && (denom > -0.000001))
	{
		return (-1.0);
	}

	return -(numer / denom);
}



//-----------------> Interseccion entre un segmento de linea <----------------//
//----------------->  y una circunferencia <----------------//

inline bool doRayCircleIntersect(Vector2D rayOrigin,
	Vector2D rayHeading,
	Vector2D circleOrigin,
	double     radius)
{

	Vector2D toCircle = circleOrigin - rayOrigin;
	double length = toCircle.length();
	double v = toCircle.dot(rayHeading);
	double d = radius*radius - (length*length - v*v);

	//Si no hubo interseccion, entonces manda falso
	return (d < 0.0);
}
