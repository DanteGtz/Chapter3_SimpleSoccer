#pragma once
#ifndef WINDOW_UTILS_H
#define WINDOW_UTILS_H
#pragma warning (disable:4786)

//An event controller for the console application

#include <windows.h>
#include <string>

struct Vector2D;

//Variable macro que detecta si una tecla es presionada
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

#define WAS_KEY_PRESSED(vk_code) ((GetKeyState(vk_code) & 0x8000) != 0)
#define IS_KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) != 0)

//Esta funcion se llama para refrescar la pantalla
inline void redrawWindow(HWND hwnd, bool redrawBackGround = true)
{
	InvalidateRect(hwnd, NULL, redrawBackGround);
	UpdateWindow(hwnd);
}

//Se llama cada vez que haya que refrescar la pantalla del cliente
inline void RedrawWindowRect(HWND hwnd, bool redrawBackGround, RECT& redrawArea)
{
	InvalidateRect(hwnd, &redrawArea, redrawBackGround);
	UpdateWindow(hwnd);
}

//Cambia los estados de item menu dados un identificador item,
//el estado deseado y el HWND(pantalla) del menu del usuario
void changeMenuState(HWND hwnd, UINT menuItem, UINT state);

//Si b es verdaderdo, la variable menuItem se verifica
//se deja sin verificar
void checkMenuItemAppropriately(HWND hwnd, UINT menuItem, bool b);

//Esta funcion es un remplazo del metodo StringCchLength que encontramos
//en el SDK de la plataforma windows. Puedes visitar MSDN para mas
//detalles. Solo se utiliza para checar las cadenas de la barra de 
//herramientas
bool checkBufferLength(char* buff, int MaxLength, unsigned int& BufferLength);

void errorBox(std::string& msg);
void errorBox(char* msg);

//Obtiene las coordenadas del cursor relativo a la ventana
//activa
Vector2D getClientCursorPosition();

//Obtiene las coordenadas del cursor relativo a la ventana
//activa 
Vector2D getClientCursorPosition(HWND hwnd);


//Estos metodos abren el common dialog box para obtener un 
//nombre de archivo
void fileInitialize(HWND hwnd,
	OPENFILENAME& ofn,
	const std::string& defaultFileTypeDescription,
	const std::string& defaultFileExtension);

BOOL fileOpenDlg(HWND               hwnd,
	PTSTR              pstrFileName,
	PTSTR              pstrTitleName,
	const std::string& defaultFileTypeDescription,
	const std::string& defaultFileExtension);

BOOL fileSaveDlg(HWND hwnd,
	PTSTR pstrFileName,
	PTSTR pstrTitleName,
	const std::string& defaultFileTypeDescription,
	const std::string& defaultFileExtension);

//Funcion que al invocarse cambia las medidas de la pantalla
//especificas por los argumentos
void resizeWindow(HWND hwnd, int cx, int cy);

int  getWindowHeight(HWND hwnd);
int  getWindowWidth(HWND hwnd);




#endif