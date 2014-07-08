#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static int e_lv; //적레벨 셋팅값

	static Point ptMouse;
	static int save_member;
	
	static in_game in_game;



	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
		backbuffer.Attach(hWnd);

		// TODO

		std::fstream file;

		file.open(_T("save1.data"), std::ios_base::in);

		in_game.attach(hWnd);
		in_game.Load_game_map(_T("ingame.bmp"));
		 
		file >> save_member;


		for (int i = 0; i < save_member; i++){
			int img;

			file >> img;

			character_inform* pchar = new character_inform(img);
			character_inform* echar = new character_inform(5);
			
			int LV;
			int HP;
			int ATK;
			int DEF;
			int ATR;
			int SPD;
			int CLS;
			int team = 1;
			int eteam = 2;

			if (i >= 10){
				team = 3;
			}

			file >> LV >> HP >> ATK >> DEF >> ATR >> SPD >> CLS;

			pchar->set_inform(LV, HP, ATK, DEF, ATR, SPD, CLS ,img ,team);

			

			//이미지를 인트로받아다가 
			// 씀
			pchar->transition(SEE_RIGHT);

			//600 이면 0~300까지만 나옴

			pchar->SetPosition(Vector(rand() % rc.width() / 2 + rc.left, rand() % rc.height() + rc.top));
		
			char_man_depot.AddEntry(i, pchar);

		
			if (i < 10){
				echar->set_inform(1, 350, 22, 10, 100, 2, 1, 5, eteam);

				echar->transition(SEE_LEFT);

				//600이면 0~300 까지나온거에 +300 더하니까 300~600임
				echar->SetPosition(Vector((rand() % rc.width() / 2 + rc.left) + rc.width() / 2, rand() % rc.height() + rc.top));

				//적은101 부터
				char_man_depot.AddEntry(i + 100, echar);
			}

			
		}

		file.close();



		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 10, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		// TODO

		::KillTimer(hWnd, 0);

		backbuffer.Detach();
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		backbuffer << RGB(255,255,255);

		// TODO


		in_game.draw(backbuffer);


		backbuffer.Draw();



		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO

		in_game.Input(dt);
		in_game.Update(dt);

		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}
