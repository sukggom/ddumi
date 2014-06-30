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


		SelectObject(hdc, GetStockObject(NULL_BRUSH)); //�巡�� �簢�� �ȿ� ����ó��
		//�̰� ���� ���ص��ǳ�

		::Rectangle(hdc, drag_start.x, drag_start.y, drag_end.x + 1, drag_end.y + 1);
	

		
	}

	

}
void chars::input(DWORD tick){

	Point ptMouse;
	::GetCursorPos(&ptMouse);
	ptMouse = ptMouse.ToClient(hOwner);

	

		// ������
	if (!drag_set && ::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		
		::GetCursorPos(&drag_start); // �簢�� ù��° �κ� left + top
		drag_start = drag_start.ToClient(hOwner); // â�ȿ� ��ǥ�� �ٲ�
		drag_set = true; // �巡�� ���� true

		drag_select = false; // �巡�� ���۵Ǹ� ���� �巡�׵Ȱ� ��� (����)

	}

	
	// ������ �����̸� �簢�� right bottom ���� ���� ���콺��ǥ������ ��ӹٱ���
	if(drag_set && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000)
	{

		::GetCursorPos(&ptMouse);  // temp �� ���콺 ��ǥ
		drag_end = ptMouse.ToClient(hOwner); // �������� �״�ΰ�  temp�� ��ǥ�� �簢�� right bottom ���� ����Է�

		
	}

	// �巡�� �簢�� ���ִ� �κ�
	if (drag_set && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0x8000)
	{
		drag_set = false;

	}
	


	if ((::GetAsyncKeyState(VK_RBUTTON) & 0x8000) == 0x8000)
	{

		if (drag_select){ // ���õȳ� ���
			//�긮���� ���� �˰���
			::GetCursorPos(&goal_center);
			goal_center = goal_center.ToClient(hOwner);

			moving_center.x = goal_center.x - center.x;
			moving_center.y = goal_center.y - center.y;


			if (abs(abs(goal_center.x) - abs(center.x)) >= abs((abs(goal_center.y) - abs(center.y)))){
				// ��~��
			
				if (iNX < 0)
					;
				//�� �̹���

				else
					;
					//�� �̹���

			}
			else{
				//�� ~ ��
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


	// �巡�׾ȿ� ���� �ɸ��� center�� �ȿ��ִ��������� Ȯ����

	//right x�� left.x���� �������� ����Ī�ؾߵ�//

	if (PtInRect(&dragRc, center)){

		//Ȯ���ؼ� ���õǸ� ���É�ٰ� Ʈ�縦 ��
		drag_select = true;

	}


}


void chars::update(DWORD tick ){


	
	// �긮���� ������ �˰��� ���ù����ڵ鸸 ���
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







//Ȯ�ο� �Լ�

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