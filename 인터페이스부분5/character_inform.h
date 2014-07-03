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
protected:
	//LPCTSTR image_name;
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
	
	void set_image(LPCTSTR image_name);


	////////////////////////////////-----------///////////////////////////////////




	void set_LV(const int&);
	void set_HP(const int&);
	void set_ATK(const int&);
	void set_DEF(const int&);
	void set_ATR(const int&);
	void set_SPD(const int&);
	void set_CLS(const int&);
	void set_inform(const int& l, const int& h, const int& a, const int& d, const int& at, const int& s, const int& c);


	int get_LV() const;
	int get_HP() const;
	int get_ATK() const;
	int get_DEF() const;
	int get_ATR() const;
	int get_SPD() const;
	int get_CLS() const;



	void SetPosition(const Point& p);
	Point getPosition() const;



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
	LPCTSTR image_name;
	

	//���ºκ�
	Point pos;


	bool state_inform_box_select; // ���ùڽ��κ�
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

class CS_STATE : public CharacterState
{
public:
	CS_STATE();
	virtual ~CS_STATE();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

};
