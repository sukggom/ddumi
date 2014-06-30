#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	static DWORD st = 0;
	static DWORD dt = 0;



	const int count = 100;
	static Point ptMouse;
	static POINT clineMouse;
	static POINT ptclient;

	static Point centers;
	static chars test;
	static double sp = 2;
	const LONG radius = 30;

	static bool bDrawLine = false;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InflateRect(&rc, -radius, -radius);

	
		//ptclinet가 rc 의 가운데에 오게끔해야됨...


		test.attach(hWnd);
		test.set_center(rc.center());

		test.set_direction(Vector());
		test.set_speed(sp);
		
		
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


		

		test.draw(hdc);



		std::wostringstream oss;
		oss << _T("cent : ") << centers.x << std::endl << _T("ptx : ") << ptMouse.x << _T("pty : ") << ptMouse.y << std::endl
			<< _T("rc. w: ") << rc.right / 2 << _T("rc.h : ") << rc.bottom / 2 << std::endl
			<< _T("rc.cent.x") << centers.x << _T("rc.cent.y") << centers.y << std::endl
			<< _T(" goal x:") << test.get_goal().x << _T(" goal x:") << test.get_goal().y << std::endl

			<< _T(" inx : ") << test.get_iNX() << _T(" iny : ") << test.get_iNY()
			<< _T(" iDistance : ") << test.get_iDistance()
			<< _T(" iCount : ") << test.get_iCount()
			<< _T(" iError : ") << test.get_iError()
			<< _T(" moving x : ") << test.get_moving_center().x << _T(" moving y: ") << test.get_moving_center().y;

		

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

		test.input(dt);

		test.update(dt);

	

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}