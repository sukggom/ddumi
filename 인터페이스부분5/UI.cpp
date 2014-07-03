#include "UI.h"

//해당 ui 에서 input에서 모든 조작을 다할거같음

//필요한정보는 매니저를 통해 다빼오면됨

//이게 나중에 최상위 FSM에 의해 다뤄지면 그때가서 고칩시당


ui::ui()
:character_inform_box(NULL)
, inform_box_select(false)
, character_drag(false)
, character_select(false)
, character_drag_change(false)
, find_key(NULL)
, temp_Position(0, 0)
, temp_key(NULL)
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

	Rect inform_box;

	if (hBitmap == NULL) return;

	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	//그냥 ui 배경
	::StretchBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC,
		rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);

	
	//여따가그림여

	
	std::map<INT,character_inform*>::iterator it;

	//이변수들은 그냥 일단 임의적으로 뿌려서 테스트하기위해 만듬 언제든 사라질수있음
	int i = 0;
	int j = 1;
	int k = 0;
	int h = 0;

	for (it = manager_depot->begin(); it != manager_depot->end(); it++){



		if (i == 5){
			i = 0;
			j++;
		}
		if (k == 10){

			h = 50;
		}
		//노가다식 계산으로 일단 좌료에다가 주전과 후보멤버를 따로 뿌려줌

		if (it->first == find_key && character_drag_change){
			it->second->SetPosition(ptMouse);
			it->second->Draw(hdc);
		}
		else{
			it->second->SetPosition(Point(50 + 75 * i, 50 * j + h));
			it->second->Draw(hdc); // 해당 state 가 가지고있는동작(SEE_STATE)일것임 그것을 그려줌
		}
		i++;
		k++;

	}

	if (character_select){ //현재 케릭터_정보_박스안에 정보가들어갔다면 검색으로 찾았다는얘기임
		//즉 케릭터정보와 현재 케릭터를 재대로 클릭이됬는지 두가지를 다 true 일때만 그려줌

		::Rectangle(hdc, ptMouse.x + 20, ptMouse.y + 20, ptMouse.x + 220, ptMouse.y + 220); //정보를 보여주는 상자를 현재마우스좌표 >>>>좀 옆에다가 그림
		inform_box = Rect(ptMouse.x + 20, ptMouse.y + 20, ptMouse.x + 220, ptMouse.y + 220);



		//걍노가다 확인용
		std::wostringstream oss;
		oss << std::endl << std::endl << std::endl << std::endl
			<< _T(" LV : ") << character_inform_box->get_LV() << _T(" HP : ") << character_inform_box->get_HP() << std::endl
			<< _T(" ATK : ") << character_inform_box->get_ATK() << _T(" DEF : ") << character_inform_box->get_DEF() << std::endl
			<< _T(" ATR : ") << character_inform_box->get_ATR() << _T(" SPD : ") << character_inform_box->get_SPD() << std::endl
			<< _T(" CLS : ") << character_inform_box->get_CLS() << std::endl
			<< _T(" 변경에들어감 : ") << test1 << std::endl
			<< _T(" 변경에들어감 : ") << test1 << std::endl
			<< _T(" 변경에들어감 : ") << test1 << std::endl;


		/*<< _T(" temp  x: ") << temp_Position.x << _T(" temp  y : ") << temp_Position.y << std::endl
		<< _T(" it x : ") << manager_depot->find(find_key)->second->getPosition().x
		<< _T(" it y : ") << manager_depot->find(find_key)->second->getPosition().y;
		*/



		::DrawText(hdc, oss.str().c_str(), -1, &inform_box, DT_CENTER);


	}



	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);




}


void ui::Input(DWORD tick){




	::GetCursorPos(&ptMouse);
	ptMouse = ptMouse.ToClient(hOwner);
	Rect click_rc = Rect(ptMouse.x - 15, ptMouse.y - 15, ptMouse.x + 15, ptMouse.y + 15);
	//클릭범위를 알수있는 렉트를 하나만들고 현재 마우스좌표부터 반지름15만큼 그려서 케릭터중심이랑 일치하는지 확인함




	std::map<INT, character_inform*>::iterator it;

	if (!character_drag_change){
		for (it = manager_depot->begin(); it != manager_depot->end(); it++){

			//케릭터 매니저로부터 모든케릭터의 좌표를 찾아봄 현재 클릭한범위에 케릭터가 잡히는게있는지

			if (::PtInRect(&click_rc, it->second->getPosition())){

				find_key = it->first;

				character_inform_box = it->second; //케릭터정보를 받아오고


			}
		}
	}

	///////////////////////////////////////
	/// 마우스움직임을 따라다니면서 chracter_inform_box에다가  마우스와 현제 it의 센터가 중첩됬을때
	/// character_inform_box에 정보가 들어갈것이다.
	/// 그러면 일단은 inform box가 있다는 조건으로 걸어준뒤에
	/// 현재마우스가 지금 charac_inform_box 에 있는지 검색해봐서 현재 마우스위치가 그 케릭터위에있지않다면 케릭터를 누르고있지않다는걸로
	/// character_select = false; 로 바꿔준다
	////////////////////////////////////////
	if (character_inform_box){
		if (!::PtInRect(&click_rc, character_inform_box->getPosition())){


			character_select = false;


		}
		else{

			character_select = true;
		}
	}


	///////////////////////////////////////
	/// 이제 VK 왼쪽버튼이 눌러졌을때 현제 마우스위치와 charac_inform_box 위치랑 같은지 비교해보고
	/// 현재마우스가 해당 케릭터 좌표 위에올라와있다면
	/// 드래그시작이라고 선언한다
	//////////////////////////////
	if (character_select && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000){

		
		character_drag_change = true;
		// temp 에 다들어감
		

		
	}

	if (character_drag_change && character_select && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0x8000){

		
		character_drag_change = false;

		std::map<INT, character_inform*>::iterator it;


		for (it = manager_depot->begin(); it != manager_depot->end(); it++){

			if (find_key == it->first){
				return;
			}
			else if (manager_depot->find(find_key) == manager_depot->end()){
				return;
			}
			
			else{
				Point temp_Point = it->second->getPosition();//

				Rect tempRc;
				tempRc = Rect(temp_Point.x - 15, temp_Point.y - 15, temp_Point.x + 15, temp_Point.y + 15);

				if (::PtInRect(&tempRc, ptMouse)){

					

					test1 = char_man_depot.change_key(it->first, find_key);

					break;
				}
			
			}
			
		} //for종료지점
	}
}




void ui::Update(DWORD tick){

	

}

void ui::Load_interface_map(LPCTSTR szFileName){

	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);

	rcSrc = Rect(0, 0, bm.bmWidth, bm.bmHeight);

	rcDest = rcSrc;

}