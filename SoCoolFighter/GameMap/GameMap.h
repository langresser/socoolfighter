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
	std::string m_mapName;		// 地图模板名字
	CCSize m_mapSize;

	CCTMXTiledMap* m_tileMap;		// tilemap
	CCTMXObjectGroup* m_mapObjects;	// 地图物件集合，比如树，门

	CCTMXLayer* m_bgLayer;			// 从上面两个集合中取出的用于快速访问的集合
	CCTMXLayer* m_fgLayer;
	CCTMXLayer* m_extraLayer;
	CCTMXLayer* m_metaLayer;
};