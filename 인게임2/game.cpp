#include "game.h"

//해당 ui 에서 input에서 모든 조작을 다할거같음

//필요한정보는 매니저를 통해 다빼오면됨

//이게 나중에 최상위 FSM에 의해 다뤄지면 그때가서 고칩시당


in_game::in_game()
{

	
}
in_game::~in_game()
{
}


void in_game::attach(HWND hWnd){

	hOwner = hWnd;

}

void in_game::draw(HDC hdc){

	Rect rc;
	::GetClientRect(hOwner, &rc);

	if (hBitmap == NULL) return;
	::GetCursorPos(&ptMouse);
	ptMouse = ptMouse.ToClient(hOwner);
	Rect inform_box = Rect(ptMouse.x , ptMouse.y , ptMouse.x +80, ptMouse.y + 80);


	::GetCursorPos(&inform_Mouse);
	inform_Mouse = inform_Mouse.ToClient(hOwner);
	Rect click_rc = Rect(ptMouse.x - 15, ptMouse.y - 15, ptMouse.x + 15, ptMouse.y + 15);



	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	//그냥 ui 배경
	::StretchBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC,
		rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);

	std::map<int, character_inform*>::iterator it;

	for (it = manager_depot->begin(); it->first != 10; it++){


		if (::PtInRect(&click_rc, it->second->GetPosition())){

			find_key = it->first;

			character_inform_box = it->second; //케릭터정보를 받아오고

			test1 = it->second->get_drag_select();

			
		}

		it->second->Draw(hdc);

	}

	if (drag_loading)
	{
		HDC hDragDC = ::CreateCompatibleDC(hdc);
		HBITMAP hDragBitmap = ::CreateCompatibleBitmap(hdc, rcBox.width(), rcBox.height());
		HBITMAP hDragOld = ::Select(hDragDC, hDragBitmap);

		HBRUSH hBrush = ::CreateSolidBrush(RGB(100, 100, 255));
		HBRUSH hOldBrush = ::Select(hDragDC, hBrush);

		HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(50, 50, 205));
		HPEN hOldPen = ::Select(hDragDC, hPen);

		::Rectangle(hDragDC, 0, 0,
			rcBox.width(), rcBox.height());

		::Select(hDragDC, hOldPen);
		::DeleteObject(hPen);

		::Select(hDragDC, hOldBrush);
		::DeleteObject(hBrush);

		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 120;
		bf.AlphaFormat = 0;

		::GdiAlphaBlend(hdc, rcBox.left, rcBox.top,
			rcBox.width(), rcBox.height(),
			hDragDC, 0, 0, rcBox.width(), rcBox.height(),
			bf);

		::Select(hDragDC, hDragOld);
		::DeleteObject(hDragBitmap);
		::DeleteDC(hDragDC);
	}


	//////////////
	



	//걍노가다 확인용
	std::wostringstream oss;
	
	oss << _T("it first : ") << find_key << std::endl << _T("drag: ") << test1 << std::endl << _T("col :") << test2;
		
	::DrawText(hdc, oss.str().c_str(), -1, &inform_box, DT_TOP);




	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);




}


void in_game::Input(DWORD tick){

	Point ptMouse;
	::GetCursorPos(&ptMouse);
	ptMouse = ptMouse.ToClient(hOwner);



	// 누르고
	if (!drag_loading && ::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{

		::GetCursorPos(&drag_start); // 사각형 첫번째 부분 left + top
		drag_start = drag_start.ToClient(hOwner); // 창안에 좌표로 바꿈
		drag_end = drag_start;
		drag_loading = true; // 드래그 시작 true

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){

			it->second->set_drag_select(false);
		

		}

	}


	// 누르는 도중이면 사각형 right bottom 값을 현재 마우스좌표값으로 계속바까줌
	if (drag_loading && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000)
	{

		::GetCursorPos(&drag_end);  // temp 용 마우스 좌표
		drag_end = drag_end.ToClient(hOwner); // 시작점은 그대로고  temp용 좌표를 사각형 right bottom 으로 계속입력



		if (drag_start.x > drag_end.x)
		{
			rcBox.left = drag_end.x;
			rcBox.right = drag_start.x;
		}
		else
		{
			rcBox.left = drag_start.x;
			rcBox.right = drag_end.x;
		}

		if (drag_start.y > drag_end.y)
		{
			rcBox.top = drag_end.y;
			rcBox.bottom = drag_start.y;
		}
		else
		{
			rcBox.top = drag_start.y;
			rcBox.bottom = drag_end.y;
		}

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){

			//현재 스테이트의 값은 주소를가져옴 즉 케릭터내부의주소

			if (::PtInRect(&rcBox, it->second->GetPosition())){

				it->second->set_drag_select(true);
				
			}
			else{
	
				it->second->set_drag_select(false);
			
			}
			//}



		}
	}

	// 드래그 사각형 없애는 부분
	if (drag_loading && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0x8000)
	{
		drag_loading = false;

	}


	if ((::GetAsyncKeyState(VK_RBUTTON) & 0x8000) == 0x8000)
	{
		::GetCursorPos(&ptDest);
		ptDest = ptDest.ToClient(hOwner);

		DestBox = Rect(ptDest, Size(20, 20));

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){
			if (it->second->get_drag_select())
			{
				it->second->SetDestination(Vector(rand() % DestBox.width() + DestBox.left,
					rand() % DestBox.height() + DestBox.top));
			}
		}
	}
}



void in_game::Update(DWORD tick){


	std::map<int, character_inform*>::iterator it, jt;


	for (it = manager_depot->begin(); it->first != 10; it++){
		it->second->Update(tick);
	}


	for (it = manager_depot->begin(); it->first != 10; it++)
	{
		for (jt = it, jt++; jt->first != 10; jt++){

			


			Rect myRect;
			myRect = Rect(it->second->GetPosition().x - 16, it->second->GetPosition().y - 16, it->second->GetPosition().x + 16, it->second->GetPosition().y + 16);

			Rect targetRect;
			targetRect = Rect(
			jt->second->GetPosition().x - 16, jt->second->GetPosition().y - 16,
			jt->second->GetPosition().x + 16, jt->second->GetPosition().y + 16);


			if (myRect.left < targetRect.right){
				if (::PtInRect(&myRect, Point(jt->second->GetPosition().x + 16, jt->second->GetPosition().y))){
					// 오른쪽 박스에 왼쪽박스가 오른쪽으로 와서 충돌했을때 ㅁ >> |ㅁ|

					jt->second->SetPosition(Vector(jt->second->GetPosition().x - jt->second->GetDirection().x, jt->second->GetPosition().y ));

				}
				if (::PtInRect(&targetRect, Point(it->second->GetPosition().x - 16, it->second->GetPosition().y))){
					//왼쪽에 위치한 myRect박스에 오른쪽 target박스가 <<왼쪽으로 와서 충돌했을때 |ㅁ| << ㅁ
					
					it->second->SetPosition(Vector(jt->second->GetPosition().x - it->second->GetDirection().x, jt->second->GetPosition().y));


				}
				


			

				//}
				//	
				//	
				//if (!(myRect.right < targetRect.left)){

				//}

				//
				//if (!(myRect.top > targetRect.bottom)){

				//}
				//		
				//if (!(myRect.bottom < targetRect.top)){
				//
				//
				//}



			}
		}
	}

}

void in_game::Load_game_map(LPCTSTR szFileName){

	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);

	rcSrc = Rect(0, 0, bm.bmWidth, bm.bmHeight);

	rcDest = rcSrc;

}