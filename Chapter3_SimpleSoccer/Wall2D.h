#pragma once
#ifndef WALL_H
#define WALL_H
//The wall2D class

#include "Cgdi.h"
#include "Vector2D.h"
#include <fstream>


class Wall2D
{
protected:

	Vector2D    m_vA;
	Vector2D	m_vB;
	Vector2D	m_vN;

	void CalculateNormal()
	{
		Vector2D temp = vec2DNormalize(m_vB - m_vA);

		m_vN.x = -temp.y;
		m_vN.y = temp.x;
	}

public:

	Wall2D() {}

	Wall2D(Vector2D A, Vector2D B) 
		:m_vA(A), m_vB(B)
	{
		CalculateNormal();
	}

	Wall2D(Vector2D A, Vector2D B, Vector2D N)
		:m_vA(A), m_vB(B), m_vN(N)
	{ }

	Wall2D(std::ifstream& in) { read(in); }

	virtual void Render(bool RenderNormals = false)const
	{
		gdi->line(m_vA, m_vB);

		//render the normals if rqd
		if (RenderNormals)
		{
			int MidX = (int)((m_vA.x + m_vB.x) / 2);
			int MidY = (int)((m_vA.y + m_vB.y) / 2);

			gdi->line(MidX, MidY, (int)(MidX + (m_vN.x * 5)), (int)(MidY + (m_vN.y * 5)));
		}
	}

	Vector2D from()const { return m_vA; }
	void     setFrom(Vector2D v) { m_vA = v; CalculateNormal(); }

	Vector2D to()const { return m_vB; }
	void     setTo(Vector2D v) { m_vB = v; CalculateNormal(); }

	Vector2D normal()const { return m_vN; }
	void     setNormal(Vector2D n) { m_vN = n; }

	Vector2D center()const { return (m_vA + m_vB) / 2.0; }

	std::ostream& Wall2D::write(std::ostream& os)const
	{
		os << std::endl;
		os << from() << ",";
		os << to() << ",";
		os << normal();
		return os;
	}

	void read(std::ifstream& in)
	{
		double x, y;

		in >> x >> y;
		setFrom(Vector2D(x, y));

		in >> x >> y;
		setTo(Vector2D(x, y));

		in >> x >> y;
		setNormal(Vector2D(x, y));
	}

};

#endif