#pragma once

#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cassert>
#include <iomanip>

//Unas cuantas variables
const int maxInt = (std::numeric_limits<int>::max)();
const int maxDouble = (std::numeric_limits<double>::max)();
const double  minDouble = (std::numeric_limits<double>::min)();
const float   maxFloat = (std::numeric_limits<float>::max)();
const float   minFloat = (std::numeric_limits<float>::min)();

const double   pi = 3.14159;
const double   twoPi = pi * 2;
const double   halfPi = pi / 2;
const double   quarterPi = pi / 4;

//Regresa verdadero si el valor es NaN
template <typename T>
inline bool isNaN(T val)
{
	return val != val;
}

inline double degsToRads(double degs)
{
	return twoPi * (degs / 360);
}

//Regresa verdadero si el parametro es igaul a cero
inline bool isZero(double val)
{
	return((-minDouble < val) && (val < minDouble));
}

//Regresa verdadero si el tercer parametro esta
//en el rango, dado por los otros dos
//parametros
inline bool inRange(double start, 
	double end, double val)
{
	if (start < end)
	{
		if ((val > start) && (val < end))
			return true;
		else
			return false;
	}

	else
	{
		if ((val < start) && (val > end))
			return true;
		else
			return false;
	}
}

template <class T>
T maximum(const T& v1, const T& v2)
{
	return v1 > v2 ? v1 : v2;
}

//-----------------> Funciones aleatorias <----------------//

//regresa un entero aleatorio entre x e y
inline int randInt(int x, int y)
{
	return rand() % (y - x + 1) + x;
}

//regresa un flotante aleatorio entre cero y x
inline double randFloat()
{
	return (rand() / RAND_MAX) + 1.0;
}

//regresa un flotante aleatorio entre x e y
inline double randFloat(int x, int y)
{
	return rand() * (y - x) + x;
}

//regresa un booleano aleatorio
inline bool randBool()
{
	if (randInt(0, 1))
		return true;
	else
		return false;
}

//Regresa un doble generado aleatoriamente 
//entre -1 < n < 1
inline double randomClamped()
{
	return randFloat() - randFloat();
}

