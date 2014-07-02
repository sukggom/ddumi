#include "UI.h"


ui::ui()
{


}
ui::~ui()
{


}


void ui::attach(HWND hWnd){

	hOwner = hWnd;

}

void ui::draw(HDC hdc){

	Rect rc;
	::GetClientRect(hOwner, &rc);

	LONG x = 50, y = 50;
	LONG tt = 60;
	LONG sizes = 25;

	Point rcCenter = Point(x, y);

	::Rectangle(hdc, rc.left + 10, rc.top + 10, rc.right - 10, rc.bottom - 10);


	std::map<INT,character_inform*>::iterator it;

	

	/*
	char_man_depot.get_inform(0)->Draw(hdc);

	char_man_depot.get_inform(1)->Draw(hdc);


	char_man_depot.get_inform(2)->Draw(hdc);

*/

	for (it = manager_depot->begin(); it != manager_depot->end(); it++){

	
		it->second->Draw(hdc);


	}
	

	/*for (int i = 0; i < 2; i++){
		for (int j = 0; j < 5; j++){
			::Rectangle(hdc, (rcCenter.x + (tt* j)) - sizes, (rcCenter.y + (tt * i)) - sizes, (rcCenter.x + (tt * j)) + sizes, (rcCenter.y + (tt * i)) + sizes);

		}
	}*/

}

