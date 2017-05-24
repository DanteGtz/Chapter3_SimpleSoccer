#pragma once
#ifndef CGDI_H
#define CGDI_H
//Carries out all the graphic interface of our application
#include <windows.h>
#include <string>
#include <vector>
#include <cassert>

#include "Vector2D.h"

//-----------------> Define algunos colores <----------------//
const int NumColors = 15;

const COLORREF colors[NumColors] =
{
	RGB(255,0,0),
	RGB(0,0,255),
	RGB(0,255,0),
	RGB(0,0,0),
	RGB(255,200,200),
	RGB(200,200,200),
	RGB(255,255,0),
	RGB(255,170,0),
	RGB(255,0,170),
	RGB(133,90,0),
	RGB(255,255,255),
	RGB(0, 100, 0),        
	RGB(0, 255, 255),      
	RGB(200, 200, 200),     
	RGB(255, 230, 230)      
};


//Ahora llamar a la clase es mas facil
#define gdi Cgdi::instance()

class Cgdi
{
public:

	int NumPenColors()const { return NumColors; }

	//Enumera los colores
	enum
	{
		RED,
		BLUE,
		GREEN,
		BLACK,
		PINK,
		GREY,
		YELLOW,
		ORANGE,
		PURPLE,
		BROWN,
		WHITE,
		DARK_GREEN,
		LIGHT_BLUE,
		LIGHT_GREY,
		LIGHT_PINK,
		HOLLOW
	};



private:

	HPEN m_OldPen;

	//Todos los lapices
	HPEN   m_BlackPen;
	HPEN   m_WhitePen;
	HPEN   m_RedPen;
	HPEN   m_GreenPen;
	HPEN   m_BluePen;
	HPEN   m_GreyPen;
	HPEN   m_PinkPen;
	HPEN   m_OrangePen;
	HPEN   m_YellowPen;
	HPEN   m_PurplePen;
	HPEN   m_BrownPen;

	HPEN   m_DarkGreenPen;
	HPEN   m_LightBluePen;
	HPEN   m_LightGreyPen;
	HPEN   m_LightPinkPen;

	HPEN   m_ThickBlackPen;
	HPEN   m_ThickWhitePen;
	HPEN   m_ThickRedPen;
	HPEN   m_ThickGreenPen;
	HPEN   m_ThickBluePen;

	HBRUSH m_OldBrush;

	//Todas las brochas
	HBRUSH  m_RedBrush;
	HBRUSH  m_GreenBrush;
	HBRUSH  m_BlueBrush;
	HBRUSH  m_GreyBrush;
	HBRUSH  m_BrownBrush;
	HBRUSH  m_YellowBrush;
	HBRUSH  m_OrangeBrush;

	HBRUSH  m_LightBlueBrush;
	HBRUSH  m_DarkGreenBrush;

	HDC    m_hdc;

	//Construccion debe ser privado
	Cgdi();

	//Los constructores copia, asignacion deben ser privados
	Cgdi(const Cgdi&);
	Cgdi& operator=(const Cgdi&);

public:

	~Cgdi();

	static Cgdi* instance();

	void BlackPen() { if (m_hdc) { SelectObject(m_hdc, m_BlackPen); } }
	void WhitePen() { if (m_hdc) { SelectObject(m_hdc, m_WhitePen); } }
	void RedPen() { if (m_hdc) { SelectObject(m_hdc, m_RedPen); } }
	void GreenPen() { if (m_hdc) { SelectObject(m_hdc, m_GreenPen); } }
	void BluePen() { if (m_hdc) { SelectObject(m_hdc, m_BluePen); } }
	void GreyPen() { if (m_hdc) { SelectObject(m_hdc, m_GreyPen); } }
	void PinkPen() { if (m_hdc) { SelectObject(m_hdc, m_PinkPen); } }
	void YellowPen() { if (m_hdc) { SelectObject(m_hdc, m_YellowPen); } }
	void OrangePen() { if (m_hdc) { SelectObject(m_hdc, m_OrangePen); } }
	void PurplePen() { if (m_hdc) { SelectObject(m_hdc, m_PurplePen); } }
	void BrownPen() { if (m_hdc) { SelectObject(m_hdc, m_BrownPen); } }

