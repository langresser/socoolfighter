#pragma once

#include "Common/Singleton.h"
#include "Role.h"

struct ActionInfo
{
	int actionId;
	int frameStartIndex;
	int frameAmount;
	int frameInterval;
};

struct ActionFrameInfo
{
	int offsetX;
	int offsetY;
};

class RoleManager : public Singleton<RoleManager>
{
public:
	RoleManager();

	void addRole(Role* role);
	void loadNameConfig();
	void loadActionData();
	void loadActionFrameData();
	int getProIdByName(const std::string& name) const;
	int getActionIdByName(const std::string& name) const;
	ActionInfo getActionInfo(int pro, int action, int weapon) const;
	ActionFrameInfo getActionFrameInfo(int actionFullId, int frameIndex) const;
private:
	std::vector<Role*> m_allRole;
	std::map<std::string, int> m_actionNameMap;
	std::map<std::string, int> m_proNameMap;
	std::map<int, ActionInfo> m_allActionInfo;
	std::map<__int64, ActionFrameInfo> m_allActionFrameInfo;

};