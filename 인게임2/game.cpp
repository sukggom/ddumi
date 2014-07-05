#include "game.h"

//�ش� ui ���� input���� ��� ������ ���ҰŰ���

//�ʿ��������� �Ŵ����� ���� �ٻ������

//�̰� ���߿� �ֻ��� FSM�� ���� �ٷ����� �׶����� ��Ĩ�ô�


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

	//�׳� ui ���
	::StretchBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC,
		rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);

	std::map<int, character_inform*>::iterator it;

	for (it = manager_depot->begin(); it->first != 10; it++){


		if (::PtInRect(&click_rc, it->second->GetPosition())){

			find_key = it->first;

			character_inform_box = it->second; //�ɸ��������� �޾ƿ���

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
	



	//���밡�� Ȯ�ο�
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



	// ������
	if (!drag_loading && ::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{

		::GetCursorPos(&drag_start); // �簢�� ù��° �κ� left + top
		drag_start = drag_start.ToClient(hOwner); // â�ȿ� ��ǥ�� �ٲ�
		drag_end = drag_start;
		drag_loading = true; // �巡�� ���� true

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){

			it->second->set_drag_select(false);
		

		}

	}


	// ������ �����̸� �簢�� right bottom ���� ���� ���콺��ǥ������ ��ӹٱ���
	if (drag_loading && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000)
	{

		::GetCursorPos(&drag_end);  // temp �� ���콺 ��ǥ
		drag_end = drag_end.ToClient(hOwner); // �������� �״�ΰ�  temp�� ��ǥ�� �簢�� right bottom ���� ����Է�



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

			//���� ������Ʈ�� ���� �ּҸ������� �� �ɸ��ͳ������ּ�

			if (::PtInRect(&rcBox, it->second->GetPosition())){

				it->second->set_drag_select(true);
				
			}
			else{
	
				it->second->set_drag_select(false);
			
			}
			//}



		}
	}

	// �巡�� �簢�� ���ִ� �κ�
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
					// ������ �ڽ��� ���ʹڽ��� ���������� �ͼ� �浹������ �� >> |��|

					jt->second->SetPosition(Vector(jt->second->GetPosition().x - jt->second->GetDirection().x, jt->second->GetPosition().y ));

				}
				if (::PtInRect(&targetRect, Point(it->second->GetPosition().x - 16, it->second->GetPosition().y))){
					//���ʿ� ��ġ�� myRect�ڽ��� ������ target�ڽ��� <<�������� �ͼ� �浹������ |��| << ��
					
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