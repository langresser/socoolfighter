#include "stdafx.h"
#include "RoleManager.h"
#include "common/jsoncpp/json/json.h"
#include <fstream>

void RoleManager::addRole(Role* role)
{
	m_allRole.push_back(role);
}

void RoleManager::loadActionData()
{
	FILE* fp = fopen("action.ini", "r");
	char szLine[256] = {0};
	while (fgets(szLine, sizeof(szLine) - 1, fp))
	{
		if (szLine[0] == '/' && szLine[0] == '/' || szLine[0] == '\r' || szLine[0] == '\n') {
			continue;
		}

		char szKey[64] = {0};
		char szValue[64] = {0};
		sscanf(szLine, "%[0-9]=%s", szKey, szValue);
		int key = atoi(szKey);
		int frameStart = 0;
		int frameEnd = 0;
		int frameInterval = 0;
		ActionInfo temp;
		temp.actionId = key;
		if (3 == sscanf(szValue, "%d,%d,%d", &frameStart, &frameEnd, &frameInterval)) {
			temp.frameStartIndex = frameStart;
			temp.frameAmount = frameEnd - frameStart + 1;
			temp.frameInterval = frameInterval;
		} else {
			temp.frameStartIndex = frameStart;
			temp.frameAmount = frameEnd - frameStart + 1;
			temp.frameInterval = 150;
		}

		m_allActionInfo[key] = temp;
	}

	fclose(fp);
}

void RoleManager::loadNameConfig()
{
	ifstream file("nameconfig.json");
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(file, root, false)) {
		CCLOG("load nameconfig.json error");
	}

	Json::Value actionValue = root["action"];
	Json::Value::Members members = actionValue.getMemberNames();
	for (int i = 0; i < (int)members.size(); ++i) {
		m_actionNameMap[members[i]] = actionValue[members[i]].asInt();
	}
	members.clear();

	Json::Value proValue = root["pro"];
	members = proValue.getMemberNames();
	for (int i = 0; i < (int)members.size(); ++i) {
		m_proNameMap[members[i]] = proValue[members[i]].asInt();
	}
}

RoleManager::RoleManager()
{
	loadNameConfig();
	loadActionData();
	loadActionFrameData();
}

ActionInfo RoleManager::getActionInfo(int pro, int action, int weapon) const
{
	int key = pro * 10000000 + action + weapon * 10000;
	std::map<int, ActionInfo>::const_iterator itr = m_allActionInfo.find(key);
	if (itr != m_allActionInfo.end()) {
		return itr->second;
	}

	// 使用默认武器查找
	key = pro * 10000000 + action;
	itr = m_allActionInfo.find(key);
	if (itr != m_allActionInfo.end()) {
		return itr->second;
	}

	CCLOG("action  %d  not found", key);
	return m_allActionInfo.begin()->second;
}

int RoleManager::getProIdByName(const std::string& name) const
{
	std::map<std::string, int>::const_iterator itr = m_proNameMap.find(name);
	if (itr == m_proNameMap.end()) {
		return 0;
	}

	return itr->second;
}

int RoleManager::getActionIdByName(const std::string& name) const
{
	std::map<std::string, int>::const_iterator itr = m_actionNameMap.find(name);
	if (itr == m_actionNameMap.end()) {
		return 0;
	}

	return itr->second;
}

void RoleManager::loadActionFrameData()
{
	FILE* fp = fopen("actionframe.ini", "r");
	char szLine[256] = {0};
	while (fgets(szLine, sizeof(szLine) - 1, fp))
	{
		if (szLine[0] == '/' && szLine[0] == '/' || szLine[0] == '\r' || szLine[0] == '\n') {
			continue;
		}

		char szKey[64] = {0};
		char szValue[64] = {0};
		sscanf(szLine, "%[0-9]=%s", szKey, szValue);
		__int64 key = _atoi64(szKey);
		int offsetX = 0;
		int offsetY = 0;
		ActionFrameInfo temp;
		if (2 == sscanf(szValue, "%d,%d", &offsetX, &offsetY)) {
			temp.offsetX = offsetX;
			temp.offsetY = offsetY;
		}

		m_allActionFrameInfo[key] = temp;
	}

	fclose(fp);
}

ActionFrameInfo RoleManager::getActionFrameInfo(int actionFullId, int frameIndex) const
{
	__int64 key = (__int64)actionFullId * 1000 + frameIndex;
	std::map<__int64, ActionFrameInfo>::const_iterator itr = m_allActionFrameInfo.find(key);
	if (itr != m_allActionFrameInfo.end()) {
		return itr->second;
	}

	ActionFrameInfo defaultInfo;
	defaultInfo.offsetX = 0;
	defaultInfo.offsetY = 0;
	return defaultInfo;
}