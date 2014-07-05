#include "character_inform.h"

/////////////////////////////////////////////////
// CharacterState Impl
/////////////////////////////////////////////////
CharacterState::CharacterState()
: pos(NULL), vpos(NULL), pAni(NULL), direction(NULL), vDest(NULL)
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

void CharacterState::SetPositionLink(Vector& vp , Vector& v , Vector& d)
{
	vpos = &vp;
	vDest = &v;
	direction = &d;
}


void CharacterState::SetDestination(Vector& v)
{
	vDest = &v;
}

void CharacterState::SetDirection(Vector& v)
{
	direction = &v;

}


/////////////////////////////////////////////////
// CS_SEE_UP Impl
/////////////////////////////////////////////////
CS_SEE_UP::CS_SEE_UP()
{

	pAni = new Animation;
	for (int i = 0; i < 2; i++)
	{

		Image* pImg = new Image;      // enum 자기숫자 (UP은 0)   
		pImg->Load(_T("001.bmp"), Rect(32 * i, 32 * SEE_UP, 32 + 32 * i, 32 + 32 * SEE_UP));
		pImg->SetTransparent(RGB(0, 0, 0));

		pAni->AddShot(pImg);
	}
	pAni->SetLoop(true);
	pAni->SetDelay(60);
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
	Vector diff = *vpos - *vDest;

	if (diff == Vector())
		return;

	*direction = *vDest - *vpos;
	*direction = direction->normalize() * 2;


	*vpos = *vpos + *direction;
	

}
void CS_SEE_UP::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*vpos, Size(40, 40)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_UP::Leave()
{
}






/////////////////////////////////////////////////
// CS_SEE_LEFT Impl
/////////////////////////////////////////////////
CS_SEE_LEFT::CS_SEE_LEFT()
{

	pAni = new Animation;
	for (int i = 0; i < 2; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("001.bmp"), Rect(32*i , 32*SEE_LEFT , 32 + 32 *i , 32 + 32*SEE_LEFT));
		pImg->SetTransparent(RGB(0,0,0));

		pAni->AddShot(pImg);
	}
	pAni->SetLoop(true);
	pAni->SetDelay(60);
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


	Vector diff = *vpos - *vDest;

	if (diff == Vector())
		return;

	*direction = *vDest - *vpos;
	*direction = direction->normalize() * 2;


	*vpos = *vpos + *direction;
}

void CS_SEE_LEFT::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*vpos, Size(40, 40)));
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

	pAni = new Animation;
	for (int i = 0; i < 2; i++)
	{
		Image* pImg = new Image;      // enum 자기숫자 (UP은 0)   
		pImg->Load(_T("001.bmp"), Rect(32 * i, 32 * SEE_RIGHT, 32 + 32 * i, 32 + 32 * SEE_RIGHT));
		pImg->SetTransparent(RGB(0, 0, 0));

		pAni->AddShot(pImg);
	}
	pAni->SetLoop(true);
	pAni->SetDelay(60);
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
	Vector diff = *vpos - *vDest;

	if (diff == Vector())
		return;

	*direction = *vDest - *vpos;
	*direction = direction->normalize() * 2;


	*vpos = *vpos + *direction;
	

}
void CS_SEE_RIGHT::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*vpos, Size(40, 40)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_RIGHT::Leave()
{


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
	for (int i = 0; i < 2; i++)
	{
		Image* pImg = new Image;      // enum 자기숫자 (UP은 0)   
		pImg->Load(_T("001.bmp"), Rect(32 * i, 32 * SEE_DOWN, 32 + 32 * i, 32 + 32 * SEE_DOWN));
		pImg->SetTransparent(RGB(0, 0, 0));

		pAni->AddShot(pImg);
	}
	pAni->SetLoop(true);
	pAni->SetDelay(60);
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

	Vector diff = *vpos - *vDest;

	if (diff == Vector())
		return;

	*direction = *vDest - *vpos;
	*direction = direction->normalize() * 2;


	*vpos = *vpos + *direction;


}
void CS_SEE_DOWN::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*vpos, Size(40,40)));
		pAni->Draw(hdc);
	}
}
void CS_SEE_DOWN::Leave()
{
}


/////////////////////////////////////////////////
// CS_ACTION Impl
/////////////////////////////////////////////////
CS_ACTION::CS_ACTION()
{

	pAni = new Animation;
	for (int i = 0; i < 2; i++)
	{
		Image* pImg = new Image;      // enum 자기숫자 (UP은 0)   
		pImg->Load(_T("001.bmp"), Rect(32 * i, 32 * SEE_ACTION, 32 + 32 * i, 32 + 32 * SEE_ACTION));
		pImg->SetTransparent(RGB(0, 0, 0));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
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
		pAni->SetRect(Rect(*vpos, Size(40, 40)));
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

	pAni = new Animation;
	for (int i = 0; i < 2; i++)
	{
		Image* pImg = new Image;      // enum 자기숫자 (UP은 0)   
		pImg->Load(_T("001.bmp"), Rect(32 * i, 32 * SEE_DIE, 32 + 32 * i, 32 + 32 * SEE_DIE));
		pImg->SetTransparent(RGB(0, 0, 0));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
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
		pAni->SetRect(Rect(*vpos, Size(170, 170)));
		pAni->Draw(hdc);
	}
}
void CS_DIE::Leave()
{
}



/////////////////////////////////////////////////
// CS_STATE Impl
/////////////////////////////////////////////////
CS_STATE::CS_STATE()
{
	//이부분에서 그림을 받아올건데
	//일단은 기본동작인 IDLE 상태를 하나 더 받고 거기에다가 전부다 이미지를 가지고있어야됨
	//이유는 움직이고나서 IDLE상태일때는 현재 상태가 뭐였는지 확인한상태에서 그 상태움직임 그대로 저장을해야되나 뭔개소리지


	pAni = new Animation;
	for (int i = 0; i < 2; i++)
	{
		Image* pImg = new Image;      // enum 자기숫자 (UP은 0)   
		pImg->Load(_T("001.bmp"), Rect(32 * i, 32 * SEE_DOWN, 32 + 32 * i, 32 + 32 * SEE_DOWN));
		pImg->SetTransparent(RGB(0, 0, 0));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
}
CS_STATE::~CS_STATE()
{
}

void CS_STATE::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_STATE::Input(DWORD tick)
{

}
void CS_STATE::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_STATE::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*vpos, Size(40, 40)));
		pAni->Draw(hdc);
	}
}
void CS_STATE::Leave()
{
}


