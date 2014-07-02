#include "character_inform.h"

/////////////////////////////////////////////////
// CharacterState Impl
/////////////////////////////////////////////////
CharacterState::CharacterState()
: pos(NULL), pAni(NULL)
{}
CharacterState::~CharacterState()
{
	if (pAni)
	{
		delete pAni;
		pAni = NULL;
	}
}
void CharacterState::SetPositionLink(Point& p)
{
	pos = &p;
}


/////////////////////////////////////////////////
// CS_SEE_DOWN Impl
/////////////////////////////////////////////////
CS_SEE_DOWN::CS_SEE_DOWN()
{
	//이부분에서 그림을 받아올건데
	//일단은 기본동작인 IDLE 상태를 하나 더 받고 거기에다가 전부다 이미지를 가지고있어야됨
	//이유는 움직이고나서 IDLE상태일때는 현재 상태가 뭐였는지 확인한상태에서 그 상태움직임 그대로 저장을해야되나 뭔개소리지


	pAni = new Animation;
	for (int i = 0; i < 7; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T(""), Rect(170 * i, 0, 170 + 170 * i, 170));
		pImg->SetTransparent(RGB(255, 0, 255));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
	pAni->SetLoop(true); 
}
CS_SEE_DOWN::~CS_SEE_DOWN()
{
}

void CS_SEE_DOWN::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_SEE_DOWN::Input(DWORD tick)
{

}
void CS_SEE_DOWN::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_SEE_DOWN::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_DOWN::Leave()
{
}






/////////////////////////////////////////////////
// CS_SEE_LEFT Impl
/////////////////////////////////////////////////
CS_SEE_LEFT::CS_SEE_LEFT()
{

	pAni = new Animation;
	for (int i = 0; i < 7; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("ryu_normal.bmp"), Rect(170 * i, 0, 170 + 170 * i, 170));
		pImg->SetTransparent(RGB(255, 0, 255));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
	pAni->SetLoop(true);
}
CS_SEE_LEFT::~CS_SEE_LEFT()
{
}

void CS_SEE_LEFT::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_SEE_LEFT::Input(DWORD tick)
{

}
void CS_SEE_LEFT::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_SEE_LEFT::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_LEFT::Leave()
{
}


/////////////////////////////////////////////////
// CS_SEE_RIGHT Impl
/////////////////////////////////////////////////
CS_SEE_RIGHT::CS_SEE_RIGHT()
{
}
CS_SEE_RIGHT::~CS_SEE_RIGHT()
{
}

void CS_SEE_RIGHT::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_SEE_RIGHT::Input(DWORD tick)
{

}
void CS_SEE_RIGHT::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_SEE_RIGHT::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_RIGHT::Leave()
{
}


/////////////////////////////////////////////////
// CS_SEE_UP Impl
/////////////////////////////////////////////////
CS_SEE_UP::CS_SEE_UP()
{
}
CS_SEE_UP::~CS_SEE_UP()
{
}

void CS_SEE_UP::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_SEE_UP::Input(DWORD tick)
{

}
void CS_SEE_UP::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_SEE_UP::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_UP::Leave()
{
}



/////////////////////////////////////////////////
// CS_ACTION Impl
/////////////////////////////////////////////////
CS_ACTION::CS_ACTION()
{
}
CS_ACTION::~CS_ACTION()
{
}

void CS_ACTION::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_ACTION::Input(DWORD tick)
{

}
void CS_ACTION::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_ACTION::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_ACTION::Leave()
{
}


/////////////////////////////////////////////////
// CS_DIE Impl
/////////////////////////////////////////////////
CS_DIE::CS_DIE()
{
}
CS_DIE::~CS_DIE()
{
}

void CS_DIE::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_DIE::Input(DWORD tick)
{

}
void CS_DIE::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_DIE::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_DIE::Leave()
{
}