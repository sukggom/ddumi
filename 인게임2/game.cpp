#include "game.h"

//�ش� ui ���� input���� ��� ������ ���ҰŰ���

//�ʿ��������� �Ŵ����� ���� �ٻ������

//�̰� ���߿� �ֻ��� FSM�� ���� �ٷ����� �׶����� ��Ĩ�ô�


in_game::in_game()
:update_dt(200), insert_dt(0), r_clickup(false), attack_choice(false), hold_choice(false)
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
	Rect inform_box = Rect(ptMouse.x, ptMouse.y, ptMouse.x + 80, ptMouse.y + 80);


	::GetCursorPos(&inform_Mouse);
	inform_Mouse = inform_Mouse.ToClient(hOwner);
	Rect click_rc = Rect(ptMouse.x - 15, ptMouse.y - 15, ptMouse.x + 15, ptMouse.y + 15);



	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	//�׳� ui ���
	::GdiTransparentBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC,
		rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), RGB(0,0,0));

	//::StretchBlt(hdc, rcDest.left, rcDest.top,
	//	rcDest.width(), rcDest.height(),
	//	hBitmapDC,
	//	rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);

	std::map<int, character_inform*>::iterator it, jt, tt;


	int arr[20];
	
	for (it = manager_depot->begin(); it != manager_depot->end(); it++)
	{
		if (it->second->get_team() == 3){

		}
		else{
			int count = 0;
			for (jt = manager_depot->begin(); jt != manager_depot->end(); jt++)
			{
				if (it == jt) //������ �񱳾���
				{
				}
				else //�ٸ���
				{

					if (it->second->get_team() != 3 && jt->second->get_team() != 3) //�Ѵ� ����� �ĺ����ƴҶ�
					{

						if (it->second->GetPosition().y > jt->second->GetPosition().y) // ���ؼ� ����ũ�� count����
						{
							count++;
						} //�񱳳�����
					}//���������
				}//�ٸ��ų�����

			}//jt�� ������

			arr[count] = it->first;
		}

	}
	
	for (int i = 0; i< 20; i++)
	{
		if(manager_depot->find(arr[i])->second->get_CHP() > 0)
		manager_depot->find(arr[i])->second->Draw(hdc);
	}


		//count = 0;
		//if (::PtInRect(&click_rc, it->second->GetPosition())){


		//	
		//	find_key = it->first;

		//	character_inform_box = it->second; //�ɸ��������� �޾ƿ���

		//	test1 = it->second->get_drag_select();

		//}
		/*for (jt = manager_depot->begin(); jt != manager_depot->end(); jt++){
			if (it->second->get_team() != 3 && jt->second->get_team() != 3){

				if (it->second->get_CHP() > 0){
					it->second->Draw(hdc);
				}
				
				if (it == jt){

				}

				else if (it->second->GetPosition().y > jt->second->GetPosition().y){
					count++;
				}



			}

			

		}*/

		

	/*for (int i = 0; i < 20; i++){
		int a = arr[i];
		
		if (manager_depot->find(a)->second->get_CHP() > 0  && manager_depot->find(a)->second->get_team() != 3){
			manager_depot->find(a)->second->Draw(hdc);
		}

	}*/


	//////////////////////////////////////////////////




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
	

	for (it = manager_depot->begin(); it != manager_depot->end(); it++)
	{

		if (it->second->get_team() == 2){
			it->second->set_drag_select(true);
		}

		if (it->second->get_team() != 3){

			if (it->second->get_drag_select()){

				if (it->second->get_CHP() > 0){
					COLORREF color;

					if (it->second->get_team() == 2){
						color = RGB(255, 0, 0);
					}
					else{
						color = RGB(0, 255, 0);

					}


					::Rectangle(hdc, it->second->GetPosition().x - 16, it->second->GetPosition().y - 30, it->second->GetPosition().x + 16, it->second->GetPosition().y - 35);
					HBRUSH hBrush = ::CreateSolidBrush(color);
					HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

					::Rectangle(hdc, it->second->GetPosition().x - 16, it->second->GetPosition().y - 30, it->second->GetPosition().x - 16 + (2 * 16) * (it->second->get_CHP()) / it->second->get_HP(), it->second->GetPosition().y - 35);

					::SelectObject(hdc, hOldBrush);
					::DeleteObject(hBrush);
				}
				
			}

		}
	}


	//���밡�� Ȯ�ο�
	std::wostringstream oss;
	
	oss << _T("it first : ") << manager_depot->find(0)->second->get_attack_dt() << std::endl << _T("drag: ") << test1 << std::endl << _T("col :") << test2;
		
	::DrawText(hdc, oss.str().c_str(), -1, &inform_box, DT_TOP);




	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);




}


