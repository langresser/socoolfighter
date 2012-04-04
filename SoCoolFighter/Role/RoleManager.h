#pragma once

#include "Common/Singleton.h"
#include "Role.h"

class RoleManager : public Singleton<RoleManager>
{
public:
	void addRole(Role* role);
private:
	std::vector<Role*> m_allRole;
};