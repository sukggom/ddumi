#include <windows.h>
#include "character_inform.h"
#include "Utility.hpp"
#include <map>

class character_inform_manager : public singleton<character_inform_manager>
{
	friend class singleton<character_inform_manager>;
	typedef INT KeyType;
	typedef std::map<KeyType, character_inform*> DepotType;

public:
	character_inform_manager();
	~character_inform_manager();

	character_inform* get_inform(const KeyType& key);

	void AddEntry(const KeyType& key, character_inform* );
	
	void RemoveEntry(const KeyType& key);

	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);

	void set_character_inform(character_inform*);

private:
	DepotType depot; //map Çü½Ä
	character_inform* _current;
};

