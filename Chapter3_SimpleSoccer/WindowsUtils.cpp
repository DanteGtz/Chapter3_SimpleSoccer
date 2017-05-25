#include <windows.h>

#include "WindowUtils.h"
#include "Vector2D.h"
#include "utils.h"
#include "Stream_Utility_Functions.h"

//Definition of the WU member methods


//-----------------> Cambia el estado del menu <----------------//

//Cambia el estado del item menu dados el identificador de
//un segundo item, el estado deseado, y el HWND del menu
//del usuario
void changeMenuState(HWND hwnd, UINT menuItem, UINT state)
{
	MENUITEMINFO mi;

	mi.cbSize = sizeof(MENUITEMINFO);
	mi.fMask = MIIM_STATE;
	mi.fState = state;

	SetMenuItemInfo(GetMenu(hwnd), menuItem, false, &mi);
	DrawMenuBar(hwnd);
}



//-----------------> Cambia el estado del menu <----------------//

//Si b es verdaderdo, la variable menuItem se verifica
//se deja sin verificar
void checkMenuItemAppropriately(HWND hwnd, UINT menuItem, bool b)
{
	if (b)
	{
		changeMenuState(hwnd, menuItem, MFS_CHECKED);
	}
	else
	{
		changeMenuState(hwnd, menuItem, MFS_UNCHECKED);
	}
}



//-----------------> checa la longitud del buffer <----------------//

//Esta funcion es un remplazo del metodo StringCchLength que encontramos
//en el SDK de la plataforma windows. Puedes visitar MSDN para mas
//detalles. Solo se utiliza para checar las cadenas de la barra de 
//herramientas
bool checkBufferLength(char* buff, int maxLength, unsigned int& bufferLength)
{
	std::string s = ttos(buff);

	bufferLength = s.length();

	if (bufferLength > maxLength)
	{
		bufferLength = 0; 
		return false;
	}

	return true;
}


void errorBox(std::string& msg)
{
	MessageBox(NULL, msg.c_str(), "Error", MB_OK);
}

void errorBox(char* msg)
{
	MessageBox(NULL, msg, "Error", MB_OK);
}


//Obtiene las coordenadas del cursor relativo a la ventana
//activa
Vector2D getClientCursorPosition()
{
	POINT MousePos;

	GetCursorPos(&MousePos);

	ScreenToClient(GetActiveWindow(), &MousePos);

	return POINTtoVector(MousePos);
}


Vector2D getClientCursorPosition(HWND hwnd)
{
	POINT MousePos;

	GetCursorPos(&MousePos);

	ScreenToClient(hwnd, &MousePos);

	return POINTtoVector(MousePos);
}



//Estos metodos abren el common dialog box para obtener un 
//nombre de archivo
void fileInitialize(HWND hwnd,
	OPENFILENAME& ofn,
	const std::string& defaultFileTypeDescription,
	const std::string& defaultFileExtension)
{
	std::string filter = defaultFileTypeDescription + '\0' + "*." + defaultFileExtension + '\0' +
		"All Files (*.*)" + '\0' + "*.*" + '\0' + '\0';

	static TCHAR szFilter[255];

	for (unsigned int i = 0; i<filter.size(); ++i)
	{
		szFilter[i] = filter.at(i);
	}

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = NULL;				//Establece las funcione Open y Close
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;          //Establece las funcione Open y Close
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = 0;						//Establece las funcione Open y Close
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = defaultFileExtension.c_str();
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

}



BOOL fileOpenDlg(HWND               hwnd,
	PTSTR              pstrFileName,
	PTSTR              pstrTitleName,
	const std::string& defaultFileTypeDescription,
	const std::string& defaultFileExtension)
{
	OPENFILENAME ofn;

	fileInitialize(hwnd, ofn, defaultFileTypeDescription, defaultFileExtension);

	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	return GetOpenFileName(&ofn);
}

BOOL fileSaveDlg(HWND               hwnd,
	PTSTR              pstrFileName,
	PTSTR              pstrTitleName,
	const std::string& defaultFileTypeDescription,
	const std::string& defaultFileExtension)
{
	OPENFILENAME ofn;
	fileInitialize(hwnd, ofn, defaultFileTypeDescription,
		defaultFileExtension);

	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	return GetSaveFileName(&ofn);
}


//-----------------> redimensiona la ventana <----------------//

//Funcion que al invocarse cambia las medidas de la pantalla
//especificas por los argumentos
void resizeWindow(HWND hwnd, int cx, int cy)
{
	//Esta ventana tiene menu? Si es asi, la bandera
	//se activa
	HMENU hwndMenu = GetMenu(hwnd);
	bool bMenu = false;
	if (hwndMenu) bMenu = true;

	//Crea unrectangulo con las medidas deseadas
	RECT DesiredSize;
	DesiredSize.left = 0;
	DesiredSize.top = 0;
	DesiredSize.right = cx;
	DesiredSize.bottom = cy;

	//Determina las medidas de la pantalla, deseadas
	//por el usuario
	AdjustWindowRectEx(&DesiredSize,
		WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
		bMenu,
		NULL);

	//Redimentsiona la ventana para que encaje
	SetWindowPos(hwnd,
		NULL,
		GetSystemMetrics(SM_CXSCREEN) / 2 - cx / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - cy / 2,
		DesiredSize.right,
		DesiredSize.bottom,
		SWP_NOZORDER);
}



//-----------------> obtiene la altura de la pantalla<----------------//

int  getWindowHeight(HWND hwnd)
{
	if (hwnd == 0) return 0;

	RECT windowRect;

	GetWindowRect(hwnd, &windowRect);

	return windowRect.bottom - windowRect.top;
}



//-----------------> obtiene el ancho de la ventana <----------------//

int  getWindowWidth(HWND hwnd)
{
	if (hwnd == 0) return 0;

	RECT windowRect;

	GetWindowRect(hwnd, &windowRect);

	return windowRect.right - windowRect.left;
}