	void DarkGreenPen() { if (m_hdc) { SelectObject(m_hdc, m_DarkGreenPen); } }
	void LightBluePen() { if (m_hdc) { SelectObject(m_hdc, m_LightBluePen); } }
	void LightGreyPen() { if (m_hdc) { SelectObject(m_hdc, m_LightGreyPen); } }
	void LightPinkPen() { if (m_hdc) { SelectObject(m_hdc, m_LightPinkPen); } }

	void ThickBlackPen() { if (m_hdc) { SelectObject(m_hdc, m_ThickBlackPen); } }
	void ThickWhitePen() { if (m_hdc) { SelectObject(m_hdc, m_ThickWhitePen); } }
	void ThickRedPen() { if (m_hdc) { SelectObject(m_hdc, m_ThickRedPen); } }
	void ThickGreenPen() { if (m_hdc) { SelectObject(m_hdc, m_ThickGreenPen); } }
	void ThickBluePen() { if (m_hdc) { SelectObject(m_hdc, m_ThickBluePen); } }

	void BlackBrush() { if (m_hdc)SelectObject(m_hdc, GetStockObject(BLACK_BRUSH)); }
	void WhiteBrush() { if (m_hdc)SelectObject(m_hdc, GetStockObject(WHITE_BRUSH)); }
	void HollowBrush() { if (m_hdc)SelectObject(m_hdc, GetStockObject(HOLLOW_BRUSH)); }
	void GreenBrush() { if (m_hdc)SelectObject(m_hdc, m_GreenBrush); }
	void RedBrush() { if (m_hdc)SelectObject(m_hdc, m_RedBrush); }
	void BlueBrush() { if (m_hdc)SelectObject(m_hdc, m_BlueBrush); }
	void GreyBrush() { if (m_hdc)SelectObject(m_hdc, m_GreyBrush); }
	void BrownBrush() { if (m_hdc)SelectObject(m_hdc, m_BrownBrush); }
	void YellowBrush() { if (m_hdc)SelectObject(m_hdc, m_YellowBrush); }
	void LightBlueBrush() { if (m_hdc)SelectObject(m_hdc, m_LightBlueBrush); }
	void DarkGreenBrush() { if (m_hdc)SelectObject(m_hdc, m_DarkGreenBrush); }
	void OrangeBrush() { if (m_hdc)SelectObject(m_hdc, m_OrangeBrush); }



	//SIEMPRE se debe llamar antes de comenzar a pintar
	void StartDrawing(HDC hdc)
	{
		assert(m_hdc == NULL);

		m_hdc = hdc;

		//Llama al lapiz actual
		m_OldPen = (HPEN)SelectObject(hdc, m_BlackPen);
		//Lo Selecciona de nuevo
		SelectObject(hdc, m_OldPen);

		m_OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		SelectObject(hdc, m_OldBrush);
	}



	//SIEMPRE se debe llamar antes de terminar a pintar
	void StopDrawing(HDC hdc)
	{
		assert(hdc != NULL);

		SelectObject(hdc, m_OldPen);
		SelectObject(hdc, m_OldBrush);

		m_hdc = NULL;

	}


	//-----------------> Texto <----------------//

	void TextAtPos(int x, int y, const std::string &s)
	{
		TextOut(m_hdc, x, y, s.c_str(), s.size());
	}

	void TextAtPos(double x, double y, const std::string &s)
	{
		TextOut(m_hdc, (int)x, (int)y, s.c_str(), s.size());
	}

	void TextAtPos(Vector2D pos, const std::string &s)
	{
		TextOut(m_hdc, (int)pos.x, (int)pos.y, s.c_str(), s.size());
	}

	void TransparentText() { SetBkMode(m_hdc, TRANSPARENT); }

	void OpaqueText() { SetBkMode(m_hdc, OPAQUE); }

	void TextColor(int color) { assert(color < NumColors); SetTextColor(m_hdc, colors[color]); }
	void TextColor(int r, int g, int b) { SetTextColor(m_hdc, RGB(r, g, b)); }


	//-----------------> Pixeles <----------------//
	void DrawDot(Vector2D pos, COLORREF color)
	{
		SetPixel(m_hdc, (int)pos.x, (int)pos.y, color);
	}

	void DrawDot(int x, int y, COLORREF color)
	{
		SetPixel(m_hdc, x, y, color);
	}

	//-----------------> Dibujar lineas <----------------//

	void Line(Vector2D from, Vector2D to)
	{
		MoveToEx(m_hdc, (int)from.x, (int)from.y, NULL);
		LineTo(m_hdc, (int)to.x, (int)to.y);
	}

