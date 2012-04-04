#pragma once
#include "Common/Singleton.h"
class GameMap : public CCNode, public Singleton<GameMap>
{
public:
	void update(ccTime dt);
	static GameMap& instance();
public:
	GameMap();
	virtual ~GameMap();

	bool create(int mapId, const std::string& mapName);
	bool load();

	CCPoint cellToScreen(CCPoint position);
	CCPoint screenToCell(CCPoint positoin);

	CCTMXTiledMap* getTileMap();
	CCSize getMapSize() const;

	CCArray* m_npcSet;
private:
	int m_mapId;
	std::string m_mapName;		// ��ͼģ������
	CCSize m_mapSize;

	CCTMXTiledMap* m_tileMap;		// tilemap
	CCTMXObjectGroup* m_mapObjects;	// ��ͼ������ϣ�����������

	CCTMXLayer* m_bgLayer;			// ����������������ȡ�������ڿ��ٷ��ʵļ���
	CCTMXLayer* m_fgLayer;
	CCTMXLayer* m_extraLayer;
	CCTMXLayer* m_metaLayer;
};