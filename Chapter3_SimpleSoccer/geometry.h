#pragma once
#include <math.h>
#include <vector>

#include "C2DMatrix.h"
#include "Transformations.h"
#include "utils.h"
#include "Vector2D.h"

const double pi = 3.14159;

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
	Vector2D planePoint,  /*Cualquier punto al plano */
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
	Vector2D rayHeading, Vector2D circleOrigin, double     radius)
{

	Vector2D toCircle = circleOrigin - rayOrigin;
	double length = toCircle.length();
	double v = toCircle.dot(rayHeading);
	double d = radius*radius - (length*length - v*v);

	//Si no hubo interseccion, entonces manda falso
	return (d < 0.0);
}



//-----------------> Interseccion entre un segmento de linea <----------------//
//-----------------> (en su forma vectorial) y una circunferencia <----------------//
inline double getRayCircleIntersect(Vector2D rayOrigin,
	Vector2D rayHeading, Vector2D circleOrigin, double  radius)
{

	Vector2D toCircle = circleOrigin - rayOrigin;
	double length = toCircle.length();
	double v = toCircle.dot(rayHeading);
	double d = radius*radius - (length*length - v*v);

	// Si no hubo interseccion entonces regresa -1
	if (d < 0.0) 
		return (-1.0);

	// Regresa la distancia entre el primer punto
	//de interseccion
	return (v - sqrt(d));
}


//-----------------> Puntos de una tangente <----------------//

//Dado un punto P y una circunferencia de radio R, con
//centro en C esta funcion determina los dos puntos en
//la circunferencia que intersecta con las tangentes definidas
//por el punto P y uno de los dos puntos de la circunferencia
//Regresa falso si P esta dentro del circulo
inline bool GetTangentPoints(Vector2D C, double R, Vector2D P, 
	Vector2D& T1, Vector2D& T2)
{
	Vector2D PmC = P - C;
	double sqrLen = PmC.lengthSq();
	double RSqr = R*R;
	if (sqrLen <= RSqr)
	{
		// Por lo tanto P se encuentra dentro de la
		//circunferencia
		return false;
	}

	double invSqrLen = 1 / sqrLen;
	double Root = sqrt(fabs(sqrLen - RSqr));

	T1.x = C.x + R*(R*PmC.x - PmC.y*Root)*invSqrLen;
	T1.y = C.y + R*(R*PmC.y + PmC.x*Root)*invSqrLen;
	T2.x = C.x + R*(R*PmC.x + PmC.y*Root)*invSqrLen;
	T2.y = C.y + R*(R*PmC.y - PmC.x*Root)*invSqrLen;

	return true;
}



//-----------------> Interseccion de dos lineas en 2D <----------------//

//Dadas dos lineas AB y CD; en el spacio 2D esta funcion
//regresa verdadero si que existe una interseccion
inline bool lineIntersection2D(Vector2D A,
	Vector2D B, Vector2D C, Vector2D D)
{
	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);

	double bot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	if (bot == 0)
		//Son paralelas
	{
		return false;
	}

	double invBot = 1.0 / bot;
	double r = rTop * invBot;
	double s = sTop * invBot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		//Las lineas se insersectan
		return true;
	}

	//Las lineas no se intersectan
	return false;
}




//-----------------> Interseccion de dos lineas en 2D <----------------//

//Dadas dos lineas AB y CD; en el spacio 2D esta funcion
//regresa verdadero si que existe una interseccion. Si
//esto ocurre devuelve la distancia a la que ocurre la
//interseccion
inline bool LineIntersection2D(Vector2D A, Vector2D B,
	Vector2D C, Vector2D D, double &dist)
{

	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);

	double bot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);


	if (bot == 0)
		//Son paralelas
	{
		if (isEqual(rTop, 0) && isEqual(sTop, 0))
		{
			return true;
		}
		return false;
	}

	double r = rTop / bot;
	double s = sTop / bot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		dist = vector2DDistance(A, B) * r;

		return true;
	}

	else
	{
		dist = 0;

		return false;
	}
}



//-----------------> Interseccion de dos lineas en 2D <----------------//

//Dadas dos lineas AB y CD; en el spacio 2D esta funcion
//regresa verdadero si que existe una interseccion. Si
//esto ocurre devuelve la distancia a la que ocurre la
//interseccion. Ademas regresa un vector dirigido al
//punto de interseccion
inline bool LineIntersection2D(Vector2D   A, Vector2D   B,
	Vector2D   C, Vector2D   D, double&     dist, Vector2D&  point)
{

	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double rBot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);
	double sBot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	if ((rBot == 0) || (sBot == 0))
	{
		//Son paralelas
		return false;
	}

	double r = rTop / rBot;
	double s = sTop / sBot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		dist = vector2DDistance(A, B) * r;

		point = A + r * (B - A);

		return true;
	}

	else
	{
		dist = 0;

		return false;
	}
}