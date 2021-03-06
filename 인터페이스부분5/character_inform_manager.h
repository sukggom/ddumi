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

	std::map<int, character_inform*>*  get_depot();



	int change_key(const KeyType& key1, const KeyType& ket2);


private:
	DepotType depot; //map ����
};

#define char_man_depot character_inform_manager::GetReference()