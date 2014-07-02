#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	static DWORD st = 0;
	static DWORD dt = 0;

	static Point ptMouse;

	const int count = 100;

	static int radius = 20;

	static ui user_interface;
	
	static bool bDrawLine = false;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InflateRect(&rc, -radius, -radius);

		user_interface.attach(hWnd);


		for (int i = 1; i < 4; i++){
			character_inform* pchar = new character_inform;

			pchar->SetPosition(Point(30 * i, 30 * i));
			pchar->set_ATK(10);

			char_man_depot.AddEntry(i-1, pchar);

		}



	
		//ptclinet가 rc 의 가운데에 오게끔해야됨...


	
		::SetTimer(hWnd, 0, 10, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);
		::PostQuitMessage(0);
		
	
		return 0;
	}
	
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO.....
		Rect rc;
		::GetClientRect(hWnd, &rc);
		LONG a = (rc.left + rc.right)/2;


		user_interface.draw(hdc);

		std::wostringstream oss;
		oss << _T("rc. w: ") << rc.right / 2 << _T("rc.h : ") << rc.bottom / 2 << std::endl
		;

		::DrawText(hdc, oss.str().c_str(), -1, &rc, DT_TOP);

	
		::EndPaint(hWnd, &ps);
		return 0;
	}

	else if (uMsg == WM_LBUTTONUP){

		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		//test.set_drag(false);

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;

	}

	else if (uMsg == WM_MOUSEMOVE){

		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}


	else if (uMsg == WM_TIMER){

	

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}