	void Line(int a, int b, int x, int y)
	{
		MoveToEx(m_hdc, a, b, NULL);
		LineTo(m_hdc, x, y);
	}

	void Line(double a, double b, double x, double y)
	{
		MoveToEx(m_hdc, (int)a, (int)b, NULL);
		LineTo(m_hdc, (int)x, (int)y);
	}



	void PolyLine(const std::vector<Vector2D>& points)
	{
		//Se asegura de tener al menos dos puntos
		if (points.size() < 2) return;

		MoveToEx(m_hdc, (int)points[0].x, (int)points[0].y, NULL);

		for (unsigned int p = 1; p<points.size(); ++p)
		{
			LineTo(m_hdc, (int)points[p].x, (int)points[p].y);
		}
	}

	void LineWithArrow(Vector2D from, Vector2D to, double size)
	{
		Vector2D norm = vec2DNormalize(to - from);

		//Calcula donde esta anclada la flecha
		Vector2D CrossingPoint = to - (norm * size);

		//Calcula dos puntos mas para dibujar la cabeza de la flecha
		Vector2D ArrowPoint1 = CrossingPoint + (norm.perp() * 0.4f * size);
		Vector2D ArrowPoint2 = CrossingPoint - (norm.perp() * 0.4f * size);

		//dibuja la linea
		MoveToEx(m_hdc, (int)from.x, (int)from.y, NULL);
		LineTo(m_hdc, (int)CrossingPoint.x, (int)CrossingPoint.y);

		//Dibuja la flecha con el color actual
		POINT p[3];

		p[0] = VectorToPOINT(ArrowPoint1);
		p[1] = VectorToPOINT(ArrowPoint2);
		p[2] = VectorToPOINT(to);

		SetPolyFillMode(m_hdc, WINDING);
		Polygon(m_hdc, p, 3);

	}

	void Cross(Vector2D pos, int diameter)
	{
		Line((int)pos.x - diameter, (int)pos.y - diameter, (int)pos.x + diameter, (int)pos.y + diameter);
		Line((int)pos.x - diameter, (int)pos.y + diameter, (int)pos.x + diameter, (int)pos.y - diameter);
	}

	//-----------------> Metodos para dibujar fig geometricas <----------------//

	void Rect(int left, int top, int right, int bot)
	{
		Rectangle(m_hdc, left, top, right, bot);
	}

	void Rect(double left, double top, double right, double bot)
	{
		Rectangle(m_hdc, (int)left, (int)top, (int)right, (int)bot);
	}



	void ClosedShape(const std::vector<Vector2D> &points)
	{
		MoveToEx(m_hdc, (int)points[0].x, (int)points[0].y, NULL);

		for (unsigned int p = 1; p<points.size(); ++p)
		{
			LineTo(m_hdc, (int)points[p].x, (int)points[p].y);
		}

		LineTo(m_hdc, (int)points[0].x, (int)points[0].y);
	}


	void Circle(Vector2D pos, double radius)
	{
		Ellipse(m_hdc,
			(int)(pos.x - radius),
			(int)(pos.y - radius),
			(int)(pos.x + radius + 1),
			(int)(pos.y + radius + 1));
	}

	void Circle(double x, double y, double radius)
	{
		Ellipse(m_hdc,
			(int)(x - radius),
			(int)(y - radius),
			(int)(x + radius + 1),
			(int)(y + radius + 1));
	}

	void Circle(int x, int y, double radius)
	{
		Ellipse(m_hdc,
			(int)(x - radius),
			(int)(y - radius),
			(int)(x + radius + 1),
			(int)(y + radius + 1));
	}


	void SetPenColor(int color)
	{
		assert(color < NumColors);

		switch (color)
		{
		case BLACK:
			BlackPen(); return;
		case WHITE:
			WhitePen(); return;
		case RED: 
			RedPen(); return;
		case GREEN:
			GreenPen(); return;
		case BLUE: 
			BluePen(); return;
		case PINK: 
			PinkPen(); return;
		case GREY: 
			GreyPen(); return;
		case YELLOW: 
			YellowPen(); return;
		case ORANGE: 
			OrangePen(); return;
		case PURPLE: 
			PurplePen(); return;
		case BROWN:
			BrownPen(); return;
		case LIGHT_BLUE:
			LightBluePen(); return;
		case LIGHT_GREY: 
			LightGreyPen(); return;
		case LIGHT_PINK:
			LightPinkPen(); return;
		}//Fin del switch
	}
};

#endif