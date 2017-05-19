#pragma once
//Analytic geometry for collision between entities
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
inline double distToLineSegmentSq(Vector2D A,
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


//-----------------> El punto de interseccion mas cercano entre <----------------//
//-----------------> un segmento de linea y una circunferencia <----------------//

//Dado un segmento de linea AB, la ubicacion de una circunferencia y su radio
//esta funcion determina si hay una interseccion y almacena la posicion de la
//interseccion mas cercana en una refecencia llamada
//intersectionPoint.
//Regresa falso si no se encontro un punto de interseccion
inline bool getLineSegmentCircleClosestIntersectionPoint(Vector2D A, Vector2D B,
	Vector2D pos, double    radius, Vector2D& intersectionPoint)
{
	Vector2D toBNorm = vec2DNormalize(B - A);
	Vector2D perp = toBNorm.perp();

	//Translada al circulo dentro de un espacio local definido por le vector
	//B-A con origen en punto A'
	//  Vector2D LocalPos = PointToLocalSpace(pos, toBNorm, toBNorm.Perp(), A);
	Vector2D localPos = pointToLocalSpace(pos, toBNorm, perp, A);

	bool ipFound = false;

	//Si a la suma del vector de la posicion local y el del radio resulta ser
	//negativo, entonce la circunferencia se encuentra atras del punto A, por
	//lo tanto niguna interseccion es posible. Por otro lado si la variable
	//localPos.x menos el radio es mayor a la longitud del segmento AB,
	//entonces ninguna interseccion es posible
	if ((localPos.x + radius >= 0) &&
		((localPos.x - radius)*(localPos.x - radius) <= vector2DDistanceSq(B, A)))
	{
		//Si la distancia desde el eje x a la posicion del objeto es menor
		//que el radio entonces hay una posible interseccion
		if (fabs(localPos.y) < radius)
		{
			//Ahora hagamos la interseccion entre la circunferencia y
			//el segmento. El centro del circulo esta representado por C(A,B)
			//Este punto de interseccion esta dado por la formula
			//x = A +/-sqrt(r^2-B^2), y=0. Solo cuando necesitamos dar con el
			//valor mas chico positivo de x
			double a = localPos.x;
			double b = localPos.y;

			double ip = a - sqrt(radius*radius - b*b);

			if (ip <= 0)
			{
				ip = a + sqrt(radius*radius - b*b);
			}

			ipFound = true;

			intersectionPoint = A + toBNorm*ip;
		}
	}

	return ipFound;
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
inline bool getTangentPoints(Vector2D C, double R, Vector2D P, 
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
inline bool lineIntersection2D(Vector2D A, Vector2D B,
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
inline bool lineIntersection2D(Vector2D   A, Vector2D   B,
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



//-----------------> Interseccion de un segmento <----------------//
//-----------------> de recta a una circunferencia <----------------//

//Regresa cierto si el segmento de linea AB in
inline bool   lineSegmentCircleIntersection(Vector2D A,
	Vector2D B, Vector2D P, double    radius)
{
	//Primero determina la distancia desde el centro del circulo
	//al segmento de linea
	double distToLineSq = distToLineSegmentSq(A, B, P);

	if (distToLineSq < radius*radius)
	{
		return true;
	}

	else
	{
		return false;
	}

}



//-----------------> Punto en la circunferencia <----------------//

//Regresa verdadero si el punto P esta dentro del radio de 
//cierta circunferencia dada
inline bool pointInCircle(Vector2D pos, double    radius,
	Vector2D p)
{
	double distFromCenterSquared = (p - pos).lengthSq();

	if (distFromCenterSquared < (radius*radius))
	{
		return true;
	}

	return false;
}


//-----------------> Interseccion de objetos 2D <----------------//

//Prueba si dos poligonos que se intersectan
//*No revisa si el poligono es cerrado*
inline bool objectIntersection2D(const std::vector<Vector2D>& object1,
	const std::vector<Vector2D>& object2)
{
	//Prueba cada segmento de linea del primer poligono contra
	//cada segmento del poligono
	for (unsigned int r = 0; r < object1.size() - 1; ++r)
	{
		for (unsigned int t = 0; t < object2.size() - 1; ++t)
		{
			if (lineIntersection2D(object2[t],
				object2[t + 1],
				object1[r],
				object1[r + 1]))
			{
				return true;
			}
		}
	}

	return false;
}


//-----------------> Interseccion de un segmento <----------------//
//-----------------> y un objeto en 2D <----------------//

//Prueba la interseccion entre el segmento de linea
//y el poligono de colision *No revisa si el poligono es cerrado*
inline bool segmentObjectIntersection2D(const Vector2D& A,
	const Vector2D& B, const std::vector<Vector2D>& object)
{
	//Prueba el segmento AB contra cada segmento
	//del poligono
	for (unsigned int r = 0; r<object.size() - 1; ++r)
	{
		if (lineIntersection2D(A, B, object[r], object[r + 1]))
		{
			return true;
		}
	}

	return false;
}



//-----------------> Dos circunferencias sobrepuestas <----------------//

//Regresa verdadero si se solapan
inline bool twoCirclesOverlapped(double x1, double y1, double r1,
	double x2, double y2, double r2)
{
	double distBetweenCenters = sqrt((x1 - x2) * (x1 - x2) +
		(y1 - y2) * (y1 - y2));

	if ((distBetweenCenters < (r1 + r2)) || (distBetweenCenters < fabs(r1 - r2)))
	{
		return true;
	}

	return false;
}




//-----------------> Dos circunferencias sobrepuestas <----------------//

//Regresa verdadero si se solapan
inline bool twoCirclesOverlapped(Vector2D c1, double r1,
	Vector2D c2, double r2)
{
	double distBetweenCenters = sqrt((c1.x - c2.x) * (c1.x - c2.x) +
		(c1.y - c2.y) * (c1.y - c2.y));

	if ((distBetweenCenters < (r1 + r2)) || (distBetweenCenters < fabs(r1 - r2)))
	{
		return true;
	}

	return false;
}




//-----------------> Una circunferencia dentro de otra <----------------//

//Regresa verdadero si encuentra que una circunferencia encierra
//a la otra
inline bool twoCirclesEnclosed(double x1, double y1, double r1,
	double x2, double y2, double r2)
{
	double DistBetweenCenters = sqrt((x1 - x2) * (x1 - x2) +
		(y1 - y2) * (y1 - y2));

	if (DistBetweenCenters < fabs(r1 - r2))
	{
		return true;
	}

	return false;
}




//-----------------> Una circunferencia dentro de otra <----------------//

//Dadas dos circunferencias, calcula los puntos de interseccion si estan
//solapadas
// Mas http://astronomy.swin.edu.au/~pbourke/geometry/2circle/
inline bool twoCirclesIntersectionPoints(double x1, double y1, double r1,
	double x2, double y2, double r2, double &p3X, double &p3Y,
	double &p4X, double &p4Y)
{
	//Primero checa si estan sobrepuestas
	if (!twoCirclesOverlapped(x1, y1, r1, x2, y2, r2))
	{
		return false;
	}

	//Calcula la distancia entre los centros
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	//Ahora calcula la distancia desde los centros de la circunferencia
	//al punto medio del segmento de linea que conecta a las intersecciones
	double a = (r1 - r2 + (d * d)) / (2 * d);
	//  double b = (r2 - r1 + (d * d)) / (2 * d);

	//Calcula el punto P2 el cual esta en centro de segmento de linea
	//el cual conecta a los dos puntos
	double p2X;
	double p2Y;

	p2X = x1 + a * (x2 - x1) / d;
	p2Y = y1 + a * (y2 - y1) / d;

	//Calcula el primer punto
	double h1 = sqrt((r1 * r1) - (a * a));

	p3X = p2X - h1 * (y2 - y1) / d;
	p3Y = p2Y + h1 * (x2 - x1) / d;


	//calcula el segundo punto
	double h2 = sqrt((r2 * r2) - (a * a));

	p4X = p2X + h2 * (y2 - y1) / d;
	p4Y = p2Y - h2 * (x2 - x1) / d;

	return true;

}



//-----------------> El area de interseccion de los dos circulos <----------------//

//Si dos circulos se sobreponen, procede a calcular el area resultante
//de esta union
//------------------------ TwoCirclesIntersectionArea --------------------
// Mas http://mathforum.org/library/drmath/view/54785.html
inline double twoCirclesIntersectionArea(double x1, double y1, double r1,
	double x2, double y2, double r2)
{
	//Primero calculamos el puntos de interseccion
	double iX1;
	double iY1;
	double iX2;
	double iY2;

	if (!twoCirclesIntersectionPoints(x1, y1, r1, x2, y2, r2, iX1, iY1, iX2, iY2))
	{
		return 0.0; //no overlap
	}

	//Calcula la distancia entre los centros
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	//Encuentra los angulos formados tal que A y B son el centro de
	//los dos circulos; C y D son los puntos de interseccion
	double CBD = 2 * acos((r2 * r2 + d * d - r1 * r1) / (r2 * d * 2));

	double CAD = 2 * acos((r1 * r1 + d * d - r2 * r2) / (r1 * d * 2));

	//Cuando encontramos el segmento de cada circulo que fue cortado
	//por la cuerda CD, tomamos el area del sector circular BCD y el
	//substraemos el area del triangulo BCD. De forma similar podemos
	//encontrar el area del sector ACD y substraemos el area
	//formado por los puntos ACD
	double area = 0.5f * CBD * r2 * r2 - 0.5f * r2 * r2  *sin(CBD) +
		0.5f * CAD * r1 * r1 - 0.5f * r1 * r1 * sin(CAD);

	return area;
}


//------------------------- Donde esta el punto  --------------------------------------
enum span_type 
{ 
	PLANE_BACKSIDE, 
	PLANE_FRONT, 
	ON_PLANE
};
inline span_type whereIsPoint(Vector2D point,
	Vector2D PointOnPlane, //Cualquier punto del plano
	Vector2D PlaneNormal)
{
	Vector2D dir = PointOnPlane - point;

	double d = dir.dot(PlaneNormal);

	if (d < -0.000001)
	{
		return PLANE_FRONT;
	}

	else if (d  > 0.000001)
	{
		return PLANE_BACKSIDE;
	}

	return ON_PLANE;
}