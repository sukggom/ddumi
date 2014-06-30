#include "character_inform.h"

#include "BaseType.h"





character_inform::character_inform()
{
}

character_inform::~character_inform()
{

	if (hBitmap)
	{
		::DeleteObject(hBitmap);
		hBitmap = NULL;
	}
}


void character_inform::draw(HDC){

	


}
void character_inform::update(DWORD){


}
void character_inform::input(DWORD){



}




bool character_inform::Load(LPCTSTR szFileName)
{
	if (!_load_detail(szFileName))
		return false;

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);

	rcSrc = Rect(0, 0, bm.bmWidth, bm.bmHeight);
	rcDest = rcSrc;

	return true;
}
bool character_inform::Load(LPCTSTR szFileName, const Rect& rc)
{
	if (!_load_detail(szFileName))
		return false;

	rcSrc = rc;
	rcDest = rcSrc;

	return true;
}

void character_inform::Draw(HDC hdc)
{
	if (hBitmap == NULL) return;

	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	if (bUseTransparent)
	{
		::GdiTransparentBlt(hdc, rcDest.left, rcDest.top,
			rcDest.width(), rcDest.height(),
			hBitmapDC,
			rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), clrTransparent);
	}
	else
	{
		::StretchBlt(hdc, rcDest.left, rcDest.top,
			rcDest.width(), rcDest.height(),
			hBitmapDC,
			rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);
	}

	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);
}

void character_inform::SetRect(const Rect& rc)
{
	rcDest = rc;
}
void character_inform::SetTransparent(const COLORREF& clr)
{
	clrTransparent = clr;
	bUseTransparent = true;
}



void character_inform::set_LV(const int& l){
	LV = l;
}
void character_inform::set_HP(const int& h){
	HP = h;
}
void character_inform::set_ATK(const int& a){
	ATK = a;
}
void character_inform::set_DEF(const int& d){
	DEF = d;
}
void character_inform::set_ATR(const int& atr){
	ATR = atr;
}
void character_inform::set_SPD(const int& s){
	SPD = s;
}
void character_inform::set_CLS(const int& c){
	CLS = c;
}

int character_inform::get_LV()	const{ return LV;}
int character_inform::get_HP()	const{ return HP; }
int character_inform::get_ATK() const{ return ATK; }
int character_inform::get_DEF() const{ return DEF; }
int character_inform::get_ATR() const{ return ATR; }
int character_inform::get_SPD() const{ return SPD; }
int character_inform::get_CLS() const{ return CLS; }