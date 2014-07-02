#pragma once



enum Character_State_id
{
	SEE_DOWN,
	SEE_LEFT,
	SEE_RIGHT,
	SEE_UP,
	SEE_ACTION,
	SEE_DIE,
};


#include "FSM.h"
#include "BaseType.h"
#include "Animation.h"
#include "Utility.hpp"



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

	void SetPositionLink(Point& p);
protected:
	Point* pos;
	Animation* pAni;
};





class character_inform : public StateMachine
{
public:
	character_inform();
	virtual~character_inform();


	
	//�̹����� �ȿ� �Ĺ�����������


	////////////////////////////////�̹��� �κ�///////////////////////////////////
	


	////////////////////////////////-----------///////////////////////////////////


	void Draw(HDC);



	void set_LV(const int&);
	void set_HP(const int&);
	void set_ATK(const int&);
	void set_DEF(const int&);
	void set_ATR(const int&);
	void set_SPD(const int&);
	void set_CLS(const int&);

	int get_LV() const;
	int get_HP() const;
	int get_ATK() const;
	int get_DEF() const;
	int get_ATR() const;
	int get_SPD() const;
	int get_CLS() const;

	void SetPosition(const Point& p);


private:

	
	//��������
	int LV;


	//AI����
	
	//�⺻����
	int HP;
	int ATK;
	int DEF;
	int ATR;
	int SPD;
	int CLS;


	//�׸�����

	

	//���ºκ�
	Point pos;
};



class CS_SEE_DOWN : public CharacterState
{
public:
	CS_SEE_DOWN();
	virtual ~CS_SEE_DOWN();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};

class CS_SEE_LEFT : public CharacterState
{
public:
	CS_SEE_LEFT();
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
	CS_SEE_RIGHT();
	virtual ~CS_SEE_RIGHT();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};

class CS_SEE_UP : public CharacterState
{
public:
	CS_SEE_UP();
	virtual ~CS_SEE_UP();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};



class CS_ACTION : public CharacterState
{
public:
	CS_ACTION();
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
	CS_DIE();
	virtual ~CS_DIE();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};

