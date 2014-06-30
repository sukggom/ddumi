
#include <windows.h>
#include <tchar.h>
#include "BaseType.h"
#include "Utility.hpp"

enum CLASS_SETTING_CLS{
	SWORD,
	SPEAR,
	KNIGHT,

};

class character_inform
{
public:
	character_inform();
	~character_inform();

	//�̹����� �ȿ� �Ĺ�����������



	bool Load(LPCTSTR szFileName);
	bool Load(LPCTSTR szFileName, const Rect& rc);

	void Draw(HDC hdc);

	void SetRect(const Rect& rc);

	void SetTransparent(const COLORREF& clr);


	void draw(HDC);
	void update(DWORD);
	void input(DWORD);




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


private:

	//�׸��κ�
	HBITMAP hBitmap;
	Rect rcSrc;
	Rect rcDest;

	COLORREF clrTransparent;
	bool bUseTransparent;

	
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

};

