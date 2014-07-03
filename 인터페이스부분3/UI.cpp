#include "UI.h"

//�ش� ui ���� input���� ��� ������ ���ҰŰ���

//�ʿ��������� �Ŵ����� ���� �ٻ������

//�̰� ���߿� �ֻ��� FSM�� ���� �ٷ����� �׶����� ��Ĩ�ô�


ui::ui()
:character_inform_box(NULL)
, inform_box_select(NULL)
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
		it->second->SetPosition(Point(50 +  75* i, 50 * j + h ));
		it->second->Draw(hdc); // �ش� state �� �������ִµ���(SEE_STATE)�ϰ��� �װ��� �׷���
		i++;
		k++;

	}

	if (inform_box_select && character_inform_box){ //���� �ɸ���_����_�ڽ��ȿ� ���������ٸ� �˻����� ã�Ҵٴ¾����
		//�� �ɸ��������� ���� �ɸ��͸� ���� Ŭ���̉���� �ΰ����� �� true �϶��� �׷���

		::Rectangle(hdc, ptMouse.x + 20, ptMouse.y + 20, ptMouse.x + 220, ptMouse.y + 220); //������ �����ִ� ���ڸ� ���縶�콺��ǥ >>>>�� �����ٰ� �׸�
		inform_box = Rect(ptMouse.x + 20, ptMouse.y + 20, ptMouse.x + 220, ptMouse.y + 220);



		//���밡�� Ȯ�ο�
		std::wostringstream oss;
		oss << std::endl << std::endl << std::endl << std::endl 
			<< _T(" LV : ") << character_inform_box->get_LV() << _T(" HP : ") << character_inform_box->get_HP() << std::endl
			<< _T(" ATK : ") << character_inform_box->get_ATK() << _T(" DEF : ") << character_inform_box->get_DEF() << std::endl
			<< _T(" ATR : ") << character_inform_box->get_ATR() << _T(" SPD : ") << character_inform_box->get_SPD() << std::endl
			<< _T(" CLS : ") << character_inform_box->get_CLS();

		::DrawText(hdc, oss.str().c_str(), -1, &inform_box, DT_CENTER );

		
	}
	

	
	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);




}


void ui::Input(DWORD tick){

	std::map<INT, character_inform*>::iterator it;


	//�巡�׶� ������������ ���콺�� ������ ������ ������ �����ְ� �巡���ϸ� �ƴϰ�...
	if ((::GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0x8000){

		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hOwner);
		Rect click_rc = Rect(ptMouse.x - 15, ptMouse.y - 15, ptMouse.x + 15, ptMouse.y + 15);
		//Ŭ�������� �˼��ִ� ��Ʈ�� �ϳ������ ���� ���콺��ǥ���� ������15��ŭ �׷��� �ɸ����߽��̶� ��ġ�ϴ��� Ȯ����



		for (it = manager_depot->begin(); it != manager_depot->end(); it++){
			//�ɸ��� �Ŵ����κ��� ����ɸ����� ��ǥ�� ã�ƺ� ���� Ŭ���ѹ����� �ɸ��Ͱ� �����°��ִ���

			if (::PtInRect(&click_rc, it->second->getPosition())){
				//�����ִٸ� 
				character_inform_box = it->second; //�ɸ��������� �޾ƿ���
				inform_box_select = true; // ���É���� Ʈ�縦 ��
				break; //�극��ũ�ϴ������� �ؿ� ����
			}
			else{
				inform_box_select = false;// ���࿡ �������� ������� �ٵ��ٸ� 1234 ���߿� 2���� ���õǵ� �ᱹ 4���������ϱ� false ����
				//�װɸ����� ã���� �׳� break�� ����. �������� ã�Ƽ� true �� �Ǵϱ� ã���� false�� �ɼ�����
			}

		}


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