void in_game::Input(DWORD tick){

	Point ptMouse;
	::GetCursorPos(&ptMouse);
	ptMouse = ptMouse.ToClient(hOwner);


	if (attack_choice && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{

		::GetCursorPos(&ptDest);
		ptDest = ptDest.ToClient(hOwner);

		DestBox = Rect(ptDest, Size(20, 20));

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){
			if (it->second->get_drag_select())
			{

				it->second->set_attack_state(true);
				it->second->set_hold_state(false);


				it->second->SetDestination(Vector(rand() % DestBox.width() + DestBox.left,
					rand() % DestBox.height() + DestBox.top));
			}
		}

	}


	// ������
	if (!drag_loading && ::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{


		::GetCursorPos(&drag_start); // �簢�� ù��° �κ� left + top
		drag_start = drag_start.ToClient(hOwner); // â�ȿ� ��ǥ�� �ٲ�
		drag_end = drag_start;
		drag_loading = true; // �巡�� ���� true
		attack_choice = false;

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){

			it->second->set_drag_select(false);


		}

	}


	// ������ �����̸� �簢�� right bottom ���� ���� ���콺��ǥ������ ��ӹٱ���
	if (drag_loading  && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000)
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



	if (::GetAsyncKeyState(0x41) & 0x8000){

		attack_choice = true;

	}



	

	if (::GetAsyncKeyState(0x48) & 0x8000){

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){
			if (it->second->get_drag_select())
			{

				it->second->set_attack_state(false);
				it->second->set_hold_state(true);


				it->second->SetDestination(Vector(rand() % DestBox.width() + DestBox.left,
					rand() % DestBox.height() + DestBox.top));
			}
		}

	}



	// �巡�� �簢�� ���ִ� �κ�
	if (drag_loading && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0x8000)
	{
		drag_loading = false;

	}




	if ((::GetAsyncKeyState(VK_RBUTTON) & 0x8000) == 0x8000){

		r_clickup = true;

	}


	if (r_clickup &&(::GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0x8000)
	{
		r_clickup = false;
		
			::GetCursorPos(&ptDest);
			ptDest = ptDest.ToClient(hOwner);

			DestBox = Rect(ptDest, Size(20, 20));

			std::map<int, character_inform*>::iterator it;

			for (it = manager_depot->begin(); it->first != 10; it++){
				if (it->second->get_drag_select())
				{
					it->second->set_attack_state(false);
					it->second->set_hold_state(false);

					it->second->SetDestination(Vector(rand() % DestBox.width() + DestBox.left,
						rand() % DestBox.height() + DestBox.top));
				}
			}

	}

}


