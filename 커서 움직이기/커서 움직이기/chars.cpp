#include "chars.h"

chars::chars()
:radius(20)
, drag_set(false)
, color(RGB(0, 0, 0))
, hOwner(NULL)
, drag_select(false)
, moving(false)
{
}

chars::~chars()
{
}

void chars::attach(HWND h){

	hOwner = h;

}


void chars::draw(HDC hdc){

	Rect rc;
	::GetClientRect(hOwner, &rc);

	
	if (drag_select)
		color = RGB(255, 0, 0);
	else
		color = RGB(0, 0, 0);

	HBRUSH hBrush = ::CreateSolidBrush(color);
	HBRUSH hOldBrush = ::Select(hdc, hBrush);


	::Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
	

	::Select(hdc, hOldBrush);
	::DeleteObject(hBrush);

	if (drag_set){


		SelectObject(hdc, GetStockObject(NULL_BRUSH)); //드래그 사각형 안에 투명처리
		//이건 헤제 안해도되나

		::Rectangle(hdc, drag_start.x, drag_start.y, drag_end.x + 1, drag_end.y + 1);
	

		
	}

	

}
void chars::input(DWORD tick){

	Point ptMouse;
	::GetCursorPos(&ptMouse);
	ptMouse = ptMouse.ToClient(hOwner);

	

		// 누르고
	if (!drag_set && ::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		
		::GetCursorPos(&drag_start); // 사각형 첫번째 부분 left + top
		drag_start = drag_start.ToClient(hOwner); // 창안에 좌표로 바꿈
		drag_set = true; // 드래그 시작 true

		drag_select = false; // 드래그 시작되면 현재 드래그된거 취소 (리셋)

	}

	
	// 누르는 도중이면 사각형 right bottom 값을 현재 마우스좌표값으로 계속바까줌
	if(drag_set && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000)
	{

		::GetCursorPos(&ptMouse);  // temp 용 마우스 좌표
		drag_end = ptMouse.ToClient(hOwner); // 시작점은 그대로고  temp용 좌표를 사각형 right bottom 으로 계속입력

		
	}

	// 드래그 사각형 없애는 부분
	if (drag_set && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0x8000)
	{
		drag_set = false;

	}
	


	if ((::GetAsyncKeyState(VK_RBUTTON) & 0x8000) == 0x8000)
	{

		if (drag_select){ // 선택된놈만 계산
			//브리즈햄 성님 알고리즘
			::GetCursorPos(&goal_center);
			goal_center = goal_center.ToClient(hOwner);

			moving_center.x = goal_center.x - center.x;
			moving_center.y = goal_center.y - center.y;


			if (abs(abs(goal_center.x) - abs(center.x)) >= abs((abs(goal_center.y) - abs(center.y)))){
				// 좌~우
			
				if (iNX < 0)
					;
				//좌 이미지

				else
					;
					//우 이미지

			}
			else{
				//상 ~ 하
				if (iNY < 0)
					;
				else
					;

			}

			iNX = (moving_center.x > 0) ? speed : ((moving_center.x == 0) ? 0 : -speed);
			iNY = (moving_center.y > 0) ? speed : ((moving_center.y == 0) ? 0 : -speed);

			moving_center.x = abs(moving_center.x);
			moving_center.y = abs(moving_center.y);

			iError = 0;

			if (moving_center.x > moving_center.y)
				iDistance = moving_center.x;
			else
				iDistance = moving_center.y;
			iCount = abs(iDistance / iNX);

			moving = true;
		}
	}



	Rect dragRc;
	Rect switch_dragRc;
	if (drag_start.x > drag_end.x && drag_start.y < drag_end.y)
		dragRc = Rect(drag_end.x , drag_start.y ,drag_start.x , drag_end.y);

	else if (drag_start.x < drag_end.x && drag_start.y > drag_end.y)
		dragRc = Rect(drag_start.x, drag_end.y, drag_end.x, drag_start.y);

	else if (drag_start.x > drag_end.x && drag_start.y > drag_end.y)
		dragRc = Rect(drag_end,drag_start);


	else dragRc = Rect(drag_start, drag_end);


	// 드래그안에 현재 케릭터 center가 안에있는지없는지 확인함

	//right x가 left.x보다 더작으면 스위칭해야됨//

	if (PtInRect(&dragRc, center)){

		//확인해서 선택되면 선택됬다고 트루를 줌
		drag_select = true;

	}


}


void chars::update(DWORD tick ){


	
	// 브리즌헴 성님의 알고리즘에 선택받은자들만 계산
	if (moving){

		if (moving_center.x > moving_center.y){

			iCount--;
			if (iCount <= 0)
				moving = false;

			iError += moving_center.y;

			if (iError >= iDistance){
				iError -= moving_center.x ;
				center.y += iNY;
			}

			center.x += iNX;
		}
		else
		{
			iCount--;
			if (iCount <= 0)
				moving = false;

			iError += moving_center.x;

			if (iError >= iDistance){
				iError -= moving_center.y;
				center.x += iNX;
			}

			center.y += iNY;
		}
	}
	
}

void chars::set_center(const Point & pt){

	center = pt;
	
}


void chars::set_color(const COLORREF & c){

	color = c;

}


void chars::set_drag(const bool & b){

	drag_set = b;
}

void chars::set_direction(const Vector& v){

	move_direction = v;

}


void chars::set_moves(const Point& m){

	moves = m;
}

void chars::set_speed(const double& s){

	speed = s;

}


Point chars::get_goal() const{

	return goal_center;

}







//확인용 함수

int chars::get_iNX() const{

	return iNX;
}

int chars::get_iNY() const{

	return iNY;

}
int chars::get_iDistance() const{

	return iDistance;
}
int chars::get_iCount() const{

	return iCount;

}
int chars::get_iError() const{

	return iError;
}


Point chars::get_moving_center() const{


	return moving_center;

}