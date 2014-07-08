#pragma once



enum Character_State_id
{
	SEE_UP,
	SEE_LEFT,
	SEE_RIGHT,
	SEE_DOWN,
	SEE_ACTION,
	SEE_DIE,
	SEE_STATE,
};


#include "FSM.h"
#include "BaseType.h"
#include "Animation.h"
#include "Utility.hpp"
#include <sstream>
#include <fstream>



class character_inform;




class CharacterState : public State
{
public:
	CharacterState();
	virtual ~CharacterState();

	virtual void Enter() =0;
	virtual void Input(DWORD tick)=0;
	virtual void Update(DWORD tick)=0;
	virtual void Draw(HDC hdc)=0;
	virtual void Leave()=0;

	//void SetImageName(LPCTSTR image_name);
	void SetPositionLink(Point& p);
	void SetPositionLink(Vector& vp , Vector& , Vector& ,bool& , int& spd, int& i,int& chp, bool& end,bool& attack,bool& hold);

	void SetDestination(Vector& v);
	void SetDirection(Vector& v);


protected:
	//LPCTSTR image_name;
	int* spd;
	int* img;
	int* chp;
	bool* the_end;
	Vector* vpos;
	Vector* vDest;
	Vector* direction;
	bool collision;

	bool* attack;
	bool* hold;

	
	Point* pos;
	Animation* pAni;
};





class character_inform : public StateMachine
{
public:
	character_inform();
	character_inform(int i);
	virtual~character_inform();


	
	//이미지를 안에 파뭍혀버려야지
	
	

	////////////////////////////////이미지 부분///////////////////////////////////
	
	void set_image(LPCTSTR image_name);


	////////////////////////////////-----------///////////////////////////////////




	void set_LV(const int&);
	void set_HP(const int&);
	void set_ATK(const int&);
	void set_DEF(const int&);
	void set_ATR(const int&);
	void set_SPD(const int&);
	void set_CLS(const int&);
	void set_inform(const int& l, const int& h, const int& a, const int& d, const int& at, const int& s, const int& c, const int& i ,const int team);


	int get_LV() const;
	int get_HP() const;
	int get_ATK() const;
	int get_DEF() const;
	int get_ATR() const;
	int get_SPD() const;
	int get_CLS() const;

	int get_team() const;

	///////////////////////////////////////////////////////////////////////////////////

	//////   마우스 이동부분//////////////


	void SetDestination(const Vector& v);
	void SetDirection(const Vector& v);
	void SetPosition(const Vector& v);
	void SetDiff(const Vector& d);


	Vector GetDestination() const;
	Vector GetPosition() const;
	Vector GetDirection() const;
	Vector GetDiff() const;

	
	void set_drag_select(const bool &b);
	int get_drag_select();

	//충돌부분
	bool iscollision(character_inform*) const;
	void set_collision(const bool&); // 부딧치면 트루
	bool get_collision() const;

	//hp
	void health(const int& attack);
	int get_CHP() const;
	void set_CHP();
	bool get_end()const;




	//시간체크용
	int get_updt() const;
	void set_updt(DWORD tick);
	int get_indt() const;
	void set_ipdt(DWORD tick);
	void reset_indt();



	void reset_atdt();
	int get_attack_dt()const;
	void set_attack_dt(DWORD tick);

	//공격체크
	bool get_attack_state()const; //홀드랑 어택은 상관관계
	void set_attack_state(const bool& );
	bool get_hold_state()const;
	void set_hold_state(const bool&);

private:

	
	//유저셋팅
	int LV; //
	int exp;

	//AI셋팅
	
	//기본셋팅
	int HP;
	int ATK;
	int DEF;
	int ATR;

	/// 공격체크용
	int SPD;
	int updt;
	int indt;
	int atdt;




	int CLS;
	int CHP;
	int team; //아군적군구분

	//그림저장
	int img;
	

	//상태부분


	bool state_inform_box_select; // 선택박스부분

	bool attack_state; //홀드랑 어택은 상관관계
	bool hold_state;
	//둘다 false 면 걍 이동상태


	////////////////이동부분/////////////
	


	Vector vDest;
	Vector vpos;
	Vector direction;

	Vector diff;

	bool drag_select;


	////////////충돌부분////////////////////

	bool collision;

	//////////////죽는부분////////////
	bool end;

};


class CS_SEE_UP : public CharacterState
{
public:
	CS_SEE_UP(int);
	virtual ~CS_SEE_UP();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

};

class CS_SEE_LEFT : public CharacterState
{
public:
	CS_SEE_LEFT(int);
	virtual ~CS_SEE_LEFT();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();


};

class CS_SEE_RIGHT : public CharacterState
{
public:
	CS_SEE_RIGHT(int);
	virtual ~CS_SEE_RIGHT();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

};



class CS_SEE_DOWN : public CharacterState
{
public:
	CS_SEE_DOWN(int);
	virtual ~CS_SEE_DOWN();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();


};




class CS_ACTION : public CharacterState
{
public:
	CS_ACTION(int);
	virtual ~CS_ACTION();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

};


class CS_DIE : public CharacterState
{
public:
	CS_DIE(int);
	virtual ~CS_DIE();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

private:

	DWORD die_count;
};

class CS_STATE : public CharacterState
{
public:
	CS_STATE(int);
	virtual ~CS_STATE();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

};
