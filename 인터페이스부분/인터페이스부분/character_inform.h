

class character_inform
{
public:
	character_inform();
	~character_inform();

	void set_LV(const int&);
	void set_HP(const int&);
	void set_ATK(const int&);
	void set_DEF(const int&);
	void set_ATR(const int&);
	void set_SPD(const int&);
	void set_CLS(const int&);

private:

	//유저셋팅
	int LV;


	//AI셋팅
	
	//기본셋팅
	int HP;
	int ATK;
	int DEF;
	int ATR;
	int SPD;
	int CLS;


	//그림저장

};

