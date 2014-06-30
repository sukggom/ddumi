#include "BaseType.h"
#include "Utility.hpp"


class chars
{
public:
	chars();
	~chars();


	void attach(HWND);

	void draw(HDC);
	void input(DWORD);
	void update(DWORD);

	void set_center(const Point &);

	void set_color(const COLORREF &);

	void set_drag(const bool&);

	void set_direction(const Vector&);

	void set_moves(const Point&);

	void set_speed(const double& s);

	Point get_goal() const;

	

	//알고리즘확인하려고만든거 나중에삭제됨

	int get_iNX() const;
	int get_iNY() const;
	int get_iDistance() const;
	int get_iCount() const;
	int get_iError() const;

	Point get_moving_center() const;



private:

	HWND hOwner;

	Point drag_start;
	Point drag_end;

	int radius;
	int speed;
	int speed_x;
	int speed_y;

	Point moving_center;
	Point goal_center;

	Point center;

	bool drag_set; // 드래그 중인지아닌지 확인함수

	bool drag_select; // 드래그했을때 범위에있으면 셀렉트 되는지안되는지 알아보는함수

	COLORREF color;

	Vector move_direction; // 케릭터 이동방향

	Point moves;

	//브레즌햄 부분

	int iNX;
	int iNY;

	int iDistance;
	int iCount;
	int iError;

	bool moving;
	

};
