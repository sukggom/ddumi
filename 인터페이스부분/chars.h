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

	

	//�˰���Ȯ���Ϸ������ ���߿�������

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

	bool drag_set; // �巡�� �������ƴ��� Ȯ���Լ�

	bool drag_select; // �巡�������� ������������ ����Ʈ �Ǵ����ȵǴ��� �˾ƺ����Լ�

	COLORREF color;

	Vector move_direction; // �ɸ��� �̵�����

	Point moves;

	//�극���� �κ�

	int iNX;
	int iNY;

	int iDistance;
	int iCount;
	int iError;

	bool moving;
	

};
