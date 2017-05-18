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

//Regresa un numero aleatorio con una distribucion
//normal.
inline double randGuassian(double mean = 0.0,
	double standar_deviation = 1.0)
{
	double x1;
	double x2;
	double y1;
	double w;
	static double y2;
	static int use_last = 0;

	//Usa el valor de la llamada anterior
	if (use_last)
	{
		y1 = y2;
		use_last = 0;
	}

	else
	{
		do
		{
			x1 = 2.0 * randFloat() - 1.0;
			x2 = 2.0 * randFloat() - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return (mean + y1 * standar_deviation);
}




//-----------------> Funciones varias <----------------//



inline double sigmoid(double input, double response = 1.0)
{
	return (1.0 / (1.0 + exp(-input / response)));
}

//Regresa el maximo entre dos numeros
template <class T>
inline T maxOf(const T& a, const T& b)
{
	if (a > b)
		return a;

	return b;
}

//Regresa el minimo entre dos numeros
template <class T>
inline T minOf(const T& a, const T& b)
{
	if (a < b)
		return a;

	return b;
}

//clamps the first argument between the second two
template <class T, class U, class V>
inline void clamp(T& arg, const U& minVal, const V& maxVal)
{
	assert((minVal < maxVal) && "<clamp>MaxVal < MinVal!");

	if (arg < (T)minVal)
	{
		arg = (T)minVal;
	}

	if (arg >(T)maxVal)
	{
		arg = (T)maxVal;
	}
}

//Redondea un valor hacia arriba o hacia abajo
//dependiendo de su valor
inline int rounded(double val)
{
	int integral = (int)val;
	double mantissa = val - integral;

	if (mantissa < 0.5)
	{
		return integral;
	}
	else
	{
		return integral + 1;
	}
}

//Redondea un doble hacia arriba o hacia abajo, de acuerdo
//si su mantisa es mas alta que el offset
inline int roundUnderOffset(double val, double offset)
{
	int    integral = (int)val;
	double mantissa = val - integral;

	if (mantissa < offset)
	{
		return integral;
	}

	else
	{
		return integral + 1;
	}
}

//Compara dos flotantes. Regresa verdadero si lo son
inline bool isEqual(float a, float b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}

//Compara dos dobles. Regresa verdadero si lo son
inline bool isEqual(double a, double b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}

template <class T>
inline double average(const std::vector<T>& v)
{
	double dAverage = 0.0;

	for (unsigned int i = 0; i < v.size(); ++i)
	{
		dAverage += (double)v[i];
	}

	return dAverage / (double)v.size();
}

inline double standardDeviation(const std::vector<double>& v)
{
	double sd = 0.0;
	double dAverage = average(v);

	for (unsigned int i = 0; i<v.size(); ++i)
	{
		sd += (v[i] - dAverage) * (v[i] - dAverage);
	}

	sd = sd / v.size();

	return sqrt(sd);
}

template <class container>
inline void deleteSTLContainer(container& c)
{
	for (container::iterator it = c.begin(); it != c.end(); it++)
	{
		delete *it;
		*it = NULL;
	}
}

template <class map>
inline void deleteSTLMap(map& m)
{
	for (map::iterator it = m.begin(); it != m.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
}