#pragma once
#include "Role.h"

class Hero : public Role
{
public:
	static Hero& instance();

	virtual void setPosition(const CCPoint& point);
};