/*
 * Vector2D.h
 *
 *  Created on: 01/05/2017
 *      Author: dante
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iosfwd>
#include <limits>
#include <math.h>

#include "../Misc/Utils.h"

struct Vector2D
{
	double x;
	double y;

	Vector2D(double a = 0.0, double b = 0.0)
		: x(a), y(b)
	{
	}

	void zero()
	{
		x = 0.0;
		y = 0.0;
	}

	bool isZero() const { return (x * x + y * y) < MinDouble; }

	inline double dot(const Vector2D& v2) const;

	inline double distanceSq(const Vector2D &v2) const;

	inline double distance(const Vector2D &v2) const;

	inline double length() const;

	inline double lengthSq() const;

	inline void normalize();

	inline Vector2D perp() const;

	inline void reflect(const Vector2D& norm);

	inline int sign(const Vector2D& v2) const;

	inline void truncate(double max);

	inline Vector2D getReverse() const;

	const Vector2D& operator+=(const Vector2D &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	const Vector2D& operator-=(const Vector2D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	const Vector2D& operator*=(const Vector2D &rhs)
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	const Vector2D& operator/=(const Vector2D &rhs)
	{
		x /= rhs.x;
		y /= rhs.y;

		return *this;
	}

	bool operator==(const Vector2D &rhs)
	{
		return (isEqual(x, rhs.x) && isEqual(y, rhs.y));
	}

	bool operator!=(const Vector2D &rhs)
	{
		return (x != rhs.x || y != rhs.y);
	}
};


//-------------------> Algunos operadores sobrecargados extras
inline Vector2D operator*(const Vector2D &lhs, double rhs);

inline Vector2D operator*(double lhs, const Vector2D &rhs);

inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);

inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);

inline Vector2D operator/(const Vector2D &lhs, double val);


std::ostream& operator<<(std::ostream& os, const Vector2D &rhs);


std::ifstream& operator>>(std::ifstream& is, Vector2D &lhs);


//-----------------> Funciones miembro <----------------//
//-----------------> Longitud

					//Regresa la longitud de un vector 2D
inline double Vector2D::length() const
{
	return sqrt(x * x + y * y);
}


//-----------------> Longitud cuadrada

					//Es decir que regresa la longitud
					//al cuadrado de un vector 2D
inline double Vector2D::lengthSq() const
{
	return (x * x + y * y);

}


//----------------->Producto punto

					//Calcula el producto punto
inline double Vector2D::dot(const Vector2D &v2)const
{
	return x * v2.x + y * v2.y;
}


//-----------------> Signo

					//Regresa positivo si v2 es un vector con
					//sentido havia las manecillas del reloj, y regresa
					//negativo si va conta las manecillas del reloj.
enum
{
	CLOCKWISE = 1,
	ANTICLOCKWISE = -1
};

inline int Vector2D::sign(const Vector2D& v2) const
{
	if(y * v2.x > x * v2.y)
		return (int)ANTICLOCKWISE;
	else
		return (int)CLOCKWISE;
}


//-----------------> Perpendicular

					//Regresa el vector perpendicular a este vector
inline Vector2D Vector2D::perp() const
{
	return Vector2D(-y, x);
}


//-----------------> Distancia

					//Calcula la distancia entre dos vectores
inline double Vector2D::distance(const Vector2D &v2) const
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;

	return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
}


//-----------------> Distancia cuadrada

					//Calcula la distancia cuadrada entre dos vectores
inline double Vector2D::distanceSq(const Vector2D &v2) const
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}


//-----------------> Truncar

					//Trunca el vector para que su longitud no rebase
					//un maximo
inline void Vector2D::truncate(double max)
{
	if(this->length() > max)
	{
		this->normalize();

		*this *=max;
	}
}


//-----------------> Reflejo

					//Dado un vector normalizado este metodo
					//refleja este vector. (como una pelota
					//que rebota en una pared)
inline void Vector2D::reflect(const Vector2D& norm)
{
	*this += 2.0 * this->dot(norm) * norm.getReverse();
}


//-----------------> Obten el inverso

					//regresa un vector que es inverso al vector
					//original
inline Vector2D Vector2D::getReverse() const
{
	return Vector2D(-this->x, -this->y);
}


//-----------------> Normalizar

					//Normaliza al vector
inline void Vector2D::normalize()
{
	double vector_length = this->length();

	if(vector_length > std::numeric_limits<double>::epsilon())
	{
		this->x /= vector_length;
		this->y /= vector_length;
	}
}


//-----------------> Funciones que no son miembro <----------------//

inline Vector2D vec2DNormalize(const Vector2D &v)
{
	Vector2D vec = v;

	double vector_length = vec.length();

	if(vector_length > std::numeric_limits<double>::epsilon())
	{
		vec.x /= vector_length;
		vec.y /= vector_length;
	}

	return vec;
}


inline double vector2DDistance(const Vector2D &v1, const Vector2D &v2)
{
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;

	return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
}


inline double vector2DDistanceSq(const Vector2D &v1, const Vector2D &v2)
{
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}


inline double vector2DLength(const Vector2D& v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}


inline double vector2DLengthSq(const Vector2D& v)
{
	return (v.x*v.x + v.y*v.y);
}


//-----------------> Operadores sobrecargados <----------------//

inline Vector2D operator*(const Vector2D &lhs, double rhs)
{
	Vector2D result(lhs);
	result *= rhs;
	return result;
}

inline Vector2D operator*(double lhs, const Vector2D &rhs)
{
	Vector2D result(rhs);
	result *= lhs;
	return result;
}

						//Sobrecarga el operador-
inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;

	return result;
}

inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;

	return result;
}

inline Vector2D operator/(const Vector2D &lhs, double val)
{
	Vector2D result(lhs);
	result.x /= val;
	result.y /= val;

	return result;
}

///////////////////////////////////////////////////////////////////

//-----------------> Otras funciones <----------------//

//Convierte a la ventana en un toroide
inline void wrapAroun(Vector2D &pos, int maxX, int maxY)
{
	if(pos.x > maxX) pos.x = 0.0;

	if(pos.x < 0.0) pos.x = (double)maxX;

	if(pos.y < 0.0) pos.y = (double)maxY;

	if (pos.y > maxY) pos.y = 0.0;
}

#endif /* VECTOR2D_H_ */













