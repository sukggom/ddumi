#include <windows.h>
#include "BaseType.h"
#include "Utility.hpp"
#include <map>
#include <sstream> // wostringstream
#include "character_inform_manager.h"

#define manager_depot char_man_depot.get_depot()

class ui
{

public:
	ui();
	~ui();

	void attach(HWND);

	void draw(HDC);

	void Input(DWORD);
	void Update(DWORD);
	
	
	void Load_interface_map(LPCTSTR szFileName);



private:

	HBITMAP hBitmap;
	Rect rcSrc;
	Rect rcDest;

	HWND hOwner;

	Point ptMouse;

	character_inform* character_inform_box;

	bool inform_box_select;

};
