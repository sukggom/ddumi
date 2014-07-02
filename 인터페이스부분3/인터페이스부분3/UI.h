#include <windows.h>
#include "BaseType.h"
#include "Utility.hpp"
#include <map>
#include "character_inform_manager.h"

#define manager_depot char_man_depot.get_depot()

class ui
{

public:
	ui();
	~ui();

	void attach(HWND);

	void draw(HDC);


private:

	HWND hOwner;

};
