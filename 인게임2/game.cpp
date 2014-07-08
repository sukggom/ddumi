#include "game.h"

//해당 ui 에서 input에서 모든 조작을 다할거같음

//필요한정보는 매니저를 통해 다빼오면됨

//이게 나중에 최상위 FSM에 의해 다뤄지면 그때가서 고칩시당


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

	//그냥 ui 배경
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
				if (it == jt) //같으면 비교안함
				{
				}
				else //다를때
				{

					if (it->second->get_team() != 3 && jt->second->get_team() != 3) //둘다 멤버가 후보가아닐때
					{

						if (it->second->GetPosition().y > jt->second->GetPosition().y) // 비교해서 내가크면 count증가
						{
							count++;
						} //비교끝나고
					}//멤버끝나고
				}//다른거끝나고

			}//jt가 끝나고

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

		//	character_inform_box = it->second; //케릭터정보를 받아오고

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


	//걍노가다 확인용
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


	// 누르고
	if (!drag_loading && ::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{


		::GetCursorPos(&drag_start); // 사각형 첫번째 부분 left + top
		drag_start = drag_start.ToClient(hOwner); // 창안에 좌표로 바꿈
		drag_end = drag_start;
		drag_loading = true; // 드래그 시작 true
		attack_choice = false;

		std::map<int, character_inform*>::iterator it;

		for (it = manager_depot->begin(); it->first != 10; it++){

			it->second->set_drag_select(false);


		}

	}


	// 누르는 도중이면 사각형 right bottom 값을 현재 마우스좌표값으로 계속바까줌
	if (drag_loading  && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000)
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



	// 드래그 사각형 없애는 부분
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
	{//포문시작
		for (jt = manager_depot->begin(); jt != manager_depot->end(); jt++){

			if (it->second->get_team() != 3 && jt->second->get_team() != 3){

				if (it != jt){


					if (it->second->get_CHP() > 0){ //살아있는지 먼저 체크
						int radius = 12;
						Rect myRect; // 케릭터 
						Rect myRangeRect; // 케릭터 공격범위
						myRect = Rect(my->GetPosition().x - radius, my->GetPosition().y - radius, my->GetPosition().x + radius, my->GetPosition().y + radius);
						myRangeRect = Rect(my->GetPosition().x - 120, my->GetPosition().y - 120, my->GetPosition().x + 120, my->GetPosition().y + 120);



						Rect targetRect; // 적케릭터
						targetRect = Rect(
							target->GetPosition().x - radius, target->GetPosition().y - radius,
							target->GetPosition().x + radius, target->GetPosition().y + radius);

						Rect targetRangeRect; //적케릭터범위
						targetRangeRect = Rect(
							target->GetPosition().x - 80, target->GetPosition().y - 80,
							target->GetPosition().x + 80, target->GetPosition().y + 80);


						Rect fc;
						//공격하는곳
						fc = Rect(my->GetPosition().x + (my->GetDirection().x * 10) - 16,
							my->GetPosition().y + (my->GetDirection().y * 10) - 16,
							my->GetPosition().x + (my->GetDirection().x * 10) + 16,
							my->GetPosition().y + (my->GetDirection().y * 10) + 16);



						if (::PtInRect(&myRangeRect, target->GetPosition())){//공격범위 조사
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


								if (::PtInRect(&targetRect, my->GetPosition())){ // 케릭터가 겹쳤을때 랜덤좌표를 주고 빼냄
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

								if (::PtInRect(&targetRect, my->GetPosition())){ // 케릭터가 겹쳤을때 랜덤좌표를 주고 빼냄
									if (my->get_CHP() > 0 && target->get_CHP() > 0){
										my->SetPosition(Vector(my->GetPosition().x - (rand() % 25 - 15), my->GetPosition().y - (rand() % 25 - 15)));
									}
								}

							}

						}
					}
				}
			}

		} //jt 시작부분
	
	}      //충돌체크 첫포문
}
					// 다양한방법을 정해야한다

					// a* 알고리즘을 사용할수없다면?

					/* 이동하는 Rect가 있고 Rect가 다른Rect 즉 (target) 이라거정한다면 에 target 침범했다면 어떤방향이든간에
					target렉트에서 빠져나올수있도록 어떻게든 빠져나가게 하는방법이다
					즉 유닛이 뭉치긴하지만 이동이끝나고나면 서로 퍼지는경우


					*/

					/* 처음꺼랑비슷한데 이동하다가 렉트끼리 겹처버리면 그냥 서로 팅겨내는방법이다
						그럼 전투를 어떻게할것인가의문제임..

						*/

					/*
					다른방법은 내가가려는길에 Rect를 하나만들고 이동하면서 Rect가 겹치는지 체크한다
					RecT가 겹쳐서 타겟의 징표(아군 적군 ) 등을 확인하고 아군일 경우 벡터의 이동방향을 잠시바꾼다


					*/


			//가는방향을 검색해보고 있으면 멈춰야지 더하면안되니까
		

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
				//////////상하
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
				//////////상하
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