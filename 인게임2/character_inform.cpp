#include "character_inform.h"



// 여기서 이미지 시작할때 




character_inform::character_inform(int im)
:drag_select(false)
, collision(false)
, end(false)
, updt(200)
, indt(0)
, atdt(0)
, attack_state(true)
, hold_state(false)
{
	

	CS_SEE_UP* pup = new CS_SEE_UP(im);
	pup->SetPositionLink(vpos,vDest,direction,collision,SPD,img,CHP,end,attack_state,hold_state);
	//pup->SetImageName(image_name);
	AddEntry(SEE_UP, pup);

	CS_SEE_LEFT* pleft = new CS_SEE_LEFT(im);
	pleft->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pleft->SetImageName(image_name);
	AddEntry(SEE_LEFT, pleft);

	CS_SEE_RIGHT* pright = new CS_SEE_RIGHT(im);
	pright->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pright->SetImageName(image_name);
	AddEntry(SEE_RIGHT, pright);

	CS_SEE_DOWN* pdown = new CS_SEE_DOWN(im);
	pdown->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pdown->SetImageName(image_name);
	AddEntry(SEE_DOWN, pdown);

	CS_ACTION* paction = new CS_ACTION(im);
	paction->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
//	paction->SetImageName(image_name);
	AddEntry(SEE_ACTION, paction);

	CS_DIE* pdie = new CS_DIE(im);
	pdie->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pdie->SetImageName(image_name);
	AddEntry(SEE_DIE, pdie);

	CS_STATE* pstate = new CS_STATE(im);
	pstate->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pstate->SetImageName(image_name);
	AddEntry(SEE_STATE, pstate);


	transition(SEE_STATE);
}



character_inform::character_inform()
:drag_select(false)
, collision(false)
{


	CS_SEE_UP* pup = new CS_SEE_UP(1);
	pup->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pup->SetImageName(image_name);
	AddEntry(SEE_UP, pup);

	CS_SEE_LEFT* pleft = new CS_SEE_LEFT(1);
	pleft->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pleft->SetImageName(image_name);
	AddEntry(SEE_LEFT, pleft);

	CS_SEE_RIGHT* pright = new CS_SEE_RIGHT(1);
	pright->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pright->SetImageName(image_name);
	AddEntry(SEE_RIGHT, pright);

	CS_SEE_DOWN* pdown = new CS_SEE_DOWN(1);
	pdown->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pdown->SetImageName(image_name);
	AddEntry(SEE_DOWN, pdown);

	CS_ACTION* paction = new CS_ACTION(1);
	paction->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//	paction->SetImageName(image_name);
	AddEntry(SEE_ACTION, paction);

	CS_DIE* pdie = new CS_DIE(1);
	pdie->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
	//pdie->SetImageName(image_name);
	AddEntry(SEE_DIE, pdie);

	CS_STATE* pstate = new CS_STATE(1);
	pstate->SetPositionLink(vpos, vDest, direction, collision, SPD, img, CHP, end, attack_state, hold_state);
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

bool character_inform::get_collision() const{

	return collision;
}

















void character_inform::set_LV(const int& l){


	exp = l; //경험치를 넣고

	int cur_exp =0; // 현재경험치를 계산하려한다

	for (int i = 1; i < 20; i++){
		//1레벨체크
		if (cur_exp > exp){ // 현재경험치는 적음 // 경험치총량보다적음 // exp 100이되는데 < cur_exp는 900이됨 즉
			LV = i; //i가 레벨이 됨
			i = 20; //멈춰랏!
 			break;
		}
		else{
			cur_exp = 300 * i; // 300경험치얻으면 레벨업함  // 2업이되면 600이 필요하니까 600을깜

			exp = exp - cur_exp; // 총경험치에서 레벨업경험치를뺌 // 근데 경험치량이 1000 이면 300 600 빼면 100남음
		}
	}
	
}
void character_inform::set_HP(const int& h){
	HP = h;
	CHP = h;
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
void character_inform::set_CHP() {

	CHP = HP;

}

void character_inform::set_inform(const int& l, const int& h, const int& a, const int& d, const int& at, const int& s, const int& c, const int& i, const int t){

	LV = l;
	HP = h;
	CHP = h;
	ATK = a;
	DEF = d;
	ATR = at;
	SPD = s;
	CLS = c;
	img = i;
	team = t; //1 아군 2적군
}


void character_inform::health(const int& attack ){

	if (CHP <= 0){

		CHP = 0;
	}
	else{
		if (attack <= DEF){

			CHP -= 1 + rand() % 2;
		}
		else{
			CHP -= ((attack - DEF) / 2) + rand() % 4;

		}
	}

}


bool character_inform::get_end()const{

	return end;
}

int character_inform::get_LV()	const{ return LV;}
int character_inform::get_HP()	const{ return HP; }
int character_inform::get_ATK() const{ return ATK; }
int character_inform::get_DEF() const{ return DEF; }
int character_inform::get_ATR() const{ return ATR; }
int character_inform::get_SPD() const{ return SPD; }
int character_inform::get_CLS() const{ return CLS; }
int character_inform::get_CHP() const{ return CHP; }
int character_inform::get_team() const{ return team; }

int character_inform::get_updt() const{ return updt; }
void character_inform::set_updt(DWORD tick){

	updt = tick;

}
int character_inform::get_indt() const{ return indt; }

void character_inform::reset_indt(){


	indt = 0;
}
void character_inform::set_ipdt(DWORD tick){

	indt += tick;
}



void character_inform::reset_atdt(){

	atdt = 0;
}

int character_inform::get_attack_dt()const{

	return atdt;
}

void character_inform::set_attack_dt(DWORD tick){

	atdt += tick;
}



bool character_inform::get_attack_state()const{

	return attack_state;

}//홀드랑 어택은 상관관계
void character_inform::set_attack_state(const bool& b){

	attack_state = b;

}
bool character_inform::get_hold_state()const{

	return hold_state;

}
void character_inform::set_hold_state(const bool& b){


	hold_state = b;
}

