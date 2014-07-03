#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static Point ptMouse;

	
	static int save_member;

	static ui user_interface;



	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
		backbuffer.Attach(hWnd);

		// TODO

		std::fstream file;

		file.open(_T("save1.data"), std::ios_base::in);

		user_interface.attach(hWnd);
		user_interface.Load_interface_map(_T("ui2.bmp"));
		 
		file >> save_member;


		for (int i = 0; i < 14; i++){

			character_inform* pchar = new character_inform;
			
			int LV;
			int HP;
			int ATK;
			int DEF;
			int ATR;
			int SPD;
			int CLS;

			file >> LV >> HP >> ATK >> DEF >> ATR >> SPD >> CLS;

			pchar->set_inform(LV, HP, ATK, DEF, ATR, SPD, CLS);

			pchar->transition(SEE_STATE);

			char_man_depot.AddEntry(i, pchar);
			
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

		backbuffer << RGB(100, 100, 150);

		// TODO


		user_interface.draw(backbuffer);


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
		user_interface.Input(dt);
	//	user_interface.Update(dt);

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
