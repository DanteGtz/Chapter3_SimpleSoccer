#pragma once
#include <math.h>
#include <vector>

#include "utils.h"
#include "Vector2D.h"

class C2DMatrix
{
private:
	struct Matrix
	{
		double _11, _12, _13;

		double _21, _22, _23;

		double _31, _32, _33;

		//Este es el constructor de la estructura
		Matrix()
		{
			_11 = 0.0; _12 = 0.0; _13 = 0.0;

			_21 = 0.0; _22 = 0.0; _23 = 0.0;

			_31 = 0.0; _32 = 0.0; _33 = 0.0;
		}
	};

	Matrix m_Matrix;

	//Multiplica dos matrices: m_Matrix con mIn
	inline void matrixMultiply (Matrix &mIn);

public:
	C2DMatrix()
	{
		//Inicializa la matriz como si fuera una
		//matriz identidad
		identity();
	}

	//Crea una matrix unitario o identidad
	inline void identity();

	//Crea una matriz de transformacion
	inline void tranlate(double x, double y);


private:

};
