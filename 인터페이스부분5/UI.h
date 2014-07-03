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
	Point temp_Position;

	character_inform* character_inform_box;

	int find_key;
	int temp_key;
	int test1;

	bool inform_box_select; // 드래그 아닌상태에서 케릭터를 클릭한 불값

	bool character_drag; // 케릭터 움직일때 드래그설정

	bool character_select;

	bool character_drag_change;

};
