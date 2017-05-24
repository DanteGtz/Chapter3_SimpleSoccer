#include "Cgdi.h"

//The instance method, cto and dto  of the Cgdi class
//-----------------> Define algunos colores <----------------//

//Esta clase es un singleton
Cgdi* Cgdi::instance()
{
	static Cgdi instance;
	return &instance;
}

Cgdi::Cgdi()
{
	m_BlackPen = CreatePen(PS_SOLID, 1, colors[BLACK]);
	m_WhitePen = CreatePen(PS_SOLID, 1, colors[WHITE]);
	m_RedPen = CreatePen(PS_SOLID, 1, colors[RED]);
	m_GreenPen = CreatePen(PS_SOLID, 1, colors[GREEN]);
	m_BluePen = CreatePen(PS_SOLID, 1, colors[BLUE]);
	m_GreyPen = CreatePen(PS_SOLID, 1, colors[GREY]);
	m_PinkPen = CreatePen(PS_SOLID, 1, colors[PINK]);
	m_YellowPen = CreatePen(PS_SOLID, 1, colors[YELLOW]);
	m_OrangePen = CreatePen(PS_SOLID, 1, colors[ORANGE]);
	m_PurplePen = CreatePen(PS_SOLID, 1, colors[PURPLE]);
	m_BrownPen = CreatePen(PS_SOLID, 1, colors[BROWN]);

	m_DarkGreenPen = CreatePen(PS_SOLID, 1, colors[DARK_GREEN]);

	m_LightBluePen = CreatePen(PS_SOLID, 1, colors[LIGHT_BLUE]);
	m_LightGreyPen = CreatePen(PS_SOLID, 1, colors[LIGHT_GREY]);
	m_LightPinkPen = CreatePen(PS_SOLID, 1, colors[LIGHT_PINK]);

	m_ThickBlackPen = CreatePen(PS_SOLID, 2, colors[BLACK]);
	m_ThickWhitePen = CreatePen(PS_SOLID, 2, colors[WHITE]);
	m_ThickRedPen = CreatePen(PS_SOLID, 2, colors[RED]);
	m_ThickGreenPen = CreatePen(PS_SOLID, 2, colors[GREEN]);
	m_ThickBluePen = CreatePen(PS_SOLID, 2, colors[BLUE]);

	m_GreenBrush = CreateSolidBrush(colors[GREEN]);
	m_RedBrush = CreateSolidBrush(colors[RED]);
	m_BlueBrush = CreateSolidBrush(colors[BLUE]);
	m_GreyBrush = CreateSolidBrush(colors[GREY]);
	m_BrownBrush = CreateSolidBrush(colors[BROWN]);
	m_YellowBrush = CreateSolidBrush(colors[YELLOW]);
	m_LightBlueBrush = CreateSolidBrush(RGB(0, 255, 255));
	m_DarkGreenBrush = CreateSolidBrush(colors[DARK_GREEN]);
	m_OrangeBrush = CreateSolidBrush(colors[ORANGE]);

	m_hdc = NULL;
}

Cgdi::~Cgdi()
{
	DeleteObject(m_BlackPen);
	DeleteObject(m_WhitePen);
	DeleteObject(m_RedPen);
	DeleteObject(m_GreenPen);
	DeleteObject(m_BluePen);
	DeleteObject(m_GreyPen);
	DeleteObject(m_PinkPen);
	DeleteObject(m_OrangePen);
	DeleteObject(m_YellowPen);
	DeleteObject(m_PurplePen);
	DeleteObject(m_BrownPen);
	DeleteObject(m_OldPen);

	DeleteObject(m_DarkGreenPen);

	DeleteObject(m_LightBluePen);
	DeleteObject(m_LightGreyPen);
	DeleteObject(m_LightPinkPen);

	DeleteObject(m_ThickBlackPen);
	DeleteObject(m_ThickWhitePen);
	DeleteObject(m_ThickRedPen);
	DeleteObject(m_ThickGreenPen);
	DeleteObject(m_ThickBluePen);

	DeleteObject(m_GreenBrush);
	DeleteObject(m_RedBrush);
	DeleteObject(m_BlueBrush);
	DeleteObject(m_OldBrush);
	DeleteObject(m_GreyBrush);
	DeleteObject(m_BrownBrush);
	DeleteObject(m_LightBlueBrush);
	DeleteObject(m_YellowBrush);
	DeleteObject(m_DarkGreenBrush);
	DeleteObject(m_OrangeBrush);

}

