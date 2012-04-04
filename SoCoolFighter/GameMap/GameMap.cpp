#include "stdafx.h"
#include "GameMap.h"

GameMap& GameMap::instance()
{
	static GameMap* s_gameMap = NULL;
	if (s_gameMap == NULL) {
		s_gameMap = new GameMap;
		s_gameMap->autorelease();
	}

	return *s_gameMap;
}

bool GameMap::create(int mapId, const std::string& mapName)
{
	m_mapId = mapId;
	m_mapName = mapName;
	return load();
}

GameMap::GameMap()
{
	
}

GameMap::~GameMap()
{
}

bool GameMap::load()
{
	char szTemp[256] = {0};
	snprintf(szTemp, sizeof(szTemp) - 1, "%s.tmx", m_mapName.c_str());
	m_tileMap = CCTMXTiledMap::tiledMapWithTMXFile(szTemp);
	addChild(m_tileMap);
	m_tileMap->setAnchorPoint(ccp(0, 0));

	m_bgLayer = m_tileMap->layerNamed("bg");
	m_fgLayer = m_tileMap->layerNamed("fg");
	m_extraLayer = m_tileMap->layerNamed("extras");
	m_metaLayer = m_tileMap->layerNamed("meta");

	m_mapObjects = m_tileMap->objectGroupNamed("go");

	if (m_mapObjects) {
		m_npcSet = CCArray::array();
		int objAmount = m_mapObjects->getObjects()->count();
		for (int i = 0; i < objAmount; ++i) {
			CCStringToStringDictionary* object = m_mapObjects->getObjects()->getObjectAtIndex(i);
			CCString* objectType = object->objectForKey("type");
			if (objectType->m_sString == "NPC") {
				m_npcSet->addObject(object);
			}
		}
	}
	

	CCSize tileSize = m_tileMap->getTileSize();
	CCSize mapSize =m_tileMap->getMapSize();

	m_mapSize.width = tileSize.width * mapSize.width;
	m_mapSize.height = tileSize.height * mapSize.height;

	return true;
}

CCPoint GameMap::cellToScreen(CCPoint position)
{
	CCSize tileSize = m_tileMap->getTileSize();
	CCSize mapSize =m_tileMap->getMapSize();

	int x = position.x * tileSize.width + 16;
	int y = mapSize.height * tileSize.height- position.y * tileSize.height - 16;
	return ccp(x, y);
}

CCPoint GameMap::screenToCell(CCPoint position)
{
	CCSize tileSize = m_tileMap->getTileSize();
	CCSize mapSize =m_tileMap->getMapSize();

	int x = position.x / tileSize.width;
	int y = mapSize.height * tileSize.height - position.y / tileSize.height;
	return ccp(x, y);
}

CCTMXTiledMap* GameMap::getTileMap()
{
	return m_tileMap;
}

CCSize GameMap::getMapSize() const
{
	return m_mapSize;
}

void GameMap::update(ccTime dt)
{

}
