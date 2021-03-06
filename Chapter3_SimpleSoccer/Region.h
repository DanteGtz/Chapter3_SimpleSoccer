#pragma once
#ifndef REGION_H
#define REGION_H
//Defines a rectangular region.

#include <math.h>

#include "Vector2D.h"
#include "Cgdi.h"
#include "utils.h"
#include "Stream_Utility_Functions.h"


class Region
{
public:

	enum region_modifier 
	{ 
		HALF_SIZE,
		NORMAL 
	};

protected:

	double        m_dTop;
	double        m_dLeft;
	double        m_dRight;
	double        m_dBottom;

	double        m_dWidth;
	double        m_dHeight;

	Vector2D     m_vCenter;

	int          m_iID;

public:

	Region() :m_dTop(0), m_dBottom(0), m_dLeft(0), m_dRight(0)
	{}


	Region(double left, double top, double right,
		double bottom, int id = -1) 
			:m_dTop(top),
			m_dRight(right),
			m_dLeft(left),
			m_dBottom(bottom),
			m_iID(id)
	{
		//Calcula el centro de la region
		m_vCenter = Vector2D((left + right) * 0.5, (top + bottom) * 0.5);

		m_dWidth = fabs(right - left);
		m_dHeight = fabs(bottom - top);
	}

	virtual ~Region() {}

	virtual inline void     render(bool ShowID)const;


	//returns true if the given position lays inside the region. The
	//region modifier can be used to contract the region bounderies
	inline bool     Inside(Vector2D pos, region_modifier r)const;

	//returns a vector representing a random location
	//within the region
	inline Vector2D GetRandomPosition()const;

	//-------------------------------
	double     Top()const { return m_dTop; }
	double     Bottom()const { return m_dBottom; }
	double     Left()const { return m_dLeft; }
	double     Right()const { return m_dRight; }
	double     Width()const { return fabs(m_dRight - m_dLeft); }
	double     Height()const { return fabs(m_dTop - m_dBottom); }
	double     Length()const { return max(Width(), Height()); }
	double     Breadth()const { return min(Width(), Height()); }

	Vector2D  Center()const { return m_vCenter; }
	int       ID()const { return m_iID; }

};



inline Vector2D Region::GetRandomPosition()const
{
	return Vector2D(randInRange(m_dLeft, m_dRight),
		randInRange(m_dTop, m_dBottom));
}

inline bool Region::Inside(Vector2D pos, region_modifier r = NORMAL)const
{
	if (r == NORMAL)
	{
		return ((pos.x > m_dLeft) && (pos.x < m_dRight) &&
			(pos.y > m_dTop) && (pos.y < m_dBottom));
	}
	else
	{
		const double marginX = m_dWidth * 0.25;
		const double marginY = m_dHeight * 0.25;

		return ((pos.x >(m_dLeft + marginX)) && (pos.x < (m_dRight - marginX)) &&
			(pos.y >(m_dTop + marginY)) && (pos.y < (m_dBottom - marginY)));
	}

}

inline void Region::render(bool ShowID = 0)const
{
	gdi->HollowBrush();
	gdi->GreenPen();
	gdi->rect(m_dLeft, m_dTop, m_dRight, m_dBottom);

	if (ShowID)
	{
		gdi->textColor(Cgdi::GREEN);
		gdi->textAtPos(Center(), ttos(ID()));
	}
}


#endif
