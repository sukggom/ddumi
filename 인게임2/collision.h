#pragma once

#include "BaseType.h"
#include "Utility.hpp"

class CollisionImpl : public singleton<CollisionImpl>
{
	friend class singleton<CollisionImpl>;
private:
	CollisionImpl();
	~CollisionImpl();

public:
	bool operator ()(const Vector& v1, const LONG& r1, const Vector& v2, const LONG& r2, Vector& meet) const;

};

#define Collision CollisionImpl::GetReference()