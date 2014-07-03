#include "character_inform_manager.h"



character_inform_manager::character_inform_manager()
: _current(NULL)
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

void character_inform_manager::Input(DWORD tick)
{
	if (_current)
		_current->Input(tick);
}
void character_inform_manager::Update(DWORD tick)
{
	if (_current)
		_current->Update(tick);
}
void character_inform_manager::Draw(HDC hdc)
{
	if (_current)
		_current->Draw(hdc);
}

std::map<int, character_inform*>* character_inform_manager::get_depot()
{
	return &depot;
}



