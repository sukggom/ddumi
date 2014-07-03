#include "UI.h"

//�ش� ui ���� input���� ��� ������ ���ҰŰ���

//�ʿ��������� �Ŵ����� ���� �ٻ������

//�̰� ���߿� �ֻ��� FSM�� ���� �ٷ����� �׶����� ��Ĩ�ô�


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

	//�׳� ui ���
	::StretchBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC,
		rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);

	
	//�������׸���

	
	std::map<INT,character_inform*>::iterator it;

	//�̺������� �׳� �ϴ� ���������� �ѷ��� �׽�Ʈ�ϱ����� ���� ������ �����������
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
		//�밡�ٽ� ������� �ϴ� �·ῡ�ٰ� ������ �ĺ������ ���� �ѷ���

		if (it->first == find_key && character_drag_change){
			it->second->SetPosition(ptMouse);
			it->second->Draw(hdc);
		}
		else{
			it->second->SetPosition(Point(50 + 75 * i, 50 * j + h));
			it->second->Draw(hdc); // �ش� state �� �������ִµ���(SEE_STATE)�ϰ��� �װ��� �׷���
		}
		i++;
		k++;

	}

	if (character_select){ //���� �ɸ���_����_�ڽ��ȿ� ���������ٸ� �˻����� ã�Ҵٴ¾����
		//�� �ɸ��������� ���� �ɸ��͸� ���� Ŭ���̉���� �ΰ����� �� true �϶��� �׷���

		::Rectangle(hdc, ptMouse.x + 20, ptMouse.y + 20, ptMouse.x + 220, ptMouse.y + 220); //������ �����ִ� ���ڸ� ���縶�콺��ǥ >>>>�� �����ٰ� �׸�
		inform_box = Rect(ptMouse.x + 20, ptMouse.y + 20, ptMouse.x + 220, ptMouse.y + 220);



		//���밡�� Ȯ�ο�
		std::wostringstream oss;
		oss << std::endl << std::endl << std::endl << std::endl
			<< _T(" LV : ") << character_inform_box->get_LV() << _T(" HP : ") << character_inform_box->get_HP() << std::endl
			<< _T(" ATK : ") << character_inform_box->get_ATK() << _T(" DEF : ") << character_inform_box->get_DEF() << std::endl
			<< _T(" ATR : ") << character_inform_box->get_ATR() << _T(" SPD : ") << character_inform_box->get_SPD() << std::endl
			<< _T(" CLS : ") << character_inform_box->get_CLS() << std::endl
			<< _T(" ���濡�� : ") << test1 << std::endl
			<< _T(" ���濡�� : ") << test1 << std::endl
			<< _T(" ���濡�� : ") << test1 << std::endl;


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
	//Ŭ�������� �˼��ִ� ��Ʈ�� �ϳ������ ���� ���콺��ǥ���� ������15��ŭ �׷��� �ɸ����߽��̶� ��ġ�ϴ��� Ȯ����




	std::map<INT, character_inform*>::iterator it;

	if (!character_drag_change){
		for (it = manager_depot->begin(); it != manager_depot->end(); it++){

			//�ɸ��� �Ŵ����κ��� ����ɸ����� ��ǥ�� ã�ƺ� ���� Ŭ���ѹ����� �ɸ��Ͱ� �����°��ִ���

			if (::PtInRect(&click_rc, it->second->getPosition())){

				find_key = it->first;

				character_inform_box = it->second; //�ɸ��������� �޾ƿ���


			}
		}
	}

	///////////////////////////////////////
	/// ���콺�������� ����ٴϸ鼭 chracter_inform_box���ٰ�  ���콺�� ���� it�� ���Ͱ� ��ø������
	/// character_inform_box�� ������ �����̴�.
	/// �׷��� �ϴ��� inform box�� �ִٴ� �������� �ɾ��صڿ�
	/// ���縶�콺�� ���� charac_inform_box �� �ִ��� �˻��غ��� ���� ���콺��ġ�� �� �ɸ������������ʴٸ� �ɸ��͸� �����������ʴٴ°ɷ�
	/// character_select = false; �� �ٲ��ش�
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
	/// ���� VK ���ʹ�ư�� ���������� ���� ���콺��ġ�� charac_inform_box ��ġ�� ������ ���غ���
	/// ���縶�콺�� �ش� �ɸ��� ��ǥ �����ö���ִٸ�
	/// �巡�׽����̶�� �����Ѵ�
	//////////////////////////////
	if (character_select && (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000){

		
		character_drag_change = true;
		// temp �� �ٵ�
		

		
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
			
		} //for��������
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