void in_game::Update(DWORD tick){

	std::map<int, character_inform*>::iterator it, jt;
#define my it->second
#define	target jt->second

	insert_dt = tick;
	update_dt = 300;


	for (it = manager_depot->begin(); it != manager_depot->end(); it++){

		if (it->second->get_team() != 3){
			it->second->set_ipdt(insert_dt);
			it->second->set_attack_dt(insert_dt);
			it->second->Update(tick);
		}


	}


	for (it = manager_depot->begin(); it != manager_depot->end(); it++)
	{//��������
		for (jt = manager_depot->begin(); jt != manager_depot->end(); jt++){

			if (it->second->get_team() != 3 && jt->second->get_team() != 3){

				if (it != jt){


					if (it->second->get_CHP() > 0){ //����ִ��� ���� üũ
						int radius = 12;
						Rect myRect; // �ɸ��� 
						Rect myRangeRect; // �ɸ��� ���ݹ���
						myRect = Rect(my->GetPosition().x - radius, my->GetPosition().y - radius, my->GetPosition().x + radius, my->GetPosition().y + radius);
						myRangeRect = Rect(my->GetPosition().x - 120, my->GetPosition().y - 120, my->GetPosition().x + 120, my->GetPosition().y + 120);



						Rect targetRect; // ���ɸ���
						targetRect = Rect(
							target->GetPosition().x - radius, target->GetPosition().y - radius,
							target->GetPosition().x + radius, target->GetPosition().y + radius);

						Rect targetRangeRect; //���ɸ��͹���
						targetRangeRect = Rect(
							target->GetPosition().x - 80, target->GetPosition().y - 80,
							target->GetPosition().x + 80, target->GetPosition().y + 80);


						Rect fc;
						//�����ϴ°�
						fc = Rect(my->GetPosition().x + (my->GetDirection().x * 10) - 16,
							my->GetPosition().y + (my->GetDirection().y * 10) - 16,
							my->GetPosition().x + (my->GetDirection().x * 10) + 16,
							my->GetPosition().y + (my->GetDirection().y * 10) + 16);



						if (::PtInRect(&myRangeRect, target->GetPosition())){//���ݹ��� ����
							if (my->get_attack_state()){
								if (my->get_team() != target->get_team() && update_dt < my->get_indt() && my->get_CHP() > 0 && target->get_CHP() > 0){


									my->reset_indt();
									my->SetDestination(target->GetPosition());
								}



								if (::PtInRect(&fc, target->GetPosition())){

									if (my->get_CHP() > 0 && target->get_CHP() > 0){

										if (my->get_team() != target->get_team()){

											if (update_dt < my->get_attack_dt()){
												my->reset_atdt();
												target->health(it->second->get_ATK());


											}
										}

										Vector temp;

										temp = my->GetDestination();

										my->SetPosition((Vector(my->GetPosition().x - (my->GetDirection().x * 3),
											my->GetPosition().y - (my->GetDirection().y * 3))));

									}

								}


								if (::PtInRect(&targetRect, my->GetPosition())){ // �ɸ��Ͱ� �������� ������ǥ�� �ְ� ����
									if (my->get_CHP() > 0 && target->get_CHP() > 0){
										my->SetPosition(Vector(my->GetPosition().x - (rand() % 25 - 15), my->GetPosition().y - (rand() % 25 - 15)));
									}
								}

							}

							if (my->get_hold_state()){




							}

							if (my->get_hold_state() == false && my->get_attack_state() == false){

								if (::PtInRect(&myRect, target->GetPosition())){

									if (my->get_CHP() > 0 && target->get_CHP() > 0){
										my->SetPosition(Vector(my->GetPosition().x - (rand() % 25 - 15), my->GetPosition().y - (rand() % 25 - 15)));


									}
								}

								if (::PtInRect(&targetRect, my->GetPosition())){ // �ɸ��Ͱ� �������� ������ǥ�� �ְ� ����
									if (my->get_CHP() > 0 && target->get_CHP() > 0){
										my->SetPosition(Vector(my->GetPosition().x - (rand() % 25 - 15), my->GetPosition().y - (rand() % 25 - 15)));
									}
								}

							}

						}
					}
				}
			}

		} //jt ���ۺκ�
	
	}      //�浹üũ ù����
}
					// �پ��ѹ���� ���ؾ��Ѵ�

					// a* �˰����� ����Ҽ����ٸ�?

					/* �̵��ϴ� Rect�� �ְ� Rect�� �ٸ�Rect �� (target) �̶�����Ѵٸ� �� target ħ���ߴٸ� ������̵簣��
					target��Ʈ���� �������ü��ֵ��� ��Ե� ���������� �ϴ¹���̴�
					�� ������ ��ġ�������� �̵��̳������� ���� �����°��


					*/

					/* ó����������ѵ� �̵��ϴٰ� ��Ʈ���� ��ó������ �׳� ���� �ðܳ��¹���̴�
						�׷� ������ ����Ұ��ΰ��ǹ�����..

						*/

					/*
					�ٸ������ ���������±濡 Rect�� �ϳ������ �̵��ϸ鼭 Rect�� ��ġ���� üũ�Ѵ�
					RecT�� ���ļ� Ÿ���� ¡ǥ(�Ʊ� ���� ) ���� Ȯ���ϰ� �Ʊ��� ��� ������ �̵������� ��ùٲ۴�


					*/


			//���¹����� �˻��غ��� ������ ������� ���ϸ�ȵǴϱ�
		

				///////////myRect  right       <<<>>>>    targetRect  left//////////
				//if (myRect.right + my->GetDirection().x < targetRect.left){

				//	my->set_collision(true);
				//	my->SetPosition(Vector(my->GetPosition().x - my->GetDirection().x, my->GetPosition().y));
				//	my->SetDestination(my->GetPosition());
				//	my->SetDirection(Vector());


				//}

				///////////targetRect  right       <<<>>>>   myRect left//////////

				//else if (targetRect.right > myRect.left + my->GetDirection().x){

				//	my->set_collision(true);
				//	my->SetDestination(my->GetPosition());
				//	my->SetDirection(Vector());

				//}

				///////////////
				///////  my 
				////////bottom
				//////////����
				/////////////////
				////// top
				//////target/////
				/////////////

				//else if (myRect.bottom + my->GetDirection().y > targetRect.top){

				//	my->set_collision(true);
				//	my->SetDestination(my->GetPosition());
				//	my->SetDirection(Vector());

				//}

				///////////////
				///////  target
				////////bottom
				//////////����
				/////////////////
				////// top
				////// my/////
				/////////////

				//else if (myRect.top + my->GetDirection().y > targetRect.bottom){

				//	my->set_collision(true);
				//	my->SetDestination(my->GetPosition());
				//	my->SetDirection(Vector());

				//}

				//else{

				//	my->set_collision(false);

				//}
				//if (!(myRect.left > targetRect.right || myRect.right < targetRect.left ||
				//	myRect.top > targetRect.bottom || myRect.bottom < targetRect.top)){

				//	my->SetPosition(my->GetPosition() - my->GetDirection());
				//	my->SetPosition(my->GetPosition() - my->GetDirection());
				//	target->SetPosition(target->GetPosition() - target->GetDirection());

				//	target->SetPosition(target->GetPosition() - target->GetDirection());

				//	my->SetDirection(Vector());

				//	target->SetDirection(Vector());

				//	my->SetDestination(my->GetPosition());

				//	target->SetDestination(target->GetPosition());



				//}


void in_game::Load_game_map(LPCTSTR szFileName){

	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);

	rcSrc = Rect(0, 0, bm.bmWidth, bm.bmHeight);

	rcDest = rcSrc;

}