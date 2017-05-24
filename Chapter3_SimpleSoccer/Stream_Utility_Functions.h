#pragma once
#ifndef STREAM_UTILITY_FUNCTIONS
#define STREAM_UTILITY_FUNCTIONS
//various methods that operate on or with streams
#include <sstream>
#include <string>
#include <iomanip>

//-----------------> ttos <----------------//

//Convierte de un tipo de datos (porque es un template) a un cadena
template <class T>
inline std::string ttos(const T& t, int precision = 2)
{
	std::ostringstream buffer;

	buffer << std::fixed << std::setprecision(precision) << t;

	return buffer.str();
}




//-----------------> btos <----------------//

//Convierte de un boleano a un cadena
inline std::string btos(bool b)
{
	if (b) return "true";
	return "false";
}



//-----------------> Obten un valor del stream <----------------//

//Agarra un valor del tipo especificado del stream de entrada
template <typename T>
inline T GetValueFromStream(std::ifstream& stream)
{
	T val;

	stream >> val;

	//Se asegura que sea del tipo de datos correcto
	if (!stream)
	{
		throw std::runtime_error("Attempting to retrieve wrong type from stream");
	}

	return val;
}


#endif