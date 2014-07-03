#include "character_inform_manager.h"



character_inform_manager::character_inform_manager()
{
}
character_inform_manager::~character_inform_manager()
{
	DepotType::iterator it;
	for (it = depot.begin(); it != depot.end();)
	{
		delete it->second;
		it = depot.erase(it);
	}
}


character_inform* character_inform_manager::get_inform(const KeyType& key){
	DepotType::iterator it = depot.find(key);
	if (it == depot.end()){

		return NULL;
	}
	return it->second;

}

void character_inform_manager::AddEntry(const KeyType& key, character_inform* pci)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
	{
		depot.insert(std::make_pair(key, pci));
	}
}
void character_inform_manager::RemoveEntry(const KeyType& key)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
		return;

	delete it->second;
	depot.erase(it);
}

int character_inform_manager::change_key(const KeyType& key1, const KeyType& key2){


	if (key1 == key2){
		return 0;
	}
	else{
		DepotType::iterator it1 = depot.find(key1);

		DepotType::iterator it2 = depot.find(key2);


		int k1;
		k1 = it1->first;
		character_inform* ki1;
		ki1 = it1->second;

		int k2;
		k2 = it2->first;
		character_inform* ki2;
		ki2 = it2->second;

		depot.erase(key1);
		depot.erase(key2);

		AddEntry(k1, ki2);
		AddEntry(k2, ki1);

		return 1;

	}
	// temp = x ; x = y ; y = temp;

	
}


std::map<int, character_inform*>* character_inform_manager::get_depot()
{
	return &depot;
}



