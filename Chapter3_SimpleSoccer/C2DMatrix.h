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

	//Crea una matriz de rotacion
	inline void rotate(double rotation);

	//Crea una matriz de rotacion a partir del vector frontal
	//y lateral del vehiculo
	inline void rotate(const Vector2D &fwd,
		const Vector2D &side);

	inline void scale(double xScale, double yScale);

	//Aplica la matriz de transformacion a un std::vector
	//de puntos
	inline void transformVector2Ds(std::vector<Vector2D> &vPoints);

	//Aplica la matriz de transformacion a un vector
	inline void transformVector2Ds(Vector2D &vPoint);

	//Crea una matriz de transformacion
	inline void translate(double x, double y);

	//Metodos de accedos a los elementos de la matriz

	void _11(double val) { m_Matrix._11 = val; }
	void _12(double val) { m_Matrix._12 = val; }
	void _13(double val) { m_Matrix._13 = val; }

	void _21(double val) { m_Matrix._21 = val; }
	void _22(double val) { m_Matrix._22 = val; }
	void _23(double val) { m_Matrix._23 = val; }

	void _31(double val) { m_Matrix._31 = val; }
	void _32(double val) { m_Matrix._32 = val; }
	void _33(double val) { m_Matrix._33 = val; }

};



//Multiplica dos matrices juntas
inline void C2DMatrix::matrixMultiply(Matrix &mIn)
{
	C2DMatrix::Matrix mat_temp;

	//Primer renglon
	mat_temp._11 = (m_Matrix._11*mIn._11) + (m_Matrix._12*mIn._21) + (m_Matrix._13*mIn._31);
	mat_temp._12 = (m_Matrix._11*mIn._12) + (m_Matrix._12*mIn._22) + (m_Matrix._13*mIn._32);
	mat_temp._13 = (m_Matrix._11*mIn._13) + (m_Matrix._12*mIn._23) + (m_Matrix._13*mIn._33);

	//segundo
	mat_temp._21 = (m_Matrix._21*mIn._11) + (m_Matrix._22*mIn._21) + (m_Matrix._23*mIn._31);
	mat_temp._22 = (m_Matrix._21*mIn._12) + (m_Matrix._22*mIn._22) + (m_Matrix._23*mIn._32);
	mat_temp._23 = (m_Matrix._21*mIn._13) + (m_Matrix._22*mIn._23) + (m_Matrix._23*mIn._33);

	//tercero
	mat_temp._31 = (m_Matrix._31*mIn._11) + (m_Matrix._32*mIn._21) + (m_Matrix._33*mIn._31);
	mat_temp._32 = (m_Matrix._31*mIn._12) + (m_Matrix._32*mIn._22) + (m_Matrix._33*mIn._32);
	mat_temp._33 = (m_Matrix._31*mIn._13) + (m_Matrix._32*mIn._23) + (m_Matrix._33*mIn._33);

	m_Matrix = mat_temp;
}



//Crea una matriz identidad
inline void C2DMatrix::identity()
{
	m_Matrix._11 = 1; m_Matrix._12 = 0; m_Matrix._13 = 0;

	m_Matrix._21 = 0; m_Matrix._22 = 1; m_Matrix._23 = 0;

	m_Matrix._31 = 0; m_Matrix._32 = 0; m_Matrix._33 = 1;

}



//Crea una matriz de rotacion
inline void C2DMatrix::rotate(double rot)
{
	C2DMatrix::Matrix mat;

	double mSin = sin(rot);
	double mCos = cos(rot);

	//Rotacion antihoraria. Mas informacion en
	//https://es.wikipedia.org/wiki/Matriz_de_rotaci%C3%B3n
	mat._11 = mCos;  mat._12 = mSin; mat._13 = 0;

	mat._21 = -mSin; mat._22 = mCos; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//Y pasamos a multiplicar
	matrixMultiply(mat);
}



inline void C2DMatrix::rotate(const Vector2D &fwd,
	const Vector2D &side)
{
	C2DMatrix::Matrix mat;

	mat._11 = fwd.x;  mat._12 = fwd.y; mat._13 = 0;

	mat._21 = side.x; mat._22 = side.y; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//Y pasamos a multiplicar
	matrixMultiply(mat);
}

inline void C2DMatrix::scale(double xScale, double yScale)
{
	C2DMatrix::Matrix mat;

	mat._11 = xScale; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = yScale; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//Y pasamos a multiplicar
	matrixMultiply(mat);
}




inline void C2DMatrix::transformVector2Ds(std::vector<Vector2D>& vPoints)
{
	for (unsigned int i = 0; i < vPoints.size(); ++i)
	{
		double tempX = (m_Matrix._11*vPoints[i].x) + (m_Matrix._21*vPoints[i].y) + (m_Matrix._31);

		double tempY = (m_Matrix._12*vPoints[i].x) + (m_Matrix._22*vPoints[i].y) + (m_Matrix._32);

		vPoints[i].x = tempX;

		vPoints[i].y = tempY;

	}
}




inline void C2DMatrix::transformVector2Ds(Vector2D & vPoint)
{
	double tempX = (m_Matrix._11*vPoint.x) + (m_Matrix._21*vPoint.y) + (m_Matrix._31);

	double tempY = (m_Matrix._12*vPoint.x) + (m_Matrix._22*vPoint.y) + (m_Matrix._32);

	vPoint.x = tempX;

	vPoint.y = tempY;

}

inline void C2DMatrix::translate(double x, double y)
{
	Matrix mat;

	mat._11 = 1; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = 1; mat._23 = 0;

	mat._31 = x;    mat._32 = y;    mat._33 = 1;

	//and multiply
	matrixMultiply(mat);

}

