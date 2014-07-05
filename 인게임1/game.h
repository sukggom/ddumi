#include <windows.h>
#include "BaseType.h"
#include "Utility.hpp"
#include <map>
#include <sstream> // wostringstream
#include "character_inform_manager.h"

#define manager_depot char_man_depot.get_depot()

class in_game
{

public:
	in_game();
	~in_game();

	void attach(HWND);

	void draw(HDC);

	void Input(DWORD);
	void Update(DWORD);


	void Load_game_map(LPCTSTR szFileName);



private:

	HBITMAP hBitmap;
	Rect rcSrc;
	Rect rcDest;
	
	Point inform_Mouse;
	
	Rect rcBox;
	Rect DestBox;
	

	HWND hOwner;

	Point ptMouse;
	Point drag_start;
	Point drag_end;
	Point temp_Position;
	Point ptDest;

	int test1;
	int find_key;
	character_inform* character_inform_box;


	bool drag_loading;

	


};
