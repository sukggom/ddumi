#include "Collision.h"

CollisionImpl::CollisionImpl()
{}
CollisionImpl::~CollisionImpl()
{}

bool CollisionImpl::operator ()(const Vector& v1, const LONG& r1, const Vector& v2, const LONG& r2, Vector& meet) const
{
	Vector d = v1 - v2;

	if (d.size() <= r1 + r2)
	{
		meet = d.normalize()*d.size() / 2 + v2;

		return true;
	}

	return false;
}

