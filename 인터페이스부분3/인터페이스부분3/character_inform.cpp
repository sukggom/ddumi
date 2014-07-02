#include "character_inform.h"



// 여기서 이미지 시작할때 




character_inform::character_inform()
{
	CS_SEE_DOWN* pdown = new CS_SEE_DOWN;
	pdown->SetPositionLink(pos);
	AddEntry(SEE_DOWN, pdown);

	CS_SEE_LEFT* pleft = new CS_SEE_LEFT;
	pleft->SetPositionLink(pos);
	AddEntry(SEE_LEFT, pleft);

	CS_SEE_RIGHT* pright = new CS_SEE_RIGHT;
	pright->SetPositionLink(pos);
	AddEntry(SEE_RIGHT, pright);

	CS_SEE_UP* pup = new CS_SEE_UP;
	pup->SetPositionLink(pos);
	AddEntry(SEE_DOWN, pup);

	CS_ACTION* paction = new CS_ACTION;
	paction->SetPositionLink(pos);
	AddEntry(SEE_ACTION, paction);

	CS_DIE* pdie = new CS_DIE;
	pdie->SetPositionLink(pos);
	AddEntry(SEE_DIE, pdie);



	transition(SEE_DOWN);
}
character_inform::~character_inform()
{}

void character_inform::SetPosition(const Point& p)
{
	pos = p;
}




void character_inform::Draw(HDC hdc){

	::Rectangle(hdc, pos.x-15,pos.y-15, pos.x+15, pos.y+15);

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



