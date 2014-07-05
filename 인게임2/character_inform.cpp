#include "character_inform.h"



// 여기서 이미지 시작할때 




character_inform::character_inform()
:drag_select(false)
{
	
	
	CS_SEE_UP* pup = new CS_SEE_UP;
	pup->SetPositionLink(vpos,vDest,direction,collision);
	//pup->SetImageName(image_name);
	AddEntry(SEE_UP, pup);

	CS_SEE_LEFT* pleft = new CS_SEE_LEFT;
	pleft->SetPositionLink(vpos, vDest, direction , collision);
	//pleft->SetImageName(image_name);
	AddEntry(SEE_LEFT, pleft);

	CS_SEE_RIGHT* pright = new CS_SEE_RIGHT;
	pright->SetPositionLink(vpos, vDest, direction, collision);
	//pright->SetImageName(image_name);
	AddEntry(SEE_RIGHT, pright);

	CS_SEE_DOWN* pdown = new CS_SEE_DOWN;
	pdown->SetPositionLink(vpos, vDest, direction, collision);
	//pdown->SetImageName(image_name);
	AddEntry(SEE_DOWN, pdown);

	CS_ACTION* paction = new CS_ACTION;
	paction->SetPositionLink(vpos, vDest, direction, collision);
//	paction->SetImageName(image_name);
	AddEntry(SEE_ACTION, paction);

	CS_DIE* pdie = new CS_DIE;
	pdie->SetPositionLink(vpos, vDest, direction, collision);
	//pdie->SetImageName(image_name);
	AddEntry(SEE_DIE, pdie);

	CS_STATE* pstate = new CS_STATE;
	pstate->SetPositionLink(vpos, vDest, direction, collision);
	//pstate->SetImageName(image_name);
	AddEntry(SEE_STATE, pstate);


	transition(SEE_STATE);
}
character_inform::~character_inform()
{}

////////이동부분////////
void character_inform::SetPosition(const Vector& v)
{
	vpos = v;
	vDest = vpos;
}


void character_inform::set_image(LPCTSTR n){

	image_name = n;

}

void character_inform::set_drag_select(const bool & b){

	drag_select = b;
}

int character_inform::get_drag_select(){

	if (drag_select){
		return 1;
	}

	else{
		return 0;
	}
}



void character_inform::SetDestination(const Vector& v)
{
	vDest = v;
}

void character_inform::SetDirection(const Vector& v)
{
	direction = v;
}

Vector character_inform::GetDestination() const
{
	return vDest;
}
Vector character_inform::GetPosition() const
{
	return vpos;
}
Vector character_inform::GetDirection() const
{
	return direction;
}


void character_inform::SetDiff(const Vector& d){

	diff = d;

}
Vector character_inform::GetDiff() const{

	return diff;
}


bool character_inform::iscollision(character_inform* characters) const{

	
	Rect myRect;
	myRect = Rect(vpos.x - 16, vpos.y - 16, vpos.x + 16, vpos.y + 16);

	Rect targetRect;
	targetRect = Rect(
		characters->vpos.x - 16, characters->vpos.y - 16,
						characters->vpos.x + 16, characters->vpos.y + 16);



	return !(myRect.left > targetRect.right || myRect.right < targetRect.left ||
            myRect.top > targetRect.bottom || myRect.bottom < targetRect.top);


}


void character_inform::set_collision(const bool& b){
	
	collision = b;

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

void character_inform::set_inform(const int& l, const int& h, const int& a, const int& d, const int& at, const int& s, const int& c){

	LV = l;
	HP = h;
	ATK = a;
	DEF = d;
	ATR = at;
	SPD = s;
	CLS = c;
}

int character_inform::get_LV()	const{ return LV;}
int character_inform::get_HP()	const{ return HP; }
int character_inform::get_ATK() const{ return ATK; }
int character_inform::get_DEF() const{ return DEF; }
int character_inform::get_ATR() const{ return ATR; }
int character_inform::get_SPD() const{ return SPD; }
int character_inform::get_CLS() const{ return CLS; }



