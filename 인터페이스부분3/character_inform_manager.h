#pragma once
#include "character_inform.h"

class character_inform_manager : public singleton<character_inform_manager>
{
private:
	character_inform_manager();
	~character_inform_manager();
public:
	friend class singleton<character_inform_manager>;
	typedef INT KeyType;
	typedef std::map<KeyType, character_inform*> DepotType;

public:
	character_inform* get_inform(const KeyType& key);

	void AddEntry(const KeyType& key, character_inform*);

	void RemoveEntry(const KeyType& key);

	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc); 
	
	std::map<int, character_inform*>*  get_depot();





private:
	DepotType depot; //map Çü½Ä
	character_inform* _current;
};

#define char_man_depot character_inform_manager::GetReference()