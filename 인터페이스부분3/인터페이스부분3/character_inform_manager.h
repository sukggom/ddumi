#pragma once
#include "character_inform.h"

class character_inform_manager : public singleton<character_inform_manager>
{
	friend class singleton<character_inform_manager>;
	typedef INT KeyType;
	typedef std::map<KeyType, character_inform*> DepotType;

private:
	character_inform_manager();
	~character_inform_manager();

public:
	character_inform* get_inform(const KeyType& key);

	void AddEntry(const KeyType& key, character_inform*);

	void RemoveEntry(const KeyType& key);

	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc); 
	
	std::map<int, character_inform*>*  get_depot();



	std::map<int, character_inform*>  get_depot2();



private:
	DepotType depot; //map ����
	character_inform* _current;
};

#define char_man_depot character_inform_manager::GetReference()